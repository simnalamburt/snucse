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
