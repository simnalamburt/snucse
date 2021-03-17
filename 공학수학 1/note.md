Week 1, Tue
========
> 2021-03-02

연락할일 있으면 개인 메일과 TA 메일을 둘다 보내면 좋겠다.

중간 30%, 기말 30%, 퀴즈 과제 프로젝트 40%

중간고사 세번, 퀴즈 일주일에 최소 한번 아무때나, 과제 두번.

Textbook: Erwin Kreyszig, Advanced Engineering Mathematics 10th edition

&nbsp;

Chap 1. First Order Ordinary Differential Equations
--------
Implicit Form인 F(x, y(x), y'(x)) = 0 을 y(x)로 바꾸는 작업.

Ordinary Differential Equation은 Partial Differential Equation의 반댓말.

Explicit Form: y'(x) = f(x, y(x)) 로 주어진 경우도 있다. Implicit form보다는
간단함.

- Ex 1: Verification of Solution

  y = h(x) = c/x (x!=0) is a solution of xy' = -y

- Ex 2: Solution Curves

  y' = cos x => y = sin x + c

  적분상수가 생김, 답이 여러개다. a family of solutions

- y' = y + x

  초기조건에 따라 solution curve가 뭔지 달라짐.

- Ex 3: Exponential Growth, Exponential Decay

  y' = ce^kt => y' = kce^3t = 3y (Exponential growth)

  y' = -0.2y => y = c * e^(-0.2t) (Exponential decay)

Initial Value Problem (IVP)

y' = f(x, y) 와 함께 initial value y(x0) = y0 가 주어진 상황에서 문제풀기

- Ex 4: Initial Value Problem

  y' = 3y, y(0) = 5.7 => y = ce^3x (the general solution)

  y(0) = c = 5.7 => y = 5.7e^3x (a particular solution)

- Ex 5: Modeling Radioactivity (Exponential Decay)

  y' = ky, k는 음수. 처음 방사성 동위원소의 양이 0.5였다면(y(0) = 0.5) y(t)는?

  y = 0.5 * e^kt

**Quiz, Midterm에서 검산을 하지 않으면 1점 감점이다.**

컴공 공수 수업은 중간고사까지 대부분 만점에서 만점-3에 50%의 학생이 분포해서,
1점 감점 매우 커용

1.3 Separable ODEs. Modeling

g(y) * y' = f(x) => ∫g(y)dy = ∫f(x)dx + c

- Ex 1: A separable ODE

  y' = 1 + y^2 => 1/(1 + y^2) y' = 1 => arctan y = x + c => y = tan(x+c)

- Ex 2: Modeling Radioactive Dating, When did the Iceman live and die?

  y' = ky => 1/y * y' = k => ln(y) = kx + C => y(t) = y0 * e^kt

  C14의 반감기 H는 5715년, y(H) = y0 * e^kH = 0.5y0, k = -ln2/H = -0.0001213 년^-1

  지금 남은 탄소가 52.5%면, 아이스맨은 언제의 사체인가?

  y(t)/y0 = e^kt = 0.525 => t = ln(0.525)/k = 5312 년

- Ex 3: Mixing Problem, 새는 바가지에 물붓기

  y' = 50 - 0.01y, y0 = 100

  => 1/(y - 5000) y' = -0.01 => ln(|y - 5000|) = -0.01t + C

  => y = ce^(-0.01t) + 5000 = 5000 - 4900e^(-0.01t)

- Ex 4: Heating on Office Building

  - 바깥의 온도 T_out이 45℉이고 난방을 꺼서 점점 온도가 낮아지고있다.
  - At 10PM, T = 70℉
  - At 2AM, T = 65℉
  - At 6AM, T = ?

  T' = k(T - T_out) => 1/(T - T_out) T' = k => ln|T - T_out| = kt + C

  => T = T_out + ce^kt = 45℉ + 25℉ e^kt

  T(4h) = 45℉ + 25℉ e^(k * 4h) = 65℉, k = ln(0.8) / 4h  = -0.056 h^-1

  T(8h) = 45℉ + 25℉ e^(ln0.8 / 4 * 8) = 45℉ + 25℉ * 0.8^2 = 61℉

Extended Method: Reduction to Separable Form

y' = f(y/x). 어케 풀까?

u := y/x, y = ux, y' = u'x + u = f(u)

1/(f(u) - u) * u' = 1/x * x' (separable!)

- Ex 6

  2xy * y' = y^2 - x^2

  y' = 0.5y/x - 0.5x/y = 0.5u - 0.5/u where u = y/x

  y = ux, y' = u'x + u = 0.5u - 0.5/u => u'x = -0.5(u + 1/u)

  => 2u/(1 + u^2) u' = -1/x => ln(1 + u^2) = -ln|x| + C => 1 + u^2 = c/x

  => 1 + y^2/x^2 = c/x => x^2 + y^2 = cx => (x - 0.5c)^2 + y^2 = 0.25c^2

  여러 원들의 집합이 답으로 나옴

&nbsp;

Week 1, Thu
========
> 2021-03-04

(PDF로 필기)

아마 이 이후 수업들도 모두 아이패드로 필기할 가능성 많음

중간고사랑 퀴즈1까지 검산 안하면 감점이다!!

&nbsp;

Week 2, Tue
========
> 2021-03-09

(PDF로 필기)

과제 1 나감, 작년 강의영상과 이번학기 지난 강의영상 확인 가능

&nbsp;

Week 2, Thu
========
> 2021-03-11

(PDF로 필기)

팝퀴즈, A4용지와 필기구를 준비하자! 태블릿에다가 해도 된다! 팝퀴즈 본 결과를
eTL 혹은 이메일로 제출.

기출문제 꼭 풀어봐라!

&nbsp;

Week 3, Tue
========
> 2021-03-16

(PDF로 필기)

팝퀴즈 한번 봄, 열심히 공부함
