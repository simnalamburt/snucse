시스템 프로그래밍
========

> 3월 3일

* 컴구의 내용을 알아야 수업을 할수있음

### Introducing Computer Systems from a Programmer's Perspective

- Randal E. Bryant, David R. O'Hallaron
- Computer Science and Electrical Engineering
- Carnegie Mellon University

### Outline

Introduction to Computer Systems

* Course taught at CMU since Fall, 1998

학생들에게 무엇을 제일 먼저 가르쳐야 하는가? 어떤 언어를 가르치는것이 제일
좋은것인가? 지난 30년동안 제일 싸워가면서 굉장히 많이 바뀌어왔다. 지금은 좀
먼지가 가라앉은것같은데 여전히 ㄱ싸우긴함. 지금 두가지 진영이 있는데, 한 진영은
우리학교처럼 C를 먼저 가르치는 긴영, 한 진영은 카이스트처럼 파이썬을 먼저
가르치는 진영. 이건 중국집악서 짜장면 짬뽕가은 둘다 장단이 있고 정답은 없음.
가장 기본적인 프로그래밍이라는것을 배웠다고 치면, 헬로월드는 쓸수 있다고 치고,
이제 시간이 지나면 그 다음엔 컴퓨터 시스템이라는게 어떻게 생겼는지. 컴퓨터가
뭐하는거냐는 대부분 알고있는데, 컴퓨터 시스템이라는건 뭐냐. 이 속에 뭐가
들어있어서 이러한 일을 할 수 있게 하는건가. 컴퓨터 시스템이라는걸 어떻게
가르칠거냐.

제일 좋은 생각은 컴퓨터를 뜯어서 보여주는것. CPU는 이렇게 생겼다. 그래픽카드는
이렇게 새겼다. 각자가 하는일을 설명해주고. 더 나아가서는 뚜껑을 열어서
안에있는걸 보여주는게 더 나은데 CPU를 열어준다고 이게 뭐가 보이나? 확대경을
가져와서 보여줘동 ㅏ무것도 안보이는데.노트북 데스크탑은 눈에 보이는데 이속에서
무슨일이 일어나는지는 알수가 업다. 블랙박스 처럼. 이 속에서 무슨일이
일어나는지를 가르쳐보자 하는것이 바로 이 **책**이다. 단, 컴퓨터를 만드는 사람읭
ㅣㅂ장이 아니라 컴퓨터 프로그램을 프로그래킹 하는 프로그래머의 입장에서 짜는것.
내가 프로그래머가 아니고 뭐 한글가지고 웹서핑하고 이런일이나 하면 이게 필요가
없다. 하지만 프로그램을 만들어서 커다랑 시스템을 만든다 하면 바로 이걸
배워야된다 이거임.

### Computer Arithmetic

*Builder's Perspective*

컴퓨터를 만드는사람의 입장에서 봤을떄엔 얘네는 계싼을 하는 회로가 컴퓨터를
이루는 근간. 게이트를 만들어서 어떻게 신호가 빠르게 움직이게 하는지. 윗쪽에서
시그날이 오면 어떻게 아웃풋이 나가는지. 전자가 움직이는 속도는 정해져있으니
중간에 거쳐가는 게이트가 몇개가 있는지에 따라 시간이 결정되겠지? 게이트가 두개면
2, 게이트가 열개면 10, 이러한 서킷을 디자인하는사람들은 어떻게하면 이 DEpth를
어떻게 낮출수 있는지, 열개까지 거치지 않고 한두개만 통과하게 할지, 혹은 이
게이트 서킷 하나하나의 시간을 ㅈㄹ이는것이 목표. 내가 컴퓨터를 만드는사람이면
이것이 목표

*Programmer's Perspective*

프로그래머의 입장에선 이제 저 전자회로는 별 상관이 없다. 프로그래머 입자에선
그냥 프로그램을 짜ㅈㅆ을떄 결과가 나오고 잘 돌아가면 되는거야. 이 컴퓨터라는건
이런 프로그램을 만들어서 집어넣으면 돌아가면서 아웃풋이 나오는것이 컴퓨터가
이것이 바로 프로그래머가 알고잇는 전부죠.

(예제를 보여줌) 이렇게 이런 프로그램을 짰으면 엑스가
오부터 오십, 오백만까지 쭉 늘어나면서 제곱을 하면서 프린트할텐데, 이것을 과연
돌리면 어떤일이 일어나느냐 (인티저 오버플로우) 여기까지는 내가 무슨짓을 했는지
알수있겠는데 여기선 왜 갑자기 이게 음수가 되고, 이 다음엔 왜 갑자기 양수가 되고
이 다음부턴 무슨일이 일어나느냐? 이건 내가 원하는 결과가 아니잖아. 여기까지는
0이 두개씩 붙었고 그 다음도 0이 두개 붙는데, 이 다음은 왜 내가 원하는 결과가
안나오는가? 이런이리 발생하면 컴퓨터를 어떠ㄱㅎ게 해야하는가? 컴퓨터를 갔다
버려야죠? 근데 이럴떄마다 컴퓨터를 버리면 작동하는 컴퓨터가 거의 없을ㄷ텐데
어떡해. 내가 원하는거랑 실제 결과가 다르면 어떻게 해야한ㄴ가? 프로그래머
입장에선 내가 안에 어떤 서킷이 있는지 아무것도 몰라. 내가 프로그램을 하지만
여기서 어떤일이 일어나고있는지 아무것도 몰라, 이런걸 할수있는것엔 한계가 있다.

이제 여러분한테 원하는건 이런일이 일어나지 않기 위해선 컴퓨터 시스템이 어떻게
돌아가는건지 좀 알려줘야겠다 이런거야. 만약 숫자를 손으로 쓴다고 하면 자릿수에
제한이 없지만 컴퓨터가 가지고 계산을 할수있는 숫자는 **Word**로 제한이 되어있다.
일정한 크기가 넘어가면 이쪽에 있는 비트들은 없어져버리는거야. 그거를 왜
위에있는걸 버리나? 밑에있는걸 버리면 더 좋을텐데? 혹은 왜 정수오버플로우가
일어나면 왜 컴퓨터가 말을 안해주나?

이제 이런일을 막기위해서 부동소수점 연산도 나왔다. 이러면 어느정도는 내가 원하는
결과를 얻을수있지. 그런걸 만들기위해선 밑에 돌아가는 원리를 알아야한다

### Memory System

*Builder's Perspective*

CPU, 레지스터, L1 data-cache, L1 instruction-cache, L2 unified cache, RAM, Disk

i-cache라는건 내가 다음에 실행할 명령어가 무엇인지 미리 저장해놓은것, 데이타
캐쉬는 내가 어떤걸 읽어서 어떤걸 쓸건지가 저장된것이 데이타 캐쉬.

보통 L1캐쉬는 자기혼자쓰고, 보통 L2캐쉬는 2~4개 코어가 같이 쓰더라. 그리고
L1에선 d캐쉬 i캐쉬가 따로있지만 L2에선 구분없이 같이쓰더라. 여기까진 L2밖에
없지만 이제 L3, L4가 있기도 하더라. 그리고 요즘은 디스크가 없이 SSD가 있는경우도
있더라. 이제 이런건 컴퓨터를 만드는사람의 입장. CPU는 얼마나 좋아야 하는가,
캐쉬와 램은 얼마나 커야하는지, Disk는 하드를 달건지 NAND Flash를 달건지 등등
여러가지를 결정해야한다. 캐쉬도 **라이트백 캐쉬, 라이트 스루 캐쉬**, **다이렉트
맵드, 인덱스드**, 메모리도 **동기, 비동기**, **가상 인덱싱, 피지컬 인덱싱** 등등
고려할게 많다.

*Programmer's Perspective*

프로그래머 입장에선 CPU가 있고 내가 쓸수있는 메모리가 얼마냐가 중요하죠. 근데
그렇다고 이제 내가 L1 L2 RAM 이런걸 다 몰라도 되느냐. 사실 이걸 안다고
도움된다고 생각되지 않을수도 있다. 하지만 이제 이걸 봐라.

(캐쉬 프렌들리한 프로그램 짜는 예시)

똑같이 2048*2048 매트릭스를 카피를 해도 row-wise로 카피하는거랑 column-wise하게
카피하는게 전혀 성능이 다르지않는가. (i7 2.7GHz에서 실험했을때 30배 느려짐) 이게
성능이 전혀 똑같다면 내가 메모리 구조를 전혀 신경 안써도 되겠지? 하지만 현실은
그리 녹록치 않다.

이제 이런걸 알면 내가 액세스하는 메모리는 다 똑같은데, 액세스 하는 방법에 따라
속도가 달라지는걸 볼수있다. 이렇게 속도차이가 많이나면 속에서 뭔가 메모리를
단순히 액세스하는거 외에 뭔가 한다는걸 알수있다 (캐싱). 이 숫자를 한번 줄여보자.
2048이 아니라 100, 200, 300, 400 등등 크기를 바꿔가며 또 해보자. 어떤 차이가
있을까? (캐시 바운더리)

결국 저 하드웨어 사이즈를 알수밖에 없다. 저 L1 데이터캐쉬 사이즈가 얼마인지.
L2로 가면 느려지지. L3로 가면 더 느려지고 RAM으로 가면 더더욱 느려지겠지. 지금
이 램이라는건 우리는 마치 이차배열을 이차원공간처럼 쓰지만 사실 이건 선형이다.
내가 이걸 row-wise로 하면 선형으로 쭉 읽겠지만 column-wise로 하면 내가 이 선형
메모리를 전체를 계속 훑겠지. 자 이럴때 보통 캐쉬는 한번 이곳을 읽으면 그 근처를
64바이트를 통쨰로 읽고, 쓸떄도 똑같이 한다. 이떄 여기서 전체를 계속 stride로 훑으면
중요한 memory bandwidth를 낭비하는거지. 이 현상이 왜 일어나느지, 어떻게
해결하는지를 알으려면 결국 이 메모리 하드웨어 구조를 알아야하는거야.

### 첫번쨰 숙제

앞으로 학생들이 주로 사용할 컴퓨터를 하나씩 정하세요. 그 다음에, 그 컴퓨터를
사용해서 방금 비슷한 프로그램을 짜서 (cache 프렌들리 예제) 이런식으로 버전을
두개 짜서 i j 순서가 다른것이 영향을 주는 예제를 짜봐. 이걸 실제로 크기를
바꿔가면서 해보면 L1~L2, L2~L3, L3~RAM 사이의 간격을 볼수있어. (계단식 그래프를
그림) 이걸 하나 그려보는게 첫번째 숙제다.

여러분들 종강할때 어느정도 레벨이 되려면 이 계산 돌리는걸 직접 하지말고 스크립트
짜서 자동화하세요. 이걸 그려보면 여러분의 캐쉬 사이즈가 대충 어느정도인지
가늠할수있을거야. 그리고 여러분 컴퓨터 스펙이랑 비교해서 얼마나 들어맞았는지
비교해봐.

굉장히 복잡하게 들리지만 사실 그렇지 않아. 여러분 컴퓨터가 너무 일을 많이해서
불쌍하다 싶으면 캐쉬 바운더리 근처만 돌려봐.

**다음주 화요일 실습시간까지**

### Memory Mountain

이쪽은 메모리 크기고, 이쪽은 메모리 스트라이드. 높이는 스루풋 (초당 얼마나 많이
읽느냐). 여러분이 숙제 1을 하면 이 메모리 마운틴을 그려볼수 있는거야. 그러면 L1
L2 크기가 얼마나 되는지 미루어 짐작할수 있겠지.

### Lecture Coverage

* Data representation
* IA32 & x86-64 asm
* Program optimization
* Memory Hierarchy
* Linking
  * With DLL
* Exceptional Control Flow
* Virtual Memory
* Application level concurrency
* I/O and network programming

### Labs

* Key teaching insight:
  * Cool labs => Great Course
* A set of 1 and 2 week labs define the course.
* 1~2주에 랩 하나씩 할거다.

1. Data lab
1. Bomb lab
1. Buffer lab
1. Performance lab
1. Shell lab
1. Malloc lab
1. Proxy lab

### Architecture

* Y86 명령어셋을 다 알아야한다 (간단한 IA32)

> 3월 5일

링킹
--------
시험범위 시작

메인이라는 함수가 있고 스왑이라는 함수가 있다. 어떻게 이 두개를 하나의
프로그램으로 붙일까? 그냥 소스를 하나로 concat 할수도있겠지. 근데 그러면 큰
의미가 없겠지? 이걸 컴파일 하고 컴파일된 결과를 어떻게 한개로 만들까?

### Static Linking

```
gcc -O2 -g -o p main.c swap.c
./p
```

main.c -> `cpp, cc1, as` -> main.o
swap.c -> `cpp, cc1, as` -> swap.o
main.o, swap.o -> `ld` -> p

*.c : 소스
*.o : separately compiled relocatable object files
p : executable, fullly linked, object file
    (contains code and data for all functions defined in main.c and swap.c)

### Why Linkers?

왜 링크가 필요할까?

1.  **증분빌드**. 프로그램의 일부만 고쳤을때 전체 리빌드를 하지
    않기위해서, 모듈 디자인을 하기 위해서.

    우리가 제일 많이 쉽게볼수있는게 리눅스 컴파일과정이야. 파일이 수백개가 있는데
    전부 다 컴파일하려면 수백개를 다시해야하지? 근데 이걸 일부를 고친다고 그
    몇시간을 다시 거친다는거는 무서운 일이지.

    **라이브러리**를 만들 수도 있지. 자주 쓰는 함수들을 미리 라이브러리로 만들어놓고,
    나중에 이걸 그냥 링크해서 쓸 수 있도록 만들 수 있겠지

2.  **Efficiency**

    Time: Separate compilation

    Space: Libraries

    라이브러리를 링크했을때 너가 그 라이브러리의 모든함수들을 다 쓰느냐. 그렇지
    않아, 링크과정에서 이 안쓰는 함수들을 뺼 수 있다.

### What does linker do

1.  Symbol resolution

    컴파일된 C 코드는 함수호출이 있는것은 알지만 이게 어느 어드레스의 함수인지는
    아직 모르지. 전역변수와 같것도 마찬가지지. 이걸 정해주는것이 링커의 역할

    ```
    void swap() { }
    swap();
    int *xp = &x;
    ```

2.  Relocation

    오브젝트파일이 여기에 100바이트, 여기에 200바이트 있을때 이걸 하나로
    합쳐줘야겠지. 근데 합쳐주는과정에서 여러가지 위치들이 바뀌겠지. 그리고 이걸
    실제로 실행하려고 메모리에 올릴때에 또 위치가 바뀌겠지. 그런 위치를 어떻게
    바꿀지 여기엔 10을 더한다 여기엔 100을 더한다, 레퍼런스들을 나중에 고칠수
    있도록 하는것이 링커의 역할

### Three kinds of object files (modules)

1.  `.o` Relocatable object file

1.  `a.out` Executable object file

1.  `.so` Shared object file

    여러 프로그램들이 공유하는 오브젝트파일. 로드타임이나 실행타임에 동적으로
    링크됨.

    윈도우에서는 `dll`, OS X 에선 `dylib`이라고 불림.

### Executable and Linkable Format (ELF)

* Standard binary format for object files

오브젝트 파일은 어떻게 만들어야 하는 Rule 이다. AT&T System V Unix 에서 만들어져
계속 쓰이는것이다.

### ELF Object file format

1.  Elf header

    워드 사이즈, 바이트 순서, 파일타입 (`.o`, exec, `.so`), 머신타입, 등

1.  Segment header table

    페이지 크기, virtual addresses memory segments (sections), segment sizes

1.  .text section: 코드
1.  .rodata section: readonly data (jump tables, ...)
1.  .data section: Initialized global variables
1.  .bss section

    Uninitialized global variables, ...

    실제로 실행되면 공간을 차지하지만, 오브젝트 파일에서는 차지할 공간의 크기,
    이름만 들어있지만 실행되는순간 메모리가 잡힘.

    "Block Started by Symbol", "Better Save Space"

1.  .symtab section

    symbol table. 주로 프로시저 이름, static variable name, section name, 등

1.  .rel.text section

    코드 세그먼트에 대한 relocation 정보. 코드에 들어있는 variable 에 대한
    reference들, 실행되면 위치를 바꿔줘야하는 정보들이 여기에 들어있다.
    일반적으로 이런걸 컴파일할때 제일 많이쓰는 방법은 data section에서 +100번지,
    현재 program counter에서 -100번지 등 현재 정해져있는 위치의 offset을
    사용한다.

1.  .rel.data section

    데이터 섹션에 대한 relocation 정보. 코드와 마찬가지로 실행되면 위치가
    바뀌어야 하는것들에 대한것들

1.  .debug section

    디버그심볼이 들어이씀

1.  섹션 헤더 테이블

    각각의 섹션의 오프셋과 크기

### Linker Symbols

*   Global symbols

    내가 쓰고, 다른 모듈에도 보이는 심볼

*   External symbols

    내가 쓰지만, 다른 모듈에서 정의된 심볼

*   Local symbols

    내가 정의하고 나만 쓰는 심볼

### Resolving Symbols

```c
// main.c
int buf[2] = {1, 2}; // Global

int main() // Global
{
  swap(); // External
  return 0;
}
```
```c
// swap.c
extern int buf[]; // External

int *bufp0 = &buf[0]; // Global
static int *bufp1; // Local

void swap() // Global
{
  int temp; // Linker knows nothing of temp

  bufp1 = &buf[1];
  temp = *bufp0;
  *bufp0 = *bufp1;
  *bufp1 = temp;
}
```

### Relocating Code and Data

표준 라이브러리

main.o

.text에 main() 코드가 들어가고
전역변수가 .data에 들어가고

swap.o

.text에 swap() 코드가 들어각
bufp0 가 .data에 들어가고
bufp1는 .bss 에 들어감. swap의 private 심볼이지만, bss에 들어감

이걸 링크하면

.text에 헤더, 시스템 코드, 메인, 스왑, 기타 시스템 코드

.data에 시스템 데이터, buf, bufp0

.bss에 bufp1

그밑에 .symtab, .debug

### Relocation Info (main)

objdump 떠서 보는것보단 -S 옵션줘서 어셈블리 파일 보는게 편함

1.  PC relative address:

    코드 안의 주소를 가리킬때, immediate 변수를 쓸때 이 방법을 사용함.

    ```
    R_X86_64_PC32

    ADDR(s) + *refptr(0) - refaddr

    ADDR(bufp1 - 0x8) - (PC - x8) = 0x601050 - 0x8 - (0x400511 - 0x8)
                                  = 0x200b3f
    ```

    PC는 항상 다음 실행할 opcode를 가리킴.

    링커에게 필요한건 operand가 encoding 된곳 주소임.

1.  `.data` relative address:

    Data segment에서 변수를 가져다 쓸때에 이 방법을 사용함.

1.  Absolute address: ADDR(s) + *refptr(0)

    ```
    R_X86_64_32S buf+0x4

    ADDR(buf + 0x4) = 0x601038 + 0x4
                    = 0x60103c
    ```

### Executable before/after relocation (.text)

relocation 하기 전에는 함수의 정보들이 main+12, asdf+x 이런식으로
들어있는데, relocation 한 이후엔 정확히 함수를 가리킴

### Strong and Weak symbols

*   Strong: Procedures and initialized globals. `.data` 에 들어감. object 파일
    안에 위치가 다 정해져있음
*   Weak: Uninitialized globals. `.bss` 에 들어감. 위치가 정해져있지 않고,
    메모리에 올라갈때 메모리가 정해짐

### Linker's Symbol Rules

1.  Multiple strong symbols are __not allowed__

    Each item should be defined only once. Otherwise; **Linker error**.

1.  Strong symbol과 weak symbol이 같이있을경우, strong symbol을 선택함.

    ```c
    // p1.c
    int foo = 5;
    p1() {

    }
    ```
    ```c
    // p2.c
    int foo; // <- p1의 foo 가 strong 이어서, 이 foo는 무시됨.
    p2 () {

    }
    ```

1.  Weak symbol이 여러개일경우, 링커 마음대로.

### Linker puzzles

`int x; p1(){}`, `p1(){}`: 에러, `p1`

`int x; p1(){}`, `int x; p2(){}`: OK

`int x; int y; p1(){}`, `double x; p2(){}`: **Evil**, writes to x in p2 might
overwite y

`int x=7; int y=5; p1() {}`, `double x; p2() {}`: Nasty, writes to x in p2 will
overwrite y

`int x=7; p1(){}`, `int x; p2() {}`: OK

### Nightmare scenario

Two identical weak structs, compiled by differenct compilers with different
alignment rules.

### Role of `.h` files

```c
// global.h
#ifdef INITIALIZE
int g = 23;
static int init = 1;
#else
int g;
static int init = 0;
#endif
```

`#ifdef` 매크로는 여러 하드웨어를 동시에 지원하기 위해서 만들어졌음.

`-DINITIALIZE` 옵션으로 같은 소스코드로 여러 프로그램을 만들 수 있음

### Global Variables

*   Avoid if you can
    - Side effect!
    - Scope does matter
    - 아까 나온 Weak symbol, strong symbol 문제
*   Instead,
    - Use `static` if you can
    - Initialize if you define a global variable
    - Use `extern` if you use external global variable

### Packaging commonly used functions

* How to package functions commonly used by programmers?
  * Math, I/O, memory managements, string manipulation, etc.

이걸 어떻게 패키징하는게 좋을까? 링킹을 함으로써 이것들을 가능케 할수 있다.

1.  함수들을 한 파일에 전부다 집어넣는다.

    그 `.o` 파일을 다른데서 링크하면 되지.

    근데 공간/시간 비효율적임

2.  그냥 여러 파일에 함수들을 퍼트려놓음.

    프로그래머가 힘들어짐

### Solution: Static Libraries

`.a`, archive files

*   잘쓰는 함수들이 들어있는 오브젝트 파일들을 전부 붙여놓음. 그리고 맨 앞에
    인덱스를 놓아서 이 함수가 어느 주소에 있는지 표시해서 필요한 함수만 가져가서
    링크할 수 있도록 함

```sh
ar rs libc.a atoi.o printf.o ... random.o
```

역시 증분 업데이트를 지원하고, 뒤에 필요한게 더 생기면 집어넣으면 됨

### Commonly Used Libraries

`libc.a` C 표준 라이브러리. 8MB, 1392 오브젝트

`libm.a` 수학 라이브러리. 1MB, 401 오브젝트

```sh
ar -t /usr/lib/libc.a | sort

# ...
# fpritf.o
# fpu_contro.o
# fputc.o
# ...
```

### Linking with static libraries

main2.o src.o libc.a libvector.a -> `ld` -> exe

### Using Static Libraries

링커를 호출했을때 나열된 `.o`, `.a` 파일들의 심볼을 순서대로 리졸브 시키고,
못찾은게 뭐가있는지 기억했다가 거기부터 리졸브를 해나감. 끝까지 다했는데
리졸브를 못하면 뭔가 잘못된거.

* Problem
  * Command line order matters!
  * Moral: put libraries at the end of the command line.

    ```bash
    gcc -L. libtest.o -lmine
    gcc -L. -lmine libtest.o # <- Undefined reference to libfun
    ```

> 3월 12일

### Shared Libraries

스태틱 라이브러리의 단점:
1.  바이너리마다 똑같은 라이브러리가 계속 반복됨
1.  메모리상에 똑같은 라이브러리가 반복됨
1.  라이브러리에 사소한거 고칠때마다 프로그램들을 전부 리빌드해야됨

이곳 저곳에서 많이 쓰이는 라이브러리를 모든 바이너리에 집어넣지말고 별도로
놓으면 용량절약이 될수있다!

1.  그 프로그램이 처음 실행될때, 그 프로그램이 요구하는 라이브러리들을 동적으로
    링킹할 수 있다. (Load-time linking)

1.  다이나믹 링킹은 프로그램이 시작 된 이후에도 일어날 수 있다. (Run-time linking)
    * Distributing software
    * High-performance web servers
    * Runtime library interpositioning
    * 코드 핫로딩 (실행중에 코드교체)

1.  다이나믹 라이브러리는 여러 프로그램에 의해 공유될수도 있다.
    * 나중에 버추얼 메모리를 배우면 더 나옴

### Dynamic Linking at Load-time

### Dynamic Linking at Run-time

함수    | 기능
--------|-----
dlopen  | 라이브러리(`.so`)를 로드함
dlsym   | 라이브러리 안에서 심볼을 찾음
dlclose | 로드했던 라이브러리를 닫음

### Case Study: Library Interpositioning

Library Interpositioning

### Some Interpositioning Applications

Security
* Confinement (sandboxing)
  * Interpose calls to libc function
* Behind the scenes encryption
  * Automatically encrypt otherwise unencrypted network connections

Monitoring and Profiling
* Count number of calls to functions

I/O나 디스크 사용통계를 내고싶다 -> 인터포지셔닝

### Example program

```c
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int main() {
    free(malloc(10));
    printf("Hello, world!\n");
    exit(0);
}
```

Compile-time Interpositioning

```c
#define malloc(n) mymalloc(n, __FILE__, __LINE__)
#define free(ptr) myfree(ptr, __FILE__, __LINE__)
```

Link-time Interpositioning

```sh
ld --wrap malloc
```

```sh
gcc -O2 -Wall -W1,--wrap,malloc
```

```c
void* __real_malloc(size_t size);
void* __wrap_malloc(size_t size) {
    void* ptr = __real_malloc(size);
    return ptr;
}

/* ... */
```

Load/Run-time Interpositioning

```
void* malloc(size_t size) {
    static void *(*mallocp)(size_t size);
    /* ... */
    if (!mallocp) {
        mallocp = dlsym(RTLD_NEXT, "malloc");
        /* error handling */
    }
    ptr = mallocp(size);
    printf("malloc(%d) = %p\n", (int)size, ptr);
    return ptr;
}
```

### Interpositioning recap

1.  Compile time
1.  Load time
1.  Run time

--------

Exceptional Control Flow:

Exceptions and Processes
--------

### Control Flow

Processors do only one thing:
켜져서 꺼질때까지, 그냥 명령어들을 읽고 실행하고를 무한히 반복할뿐이다.

이것을 바로 컨트롤 플로우라고 한다.
근데 갑자기 다른일을 해야될떄가 있음

### Altering the Control Flow

Normal Control Flow:
* Jumps and branches
* 함수 호출, 반환

Both react to changes in program state

Insufficient for a useful syhstem: Defiicult to react to changes in system state
- 갑자기 누군가 이 프로그램을 강제로 끌때
- 시간에 맞춰서 프로그램이 꺼질때
- CPU를 서로 다른 프로그램들이 공유할때

이것을 Exceptional Control Flow 라고 함

### Exceptional Control Flow

1.  Low level mechanisms
    * Exceptions
    * hardware / OS soft의 역할이다
1.  High level mechanisms
    * 컨텍스트 스위치
    * ...

프로그래머가 컨트롤할 수 있는게 아님

### Exceptions

**Exception**이란 어떠한 이벤트에 대한 대답으로 OS로 컨트롤 플로우를
넘겨주는것을 뜻함

코어덤프, abort, div by 0, arithmetic overflow, page fault, I/O request
completes, Ctrl-C, ...

### Interrupt Vector

익셉션 테이블이라는걸 만든다.
32/64bit 짜리 함수포인터들이 쭉 들어있음.
익셉션0, 익셉션 255번 이런식으로 익셉션마다 번호를 부여함.

익셉션이 발생하면 정해진 익셉션 번호로 가서 어떠한 행동을 수행하고 정리되던가
끝나던가 함.

### Asynchronous Exceptions (Interrupts)

프로그램하고 상관없이 작동하는 익셉션.

1.  I/O interrupts

    I/O를 요청하면 기다리는게 얼마나 오래 지속될지 알수가없다.

1.  Hard reset interrupt

    전원 뽑기, 리셋버튼 누르기

1.  Soft reset interrupt

    `Ctrl` + `Alt` + `Delete`

### Synchronous Exceptions

1.  Traps
    * 의도적인것
    * 시스템콜, 브레이크포인트, 특수한 여러 명령어들
1.  Faults
    * Unintentional하게 발생한것이지만, recover 가능할수도 있음
    * 페이지 폴트, 세그폴, 부동소수점 익셉션
1.  Aborts
    * Unintentional, UNrecoverable
    * 패리티 에러, 머신체크
    * 그냥 abort 하는수밖에 없음

### Trap Example: Opening File

User calls: `open()`

실행이 OS로 넘어갔다가(익셉션) 다시 돌아옴. OS가 파일 여는 동작들을 해줘야됨

### Fault Example: Page Faults

이상한곳에 메모리를 쓰려고 시도함. 빨리 죽어주는게 차라리 더 나음.

```c
int a[1000];
main() {
    a[5000] = 13;
}
```

--------

> 3월 17일

### Concurrent Processes

여러개의 프로세스가 하나의 코어를 쓰기도하고, 여러 프로세스가 여러 코어를 쓰기도
하고.

두 프로세스가 동시에 실행되면 그걸 두 프로세스가 Concurrent하게 실행된다고 한다.
그렇지 않은것은 Sequential한것

근데 이건 CPU 입장에서 본거고, 사용자 입장에서 보면 프로세서가 멈췄다가
실행되는건지, 둘이 같이 실행되는건지 구분이 안된다.

컨텍스트 스위치가 요즘은 2기가헤르츠 프로세서에선 5마이크로 ~ 7마이크로정도 정도
걸린다. 커널 코드가 컨텍스트 스위치를 해줌. 프로세스가 갖고있던 여러
스테이트들을 전부 세이브하고, 저장되어있던 프로세스의 스테이트를 다시 읽어오는게
컨텍스트 스위치

Page Table. Virtual Memory에서 Physical Memory로 매핑해주는게 페이지 테이블인데,
보통 이걸 캐쉬에 저장함. 프로세스마다 다 다른 페이지 테이블을 갖고있다. 캐쉬가
넉넉하지 못하니 컨텍스트스위치 되어서 내려간 프로세스의 페이지 테이블은
내려버린다던가 할수있다.

### fork: Creating New Processes

```c
int fork(void);
```

fork는 호출은 한번되지만 리턴은 두번되는 아주 흥미로운 함수. 프로세스를 복사하는
함수. 자식일경우 0, 부모일경우 PID가 리턴됨.

```c
#include <stdio.h>
#include <unistd.h>

int main() {
    puts("ㅇㅅㅇ");
    fork();
    puts("ㅇㅅㅇ..");
    fork();
    puts("ㅇㅅㅇ....");
    fork();
    puts("ㅇㅅㅇ......");
    return 0;
}
```

위 예제를 실행했을때 나오는 경우의 수가 얼마일까? 이게 사실 이건 별문제는 아닌데
컨커런트 프로그램을 만들다보면 실행 타이밍에 따라 문제가 생기기도하고
안생기기도하고 이런 문제가 생김. 이런걸 편하게 디버깅할 수 있을까? 이거 좋은
문제임.

### exit: Ending a process

```c
void exit(int status)
int atexit(void (*func)(void));
```



### Zombies

죽고나서도 리소스를 잡아먹는 프로세스

Reaping
- 부모가 자식이 죽으면 깨끗하게 나머지를 정리함
- Parent에게 자식 프로세스의 exit status가 들어감
- 커널은 프로세스의 흔적을 지움

What if parent doesn't reap
- 부모가 자식보다 먼저죽으면, 리핑을 init이라는 process가 대신 해줌
- shells, server, 데몬처럼 한번 만들면 죽지않고 계속 사는 프로세스에만 이런일이
    일어남

왜 이렇게 만들었을까? 왜 프로세스가 스스로 자기 흔적을 지우게 하지 않았을까?
부모 프로세스에 return value같은걸 넘기고싶을 수 있으니까.

defunct. exit을 했는데 부모가 아직 reap 하지 않은 프로세스. 이 상태가 지속되면 좀비.

### wait: Synch with children

```c
int wait(int *child_status);
```

자식 프로세스가 끝날때까지 기다리고, child_status에 자식 프로세스가 반환한
리턴값이 들어감.

만약 여러 childern이 완료되었으면, will take in arbitrary order

### execve: Loading and Running Programs

> Execve() transforms the calling process into a new process.

```c
int execve(char *filename, char *argv[], char *envp[]);
```

Loads and runs in current process

Does not return unless error

쉘이 이렇게 만들어짐. 라인 하나 읽으면 포크하고, 자식에서 execve

### Summary

```
fork
exit
wait / waitpid
execve
```

Signal
--------

### The world of Multitasking

하나의 프로세스가 돌다가 다른프로세스가 돌고 이러면 컨텍스트 스위칭이 일어난다.
메모리는 메모리에 있으니까 냅두고, 레지스터 값을 통째로 저장하고 그런다. 근데
실제로 OS가 하는 일은 마치 여러개의 프로세스가 같이 동시에 돌아가는것처럼 보이게
해주는거. 실제로는 정해진 시간엔 하나밖에 안돌아가지만 이걸 추상화해서 여러개의
프로세스가 동시에 돌아가는거처럼 보이게 해주는거.

프로그래머가 여러개가 돌아가는걸 알때가 언제냐. fork를 해보면 알지. 중간에
exit을 한다, wiat을 할수도있고, 등등.

가장 쉽게 컴퓨터를 죽이는 방법?

```c
while(1) { fork(); }
```

이런거 잘못쓰면 굉장히 위험할 수 있다.

### Unix Process Hierarchy

[0]
- init [1]
  - D

(피피티 참고)

### Shell

```
sh
csh, tcsh
bash
zsh
```

한라인씩 읽어서 그 라인을 읽고 커맨드를 실행하고 끝나는게 쉘이다.

백그라운드 모드, 포그라운드모드가 따로있음

일반적으로는 한번에 하나의 일만 하지만 경우에 따라서 한 명령어가 굉장히 오래
돌아갈 수 있음. 이런건 뒤에 `&`를 붙이면 프로세스가 백그라운드로 돌아감

```sh
(sleep 7200; rm /tmp/junk) &
```

Background job의 문제는?

1.  백그라운드 잡이 끝나면 좀비가 될거임
1.  절대 reap되지 않음
1.  이런일이 반복되면 메모리릭임

```
limit maxproc # csh
ulimit -u     # bash
```

### ECF to the Rescue!

### Signals

A *signal* is a message that notifies a process that an event of some type has
occurred in the system

* 커널이 프로세스에게 보내는것
* Akin to exceptions and interrupts
* 시그널 ID는 1-30 정도의 작은 숫자임
* 시그널이 왔을때 알수있는것은 시그널 ID와 시그널이 있었다는 사실일뿐

이걸 쓰면 쉘이 백그라운드 잡에 대해서도 리핑을 할 수 있음


ID | Name    | corresponding event
---|---------|---------------------
2  | SIGINT  |
9  | SIGKILL |
11 | SIGSEGV |
14 | SIGALRM |
17 | SIGCHLD |

커널이 목표 프로세스의 어떤 값들을 바꿔서 보냄.

보통 시스템콜 `kill` 로 보내짐

### 시그널 받는법

시그널에 대해 할수있는 대응

1.  무시하기
1.  꺼지기
1.  시그널을 Catch하고, 적절한 핸들링을 함. Signal Handler 가 호출됨

--------

> 3월 19일 목요일

### Pending and BLocked Signals
Pending signal: 보내졌는데 아직 받아지지 못한 시그널

시그널은 큐가 있는게 아니라 시그널이 도착했다, 도착하지 않았다 만 있는 비트만
있는것이기 때문에 시그널은 여러개를 보낼 수 없음.

프로세스는 마음대로 시그널을 블락할 수 있음. 언블락할때까지는 그 시그날을 받지
않음. 인터럽트 마스크랑 똑같음.

### Signal Concepts
시그널마다 비트가 있어서, 비트가 셋이 되면 블락된거임.

Pending bit: 시그널 갯수(0~30)만큼 있고, 시그널이 오면 해당 비트가 셋됨

Blocked bit: `sigprocmask`, 특정 비트를 셋 하면 그 비트에 해당하는 시그널이
block됨

### Process Groups
각각의 프로세스들엔 `pid`가 있는데, 프로세스들을 묶어서 `pgid`라는것도 또 부여됨

보통 한 프로세스는 자기 자신을 프로세스 그룹으로 갖는데

Foreground-job 을 만들고 걔네가 차일드 프로세스를 만들면 걔네들은 같은 그룹이
되는거임

* `getpgrp()`
* `setpgid()`

### Sending signals with `/bin/kill`
`kill`로 `24817`에 `SIGKILL` 보내기
```sh
kill -9 -24817
```

### Sending signals from the keyboard
키   | 이름    | 설명
-----|---------|-------------------------
`^Z` | SIGTSTP | Stop precess, resumable
`^C` | SIGINT  | Terminate process

```
First letter of STAT
S: sleeping
T: stopped
R: running

Second letter of STAT
s: session leader
+: foreground proc group
```

sleep과 stop의 차이점? sleep은 자발적으로 한거고, stop은 외부의 요인때문에
생긴것

### Sending signals with `kill()`
```
kill(pid, SIGKILL);
```

### Receiving signals
Kernel computes `pnb = pending & ~blocked`

시그널은 인터럽트처럼 실행을 가로막고 검사할정도로 그렇게 강력하진 않음.
어딘가로 컨트롤이 넘어갔다가 다시 들어올때 시그널을 검사함. (ex: 인터럽트, 트랩,
컨텍스트 스위치, ...)

`^C` 를 누른다고 바로 프로세스가 멈추지 않는 이유.

* `if (pnb == 0)`
  * 프로세스에게 실행을 넘겨줌
* `else`
  * Choose least nonzero bit k in `pnb` and force process `p` to receive signal `k`
  * ..

### Default Actions
각 시그널들은 아래중 하나의 디폴트 액션을 가짐

* 프로세스가 종료됨
* 프로세스가 종료되고 코어덤프
* 프로세스가 `SIGCONT` 시그널이 들어올때까지 멈춤
* 프로세스가 시그널을 무시함

### Installing signal handlers
프로세스별로 각자 새로운 시그널 핸들러를 등록할 수 있음.

```c
handler_t *signal(int signum, handler_t *handler);
```

Different values for handler:

* `SIG_IGN`: `signum`을 무시해라
* `SIG_DFL`: `signum`에 대한 시그널 핸들러를 디폴트 액션으로 돌려버려라
* Otherwise: `handler`는 시그널 핸들러의 주소
  * 이를 Installing signal handler 라고 함

```c
void int_handler(int sig) {
    safe_printf("Process %d received signal %d\n", getpid(), sig);
    // 시그널 핸들러 안에서 사용하는 printf 펑션
    // async-signal-safe wrapper for printf
    //
    // write(1, buf, strlen(buf)); /* write is async-signal-safe */

    exit(0);

}

signal(SIGINT, int_handler);
```

시그널은 보내는순서대로 받지 않음.

우리는 어느 프로세스가 어떻게 컨텍스트 스위치 될지 모른다.

### Signals handlers as Concurrent Flows
A signal handler is a separate logical flow (not process) that runs concurrently
with the main program

마치 멀티스레딩처럼 작동함.

### Another View of Signal Handlers as Concurrent Flows
프로세스는 시그날이 발생해도 모름. 컨텍스트 스위치나 시스템콜을 해서 커널코드로
컨트롤플로우가 넘어갔다가 다시 돌아와야만 시그널을 처리함

디폴트 시그널 핸들러는 커널코드 안에 들어있음

### Signal Handler Funkiness
* Pending signals are not queued
  * 어느게 먼저왔는지도 모르고 그저 이게 왔었다는 사실만 알수있을뿐
  * 여러 프로세스가 비슷한 시간에 같은 종류의 시그널을 동시에 보내오면,
    시그널들이 서로 씹힐수도 있음

### Living with Nonqueuing Signals
시그널 핸들러가 한번 불려도, 핸들러 하나 안에서 여러 시그널을 처리할 수 있는
구조를 만듬

```c
waitpid(-1, &child_status, WNOHANG);
```

시그널 핸들러가 실행중인동안 새 시그널이 들어오면? 교수님께서는 이미 실행중인
시그널 핸들러가 종료된 다음 실행된다고 하심.

시그널 핸들러가 호출된순간 이미 pending bit는 사라진상태.


### More signal handler funkiness
`read()`와 같이 오래걸리는 시스템콜을 하는도중 시그널이 오면?

시그널 핸들러는 `read()` 호출을 인터럽트한다.

* Linux: 시그널 핸들러가 끝나면, `read()` 콜을 자동으로 재개함
* 다른 일부 Unix 환경에선 `read()` 호출이 `EINTER`를 반환하고 실패하고,
  `errno`가 세팅된다. 이경우 어플리케이션이 재개해야함.

시그널을 쓰면서 포터블한 프로그램 만드는건 굉장히 골치아픔

`SIGKILL`이 오버라이드 불가능한이유? 프로그램을 무조건 끌 수 있게 하기위해.
`SIGINT` 오버라이드한다음에 `exit()` 호출을 안해봐라.

### A Program That Reacts to Internally Generated Events
프로그램 내부에서 만든 시그널을 스스로 처리함.

### Async-Signal-Safety
`async-signal-safe` 한 프로그램은 아래 조건중 하나를 만족해야함.

* reentrant (all variables stored on stack frame, 전역변수를 쓰면 안됨;
    stateless 해야함. 프로그램을 여러번 실행해도 결과가 같아야함)
* Non-interruptible by signals

> Reentrant == Stateless && No side effect

POSIX 표준은 117개 함수들에 대한 `async-signal-safe`를 보장함

```c
void safe_printf(const char *format, ...) {
    char buf[MAXS];
    va_list args;

    va_start(args, format);                     /* reentrant */
    vsnprintf(buf, sizeof(buf), format, args);  /* reentrant */
    va_end(args);                               /* reentrant */
    write(1, buf, strlen(buf));                 /* async-signal-safe */
}
```

### Signal example
```c
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

void s(int d) {
  printf("begin (%d)\n", d);
  sleep(5);
  printf("end   (%d)\n", d);
}

int main() {
  int pid = getpid();
  signal(SIGINT, s);
  signal(SIGCHLD, s);
  if (fork() == 0) {
    kill(pid, SIGINT);
    sleep(1);
    kill(pid, SIGINT);
    sleep(1);
    exit(0);
  }
  for(;;);
}
```

결과:
```
begin (2)
begin (20)
end   (20)
end   (2)
begin (2)
end   (2)
```

결론:

* 컨텍스트 스위치는 충분히 자주 일어남
* 한 시그널에 대해선, 시그널 핸들러가 동시에 1개 이상 실행되지 않음
* 다른 시그널의 경우 시그널 핸들러가 실행되는 도중 다른 시그널 핸들러가 시작될
  수 있음
* 그러나 여러 시그널 핸들러가 동시에 실행될수는 없음

### Nonlocal Jumps: `setjmp`/`longjmp`
* Powerful but dangerous
* User-level mechanism for transferring control to an arbitrary location
  * Controlled to way to break the procedure call / return discipline
  * Userful for error recovery and signal handling

이건 점프를 하고 나서 원점으로 돌아오지 않는것이 특징.

`longjmp`를 하기위해선 항상 `setjmp`를 먼저 해서, 어디로 갈지 정해야함.

```c
int setjmp(jmp_buf j);
```

* Must be called before `longjmp`
* Identifies a return site for a subsequent `longjmp`
* Called once, return one or more times
* `setjmp()` 를 실행하면 무의미한 값이 리턴되고 그냥 다음 인스트럭션이 호출되고,
  차후에 `longjmp`가 호출되면 실행이 여기로 돌아오면서 유의미한 값이 반환됨.

```c
void longjmp(jmp_buf j, int i);
```

* 아까 `setjmp` 했던 위치로 돌아가는것.
* `i` 에 준 값이 `setjmp`에서 반환됨. 반환될때의 정보는 모두 `j`에 들어있음.

### `setjmp`/`longjmp` example

> 피피티

### Limitations of Nonlocal Jumps
Works within stack discipline

* longjmp 하기전에 있던 스택이 점프하고나서 사라지면?
* 자식함수에서 `setjmp`를 하고, 부모함수에서 `longjmp`를 하면? 무슨일이 일어날지
  알수없다.

### Summary

* 시그널은 오버헤드가 아주 크다.
  * >10,000 clock cycles
  * 예외적인 상황에서만 쓸것

--------

보강할때엔 출석 안부름

Idempotent operation

> 시프 예제 다 쳐보기

--------

> 3월 24일

System I/O
--------

### Unix Files

In Unix

* **file** 은 m 바이트의 시퀀스.
* 모든 I/O 장치는, 파일로 표현된다.
  * `/dev/sda2`, `/usr` disk partition
  * `/dev/tty2`, 터미널
* 커널도 파일로 표현된다
  * `/dev/kmem`, 커널 메모리 이미지
  * `/proc`, 커널 데이터 구조

### Unix File Types
* Regular file
* Directory file
* Character special and block special files
  * 터미널 (캐릭터 스페셜), 디스크 (블럭 스페셜)
  * RW의 단위가 한 캐릭터씩/한 블럭씩 이러한 차이가 있다.
  * 캐릭터 스페셜은 읽고 쓰는 위치가 없다. 항상 그 위치에서 새 캐릭터가 들어오고
    나갈뿐, 블럭 스페셜은 몇번째 블락을 읽고, 어느 위치에 써라 이런게 있음.
* FIFO (named pipe)
  * IPC을 위해 쓰임
* Socket
  * Network communication을 위해 쓰임

### Unix I/O

* `open()` and `close()`
* `read()` and `write()`

Open을 하면 current file position이라는게 생기고, `seek()`으로 그 위치를 바꿀 수
있음.

### Opening Files
파일을 열면 File descripter가 나옴. 에러일경우 `-1`. 프로세스가 시작할경우 0, 1,
2 파일 디스크립터는 이미 정의가 되어있고, 파일을 그 이후로 셀때마다 3 이후로
파일 디스크립터가 늘어남.

* 0: stdin, STDIN_FILENO
* 1: stdout
* 2: stderr

그리고 커널 안에 파일 디스크립터 테이블이 있어서, 어느 엔트리가 어느 파일을
가리키는지가 저장됨.

파일 디스크립터 테이블은 프로세스마다 하나씩 할당됨.

### Closing Files
역할이 끝난 파일 닫기.

이미 Close된 파일을 또 닫으면 문제의 시작.

Moral: Always check return codes, even for seemingly benign functions such as
`close()`

### R/W Files

N바이트 읽으라고 요구해도, 요구한것보다 작게 읽는 수가 있음. N바이트 쓰라고해도,
요구한것보다 작게 쓰는수가 있음. 이를 Short-count 라고 함

임피던스 미스매치

### Short Counts
쇼트카운터가 생기는 경우

* 읽다가 EOF 만났을때
* 터미널에서 텍스트 라인을 읽고있는경우
* 유닉스 파이프나 네트워크 소켓을 읽고 쓰는경우

쇼트카운트가 절대 생기지 않는경우

* 디스크 파일에서 읽는경우 (EOF가 아닌이상)
* 디스크 파일을 쓰는경우

쇼트카운트를 처리하는 방법

* RIO(Robust I/O) 패키지를 쓰삼
* 기운찬 입출력

디스크에 파일을 쓰는경우, `write()` 함수가 리턴된다고 해서 그게 지금 디스크에
들어있다는 뜻은 아님. (커널 버퍼에 들어있다던가, 등..) 확실하게 할 수 있는
경우는 `flush()`를 써서 버퍼를 전부 비우고 디스크에 써지기를 기다리는수밖에
없음. 근데 그렇다고 해서 그게 디스크에 있는거지, 하드디스크 전의 디스크 버퍼에
있는건지 알수없음.

레귤러 파일은 읽고 쓸때 short count가 일어나지 않음.

### Robust I/O
http://csapp.cs.cmu.edu/public/code.html

쇼트카운터가 안나게 만들어놓은 패키지임.

* `rio_readn`, `rio_writen`
  * Unbuffered RIO

##### Buffered I/O: Motivation
실제 `read()`, `write()` 호출 횟수를 줄이자. 커널 다녀오면 10000 사이클 이상이
소모됨.

* `rio_readlineb`, 텍스트 라인 한줄이 끝날때까지 읽음.
* `rio_readnb`, N 바이트 읽기

### File Metadata
Metadata는 데이터에 대한 데이터라는뜻이다. 이경우 파일에 대한 데이터를 의미함.
파일들의 메타데이터는 커널에 의해 관리됨. `stat`, `fstat`으로 볼 수 있음

* device
* inode
* 액세스 시간
* 블락 크기
* 할당된 블락 갯수
* UID, GUID
* 하드링크 갯수
* ...

modification time이랑 change time의 차이? 오너가 바뀌거나 퍼미션이 바뀌거나는
change이고, 그게 아닌것은 modification

### Accessing Directories
* `opendir()`, 디렉토리의 내용을 여는 권장되는 방법.
* `readdir()` 함수를 사용해 디렉토리 안에있는 파일들의 내용을 디렉토리 엔트리
  구조체에 저장해서 볼 수 있음.

### Unix Kernel이 Open File을 나타내는 방법
* 프로세스마다 파일 디스크립터 테이블이 있음
* 커널 스페이스에 'Open File table'이라는게 있음. 파일 디스크립터들은 오픈파일
  테이블들을 가리킴. 오픈파일 테이블에 파일 위치와 레퍼런스 카운터가 있음.
* v-node table

### File Sharing
같은 파일을 `open()` 두번함: openfile table에 파일이 두개가 생기고, 둘이 v-node
table의 같은 파일을 가리킴.

### Share files: `fork()`
(PPT 참고)

Open file table, v-node table은 클론되지 않고, Descriptor table만 클론됨. 각
파일 디스크립터들이 한 Open file table을 가르키게되고, open file table의
레퍼런스 카운터가 1이 늘어남.

포크 외에 같은 Open file table을 가리키는 파일 디스크립터가 두개 생기는경우가
있을까? 있다.

### I/O Redirection
쉘이 아래 문장을 어떻게 구현할까?

```sh
ls > foo.txt
```

`dup2(oldfd, newfd)`

하나의 프로세스 안에서 일어나는 일임. oldfd가 가리키는 파일을 닫아버리고
(`close()`, 레퍼런스 카운터도 줄음) newfd의 값으로 oldfd를 오버라이트 해버림.

--------

> 3월 27일 금요일 (보강)

캐쉬

### End-to-end Core i7 Address Translation

### Core i7 Level 1-3 Page Table Entries

### Core i7 Page Table Translation
Virtual address -> Physical address

### Cute Trick for Speeding Up L1 Access
* Virtually indexed, physically tagged

### Virtual Memory of a Linux Process

### Linux organizes VM as Collection of Areas
* `task_struct`가 `mm_struct`를 가짐
* `mm_struct`가 `vm_area_struct`의 첫 노드를 가짐
* `vm_area_struct`가 링크드리스트로 만들어져있음

### Linux Page Fault Handling
`vm_area_struct`에 `vm_end`, `vm_start`가 적여있어서 어디부터 어디까지 읽어도
되는지가 저장되어있음. 이걸로 이상한데 읽으면 페이지폴트

`vm_area_struct`에 읽기전용인지 여부도 써있어서 쓰려고 시도하면 또 페이지폴트.

### Memory Mapping
Disk object로 만들어진 VM area. mmap은 아래와같은 두 종류가 있는데

* Regular file

  디스크에 있는 파일로 만들어진 메모리맵

* Anonymous file

  처음에 메모리맵을 하면 0으로 채워진 페이지가 나옴 (demand-zero page). 여기에
  뭔가를 쓰면 (dirtied), 다른 페이지처럼 작동함

Dirty page들은 스왑파일을 통해 메모리로 복사된다

### Demand paging
*   Key point: No virtual pages are copied into physical memory until they arer
    referenced

    이를 Demand paging이라고 한다. 메모리맵을 하고 R/W를 안하면, 메모리가
    사용되지 않는것

### Sharing Revisited: Shared Objects
프로세스 1, 2의 버추얼 메모리가 있고 셰어드 오브젝트가 한 있을때

1.  Process 1이 메모리에 shared object를 mmap함.

    물리 메모리에 올라가고, VM에도 매핑됨

2.  Process 2가 같은 shared object를 mmap 함.

    물리 메모리에 이미 있는 shared object가 다른 프로세스의 VM에 매핑됨.

### Sharing Revisited: Private Copy-on-write Objects
두 프로세스가 한 CoW 오브젝트를 공유하는상황

1.  양쪽에서 아직 읽기밖에 하지 않은 상황에선 앞의 경우와 같이 그냥 같은 물리
    메모리를 매핑 해서 씀

2.  Write가 발생하면, 그순간 그 페이지를 다른곳으로 복사해서 그부분만 따로
    매핑함. 전체 오브젝트를 다 복사하는게 아니라 변경이 일어난 페이지만
    복사하는것이 뽀인트

최대한 늦게 카피하기

### `fork()` Revisited
프로세스의 포크가 일어날때, 처음 시작하자마자 모든 메모리를 다 복사하지 않는다.

포크할때도 똑같이, 물리 메모리들은 냅두고 페이지테이블들만 다 복사하고,
read-only로 마크를 함. 그리고 `vm_area_struct`들을 양쪽 프로세스에 모두 private
COW로 지정한다.

### `execve()` Revisited
원래 갖고있던 `vm_area_struct`를 전부 버리고, 새 `vm_area_struct`를 가져오고
PC를 옮김

### User-Level Memory Mapping
```c
void *mmap(void *start, int len, int prot, int flags, int fd, int offset);
```

* start: may be 0 for 'pick an address'
* prot: 프로텍션 (read only, write only, ...)

파일디스크립터의 특정부분을 메모리에 입혀버리기

### Using `mmap` to Copy files
이런거 웹서버들이 많이함. 웹서버가 하는일의 가장 기본적인 일이 바로 Static File
Serving임. 디스크에 있는 파일을 일단 커널버퍼로 읽어들이고, 이걸 유저스페이스
버퍼로 옮기고, 이걸 다시 커널버퍼로 옮기고, 이를 그 다음에 네트웍으로
보내는건데, 이건 불필요하게 카피가 두번되는거임. 그래서 좀 똑똑한 웹서버들은
디스크에서 커널버퍼로 읽으면, 이를 바로 네트웍 카드로 보냄. 좀 더 잘하면
디스크에서 바로 네트웍 카드로 보냄 (Zero copy).

웹서버 만들때 보통 이런거 하는게 큰 이슈가 됨. mmap을 쓰면 바로 이걸 할 수 있음.
```c
void *bufp = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd_in, 0);
write(fd_out, bufp, size);
// mmap 하자마자 바로 바로 write 시스템콜을 함, 카피가 없음
```

--------

> 4월 2일 목요일

### Garbage Collection
메모리 매니저가 어떻게 어느 메모리가 free 될 수 있는지 어떻게 아나?

GC를 할때, 까는 가정

* 어떤 값을 하나 주면, 시스템에서 그 값이 포인터인지 아닌지 알 수 있다고 가정
* 모든 포인터는 메모리블럭의 시작점을 가리킨다
* 포인터를 감출 수 없다

### Classical GC Algorithms
연도 | 설명
-----|-----
1960 | Mark and sweep
1960 | Reference counting
198x | Generational collection

### Memory as a Graph
메모리를 유향그래프로 그린다고 쳐보자

- 각 블럭은 노드
- 각 에지는 포인터

### Mark and Sweep
루트노드부터 시작해서 재귀적으로 전부 마크한뒤 (graph traversal), 노드를 전부
돌면서 마크가 안된애를 지움

```
ptr mark(ptr p) {
    if (!is_ptr(p)) return;
    if (markBitSet(p)) return;
    setMartBit(p);
    for (i = 0; i < length(p); ++i) {
        mark(p[i]);
    }
}
```

### Conservative Mark & Sweep in C
C 포이너들은 블럭의 중간을 가리키고있을수도 있음

블럭의 헤더를 어떻게 찾느냐? 블럭들을 바이너리 밸런스드 트리로 보관하기

### Memory-related perils and pitfalls
- (PPT 보면 많음)

### C Pointer declarations
```c
int *p;               // 정수에 대한 포인터
int *p[10];           // 배열에 대한 포인터
int *(p[10]);         // 배열에 대한 포인터
int **p;              // 2차 포인터
int (*p)[10];         // 포인터들의 배열
int *f();             // 리턴값이 포인터인 함수
int (*f)();           // 함수포인터
```

```c
int (*(*f90)[10])();
```
f is a function returning ptr to an array[13] of
pointers to functions returning int

```c
int (*(*x[3])())[5];
```

### Deref Bad pointer
```
int val;
scanf("%d", val);
```

이거 한번도 안해본사람은 뭔가 잘못된사람이야

### Read uninitialized memory
### Overwriting memory

```c
char s[8];
gets(s); // read more than 8
```

- 포인터 연산 실수
- 실수로 포인터 deref를 안함

### Referencing Nonexistent Variables
### Referencing Freed Blocks
### Memory Leak

### Dealing With Memory Bugs
* gdb
* malloc만 디버깅 하는 툴도 많음
* 바이너리 트랜슬레이터: valgrind (리눅스), Purify

--------

Internetworking
--------
### A Client-Server Transaction

### Hardware organization of a network host

### Computer Networks
* SAN (System Area Netwrok)
  * Cluster, Machine room, ...
* LAN
  * Building ore campus. "Ethernet"
* WAN
  * Country or world.

"Global IP Internet" is most famous example of an internet.

### Lowest Level: Ethernet segment
* Hub, broadcast network
  * 들어오는 요청을 전부 echo함. 패킷이 동시에 하나밖에 못지나감.
* Collision
  * 부딪치면, 서로 랜덤한 시간 이후로 리트라이
* Ethernet header
  * 보내는 사람의 주소, 받는 사람의 주소가 있음. 48-bit unique address, MAC
    address임. MAC address를 관리하는 국제 기관이 있음.
* Switch
  * 들어오는 요청 맥어드레스를 보고, 패킷을 어느 허브로 보낼지를 정해줌. 동시에
    여러 커넥션이 있을 수 있음.

### Next Level: Bridged ethernet segment
* Spans building or campus
* 선택적으로 프레임을 복사한다.

### Next Level: Internet
* Router
  * 라우터에서는 맥어드레스가 소용이 없음. IP 어드레스가 필요해짐.

### Logical Structure of an internet
* Ad hoc interconnection of networks

### The Notion of an internet Protocol
어떻게 IP만 가지고 패킷이 길을 찾아갈까?

* Host addresses
* Standard transfer unit: packet
  * Header + Payload

큰 패킷도 작은 패킷 여러개로 잘라서 보낼 수 있음. 나중에 합치면 되니까.

### Transferring Data over an internet
1. Data
1. (Data + internet packet header) + LAN1 frame header1
1. `Router`
1. (Data + internet packet header) + LAN2 frame header1
1. Data

### Other Issues
* (큰) 라우터 만들때 IP주소 어떻게 저장하는지
  * Content Addressable Memory
* 라우터가 프레임을 어디로 포워딩할지 어떻게 아는가?
* 네트워크 토폴로지가 변하면 어떻게하는가?

### Global IP Internet

### Hardware and Software Organization(Abstraction) of an Internet Application
(피피티에 그림있음)

Application Level에선 system call로 추상화됨

### Basic Internet Components
* Internet backbone
* Network Access Point (NAP)
* Regional networks
* Point of presence (POP)
* Internet Service Providers

### NAP based internet architecture

### Internet Connection Hierarchy
(피피티)

### Naming and Communicating on the Internet
* 원래는
  * 인터넷을 이렇게 많이쓸지 몰랐음. 모든 노드에 글로벌 IP를 하나씩 주려고했음.
    * 2^32 개를 다 쓰지도 못하고, 점점 모자라감
  * 보안성 아예 없음.

> 4월 9일

### Evolution of Internet: Naming
* Dynamic address assignment
  * 내가 어떤 IP를 받는다고, 그걸 하루종일 쓰는게 아님. 인터넷 끊는동안 IP를
    반환하기.
  * 클라이언트의 경우엔 고정된 IP를 쓸 필요가 없음.

Network address translation: 이 어드레스를 예약해놓고, 이 어드레스는 서버로 쓸
수 없다.

### Evolution of Internet: Firewall
* 들어오면 안되는건 막아버리기, 나가면 안되는걸 막아버리기
* 패킷 감청 외에도, 불필요한 정보가 밖으로 나가는걸 막음
  * LAN에 있는 노드 갯수 숨기기, 등..

Firewall이랑 Network address translation은 같은 레이어에서 일어남

Port address translation: 같은 IP 포트 여럿이 서로 비켜서 나눠쓰기

### Virtual Private Networks
VPN 쓸때, Firewall 반대편 유저가 나인지 아닌지 알아야됨. 인증과정을 거치기

내가 아이피가 XXXX인데, VPN으로 마치 YYYY 인것처럼 행세한다던가.

### DNS

### IP Address
port address: 16byte unsigned short

Host/Network Byte Order. htonl, htons, ntohl, ntohs

인텔은 리틀엔디언, 네트웍은 빅엔디언.

### Dotted Decimal Notation

### IP Address Structure
* Class A: 64 개
* Class B
* Class C: 16,000,000개
* Class D: 멀티캐스트
* Class E: Reserved for 실험

(그림 참고)

종종 Class A와 B 사이로 쪼개서 쓰기도 함

Unrouted (private) IP

* 10.0.0.0/8
* 172.16.0.0/12
* 192.168.0.0/16

### Internet domain names
트리구조

### DNS
* 도메인네임 하나에 여러 아이피가 있을 수 있다.
* 모든 호스트에는 루프백 어드레스가 있다 (127.0.0.1)
* 여러 도메인이 같은 아이피일 수 있다.

도메인 네임만 보고 이게 valid 한지 아닌지 알 수 없다.

`gethostbyaddr`, `gethostbyname`

### Domain Information Groper (dig)
DNS에 커맨드라인으로 쿼리하는거임

### Internet connections
Point-to-point

* port
  * Ephemeral port: 클라에서 자동으로 할당되는 포트번호
  * Well-known port: 잘 알려진 포트번호

Well-known 포트로 연결이 들어오면, 그 연결을 다른 포트로 옮겨버리고 원래 포트를
빨리 비워주는 경우도 있음

> 시험범위: 링커~인터넷

--------

> 4월 16일

### Sockets Interface

Web Services
--------
하이퍼텍스트

Memex라는 개념이 제시됨. 이책 저책 이리저리 알아보는 과정을 편하게 하자.

### Web History

### Web Content
* Multipurpose Internet Mail Extensions, MIME
  * `text/html`
  * `application/postscript`
  * `image/jpeg`
  * ...

메일에 아스키코드밖에 못쓰니까, 익스텐션을 만든거임.

### Static content vs Dynamic content

### URLs

### How clients and servers user URLs
```
http://www.cmu.edu:80/index.html
```

* Clients use `http://www.cmu.edu:80` to infer
  * Protocol
  * Server location (`www.cmu.edu`)
  * Port number (`80`)
* Servers use `/index.html` to
  * Determine which to serve

### HTTP
요청 한번 할때마다 TCP를 맺음

### HTTP Requests
```
<method> <uri> <version>
GET /index.html HTTP/1.1
```

### HTTP/1.1
* `Connection: Keep-Alive`
* `Host: www.cmu.edu`
* `Transfer-Encoding: chunked`
* ~

> 4월 21일

### Serving Dynamic Content With GET
포크, execve

environment variable에 파라미터가 저장됨. `getenv`로 받아옴

### Additional CGI Environment Variables
```
SERVER_SOFTWARE
SERVER_NAME
GATEWAY_INTERFACE
...
```

## Even More CGI Environment Variables
```
HTTP_ACCEPT
...
```

### Serving Dynamic Content With GET
sprintf, printf로 길이재고 이리저리 해서 막 함

### Data Transfer Mechanisms
* Standard
  * Specify total length with content-length
  * Requires that program buffer entire message
* Chunked
  * Break into blocks
  * Prefix each block with number of bytes (Hexademical)
  * 맨 마지막 chunck는 0 크기로 표시됨

### Proxies
프락치

인터넷 안좋던시절 HTTP에서 쓰던거.

캐슁, 로깅, IP 우회, DDoS, 트랜스코딩, ...

--------

Concurrent Programming
--------
PC 성능이 발전하면서 클락스피드가 공짜로 늘어나니까 프로그램을 복잡하고 무겁게
만들어갔음

근데 이제 단일코어 성능향상이 끝나고 멀티코어로만 발전하고있음. 그래서 이제
컨커런트한 프로그래밍을 해야된다

### Concurrent Programming is Hard
* 사람은 보통 시퀀셜로 생각함
* 시간 전후관계 따지는게 굉장히 헷갈림
* 레이스 컨디션

컨커런트 프로그래밍은 딱딱하다

* Races
* Deadlock
* Livelock: 둘이 계속 열심히 뭔가 하는데 쓰잘데기 없는짓만 하고있음
* Starvation / Fairness: 기회가 특정 한놈한테만 돌아가서 나머지놈이 굶주림,
    Fair하지 못함

스케줄링 문제떄문에 컨커런트 프로그램은 비결정적일떄가 많음.

### Iterative Server
어셉트하는 스레드에서 일을 다 처리하면, 다른 클라이언트가 못들어옴.

컨커런트 써버를 써야됨 -> 어셉트하는 스레드에서 일을 처리하지말고, 어셉트하는
스레드에선 어셉트 하자마자 일을 다른 스레드한테 넘김

### Making Concurrent Flows
1. Processes
1. Threads
1. I/O multiplexing with `select()`: Logical flow를 수동으로 interleave 할 수
있다. 코어가 많을떄엔 별로 좋은 생각이 아니다. 코어가 하나일때엔 제일 효율적임.

### Process based concurrent server
Reap all zombie children

fork를 하고 부모프로세스는 connfd 한걸 반드시 닫는다

### View from Server's TCP Manager
Port Demultiplexing

서버는 내부적으로 이게 어느 아이피/포트 쌍에서 온건지를 다 갖고있음

### 프로세스 기반 디자인의 장단점
장점

* 여러 커넥션을 컨커런트하게 관리함
* 셰어링 모델이 깔끔함
  * 디스크립터 (노)
  * 파일 테이블 (예스)
  * 전역변수 (노)
* 간단하고 직관적임

단점

* 프로세스 컨트롤에 오버헤드가 들어감
* 프로세스간 통신이 어려움

커넥션 들어올때 포크가 일어나면 그게 느림. 프리 포킹을 함 (루비의 unicorn이
이거) connfd가 들어오면 바로 서비스하고 놀고 이럼

### 멀티플 스레드

멀티플 프로세스랑 굉장히 비슷한데, 프로세스 대신에 스레드 쓰는거.

메모리가 공유되어있음.

일반적인 프로그램의 모습: 프로그램 컨텍스트 + 커널 컨텍스트

프로세스 = 스레드 + 코드, 데이터, 커널 컨텍스트

--------

> 5월 12일

Synchronization: Advanced
--------
### Producer-consumer problem
```
( Producer thread ) ==> / Shared buffer / ==> ( Consumer thread )
                 enqueue                dequeue
```

enqueue, dequeue를 각자 한 프로세스들이 하면 락 없이 할 수 있다.

락은 필요없는데 메모리펜스는 필요함.

메모리 펜스 없이하면, 인큐하자마자 디큐했을때 쓰이지 않은 빈 값을 읽으려고
시도할 수 있음.

### Readers-Writers Problem
일반화된 상호배제 문제

자주 일어남

#### First readers-writes problem (favors readers)
리드가 안끝났는데 리드가 또 들어오면 그냥 리드를 계속 함.

라이트가 스타베이션 될 수 있음.

아토믹 연산으로 락을 절약할 수 있음.

#### Second readers-writes problem (favors writers)
라이트가 예약된 상황에서 리드가 또 들어오면 리드를 라이트 뒤에 함.

1.  라이트중일때 라이트가 또 오면, 라이트를 리드보다 앞서서 함

    노 스타베이션

1.  라이트중일때 라이트가 또 와도 리드를 다 하고 라이트를 함

### Prethreaded Concurrent Server

### Crucial concept: Thread Safety
Functions called from a thread must be *thread-safe*

스레드 언세이프한놈들

1.  Unprotected shared variables.
2.  Keep state across multiple invocations.
3.  Return a pointer to a static variable.
4.  Calls thread-unsafe functions.

### Reentrant Functions
스테이트가 필요 없고, 주어진 정보만 가지고 다 리턴되는 함수.

같은 인풋엔 항상 같은 아웃풋이 나옴. Stateless

*숙제*: 1-element 짜리 shared buffer. 목요일까지.

--------

> 5월 14일 목요일

Mutex
--------
### Events
### Threads
### Threads are State Machines
### States
* Thread State
  - Program counter
  - Local variables
* System State
  - etc

### Concurrency
### Interleaving
### Intervals
### Intervals may overlap
### Precedence Ordering
### Partial Orders
* Irreflexive
* Antisymmetric
* Transitive

### Total Orders

### Implementing a Counter
### Using Locks
### Mutual Exclusion

### Deadlock-Free
### Starvation-Free

### LockOne
### Deadlock Freedom
### LockTwo
### Peterson's Algorithm
Starvation-free

스레드가 둘뿐인 경우

### The Filter Algorithm for n Threads
### No Starvation
### Bakery Algorithm
### Bakery Y2**32K Bug

--------

> 5월 28일

### Total Store Order
멀티코어가 아니고, 싱글코어만 쓴다. 멀티코어라 하더라도 각각의 코어들이 다
똑같다 하면 문제가 없죠. 캐쉬에서 읽어오나, 메모리에서 읽어오나 항상 같은 값을
읽어오니까.

그래서 이게 싱글코어일떄엔 문제가 안되는데, 멀티코어일때엔 문제가 됨. L1, L2를
따로 갖고있고, L3를 쉐어한다던가 등..

* SPARC
* X86

읽는것보다, write가 오래걸려서 씀.

Store가 있은 후 Load를 수행할때 이 순서가 바뀌는것을 허용함.

Wait-Free Implementation
--------
Lock 없이 컨커런트 프로그래밍 하기

### Rationale for wait-freedom
왜 락이 안좋은가?

#### Heterogeneouse
특정 프로세스만 엄청 느리다던가

#### Fault-tolerance
한놈이 락을 잡은채로 죽어버리면?

실제로는 보통 타임아웃을 씀. 죽은것같으면 락을 강제로 풀고 나옴.

하고싶은것: Wait-free 한 구현을 쓰자

레지스터만 가지고는, Wait-free 한 무언가를 만들수는 없다.

### The Consensus Hierarchy
CAS는 강력하고 비쌈. 락을 안쓴다고 했지만, 소프트웨어적으로 안썼을 뿐이지,
하드웨어에선 BUS를 락으로 걸어버림.

### LL & SC
Load locked, store conditional.

이게 조금더 Lightweight 하고, 더 acceptile한데, 인텔에서는 특허때문에 못쓰는거임

--------

> 6월 2일

링크드리스트

### 지난시간
어떻게하면 락을 안하고 쓸 수 있을까?

Concurrent Objects
--------
두개 네개 이상의 코어가 하나의 기계 안에 들어있으니, 10% 20%라도 좀더
빨라져야하지 않을까? 패러렐리즘을 넣으면 코어를 두개를 쓰고 네개를 쓰면 스루풋이
올라갔으면 좋겠다.

병렬화 하는거죠. 한순간에 하나가 아닌 두개, 네개의 인스트럭션 스트림이 동시에
작업을 할 수 있도록. 자 근데 문제 자체가, 시퀀셜 프로그램이라면 코어가 아무리
많아도 아무런 소용이 없죠. 어떻게 하면 시퀀셜한 프로그램을 컨커런트하게 여러개의
스레드에서 돌아가게 바꿀 수 있을까?

백지장도 맞들면 낫다. 일을 나눠서하는거죠. 근데 나눌때마다 싱크로나이제이션을
해야되는데, 이 코스트가 경우에따라 꽤 클 수 있다.


### Coarse-Grained Synchronization
오브젝트에 어떤 메서드들이 있는데 이 메서드들을 한번에 하나씩만 해야한다.

Q-lock. 쭉 줄을 세워서 한번에 하나씩만 할 수 있게 만드는거지.

이건 오브젝트 입장에서 보면 시퀀셜하게 돌아가는거랑 다를게 없으니, reason하기가
쉽죠. 자바 앞에 `Synchronized`라는 키워드를 붙이면 이거처럼 작동한다. 가장
간단한 싱크로나이제이션.

문제는 이건 동시에 한놈밖에 실행이 안된다는게 문제다. 프로그램 안에 오브젝트가
여러개라던가, 메서드 말고 다른 할 일이 많으면 성능 이득이긴 한데 그렇지 않을경우
시퀀셜이랑 큰 차이가 없다. 저 메서드 실행이 보틀넥이면, 아무소용 없게된다.

### This Lecture
오늘 할것은, 어떻게하면 그런것들을 더 패러렐하게 만들 수 있을지를 논한다.

문제 자체가 시퀀셜할수밖에 없는 문제라면 이건 병렬화 할 수 없다. 근데 만약
문제가 병렬화가 가능하다면 이건 뭔가 좋은 방법이 있을거다.

우리가 원하는건 어떤 오브젝트가 있는데 이 오브젝트를 컨커런트하게 만들어서, 여러
스레드를 부여하면 성능이 좋아지도록 만드는거야.

### Fine-Grained Synchronization
오브젝트 전체에 하나의 락을 부여하는 대신, 동기화가 필요한 최소의 단위에 락을
각각 부여한다. 독립적으로 수행할 수 있는 일의 단위가 열개다 하면, 스레드가 열개
들어가면 열개의 일이 동시에 진행가능해짐.

### Optimistic Synchronization
실패했을때의 패널티가 크긴 하지만, 걸릴 확률이 적을때 쓰는 방법.

### Lazy Synchronization
* Postpone hard work
* 예를들어 레드블랙 트리를 한다면, 딜리션 할때마다 밸런싱하지 말고 딜리션을 몇번
    한다음에 밸런싱을 몰아서 하기

1.  Logical Removal
2.  Physical Removal

### Lock-Free Synchronization
> Holy Grail

atomic 오퍼레이션(CAS, ...)만을 이용해 동기화를 구현.

Linked List
--------
이것들을 어떻게 자료구조에 도입할건지, 링크드리스트에서부터 알아보자.

이 링크드리스트가 항상 만족해야하는 Invariant가 딱 있음.

### Sequential List Based Set
* add()
* remove()

### Coarse Grained Lock
링크드 리스트 전체에 락을 잡음

### Fine Grained Lock
Requires **careful** thought

노드마다 락을 다 따로잡음

##### Hand-over-Hand locking
링크드리스트 조작하느라 링크드리스트 traversal을 하고있는데, 둘이 막 추월하면
어떡함.
```
a -> b -> c
```
이렇게 있으면 a에 락을 잡았다면 b에 락을 먼저 잡고 a를 풀어야함. a풀고 b
락잡으면 망함.

* Add할때엔 잘 됨
* Remove할때에도 보면 내가 지울 놈에 대해서도 락을 잡아야한다.

### Insight
* If a node is locked
  * No one can delete node's *successor*
* If a thread is locked
  * asdf

내가 락 잡고있는놈에 대해서만 어떠한 조작을 가할 수 있다.

락일 잡기 전까지는 내가 읽었던놈이 어떻게 변할지 모름.

### Optimistic Synchronization
오퍼레이션을 무조건 락 잡고만 하지말고, 해피하게 락 안잡고 읽기만 쓱쓱 하다가,
실제 액션을 하기 직전에 락을 잡고, Validate하고, 오퍼레이션을 하고 락을 품.

##### Evaluation
옵티미스틱이라는건 내가 락을 안잡지만, 항상 두번씩 traverse하게됨. "락 없이 두번
스캔하는 코스트"가 "락 잡으면서 한번 스캔하는 코스트"보다 작을때에만 쓰는거.

* Drawback
  - `contains()`도 락을 필요로함

리드는 락을 잡지 않도록 하게해보자.

### Lazy List
Optimistic이랑 같은데, 아래 두가지가 다름.

* 한번만 스캔한다
* `contains()`는 락을 안잡음

핵심
* 결국 모든 문제의 핵심은 `remove()`

Logical delete와 Physical delete를 구분하기.

노드별로 따로 마크 비트를 둬서, 링크 안에 있어도 마크가 되어있으면 없는놈
취급함. 그리고 나중에 몰아서 Physical하게 삭제.

remove() 할때엔 락을 잡으면서 travarse하고, 마크를 먼저 함. 지울놈의 부모로부터
지울 놈을 끊은다음, 부모의 락을 풀고 지울놈을 실제로 지움.

Lazy한 `add()`, `remove()`, wait-free한 `contains()`

##### Evaluation
`contains()`가 wait-free라서 좋고, `contains()`는 자주 부르는 함수라서 좋음.

나쁜점 : ?

### Traffic Jam
한놈이 락을 오래잡고있으면, 그 뒤로 계속 밀림.

### Lock free vs wait-free
Lock free가 wait-free보다 약함.

wait-free는 모든 순간 모든 프로그레스가 항상 진행중인걸 일컫지만, Lock-free는
계속 진행이 되고있을수는 있어도 같은 위치를 계속 뻉뻉이돌수도 있음.

### Lock-free wait-list
Add는 CAS 쓰면 쉽게 됨. Remove는 문제임

`AtomicMarkableReference` 연산을 써야됨. 포인터에서 한 비트 빌어다가 그걸 마크
비트로 쓰기.

아까같이, Logical delete를 먼저 하고, Physical delete를 나중에 하는거임.

1. 지울 노드를 먼저 로지컬 딜리트한다고 마크함.
2. 부모로부터 지울 노드를 떼는걸 CAS로 함. 이때 마크 되어있으면 fail. 그냥 fail
된채로 둠.
3. 나중에 다른 Traverse라던가 할때 그때 physical delete를 수행함.

그래서 로지컬 딜리트만 되고, physical delete가 미뤄진 상태여도 사실상 delete
된거나 다름없음.

### 성능비교
코스그레인, 파인그레인은 저 밑에 있고, 레이지랑 락프리가 비슷함.
