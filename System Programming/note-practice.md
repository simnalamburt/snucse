시스템 프로그래밍 실습
========

과제 제출은 기본적으로 이메일을 쓴다.

```
To: tskim@dcslab.snu.ac.kr
CC: sjpark@dcslab.snu.ac.kr
Subject: spp#_2013-11392_HyeonKim
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
