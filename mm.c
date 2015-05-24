//
// mm.c - Tiny malloc library
//
// NOTE TO STUDENTS: Replace this header comment with your own header
// comment that gives a high level description of your solution.
//
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "mm.h"
#include "memlib.h"

student_t student = { "Hyeon Kim", "2013-11392" };


// Single word (4) or double word (8) alignment
#define ALIGNMENT 8
// Rounds up to the nearest multiple of ALIGNMENT
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~0x7)
// Size of size_t
#define SIZE_T_SIZE (ALIGN(sizeof(size_t)))


//
// Initialize the malloc package.
//
int mm_init(void) {
  return 0;
}


//
// Allocate a block by incrementing the brk pointer. Always allocate a block
// whose size is a multiple of the alignment.
//
void *mm_malloc(size_t size) {
  int newsize = ALIGN(size + SIZE_T_SIZE);
  void *p = mem_sbrk(newsize);
  if (p == (void *)-1) {
    return NULL;
  } else {
    *(size_t *)p = size;
    return (void *)((char *)p + SIZE_T_SIZE);
  }
}


//
// Freeing a block does nothing.
//
void mm_free(void *ptr) {
}


//
// Implemented simply in terms of mm_malloc and mm_free
//
void *mm_realloc(void *ptr, size_t size) {
  void *newptr = mm_malloc(size);
  if (newptr == NULL) { return NULL; }

  size_t copySize = *(size_t *)((char *)ptr - SIZE_T_SIZE);
  if (size < copySize) { copySize = size; }

  memcpy(newptr, ptr, copySize);
  mm_free(ptr);
  return newptr;
}
