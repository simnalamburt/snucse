//
// mm.c - Tiny malloc library
//
// NOTE TO STUDENTS: Replace this header comment with your own header
// comment that gives a high level description of your solution.
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

  void *p = mem_sbrk(size + 8);
  if (p == (void*)-1) { return NULL; }

  return (void*)((uintptr_t)p + 4);
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

  memcpy(newptr, ptr, size);
  mm_free(ptr);
  return newptr;
}
