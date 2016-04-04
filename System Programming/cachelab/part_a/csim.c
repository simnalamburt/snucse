// 2013-11392 김지현
//
// 먼저 `getopt` 함수로 프로그램에 입력된 인자들을 과제 스펙이 주어진바와 같이
// 파싱한다. 그리고 주어진 인자를 통해 가상의 캐쉬 구조를 메모리에 생성한다.
// 가상 캐쉬 구조는 교과서에서 배운 바와 같이, 아래와 같은 구조로 되어있다.
//
//     Cache = [Set0, Set1, ..., SetA]    (A : set associativity)
//     SetN  = [Line0, Line2, ..., LineE] (E : number of cache line per set)
//
//     LineM = (valid_bit, tag, timestamp)
//
// `malloc`과 `calloc` 함수를 이용해 셋과 라인으로 이뤄진 2차배열을 초기화하고,
// 가상 캐쉬의 끝나면 `fscanf` 함수를 이용해 인자를 입력받는다. 이때, 과제
// 스펙에 의해 'I' 입력은 무시하고, 'M' 입력일경우 같은 위치를 두번 액세스한다.
//
// 캐쉬 액세스 시뮬레이션은 교과서에서 배운대로 하고, Eviction algorithm으로는
// LRU 를 썼다. 캐쉬 룩업이 발생할경우, 일단 처음엔 어드레스를 비트연산자로
// 마스킹하여 어느 셋인지를 고르고, 그 다음 캐쉬히트여부를 알아보기 위해
// 캐쉬라인을 순회하며 valid비트가 set 되어있고 동시에 어드레스와 같은 태그를
// 공유하는 캐쉬를 찾는다. 캐쉬히트에 실패할경우, 빈 캐쉬 자리를 찾기위해 캐쉬를
// 순회하며, 캐쉬에 빈 라인이 한라인도 없을경우 가장 쓰이지 않은지 오래된
// 캐쉬라인을 지우고 그자리에 캐쉬를 쓴다.
//
// timestamp는 [0, E) 범위의 정수값을 갖게하여, 특성 캐쉬라인에 액세스가
// 발생할때마다 그 캐쉬라인보다 덜 최근에 쓰인 캐쉬라인들의 타임스탬프가 1씩
// 감소하게 하여, 결과적으로 제일 가장 오랫동안 안쓰인 캐쉬라인의 타임스탬프값이
// 0이 되도록 하였다.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <getopt.h>
#include "cachelab.h"


//
// Virtual cache type structures
//
typedef struct {
  bool valid;
  int tag;
  int timestamp;
} line_t;

typedef struct {
  line_t *lines;
} set_t;

typedef struct {
  set_t *sets;
  size_t set_num;  // Number of set
  size_t line_num; // Number of lines per set
} cache_t;


//
// Global variables
//
cache_t cache = {};
int set_bits = 0, block_bits = 0; // Cache metadata
size_t hits = 0, misses = 0, evictions = 0; // Simulation results


void simulate(int addr);
int main(int argc, char *argv[]) {
  //
  // Parse parameter
  //
  FILE *file = 0;
  for (int opt; (opt = getopt(argc, argv, "s:E:b:t:")) != -1;) {
    switch (opt) {
      case 's':
        set_bits = atoi(optarg); // Number of set index bits
        cache.set_num = 2 << set_bits; // Number of sets
        break;
      case 'E':
        cache.line_num = atoi(optarg); // Number of lines per set (set associativity)
        break;
      case 'b':
        block_bits = atoi(optarg); // Number of block bits
        break;
      case 't': // Input filename
        if (!(file = fopen(optarg, "r"))) { return 1; }
        break;
      default:
        // Unknown option
        return 1;
    }
  }
  if (!set_bits || !cache.line_num || !block_bits || !file) { return 1; }


  //
  // Initialize virtual cache
  //
  cache.sets = malloc(sizeof(set_t) * cache.set_num);
  for (int i = 0; i < cache.set_num; ++i) {
    cache.sets[i].lines = calloc(sizeof(line_t), cache.line_num);
  }


  //
  // Parse trace input
  //
  char kind;
  int addr;
  // Parse only kind and access address, ignore access size,
  while (fscanf(file, " %c %x%*c%*d", &kind, &addr) != EOF) {
    // Ignore instruction load
    if (kind == 'I') { continue; }

    simulate(addr);
    if ('M' == kind) { simulate(addr); }
  }
  printSummary(hits, misses, evictions);


  //
  // Clean up
  //
  fclose(file);
  for (size_t i = 0; i < cache.set_num; ++i) { free(cache.sets[i].lines); }
  free(cache.sets);
  return 0;
}


void update(set_t *set, size_t line_no);
void simulate(int addr) {
  //
  // Get set index and tag bits from the address
  //
  //     31                           s+b                  b               0
  //     |             tag             |    set index      |    offset     |
  //
  size_t set_index = (0x7fffffff >> (31 - set_bits)) & (addr >> block_bits);
  int tag = 0xffffffff & (addr >> (set_bits + block_bits));

  // Select a set
  set_t *set = &cache.sets[set_index];

  // Look up for cache hit
  for (size_t i = 0; i < cache.line_num; ++i) {
    line_t* line = &set->lines[i];

    // Check if the cache line is valid
    if (!line->valid) { continue; }
    // Compare tag bits
    if (line->tag != tag) { continue; }

    // Cache hit!
    ++hits;
    update(set, i);
    return;
  }

  // Cache miss!
  ++misses;

  // Look up for empty cache line
  for (size_t i = 0; i < cache.line_num; ++i) {
    line_t* line = &set->lines[i];

    if (line->valid) { continue; }

    line->valid = true;
    line->tag = tag;
    update(set, i);
    return;
  }

  // No empty cache line, eviction!
  ++evictions;

  // Look up for least recently used cache line
  for (size_t i = 0; i < cache.line_num; ++i) {
    line_t* line = &set->lines[i];

    if (line->timestamp) { continue; }

    line->valid = true;
    line->tag = tag;
    update(set, i);
    return;
  }
}


void update(set_t *set, size_t line_no) {
  line_t *line = &set->lines[line_no];

  for (size_t i = 0; i < cache.line_num; ++i) {
    line_t *it = &set->lines[i];
    if (!it->valid) { continue; }
    if (it->timestamp <= line->timestamp) { continue; }

    --it->timestamp;
  }

  line->timestamp = cache.line_num - 1;
}
