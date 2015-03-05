그래픽스
========

숙제는 그 날 밤 자정 12시까지

### 쳌

1.  D. Hearn and M.P. Baker, Computer Graphics with OpenGL, 3rd edition, Prentice Hall
2.  Steven Gortler, Foundations of 3D Computer Graphics, MIT Press
3.  OpenGL Programming Guide, Addison Wesley. This book is available online at
    http://fly.srk.fer.hr/~unreal/theredbook/

### Prerequisites

A good knowledge on C or C++ programming

### What is computer graphics?

좁은 정의

..

넓은 정의: Interactive Computer Graphics

-   Man-machine graphical communication
    * Ivan Sutherland's Sketchpad
-   "Interactivity" is as important as "visual output"
-   Nowadays, the term computer graphics includes almost everything on computers
    that is not text

### Sketchpad (Ivan Sutherland 1963)

*   The first program ever to utilize a complete graphical user interface using
    CRT and light pen
*   펀치카드, 배치 프로세스 시절 라이트 펜을 만들어서 그림을 그리는 시스템을
    만들었음.
*   한낱 계산기에 불과하던 컴퓨터에 Interactivity 를 부여함

### A Brief History of Computer Graphics

1885: CRT

1960: William F. Boeing coins "Computer Graphics"

1961: John Whitney, Intro to Alfred Hitchcock's Vertigo

1961: Spacewars, 1st video game, 이즈음에 삼각함수 계산이 가능한 벡스 컴퓨터들이
등장해서 비디오게임이 등장하기 시작함

1974: z-buffer, Ed Catmull, 원래 교수였다가 현재 픽사의 사장

1975: Phong shading

1980: Tron, 1st feature film by CG

Mid 1980's: GUI의 등장

1986: Luxo Jr. nominated for Oscar. 픽사 로고에 뛰는 램프가 있는 이유. 이거
만든사람 감독이 지금 디즈니 부사장 (빅히어로, 토이스토리, ...)

1995: Toy Story, 1st full CG feature film

1999: Cheap consumer 3D graphics == 그래픽카드의 등장. 이 전까지는 그래픽스
연구를 하려면 각자 자기 책상 앞에 3천만원짜리, 2억원짜리 장비를 놓아야 했음.

### What is Computer Graphics About?

*   In 1980, **Holy Grail**, Big agenda of computer graphics: Replicate the real world in computers

    = Done.

*   21세기: Visualize your imagination in computers.
*   CG = Reality + Imagination
*   근데 지금 헐리웃에 가서 특수효과팀에 가서 얘기를 하면, 이미 당신이 무슨
    생각을 하던 내가 모두 화면에 띄울수 있다고 말한다.
*   또 다른 Goal 이 필요해짐

*   Now: 내가 현실에서 가지고온것, 그리고 그것을 상상과 함친것, 그것을 다시
    현실에 갔다놓는것이 지금시대의 목표.
*   저(교수)는 20년동안 이 분야에 있어왔는데 큰 Goal이 두번 바뀌는것을 보았다.
    그리고 또 목표가 어떻게 바뀔지 모르겠다. 하지만 여러분들은 이제 그 첫번째
    단계를 배우게될것이다.

*   이 과목을 통해서는 1970년대까지 커버할수있을것이다. 그 이후의것은 교과서에
    잘 안들어감. 지금 연구의 수준은, 컴퓨터 그래픽스라는건 굉장히 독특한 성격이
    있어서 컴퓨터그래픽스는 옛날부터 융합적인 성격을 띄어왔다. 어느 분야에서든
    그분야에서 진짜 잘하는사람 - 기하학의 완전 대가, 컴퓨테이셔널 유체역학의
    완전 대가 - 어느시점에 다다르면 다 컴퓨터그래픽스에 와서 논문을
    내고싶어한다. 한마디로, 그래픽스는 온갖분야의 사람들이 와서 다 논문을 낸다 -
    주제가 다 여러분야로 퍼져서, 그래픽스를 공부하는사람들은 다 분야가 아주
    넓다. 오만갖 분야의 내용들이 뒤섞여있고 그럼. 그러면 도대체 교과서를 어떻게
    쓰느냐 - 교과서를 백과사전으로 만드느냐 - 그래서 근래의 내용은 교과서에 잘
    안넣음. 수업시간으로 배우는 그래픽스는 다 Old fassioned.

> 3월 5일

옛날 이야기
--------

*   CRT

    이제는 소니밖에 안만듬

*   빛의 3원색?

    3원색이 아님, 3개면 사람이 인식할수있는 색공간을 대부분 커버가능

*   Vecter CRT vs Raster CRT

    메모리가 너무 비싸서 래스터 CRT를 쓸 수 없었음. 그리는것이 많아질수록
    주사율이 낮아짐.

*   Scan conversion

    화면에 라인바이 라인으로, 윗쪽부터 그리기 시작함.

*   Frame buffer

*   Color depth

    1bit, 8bit, 15-16bit, 24bit 순으로 발전해옴, 이 뒤로 15년간 발전 안해옴.
    최근 몇몇 디스플레이는 96비트를 지원함.

*   주사율

    1930년대에도 이미 24프레임으로 촬영해옴, 그뒤로 발전이 없다가 3년전 호빗이
    초당 48프레임으로 발전.

    최근 영화관에서 영화를 보는것에 대한 큰 이득이 없어져서, 영화관에서 새로운
    시도를 하는데 그중하나가 3D이고, 나머지 하나가 48프레임.

    근데 아직 블루레이도 48프레임 지원을 안해서 극장이 아니면 보기 힘듬.

*   Color lookup table

*   Deeper Frame buffer

    색에 24비트, 알파채널에 8비트, z버퍼에 16비트, 더블버퍼링

    (24 + 8 + 16)*2 = 96

*   Interlacing

    홀/짝 따로 그림. Prograssive scaning 으로 대체됨 (그냥 구분안하고 다 제때
    60Hz로 그리는거)

*   Display Processor

    Frame buffer가 시스템 메모리에 직접 들어있는건 애플2 시절 이야기.

    지금은 Frame buffer가 System bus 밖으로 빠져있고 별도의 하드웨어에 들어있음.
    근데 이것도 옛날이야기.

    GPU엔 디스플레이 프로세서도 있고, 프로세서도 있고 비디오 컨트롤러도 있는데
    디스플레이 프로세서가 엄청 크고 자기 자체의 메모리, BUS 를 가짐

*   인텔

    GPU 회사들은 전적으로 병렬 프로세서에 기대고 있었음. 인텔은 70년대에
    병렬처리에 대한 가능성을 믿지 않았고, 클럭스피드를 미친듯이 올리기 시작.
    클럭스피드를 올리는 제일 쉬운방법은 회선 굵기를 줄이는것. 지금 시그널당
    들어가는 전자 갯수가 100개 단위. 물리적인 한계에 도착해서 이제 인텔은 뒤늦게
    GPU 시장에 들어가기 시작.

*   Flat Panel Displays

    - Thin, light
    - Flicker free
    - Narrower color gamut? Not anymore

*   OpenGL

    실리콘 그래픽스에서 만든 GL (그래픽 워크스테이션 만드는 회사) 이라는
    라이브러리가 있었는데, 그 회사가 없어지기 전 이 라이브러리를 오픈했고

    산업계에서 이걸 표준화해서 (위원회를 거친것은 아님) OpenGL 로 만듬
