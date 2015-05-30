//
// mm.c - Tiny malloc library
//
// Block은 아래와 같이 생겼음
//
// 0 ______ 4 _________________________________________ size+4 ___ size+8
// |  head  |                       payload                |  tail  |
// """"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
//
// head와 tail에는 payload의 길이(바이트)가 들어있다.
// 그리고 LSB에 allocated 여부가 저장되어있다.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

#include "mm.h"
#include "memlib.h"

student_t student = { "Hyeon Kim", "2013-11392" };


//
// Initialize the malloc package.
//
int mm_init(void) {
  uintptr_t end = (uintptr_t)mem_heap_hi() + 1;
  uintptr_t target = ((end + 3)/8 + 1)*8 - 4;
  mem_sbrk(target - end);
  return 0;
}


//
// Allocate a block by incrementing the brk pointer. Always allocate a block
// whose size is a multiple of the alignment.
//
void *mm_malloc(size_t size) {
  if (size & 0x7) {
    size &= ~0x7;
    size += 8;
  }

  assert(size % 8 == 0);

  void *mem = mem_sbrk(size + 8);
  if (mem == (void*)-1) { return NULL; }

  uint32_t *head = mem;
  uint32_t *tail = (uint32_t*)((uintptr_t)mem + 4 + size);

  *head = size | 1;
  *tail = size | 1;

  return (void*)((uintptr_t)mem + 4);
}


//
// Freeing a block does nothing.
//
void mm_free(void *ptr) {
}


//
// Implemented simply in terms of mm_malloc and mm_free
//
void *mm_realloc(void *old, size_t size) {
  void *new = mm_malloc(size);
  if (new == NULL) { return NULL; }

  uint32_t *head = (uint32_t*)((uintptr_t)old - 4);
  uint32_t oldsize = (*head & ~1);
  memcpy(new, old, oldsize);

  mm_free(old);
  return new;
}
