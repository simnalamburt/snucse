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
7.  Complementarity, 상보성

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
5.  Complementarity, 상보성
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

&nbsp;

Week 1, Mon
========
#### Choosing different realizations of a function
하나의 진리표를 논리게이트로 옮길때에, 여러 구현방법이 존재할 수 있다. 구현 방법에 따라 Trade-off가 존재할 수 있다.

- 비싸고 게이트가 많은 방법
- 싸고 게이트가 적은 방법
- 단순하게 생겼지만 비싼 방법

XOR은 단순하게 생겼지만 내부 구현이 복잡하다. NAND도 AND와 비슷해보이지만 훨씬 싸다. 그리기에 단순한것과 실제로 단순한것은 별개이니 유의하자.

어떤 구현이 제일 나을까?

- 입력이 적을수록 좋다
  - 구현이 심플해짐, 서킷이 저렴해짐. 입력이 적으면 보통 게이트 수도 적기때문에 더 빠름.
- 게이트 수가 적을수록 좋다
  - 게이트 숫자가 회로 가격에 가장 직접적인 영향을 줌

### Two-level logic
논리회로를 잘 만드는 방법을 알아보자.

#### Canonical forms
하나의 Boolean function마다 유니크한 하나의 진리표가 존재한다. 그 진리표를 구현하는 방법에는 여러가지가 있을텐데, Canonical form은 그중에서 가장 standard한 형태를 의미한다.

- Sum-of-products (S-o-P) canonical forms
  - Truth table에서 결과가 1인 경우를 모두 모아놓은 형태
  - Disjunctive normal form, Minterm expansion 이라고도 불림
- Product-of-sums (P-o-S) canonical forms
  - Truth table에서 결과가 0인 경우를 모두 모아놓은 형태
  - Conjunctive normal form, Maxterm expansion 이라고도 불림

PoS form은 SoP form의 Dual이라고 볼 수 있음. Canonical Form이 Minimal form이 아님에 유의하라

- Minterm form과 Maxterm form은 간편하게 변환 가능함
  - Σm(1, 3, 5, 6, 7) = ΠM(0, 2, 4)
- F의 minterm과 F'(not F)의 minterm도 간편하게 변환 가능함
  - F = Σm(1, 3, 5, 6, 7), F' = Σm(0, 2, 4)
- F의 maxterm과 F'(not F)의 maxterm도 간편하게 변환 가능함
  - - F = ΠM(0, 2, 4), F' = ΠM(1, 3, 5, 6, 7)

교수님께서 수업하다가 터치펜이 고장나서 손가락으로 수업하심. 장인의 손맛

#### Incompletely specified functions
지금까지 배운 Canonical forms에선 on-set과 off-set중 하나에만 초점을 맞췄는데, "Don't care"도 표현할 수 있어야 한다. 아래 둘중 하나로 표현해야함

- on-set + dc-set
- off-set + dc-set

수식은 PPT 참고

### Motivation for Two-level simplification
논리회로 단순화 하는 방법들

- Minimal S-o-P, P-o-S realization 찾기
  - Exploit "Don't care" information in the process
  - Don't Care output은 아무렇게나 정의해도 상관이 없으니까, 이걸 이용해서 수식을 간편하게 만드는데에 쓸 수 있다.
- Algebraic simplification
  - Algorithmic/Systematic procedure가 아니여서, 지금의 표현이 minimum realization이라는것을 알 수 없다.
- Computer-Aided Design (CAD)
  - NP문제여서 최적해 찾기는 아주 오래걸린다. 특히 입력이 10개 초과로 넘어가면 아주 느려짐
  - Educated guesses 휴리스틱으로 풀수는 있긴 한데 최적해는 아님
- 손으로 하는것도 의미가 있음
  - 자동화 툴의 장단점을 익혀야히는데에 좋음
  - 작은 예제에 대해선 직접 결과를 체크하는 능력을 키워줌

논리회로를 단순화하는 두 테크닉

- Boolean Cubes
- Karnaugh-maps (K-maps)

두 방법 모두 Uniting Theorem에 기반한것임

#### The Uniting Theorem
A(B' + B) = A. Two-level logic 단순화의 핵심이다. 변수 X의 값과 무관하게 변수 Y의 값에 의해서만 결정되는 출력이 있다면 거기에 Uniting Theorem을 적용할 수 있음

#### Boolean Cubes
Uniting Theorem을 적용시키기 쉽도록 진리표를 시각화하는 방법. 입력이 N개이면 N-dimensional Cube에 매핑된다. 방법은 PPT 참고

&nbsp;

Week 3, Wed
========
Boolean Cubes는 input 수가 올라가면 힘들어진다. 그러면 어떻게 하면 될까

#### Karnaugh Maps
Flat map of Boolean cube. Adjacencies를 잘 보여주는 진리표의 대체재이다.

입력이 세개 이상일 경우, Gray-code를 기반으로 입력을 나열하면, 서로 인접한 칸끼리 입력이 1비트씩만 변하기 때문에 adjacenies를 쉽게 파악할 수 있다. 카르노맵의 양쪽 끝은 연결되어있다. 토폴로지가 도넛 모양임.

(카르노맵으로 수식 최적화하는거 PPT 참고)

변수가 5개 넘어가면 카르노맵으로도 어려워지는데, 이러면 사람이 안하고 컴퓨터가 해줘요!

숙제: ~~인풋이 26개인 아주 거대한 진리표를 minimize하는 회로를 만들어보세요!~~ 이건 만우절 농담이고, Chapter 2에 있는 Problem Set을 풀고, 스캔해서 온라인으로 Submit하세요. Pass/Fail임

카르노 맵은 중간고사에 반드시 나오니까 꼭 연습을 하세요!

&nbsp;

Week 4, Mon
========
2x2-bit multiplier를 카르노맵으로 최적화하는중

왜 2-level simplification인가? 최적화한 결과가 2-level logic이여서.

2-level simplification에 등장하는 용어들

- Implicant: ON-set과 DC-set으로만 이뤄진 subcube
- Prime implicant: 다른 Larger subcube에 합쳐질 수 없는 Implicant
- Essential prime implicant: 특정 ON-set을 이 prime implicant만으로만 커버할 수 있으면, Essential prime implicant. DC-set만 덮고있는건 essential하지 않음.
- Optimization Objective
  - Implicant들을 모두 Prime implicants들로 키우기
  - ON-set들을 제일 작은 숫자의 Prime implicants로만 덮기

2-level simplification 알고리즘

1.  카르노맵에 ON-set과 DC-set, OFF-set을 모두 그린다
2.  모든 Prime Implicants를 찾는다
    - 카르노맵의 맨 윗줄과 맨 아랫줄, 맨 왼쪽줄과 맨 오른쪽줄, 각 코너들이 모두 연결되어있다는 사실을 기억하라
3.  Essential Prime Implicant를 모두 찾아라. Essential Prime Implicants는 무조건 결과에 포함되어야함
4.  이제 Essential Prime Implicant에 의해 커버되지 않는 1들을 제일 적은 수의 Prime Implicant로 덮으려고 시도하면 된다 (NP-hard)

### HDL: Hardware Description Languages
하시설에서 배운거. 우리는 Verilog를 배운다. 손으로 논리회로를 그리는걸 Schematic Diagram이라고 하는데, Verilog를 쓰면 그것보다 훨씬 더 쉽게 논리회로를 짤 수 있다.

HDL의 역사

- Abel, 약 1983
- ISP, 약 1977
- Verilog, 약 1985
  - 파스칼, C와 유사한 문법
  - 코드가 짧고 작성하기 쉬움
  - IEEE 표준
- VHDL, 약 1987
  - Ada와 유사한 문법
  - Very general하지만 너무 verbose함
  - IEEE 표준

Abel, ISP는 프로토타입이고 Verilog와 VHDL은 널리 쓰임. Verilog가 한국 미국 등지에선 더 많이 쓰이는데 VHDL은 유럽에서 많이 쓰임

하시설에서 안배운거

- `$display`: 콘솔에 글자 찍는 명령어
- `$finish`: 시뮬레이션 멈추는 명령어
- Assign에도 delay를 줄 수 있다. Propagation Delay를 묘사 가능

&nbsp;

Week 4, Wed
========

#### Verilog Design Flow
1. Hierarchy/Block Diagram
2. Coding
3. Compilation
4. Simulation/Verification
5. Synthesis
6. Fitting/Place+Route
7. Timing verification

5/6 단계 이후 그 결과를 보고 최적화를 위해 힘들지만 2나 1로 돌아오기도 한다.

### Realizing SoP and PoS logic networks
Two-level logic을 NAND나 NOR 만으로 표현해보자.

드 모르간 법칙 `A' + B' = (AB)'`을 사용해 AND와 OR의 중첩으로 표현된 SoP Two-level logic을 쉽게 NAND + NAND 회로로 바꿀 수 있다. 마찬가지로 PoS도 쉽게 NOR + NOR 회로로 표현할 수 있다.

### Multilevel Logic
입력에서 출력까지 거치는 게이트가 두개 이상으로 여러개 있을 수 있다면 Multilevel Logic이다. 

장점

- 회로가 작아질 수 있다
- Gates have smaller [fan-in]. [Fan-in]은 게이트 입력 갯수, 항의 숫자를 말함.

단점

- 회로가 느려질 수 있다
- 디자인 하기 더 어려워진다
- 최적화도구가 two-level만큼 좋지 못하다
- 분석이 더 복잡해진다

Multilevel Logic도 SoP, PoS와 마찬가지로 NAND/NOR로 편리하게 변환이 가능함.

[Fan-in]: https://en.wikipedia.org/wiki/Fan-in

#### AND-OR-Invert (AOI) Gate
AND, OR, NOT 게이트 세개를 하나로 합쳐놓은것. 얘를 트랜지스터로 바로 구현하면 NAND, NOR 여러개를 쓰거나 AND, OR, NOT을 여러개 쓰는것보다 훨씬 컴팩트하다. 이런걸로 회로를 최적화할수도 있음.

&nbsp;

Week 5, Mon
========
#### Time behavior of combinational networks
Waveform: 시간의 변화에 따라 wire의 출력을 그린것. 실습시간에 Vivado나 ISE로 그리는 그거.

- Gate delay: 게이트 입력변화가 출력변화에 영향주기까지의 시간
  - Min delay, Typical/Nominal delay, Max delay
  - 회로를 설계하는 사람은 Max delay를 고려해 만들어야한다
- Rise time: 출력전압이 낮았다가 높아지는데에 걸리는 시간
- Fall time: 출력전압이 높았다가 낮아지는데에 걸리는 시간
- Pulse width: 출력전압이 낮은채로/높은채로 유지되는 시간

게이트 딜레이로 인해 게이트의 결과가 이상해질 수 있다. Delays matter!

Oscillatory behavior: 논리회로 배치에 따라, 딜레이때문에 회로가 출력하는 값이 하나로 수렴하지 못하고 계속 진동할 수 있다.

&nbsp;

Combinational Logic Technologies
--------
조합논리 기술들에 대해 알아보자

- Standard gates: Gate packages, cell libraries
- Regular logic: Multiplexers, decoders
- Two-level programmable logic: PALs, PLAs, ROMs

Random logic, Regular logic 구분이 그렇게 중요한건 아님

### Random (fixed) logic
Pritimive한 게이트들을 조립해서 만드는 단순한 로직을 Random Logic이라고 한다. 할 수 있는 일이 하나로 정해져있는 로직을 Random logic, Fixed logic이라고 한다.

1960년대에 트랜지스터 기술이 논리회로 만드는데에 보급되기 시작함. 논리게이트 역할을 하는 트랜지스터들이 만들어졌다.

오늘날에는 이런 게이트 역할만 하는 트랜지스터는 거의 안쓰인다. 그러나    이 때에 만들어졌던 디자인들은 여전히 라이브러리처럼 쓰이고있다.

### Regular logic
Logic의 내용을 자유롭게 바꿀 수 있으면 Regular Logic이라고 한다. 디자인을 빠르게 하고싶고, 엔지니어링 수정을 쉽게 해야하고싶어서 Regular Logic을 쓴다.

Regular Logic을 만드는 방법은 다양한데 MUX와 DEMUX를 많이 써서 쉽게 구현할 수 있다.

MUX와 DEMUX를 왜 많이쓰지? MUX와 DEMUX를 함께 사용하면, 임의 개수의 입력을 임의 개수의 출력에 연결할 수 있음. 하나의 계산 모듈을 여럿이 공유하기위해서도 MUX-DEMUX를 쓸 수 있음. Mux-demux 콤보는 유용하다!

Cascading multiplexers: 작은 mux 여러개를 조립해 큰 mux를 만들 수 있다.

### Loop-Up Tables (LUTs), MUX as general-purpose logic
2**n : 1 multiplexer를 사용해 변수가 n개인 모든 함수를 구현할 수 있다! Truth table을 그대로 mux의 입력에 꽂아놓으면, n개의 스위치만 조작해서 모든 임의의 함수를 구현할 수 있다. 와!

변수 하나를 줄여서, 2**(n-1) : 1 mux로도 변수가 n개인 모든 함수를 구현할 수 있다!

일단 n-1개의 변수를 control input으로 쓴다. 그리고 Truth table을 보면 출력이 마지막 변수인 X, 혹은 그 변수의 complement인 X'에 tie된 경우가 있는데, 이걸 활용해 Truth table의 행 갯수를 반으로 줄일 수 있다. 0과 1만 출력으로 뱉는 Truth table이 아니라 0, 1, X, X' 를 뱉는 Truth table로 바꾸는거다. 이런 테크닉을 써서 2**(n-1) :1 mux로 변수가 n개인 함수를 구현할 수 있음.

&nbsp;

Week 5, Wed
========
### Template-based Logic, DEMUX as general-purpose logic
DEMUX. Decoder는 Input이 1로 고정되어있는 demux의 특수한 경우라고 생각할 수 있다. demux는 NOT과 AND, 혹은 NOT과 NAND만 써서 쉽게 만들 수 있음.

n : 2**n decoder를 사용해 변수가 n개인 모든 함수를 구현할 수 있다! decoder가 Minterm generator처럼 동작하기때문에, decoder의 출력에 AND, OR, NOT 몇개를 연결하기만 해도 모든 minterm을 표현할 수 있음.

작은 mux로 큰 mux를 만드는 것 처럼, decoder도 작은 decoder 여러개를 조합해 만들 수 있다.

### Programmable Logic Arrays (PLAs)
AND plane(AND array)과 OR plane(OR array)두개의 큰 평면으로 나뉘어져있음. 실제로는 NAND와 NOR로 구현함

(PPT 그림 참고)

안쓰는 커넥션을 임의로 없애는 방식으로 회로를 재프로그램한다. fuse (평상시엔 연결됨, 원할때 날림) 혹은 anti-fuse (평상시엔 끊어짐, 원할때 연결) 을 씀.

PLA를 그림에 그릴때엔, 회선이 너무 많아서 더 간략화된 형태로 그린다. 그림은 PPT 참고. "x표"가 연결되었다는 뜻임.

### PAL vs PLA
- PLA: Programming Logic Array
  - Unconstrained, fully general AND/OR arrays
- PAL: Programming Array Logic
  - PLA중에서, AND plane은 커스텀이 가능하고, OR plane은 고정되어있으면 PAL
  - 기능이 제약되어있으나, 더 싸고 더 빠름

PAL의 유즈케이스: BCD to Gray code converter. PLA로 해보면, OR Plane에 "reuse"가 단 한개도 없다. 이런 경우는 PAL로 하면 더 빠름

PAL이 더 빠른 이유

1.  PAL은 OR gate의 입력 (fan-in)이 작음
2.  PAL은 Wiring overhead가 적음 칩 면적을 절약할 수 있다.

&nbsp;

Week 5, Mon
========
PAL, PLA 실제로 써보자!

- W = AB + A'C' + BC'
- X = ABC + AB' + A'B
- Y = ABC' + BC + B'C'

수식에 9개의 항이 있는데, PLA에는 7개의 term밖에 없다. 어떻게하면 될까?

1.  concensus theorem을 적용시켜 W에서 항 하나를 날린다

    W = AB + A'C'

2.  다른 수식에 ABC와 ABC'가 이미 쓰이는데, AB를 ABC와 ABC'의 조합으로 표현할 수 있다.

    W = ABC + ABC' + A'C'

이제 7줄짜리 PLA로도 표현이 가능해진다. 이렇게 제한된 리소스로 논리회로를 구현하기위해 수식을 변형하는 행위를 Technology mapping이라고 함.

### ROM: Read-Only Memory
ROM은 입력으로 "메모리 주소"를 넣으면 "그 메모리에 저장된 데이터"가 나오는 거대한 논리회로라고 볼 수 있다.

거대한 decoder와, 고정된 output들을 program하고있는 bit lines, word lines들의 행렬로 이뤄져있다.

ROM은 거대한 Truth table을 그대로 회로로 옮겨놓은것으로 볼 수 있다. ROM으로도 임의의 회로를 구현할 수 있음.

ROM은 AND array가 fully decoded되어있는 PLA라고 볼 수 있다. PAL과는 다르게 OR array가 completely flexible하다.

### ROM vs PLA/PAL
ROM 장점

- 빠르게 디자인할 수 있음: output function을 minimize할 필요 없음
- 모든 input combination에 대해 별도의 구현을 다 해야할 떄
- Output functions들 사이에 Product term 공유가 적을때

ROM 단점

- input이 하나 늘때마다 크기가 두배
- Don't Care term을 활용할 수 없음

PLA 장점

- Multi-output minimization을 해주는 Design tool을 쓸 수 있을때
- There are relatively few unique minterm combination
- Many minterms are shared among the output functions

PAL 단점

- OR plane의 입력(fan-in)이 제한되어있음

### ROM, PAL, PLA
ROM: Full AND plane, general OR plane

- 제일 쌈, High-volume component
- 입력이 n개인 모든 함수 구현 가능
- Medium speed

PAL: Programmable AND plane, fixed OR plane

- 적당한 가격
- Can implement functions limited by number of terms
- High speed (only one programmable plane that is much smaller than ROM's decoder)

PLA: Programmable AND, OR plane

- 셋중에 제일 비쌈 (디자인이 제일 복잡함)
- Product term 제한 아래에는 모든 함수 구현 가능
- 느림 (Programmable plane이 두개여서)

경우에 따라 비용효율적인 Programmable Logic을 골라서 쓰자. 최근 PLA, PAL는 FPGA로 대체되었다. Fixed Logic보다 덜 효율적이지만 여전히 소프트웨어보다 훨씬 나아서 여기저기에 쓰임.

**5월 첫째주에 중간고사 본다. 시험범위: 챕터 1 ~ 챕터 5, 조합논리에 대한 모든것.**

&nbsp

Case Studie in Combinational Logic Design
--------
조합논리를 설계하는 일반적인 과정

1. 문제 이해
2. 적절한 design representation으로 문제 표현
3. Implementation target 고르기
4. Implement하기


