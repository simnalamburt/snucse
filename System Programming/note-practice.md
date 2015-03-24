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
