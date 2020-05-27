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

Week 6, Mon
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

&nbsp;

Case Studie in Combinational Logic Design
--------
조합논리를 설계하는 일반적인 과정

1. 문제 이해
2. 적절한 design representation으로 문제 표현
3. Implementation target 고르기
4. Implement하기

&nbsp;

Week 7, Mon
========
### Case 1: BCD to 7-segment
문제 이해: 논설 실습시간에 만든 그 회로. BCD 입력을 4bit로 받아, 7 세그먼트 출력인 7bit를 뱉는 회로다.

문제 표현: Truth table을 만들어보자.

Implementation target:

- ROM으로 구현한다면 이 시점에 이미 끝났음
- Don't care가 많으므로, PAL/PLA도 유용할 수 있다

PAL/PLA로 만들기 위해, K map을 그려보자. 그러면 15 unique product term이 나오는데, PAL/PLA로 만들려면 unique product term이 작을수록 좋다. 다른 product term의 조합으로 표현할 수 있는 product term은 모두 없애, 9개의 unique product term으로 줄였다.

이렇게 표현한 뒤에 보면, 한 output에 최대 5개의 product term이 들어가서, PAL로 표현하기 부적절할 수 있다. PLA로 쉽게 표현 가능.

반드시 PAL로 표현하고싶은데 product term 갯수가 PAL의 product term 갯수 제한보다 더 커지면 어떻게 할까? multi-level logic로 바꿔야한다.

CAD tool의 도움을 받아 함수들간의 common sub-expression을 찾아 이걸 PAL의 입력으로 넣어주면 된다. PAL은 shared term이 많아도 활용이 불가능한데, 저렇게 공통된 부분을 sub-expression으로 미리 처리한 뒤 PAL의 입력으로 넣어주면, PAL로 처리하지 못하는 회로도 PAL로 처리할 수 있게된다.

### Case 2: Logical function unit
(PPT 참고) 두 입력을 주고, 두 입력 사이에서 어떤 연산을 할지 스위치로 선택이 가능한 유닛

8:1 MUX로 편리하게 구현이 가능하다.

### Case 3: Production line control
(PPT 참고) 컨베이어 벨트 위에 Rod가 실려 움직이는데, Rod가 원하는 길이에 딱 맞는지 검사하는 논리회로를 만들어보자.

몹시 간단하니 걍 gate 몇개 조합해서 만들면 됨

### Case 4: Calendar subsystem
(PPT 참고) N월의 마지막날이 28, 29, 30, 31일중 어느것인지 판별해주는 회로. 윤년 여부와 N을 입력으로 받는다.

윤년 규칙이 좀 복잡하다

- For years after 1582 (Gregorian calendar reformation)
- All years divisible by 4 except years divisible by 100 are leap years
- Yet, years divisible by 400 are leap years

이걸 논리회로로 구현해보자

### Activity: divisible-by-4 circuit
회로 `f(N) = (N % 4) == 0` 를 만들어보자. 이때 N은 네자리 10진수가 BCD로 인코딩되어 입력된다.

&nbsp;

Week 7, Wed
========
윤년 계산기 계속 만드는중.

- All years divisible by 4 except years divisible by 100 are leap years
- Yet, years divisible by 400 are leap years

위의 규칙을 `leap_year_flag = D4 * (D100)' + D400` 로 구현했다.

### Arithmetic circuits
지원하는 자리수가 커질수록 느려지므로, Time vs space trade off 가 존재함.

정수를 표현하는 세 방법으로 아래의 세개가 있는데, 각각이 무엇인지, 다른 방법들의 단점과 2의 보수가 좋은 이유를 잘 이해해야함.

- Sign and magnitude
- 1's complement
- 2's complement

2's complement에서 Carry를 무시할 수 있는 이유는? N비트 2의 보수가 원소가 2^N개인 유한체여서, 덧셈에 대해서 순환군을 형성하므로.

Integer overflow가 발생했는지 판별하는 방법:

- 양수끼리 더했는데 결과가 음수
- 음수끼리 더헀는데 결과가 양수

&nbsp;

Week 7, Fri
========
**TODO**

&nbsp;

Week 8, Mon
========
**TODO**

&nbsp;

Sequential Logic
--------
이제 Stateful한 시퀀셜 로직 디자인에 대해 배워보자. 순차논리란: circuits with feedback. outputs = f(inputs, past inputs, past outputs)

유명한 시퀀셜 로직으로는 이런게 있다.

- Simple circuits with feedback
- Latches
- Edge-triggered Flip-flops

그리고 레지스터에 대해서도 배워보자

- Shift Registers
- Simple Counters

### Simple circuits with feedback: Inverter Pair
(생김새는 PPT 참고) 피드백이 존재하는 간단한 논리회로로 회로에 state를 저장할 수 있다.

### Memory with cross-coupled gates
- Cross-coupled NOR gates (R-S Latch)

  Inverter Pair와 유사한데, 두 입력인 R(reset), S(set)의 값에 따라 출력을 0으로 고정하거나 (R=1, S=0) 1로 고정시킬 수 있다 (R=0, S=1)

- Cross-coupled NAND gates

  얘도 Inverter Pair와 유사하다. 입력 R', S'에 따라 출력을 0으로 고정하거나 (R'=0) 1로 고정시킬 수 있다. (S'=0)

R-S Latch는 입력을 R=S=1로 주면 안된다.

### R-S Latch analysis
R-S Latch는 입력으로 R, S을 받고 출력으로 Q(그리고 Q')를 뱉는데 이것이 바로 입력으로 들어온다. 순차논리를 어떻게 분석할까?

먼저 Feedback path를 끊어서, R-S Latch를 R, S, Q(t) 입력으로 받아 Q(t+dt)를 출력으로 뱉는 조합논리로 탈바꿈시킨다.

R-S Latch using NAND도 같은 패턴으로 분석할 수 있다.

### Gated R-S Latch
R-S Latch는 R과 S 둘 중 하나라도 1이 되어버리면 값이 즉시 변경된다. 이걸 원치 않으므로 enable이라는 입력을 하나 추가로 만들어서, enable이 1일 때에만 R, S 입력이 효과를 발휘하도록 만든다.

### Clocks

&nbsp;

Week 8, Wed
========
**TODO**

&nbsp;

Week 9, Mon
========
기말고사는 두번 볼것같다. 지금 안은 아래와 같다

- 기말1: 2020-06-01 월 수업시간, Chapter 5 조합논리까지
- 기말2: 2020-06-17 수 랩시간, 2020-06-19 금 오후, 2020-06-22 월 수업시간, 2020-06-24 수 수업 혹은 랩시간, Chapter 6 순차논리부터

(수업에서 투표를 열심히 함)

이렇게 될 것 같다

- 기말1: 2020-06-01 월 수업시간, Chapter 5 조합논리까지, 90분 시험
- 기말2: 2020-06-17 수 랩시간에 기말을 본다. 2020-06-17 수 수업시간에는 수업을 안한다. 대신 보강수업을 한다. 시험시간은 미정이지만 아마도 2시간

기말고사 Open Book은 아니다. A4 한면 cheat sheet 허용.

### Comparison of latches and flip-flops (FFs)
**TODO**

### Typical timing specifications
- setup and hold times
- minimum clock width (Tw)
- propagation delays (Tpd): low to high, high to low, max and typical

low to high Tpd랑 high to low Tpd랑 다를 수 있다

### Verilog behavioral model of an edge-triggered D flip-flop
여러 조건 주고 베릴로그로 Flip flop 짜라는거 하드웨어 회사 취직할때 아주 많이 나오는 문제다.

`always @ (podedge CLK)` 문을 써서 쉽게 짤 수 있다. Output에 레지스터를 연결하고싶은 경우, `output reg`로 쉽게 짤 수 있다.

### 74x74-like D flip-flop with preset and clear
NOTE: ~X 핀을 입력일때엔 X_L라고 쓰지만, 출력일때엔 보통 XN라고 씀. X_L가 Active
Low 이런 뜻인데, Active low는 입력에 대해서만 쓰는 말이니까

CLR과 PR 핀이 asynchronous하다고 쓰여져있는데, 이거는 rising CLK edge가 오지
않아도 CLR과 PR 핀이 변하는 순간 바로 값이 반응한다는 뜻임.

**TODO**

### Registers
Flip-flops와 유사한 controls & logic 들의 집합. 연관되어있는 여러 값을 저장한다. 클락과 reset/set lines를 공유한다.

Register file: 여러 레지스터들의 집합. CPU와 GPU의 key component다. mux/demux로 레지스터들을 관리한다

### Shift register
레지스터의 일종. 매 사이클마다 값이 1씩 시프트된다.

Universal shift register: 매 사이클마다 값이 어느 방향으로 시프트될지 설정할 수 있는 shift register

&nbsp;

Week 9, Wed
========
시험 기출 미리 올려드리겠습니다. 그리고 시험 답은 한국어 혹은 영어로 쓸 수 있습니다.

### Shift register application
1.  시프트 연산 구현하는 ALU에 사용할 수 있다. PRNG(의사난수생성기)의 일부로 많이 쓰임
2.  Parallel-to-serial conversion for serial transmission
3.  Pattern recognizer
4.  Straight ring counter (1000 0100 0010 0001)
5.  Mobious counter, Johnson counter (1000 1100 1110 1111 0111 0011 0001 0000)
6.  Binary counter
7.  Offset counter

먼 지역에 8비트 정수를 보내고싶은데, 1비트씩밖에 보내지 못하는 상황이라고 해보자. 이 경우 양쪽에 Shift register를 사용하면 쉽게 1비트씩 정보를 보내고 받을 수 있다. PCIe같은애들이 1 LANE당 1 cycle에 1 bit만 보낼 수 있는데, 얘네도 이런식으로 양쪽에서 정보를 보내고 받는다.

Shift register를 사용해, 입력 스트림에서 원하는 연속된 패턴이 발생했는지 검사하는 장치를 쉽게 짤 수 있다.

Mobious counter는 가능한 경우의 수가 0000, 0100 무조건 이 둘중 하나다.

- 0000 1000 1100 1110 1111 0111 0011 0001
- 0100 1010 1101 0110 1011 0101 0010 1001

Binary counter 구조는 PPT 참고. XOR이 어느 비트가 뒤집혀야하는지를 결정한다. 특정 비트의 하위 비트가 모두 1이면, 다음 클락에 그 하위 비트들은 모두 0이 되어야하고, 특정 비트는 1이 되도록 하면 된다.

실제로 쓰는 카운터는 단순히 클락과 1 세는 기능 말고도 이런 기능들이 붙어있다

- Enable 기능(EN)
- 1111이 되었는지 감지하는 기능 (RCO, Ripple carry out). 이게 있어야 counter 여러개를 조합해 큰 counter를 만들 수 있다.
- 0으로 초기화하는 기능 (CLR, Clear)
- 원하는 숫자로 set 하는 기능 (A, B, C, D, Load)

Starting offset counter: 0이 아니라 특정 숫자부터 시작하는 카운터. Preset을 지정하고, RCO를 Load에 연결하면 된다. (PPT 참고)

Ending offset counter: 1111이 아니라 특정 숫자에 끝나는 카운터. QA, QB, QC, QD가 특정 값일때 CLR가 1이 되도록 하면 된다. (PPT 참고)

Starting-Ending offset counter: 위의 두개를 조합하면 된다.

### 결론
1.  Latch와 Flip-flop은 모던 디지털 시스템의 근본 빌딩블럭이다.
    - "memory"를 구현하는데에 쓰인다
    - 레지스터와 카운터를 만드는데에 쓴다
    - Digital system = memory + combinational logic
2.  Timing constraints are real-world design issues in digital logic design
    - Setup time and hold time constraints must be satisfied
3.  HDLs are heavily used to describe sequential logic, too

&nbsp;

## 7. FInite State Machines: FSMs
Sequential Logic은 Combinational Logic + FSM 으로 나눌 수 있다.

- Asynchronous sequential logic: Wire is storage element. No clock
- Synchronous sequential logic: There is explicit storage element. There is clock (periodic waveform). State changes occur in lock step across all storage elements using the clock.

Asynchronous sequential logic은 state 관리가 몹시 어려워 잘 쓰지 않는다.

### FSM
유향그래프로 FSM을 나타낼 수 있다

States: 유향그래프의 node
Transitions: 유향그래프의 edge

수업 끝 후 Q&A

- Q: 교수님 혹시 김진수 교수님 OS 수업시간에 들어오셨었나요?
- A: 제 TA가 잘못들어갔어요. 김진수 교수님 OS 수업은 워낙 명강이라 저도 듣고싶은데, 제가 들어가면 안좋아하실까봐.. 오해 없으시길

&nbsp;

Week 10, Mon
========
우리가 지금까지 했던 전자 도어락, n-bit Shift register, 3-bit up counter 등등 모두 FSM으로 볼 수 있다.

어떻게하면 FSM을 로직으로 바꿀 수 있을까?

- Register, flip-flop으로 state를 저장하고
- next state를 계산하는 조합논리를 만들고
- 클락시그널마다 state가 next state로 넘어가게 하면 된다
  - 클락 주기가 next state 계산하는데에 필요한 딜레이보다 커야한다
  - 너무 오래 기다리면 성능이 떨어지니 주의

FSM은 Mealy machine과 Moore machine으로 나뉜다

- Mealy machine
  - output = f(state, input), output이 transition에 연관됨
  - 상대적으로 state 수 적음
  - 입력이 async할경우 문제가 생길 수 있음
  - 입력이 변하면 출력이 즉시 변함 (No cycle delay)
- Moore machine
  - output = f(state), output이 state에 연관됨
  - 상대적으로 state 수 많음
  - 입력이 async해도 별 문제 없음
  - Mealy에 비해 1 cycle delay 존재

Mealy는 입력이 output에 영향을 주기때문에, 입력이 변한 순간 바로 output이 변한다. 반면 Moore는 input이 next state에만 영향을 주기때문에, 현재 입력이 next state로 넘어가고 나서야 output에 영향을 주기때문에 mealy에 비해 1 사이클 딜레이가 있다.

![A cow saying "Moo"](moo.jpg)

둘중에 뭐가 Mealy이고 뭐가 Moore인지 헷갈리는데.. Moore가 1사이클 더 느리고 더 무식하게 생겼으니 Moore라고 외우자.

Mea

#### Basic FSM design approach
9스텝으로 나뉜다

- State/output diagram
  - 1: State/output table or diagram
  - 2: Minimize # of states if possible
- State/output table
  - 3: State variable assignment
  - 4: Transition/output table
  - 5: Choose a f/f type
  - 6: Excitation table
- Excitation/output equations
  - 7: Excitation equations
  - 8: Output equations
  - 9: Draw a logic diagram

예제 문제를 풀어보자.

예제: 입력으로 CLK와 X를 받고, Z 하나를 출력 하는 synchronous FSM을 만들어보자. 입력으로 패턴 0011 혹은 1100이 들어오면 1를 출력하고, 그 이외의 경우 0을 출력하는 회로이다.

##### 1: State/output table or diagram

(PPT 참고)

중복된 state도 잘 없애고, 예외 케이스가 발생하지 않게 state간 간선을 잘 그어주면 16페이지 슬라이드처럼 나옴

다른 접근방법도 있음: 18페이지 슬라이드. Mealy에서 4비트 패턴을 찾는데엔, state가 3bit만 기억하고있으면 됨. 4비트 미만의 입력이 입력되었을때 잘못 1이 켜질 수 있긴 한데, 애초에 4bit 패턴을 찾는 회로여서, 입력이 4비트 미만일경우 출력이 undefined라고 치면 된다.

State transition diagram 말고 PPT와 같이 표로도 나타낼 수 있는데, 이걸 Tabular form of state transition diagram이라고 함.

##### 2: Minimize # of states if possible
서로 다른 state인데 모든 input에 대해 output과 next state가 완전히 같다면 두 state는 같은 state이다.

##### 3: State variable assignment
N개의 state를 나타내기 위해선, `k = ceil(log_2 N)` bit 메모리가 필요하다. k개의 flip flop을 쓰면 됨.

state assign을 어떻게 하느냐에 따라 서킷 성능에 미치는 영향이 큼. Practical guidelines로는 이런게 있음

- 시작 state는 0
- transition할떄 바뀌는 variable 수를 최소화하삼
- 연관된 state들 사이에서 바뀌지 않는 variable 수를 최대화하삼
- 대칭성을 활용하삼: 연관된 state들은 1비트만 다르고 나머지는 똑같게 한다던가
- unused state를 risk 혹은 cost를 줄이는 용도로 잘 쓰세요
- decompose: state의 각 비트가 특별한 의미를 갖도록 분해할 수 있음
- 최소 필요한 비트 수 보다 더 쓰는게 성능에 도움이 될 수 있다
  - One-hot encoding

unused state가 몇이 되느냐에 따라 회로가 더 저렴해질 수 있음

##### 4-6: Transition/Excitation/Output Table
Transition Table: 위에서 한 그거

Output Table: output이 드러난 그것

Excitation Table: Flipflop에 어떤 입력을 줘야하는지도 같이 나타난 transition table

Excitation Table에는 D_C, D_B, D_A 이런 핀이 새로 생겨서, flipflop을 어떻게 조작할지가 직접 나온다.

##### 7-8: Excitation/Output Eqs.
Flipflop과 output을 관장하는 D_C, D_B, D_A, Z 는 모두 state와 X를 입력으로 갖는 조합논리인데, D_C, D_B, D_A, Z를 어떻게 하면 최소한의 회로로 표시할 수 있는지 여기서 계산해야한다.

##### 9: Logic Diagram
이 예제는 결과적으로 14 NAND, 3개의 flipflop, 1개의 not 게이트로 구현이 가능하다.

Unused states일때의 next state는 Don't Care로 두면 회로 만드는 비용을 줄일 수 있다.

unused state로 잘못 빠지는 경우를 대비해, unused state의 next state가 used state가 되도록 해주면 리스크를 줄일 수 있다. 리스크를 감당할 수 없는 경우엔, don't care로 두지말고 명시적으로 unused state로 보내주면 좋다.

### Basic sequential circuits revisited
Shift registers와 Counters를 FSM 관점에서 다시 보자

- Revisited: 3-bit binary counter
- Revisited: Shift register
- More complex counter example

위 세개 예제를 풀면서, Unused state와 don't care를 exploit 하는 방법을 잘 알아보자.

#### Selt-starting solution
예시: Self-starting counters

맨 처음 전원이 켜졌을 때 카운터가 unused state 내지는 invalid state에 있을 수 있다. 어떤 invalid state에 있더라도 언젠가 valid state로 들어간다는 사실을 보장하도록 만드는 것이 바로 self-starting solution이다.

Self-starting solution은 state를 임의로 초기화할 필요가 없지만, 대신 Don't Care 최적화를 제한할 수 있다.

(PPT 참고)

카운터와 시프트 레지스터는, output = 현재 state이다. 그러나 이건 특수한 경우이고, 보통의 밀리 머신은 output = 조합논리(현재 state, 현재 input) 임

### Moore vs Mealy machine
- 밀리가 state가 더 적음
  - 밀리는 transition이 output이지만 무어는 state가 output이기 떄문
- 무어가 더 안전함
  - 무어는 output이 clock edge에만 변함 (always one cycle later)
  - mealy는 입력이 변하면 즉시 output이 변함. 두 장치가 연결되어있을 때 위험할 수 있다.
- 밀리가 입력에 더 빠르게 반응함
  - 무어는 무조건 한 클락 기다려야함

&nbsp;

Week 10, Mon
========
#### Example: Vending machine
(PPT 참고)

자판기를 무어와 밀리머신을 둘 다 써가며 다양하게 구현해보자.

1.  무어 머신: 동전 넣는거에 따라 state가 변하고, state에 따라 출력이 나오게 하면 됨
2.  무어 머신 + one-hot encoding: one-hot을 쓰면, product term의 곱셈 갯수가 준다!
3.  밀리 머신

#### Verilog Description of FSM
베릴로그로 FSM 짜는 템플릿이 있다

(PPT 참고, 기본적으로 case 문을 많이 썼다)

`parameter`는 상수 정의하는 문법입니다. 모든 프로그래밍 언어는 상수를 정의하는 메커니즘을 갖고있죠

(파이썬: ._.)

#### FSM summary
우리가 아는 대부분의 시스템은 FSM이다. 컴퓨터도 state가 아주 거대한 FSM이라고 볼 수 있음.

state가 있는 회로를 어떻게 FSM으로 변환하는지, FSM을 어떻게 회로로 표현하는지, FSM을 어떻게 HDL로 표현하는지 알아봤다.

- Q: Verilog로 Don't Care를 명시해서 자동으로 회로를 최적화시킬수는 없나요?
- A: 걍 specify를 안하면 Don't Care라고 인식해서 알아서 최적화해줘유

&nbsp;

## 8. Working with FSM (Sequential Logic Optimization)
FSM 표현을 더 적은 리소스로 하는법을 알아보자.

1.  State minimization
    - state 수가 적으면 state bit 수도 적어짐
    - state bit 수가 적으면 구현해야할 수식 숫자도 줄음
2.  Encodings: State, Inputs, Outputs
    - Dense한 인코딩을 쓰면 구현해야할 수식 숫자는 줄지만, 식이 더 복잡해질 수 있다
    - Sparse한 인코딩을 쓰면 더 단순한 수식이 나옴
    - Input/Output 인코딩은 보통은 선택의 여지가 없음

### State Minimization/Reduction
크게 두 방법이 있음

- Row Matching Method
- Implication Chart Method

#### Row matching method
equivalent states를 모두 찾아, 중복을 제거하자. equivalent state 찾는법은 아래와 같다.

1. 모든 state를 나열함
2. output behavior가 같은것들로 모두 group함
3. 한 group 내에서 next state transitions가 같은것들끼리 모두 group함
4. 2와 3을 거쳤는데도 한 group 안에있는것은, next state transitions와 output behavior가 모두 같은 state임 (equivalent state)

Example: `010`, `110` sequence detector (PPT 참고)

&nbsp;

Week 10, Wed
========
#### Implication chart method
두개의 state가 equivalent한지 체크하는 다른 방법.

가로축에는 S(0)부터 S(n-1)까지, 세로축에는 S(1)부터 S(n)까지 나열한다. 그리고 가운데에 있는 표에 체크해서 총 nC2 가지의 모든 경우의 수를 나열했다. 두 state의 output이 다른 경우는 같은 state일 가능성이 없으니 X표 쳐버리고, output이 같은 경우만 비교하면 된다.

이미 알고있는 equivalent한 칸들과 equivalent하지 않은 칸들을 사용해, equivalent 여부를 알 수 없는 칸들을 transitive하게 동치인지 아닌지 체크를 해주면 된다.

Problem Set으로 이거 연습을 꼭 해보세요.

- Q: 이거 1-pass로 모든게 풀리는 알고리즘인가요?
- A: 아니다. 2-pass 이상이 필요할 수 있음.
- Q: 안 지워진 박스는 quivalent하다는게 어떻게 증명되나?
- A: 동치가 아닌 여러 state들을 다 검사했는데도 disprove가 안되었다는것은, equivalent하다고 간주해도 문제가 없다는 뜻이다.

### State Assignment
각 symbolic State를 어느 비트로 배정할까? 어떻게 배정하냐에 따라 회로의 비용과 성능이 달라진다.

n bit로 m개의 state를 표현하려 할 때, `(2**n)!/(2**n - m)!` 개의 경우의 수가 존재한다. n, m 숫자가 작아도 수많은 경우의 수가 존재함. 다 해보고 최적을 찾는것은 불가능하니, 휴리스틱으로 결정해야한다. 조합논리 최적화할때 쓰는 아래의 세 메트릭으로 성능을 비교하면 된다.

- Size: 로직 숫자와 플립플랍 수
- Speed: 로직의 depth와 fanout
- Dependencies: decomposition

대충 아래와 같은 전략이 존재함

1.  Sequential: 000, 001, 010, 011, ...
2.  Random
3.  One-hot: 0001, 0010, 0100, 1000
4.  Output
5.  Heuristic

위 전략 모두 최적해라는 보장이 없다. 회로 최적화와 비슷한 Intractable problem임

#### One-hot State Assignment
- Simple: 인코딩하기 쉽고 디버깅도 편리함
- Small Logic Functions: 논리회로 생김새도 간단해짐
- Good for Programmable Devices
  - 많은 flipflop이 이미 준비되어있음
  - Simple functions with small support (signals its dependent upon)
- Impractical for large machines: 큰 머신에서 one-hot을 쓰면 flip-flop 소모량이 너무 커짐

보통 머신을 통쨰로 one-hot으로 만들기보단, FSM을 여러 작은 부분 FSM으로 만들어서 작은 FSM을 one-hot으로 만든다.

one-hot에 살짝 변형을 넣은 인코딩 방식을 많이 쓴다. one-hot + all-0 같은것들

#### Bit change heuristic
bit switch가 최소화되는 방향으로 state를 배정해보자. bit switch를 최소화하는게 왜 좋은가? bit change가 적을수록 전력을 적게쓴다.

State map: 각 state가 몇비트인지를 카르노맵처럼 그린것이다. state map상에서 상하좌우로 1칸씩 움직이면 1bit만 변하는것이다. state가 statemap상에서 이동을 적게할수록 좋다.

#### Adjacency Heuristics for State Assignment
(PPT 그림 참고)

이 세가지 조건을 만족하게 state를 assign하면, 하드웨어 코스트를 줄일 수 있다. 그리고 겸사겸사 bit change도 함께 줄어들음. 우선순위 순서(Successor/Predecessor 휴리스틱)대로 아래와 같다.

1.  next state를 공유하는 경우: `c = i*a + i*b`
2.  조상을 공유하는 경우: `b = i*a`, `c = k*a`
3.  output behavior가 같은 경우: `j = i*a + i*c`, `b = i*a`, `d = i*c`

우선순위대로, 위 조건을 만족하는 state들은 group하여 statemap 상에서 가까이 놓아야한다.
