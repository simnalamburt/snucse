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

TPU systolic execution: MAC Unit이 격자 모양으로 깔려있고, 데이터는 가로세로로 움직이면서 행렬곱 계산에 필요한 연산을 자동으로 함. 행렬곱과 동시에 Systolic Array 맨 밑에선 Partial sum 결과를 계속 읽어, 계산 결과를 저장한다.

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

&nbsp;

Week 7, Tue
========
Zynq FPGA에 대해 배워보자

### Why Hardware?
소프트웨어 대신 하드웨어로 만들면 성능도 좋고 전기도 덜쓴다. 하드웨어 가속기는 점점 흔해지고있음. 하이엔드 스마트폰에는 Neural Processing Unit도 흔하게 탑재되고있음

- Apple: A12, A13
- 화웨이: Cambricon-X, Hi-Silicon solutions
- 구글: Pixel 3, 4, on-device AI를 제공하는 Visual core가 있음
- 삼성: 갤럭시 S10부터 새 NPU가 들어감, zero skipping function 관련해 자세히 배울 예정

### Two Ways in Hardware Design
Chip vs FPGA

- Chip 장점: 대량생산 비용 몹시 저렴함, 저전력, 고성능
- Chip 단점: 소량생산이 매우 비쌈, Design time이 긺 (1.5년 이상), 7nm의 평범한 칩 하나 디자인하는데에 10M$ 이상이 필요함

그래서 대신 FPGA를 쓴다

- FPGA 장점: 소량생산에 유리함, 빠른 디자인 시간 (몇시간 단위)
- FPGA 단점: 칩에 비해 성능이 안좋고 전기를 많이 쓴다.

### Zynq FPGA
소프트웨어 부분과 FPGA부분이 AXI 인터페이스로 소통하게된다. Zynq FPGA에는 다양한 페리퍼럴들이 있는데, 얘네들이 인터커넥트로 연결되어있다.

- Zyng Processig System (Zynq PS) = APU + DRAM + peripherals + ...
- Zynq Programmable Logic (Zynq PL)

### Zync Programmable Logic
Logic fabric Configurable Logic Block(CLB), switch matrix, interconnect의 집합이다. CLB를 고쳐서 로직을 구현할 수 있다. CLB 안에는 Look Up Table (LUT)이 있어서, 임의의 조합논리를 구현할 수 있게 만들어놨다.

- 1 LUT have 6 inputs
- 1 Slice = 4 LUTs + 8 F/Fs

Switch matrix는 slice-to-slice, CLB-to-CLB/IOB 연결을 관리한다. LUT 입력뿐만 아니라 Carry Signal도 CLB로 들어오고 나감.

그 외에 특별한 블럭들이 있다

- Input/Output Block (IOB)
- DSP48E1
- BRAM

### Zynq PS-PL Interface
AXI 표준을 쓴다.

Software->Hardware communication에선 memory-mapped IO (pointer to device register)와 memory-mapped on-chip memory를 쓴다.

### MV Accelerator
이번주부터 MV 가속기를 짜기 시작할것이다.

(PPT 참고)

여러 BRAM 모듈을 다루는것이 까다롭다.

&nbsp;

Week 7, Tue, Lab
========
Zync 보드를 조심히 다루세요. 부서져있다면 미리 말하세요.

(PPT 참고)

&nbsp;

Week 8, Tue
========
휴강

&nbsp;

Week 9, Tue
========
소프트웨어-하드웨어 통신에 대해 배워보자. DRAM은 그냥 램처럼 쓰면 되는데 BRAM은 그렇게 간단하지 않다. Memory-mapped I/O를 사용해 BRAM에 접근하는 방법에 대해 알아보자.

임베디드 시스템은 아래와 같이 이뤄져있다.

- 프로세서
- 메모리 컨트롤러
- 페리퍼럴
- 시스템 버스
- 페리퍼럴 버스

CPU와 BRAM을 연결해보자.

- CPU in PS, AXI interconnect
- BRAM in PL, BRAM controller

소프트웨어가 하드웨어와 통신하는 방법

1. Memory-mapped I/O
2. Consider it as a device (requires driver)

### mmap() BRAM
Xilinx address editor에서 BRAM의 메모리 offset을 지정할 수 있다. mmap()에 성공하면 그냥 그 메모리 영역을 읽고 쓰기만 해도 알아서 디바이스에 읽고쓰기를 할 수 있다.

(PPT 참고)

### Memory/Storage Address Space
Virtual address space, physical address space, logical block address space, physical block address space 등 다양한 주소공간이 존재함.

### Page Table
페이지 테이블은 VA -> PA 매핑을 저장하는 맵. 맵이 너무 커지는걸 막기 위해 Hierarchical page table도 만듦. 48비트 주소공간은 9*4 + 12 이렇게 4 level page table로 만듦

### Cache & TLB
L1 Cache, L2 Cache, L3 Cache 등 다양한 캐시가 존재함. Page Table 액세스가 느려서 TLB도 만듦. TLB miss가 나더라도, 최근에 액세스한 페이지 테이블은 MMU cache가 도와줄 수 있음.

### Decompositing Load Instruction Execution
memory mapped IO로 BRAM을 읽는다고 쳐보자. CPU가 L1 캐시 접근하는것조차 복잡하다.

1.  Load unit accesses L1-data $
    - TLB access for virtual address to physical address translation
    - Non-cacheable access for hardware components other than main memory

캐시 미스가 날경우 CPU가 Bus를 통해 BRAM에 요청을 보내는데 이건 다음수업에서 하자

### IOMMU: Input Output Memory Management Unit
하드웨어 컴포넌트가 메인 메모리에 접근하기 위해선, CPU뿐만 아니라 하드웨어 컴포넌트도 Virtual Address를 쓸 수 있어야한다. 여기서 IOMMU가 등장한다.

IOMMU는 하드웨어 컴포넌트를 위한 VA -> PA 변환기임.

하드웨어가 Physical Address를 그냥 곧바로 쓰면, 주소 공간이 낭비된다. 예를들어 하드웨어를 안쓰는동안에는 그 Physical Address를 못 쓰게됨. 그래서 몇년 전부터 하드웨어 컴포넌트에도 virtual address 개념을 쓰기 시작했음.

하드웨어마다 페이지테이블이 생기고, IOMMU가 노는 메모리 공간을 잘 재사용해줌.

### Interconnect
이번 랩에선 CPU와 하드웨어가 Bus로 통신하는걸 하고, 다음주 랩에선 하드웨어 컴포넌트끼리 Bus로 통신하는걸 하게됨.

&nbsp;

Week 9, Tue, Lab
========
Vivado에서 AXI Interconnect를 어떻게 쓰는지 등의 설명이 있었음

&nbsp;

Week 10, Tue
========
IP core, IP block에서의 IP: intellectual property

AXI interconnect를 활용해 HW block들끼리 서로 통신하는 방법을 알아보자.

- Q: 기말일정은 어떻게 되나요?
- A: 이번수업 끝날때에 조사해봅시다

### AMBA3 Advanced eXtensable Interface (AXI) Protocol
- Multiple channels
- Narrow and wide transfer
- Single credit-based flow control: valid and ready signals
- Burst
- Split transaction to overlap request and data transfer
- Multiple outstanding requests
- Implementation issue: connectivity and arbitration

### Split Transacntion
address, data, response는 모두 독립적으로 처리된다.

(PPT 참고)

write address/control 채널로는 쓰기 주소/제어에 관한 일만 한다. 읽기 작업을 동시에 안한다. 이렇게 타입별로 채널을 여러개를 둔 이유는 여러 통신을 동시에 하기 위해서.

커뮤니케이션 채널이 늘면 속도는 빨라지지만, 트레이드오프가 있다. 일단 시그널이 너무 많아짐. (PPT 25장 참고)

각 채널별로 valid, ready 시그널이 존재하는데, 이 시그널덕분에 성능이 좋아진다.

### Narrow vs Wide transfer
bus에도 비트가 전달되는 lane이 여러개 있다. lane이 여러개 있기도 하고 (ARSIZE) lane별로도 길이가 있음 (ARLEN) 각 레인은 1사이클당 1byte의 정보만 보낼 수 있고, 각 레인에는 길이만큼의 비트가 올려질 수 있음.

WSTRB (write strobes) 핀을 사용해, 현재 레인의 어디가 유효한 입력인지를 같이 전송해준다.

lane size를 잘 exploit하면 wide transfer, 잘 exploit 못하면 narrow transfer

비효율적인 narrow transfer를 애초에 왜하나? 보낼 정보가 한방에 준비되지 않을 수 있으니까.

### Flow control
flow control 방식이 여러개다

1.  Stop-and-Wait: 사이클이 흐를때마다 Req, Ack, Req, Ack, ... 이 반복됨

2.  Single Credit-based Flow Control: Req 랑 같은 사이클에 Ack가 켜진다. Ack가 1사이클 일찍 켜진다고 해서 credit이라는 용어를 씀.

    데이터를 받을 공간이 미리 확보가 되어있으면 Ack=1, 안되어있으면 Ack=0

### Burst & Split transaction to overlap request and data transfer
원래는 캐시미스가 일어나면 패널티가 크다. 캐시미스가 전체 실행흐름을 막을 수 있다.

근데 요즘은 MSHR(miss state handling register)라는게 있어서 캐시 미스가 있더라도, 캐시 미스 일어난 데이터만 늦게 응답하게 하고, 캐시 히트한 데이터는 빠르게 빠르게 응답하도록 해준다. 캐시미스가 실행 전체를 막지 않는다. "hit under miss" 허용

작은 데이터가 필요해 캐시블락 하나를 통째로 읽는걸 Burst라고 한다.

One Address for Burst: Separation of address and data channel

- Master provides the start address of burst
- Slave needs to generate the remaining addresses based on burst type (FIXED, INCR, WRAP)

캐시 미스 상황에서, CPU는 보통 캐시라인 데이터 전체가 필요하지 않다. Line fill buffer에 캐시 데이터가 조금씩 조금씩 채워질 때, CPU가 필요로 하는 부분이 채워지면 캐시는 이를 CPU에 즉시 알린다.

### Multiple outstanding requests
"hit under multiple miss", "miss under miss"를 허용하면 성능을 더 끌어올릴 수 있음. 캐시미스가 병렬로 나는것이 허용되면, 캐시미스로 기다리는 시간을 줄일 수 있음. 대신 Bus가 이걸 지원할 수 있도록 고쳐져야함.

AXI는 이걸 지원한다. (PPT 55장 참고) 

### Implementation issue: connectivity and arbitration
Bus를 구현해보자. 여러 다양한 구현을 하나의 AXI 프로토콜로 통일시켜야하는데, 이게 쉽지 않다.

모든 master와 slave 조합이 다 연결되어있는건 아니고 (not a full cross-bar) 필요한애들끼리만 연결되어있다. 이러면 회로 절약 가능

decoder와 arbiter에 붙어있는 demux와 mux를 많이 써서 구현한다.

Arbitration problem: "한 slave에 여러 마스터로부터 입력이 들어오는데, 이중에 뭘 slave한테 보내야하지?" 문제를 일컫는 말. 이를 푸는 arbitration scheme에 여러개가 존재한다

Arbitration scheme - fixed priority: 여러 마스터에 고정된 우선순위들을 부여한다. 우선순위 높은 데이터를 우선한다. 단순하고 좋긴 하지만 starvation 문제가 가능하다. 높은 우선순위의 마스터가 데이터를 안끊고 계속 보내면 낮은 우선순위의 마스터는 데이터를 전혀 보낼수가 없음

Arbitration scheme - round robin: 여러 master들에 fair하게 자원을 할당함. 일단 fixed priority를 주되, 현재 stage에서 어떤 master로부터 데이터를 받을지(active master)가 계속 변함. 한 stage에서 win 한 master는, 다음 stage에서 우선순위 높은애한테 active를 넘겨줌

Arbitration scheme - hybrid: fixed priority랑 round robin 섞기

Arbitration scheme - LRG(Least recently granted): 마스터를 여러 그룹으로 나눠, 각 그룹 내에서 grant 안된지 제일 오래된 애들이 가장 높은 우선순위를 가짐.

AXI가 LRG를 쓴다. ARM 스마트폰을 비롯해 많은 애들이 LRG를 씀

&nbsp;

Week 10, Tue, Lab
========
지난 실습에선 Zync에 PS+BRAM만 했다면, 이번엔 PS+BRAM에 Custom IP를 올린다.

### Term Project v0
구현했던 V×V 곱셈기를, PE Array를 써서 M×V로 확장하세요.

- Term Project v0 중간제출: 6월 2일
- Term Project v0 최종제출: 6월 16일
- Advanced Project 제출: 6월 23~30일

Term Project v0 중간제출은 속도를 안보지만, 최종제출은 속도를 본다. Advanced Project도 혼자 하게될것이다.

&nbsp;

Week 11, Tue
========
- 기말고사: 2020-06-09
- eTL에 2017년과 2019년의 중간고사, 기말고사 기출문제가 올라간다.

6월 16일에 이론수업은 없으나 실습은 한다.

## Low Precision Computation on Neural Networks
소수점 정밀도를 낮춰, 더 빠르게 계산할 수 있다.

소수점 정밀도를 낮추면, 같은 비용으로 계산을 몇회 더 할 수 있기때문에, 실리콘 면적을 더 유틸라이즈 할 수 있다.

### Floating point representations
- float32
- float16
- bfloat16: Brain floating point format
  - Mantissa가 적어 정밀도는 떨어지지만, 표현가능한 범위는 더 넓다. bloat16과 float32 둘다 8bit exponent를 씀
- int8
  - 극단적으로 낮은 정밀도와 표현범위
  - 그런데.. 최근에 int8로도 추론에 충분하다는게 밝혀지고있음.

### Quantization
- No saturation: |max| 이상을 127로 매핑한다면, Rounding error로 인해 Significant accuracy loss가 발생해 뉴럴넷 퀄리티가 망한다
- Saturation: 하지만 |threshold| 이상을 모두 127로 saturate시키면 정확도를 올릴 수 있다.

그럼 이제 어느 |threshold|가 적당하냐? 이것이 이슈가 됨.

### SIMD or Vector (Addition)
int8 유행이 커지고있음. NVIDIA P40, P4 모두 INT8 을 지원함.

Nvidia V100의 다음버전인 A100 에선, FP32 FP16 말고도 TF32, BF16, INT8, INT4, BINARY 등 다양한 형식의 SIMD를 지원한다.

## How to Quantization
### Google's INT8 quantization
(Quantization and Training of Neural Networks for Efficient Integer-Arithmetic-Only Inference, CVPR 2018)

목표: INT8 SIMD 연산만 써서 뉴럴넷을 만들어보자.

(PPT 참고) 뉴럴넷에 쓰이는 숫자 범위가 있을텐데, 중간값을 새로운 0으로 잡고, 적당히 위 아래 max를 찾으면 된다. 근데 어느 중간값과 어느 스레숄드가 제일 적절한지 어떻게 알까? 퀀타이제이션을 적용한것과 안한것을 비교한다.

레이어별로 각각 다른 Z, S 값을 써야한다. 보통은 [-128, 128) 혹은 [0, 256) 둘 중 하나로 퀀타이제이션 한다. 그 이외의 더 나은 Z S 값을 찾을수도 있지만, 여러 뉴럴넷에 제너럴하게 적용하기 힘들기 때문에 안한다.

### NVIDIA's INT8 quantization
8-bit Inference with TensorRT

특정 스레숄드 값 이상을 saturate해버리면 되는데, saturate 시킬 스레숄드를 어떻게 찾으면 될까?

(PPT의 Migacz, 2017 참고)

NVIDIA TensorRT에선, Truncate하면서 읽어버리는 정보에 집중을 했다. 정보를 얼마나 잃어버렸는지를 측정하는 메트릭으로 KL divergence을 사용했다.

KL divergence는 원래 분포 대신 새 분포를 썼을때 얼마만큼의 정보가 손실되는지를 알려주는 척도이다. (수식은 PPT 참고) 분포가 유사할수록 KL divergence값이 작다.

KL divergence 값이 충분히 작아지도록 잘 잘랐더니, FP32로 계산하던걸 INT8로 계산해도 아주 작은 성능손실만이 존재했다.

KL divergence는 적분을 실제로 하진 않고 근사한다. 그리고 해보기도 전에 모든 데이터를 넣어볼 수는 없으니, 갖고있는 테스트 데이터를 넣어서 학습시킨뒤 거기에 KL divergence를 적용시켜 계산한다.

### Logarithm-based quantization
Convolutional Neural Networks using Logarithmic Data Representation, CVPR 2017

0에 가까운 값일수록 값들이 더 촘촘하게 모여있고, 0에서 먼 값일수록 값들이 멀리 떨어져있다. 0에 근접할수록 더 촘촘해지는 방식의 quantization이 필요하다.

그리고 *2, /2 연산은 시프트연산으로 구현이 가능하다는 성질을 활용할 수도 있다.

로그베이스 퀀타이제이션을 하면, 0에서 먼 값에 대해선 라운딩 에러가 몹시 커진다. 그러나 로그베이스 퀀타이제이션을 적용한채로 트레이닝을 다시 시켜서 라운딩 에러를 극복할수도 있다. 극복 못한다면 비트를 더 많이 써야함.

이거로 하는거랑 리니어하게 int8로 바꾸는거랑 결과가 비슷할 수 있는데, 이거는 곱셈을 시프트연산으로 바꾼다는 장점이 있다.

### Binary-weight neural network
XNOR-Net: ImageNet Classification Using Binary Convolutional Neural Networks

Quantization의 아주 극한 형태. 각 데이터에 1bit만 존재함.

Binary weight: 웨이트가 무조건 1 아니면 -1 임. AlexNet에선, 정말 충격적이게도 binary weight를 써도 정확도가 그렇게 나빠지지 않는다.

얘도 다른 퀀타이제이션이랑 마찬가지로, 퀀타이제이션을 적용시킨 뒤 라운딩 에러를 극복하기 위한 학습을 다시 시켜줘야한다.

Binary-weight가 아니라 XNOR-network(All binary solution)은 정확도 로스가 좀 더 있다.

&nbsp;

Week 11, Tue, Lab
========
IP on Board & Quantization

- V0: 2020-06-16 까지
- V1: 2020-06-23 까지

### V0: 우리가 만든 IP를 어떻게 Board에서 실행하는지
시뮬레이션에선 잘 되는데, 하드웨어에 올렸더니 실패할 수 있다. 이걸 검증하는 방법을 알아보자.

(PPT 참고)

CPU와 FPGA의 연산결과를 비교하면 된다. 약간의 계산오차가 발생할 수 있는데, 둘의 값이 미세하게 다를 수 있다. 이는 수용 가능함.

값이 많이 다르다면? IP에 문제가 있다는 뜻임.

### V0: 컨벌루전 로워링을 FPGA에서 하는방법
(PPT 참고)

### V1: 퀀타이제이션 하는법
32bit 있던걸 타일링해서 8bit로 나눠 계산하면 된다. FP32 모듈도 모두 없애버리고 INT8 모듈로 바꿔야한다.

V1은 optional 프로젝트다.

V2가 예정되어있음.

&nbsp;

Week 12, Tue
========
> 2020-06-02

Optimizing Neural Networks: Software/Hardware Co-Design for Zero Skipping

머신러닝 엔지니어들은 Weight pruning이라는걸 한다. 대부분의 가중치들이 0에 가까운 값이 되어버리기 때문이다. 우리는 이런 0 weight들에 대해 계산을 생략하는 테크닉에 대해 배울것이다.

소프트웨어와 하드웨어 양쪽의 협력이 필요하다. 소프트웨어 단에서는 weight pruning을 해서 일정 weight들을 0으로 만들어야하고, 하드웨어 단에선 그런 0들에 대해 계산을 생략해야한다.

### Zero Skipping in production
Zero Skipping은 Sparse matrix 곱을 효율적으로 줄여주는 아주 강력한 테크닉이다. 갤럭시 S10에는 이미 zero skipping을 지원하는 하드웨어 가속기가 탑재되어있다. NVIDIA A100에도 zero skipping이 들어갔다. 

### Weight pruning: Why
실제 사람 뇌도 시간이 지나면 자원 효율성을 위해 잘 안쓰는 시냅스는 prune된다. 뉴럴넷에도 적용 가능하다.

Pruning CNN: NIPS 2015. Weight가 아주 작은 간선은 prune해버려서, 더 나은 효율성을 얻을 수 있다. 안쓰는 간선과 뉴런을 prune해버리고 나면 sparse network가 결과로 나온다. 0 weight에 대해선 결과가 0이라는걸 이미 알고있으므로, 계산을 아예 할 필요가 없다. 이렇게 계산하면 성능면에서 이득을 볼 수 있음

CPU가 하는 연산중 제일 자원을 많이 소모하는 연산은 DRAM Access이다. (수업 PPT 참고) 32-bit DRAM Memory Access에는 640pJ 소모, 32-bit int ADD에는 0.1pJ 소모. 6400배 차이난다. 에너지 소모는 행렬곱이 아니라 메모리 액세스에서 일어난다는것을 기억해야한다.

메모리 액세스를 줄이려면 메모리에 애초에 데이터를 적게 담아야한다. 이 때, sparse 행렬곱의 경우, 0을 일일이 메모리에 담지 말고, 0이 메모리 상 어느 위치에 있었는지 인덱스만 기록해주면 메모리 액세스를 훨씬 줄일 수 있다.

Weight pruning이 파워풀한 솔루션인것은 계산을 줄일 뿐 아니라, DRAM 액세스를 줄여주기 때문이다!

### Weight pruning: How
얼마나 작은 weight를 prune 할까?

(PPT 참고) prune한다는것은, weight들의 분포를 이렇게 그렸을때, 0에 가까운 이 값들을 모두 0으로 간주하겠다는 것이다. 이 값을 0으로 바꾼 뒤, 추가적인 트레이닝을 해줘야한다.

우리가 아주 작은 값들을 prune하긴 했지만, 아무튼 0이 아니었으니 output에 기여를 하고있었을 것이기 때문에, 정확도 손실이 발생했을 수 있다. 그래서 남아있는 non-zero weight를 가지고 추가적인 훈련을 시켜야 한다.

weight pruning을 적용시킨채로 트레이닝을 다시 하면 봉우리가 두개 있는 분포가 나오고, 이건 정상이다. 추가 트레이닝으로 원래의 정확도를 다시 얻었다고 가정해보자. 이경우, pruning process를 멈추지 않고, pruning iteration을 한번 더 돌린다. 정확도 손실이 발생하지 않는 한, prune과 재훈련을 반복해도 된다.

이것이 기본적인 pruning 테크닉이고, 매우 직관적이고 잘 동작한다. 여기에 추가적인 메모리 최적화를 적용시킬 수 있다.

### Weight Clustering
비슷한 값의 weight를 갖는 간선들을 모두 cluster시켜버린다. 이러면 행렬에 weight를 일일이 쓰는 대신 cluster의 index만 기록하고, 각 cluster의 centroid를 따로 저장하면 되기때문에 메모리 사용량이 훨씬 줄어들음. 저장은 이렇게 하고, 계산하기 직전에만 각 index에 맞는 value를 써서 계산하면 된다.

그리고 특정 cluster에 값이 많이 들어있다면, 자주 등장하는 문자열을 짧은 압축문으로 바꿔주는 허프만 인코딩 기술을 사용해, cluster index를 더더욱 압축시킬 수 있다.

### Pruning + Quantization + Compression: ICLR 2016
- Pruning을 통해 정확도를 유지하며 9~13배 크기 감소
- Quantization을 통해 정확도 유지하며 27~31배 크기 감소
- Huffman Coding을 통해 정확도 유지하며 35~49배 크기 감소

AlexNet같은애들에도 Huffman Coding 적용시켰더니 크기가 35배 이렇게 줄더라. 레이어별로 따로 압축을 적용시켜본 결과, CONV 레이어는 웨이트당 ~2.5bit, FC(fully connected) 레이어는 웨이트당 ~3.5bit으로 줄었다.

### Per-Layer Sensitivity
Pruning 하는 양에 따라 accuracy loss가 얼마나 생기는지 비교 (PPT 참고)

CONV1(입력 근처)가 제일 sensitive했고, FC(출력 근처)가 제일 less sensitive 헀다. General하게, 입력에서 멀어질수록 sensitivity가 감소하는 현상이 관찰된다.

또한, CONV 레이어보다 FC 레이어가 최적화에 따른 정확도 감소가 적은데, 이 역시 general하게 관찰되는 현상이다. 이유는 단순한데, FC 레이어가 갖는 웨이트 수가 CONV 레이어보다 훨씬 많기때문이다.

### Parallel Computing of convolution
지금까지는 소프트웨어 단에서 트레이닝할 때 적용시키는 최적화에 대해 알아봤는데, 이제 하드웨어단에서 적용하는 최적화에 대해 알아보자.

2D 컨벌루전 계산을 하는 상황이라고 가정해보자. MAC Unit은 8개뿐인데, 커널이 3*3 크기다. 어떻게 하면 좋을까?

1 clock cycle: 커널 좌상단의 맨 처음 kernel weight를 읽어서, 8개의 MAC Unit에 broadcast한다. 각 MAC Unit에겐 weight와 input activation이 필요한데, 각 MAC Unit은 feature map으로부터 자기 자신의 input activation을 읽는다.

각 MAC Unit은 그에 맞는 Output 뉴론과 컨벌루전 윈도우를 갖고있다. 다음 MAC Unit은 다음번 Output 뉴론과 다음 컨벌루전 윈도우를 담당. 그 다음 MAC이 각자 자신의 input activation과 broadcast weight를 곱한다. 이러면 맨 첫 곱셈 한거임.

2 clock cycle: 커널의 다음 weight를 broadcast한다음에 같은 계산을 반복함. MAC이므로 이전 사이클에서 했던 결과에 더해져서 나옴

이걸 커널의 모든 weight에 대해 반복하면 convolution이 나온다.

그러니까 걍 convolution이랑 계산 하는 횟수가 같은데, 순서만 다르게 한것임. 이렇게 하면 kernel의 weight 수보다 적은 MAC을 갖고있어도, 다양한 크기의 입력에 대응되는 convolution 계산기를 만들 수 있음.

8개의 MAC Unit을 써서 8개의 곱셈과 덧셈을 병렬로 수행했다. 근데 MAC Unit이 더 많을때엔 더 많은 MAC Unit을 어떻게 활용할 수 있을까? 3D Convolution일 경우, 훨씬 많은 MAC을 계산에 쓸 수 있다. 이걸 하는 이유는 삼성의 Zero-skipping convolution 계산기 원리를 이해하기 위해서다.

### Zero-Skipping in SAMSUNG
ISSCC 2019, An 11.5 TOPS/W 1024-MAC Butterfly-Structure Dual-Core Sparsity-Aware Neural Processing Unit in 8nm Flagship Mobile SoC

https://doi.org/10.1109/ISSCC.2019.8662476

일단 3D Convolution 연산을 2D Convolution 연산으로 나눴다.

만약 커널의 특정 weight가 0이라는걸 안다면, 그 커널의 weight를 MAC에 broadcast할 필요도 없고, MAC이 feature map으로부터 데이터를 읽어 곱셈을 할 필요도 없다. MAC 유닛이어서, 그냥 그 weight를 스킵해버려도 맞는 답이 나온다. 그렇게 skip해서 확보한 시간을 그냥 놀지말고, 다음 non-zero weight 계산을 빠르게 시작하는데 써야한다.

(PPT 34페이지) weight의 일부가 0이라는것을 미리 알 경우, 더 작은 clock cycle로 계산이 끝난것을 볼 수 있다. zero를 skip한것임.

이걸 실제로 구현하려고 해보면 훨씬 복잡하다. 그러나 동작원리 자체는 이해하기 쉽다.

Zero-skipping의 효과를 측정해봤는데, Zero-Weight의 비율이 높을수록 성능 향상이 컸고, kernel의 크기가 클수록 성능 향상이 컸다.

### Network Traversal: Feature-Map Forwarding
삼성 논문에선 이거 말고도 추가적인 최적화 아이디어를 제시했다. 보통 이런 특수한 연산 가속기는 제한된 양의 메모리를 갖고있기때문에, 더 큰 데이터를 사용하려면 반드시 메인 메모리 액세스가 필요하다. 하지만 앞서 보았듯이 메인메모리 액세스는 성능면에서도 나쁘고 에너지면에서도 나쁘다. 심성은 이 메모리 액세스양을 줄이는 방법을 제시했다. FC 레이어에선 이 아이디어를 쓸 수 없으나, CNN에선 가능하다.

Convolution 연산을 할 때, 모든 입력 데이터를 한번에 읽을 필요가 없다. 입력 데이터의 일부만으로 충분함. 그리고 한 레이어에서의 평가가 끝났을 때, 계산 결과를 DRAM에 저장하지 말고 바로 다음 레이어로 넘겨주면 DRAM 액세스 수를 줄일 수 있다.

### Zero Skipping in NVIDIA A100
A100의 경우, Weight pruning이 "2:4 rule" 규칙에 따라 이뤄졌다고 가정한다. (PPT 참고) 행렬이 네칸씩 나뉘어서, 각 네칸마다 두개의 셀은 prune되고, 나머지 두 셀은 prune 안된것을 볼 수 있다. Prune을 이렇게 하면 NVIDIA A100의 Zero-Skipping 기능을 쓸 수 있다. 

0이 포함되어있던 큰 Weight 행렬을 non-zero 값만 모아 들어있는 non-zero data와 non-zero 값이 어느 index에 위치했었는지 알려주는 non-zero-indices로 변환한다. 이렇게 만들면 행렬곱 하기 곤란할 것 같지만, non-zero indices를 select로 갖는 mux를 적절히 활용해 행렬곱의 `x*0` 항을 계산하지 않도록 조작해주면 된다.

이제 문제는 "2:4 rule"을 어떻게 지키는지이다. Pruning을 막 하는게 아니라 규칙에 맞춰서 해야하는데, 어떻게 할까? 작은 값을 가진것을 prune 한다는 아이디어는 같은데, 이것을 행렬의 칼럼 전체와 같이 좀더 큰 범위에 대해 수행하면 된다. nvidia에서도 pruning하는데에 적합한 알고리즘을 패키지로 제공할것이다.

### HW Accelerator 요약
현재 마켓에 있는 상업용 액셀러레이터는 이러하다

1.  Systolic Array: Google TPU, Tesla
    - Good data reuse
    - Zero skipping 못함. zero-skipping systolic array 프로포절도 있는데 오버헤드가 있음
2.  Direct convolution: Samsung
    - Zero skipping 있음
    - Wiring이 복잡함
3.  Dot-product engine: NVIDIA, Microsoft
    - Zero skipping 있음
    - Wiring이 복잡함

### Zero skipping 구현
Matrix*Vector 곱셈기에서 Vector 부분을 보고 0이 있는지 검사하고, 0이 있으면 건너뛴다.

Zero skipping 하는동안 데이터 트랜스퍼를 안할 수 있으므로 클럭이 아껴진다. 그러나 compression/decompression 구현을 해야해서 어려워진다. 쉬운 방법은 zero skipping을 compution 부분에서 구현하는것이다.

vector가 0이면 그 vector는 broadcast 안해도 되어서, computation부분에서 zero-skipping을 구현해도 클락사이클 절약이 존재한다. 작년에는 이걸 구현하는 실습을 했는데 올해는 안했다. Layerwise acceleration 효과가 훨씬 커서.

### Q&A
01:45 질문:
re-training을 무한정 계속하면 pruning하기 전의 상태로 돌아가나요? 그러면
re-training을 정확히 어느 시점에 끝낼지는 경험적으로 정하는 건가요?

02:00 질문:
현재 슬라이드를 보면 8개에서 4개만 선택해서 계산을하는데 8개 모두 0에서 멀어서
의미있는 weight면 정확도에서 손실이 크지 않나요?

02:06 질문:
교수님 삼성이 16개의 MAC을 쓴다고 하셨는데 그러면 layer output의 size가 항상 4*4
여야 하는건가요?

&nbsp;

Week 12, Tue, Lab
========
https://github.com/tahsd/hsd20_lab12_quantization

- Q: 교수님께서 말씀하신, 기말고사 중 project에서 3문제 나온다는 것에는 v1, v2는 포함되지 않는 건가요?
- A: 당연히 포함 됩니다.

- Q: 조교님, v0를 구현했는데 cpu로 구동하는 것보다 fpga에서 하는 게 더 느린 것이 정상인가요?
- A: 네, 아까 말씀드렸듯이 cpu는 여러 memory optimization 테크닉, calculation 테크닉들이 적용이 되어있는데 우리 fpga는 간단하게 구현한 형태여서 더 느린것이 맞습니다.

- Q: lab10이 revised됐는데, revised 된 부분중 clk generator에 대한 부분이 있는데 그 페이지에 적혀있는 clk generator는 lab10의 shifter에서 사용된 generator와 동일한가요?
- A: 본인이 ip editor로 해당 부분 직접 확인 부탁합니다.

- Q: 랩10을 기본 설정으로 빌드해도 잘 작동하는데 그렇다면 ip custom 단계에서 별도의 포트 매핑은 해줄 필요가 없는 것이 맞나요?
- A: 동작하는 것이 확인되면 잘되는 것이 맞습니다. 다만 간혹 전부 리셋되는 경우가 있어서 해줄 필요가 있는 경우도 있습니다.(vivado 상의 이슈라서 정확한 이유는 모르겠네요)

lab 12는 과제 없음
