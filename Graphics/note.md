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

Affine Geometric
--------

> 3월 12일

Geometric Transformations
--------

* Linear transformation
* Rigid transformation
* Affine transformation
* Projective transformation

### Linear Transformations

어떤 Vector들의 Combination을 Linear Transformation한것이나,
어떤 Vector들의 Transformations들을 Combine한것이나 같을경우

Linear combination is invariant under *T*

T(v) = M33 v31 (Column major)
     = v13 N33 (Row major)

교과서는 칼럼메이저로 쓰는게 종이를 덜 차지함

Examples:

1. Scaling
1. Shear
1. Reflection
1. Rotation

*   모든 3D 선형변환은 3x3 행렬의 곱으로 표현할 수 있음
*   모든 3D 선형변환은 회전, 스케일링, Shear의 조합으로 표현될 수 있다.
*   회전은 스케일링과 Shear의 조합으로 표현될 수 있다. 과거에 이미지
    프로세싱하는사람들은 절대로 로테이션 매트릭스를 그대로 쓰지 않았음. 무조건
    Scaling과 Shear의 조합으로 썼음

Matrix decomposition은 어렵다. 마음에 드는 decomposition 종류가 별로 없다.
종류가 아주 수많음.

Transform은 decompose가 쉽게 되지 않음. 기본 단위를 정하기 어렵다.

### Changing bases

v0/v1 벡터 공간 위의 (x, y) 점이 있다. 이 점은 가만히 냅두고 좌표계를 v0'/v1'로
바꾸고싶다

```
x'v0' + y'v1' = xv0 + yv1
```

```
v0 = a0v0' + a1v1'
v1 = b0v0' + b1v1'
```

```
| x' |   | a0 b0 || x |
| y' | = | a1 b1 || y |
```

### Affine Transformations

어파인 변환 T.

T maps vectors to vetors, points to points

Affine combination is invariant under T

T(p) = M33p31 + T31

### Homogeneous Coordinates

```
T(p) = | M33 T31 || p31 |
       |  0   1  ||  1  |
```

Affine transformation is *linear* in Homogeneouse Coordinates

### Affine Transformation의 속성

어파인변환은..
1.  선을 선으로 매핑한다
1.  평행선 둘을 평행선 둘로 매핑한다.
1.  선 상의 점들의 거리 비율을 유지한다.
1.  절대적인 길이나 각도를 유지시켜주지 못한다.

```
| x` |   | a0 b0 c0 || x |
| y` | = | a1 b1 c1 || y |
| 1  |   | 0  0  1  || 1 |
```

### Rigid Transformations

Rigid Transformations는 변환 전/후에, 모든 거리들이 유지되는 변환

T

1.  T는 벡터를 벡터로, 점을 점으로 매핑
1.  T는 모든 점 사이의 거리를 유지
1.  T는 모든 벡터들 사이의 외적을 유지 (to avoid reflection)

리지드 트랜스폼은 딱 두개밖에 없음.

1.  로테이션
1.  트랜슬레이션

```
Orthogonal: R * R^T = R^T * R = I
Special: det R = 1
3D Transform
```

SO(3) 라고 한다.

### Rigid Body Rotation

R is orthogonal

칼럼벡터를 그려도 90도, 로우벡터를 그려도 90도라는 뜻이다.

이건 설명이 잘 안되고 여러분들이 열심히 들여다보세요.

### Taxonomy of Transformations

* Linear
* Rigid
* Affine
* Projective

Linear, Rigid < Affine < Projective

### Composition of Transforms

* Linear + Linear -> Linear
* Affine + Affine -> Affine
* Rigid + Rigid -> Rigid

* Linear transformation의 Linear Combination은 Linear transformation
* Affine transformation의 Linear Combination은 Affine함
* Affine transformation의 Affine Combination은 Affine함
* Rigid transformation의 Affine Combination은 Affine transformation

--------

> 3월 17일 화요일

회전행렬의 정의 = A^-1 이 A^T 인것.

코디네이트를 새 코디네이트 시스템으로 보내주는것과
한 코디네이트가 있을때, 새 코디네이트 시스템에서의 이 점의 좌표를 보는것은
전혀 다르다

임의의 축에 대한 회전 만드는법.

1. Old fassioned
2. Modern way

코딩할때 아크코사인 쓰지마라. 뭔가 잘못되고있는것. 금기시되는 함수

코사인이랑 사인을 알면 이미 행렬을 만들 수 있으니 각도를 몰라도 됨.

### 천재를 구분하는 방법

어떤 결론에 도달했는데, 왜 그 결론에 도달했는지 아무리 노력해도 그 이유를 알 수
없을때 그를 천재라고 한다.

오일러 각도

아폴로 우주선 핸들이 짐버였다고 함

인공위성의 지상촬영 카메라도 짐블에 달려있음

xyz, xyx, xzy, xzx, 등 12가지 방법으로 오일러각도를 만들 수 있음

로테이션을 시키다보면 xyx가 xyz로 변신할 수 있음.

로테이션의 비극

짐버락

자유도가 사라지는 마법을 보여주마

현질의 physics와 mathmatical repr이 매치하지 않아서 나타나는 일

오일러 각도는 Ambiguous 함

(x, pi/2, 0) = (0, pi/2, -x)

이거떔에 이십년정도 전에 모 방송사에서 2억원주고 wavefront 샀더니 망한일이 있음

* 지오메트리
* 렌더링
* 애니메이션

학과 사무실에 있는 3D 프린터 내(이제희 교수님) 핑계 대고 막 쓰세요

--------

### 3D Object repr
- 바운더리 레프리젠테이션
  - 너무 유명한 그것
- Space partitioning
  - 복셀. CT사진
- Procedural methods
  - 수식으로 모델 표현
- 컨스트럭티브 솔리드 죠메트리
- 피지컬리 베이스드 모델링

### 뭘 골라야할까?
- 계산 코스트
  - 저장용량
  - 컨스트럭션 타임
  - 디스플레이 타임

남들이 뭘 할때 비웃을때엔 조심해야해요.
10년만 지나도 세상이 변해요.
처음 복셀렌더링 나왔을때 사람들이 모두 비웃었어요.

- 특정 피노미나를 얼마나 효과적으로 표현할 수 있는가
  - 시뮬레이션의 정확도
  - Looks good
- 구현 복잡도
  - 프리미티브가 얼마나 많고, 복잡한가

### Polyhedra
모든 폴리히드라는 Planar graph로 표현가능

오일러 포뮬라
```
V - E + F = 2
```

오일러 푸앙카레 포뮬라
```
V - E + F - L = 2(S - G)
```
푸앙카레가 뭐한사람인지 알아요?
추측한 사람이요.
푸앙카레는 지독히도 계산을 못했던 사람이에요
두자리수 곱하기 두자리수 계산은
이사람에게는 불가능하게 느껴졌대요
수학시험을 보면 항상 0점 비슷한 점수를 받지않겠어요?
프랑스 모 대학에서 수학을 0점을 받고
이 이후로 너무도 유명한 사람이 되니까
그래서 학교 입학시험에 예외규정이 들어감
너무 특이한 성적의 사람은 셤 한번 더볼수있음

### Functional Repr
Explicit
```
z = f(x, y)
```

Implicit
```
f(x, y, z) = 0
```

Parametric
```
(x(t), y(t), z(t)) for t in [a, b]
```

##### Issues
- Repr power
  - Explicit이 제일 제한됨 (지형), Implicit이랑 Parameter는 경우에 따라 양쪽이
    더 나은 표현력을 가진 경우가 있음.
- Easy to render
  - Explicit이랑 Parametric은 그리기 아주 쉽지만, Implicit은 그리기 매우 힘듬
- Manupulate (translate, rotate, ...)
  - Imlicit이 제일 어려움

결과적으로 파라메트릭 repr이 제일 보편적임. 표준화된 방법. OpenGL에도 parametric
form들은 제공됨.

### Implicit Surfaces
- Quadric surfaces
  - 코닉 섹션(원뿔 곡선)이 진화된 Quadrics. 제일 차수가 낮은 곡면이라서 배움.
- Superquadric surfaces
- Blobby objects

### Superquadrics
```
(x/a)**(2/S) + (y/b)**(2/S) = 1
```

### Blobby Objects (metaballs)
A collection of density functions

### Spatial partitioning
복셀

파티셔닝을 넌유니폼하게 수행, 옥트리를 그려서 메모리를 절약. 근데 대충구현하면
별로 효과가 없음. 복셀들마다 링크드리스트 만드는게 오히려 시간 더걸림

##### Binary Space Partitioning tree
공간을 한번에 하나의 기울기와 위치가 자유로운 Plain으로 나눔.

컴퓨터 게임엔진에 굉장히 많이 들어감. 던전 딱 들어가면 자동문 달려있고, 어디
부터 어디까지 보이고 이런거 할때 쓰임. Visible polygon이랑 Invisible polygon
구분하는데에 많이 쓰임

### Constructive Solid Geometry
이도 저도 아닌 중간쯤. 기본적으로 간단한 프리미티브를 갖고있고, 이
프리미티브들로 불리언 오퍼레이션을 해서 새 쉐입을 만듬. 쉐입은 트리로 표현됨.

트리의 leaf엔 리프노드와 리프노트에 대한 트랜스포메이션이 있고, 인터널 노드엔
오퍼레이터가 들어있음. 저장효율이 매우 뛰어남, 그리는데에 시간이 너무 오래걸림.

보통 렌더링할때 레이캐스팅을 씀. 레이를 공간상에 그어놓고, 불리언 오퍼레이션을
1차원 상에서 함.

기계설계하는 캐드시스템에 많이 들어있음

### Procedural Method
자기유사성 프랙탈, Demensionality에 대한 새로운 인식.

Space filling curve. 원래 얘 본질이 뭐냐에 상관없이, 얘가 어떤 절차를 거치느냐에
따라 차원이 달라질수 있다, 1.x 차원도 될 수 있다.

Terrain by random perturbation. 절차적 지형생성.

### Physically Based Modeling
파티클 시스템. 모델링과 애니메이션을 구분하지 않음. 물리에 기반해 현상을
시뮬레이션함. 물, 불, 옷감, 바람, 천체 시뮬레이션, ...
