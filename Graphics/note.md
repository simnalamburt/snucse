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

--------

> 4월 21일

### Matrix Equations for B-splines

### Curve refinement
베지에곡선 둘로 쪼개기

### Binary Subdivision

### Subdivision Rule for Cubic B-Spline
컨트롤포인트를 잘게 쪼개가도, 같은 곡선이 나옴. 이걸 무한히 하면 그냥 곡선이
나옴

### Chakin's Algorithm
Corner cutting subdivision

이걸 반복하면 quadratic B-spline으로 수렴함.

### Interpolating subdivision
Weight의 합은 항상 1

### Subdivision Surfaces
캣멀과 클락.

4각형, N각형에 서브디비젼을 적용

이 아이디어가 제법 그럴싸했는데, 모든사람들이 B-spline과 lerps를 연구하던 시대.
비웃음만 사다가, 78년도에 논문이 나왔는데 80년대 후반에나 재조명받기 시작함. 그
사이엔 원래 하던대로 베이시스 펑션을 가지고, 임의의 서페이스를 그리려고
시도했음. 하지만 box-spline 연구는 실패.

굉장히 복잡한 모양을 만들 수 있고, 마음대로 refine 할 수 있음.

### Subdivision in Action
아주 부드럽고 말캉말캉한건 시뮬레이션이 잘되는데 딱딱한건 잘 안됨. 말랑말랑하면
타임스텝이 넓어도 되는데, 딱딱하면 타임스텝을 상당히 조밀하게 놓아야함.

Cloth 시뮬레이션하는거랑 완전히 딱딱한거 시뮬레이션하는건 방법이 아예 다름.

B-spline이 약한게 뾰족뾰족한거인데, 그냥 displacement mapping 해서 꾜족하게
만든다는거임. 강력한 테크닉임

Environment mapping

스키닝

그래픽스하는사람들은 항상 조절할 수 있는것을 좋아해요

차회 예고: 쿼터니온으로 어파인 변환하는 이야기가 나옴.

### Displaying Spline Curves
목표: 덧셈만 가지고 그릴 수 있다!

x(t)를 안다면, x(t+d)를 빠르게 계산할 수 있다!

합 크라프트: 우리 이전세대에 온갖 교과서를 다쓴사람. 코넬에서 연구 슬슬 접으면서
자기 인생 마지막 문제라고 들고온게 exact computation이었음.

무덤분야. 아무도 해답을 못냄. Box spline도 그렇고, 손대면 백수가 되는 분야가
있음. 문제를 잘골라야됨.

문제를 잘못고르면 폭삭 망해요
문제를 잘고르는게 굉장히 중요합니다.
무덤 연구분야가 있어요.
수업시간에 되게 잘하고 그랬던 친구가
내가 추천서 써서 유학을 보내줬는데
지도교수 찾은게 딱 그 지오메트리 하는 양반을 찾았어요.
LM에 가있어요
스타워즈 만든회사
fluid sim도 하다가
다른것도 하고
내가 데리고있는 포스닥중 한명은
웨타에 가있어요
반지의 제왕 시리즈
킹콩
호빚
거기서 모션캡쳐를 하는 스페셜리스트로 일을 하죠
질문: 그래픽스 하는사람 별로 없어요?
모든 분야가 유행을 타요
내가 그래픽스 하던시절엔 그래픽스가 최고의 인기 분야였어요
가장 똑똑한 사람들이 오는 분야였어요
근데 요즘은 그렇진 않고
적절한 숫자에 적절한 학생들이
나는 곧 죽어도 이걸 하겠다는 학생들이 와요
이건 좋은사람들이 하는 분야에요
뭔가 그려지고 보여지고 내맘대로 조작할 수 있는게 확 끌리는 사람들이 해야해요
이걸 하는사람들은 굉장히 종류가 다양해요
입맛에 따라서 사람들이 꽤 편차가 있을 수 있어요
어느 분야든 마찬가지지만
그래픽스는 항상 다른걸 해요
자꾸 바꿔가면서
새로운걸 찾아다냐요
원래 연구를 하는 사람들은 어쩔 수 없이 새로운것을 뒤져가는 사람이에요
학생들중에 그거에 적응을 잘 하는 사람이 있고 아닌 사람이 있어요
편한게 좋은지 아니면 막막한게 좋은지
마치 김명수교수님같군
스스로한테 한번 물어보세요
우리 연구실에 들어오는 학생들은 연구실에 들어와서
내가 10몇년전에 했던걸 하고싶어해요
나는 그때 할떄 나혼자 황무지에서 아무도 하는사람 없고 혼자했는데
학생들은 내가 10몇년전 전에 했던걸 하고싶어해요
왜냐면 정리가 잘되어있거든
그렇게 가는 사람들은 다 망해요
원래 대학원에 가면 제일 좋은건
교수든 학생이든 Agree해야하는데
학생들을 황무지에 놓고 버리고 오는거에요
그리고 거기를 번듯한 땅으로 바꿔놓는게 학생들이 하는일이에요
댛가운에 들어갔는데
대학원에 들어가는데
익숙하고 잘 닦인 일을 한다면
굉장히 고민해야해요
그런데서 들어가서 연구하는거 아니에요
20년전에 누가 이미 다 해놨다는 뜻이에요
세상은 그렇게 돌아가는겁니다
제일 좋은건 지금은 황무지인데 10년뒤에 진짜 잘풀릴곳을 가야하는데
그게 찾기가 힘들어요
황무지에 가서 메말라죽거나
황무지에 가서 살아 돌아오거나
근데 그건 반반 확률이잖아요
잘 닦여진곳에 가면 그대로 죽는거에요
뉴튼이 한 유명한 말이 있어요
내가 멀리볼 수 있었던 이유는
거인의 어꺠에서 시작했기 때문이라고
대학원생들은 지도교수들의 어깨에서 시작합니다
훌륭한 지도교수를 둔 대학원생들은
손을 조금뻗치면 State of art가 손에 닿습니다.
근데 여기 밑에서부터 시작하면 마르고 닳도록 노력해도 닿지 않아요
그게 공부하는 방법이에요
근데 가끔 보면 똑똑한 학생들일수록 그런경우가 많은데
우리는 뭔가 만들어야하거든요
근데 그 만드는걸 밑바닥부터 만들겠대요
남이 하던거 위에 하는건 잘 못하겠대요
근데 밑이 어딘데
도대체 어디서부터 만들면 밑바닥이냐고 항상 싸워요
교수들은 니 선배들이 했던거 절대 반복하지 마라 그러는데
자꾸 학생들은 자기가 배운것부터 쌓겠대요
저래가지고 언제 끝날까
그게 되풀이되는 교수와 학생들의 싸움 중 하나입니다.
여러분중에 나중에 대학원가서 그런일 할 사람이 분명 있어요
교수가 보기에 땡깡이에요 땡깡
몇년동안 쭈그리고 앉아서 졸업할 생각도 없고
뻔히 전세대가 한걸 하겠대요
여러분들은 새로운걸 하는겁니다
그럴 마음의 준비를 하고
대학원을 가도 그렇고
사회생활을 해도 그래요
익숙하지 않은걸 즐길 준비를 하십시오.

물 시뮬레이션 제대로된거 처음 나온게 벅스라이프

--------

> 5월 12일

Chromaticity Diagram

### CIE XYZ Color Space
색깔을 원색을 섞은걸로 표현하려고 하면 negative coefficient가 있음.

그래서 물리적으로 존재할 수 없는 가상의 X, Y, Z 색을 만듬. 얘네는 positive
coefficient만 있고 이걸 섞으면 모든 색이 표현됨.

x = X/(X+Y+Z), y = Y/(X+Y+Z)로 만든다음에 이걸로 Colorspace diagram을 그릴 수
있음.

CIE XYZ 다이어그램, 제일 흰 색 기준이 좀 애매함. 그래서 걍 임의로 정해놨음.
사람들 문화에 따라 제일 흰색이 뭐다 받아들이는 기준이 다름.

CIE XYZ 컬러스페이스는 linearity가 만족됨.

sRGB는 color gamut이 좁아서, 아주 붉은색이나 아주 녹색은 범위 밖임.

보통 Adobe RGB를 씀. 어도비 RGB 지원하는 모니터는 좀 더 잘보임. 근데 sRGB
모니터에 비해 가격이 너무 비쌈. 이런애들은 모니터 옆에 가림막 있고 터무니없이
비싸고 그럼.

Illuminant C, 이걸 기준으로 보색을 정의함

Dominant Wavelength

### CIELAB, CIE Lab
Perceptuallc Uniform color space

### CCD
Bayer filter

녹색 민감도가 높다고 믿어지고 있음. 그래서 그냥 녹색 CCD를 많이 넣음.

경계가 깨끗하게 나오지 못함.

### White Balance
Chromatic adaptation

사람의 눈은 절대적인 값보단 상대적인거에 민감. 사람의 의식은, 세상에 대한 모델을
구축한다.

오토매틱 화이트밸런스는, 사람이 보고싶은 영상을 보여줘야함. 이게 똑바로 될리가
없다.

### The infamous gamma curve
감마 조절.

### Color quantization gamma
http://en.wikipedia.org/wiki/Weber%E2%80%93Fechner_law
```
<@지현> 오늘 이제희 교수님 명언
<@지현> "고문은 익스포넨셜 하게 해야지"
<@지현> "이 친구가 느끼는 고통이 리니어하게 증가해요"
<@지현> 인지과학
```

### HDR
