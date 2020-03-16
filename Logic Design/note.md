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