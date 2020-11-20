RISC-V Co-Inventor한테 듣는 RISC-V 탄생의 비화, 현재, 그리고 미래
========

발표자      | 이윤섭 (Yunsup Lee) 박사 
------------|----------
발표자 소속 | SiFive, Inc.
날짜        | 11/20(금), 2020
시간        | 02:00PM - 03:00PM
장소        | Online seminar using Zoom
호스트      | 김진수 (x7302)

### 발표내용
RISC-V is a free and open instruction set architecture that has rapidly grown
across various applications over the past years.  RISC-V started at UC Berkeley
in 2010 (link to history) as a computer architecture research project, and in
2020, RISC-V has just hit its 10th year anniversary.  In this talk, we will look
back 10 years on RISC-V's past and present -- also talk about some fun stories
along the journey -- and discuss where RISC-V is headed in the next 10 years.

### 발표자 소개
Yunsup Lee is SiFive's Chief Technology Officer and co-founder. Yunsup received
his PhD from UC Berkeley, where he co-designed the RISC‑V ISA and the first
RISC-V microprocessors with Andrew Waterman, and led the development of the
Hwacha decoupled vector-fetch extension. Yunsup chairs the RISC-V technical
steering committee.  Yunsup also holds an MS in Computer Science from UC
Berkeley and a BS in Computer Science and Electrical Engineering from the Korea
Advanced Institute of Science and Technology (KAIST).

&nbsp;

필기
--------

SiFive, 이윤섭 CTO

김진수: 큰 기여 많이 하심. 내 OS 수업 A+ 받으셨음.

다른데에서 안하는 RISC-V에 대한 이야기를 해보자

만든지 5년 됨. 회사가 300개정도

- 2001-2004: KAIST
- 2005-2007: PIOLINK
- 2008-2016: UC Berkeley
- 2011-2014: NVIDIA
- 2015-now: SiFive

2000년대에 i386 위에서 파스칼 프로그래밍을 시작했다. 정보 경시대회, 계절학교를 나감.

2008: "What is the difference between a flop and a latch?" 대답을 못했다..
교수님이 당황 안하시고 차근차근 설명을 하셨다. CPU 설계를 배우고싶어서 버클리에
왔는데 큰일났다고 생각함.

2008: Helped build a SPARCv8 machine on an FPGA. 리눅스가 안켜져서 1주 가까이
디버깅을 했었는데.. Sun이 SPARC를 냈을때 MMU에 버그가 있어서 리눅스가 그 버그를
회피하는 코드를 커널에 넣어둔거였다. 그래서 남이 만든 버그를 그대로 재현했더니
커널이 돌아갔다. 그러지 말고 MIPS를 써볼까? 하면서 만들어봄.

2009: Built a 32-bit Simple MIPS machine.
<https://inst.eecs.berkeley.edu/~cs250/fa09/> 조교함, 교수님이 버클리로 온지
2년밖에 안되어서 인프라가 없었다. 직접 이것저것 깔면서 맨땅에 헤딩함.

CAD도 전혀 몰랐지만 1년 반동안 파면서 열심히 함. 수업 프로젝트로 MIPS 벡터
머신을 만듦.

2010: Upgraded 32-bit MIPS to 64-bit RISC-V
<https://inst.eecs.berkeley.edu/~cs250/fa09/>
어차피 컴파일러고 뭐고 모조리 다 다시짤거면 왜 MIPS를 쓰지 싶어서 이렇게 함.
조교를 한번 더 하면서, 랩을 RISC-V로 다 고침.

2010년도에 누가 ISA를 새로 만들어서, 그것의 임팩트가 대체 뭐냐? 근데 대학원생이
하고자 하면 교수는 못말린다. 2-3년동안 꿍시렁 꿍시렁하면서 도와주셨다.

2010: Build First Full RISC-V CPU, named it Trainwreck
<https://github.com/aswaterman/trainwreck>
이때까지한 해도 Verilog로 짰음

2011: First Trainwreck tapeout on ST 28nm FDSOI
처음 만들어보는 칩. 문제가 좀 있었다. 나중에 알고보니, verilog의 input 포트랑
output 포트를 잘못연결해서 합성을 잘못했다.

Verilog가 정말 후지구나 이렇게 느꼈다. 그 전부터도 안좋아했지만 여기서 진짜
안좋아함. 앤드류랑 이것저것 대안을 찾다가..

2012: Verilog is a terrible language, think like a computer scientist!
Chisel을 쓰기 시작했음.

2012: Built better RISC-V CPU in Chisel, named in Rocket

2012: First working RISC-V chip tapeout on IBM 45nm SOI

위키피디아에 가면 제가 손으로 들고있는 EOS14 칩 사진이 나온다. 이 사진이
어쩌다가 인터넷으로 흘러갔는지는 불명.

첫번째 칩보단 훨씬 동작을 잘했다. 첫번째에서 잘못한것도 보완 많이 했고, 등.
내공이 좀 올라왔다. 근데 테스트해보니까 가끔 죽는다. 보스턴까지 비행기타고 가서
3일 밤새고 오실로스코프로 찍어보면서 버그를 찾았는데, 클락이 순간적으로 0으로
떨어지는 버그가 있었다. 너무 많은 핀이 동시에 1로 올라갈때 전압이 떨어지는
버그였음. 디커플링 캡이 CPU 근처에 있어야했는데 멀리 떨어트려놓은거였다.
인더스트리에선 굉장히 유명한 문제인데 우린 안해봐서 모르는 거였다.

보드를 새로 만들어야하는데 랩에 돈도 없고.. 보드를 최대한 싸게 새로 만드는
방법을 고민했는데, 실크스크린에 납을 묻혀서 집에있는 토스터오븐을 써서 리플로우
납떔을 하며 보드를 직접 만드는 상황이 되었다. 이번에는 디커플링 캡이 CPU 바로
밑에 있다. 지금 돌이켜보면 추억임

두개정도 이렇게 망하고 힘들게 하다보니, 랩에 있는 사람들도 내공을 쌓아
안정적으로 굉장히 많은 칩을 냄. IBM 45nm, ST 28nm FDOI, TSMC 28nm and 16nm FF,
등. 데모도 점점 간소화해서 이더넷 통신 켜고, 파워서플라이 하나만 들고다니면 되게
만듦.

2013: RISC-V Debut on riscv.eecs.berkeley.edu (지금은 안되는 웹페이지)

누가 쓰는거 없는줄 알고 ISA를 계속 바꾸고 있었는데, 이메일이 왔다. 내가 이걸
쓰고싶은데 그만좀 바꾸라고. 그래서 "아 사람들이 FOSS ISA에 관심이 있을수도
있겠다"라는 생각을 했다.

2014: RISC-V Debut at HotChips conference

부랴부랴 99designs 웹페이지에 500USD를 주고 RISC-V 로고를 만듦. 그리고 티셔츠도
만들어서 단체로 셔츠를 입고다녔고, 세간의 이목을 집중받음.

<https://99designs.com/logo-design/contests/create-logo-high-profile-open-source-microprocessor-platform-401473>

2015: RISC-V 파운데이션, SiFive 창설

2016: RISC-V Textbooks. 컴퓨터 구조 수업을 RISC-V로 꼭 바꿔야한다고 생각을 했다.
그래야 RISC-V가 잘되니까. 그래서 여기저기 컴퓨터 수업 교과서를 바꾸자고 이야기를
하고다녔는데, 데이브가 "나는 커머셜한 ISA 아니면 안된다"고 잘라말하더라구요.
그래서 SiFive 창업한 뒤엔 이제 되나? 라고 생각했더니 데이브가 먼저 연락해서
"RISC-V로 바꾸고 싶은데 난 시간이 없으니 너네가 바꿔보는거 어때" 래서 RISC-V로
앤드류랑 밤새면서 고쳤다.

김진수 교수님이 여기저기에다가 왜 RISC-V를 안쓰고 다른걸 쓰냐 고 물어봐주셔야
한다.

2016: SiFive builds first commercial RISC-V chip, ships HiFive1

사람들이 대만으로 가서 hand-carry를 하면 빨리 가져올 수 있다고 해서 내가 직접
대만에서 들고왔다. 웨이퍼를 받으려고 대만까지 갔는데, 이 웨이퍼를 짐으로
실을수가 없어서.. 티켓 하나 더 가서 비행기에 앉혀서 갔다.

근데 알고보니 hand-carry를 직접 하라는게 아니라 이걸 하는 회사가 있더라구요.
그것도 모르고 직접 했던 기억이 있다. 소프트웨어 에코시스템도 많이 만들고..
이것저것 많이 했다.

Embedded RTOS & Tools for RISC-V. "야 RISC-V 그거 안돼." "그런가요" "RISC-V 그거
T32는 되냐?" "T32가 먼가요" 이러니까 더 질문을 안하셨어요

2018: RISC-V 새 개발보드

Apps & Linux for RISC-V. 각종 배포판, 각종 소프트웨어들, 러스트 컴파일러, 등
다양한 소프트웨어들 포팅 많이 됨.

SiFive HiFive Unmatched. PCIe Zen3도 넣고 등등.

오늘 런칭한 프로덕트가 있다.

2020: HiFive Inventor launched Today!

어린 친구들이 코딩에 입문할 수 있게.. BBC에서 공익 차원에서 ARM이랑 같이 만들던
BBC 마이크로비전과 호환되게 만듦. BBC의 닥터후를 전면으로 내세워서 닥터후가
프로그래밍을 어린 친구들에게 가르치는 프로젝트를 오늘 런칭을 했다.

2021 and beyond: 세가지는 꼭 하고싶다. Deep Learning, 5G, IoT.

RISC-V가 좀더 숙성이 되면, 스마트폰이나 PC 랩톱 데이터센터에도 넣을 수
있을것같다. 저는 사실 되냐 안되냐 의 문제는 아니고 언제 되냐의 문제같다.
소프트웨어 ecosystem이 얼마나 빨리 진행이 되느냐의 문제같음. 모든 컴퓨터
device가 RISC-V로 동작하는 시대가 오지 않을까 싶다.

리눅스가 맨 처음 나왔을때 사람들이 저게 되냐 라고 했지만 결국 이제 다른 OS는 다
사장되지 않았는가? FOSS의 힘은 강력하다. ISA가 여전히 propriorty인것은 말이
안된다. 아주 장기적으로 보면 다 이 방향으로 갈것.

한국에 semi-five라는 합작으로 만든 회사가 있는데, 인턴십이 꽤 많다. 관심 있으면
지원해보세용.

- Q: 혹시 CPU말고 GPU쪽으로도 이런 open-source 프로젝트가 있나요?
- GPU쪽에 한두개 있는데 RISC-V만큼 커뮤니티가 활발한 플젝은 없다. RISC-V 기반
    GPU는 더러 있긴 함. 이매지네이션 GPU도 RISC-V 기반.
- Q: ARM에서 견제(?)를 받았다는 기사를 봤는데 어떻게 대처하셨나요?
- RISC-V가 여기까지 올 수 있었던건, 소프트뱅크가 ARM을 인수해서다. 그거때문에
    사람들이 RISC-V를 더 찾고있다. 앞서가는 사람은 절대 뒷사람을 인정하지 않고
    이야기도 안하고, 뒤에서 따라가는 사람은 앞사람이랑 열심히 비교를 하는게
    마케팅의 정석. ARM이 RISC-V에 대해 이야기를 안하다가 한번 RISC-V를 대놓고
    디스하는 웹사이트를 만든적이 있었다. ARM이 RISC-V를 인정하게된 포인트라고
    본다. ARM이 RISC-V를 견제하냐 안하냐라고 물으면 전 항상 견제한다고 대답함.
    힘든 싸움이긴 한데 큰 그림을 보면 결국 RISC-V로 가는 방향이 맞기때문에..
    결국엔 RISC-V로 에코시스템이 넘어올거라고 본다.
- Q: ARM이랑 RISC-V를 비교했을때에, 비슷하게 느껴졌었다. 머가 주로 다른지?
- ISA만 보면 큰 차이 없다고봄. ISA에 락인이 되냐 안되냐의 차이지. ARM이랑
    RISC-V랑 자세히 들여다보면 몇가지 장단점이 있다. ARM은 AArch64로 오면서
    없앤 인스트럭션이 좀 있는데, RISC-V는 다름, 굉장히 마이너한 디테일이긴
    한데.. ARM은 분기 명령어가 둘로 나뉘어져있지만 RISC-V는 MIPS 비슷하게
    compare - branch가 한 명령어. 통계적으로 분기 명령어가 6개마다 1개씩 있다고
    하는데, ARM은 그점에서 약간 불리한것.
- Q: 가장 먼저 상용화될 것 같은 분야 (임베디드, 모바일, 랩탑, 서버 등)가
    있을까요? 있다면 risc v의 어떤 특징이 상용화에 도움이 될까요?
- 좋은 질문, 맨날 이거 고민한다. 일단 임베디드에는 안착한것같다. 임베디드가
    소프트웨어 에코시스템에 영향을 제일 덜 받아서 여기로 먼저 슥 들어갔음. 이제
    싸우고있는 변수는 모바일, 랩탑, 서버.
- Q: 이번에 애플 실리콘이 발표되면서 x86 기반 프로그램들을 돌릴 수 있도록
    로제타를 사용하게 되는데, RISC-V에도 비슷한게 있나요?
- qemu가 있어서 이런게 있긴 한다. 로제타처럼 모든 프로그램을 다 돌릴 수 있는
    바이너리 트랜슬레이터는 아직 없다. 소프트웨어 에코시스템이 하루만에
    만들어진게 아니어서..
- Q: ISA에 명령어를 할당할 때 제한된 개수의 명령어만 넣을 수 있을텐데, 어떤
    명령어를 선택할지는 어떤 기준으로 정해지는 건가요? 예를 들어서, 레지스터 두
    개를 비교하여 분기하거나 immediate value와 비교하여 레지스터에 1 또는 0을
    set하는 명령어는 있는데 immediae value와 비교하여 분기하는 명령어는 없던 것
    같더라고요(if a>3과 같이 나름 자주 사용된다고 생각됨에도 불구하고) 이런
    tradeoff를 결정하는 기준이 있나요?
- 아주 좋은 질문. 덜어내는게 훨씬 어렵고, 더 넣는게 훨씬 쉽다. 메뉴얼을 보면
    "어떤 명령어를 왜 안넣었는지"에 대한 설명이 엄청 길다. 예를들어 지금
    RISC-V는 conditional move, zero extend 이런거 다 없다.
- Q: 대학원생때 처음 이걸 하셨다고 한다. 저도 대학원생인데.. 정말 정립되어있는
    분야를 처음부터 밑바닥부터 다시하면서 논문을 쓸 수 있을까 졸업할 수 있을까
    이런 걱정은 안하셨는지
- 저는 대학원 갈때부터 CPU를 만들고싶었다. 이런거 바닥부터 하다보니까 중간중간
    파인딩이 나오면서 논문 쓸 거리가 생겼다. 생각을 하고 RISC-V를 만들기
    시작하고 그런건 아니었다
- Q: 기존의 open ISA와 비교해 RISC-V가 갖는 장점이 무엇인지 궁금합니다.
- 기존에 open ISA가 몇개 있었져. RISC-V의 장점은 인더스트리의 관심과
    에코시스템임. 많이 사용이 되어야 도움이 되는건데, RISC-V는 운 좋게
    소프트뱅크가 ARM을 사면서 여기까지 오게됨.
- Q: 제가 질문을 할건 아니고 팩트체크를 할게있어서.. 히스토리를 보면 마치 박사님
    지도교수님이 굉장항 비전과 그런 생각이 있으셔서 학생들 몇명을 데리고가서
    이걸 뭐 서머 프로젝트로 했다 그 결과가 RISC-V다 이렇게 세일즈하시더라구여.
    근데 오늘 말씀하신걸 보니 전혀 순서가 안맞는데 어케된거조? 팩트가 궁금합니다
- 아 뭐.. 제가 생각하는 이 전개과정과 교수님이 생각하는 전개과정은 다를 수
    있다고 생각하구요, 교수님이 RISC-V를 시작하자고 해서 시작한거같진 않고, 제가
    봤을때 이 2010년도에 했던 CS250에서 "우리가 하고싶은걸 했으면 좋겠다" 라고
    교수님이 했던거같기도 하다. SparcVSA하고 MIPS 하다가 왜 남이 만든걸
    해야하지? 이런 생각을 한거고..
- Q: 강의하면서 많이 받는 질문 중 하나가 "왜 굳이 little-endian"이냐.
- 좋은 질문이다. 바이엔디안이긴 한데, 왜 little-endian부터 했냐? ARM이랑 x86이
    리틀 엔디언이어서 리틀엔디안부터 했다. IP를 하다보니 빅엔디안도 많이 써서
    지금은 바이엔디안으로 둘 다 지원한다.
- Q: RISC-V를 만드시면서 많은 문제점들을 마주하시고 해결하셨을 것 같은데, 가장
    challenging 했던 부분은 무엇인가요?
- 떠오르는게 없네요. 회사차리고 투자받는거? 하드웨어 스타트업이 전무후무한 상황,
    AI가 뜨기 전이었다. 하드웨어 스타트업에 대한 VC의 관심이 없었음. 제가 딱
    "FOSS CPU를 하겠다"라고 했더니 바로 "I'm not interested"라고 하더라구요.
    그러다가 좀 실리콘밸리에서 오래하고 유서깊은 VC를 만났다. NVIDIA에도
    시리즈A에 투자했던 VC. 인프라 관련 투자를 좋아하는 VC. 칩과 프로세서를 많이
    다룬 VC여서 투자를 해주심.
- Q: 상장계획 있는지
- 상장을 했으면 좋겠는데 제가 통제할 수 있는 부분은 아닙니다. 그래서 여러분들이
    졸업하고 일하러 다니면 왜 RISC-V 안쓰냐라고 물어봐주셔야한다.
- 나: 지금 RISC-V의 adoption을 높이기 위해 소프트웨어 사이드에서 가장 필요하다고
    생각되는 액션이 무엇이신가요?
- 안드로이드 RISC-V 포팅같은게 있으면 좋을거같다. RISC-V 타겟하는 JIT 컴파일러가
    몇개 없다. 서버쪽에서 쓰는 여러 소프트웨어들이 RISC-V 타겟이 안되어있다.
- 나: 오홍 / ?!아직없나요 / 좋은 주제 주셔서 감사합니다 (?
