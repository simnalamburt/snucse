Week 1, Tue
========
> 2020-09-01

1시간 50분 수업인데, 실습 진행이 어려워서 가능하면 1시간 안에 끝내고, 늦어도 1.5시간 수업으로 끝내겠다. 다음부턴 수업자료를 미리 올리겠다. 조교 메일은 <pp@sf.snu.ac.kr>. 수업시간에는 노트북 지참 필수. 필요하면 학과에서 노트북을 빌려줘요. 질문은 채팅이나 마이크로 언제든지 편하게 해주세용.

출석 5%, 과제 25%, 중간 30%, 기말 40%. 모든 과제 채점은 자동채점기다. 과제는 보통 총 4~5개에 Term project 한번. 시험은 프로그래밍으로 치룬다. 컴파일이 되는지 안되는지는 실시간으로 알려주지만, 점수는 공개하지 않는다. 시험 포맷은 숙제랑 비슷하고, 시간제한은 없다. 기본적으로 4시간 시험인데, 학생이 더 하고싶다고 하면 조교가 설득은 하겠지만, 시간은 무한히 준다. 여러번 제출이 가능하다.

조교 추천도서: [스칼라로 배우는 함수형 프로그래밍](https://www.yes24.com/Product/Goods/16969986), [Functional Programming in Scala (ISBN: 9781617290657)](https://books.google.co.kr/books/about/Functional_Programming_in_Scala.html?id=bmTRlwEACAAJ)

후 엠 아이: 카이스트에서 학부하고 병특한다음 영국으로 유학가서 박사했다. 고딩때엔 1994 IMO 동메달. 소프트웨어 검증, 로레벨 언어 시맨틱 (C, C++, LLVM, Rust) Relaxed-memory 컨시스턴시 관련 연구.

요즘은 구글에서 Protected KVM같은 연구를 하고있다. OS도 접근 못하는 메모리영역을 만들기. 몇년 내로 안드로이드에 모두 들어갈듯. 요즘은 삼성에서 커널 패치를 직접 안하고, 구글에서 제네릭 커널 이미지를 배포하는데, 이거덕분에 구글에서 신기술을 적용하면 여러 안드로이드에서 쓰기 쉬워짐. 요즘은 정적검증으로 Protected KVM의 안정성을 증명하는 일을 하고있음.

대부분의 컴파일러 최적화는 컨커런시를 고려하지 않고 싱글코어 기준으로 개발되었음. 90년대 들어서 멀티코어가 나오니까 그런 최적화들중 올바르게 동작하지 않는것이 많았음. 이 잘못된 최적화를 바로잡고, 컨커런시를 위한 최적화를 바로잡는것이 오래 연구되었었는데, 여기서 나온 연구중 하나가 Relaxed-Memory 컨커런시.

POPL이랑 PLDI가 PL에선 탑 2 컨퍼런스. <https://csrankings.org> 참고하세용. Software Foundation 랩에서 2011년부터 2020년까지 7개의 PLDI 논문, 7개의 POPL 논문 퍼블리시 (전세계 8등), 10년동안 매해 POPL이나 PLDI중 한곳에 계속 논문을 냄 (전세계 3등), distinguished paper award 두번받음 (PLDI 2017, POPL 2020)

프원 수업에서 가르친는건 제가 연구하는 분야는 아니에용. 그리고 제가 controversial한걸 가르칠수도 있어용. 여러분들도 제가 가르쳤다고 제가 한 말을 모두 믿지 마시고, 본인이 직접 경험하고 판단하세용.

수업에서 크게 세개를 합니다.

1. Functional Programming with Function Applications
2. OOP
3. Type Classes for Interface

교수님 피셜: 제가 해보니까 타입 클래스가 모든 면에서 OOP보다 나아요.

교수님 피셜: 이론적으로 핵심만 놓고 보면 OOP는 장점이 없는것같아요.

제 생각엔 타입클래스가 더 좋다고 주장을 할거고.

### Imperative vs Functional programming
##### 명령적
- 메모리 읽기쓰기에 의한 계산
- 컴퓨터 수준에서 How to do를 구체적으로 기술
- 효율적인 코드를 쓰기 쉽다
```c
sum = 0;
i = n;
while (i > 0) {
  sum = sum + i;
  i = i - 1;
}
```

##### 뻥셔널
- 함수 apply, 함수 조합에 의한 계산
- 계산 결과 관점에서 what to do만 기술
- 안전한 코드를 쓰기 쉽다, 훨씬 빠르게 짤 수 있음
- 컴파일러가 똑똑하고 최적화를 잘 해줘야함
```scala
def sum(n) = 
  if (n <= 0)
    0
  else
    n + sum(n-1)
```

알고리즘에 따라 Imperative로 기술하는게 훨씬 효율적이고 간단할때에도 많다. 그런데 여러분 Imperative 맨날 하잖아요? 그러니까 이번 수업에선 안할게용.

Rust가 굉장히 Fancy한 언어이니 여러분 알아보세요. C와 같은 성능을 내면서 쉽게 프로그래밍을 할 수 있어요. Rust로 OS도 짤 수 있고, 브라우저도 만들어요.

많은 언어들이 imperative 스타일과 functional 스타일을 모두 지원한다.

- 주로 명령형: Java, js, C++, Python, Rust, ...
- 주로 함수형: OCaml, SML, Lisp, Scheme
- 중간: Scala
- Purely function하지만 모나드로 명령형 지원: Haskell

교수님 피셜: Rust랑 잘 맞는 사람이 프로그램을 잘 짜는 사람일 가능성이 크죠. 미래에 면접을 프로그램을 러스트로 짜보세요 이렇게 할수도 있어요.

수업에서 스칼라 쓰는 이유: 명령형 & 함수형 스타일 모두 지원, OOP와 타입클래스 지원, 자바 호환됨

### OOP
내가 잘 아는 그것,,

요즘은 Interface와 구현을 나누는것이 중요한 대세에요.

오늘 썰이 좀 길어지는데 첫수업이니 썰을 좀더 풀겠습니다. Interface는 디테일은 숨기고 what to do만 기술한것이라고 볼 수 있잖아요? Type level에서 what to do만 기술한 interface만 가지고도 구현을 할 수 있는데 이 추상이 아주 중요해요. 여러분이 자동차의 동작원리를 다 알아야만 차 운전 할 수 있는거 아니잖아요? 현대차 포르셰 테슬라 다 내부는 전혀 다르지만 인터페이스가 같으니 여러분이 다 운전할 수 있는거잖아요? 이것이 코드 재활용성을 굉장히 키워요.

요즘 큰 회사에서 하는 SOA(서비스중심설계)같은걸 보면, 팀끼리 인터페이스만 공유하고 내부 코드를 절대 공유 못하게 막아요. 이렇게 인터페이스만 공유하며 프로그래밍하는것이, 큰 스케일인 서비스 설계에서도 일어나고, 작은 스케일인 코드 수준에서도 일어나요.

혹자는 컴퓨터과학이 머냐 했을때 "Abstraction of mechanization"라고 대답하기도 해요. 컴퓨터는 점점 복잡해지고 할수있는 일이 많아지는데, 이걸 어떻게 추상화하고 쉽게 짤 수 있게 만드느냐 라고 이야기하는데 맞는말같아요.

파트3에는 OOP를 매번 까면서 타입클래스에 대해 배울겁니다. 왜 OOP가 안좋은지. 제 개인적인 의견이 조금 들어가있을 수 있습니다.

Q&A

- Q: 저기 스칼라 예제코드에 있는 Unit이 먼가요?
- A: 가능한 값이 하나뿐인 타입

출석은 본인이 알아서 하세용. 온라인인 학생이 너무 적으면 할수도 있긴한데, 온라인 수업이라 어차피 접속해놓고 놀수도 있는거고.. 알아서 하세용

&nbsp;

Week 1, Thu
========
> 2020-09-03

## Part 1. Functional Programming with Function Applications
### Values, Expressions, Names
- Value: 값
- Type: 값의 집합
- Expressions: Values, names, primitive operations 등 수식의 조합
- Name Binding: Expression을 Name에 결합하는것

```scala
def a = 1 + (2 + 3)
def b = 3 + a * 4

// 모든 expression에 타입을 붙일 수 있음
def a = 1 + ((2 + 3): Int)
```

### Evaluation
실행은 아래의 순서로 이뤄짐

1. 가장 바깥쪽부터 안쪽으로, 수식에 있는 연산자와 name들에 대해 아래를 적용시킴
2. (name) name들을 모두 바인딩된 expression으로 바꿔줌
3. (name) expression을 실행함
4. (operator) operator들의 operand들을 evaluate함
5. (operator) operands들을 operator에 적용시킴

### Functions and Substitution
```
def f(x: Int): Int = x + a
```

- Function: 파라미터가 있는 expression, 함수도 name에 바인딩할 수 있음
- Evaluation by substitution: operand들을 맨 왼쪽부터 차례대로 evaluate 한 뒤, 

Polymorphic function이 나중에 나옴

### Simple Recursion
함수 X의 정의 안에서 X를 호출할 수 있음

```scala
def sum(n: Int): Int =
  if (n <= 0)
    0
  else
    n + sum(n-1)
```

&nbsp;

Week 2, Tue
========
> 2020-09-08

### Termination/Divergence
끝나지 않는 연산

- Termination: 하나의 값으로 reduce되는 expression
- Divergence: 영원히 reduce하는 expression

```scala
def loop: Int = loop
```

### Evaluation strategy: Call-by-value, Call-by-name
```scala
def foo(value: Int, name: =>Int) = value

foo(1+2, loop) // 계산이 끝남
foo(loop, 1+2) // 무한루프에 들어감
```

### Name binding strategy
```scala
// Call-by-value
val x = 1 + 2 + 3
val foo = loop

// Call-by-name
// Bind to the name without evaluating it, mostly used to define functions
def y = 1 + 2 + 3
def bar = loop
```

### Conditional expressions
```scala
if (cond) exp1 else exp2

// Rewrite rules:
if (true) exp1 else exp2 //=> exp1
if (false) exp1 else exp2 //=> exp1
```

### Boolean expression
```scala
true, false, !exp

// e1은 call by value, e2는 call by name
e1 && e2, e1 || e2

e1 <= e2, ...
```

### Practice
```scala
def sqrt(x: Double) = {
  def sqrtIter(guess: Double, x: Double): Double = {
    if (isGoodEnough(guess, x)) guess
    else sqrtIter(improve(guess, x), x)
  }

  def isGoodEnough(guess: Double, x: Double) = {
    val ratio = guess * guess / x
    0.999 < ratio && ratio < 1.001
  }

  def improve(guess: Double, x: Double) =
    (guess + x/guess) / 2

  sqrtIter(1, x)
}

sqrt(2)
```

스칼라는 재귀함수의 경우 반환형을 명시하도록 강제하고있다. 프로그래머가 알아보기 쉬우라고 강제하는것이다. ML이나 하스켈 등 반환형 안써도 타입추론 잘 되는 언어들은 많음.

&nbsp;

Week 2, Thu
========
> 2020-09-10

### Blocks
```scala
val bla = {
  val x = 3
  // ...
}
```

블락도 하나의 expression

```scala
// OK
{
  def y = x*2
  def x = 10
}

// FAIL
{
  val y = x*2
  val x = 10
}
```

val은 eager하게 evaluate하기때문에 정의 순서가 바뀌면 안되지만, def는 상관없다.

```scala
val x = 10
def func(): Int = x * 2
{
  val x = 20
  {
    val x = 30
    foo(x) // 가장 가까이 있는 x를 사용하는것
  }
}
```

변수명 섀도잉이 가능함. 함수는 정의될 당시의 제일 가까운 이름을 static하게 사용함.

한줄 한줄 실행할때마다 환경에 symbol들이 추가되며 실행됨. 환경은 함수콜이 일어날때마다 스택처럼 쌓임.

```scala
// FAIL
{
  def x = 10
  def x = 20
  x
}

// FAIL
{
  val x = 20
  val x = 10
  x
}
```

하나의 블럭 안에 이름이 두번 정의될 수 없음.

```scala
val t = 10
def foo1 = t*3
def foo2() = t + t;
{
  val t = 100

  println(foo1)
  println(foo2())
}
```

인자가 없는 함수는 괄호가 없는 `def`와 매우 유사함. 정의된 스코프에 있는 변수를 가져다 씀.

```scala
// 에러가 나야하는데 일부 repl에서 에러가 안날때가 있음
def x = v * 5
println(x)
val v = 20

// 이러면 됨
{
  def x = v * 5
  println(x)
  val v = 20
}
```

스칼라 repl이 중괄호를 안씌우면 결과가 이상한 경우가 있으니 조심하세용.

&nbsp;

Week 3, Tue
========
> 2020-09-15

블락 안으로 함수를 숨기는 이유: 어린이들 키워보면 손에 보이는거 아무거나 다 눌러보잖아요? 이렇게 함수 내부에서 쓰는 함수도 노출하면 쓰게되니까, 안으로 숨겨놓는거에요.

### Lazy Call-by-value
- Call by value: eager하게 선언된 즉시 계산함
- Call by name: lazy하게 사용될때마다 매번 계산함
- Lazy call by value: lazy하게 맨 처음 사용될 때 딱 한번 사용됨

```scala
lazy val x = a*a + b*b + c*c

x + x // x는 한번만 계산됨
```

### Tail Recursion
```scala
import scala.annotation.tailrec

def sum(n: Int): Int = {
  @tailrec def sumItr(res: Int, m: Int): Int =
    if (m <= 0) res else sumItr(m + res, m - 1)
  sumItr(0, n)
}
```

`@tailrec`은 붙였음에도 불구하고 꼬리재귀 최적화가 발생하지 않을 경우, 컴파일러 경고가 발생함. 스칼라 2.8에 추가됨.

Continuation은 데이터로 표현할수도 있다. Higher-order function이라는걸 써서 이 tail recursion을 일반화할 수 있다.

C, Java 등 많은 컴파일러들이 tail call optimization을 지원하는데, 파이썬은 일부러 안한다.

꼬리재귀로 피보나치 짜기

```scala
import scala.annotation.tailrec

@tailrec
def fib(nth: Int, a: Int = 0, b: Int = 1): Int = {
  if (nth == 0) { return a }
  fib(nth - 1, b, a+b)
}

fib(0)
fib(1)
fib(2)
fib(3)
fib(4)
fib(5)
fib(6)
fib(7)
fib(8)
```

&nbsp;

Week 3, Thu
========
> 2020-09-17

### Higher-Order Functions
익명함수와 하이어 오더 뻥션을 사용하면, 코드를 굉장히 DRY하게 짤 수 있음

맵리듀스는 구글에서 제프딘이라는 사람이 빅데이터 처리하는데에도 쓰셨죠

클로저: 하이어오더뻥션을 지원하기 위해 필요한 개념. 여러분 클로저 어디서 들어보셨어요?

> 김지현:
>
> 1. 리습 비스무리하게 생긴 언어이름
> 2. 야구용어
> 3. 수학용어
>
> 로 들어봤어요

2, 3은 별 관련이 없고 1이 제일 관련이 깊어요.

[파라미터 list가 없는 definition과, 빈 파라미터 list를 가진 definition의 차이](https://stackoverflow.com/a/2774788/13977061)

> 내 몸이 parameterized expression이라고 해볼게요

(대충 익명함수를 어디에서 쓰더라도 맨 처음 정의된 환경을 사용한다는 설명을 하다가 나온 말)

&nbsp;

Week 4, Tue
========
> 2020-09-22

화면을 켜자 교수님께서 네이버 부동산 스터디 카페를 보고계셨음. 윈도우용 X11 서버도 눈에 띈다.

Higher-order function 계속 설명

### Currying
커리잉 문법 설명

&nbsp;

Week 4, Thu
========
> 2020-09-24

커리잉 계속 설명

### Exception
다른 언어 익셉션과 거의 같음, 짧게 설명하고 지나감

### Datatypes
튜플, 레코드 배움
