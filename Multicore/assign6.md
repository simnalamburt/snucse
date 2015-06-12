멀티코어 숙제6
========
김지현

K-means
--------
센트로이드 16, 데이터 수 1048576

스레드 수 | 성능
----------|----------
1         | 20.239860722
2         | 14.667493004
3         | 12.048880991
4         | 12.086308730
8         | 8.335200048
16        | 6.864693834
31        | 6.871733394
32        | 6.858923794

스레드 수는 아래 코드를 이용하여 조절했다.
```c
#include <omp.h>
/* ... */

omp_set_num_threads(16);
```

스레드 수가 32이면, 간혹가다가 실행시간이 40초 이상으로 극단적으로
느려지는경우가 있는데, 이러한 결과는 걸러내었다.

행렬 곱
--------
위 실험을 토대로 스레드 수를 제한시켜야한다는 사실을 알 수 있었다. 그래서 이하
실험들은 모두 31개의 스레드로 진행되었다.

ikj 순서로 루프를 돌고, 2048*2048
```c
omp_set_num_threads(31);
#pragma omp parallel for
for (size_t i = 0; i < width; ++i) {
  for (size_t k = 0; k < width; ++k) {
    for (size_t j = 0; j < width; ++j) {
      result[i*width + j] += lhs[i*width + k] * rhs[k*width + j];
    }
  }
}
```

스레드 수 | 성능
----------|----------
1         | 9.46048
2         | 2.43917
4         | 2.36918
8         | 1.33443
16        | 1.12647
31        | 0.979944
32        | 0.974735

### 루프에 따른 병렬화 성능비교
ijk 순서로 계산, 2048*2048

스레드 수 | i       | j       | k
----------|---------|---------|--------
1         | 13.3262 | 26.1869 | 19.5702
2         | 12.5457 | 13.0891 | 15.3761
4         | 1.95438 | 6.93723 | 15.7761
8         | 2.09495 | 3.76947 | 22.2628
16        | 2.14756 | 2.39504 | 35.0341
31        | 2.1448  | 2.15896 | 59.374
32        | 2.009   | 2.01432 |

##### i
```c
omp_set_num_threads(16);
#pragma omp parallel for
for (size_t i = 0; i < width; ++i) {
  for (size_t j = 0; j < width; ++j) {
    for (size_t k = 0; k < width; ++k) {
      result[i*width + j] += lhs[i*width + k] * rhs[k*width + j];
    }
  }
}
```

##### j
```c
omp_set_num_threads(16);
for (size_t i = 0; i < width; ++i) {
  #pragma omp parallel for
  for (size_t j = 0; j < width; ++j) {
    for (size_t k = 0; k < width; ++k) {
      result[i*width + j] += lhs[i*width + k] * rhs[k*width + j];
    }
  }
}
```

##### k
제일 안쪽 루프의 병렬화에는, OpenMP Reduction 기능이 사용되었다.
```c
omp_set_num_threads(16);
for (size_t i = 0; i < width; ++i) {
  for (size_t j = 0; j < width; ++j) {
    float sum = 0.0f;
    #pragma omp parallel for reduction (+:sum)
    for (size_t k = 0; k < width; ++k) {
      sum += lhs[i*width + k] * rhs[k*width + j];
    }
    result[i*width + j] = sum;
  }
}
```
제일 안쪽 루프를 Reduction으로 병렬화시키면 계산 결과가 살짝 다르게 나온다.
부동소수점 표기법은 라운딩 오프 에러때문에 덧셈 순서에 따라 오차가 발생할 수
있기 때문이다.

### `#pragma omp collapse`
자명한 형태의 중첩 for문을 하나로 합쳐서 병렬화 시켜주는 Directive이다. 아래와
같이 사용하면 된다.

```c
#pragma omp parallel for collapse(2)
for (size_t i = 0; i < width; ++i) {
  for (size_t j = 0; j < width; ++j) {
    for (size_t k = 0; k < width; ++k) {
      result[i*width + j] += lhs[i*width + k] * rhs[k*width + j];
    }
  }
}
```

32개 스레드로 2048*2048 행렬에 대해 계산하였을때의 결과는 `2.071607초`로,
collapse를 쓰지 않았을 경우에 비해 큰 차이는 나지 않았다.
