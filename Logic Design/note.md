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

조합논리회로의 예시: 전자시계 월별 day 수 계산기. 입력으로 월 과 윤년 여부를 받아서 그 월에 있는 day의 수를 출력하는 작은 회로

교수님께서 클럽가지 말고 집에서 안전하게 있으라고 하심