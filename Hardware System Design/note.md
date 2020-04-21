Week 1, Tue
========

강의하는 기분을 내기위해 교수님께서 강의실에서 원격수업을 하시기로함. ETL에 목소리가 녹음된 PPT를 업로드했다. 강의시간에는 기본적으로 PPT를 재생하고, 학생들이 질문을 하면 바로 교수님이 답변하는 플립러닝 형태로 진행하기로 함.

매 주 Lab report를 다음주까지 제출해야함. Grace period는 없다.

Team formation: 온라인 강의를 하는 기간동안에는 1인 1팀이고, 중간고사 이후부터 FPGA로 실습을 해야하는데 FPGA 수가 모자라서 2인1조 팀을 만들게될것이다.

### 강의 목표
하드웨어/소프트웨어 시스템 디자인을 하면서 어떤 문제를 겪게될지, 어떻게 해결하는지를 알아보자.

Zynq FPGA를 실제로 받아, Zynq FPGA 센서 위에서 동작하는 이미지 인식 어플리케이션을 만들것임. 하드웨어뿐만 아니라 소프트웨어도 co-design 하게된다. Verilog, Vivado 등을 사용

이미지 인식은 CNN으로 할것임. 보통은 Matrix-Matrix Multiplication으로 CNN을 구현하지만 (Convolution Lowering) 하드웨어에서는 그렇게 하는데에 이슈가 있다. 그걸 해결하는 방법을 알아볼것이다.

행렬곱을 가속하는 하드웨어도 Verilog로 설계한다. 베릴로그 짤막한 리뷰도 하게된다. Blocking이라고 제한된 메모리의 칩에서 행렬곱을 하는 테크닉이 있다 (행렬을 여러 조각으로 잘라서 연산함) Blocking 테크닉과 FPGA의 BRAM을 함께 쓰는 방법도 익힐것이다.

올바르게 동작하는 Baseline 디자인을 배우는 방법뿐만 아니라 최적화하는법도 배운다. Zero-skipping이 그중 하나. 전통적인 기법의 최적화도 한다. Direct memory access(DMA), Reduced precision, 등

우리의 디자인과 실제 Google, Apple, 삼성에서 쓰이는 신경망 가속기는 규모 면에서는 차이가 크지만, 최적화 아이디어는 견줄 수 있음.

- 우리: ~100 multipliers, 50MHz
- 구글 TPUv1: 64k multipliers, more than 500MHz
- Apple Neural Engin: 4k multiplers, more than 500MHz

### Why neural net Works?
왜 뉴럴넷이 동작하는지 항상 어려워했는데, 알고보니 실제 신경망의 동작원리와 유사한점이 많았다. 우리 시세포에 대해 알아보자.

V1 neuron이라는게 있다. 선을 감지하는 능력만 갖고있는 간단한 신경이다. https://en.wikipedia.org/wiki/Visual_cortex#Primary_visual_cortex_(V1) 얘 동작하는 원리가 퍼셉트론과 유사함.

근데 우리 시신경에는 저런 간단한 신경들의 출력을 입력으로 받는 "complex cell"이라는 뉴런이 하나 더있다. 입력중 하나라도 활성화되면 complex cell도 활성화되는, max 함수처럼 동작한다. 인공신경망의 Max Pooling Layer 역할을 하는것이고, Saliency selection이 가능해짐.

Cat Cell이라는것이 있다. 시신경 뒤의 여러 망을 거친 뒤, Inferior temporal cortex에 "고양이를 보면 무조건 활성화되는 셀", "사람을 보면 무조건 활성화되는 셀" 이런것들의 존재가 발견되었다. 인공신경망의 "output" 처럼 동작함

사람의 뇌는 새로운 물체를 보고 인식하기까지 200ms정도가 소요된다. 인공신경망은 그것보단 훨씬 빠름 (Optimized AlexNet: <100μs in GPU V100, ~1ms in Galaxy S10).

### Multi-layer perceptron (MLP)
(퍼셉트론 동작원리 설명)

퍼셉트론을 겹쳐서 Multiple Layers로 만들면 Step functions와 biases덕분에 Higher Order Function을 만들 수 있다.

### CNN
앞 레이어 입력 전체를 퍼셉트론에 넘기지 말고, 앞 레이어 입력의 일부(window)만 퍼셉트론에 넘기자.

이미지를 입력으로 하는 2D CNN 말고도, 3D CNN도 있다. Input Channel이 여러개면 3D CNN이 됨.

CNN에 대한 자세한 설명은 http://cs231n.github.io/convolutional-networks/ 참고

이 수업에선 트레이닝은 신경안쓰고, 평가(추론) 속도만 신경쓴다.

이 CNN 계산을 전통적인 방식으로 CNN을 구현하게되면 입력에 중복된 숫자가 너무 여러번 나오게된다. cuBLAS GEMM, GEMV에는 이런 문제가 있었어서 cuDNN V4에서 이런 문제를 해결했다. V5에선 Winograd convolution라는게 추가됨.

### 산업계에서의 사용
- Google TPU: 자체 실리콘 칩
- Microsoft Catapult: FPGA기반, 최근에는 실리콘칩 개발 시작함
- NVIDIA Volta GPU: GPU뿐만 아니라 Tensor Core라는 녀석을 탑재함. Tensor Core는 4x4 Fused Multiply Add에 최적화된 연산장치임

### 우리가 할 프로젝트
행렬-벡터 곱 연산장치를 직접 설계할것이다. Blocking을 기본적으로 사용하게됨.

소프트웨어로 이걸 구현하면 하드웨어 가속기 호출이 느리기때문에, 호출 오버헤드를 줄여야한다. 그러려면 블록 크기를 늘려야한다. 하지만 블록 크기를 무한정 늘릴수는 없으므로, 사용 가능한 메모리 크기와 사용 가능한 하드웨어 가속기 수에 의해 블록 크기가 결정된다.

직접 CNN을 구현하는게 첫 과제인데, 이후의 프로젝트에서도 이 구현체를 계속 사용하게된다.

Q: 하드웨어 가속기를 호출할때마다 매번 끝나기를 기다려야해서 오버헤드가 큰듯한데, 파이프라이닝을 하거나 비동기적으로 호출결과를 받아볼수는 없나요?

&nbsp;

Week 2, Tue
========
Verilog Design의 기본과, testbench에 대해 배워보자. Verilog와 Vivado에 대해 배울것이다.

우리의 어플리케이션은 MLP(멀티레이어 퍼셉트론)다. 블록 행렬곱 부분을 하드웨어로 치환할것인데, 이를 위해선 하드웨어를 디자인할 줄 알아야한다.

HDL(Hardware Description Language)이란? 하드웨어의 디자인을 추상적으로 표현하고, 디자인 수준에서 하드웨어의 디자인을 테스트할수있다. 쉽게 하드웨어를 디자인할 수 있다. Verilog는 아주 유명한 HDL중 하나다.

Number representation (피피티 참고). Sized number과 Unsized number이 있는데 unsized는 기본으로 32비트.

- x: Unknown Value. 한 회로에 두개 이상의 드라이버가 연결되면 x가 된다
- z: High impedance. 한 회로에 드라이버가 없으면 z가 된다

데이터타입

- Nets, `wire`: 와이어
- Variable, `reg`: 데이터 저장소
  - Integer variable
  - Time variable: 시간을 표현하기 위한 특수한 변수

Vectors, 배열이다. 메모리안의 원소를 표현하기 위해 주로 사용됨

Memory, 모델 ROM이나 RAM, 레지스터 파일 등을 추상화한것

`assign`, 물리적으로 와이어로 연결하는것을 뜻함

Verilog에는 다양한 연산자가 존재한다. 그러나 `Unsynthesizable Operators`라고 너무 복잡해서 하드웨어로 그대로 매핑될 수 없는 연산자도 존재함.

산술연산을 할때엔 기본적으로 2의 보수를 쓴다

Concatenation/Replication Operator: 여러 값을 하나로 붙이거나 복제해주는 특이한 연산자

Reduction Operators: Vector를 입력으로 받아 1bit 결과를 냄. 예를들어 모든 비트가 1인지 검사하는 연산자가 리덕션 연산자에 해당됨

Relational Operators: 비교연산자

Equality Operators: 두 유형의 이퀄리티가 있음

- Logical equality, `==`, `!=`: 자료형의 크기가 달라도 zero-extend 해서 비교함
- Case equality, `==`, `!=`: 자료형의 크기까지 같아야만 같다고 쳐줌

`initial` Block: 시뮬레이션 맨 처음에 딱 한번만 실행되는 블락, 여러 이니셜 블락이 있으면 동시에 병렬실행됨. `always` Block: 시뮬레이션을 하는 내내 연속적으로 계속하여 실행되는 블락. 우리의 모델 코드는 `initial`이나 `always` 둘중 하나 안에는 반드시 들어가야함.

Regular Delay Control: 연산자 사이에 딜레이를 줄 수 있음. testbench에 사용함

Intra-Assignment Delay Control: Assignment 도중에 발생하는 딜레이를 HDL로 기술하는게 가능해짐

Blocking Assignments, `=`: Assignment가 실행 순서대로 차례대로 순차적으로 일어남. Assignment 하나 할때마다 딜레이가 발생함.

Non-Blocking Assignments, `<=`: 넌블럭IO마냥 대입문을 만나도 일단 진행하고 일정시간이 지나면 Assignment가 끝남.

#### Event Timing Control
Event란 무엇인가? 레지스터나 넷의 값이 변하는 일

- Edge-Triggered Event Control
  - `@(posedge clock)`, `@(negedge clock)`와 같이 클락 엣지에 의해 발생되는 이벤트들
- Level-sensitive Event Control

`@(posedge clock or negedge reset_n)` 이런식으로 여러 이벤트를 조합할 수 있다.

#### Modules
기본적인 빌딩블록 하나가 모듈이 된다. 모듈은 함수처럼 `input`, `output`, `inout` 이렇게 파라미터를 노출한다. `defparam`으로 파라미터의 기본값을 만들 수 있다. 그리고 모듈 호출할때에 positional arguments 말고도 swift처럼 named parameter 문법을 쓸 수 있으니 잘 활용하자.

모듈을 사용할때엔 instantiation이 필요하다

#### Simulation
테스트하고싶은 유닛이 있을때 그 유닛을 테스트시켜주는 테스트코드를 Stimulus Block 혹은 TestBench라고 부른다.

&nbsp;

Week 2, Tue, Lab
========
Zoom이 중간에 끊기면 TA에게 이메일을 남겨주세요!

Vivado Tutorial 죄다 스킵함. Vivado는 2018.3 버전을 쓰자. PPT 보고 독학하기. MY_IP에서 IP는 Integrated Processor의 약자다.

테스트벤치 하는법도 아주 빠르게 넘어갔음.

NOTE: Vivado 프로젝트 만들때에 "Copy sources into project"를 체크 안하면 프로젝트 파일을 압축해도 소스코드가 포함되지 않을 수 있음. 과제 제출하기 전에 반드시 압축파일 안쪽을 살펴봐서 과제 소스코드가 정상적으로 잘 포함되어있는지 체크해주세요.

&nbsp;

Week 3, Tue
========
for, while, repeat 문을 쓸 수 있음. genvar와 generate 문을 써서, 반복적인 코드를 생략할 수 있음.

모듈 모델링 스타일에 여러가지가 있다.

- Structural style
  - Gate Level
- Dataflow style
  - Gate level보다 상위의 표현, 여러 비트들에 대한 계산을 겹쳐서 한번에 표현하기
- Behavioral or Algorithmic style
  - C 코드 처럼 절차적으로 서술하기
- Mixed style
  - RTL = synthesizable behavioral + dataflow constructs

모듈 인스턴스화 할때에 배열을 쓸 수도 있음.

```verilog
wire [3:0] out, in1, in2;

// basic array instantiations of nand gate.
nand n_gate[3:0] (out, in1, in2);

// this is equivalent to the following
nand n_gate0 (out[0], in1[0], in2[0]);
nand n_gate1 (out[1], in1[1], in2[1]);
nand n_gate2 (out[2], in1[2], in2[2]);
nand n_gate3 (out[3], in1[3], in2[3]);
```

### Understanding bus interface
베릴로그 코딩을 한 결과를 실제 하드웨어로 만들어보자.

실제로 구현을 할때엔 Synthesizable code를 매번 새로 구현하기보단, 기존 하드웨어를 재사용하는것이 좋다. IP Catalog에서 재사용 가능한 하드웨어 컴포넌트들중 하나를 고를 수 있다.

한 하드웨어 컴포넌트에는 기능이 엄청 많은데, 사용할 기능만 체크해주자. Flow Control도 Blocking, NonBlocking이 있는데 우리는 Non Blocking만 쓸거다.

이렇게 하면 하드웨어 컴포넌트에서 안 쓰는 핀이 없어지게된다.

Blocking/NonBlocking은 Bus Interconnect와 관련이 있다. 현대 하드웨어 시스템에선 CPU나 Memory와 같은 여러가지 컴포넌트들이 하나의 Bus에 붙어있다. CPU와 같은 Master component가 메모리 읽기와 같은 요청을 Bus에 보내면, Bus는 그 요청을 처리할 Slave가 무엇인지 찾아 전달한다. 우리는 ARM AMBA AXI bus를 쓰니 AXI 스펙대로 배워보자.

AXI 마스터가 AXI 슬레이브에 요쳥을 보낼 때 요청에 필요한 각종 정보를 보내는데, 그중 핸드셰이킹에 쓰이는 두 중요한 신호가 있다. Valid와 Ready이다.

#### Blocking
마스터에선 정보를 보내는것과 동시에 Valid 신호를 1로 셋해줘야한다. 받는 쪽에선 매 클락마다 Valid를 체크하여 Valid가 1이면 들어온 정보를 사용하고, Valid가 0이면 입력 정보들을 모두 무시한다.

반면 Raedy는 슬레이브가 컨트롤하는 신호다. 슬레이브가 받을 준비가 되었다면 Ready를 1로 설정하고, 준비가 되지 않았다면 0으로 설정한다.

Clock rising edge일 때 valid과 ready가 모두 1이면 커뮤니케이션이 발생한다.

Clock rising edge일 때 Valid가 1이지만 Ready가 0이면? 아무일도 일어나지 않는다. 보내는쪽에선 Valid가 1로 변할때까지 대기해야한다. 이래서 이 프로토콜은 Blocking이다.

#### Non-blocking
Non-blocking에선 ready가 항상 1이다. Ready 비트에 대해 신경쓸 필요가 없고, Sender가 절대 block되지 않기때문에 회로가 간단해진다. Non-blocking이 어떻게 동작하는지는 다음 시간에 더 자세히 설명하기로 함

&nbsp;

Week 4, Tue
========
중간고사가 취소되었다.

7주차에 중간고사를 볼 예정이었지만, 중간고사는 취소. 8주차 어린이날에 출석체크가 없는, Optional Lab 세션을 할 예정임.

앞으로 Lab Session을 17:30 시작한다. 미리 와서 미리 질문할 수 있음. 그리고 공식 Lab Session은 18:30 에 시작하고, 출석체크도 18:30에 한다.

Matrix Multiplication IP를 만들어보자.

2~3주차에는 Float32 MUL+ACC를 만들었다. 4주차에는 Processing Element를 만들게되고, 5주차에는 IP 전체를 만들게된다.

### BRAM Model
메모리가 32KB이므로 15bit로 모든 메모리영역을 표현할 수 있다. 하지만 모든 데이터가 4 byte align되어있어서, 실제로는 13bit만으로도 모든 데이터에 접근할 수 있다. 1 byte만 읽고싶으면, 4바이트를 통쨰로 읽은 뒤 하나만 고르면 됨.

4바이트중 일부 byte만 쓰고싶다면? Write Mask가 있어서 조절이 가능하다. 근데 우리는 이런상황이 없을거임

### Processing Element for Dot Product
1. peram이라는 곳에 먼저 곱셈을 수행할 Matrix의 row가 저장된다. `addr`과 `din` 핀을 쓴다. `we` 시그널이 켜져서 쓰기를 수행하게됨.
2. 그 다음 `ain`으로 벡터가 입력되고, `addr`로 peram안의 행렬을 입력한다. `valid` 시그널이 켜져서 계산을 시작함.
3. 부분합을 계속 계산하다가, 곱셈이 끝나면 출력하게된다. `dvalid`로 계산이 끝났다는것을 알림

Matrix는 PE 안에 저장되는데, Vector는 PE 밖에 저장된다. PE를 여러개 두고 하나의 Vector를 여러 PE에 동일하게 쓰기 위해서다.

### Components in Sequential Logic
조합논리와는 달리, 순차논리에는 아래와 같은 state들이 존재한다.

- Flip-flops
- Memory elements
- Shift registers
- Counters

#### Flip-flop
Positive Edge Triggered Flip-Flop이나, Transparent (level-sensitive) Latch나, 동작이 같지만 우리는 플립플랍만 쓸거다. Latch로 디자인하면 굉장히 복잡해서 우린 Latch는 안쓸거다.

- D-Type Flip-Flops: 평범한 플립플랍, 리셋 없음
- Asynchronous Reset D-Type Flip-Flops: 리셋이 들어오면 출력인 Q값이 즉시 리셋된다.
- Synchronous Reset D-Type Flip-Flops: 리셋이 들어와도 Rising Clock Edge에서만 값이 초기화됨.

#### Data Registers
Flip Flop의 배열. 얘에도 클락과 load, reset 등의 값을 넣어줄 수 있어요

#### Register File
여러 레지스터의 집합. 두개의 주소를 동시에 읽을 수 있음. 여러 주소를 동시에 읽을 수 있게 만들어서 ALU에서 덧셈할때 두 operand를 동시에 읽을 수 있게 만들거임.

#### Synchronous RAM
큰 레지스터 파일은 SRAM회로로 구현함.

#### Shift Register
레지스터인데, 클락이 하나 지나갈때마다 값이 한칸씩 Shift됨.

#### Binary Ripple Counter
플립플랍 여러개를 결합해서 카운터를 구현할 수 있다.

#### Binary Up/Down Counter
할뚜이따

#### Finite-State Machine
State는 항상 Input과 이전 State로 결정된다. Input ⨉ State → State

Output Function은 아래의 두 스타일중 하나로 만들 수 있다.
- Moore Machine: State → Output
- Mealy Machine: Input ⨉ State → Output

FSM은 항상 아래의 세 스텝으로 이뤄짐

1. State 초기화/업데이트
2. 다음 State로 넘어감
3. Output 출력

FSM의 예시

1. 0101 Sequence Detector
2. Vending Machine (자판기)
3. Simple PE (Processing Element) Controller

&nbsp;

Week 4, Tue, Lab
========
Practice 5는 PE implementation & BRAM Modeling다.

Practice 4에서는 FMA, Fused Multiply-Add를 했지만, 이제부턴 MAC,Multiply-Accumulate 을 한다.

&nbsp;

Week 5, Tue
========
ZedBoard를 구매했다.

ZedBoard가 언제 도착할지 불투명해 강의순서를 변경해 Week 6에는 컨벌루전 로워링을 먼저 한다.

### PE controller overview
지난주에 했듯이 PE 계산이 2 step으로 이뤄져있는데, 이걸 PE 혼자서 못한다. 스텝을 조절해주는 녀석이 필요한데 그게 PE controller다.

PE controller = PE + FSM + Global BRAM

PE controller FSM의 네 상태가 있음

- Idle: start == 0 이면 idle. start가 1이 되면 Load 로 넘어감
- Load: 데이터를 읽어서 matrix를 PE에, 벡터를 Global BRAM에 로드시키는 단계
- Calc: peram에 있는 matrix와 Global BRAM에 있는 vector를 곱하는 단계
- Done: dot product가 끝나고 결과를 dout으로 출력하는 단계

### Synthesizable Verilog code
한 state를 고정횟수만큼 반복할 필요가 있는데, Verilog에선 Counter를 만들어서 이걸 구현하게된다.

Synthesizer에게 필요한건 Verilog 코드뿐만 아니다. RTL code 외에도, Design environment, Design constraints, Technology library 를 요구함

Synthesis 과정

- Frontent
  - Parsing
  - Elaboration
    - **Unroll loops, expand generate loops**
    - Connect the internal components
    - Set up parameters passing for tasks and functions
- Backend
  - Analysis/translation
  - Logic synthesis
  - Netlist generation

Synthesizable code를 짜려면, synthesizable operators만을 사용해야한다.

We should avoid using any latches in a design. Assign outputs for all input conditions to avoid inferred latches. 조합논리를 짜려고 했는데, 의도치 않게 latch로 infer되는, 순차논리를 짜게되는 버그도 있다.

Latch 피하는법

1.  항상 모든 변수를 initial value와 함께 초기화시키기
2.  모든 조건문에 else문이나 default문을 잘 달아서 대입을 exhaustive하게 시켜주기

posedge/negedge와 plain level signal reference를 섞어 사용하는것도 문제임.

루프문도 유한한 횟수만 반복해야 synthesizable하고, forever 문은 timing control과 반드시 함께 쓰여야 synthesizable함.

Loop문 안에서 non-blocking assignment 문을 쓰면 의도치 않은 결과가 나올 수 있음.

### Logic optimization review
간단한 조합논리는 카르노맵으로 항의 수를 줄일 수 있음. 이런 최적화는 컴파일러가 자동으로 해줌.

그러나 순차논리의 경우, state의 갯수를 줄이는건 손으로 해줘야함.

FSM: 모든 입력 조합에 대해, Output과 state transition이 동일할 경우 같은 state이다.

&nbsp;

Week 5, Tue, Lab
========
Practice 6, PE Controller를 구현한다.

&nbsp;

Week 6, Tue
========
Convolution Lowering

### Convolution lowering on GPU
cuBLAS: BLAS(Basic Linear Algebra Subprograms) in CUDA

- GEMM: Matrix-Matrix multiplication, Problem in data duplication of input
- GEMV: Matrix-Vector multiplication

cuBLAS는 Input Matrix 데이터에 중복이 존재한다. 이거때문에 입력 행렬 크기가 GPU Cache 크기보다 커질 수 있는데, 이렇게되면 cache miss가 잦아져서 느려진다.

cuDNN

- V4: Focuses on avoiding duplication of input data in main memory
- V5: 3x3 컨벌루전을 위해 위노그라드 convolution이 추가됨

### Convolution lowering on TPU
TPU의 핵심은 Matrix-Matrix multiplication unit이다.

cuDNN에서는 Convolution operation을 소프트웨어로 구현했는데, 여기에선 하드웨어로 하게된다.

TPU systolic execution: MAC Unit이 격자 모양으로 깔려있고, 데이터는 가로세로로 움직이면서 행렬곱 계산에 필요한 연산을 자동으로 함.

행렬곱과 동시에 Systolic Array 맨 밑에선 Partial sum을 계속 계산한다

Accelerator area and power is dominated by memory buffer. 메모리가 클수록 외부와의 인터랙션을 덜 해도 되니까

### Tesla
Tesla HydraNet: One of the world-largest CNN models. 테슬라도 자체 칩을 만들어서 하드웨어로 HydraNet을 평가한다.

(PPT 참고)

### HW 가속기 스타트업
- Graphcore: $200M series D, Microsoft Azure Cloud에 납품
- Habana: $75M series B, 인텔에 $2B로 인수됨
- Groq: $62M, 1 Peta-Ops chip
- Nuvia: $53M, series A
- Cerebras: $112M, Aragonne National Lab

### nVidia TensorCore
Tensor Core: 64개의 half-precision 부동소수점(FP16) 곱셈을 1 clock cycle에 할 수 있다.

Tensor Core는 FP16을 원소로 갖는 4x4 행렬의 FMA를 1 clock cycle에 할 수 있는데, Tensor Core가 여러개 있기때문에 하나의 GPU 스레드는 여러 Tensor Core 연산을 병렬로 수행한다.

타일링을 여러 레벨로 하게된다

- Warp block
- Thread block
- Tensor Core block

&nbsp;

Week 6, Tue, Lab
========
Lab 2의 부활. 멀티레벨 퍼셉트론 대신 CNN 쓰는게 다에요.
