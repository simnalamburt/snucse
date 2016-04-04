// 2013-11392 김지현
//
// 이 문제의 핵심은, 문제에 주어진 조건으로 Matrix Transpose를 수행하게 될때,
// 내가 Matrix의 각 원소들을 접근할때 그 원소들의 set index가 무엇이 될 지를
// 표로 모두 그려보는것이다.
//
// 캐쉬가 s = 5, E = 1, b = 5 로 주어지기때문에 아래와 같은 성질들이 있다:
//
// 1.  Direct Mapped Cache 이다. Set index가 같지만 Tag가 다른 메모리를
//     한번씩이라도 접근하면 즉시 Eviction이 발생한다.
// 2.  셋이 총 32개이다.
// 3.  라인당 크기가 총 32바이트이다.
//
// 32x32, 64x64, 67x61 세가지 경우에 따라 풀이방법을 달리하여야 한다.
//
// 세가지 경우에 모두 적용되는 풀이는, Eviction을 최소화하고 하더라도 Cold
// miss일때 일으키도록 하는것이다. 매트릭스의 모든 부분을 한번에 계산하려
// 하지말고, 매트릭스를 캐쉬라인 안에 들어가는 여러 부분으로 나누어
// 계산하면 쉽다. 67x61은 매트릭스를 여러 8x8 부분으로 나누어 푸는것만으로
// 만점이다.
//
// 32x32는 8x8부분으로 나누되, 종이에 각 엘레먼트에 액세스할때 사용되는 set
// index를 손으로 써보면, i와 j가 같을때 "output[i][j] = input[j][i]" 연산을
// 수행하는것이 eviction을 일으킨다는것을 알 수 있다. 액세스 순서를 많이
// 조작하면 Eviction을 완전히 피할 수도 있겠으나, 이 문제의 경우 "i == j" 인
// 경우를 각 블럭별 연산의 맨 마지막에 따로 처리해주는것만으로 만점을 얻을 수
// 있다.
//
// 64x64의 경우 set index 를 종이로 그려보면 가까운 위치상의 엘레먼트들이 같은
// set index를 공유하는경우가 많아 캐쉬 최적화가 어려움을 알 수 있다. 일단
// 매트릭스를 모두 8x8 부분으로 나눈 후, 부분의 윗쪽 반(8x4)과 아랫쪽 반(8x4)이
// 같은 set index를 공유하므로 따로 처리해줘야함을 알 수 있다.
//
// 만약 output의 set index를 기준으로 윗쪽 반과 아랫쪽 반을 처리한다고했을때,
// input의 set index를 기준으로는 왼쪽 반과 오른쪽 반을 액세스하게되는데 이때
// eviction이 반드시 일어난다. 이를 최소화하기위해 ㅡ eviction을 조금이라도 덜
// 일으키기위해 input 왼쪽 반의 첫번째줄은 액세스할때 미리 변수들에
// 캐시시켜놔서, 오른쪽 반 루프를 돌때 루프를 한번 덜 돌아서 캐시미스 횟수를
// 줄일 수 있다.

#include <stdio.h>
#include "cachelab.h"

typedef void (*per_block_t)(int M, int N, int input[N][M], int output[M][N], int row, int col);
void square(int M, int N, int input[N][M], int output[M][N], int row, int col);
void square_hard(int M, int N, int input[N][M], int output[M][N], int row, int col);
void naive(int M, int N, int input[N][M], int output[M][N], int row, int col);

void transpose(int M, int N, int input[N][M], int output[M][N])
{
  per_block_t per_block;
  if (M == 32 && N == 32) {
    per_block = square;
  } else if (M == 64 && N == 64) {
    per_block = square_hard;
  } else {
    per_block = naive;
  }

  for (int row = 0; row < N; row += 8) {
    for (int col = 0; col < M; col += 8) {
      per_block(M, N, input, output, row, col);
    }
  }
}

void square(int M, int N, int input[N][M], int output[M][N], int row, int col) {
  if (row != col) { return naive(M, N, input, output, row, col); }

  // Special handling for same block
  for (int i = row; i < row + 8 && i < N; ++i) {
    int tmp = input[i][i];
    for (int j = col; j < col + 8 && j < M; ++j) {
      // "output[j][i] = input[i][j]" for same i, j will cause cache miss.
      if (i == j) { continue; }
      output[j][i] = input[i][j];
    }
    output[i][i] = tmp;
  }
}

void square_hard(int M, int N, int input[N][M], int output[M][N], int row, int col) {
  // 첫번째줄 미리 캐싱
  int *t = &input[col][row + 4];
  int a = t[0], b = t[1], c = t[2], d = t[3];

  // output의 윗쪽 반
  for (int k = 0; k < 8; ++k) {
    int *t = &input[col + k][row];
    int a = t[0], b = t[1], c = t[2], d = t[3];
    t = &output[row][col + k];
    t[0] = a; t[64] = b; t[128] = c; t[192] = d;
  }

  // output의 아랫쪽 반
  for (int k = 7; k > 0; --k) {
    int *t = &input[col + k][row + 4];
    int a = t[0], b = t[1], c = t[2], d = t[3];
    t = &output[row + 4][col + k];
    t[0] = a; t[64] = b; t[128] = c; t[192] = d;
  }

  // 캐싱된 첫번째줄 사용
  t = &output[row + 4][col];
  t[0] = a; t[64] = b; t[128] = c; t[192] = d;
}

void naive(int M, int N, int input[N][M], int output[M][N], int row, int col) {
  for (int i = col; i < col + 8 && i < M; ++i) {
    for (int j = row; j < row + 8 && j < N; ++j) {
      output[i][j] = input[j][i];
    }
  }
}

void registerFunctions() { registerTransFunction(transpose, "Transpose submission"); }
