//
// mm.c - Tiny malloc library
//
// 한 Allocation block은 아래와 같은 형태를 갖고있다.
//
// 0 ______ 4 _________________________________________ size+4 ___ size+8
// |  head  |                       payload                |  tail  |
// """"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
//
// head와 tail에는 payload의 길이(바이트)가 들어있다.
// 그리고 LSB에 allocated 여부가 저장되어있다.
//
// 본 구현체는 기본적으로 free block 관리를 위해 Red-black tree를 사용한다.
//
// mm_free() 가 호출될때마다, free block들이 레드블랙트리에 삽입된다.
//
// mm_malloc()이 호출되면, free block들 중에서 요구된 size보다 큰 최소크기의
// free block을 찾는다(best-fit). 그러한 free block이 없을경우 새로 sbrk()
// 함수를 호출하며, 있을경우 그 블럭을 재활용한다. free block이 충분히 큰 경우
// free block을 쪼개어 남는부분을 다시 free block으로 만들어 레드블랙트리에
// 삽입한다.
//
// 본 구현체는 기본적으로 모든 free block을 만들때마다 코얼레싱을 시도한다.
// mm_free()가 호출되었을때, mm_malloc()이나 mm_realloc()이 호출된 도중
// allocation block의 스플리팅이 발생할때, 등 모든 free block이 생성될 때 마다
// 코얼레싱을 시도하기때문에 결과적으로 본 구현체에서는 절대 두 free block이
// 인접하여 위치하는 경우가 발생하지 않는다.
//
// mm_realloc()의 경우, 작아지는경우와 커지는 경우가 처리가 다르다.
//
// 작아지는 realloc의 경우 mm_alloc()때와 마찬가지로, 블럭을 줄어든 크기에 맞게
// 스플리팅한다. 이때 역시 스플리팅되어 생성된 free block은 오른쪽으로
// 코얼리싱을 시도한다.
//
// 커지는 realloc의 경우, 인접한 free block으로 코얼리싱을 시도하여 코얼리싱을
// 수행함으로써 realloc의 완수가 가능한경우 추가적인 메모리할당 없이
// 코얼리싱만으로 realloc을 수행하며, 불가능한경우엔 새로이 mm_malloc()을
// 호출한다. 이때 양쪽 모든 방향으로 코얼리싱이 가능한경우, 오른쪽방향이
// 우선되어 수행되는데 이는 왼쪽으로 코얼리싱할경우 저장되어있던 데이터를
// 이동시켜주는 연산이 필요하기때문이다.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "mm.h"
#include "memlib.h"

student_t student = { "Hyeon Kim", "2013-11392" };


//
// Red-black tree
//
typedef uint32_t data_t;
typedef enum { BLACK, RED } color_t;
typedef struct node {
  struct node *left, *right, *parent;
  color_t _color;
} node_t;

static inline data_t get_data(const node_t* this) {
  uintptr_t payload = (uintptr_t)this;
  uint32_t *head = (uint32_t*)(payload - 4);
  uint32_t size = (*head) & ~1;
  uint32_t *tail = (uint32_t*)(payload + size);
  assert(size == ((*tail) & ~1));

  return size;
}
static inline void set_data(node_t* this, data_t size) {
  assert((size & 1) == 0);

  uintptr_t payload = (uintptr_t)this;
  uint32_t *head = (uint32_t*)(payload - 4);
  uint32_t *tail = (uint32_t*)(payload + size);

  bool bit = (*head) & 1;
  *head = size | bit;
  *tail = size | bit;
}

static inline bool get_allocated(const node_t *this) {
  uintptr_t payload = (uintptr_t)this;
  uint32_t *head = (uint32_t*)(payload - 4);
  uint32_t size = (*head) & ~1;
  uint32_t *tail = (uint32_t*)(payload + size);
  bool bit = (*head) & 1;
  assert(bit == ((*tail) & 1));

  return bit;
}
static inline void set_allocated(node_t *this, bool allocated) {
  uintptr_t payload = (uintptr_t)this;
  uint32_t *head = (uint32_t*)(payload - 4);
  uint32_t size = (*head) & ~1;
  uint32_t *tail = (uint32_t*)(payload + size);

  if (allocated) {
    *head |= 1;
    *tail |= 1;
  } else {
    *head &= ~1;
    *tail &= ~1;
  }
}

static inline color_t get_color(const node_t *this) { return this == NULL ? BLACK : this->_color; }
static inline void set_color(node_t *this, color_t color) { this->_color = color; }

static void insert(node_t **root, node_t *node);
static node_t *best_fit(const node_t *root, data_t query);
static void delete(node_t **root, node_t *node);


//
// Global variable which holds root node's position
//
static node_t *root = NULL;


//
// Initialize the malloc package.
//
int mm_init(void) {
  root = NULL;

  // Preparation for 8 bytes alignment
  uintptr_t end = (uintptr_t)mem_heap_hi() + 1;
  uintptr_t target = ((end + 3)/8 + 1)*8 - 4;
  mem_sbrk(target - end);
  return 0;
}


//
// Helper functions
//
static inline size_t align(size_t size) {
  // Minimal size of payload
  if (size < sizeof(node_t)) {
    size = sizeof(node_t);
  }
  // 8 bytes alignment
  if (size & 0x7) {
    size &= ~0x7;
    size += 8;
  }
  assert(size % 8 == 0);
  return size;
}

static node_t *left_node(const node_t *n) {
  uintptr_t begin = (uintptr_t)mem_heap_lo();
  uintptr_t tag_left = (uintptr_t)n - 8;
  if (tag_left < begin + 4 + sizeof(node_t)) { return NULL; }
  uint32_t size_left = (*(uint32_t*)tag_left) & ~1;
  node_t *left = (node_t*)(tag_left - size_left);
  assert(get_data(left) == size_left);
  if (get_allocated(left)) { return NULL; }
  return left;
}

static node_t *right_node(const node_t *n) {
  uintptr_t end = (uintptr_t)mem_heap_hi() + 1;
  node_t *right = (node_t*)((uintptr_t)n + get_data(n) + 8);
  if (end <= (uintptr_t)right || get_allocated(right)) { return NULL; }
  return right;
}

static node_t *coalesce_left(node_t *n) {
  uint32_t size = get_data(n);
  node_t *left = left_node(n);
  if (left == NULL) { return n; }
  uint32_t size_left = get_data(left);
  delete(&root, left);

  size += size_left + 8;
  set_data(left, size);
  return left;
}

static void coalesce_right(node_t *n) {
  uint32_t size = get_data(n);
  node_t *right = right_node(n);
  if (right == NULL) { return; }
  uint32_t size_right = get_data(right);
  delete(&root, right);
  size += 8 + size_right;
  set_data(n, size);
}

static void try_split(node_t *prev, size_t size) {
  // Split existing free block if size is enough
  uint32_t prevsize = get_data(prev);
  uintptr_t new = (uintptr_t)prev + size + 8;
  assert(sizeof(node_t) % 8 == 0);
  if (new + sizeof(node_t) > (uintptr_t)prev + prevsize) { return; }

  // Resize existing free block
  set_data(prev, size);
  set_allocated(prev, true);

  // Initialize remaining free block
  node_t *n = (node_t*)new;
  n->left = n->right = n->parent = NULL;
  set_data(n, prevsize - size - 8);
  set_allocated(n, false);
  coalesce_right(n);
  insert(&root, n);

  //
  // Split된 이후의 block 은 아래와 같이 변한다
  //
  //                                    size   size+4   size+8      prevsize
  // 0_____________________________________|______|______|_______________|
  // |                  prev               | tail | head |      new      |
  // """""""""""""""""""""""""""""""""""""""""""""|"""""""""""""""""""""""
  //
}


//
// Allocate a block by incrementing the brk pointer. Always allocate a block
// whose size is a multiple of the alignment.
//
void *mm_malloc(size_t size) {
  size = align(size);

  // Try reuse existing free block
  node_t *prev = best_fit(root, size);
  if (prev != NULL) {
    // Reuse existing free block
    delete(&root, prev);
    set_allocated(prev, true);
    try_split(prev, size);
    return prev;
  } else {
    // No adequate free block, allocate memory from heap
    void *mem = mem_sbrk(size + 8);
    if ((intptr_t)mem == -1) { return NULL; }

    node_t *payload = (void*)((uintptr_t)mem + 4);
    set_data(payload, size);
    set_allocated(payload, true);

    return payload;
  }
}


//
// Freeing a block does nothing.
//

void mm_free(void *_n) {
  node_t *n = _n;
  assert(get_data(n) >= sizeof(node_t));

  // Coalescing
  coalesce_right(n);
  n = coalesce_left(n);

  n->left = n->right = n->parent = NULL;
  set_allocated(n, false);

  // Insert free block into the red-black tree
  insert(&root, n);
}


//
// Implemented simply in terms of mm_malloc and mm_free
//
void *mm_realloc(void *prev, size_t size) {
  size = align(size);
  uint32_t prevsize = get_data(prev);

  if (prevsize > size) {
    // Shrinking
    try_split(prev, size);
    return prev;
  } else if (prevsize < size) {
    // Enlarged
    node_t *right = right_node(prev);
    if (right != NULL && size <= prevsize + 8 + get_data(right)) {
      coalesce_right(prev);
      try_split(prev, size);
      return prev;
    }

    node_t *left = left_node(prev);
    if ((left != NULL && size <= prevsize + 8 + get_data(left)) ||
        (right != NULL && left != NULL && size <= get_data(left) + 8 + prevsize + 8 + get_data(right)))
    {
      coalesce_left(prev);
      memmove(left, prev, prevsize);
      set_allocated(left, true);
      try_split(left, size);
      return left;
    }

    void *new = mm_malloc(size);
    if (new == NULL) { return NULL; }
    memcpy(new, prev, prevsize);
    mm_free(prev);
    return new;
  } else {
    // Same
    return prev;
  }
}


//
// Red-black tree implementation
//
static node_t *grandparent(const node_t *n) {
  return n != NULL && n->parent != NULL ? n->parent->parent : NULL;
}

static node_t *uncle(const node_t *n) {
  node_t *g = grandparent(n);
  if (g == NULL) { return NULL; }

  return n->parent == g->left ? g->right : g->left;
}

static node_t *sibling(const node_t *n) {
  assert(n != NULL);
  assert(n->parent != NULL);

  return n == n->parent->left ? n->parent->right : n->parent->left;
}

static void replace_node(node_t **root, node_t *old, node_t *new) {
  if (old->parent == NULL) {
    // old is root
    *root = new;
  } else if (old == old->parent->left) {
    // old is on parent's left
    old->parent->left = new;
  } else {
    // old is on parent's right
    old->parent->right = new;
  }

  if (new == NULL) { return; }
  new->parent = old->parent;
}

static node_t *maximum_node(node_t *n) {
  assert(n != NULL);
  while (n->right != NULL) {
    n = n->right;
  }
  return n;
}

static void swap_node(node_t *lhs, node_t *rhs) {
  assert(lhs != NULL);
  assert(rhs != NULL);
  assert(lhs->right != rhs);

  // Swap color
  color_t c = get_color(rhs);
  set_color(rhs, get_color(lhs));
  set_color(lhs, c);

  if (lhs->left == rhs) {
    lhs->left = rhs->left;
    rhs->parent = lhs->parent;
    lhs->parent = rhs;
    rhs->left = lhs;
    rhs->right = lhs->right;
    lhs->right = NULL;
    rhs->right->parent = rhs;
    if(lhs->left != NULL) {
      lhs->left->parent = lhs;
    }
    if (rhs->parent != NULL) {
      if(rhs->parent->left == lhs) {
        rhs->parent->left = rhs;
      } else {
        rhs->parent->right = rhs;
      }
    }
    return;
  }

  void swap_addr(node_t**, node_t**);

  // Swap backref
  if (lhs->left != NULL && rhs->left != NULL) {
    swap_addr(&lhs->left->parent, &rhs->left->parent);
  } else if (lhs->left != NULL) {
    lhs->left->parent = rhs;
  } else if (rhs->left != NULL) {
    rhs->left->parent = lhs;
  }

  if (lhs->right != NULL && rhs->right != NULL) {
    swap_addr(&lhs->right->parent, &rhs->right->parent);
  } else if (lhs->right != NULL) {
    lhs->right->parent = rhs;
  } else if (rhs->right != NULL) {
    rhs->right->parent = lhs;
  }

  node_t **l_backref = lhs->parent == NULL ? NULL :
    lhs->parent->left == lhs ? &lhs->parent->left : &lhs->parent->right;
  node_t **r_backref = rhs->parent == NULL ? NULL :
    rhs->parent->left == rhs ? &rhs->parent->left : &rhs->parent->right;
  if (lhs->parent != NULL && rhs->parent != NULL) {
    swap_addr(l_backref, r_backref);
  } else if (lhs->parent != NULL) {
    *l_backref = rhs;
  } else if (rhs->parent != NULL) {
    *r_backref = lhs;
  }

  // Swap itself
  swap_addr(&lhs->parent, &rhs->parent);
  swap_addr(&lhs->left, &rhs->left);
  swap_addr(&lhs->right, &rhs->right);
}

void swap_addr(node_t **lhs, node_t **rhs) {
  void *t = *rhs;
  *rhs = *lhs;
  *lhs = t;
}

static void rotate_left(node_t *n) {
  assert(n != NULL);

  node_t *c = n->right;
  node_t *p = n->parent;

  if (c->left != NULL) {
    c->left->parent = n;
  }

  n->right = c->left;
  n->parent = c;
  c->left = n;
  c->parent = p;

  if (p == NULL) { return; }
  if (p->left == n) {
    p->left = c;
  } else {
    p->right = c;
  }
}

static void rotate_right(node_t *n) {
  assert(n != NULL);

  node_t *c = n->left;
  node_t *p = n->parent;

  if (c->right != NULL) {
    c->right->parent = n;
  }

  n->left = c->right;
  n->parent = c;
  c->right = n;
  c->parent = p;

  if (p == NULL) { return; }
  if (p->left == n) {
    p->left = c;
  } else {
    p->right = c;
  }
}


//
// Insert
//
void insert(node_t **root, node_t *n) {
  assert(root);

  // If root is NULL, set n as root and return
  if (*root == NULL) {
    set_color(n, BLACK);
    (*root) = n;
    return;
  }

  // Standard BST insertion
  node_t *y, *x = (*root);
  while (x != NULL) {
    y = x;
    x = (get_data(n) < get_data(x)) ? x->left : x->right;
  }
  set_color(n, RED);
  n->parent = y;
  if (get_data(n) < get_data(y)) {
    y->left = n;
  } else {
    y->right = n;
  }

  // Fixup red-black tree
  void insert_rec(node_t*);
  insert_rec(n);

  // Correct root node's position
  while ((*root)->parent != NULL) {
    assert(*root != (*root)->parent);
    *root = (*root)->parent;
  }
}

void insert_rec(node_t *n) {
  assert(n);

  // Case 1
  if (n->parent == NULL) {
    set_color(n, BLACK);
    return;
  }

  // Case 2
  if (get_color(n->parent) == BLACK) { return; }

  // Case 3
  node_t *u = uncle(n);
  if ((u != NULL) && (get_color(u) == RED)) {
    set_color(n->parent, BLACK);
    set_color(u, BLACK);
    node_t *g = grandparent(n);
    set_color(g, RED);
    return insert_rec(g);
  }

  // Case 4
  node_t *g = grandparent(n);
  if ((n == n->parent->right) && (n->parent == g->left)) {
    rotate_left(n->parent);
    n = n->left;
  } else if ((n == n->parent->left) && (n->parent == g->right)) {
    rotate_right(n->parent);
    n = n->right;
  }

  // Case 5
  set_color(n->parent, BLACK);
  g = grandparent(n);
  set_color(g, RED);
  if (n == n->parent->left) {
    rotate_right(g);
  } else {
    rotate_left(g);
  }
}


//
// Best fit
//
node_t *best_fit(const node_t *n, data_t query) {
  if (n == NULL) { return NULL; }
  if (get_data(n) == query) { return (node_t*)n; }
  if (get_data(n) < query) { return best_fit(n->right, query); }

  node_t *try = best_fit(n->left, query);
  if (try == NULL || get_data(try) < query) { return (node_t*)n; }
  return try;
}


//
// Removal
//
void delete(node_t **root, node_t *n) {
  if (n == NULL) { return; }
  if (n->parent == NULL && n->left == NULL && n->right == NULL) {
    assert(*root == n);
    *root = NULL;
    return;
  }

  if (n->left != NULL && n->right != NULL) {
    // Copy key/value from predecessor and then delete it instead
    node_t *pred = maximum_node(n->left);
    swap_node(n, pred);
  }

  assert(n->left == NULL || n->right == NULL);
  node_t *child = n->right == NULL ? n->left  : n->right;
  if (get_color(n) == BLACK) {
    set_color(n, get_color(child));

    void delete_rec(node_t*);
    delete_rec(n);
  }
  replace_node(root, n, child);
  if (n->parent == NULL && child != NULL) {
    // root should be black
    set_color(child, BLACK);
  }

  // Correct root node's position
  if (*root == NULL) { return; }
  while ((*root)->parent != NULL) {
    assert(*root != (*root)->parent);
    *root = (*root)->parent;
  }
}

void delete_rec(node_t *n) {
  // Case 1
  if (n->parent == NULL) { return; }

  // Case 2
  if (get_color(sibling(n)) == RED) {
    set_color(n->parent, RED);
    set_color(sibling(n), BLACK);
    if (n == n->parent->left) {
      rotate_left(n->parent);
    } else {
      rotate_right(n->parent);
    }
  }

  // Case 3
  if (get_color(n->parent) == BLACK &&
      get_color(sibling(n)) == BLACK &&
      get_color(sibling(n)->left) == BLACK &&
      get_color(sibling(n)->right) == BLACK)
  {
    set_color(sibling(n), RED);
    return delete_rec(n->parent);
  }

  // Case 4
  if (get_color(n->parent) == RED &&
      get_color(sibling(n)) == BLACK &&
      get_color(sibling(n)->left) == BLACK &&
      get_color(sibling(n)->right) == BLACK)
  {
    set_color(sibling(n), RED);
    set_color(n->parent, BLACK);
    return;
  }

  // Case 5
  if (n == n->parent->left &&
      get_color(sibling(n)) == BLACK &&
      get_color(sibling(n)->left) == RED &&
      get_color(sibling(n)->right) == BLACK)
  {
    set_color(sibling(n), RED);
    set_color(sibling(n)->left, BLACK);
    rotate_right(sibling(n));
  } else if (n == n->parent->right &&
      get_color(sibling(n)) == BLACK &&
      get_color(sibling(n)->right) == RED &&
      get_color(sibling(n)->left) == BLACK)
  {
    set_color(sibling(n), RED);
    set_color(sibling(n)->right, BLACK);
    rotate_left(sibling(n));
  }

  // Case 6
  set_color(sibling(n), get_color(n->parent));
  set_color(n->parent, BLACK);
  if (n == n->parent->left) {
    assert(get_color(sibling(n)->right) == RED);
    set_color(sibling(n)->right, BLACK);
    rotate_left(n->parent);
  } else {
    assert(get_color(sibling(n)->left) == RED);
    set_color(sibling(n)->left, BLACK);
    rotate_right(n->parent);
  }
}
