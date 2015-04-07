시스템 프로그래밍 실습
========

과제 제출은 기본적으로 이메일을 쓴다.

```
To: tskim@dcslab.snu.ac.kr
CC: sjpark@dcslab.snu.ac.kr
Subject: sp_practices#_2013-11392_김지현
```

실습 서버: **sp02@sp.snucse.org**

Buffer Bomb
--------

### Background

*   Calling convention, Stack overflow
*   Subroutine, side-effects, 절차적 프로그래밍

*   Calling convention

    Caller는 파라미터를 어떻게 Callee로 넘길것인가?
    Callee는 어떻게 리턴값을 Caller에게 넘길것인가?
    실행 흐름을 어떻게 조정할것인가?

    우린 **IA-32**에만 집중한다

### IA-32 Calling Convention: Roles

Caller의 몫:

* 파라미터를 Callee에게 넘겨야 한다
* return address를 설정해야한다
* Callee에게 실행 흐름을 넘겨줘야한다

Callee의 몫:

* return address를 기억해야한다
* return address로 돌아가야한다

### Stack

x86에선 스택이 커질수록 메모리 값이 줄어듬 (High -> Low). **ESP**에 스택의 *top*이 저장되어있음

Stack Frame = Parameters + Return address, local variables
            = Parameter부터 *top* 까지의 공간

Stack Frame Pointer = 마지막 스택 프레임이 시작하는 주소 = **EBP** (Extended Base Pointer)

### Calling Step: Caller to Callee

1.  파라미터들을 코드의 역순으로 넣는다
1.  `call` 명령어 실행
    i.  return address를 스택에 `push`
    i.  PC를 서브루틴의 시작주소로 옮김

### Calling Step: Callee to C code

1.  이전 스택프레임 시작주소(EBP)를 스택에 `push`
1.  ESP를 EBP에 복사함 (EBP에 현재 스택프레임의 시작주를 저장해줌)
1.  Callee가 사용할 지역변수들을 위한 공간을 할당

### Calling Step: Return

1.  반환값을 EAX, EDX에 저장
1.  현재 EBP의 값을 ESP에 복사 (Callee의 스택프레임 사라짐)
1.  스택에서 pop한 값(Formal EBP)를 EBP에 저장
1.  `ret` 명령어 실행
    i.  스택에서 pop한 값(return address)로 PC를 설정함

### C & Asm Code

```bash
gcc -m32 -c code.c
objdump -d code.o
```

### Stack Overflow

```c
int foo(void) {
  char buf[8];
  gets(buf);
  return 1;
}
```

*   `gets()` store data until `\n` or `EOF` met.

*   What if `gets()` stored 16 bytes?

    Former EBP, Return address에 엉뚱한 값이 쓰이게됨

*   덮어쓰여진 Return address가 다른함수의 주소라면 어떻게될까?

    Unexpected function call

*   덮어쓰여진 Return address에 나쁜 코드가 들어있으면?

    뻥!

### Assignment

```sh
cp /home/sp_files/bufbomb/* ./

cat exploit.txt | ./hex2raw | ./bufbomb -u sp02
```

*   hex2raw: convert hex to raw binary, supports c style comment

    ```
    a0 b8   /* 헬렐레 */
    ```

*   makecookie: create your cookie

    ```
    ./makecookie sp02
    ```

*   bufbomb: executable to attack

*   Machine Code Generating

    ```
    echo 'push $0xc0ff33' > example.s
    gcc -m32 -c example.s
    objdump -d example.o
    ```

*   `objdump`

    ```sh
    objdump -d bufbomb
    ```

*   `strings`

    ```sh
    strings bufbomb
    ```

*   `gdb`

    런타임에 프로그램의 실행정보를 얻어오기

    ```gdb
    break getbuf
    run -u sjpark
    print $ebp
    print (void *)fizz
    print (void *)&global_value
    ```

과제가 4단계까지 있다.

1.  Return address를 덮어씌워서 `smoke()` 함수가 호출되게 해야됨

1.  `fizz()` 함수가 호출되게 하되, 함수 파라미터로 쿠키를 넘겨야함

1.  `bang()` 함수가 호출되게 하되, `global_value` 변수에 쿠키를 넣어야함

1.  `global_nitro`를 0이 아닌 값으로 세팅하고 `testn()` 를 호출한다

1.  `getbuf()` 함수가 `test`로 리턴되게 하게, 리턴밸류로 쿠키를 반환해야함

### Submission

`spp1_2013-11392_HyeonKim.zip` 에 `mission[0-3].txt` 를 넣는다. 그리고 코멘트로
설명을 좀 더 넣으삼

3월 16일 (월) 23:59:00 까지.

--------

### Micro Processor
State: registers, memory, clock, ...
Operation: Add, load, store, rising clock, ...

프로세서마다 다 다름. Complex & Not reusable

### ISA: Instruction Set Architecture
컴파일러 writer와 Processor designer 사이의 추상 레이어

### ISA: Compatibility
* 모든 프로세서가 같은 ISA를 사용하진 않음
  * IA32, PowerPC, ARM, ...
* Different models in same family are compatible in ISA level
  * Snapdragon & Exynos

### ISA: Policy & Mechanism
ISA implication: instructions be executed sequentially

ISA Implementation: 명령어들이 선형으로 실행되는것으로 보이지만, 실제로는 그
순서대로 꼭 수행할 필요가 없음. 결과만 같으면 됨. 이걸로 성능 최적화를 이룰 수
있음

### Why ISA?
asdf

Y86
--------
Subset of x86 (IA32). Simple ISA example for us

### Programmer-Visible State
State on assembly level

* esp: `push`, `pop`, `call`, `ret`, ...
* PC: program counter
* CC: condition code register
* Stat: for exception

### Instructions

initial | mean
--------|------
r       | register
m       | memory
i       | immediate

* *source*-*dest*-movl
* fn Operations
  * addl, subl, andl, xorl
* fn Conditions
  * le, l, e, ne, ge, g, jmp


asm               | opcode
------------------|-------
halt              | 0 0
nop               | 1 0
rrmovl rA, rB     | 2 0 rA rB
irmovl V, rB      | 3 0  F rB V
rmmovl rA, D(rB)  | 4 0 rA rB D
mrmovl D(rB), rA  |

### Instruction Encoding
First byte: 4-bit for code, following 4-bit for function

### Register Identifier
4-bit for register

### Little Endian
rmmovl %esp, 0x00012345(%edx)

40 42 45 23 01 00

### Exceptions
익셉션이 발생하면, Y86 실행이 그냥 멈춰버린다. 익셉션은 Stat 레지스터에 저장됨

### Y86 vs X86

SISC, RISC. 요즘은 x86도 SISC로 일단 읽고 내부적으로 RISC 형태의 마이크로
오퍼레이션으로 바꿈

### example
`.pos 0` 메모리의 어디에 올라갈지 정함

data도 메모리에 올라간다

### Tools

이름 | 설명
-----|-----
yas  | Y86 어셈블러
yis  | Y86 시뮬레이터. 실행 전후 스테이터스 변화를 보여줌

### Circuit Design using HDL
synchesis

### HCL: Hardware Control Language
HDL과 유사하지만, 제한되어있고 훨씬 간단해짐

```
bool eq = (a && b) || (!a && !b) # equal
bool out = (s && a) || (!s && b) # MUX
```

Word-level MUX

```
int A;
int B;
bool Eq = (A == B)
```

HCL `case` expression

```
[
  case_1 : expr_1;
  case_2 : expr_2;
  case_3 : expr_3;
]
```

HCL `for` Minimum

```
int Min3 = [
  A <= B && A <= C : A;
  B <= A && B <= C : B;
  1                : C;
];
```

HCL `set` Membership

```
bool s1 = code == 2 || code == 3;
bool s0 = code == 1 || code == 3;

// is same as
bool s1 = code in {2, 3};
bool s0 = code in {1, 3};
```

### SQE: Sequential Y86 Implementation
Using HCL, any ISA could be implemented

SEQ is a Y86 Implementation

SEQ uses sequential execution mechanism

seq-full.hcl

1. Fetch
1. Decode
1. Execute
1. Memory
1. PC-update

이걸 한 사이클 안에 처리함.

파란색으로 표시된건 이미 구현된것, seq-full.hcl은 각 시그널을 매핑할뿐

### 하버드 아키텍처
데이터랑 명령이 구분됨

### 과제

1.  Y86으로 간단한 프로그램 만들기

1.  SEQ 위에 `iaddl`, `leave` 명령어 만들기

    ```
    make VERSION=full

    cd seq
    ./ssim -t ../y86-code/asumi.yo
    ./ssim -t ../y86-code/asuml.yo
    ```

    ```
    ssh -X
    ./ssim -g ../y86-code/asumi.yo
    ```

    Correctness Test (this will not test `iaddl`, `leave`)

    ```
    cd ../y86-code; make testssim
    ```

### Submission

sp_practices2-1_2013-11392_김지현.zip

23일(월) 자정까지

--------

Pipeline
--------
Overlapped Execution

### Problem of SEQ
* 모든 명령어가 한 클럭 안에 끝남
  * 일부 명령의 게이트딜레이때문에 클럭속도가 제한받음
* Not every unit be fully utilized
  * 일부 명령어를 쓸때 안쓰고 노는 유닛들이 많음

### Multi-cycle Execution
한 명령어 실행을 여러 사이클로 나눔

Fetch -> Decode -> Execution

### Pipelining
### Pipelining: Non-uniform Cycles
Throughput is limited by slowest stage

### Pipelining Steps and Throughput
* 요즘 프로세서들은 15 스테이지를 씀
  * 프로세서 클락수를 높임
  * 디자이너들은 파이프라인 레지스터 딜레이를 줄이기위해 아주 조심스럽게 디자인함

### Branch Prediction & Roll back

### Dependence
* Flow dependence (true dependence)
* Anti dependence
* Output dependence
* Input dependence

* Data hazard
* Structural hazard
* Control hazard

### Resolving dependence
1.  Stalling

    Bubble 끼워넣기

1.  Forwarding

    Write Back을 잘게 두개로 쪼개서, 계산을 하자마자 바로 그 결과를 필요한곳에
    넘겨주기

### Assignment

런타임을 줄여보자.

`ncopy.ys`, `pipe-full.hcl` 을 수정하여 어떻게 빠르게 만들었는지, 왜 빨라지는지,
얼마나 빨라졌는지 등을 설명하기

* PIPE에 새 명령어 구현
* Re-order instruction of ncopy
* Loop unrolling on ncopy
* Replace groups of instructions with single instructions
* Delete some instructions

##### Rules
1.  `ncopy.ys`는 임의의 크기에 대해 작동해야함
2.  `ncopy.ys`는 `yis`와 함께도 잘 돌아가야함
    * `src`에서 `dst`로 잘 데이터가 복사되어야함.
    * 올바른 반환값이 `%eax`에 들어있어야함.
3.  `ncopy.ys`를 `yas`로 컴파일한 결과물이 1000바이트를 넘으면 안됨.
    * `./check-len.pl < ncopy.yo`
4.  `pipe-full.hcl`은 리그레션 테스트를 전부 통과해야함.

원래 CPE 10까지 줄이는게 기준이었음.

--------

> 3월 31일 화요일

캐쉬
--------

CPU 속도는 크게 증가했는데, 메모리 속도는 더디게 진화

### Memory Hierarchies
보통 빠를수록 용량이 작아짐 (trade-off)

일정 이상 속도의 메모리들은 휘발적이기도 함

전통적으로 있어왔던 구조. 폰노이만도 이런 구조가 생길것을 예상했음

### Cache
캐시 안에 셋이 여럿, 셋 안에 라인이 여럿.

한 라인 = Valid bit + 태그 + 캐쉬 내용

### Direct-Mapped Caches
하나의 셋에 하나의 라인만 있는 캐쉬. 데이터를 찾기 아주 간단하다. 셋 인덱스가
있으면, 추가연산 필요없이 valid bit만 보면 되기때문. 구현이 간단 -> 하드웨어적인
리소스가 적다 -> 싸다.

단점: Confilct에 의한 미스가 쉽게 발생한다.

Cache Trasing

컨플릭을 해결하는법: 패딩을 추가하여, 같은 셋 인덱스를 여러 변수가 공유하게 하지
않는다.

Eviction

### 왜 중간 비트를 셋 인덱스로 쓰는가?
Spacial locality

Locality? 한 메모리에 접근했다면 그 근처 메모리를 다시 접근할 확률이 높을경우,
이를 로컬리티가 높은 프로그램이라고 한다.

High-order bit를 인덱스로 쓰면 시퀀셜하게 메모리를 액세스하면 계속 캐시 미스가
남.

### Set associative caches
한 셋에 여러 라인이 들어감

1 < E < C / B

E: 한 셋당 라인 갯수
C: 캐패시티
B: 블록 사이즈

E-way associative cache

라인 선택이 느려지고 복잡해질 수 있다. 셋을 고른 후 태그를 비교해서 라인을 고름.
하드웨어를 써서 병렬적으로 비교하긴 하지만, 하드웨어가 복잡해진다. Eviction을
늦출 수 있다.

way의 값이 커질수록 태그 비교하는게 어려워지고 복잡해진다.

### Eviction Policy
* Not every conflict means eviction
* Eviction victim: cache line that will not be used soon
* 누구를 떨굴지 정하는 정책
  * LFU: Least Frequently Used
  * LRU: Least Recently Used
  * pseudo LRU

### Fully Associative Caches
E = C/B

셋이 하나뿐. Low eviction chance, complex line matching

TLB 캐쉬와 같이 아주 작은 cache에 쓰인다.

### Write Policy of Caches
내가 쓰려는 블럭이 캐쉬에 올라와있을수도있고, 그렇지 않았을수도 있다.

힛이 났다면 -> 캐쉬에 데이터 쓰고 잊으면 됨. 근데 캐쉬에 쓴 데이터는 언제
RAM으로 내려갈까?

##### Write-through
캐쉬에 쓸때 RAM에도 바로 써버린다

구현이 간단해짐, 그러나 데이터 트래픽이 증가함

##### Write-back
캐쉬에 쓰고, 나중에 eviction이 될때 RAM에 쓰자

트래픽이 최소화되지만, 하드웨어가 복잡해짐

##### Write-allocate


##### No-write-allocate
캐시가 미스되었을때, 캐쉬는 bypass 시켜버리고 바로 아래 레이어에 써버림. 주로
write-through와 함께 쓰임. 로컬리티가 나빠짐

### Intel i7 Cache Hierarchy
코어마다 L1 i-cache, L1-d-cache, L2 unified cache가 있고
모든 코어가 공유하는 L3 unified cache가 있음

i-cache와 d-cache를 나누는것의 장점

* 데이터랑 인스트럭션이 분리되어있어 좋긴함
* 캐쉬 히트율이 낮아짐
* 인스트럭션과 데이터가 동시에 액세스 가능해짐
* 두 캐쉬가 두 캐쉬의 특성에 맞게 최적화될 수 있음

### Performance and Cache Parameters
* 캐쉬가 클수록
  * 히트율이 증가
  * 하지만 히트타임이 감소
* 블록이 클수록
  * 스페이셜 로컬리티에 의한 히트율 증가
  * 템포러리 로컬리티에 의한 히트율 감소
  * 트래픽 증가 -> 미스 패널티 증가
* 어소시에이티비티가 클수록
  * ?

이번 과제
--------
캐쉬 시뮬레이터를 짤거임

```
valgrind --log-fd=1 --tool=lackey -v --trace-mem=yes pwd
```

트레이스 포맷

operation, address, size

* I: 명령어 로드
* M: 데이터 수정
* L: 데이터 로드
* S: 데이터 저장

I로 시작하는것은 무시

### csim-ref
우리가 과제로 만들것의 레퍼런스 구현체

valgrind로 만들어진 메모리 트레이스를 입력으로 받아, 캐쉬 히트, 미스, eviction
횟수를 출력해준다.

### Task
`csim-ref`와 같은 작동을 하는 프로그램을 `csim`이라는 이름으로 만들면 된다.

### Programming Rules
* 위에 주석으로 내 이름 학번 쓰고
* 어떻게 짰는지 설명을 쓰고
* 워닝 없이 컴파일 되도록 하고
* Instruction cache는 무시하고, data cache만 시뮬레이션 하면 되겠음
* 모든 접근이 한 블럭에 들어간다고 가정한다
* 8개의 케이스에 대해서만 올바른지 검사함, 케이스별로 3점씩, 마지막것은 6점,
  총 27점
* 코딩스타일 점수
* `.csim_results`는 안만들어도 됨
* `-v`랑 `-h` 옵션은 옵셔널임

`test-csim`, 채점기계임

### 힌트
* `traces/dave.trace`가 아주 짧은 트레이스임, 이걸 디버그할때 쓰셈
* 레퍼런스 프로그램같은경우 `-v` 옵션을 주면 왜 이게 히트이고 왜 이게 미스인지
  설명됨
* `getopt` 함수가 파라미터 파싱하는데에 좋음
* `L`, `S`와는 달리 `M`은 2히트 혹은 2미스, 등등 이렇게 될 수 있음

```
sp_practices3-1_2013-11392_김지현/
 - csim.c

sp_practices3-1_2013-11392_김지현.zip

to : tskim
cc : sjpark
```

--------

> 4월 7일

CPU 속도에 비해 메모리는 용량위주로 발전, 속도는 제자리. 메모리 월. 캐쉬, 메모리
하이어라키.

어떻게 짜면 캐쉬를 더 잘 활용할 수 있을까.

* 가장 안쪽 루프에 신경쓸것
* 스페이셜 로컬리티를 극대화시킬것 (시퀀셜 액세스)
* 한번 접근한 데이터라면 가능한한 빈번하게 사용할것

컴퓨터마다 캐시구조는 다 다름. 내가 짠 프로그램이 어디서 돌아갈지 모르는경우엔
어쩔 수 없다.

```
valgrind --log-fd=1 --tool=lackey -v --trace-mem=yes pwd
```

* 이름, 학번, 작동 설명
* 워닝 없이 컴파일
* 재귀호출 쓰지 말라
* 지역변수를 int만 써야하고, 스택에 들어가는 지역변수가 12개가 넘으면 안됨
* 입력(A)을 고치면 안됨
* 새 배열을 정의해서도 안되고, `malloc`과 같은 동적배열을 호출해서도 안됨
* 성능
  * 32x32 (300~600), 64x64, 61x67
  * 미스 카운트에 따라 점수가 나옴
* 코딩 스타일 점수

##### test-trans
자동으로 우리가 짠걸 정상적으로 작동하는지 체크하고, 점수를 냄

##### 힌트
* 캐쉬는 Direct mapped cache임
* [Blocking technique](http://csapp.cs.cmu.edu/public/waside/waside-blocking.pdf)
