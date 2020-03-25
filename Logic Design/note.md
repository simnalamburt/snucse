Week 1, Mon
========
첫수업. Zoom 연습을 서로 하고 온라인으로 출석체크를 했다. 교수님께서 수업 참여를 할것이기때문에 마이크와 (가능하다면) 카메라가 필요하다고 함. 그리고 Zoom에 "Raise Hand" 기능이 있으니 필요하면 활용할것. 카카오톡 오픈채팅방이 있으니 사용할것. 학생 전원의 NDA가 모이면 강의 녹화영상을 풀겠다.

교수님께서 온라인 강의를 위해 비싼 마이크를 샀다고 자랑하심

**실습은 2인 1조인데, 원하는 팀원이 있다면 구글폼으로 2020-03-17 까지 제출할것.**

책: Contemporary Logic Design, Randy H. Katz and Gaetano Borriello, Pearson, 2004 2판. 구할 수 있으면 구할것

오프라인 퀴즈, 오프라인 실습, 오프라인 시험이 예정되어있지만 코로나바이러스 대유행때문에 수업일정이 바뀔 수 있다는점을 양해해달라.

### 무엇을 하는 수업인가
Digital Logic Design에 대해 배운다. Digital Signal은 이산적이고(discrete) quantize되어있음. 대부분의 물리적인 값들은 연속적이지만, digital abstraction에선 그 값들의 이산적인 부분집합만 다루게된다.

0과 1은 보통 물리적인 신호의 범위로 다루게됨. 예를들면 0은 0.1V 이하, 1은 5V 이상으로 정의할 수 있다. 전압이 그 사이에 걸쳐있다면 노이즈

신호를 degrade하는건 모조리 노이즈다. 아날로그 신호와는 다르게 디지털 신호는 노이즈가 껴도 결과가 변하지 않게 만들 수 있기때문에 더 robust함.

### Design of Digital Systems
세개의 레벨로 나눔

- System Design: 하나의 시스템을 여러개의 서브시스템으로 쪼개는 일
- Logic Design: 바로 이 수업
- Circuit Design: 전전회

### Switching Circuit
- Combinational Circuit(조합 회로): 출력이 현재 입력에만 의존함
- Sequential Circuit(순차 회로): 출력이 현재와 과거 입력에 의존함(=memory가 있음)

&nbsp;

Week 1, Wed
========

왜 논리설계를 배우는가? 현대 컴퓨팅 기계의 제일 기본이기때문. 컴터가 어떻게 동작하는지 알아야 더 효율적인 소프트웨어 디자인이 가능.

뭘 배우는가? 부울 대수, Logic minimization, state, timing, CAD tool과 같은 논리설계 기본을 배운다. 디지털 시스템의 "state"에 대한 개념에 대해 배운다.

HDL로 디자인하고, 시뮬레이션하고, 컴파일한 뒤 실제 프로그래머블 하드웨어(FPGA)에 매핑해본다. 많은 일들이 병렬로 동시에 일어나기때문에 소프트웨어 디자인과 많이 다를것임

Primitive digital hardware devices
- Logic computation devices (sense & drive): AND, OR, NOT, 등, 조합논리에 관한것들
- Memory devices (store): 순차논리에 관한것들

### Computation
Computation의 기본 단위로는 이런것들이 있는데, 얘네들을 하드웨어에서 어떻게 구현하는지 알아보자

- Representation: `0`, `1` 등의 값을 회로로 표현하기
- Assignment: `x = y`
- Data operations: `x + y - 5`
- Control
  - Sequential Statements: `A; B; C`
  - Conditionals: 조건문
  - Loops: 반복문
  - Procedures: 함수호출들

보통 하드웨어에서 false을 1V 이하, true를 3V 이상 이런식으로 표현하는데 이때 1~3V 사이의 값은 undefined로 취급한다.

스위치로 가장 기본적인 논리회로를 구현할 수 있다. 연결된(closed) 상태를 1, 끊은(open) 상태를 0으로 취급한다고 쳐보자. 두 스위치를 직렬로 연결하면 AND를 구현할 수 있고, 두 스위치를 병렬로 연결하면 OR를 구현할 수 있다. 그리고 이렇게 만든 스위치들을 조합해 더 복잡한 논리회로를 만들어낼수도 있다.

현실에서는 스위치가 아니라 트랜지스터를 씀. CMOS는 전압으로 켜고 끄는 아주 작은 스위치다. Source와 Drain을 open할지 close할지를 Gate의 입력전압으로 정한다.

종류 | G is low | G is high
-----|----------|----------
nMOS | open     | closed
pMOS | closed   | open

(Len01-intro.pdf 15p 참고) nMOS랑 pMOS를 하나씩 써서 NOT Gate를 만들 수 있다.

CMOS를 잘못 조합해서 한 회로에 다른 두 전압이 섞여지게 만들거나, 아예 전류가 흐르지 않게 만들어질 수 있는데, 이경우 undefined이다. Well-formed CMOS circuit에선 이런 상황이 일어나면 안되고, 반드시 출력에 하나의 driver만 존재해야한다.

nMOS의 구조: Source-Gate-Drain 세 terminal이 존재함. Polysilicon - SiO2 (절연체) - Substrate 세 레이어로 만들어져있음. G에 강한 전압이 가해지면 substrate에 있는 전자들이 G terminal로 이동하면서 S-D 가 연결됨. 예전에는 Polysilicon 자리에 금속을 썼었는데, 더 잘 달라붙는 polysilicon으로 바뀜

### 조합논리 vs 순차논리
지금 입력에만 의존해서 결과가 나오는 회로는 Combination Circuit이다. 수학의 순수함수같은거임. `Output = f(input)`

Sequential Circuits은 이전의 입력이 미래의 결과에 영향을 주는 회로. 조합논리가 아닌거. State가 존재함. `Output = f(input, previous input)`

유명한 조합논리 기호들. 생긴거에 표준이 있다.

- Buffer: 아무것도 안함. 전압을 정규화하려고 쓰는거 (입력이 3.8V 이렇게 애매하게 들어와도 출력은 5V!) 논리회로 수업시간에는 잘 쓰지는 않겠지만, 현실세계에서 아주 주파수가 높고 프로패게이션 딜레이가 문제가 되는 고성능의 회로를 디자인할때에는 가끔 필요함.
- NOT, NAND, NOR: CMOS로 구현하기 가장 쉬워서 가장 흔히 쓰는거
- AND, OR

#### 조합논리 연습
조합논리회로의 예시: 전자시계 월별 day 수 계산기. 입력으로 월 과 윤년 여부를 받아서 그 월에 있는 day의 수를 출력하는 작은 회로

교수님께서 클럽가지 말고 집에서 안전하게 있으라고 하심

&nbsp;

Week 2, Mon
========
조합논리회로 연습으로, 입력으로 월(Month)와 윤년 여부(isLeap)를 넣으면 그 월에 있는 day의 수를 출력하는 작은 회로를 만들고있음.

[Garbage in, garbage out](https://en.wikipedia.org/wiki/Garbage_in,_garbage_out). 입력이 정의된 인코딩대로 입력되지 않을경우엔, 출력으로 아무거나 내뱉어라.

#### 순차논리 연습: 도어락
세개의 숫자(0~9)를 입력해서 비밀번호를 설정하고, 비밀번호를 다시 입력하면 문이 열리는 도어락을 만들어보자.

입력: 0~9 숫자니까 와이어 네개로 표현할 수 있다. (4bit의 표현범위는 0~16)\
출력: 문이 열려야하는지, 닫혀야하는지 여부

순차논리에는 시간의 개념이 존재하기때문에, 클락(clock)이 필요해진다! 그리고 State에 따라 출력이 달라지므로, Truth table이 아니라 State table 혹은 FSM으로 동작을 기술해야한다.

순차논리는 조합논리에 State/Clock만 더한것으로 생각할 수 있다.

&nbsp;

Week 2, Wed
========
모의 중간고사, 모의 기말고사 시험지를 나눠줘서 공부를 할 수 있게 할것이다.

### Boolean algebra
Algebraic structure란 무엇인가. 원소와 Binary/unary operators, 그리고 몇가지 Axiom으로 구성된 수학적 구조이다. 어떤 Axiom들이 있을까

1.  셋 안에 원소가 최소 두개 존재한다
2.  Closure, 연산에 대해 닫혀있음
3.  Commutativity, 교환법칙
4.  Associativity, 결합법칙
5.  Identity, 연산에 대해 항등원이 존재함
6.  Distributivity, 분배법칙
7.  Complementarity, 연산에 대해 역원이 존재함

Boolean algebra는 집합에 원소가 `true`, `false` 둘뿐이고 binary operator `or`, `and`와 unary operator `not`이 존재하는 algebraic structure이다. 위에서 언급한 7개의 axiom을 모두 만족시킬 수 있다.

Truth table로 표현 가능한 모든 임의의 Logic function은 AND, OR, NOT의 조합으로 표현할 수 있다.

Boolean algebra에서의 Axiom들과 Theorem들

1.  Identity, 항등원
    - X or false = X
    - X and true = X
2.  Null
    - X or true = true
    - X and false = false
3.  Idempotency, 멱등성
    - X or X = X
    - X and X = X
4.  Involution
    - !(!X) = X
5.  Complementarity, 역원
    - X or !X = true
    - X and !X = false
6.  Commutativity
    - X or Y = Y or X
    - X and Y = Y and X
7.  Associativity
    - (X or Y) or Z = X or (Y or Z)
    - (X and Y) and Z = X and (Y and Z)
8.  Distributivity, 분배법칙
    - X and (Y or Z) = (X and Y) or (X and Z)
    - X or (Y and Z) = (X or Y) and (X or Z)
9.  Uniting
    - (X and Y) or (X and !Y) = X
    - (X or Y) and (X or !Y) = X
10. Absorption
    - X or (X and Y) = X
    - X and (X or Y) = X
    - (X or !Y) and Y = X and Y
    - (X and !Y) or Y = X or Y
11. Factoring
    - (X or Y) and (!X or Z) = (X and Z) or (!X or Y)
    - (X and Y) or (!X or Z) = (X or Z) and (!X or Y)
12. Concensus
    - (X and Y) or (Y and Z) or (!X and Z) = (X and Y) or (!X and Z)
    - (X or Y) and (Y or Z) and (!X or Z) = (X or Y) and (!X or Z)
13. de Morgan's Law
    - !(X or Y) = !X and !Y
    - !(X1 or X2 or ... Xn) = !X1 and !X2 and ... !Xn
    - !(X and Y) = !X or !Y
    - !(X1 and X2 and ... Xn) = !X1 or !X2 or ... !Xn
14. Generalized de Morgan's Law
    - !f(X1, X2, ... Xn, 0, 1, or, and) = f(!X1, !X2, ... !Xn, 1, 0, and, or)
15. Duality (Meta-theorem)
    - 한 Boolean expression 안에 있는 모든 and와 or를 맞바꾸고 true와 false를 맞바꿔서, 한 expression의 dual을 얻을 수 있다.
    - f(X1, X2, ... Xn, 0, 1, or, and) 의 Dual은 f(X1, X2, ... Xn, 1, 0, and, or)

Theorems을 증명하는데엔 크게 두가지 방법이 있다.

Rewrite로 증명하기

1.  Rewrite로 증명하기

    ```
    (X and Y) or (X and !Y)
    = X and (Y or !Y)                 (Distributivity)
    = X and true                      (Complementarity)
    = X                               (Identity)
    ```

    ```
    X or (X and Y)
    = (X and true) or (X and Y)       (Identity)
    = X and (true or Y)               (Distributivity)
    = X and true                      (Null)
    = X                               (Identity)
    ```

2.  Complete Truth table로 증명하기, Perfect induction

    가능한 입력의 경우의 수를 모두 다 써서 수식이 맞다는걸 증명하면 증명된거임

### Realizing Boolean Formulas
입력이 2개일 경우, 16개의 가능한 논리회로 조합이 있다. 입력이 x개일 경우 2**(2**x)개의 가능한 논리회로 조합이 있다.

한 회로를 구현하는데엔 여러가지 방법이 있고, 방법에 따라 구현 비용이 모두 다르다. 어떤 회로는 구현하는데에 아주 적은 스위치가 소모되고, 어떤 회로는 아주 많은 스위치가 소모된다. 우리는 가능하면 회로를 싸게 구현해야한다.

AND, OR, NOT 보다 NAND, NOR, NOT이 더 저렴하다! 그리고 모든 논리회로는 NAND 단 하나만으로, 혹은 NOR 단 하나만으로 구현이 가능하다.

NAND와 NOR은 서로 듀얼이기때문에, 한 회로를 NAND로 구현했다면 그 듀얼에 해당하는 회로도 쉽게 만들 수 있음.

#### Waveform view of logic functions
시간에 따라 다른 입력을 연속적으로 흘려줌으로써 진리표를 쉽게 뽑을 수 있음. Propagation Delay때문에 출력이 약간 늦게 나오는것을 감안해라.
