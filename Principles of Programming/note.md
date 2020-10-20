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
튜플, 레코드, Type Alias 배움

&nbsp;

Week 5, Tue
========
> 2020-09-29

Algebraic Datatypes 배움. ADT 좋아! Scala의 ADT는 자바 상속을 사용해 구현되어있다.

```scala
sealed abstract class Attr
case class Name(name: String) extends Attr
case class Age(age: Int) extends Attr
case class Birth(year: Int, month: Int, date: Int) extends Attr
case class Height(height: Double) extends Attr

val a: Attr = Name("김지현")
val b: Attr = Birth(2000, 3, 10)
```

Recursive ADT도 가능.

```scala
sealed abstract class MyList
case class MyNil() extends MyList
case class MyCons(head: Int, tail: MyList) extends MyList

val x: MyList = MyCons(10, MyCons(20, MyNil()))
```

바이너리 트리도 만들어보아요

```scala
sealed abstract class BTree
case class Leaf(value: Int) extends BTree
case class Node(left: BTree, right: BTree) extends BTree

val x: BTree = Node(Node(Leaf(10), Node(Leaf(20), Leaf(30))), Leaf(50))
```

패턴매칭을 해보아요

```scala
exp match {
  case C1(...) => exp1
  case C2(...) => exp2
  // ...
  case Cn(...) => expn
}
```

MyList의 길이를 재는 함수를 패턴매칭으로 만들어보아요

```scala
sealed abstract class MyList
case class MyNil() extends MyList
case class MyCons(head: Int, tail: MyList) extends MyList

def length(list: MyList): Int = {
  list match {
    case MyNil() => 0
    case MyCons(_, tail) => 1 + length(tail)
  }
}

val x: MyList = MyCons(10, MyCons(20, MyNil()))
length(x)
```

겨스님: 사람들 사이의 컨벤션을 지키는것은 굉장히 중요합니다.

case class는 오버로딩이 안돼용.

```scala
sealed abstract class Yolo
case class Swag(value: Int) extends Yolo
case class Swag(value: Double) extends Yolo
// FAIL!
```

스칼라는 기본적으로 non-exhasutive match에 대해 워닝만 띄우고 에러를 안줌

```scala
sealed abstract class MyList
case class MyNil() extends MyList
case class MyCons(head: Int, tail: MyList) extends MyList

def something(list: MyList): Int = {
  list match {
    case MyNil() => 0
  }
}
```

패턴매칭에서 특정 값으로 매칭할수도 있다.

```scala
sealed abstract class MyList
case class MyNil() extends MyList
case class MyCons(head: Int, tail: MyList) extends MyList

def have_ten(list: MyList): Boolean = {
  list match {
    case MyNil() => false
    case MyCons(10, tail) => true
    case MyCons(_, tail) => have_ten(tail)
  }
}

val with_ten: MyList = MyCons(1, MyCons(10, MyCons(20, MyNil())))
val no_ten: MyList = MyCons(1, MyCons(11, MyCons(20, MyNil())))

have_ten(with_ten)
have_ten(no_ten)
```

```scala
sealed abstract class BTree
case class Leaf() extends BTree
case class Node(value: Int, left: BTree, right: BTree) extends BTree

def find(tree: BTree, query: Int): Boolean = {
  tree match {
    case Leaf() => false
    case Node(value, left, right) if value == query => true
    case Node(_, left, right) => find(left, query) || find(right, query)
  }
}

val x: BTree = Node(5,
  Node(4,
    Node(2,
      Leaf(),
      Leaf()),
    Leaf()),
  Node(7,
    Node(6,
      Leaf(),
      Leaf()),
    Leaf()))

find(x, 1)
find(x, 6)
find(x, 7)
find(x, 10)
```

&nbsp;

Week 6, Tue
========
> 2020-10-06

테일콜 버전도 만들어보자

```scala
sealed abstract class BTree
case class Leaf() extends BTree
case class Node(value: Int, left: BTree, right: BTree) extends BTree

sealed abstract class BTreeList
case class Nil() extends BTreeList
case class Con(node: BTree, tail: BTreeList) extends BTreeList

def findList(list: BTreeList, query: Int): Boolean = {
  list match {
    case Nil() => false
    case Con(Leaf(), tail) => findList(tail, query)
    case Con(Node(value, _, _), _) if value == query => true
    case Con(Node(_, left, right), tail) => findList(Con(left, Con(right, tail)), query)
  }
}

def find(tree: BTree, query: Int): Boolean = {
  findList(Con(tree, Nil()), query)
}

val x: BTree = Node(5,
  Node(4,
    Node(2,
      Leaf(),
      Leaf()),
    Leaf()),
  Node(7,
    Node(6,
      Leaf(),
      Leaf()),
    Leaf()))

find(x, 1)
find(x, 6)
find(x, 7)
find(x, 10)
```

아이조와

### Type Checking & Inference
타입: 값의 정의역. 정적타입 언어와 동적타입 언어가 있음

타입체킹 방식

- 스태틱 타입체킹: 타입에 맞는 값이 생성되는지 컴파일타임에 체크, 런타임에는 타입정보 안들고다녀도 됨
- 다이나믹 타입체킹: 런타임 타입체킹, 값과 함께 타입체크를 들고다니고, 매 계산 전에 타입을 검사함
- 타입체킹 안하기: 아예 안하기, 디버깅 어렵다

러스트는 타입체커가 몹시 강력해요. 일반 타입체커들은 타입에러가 나지 않을것정도만 보장하는데, 러스트 타입체커는 매우 강력해서 타입에러뿐 아니라 데이터레이스, 소유권 에러가 발생하지 않는다 이런것까지 모두 보장해요.

원래 개념적으로 잘 짜던 사람들은 러스트를 보면 되게 좋아해요. 코드를 잘 못짜는 사람들이 보면 정말 싫어하고. 그래서 C 프로그램 하던사람들 보면 극단적으로 갈려요. 아주 싫어하고 못하겠다고 하는사람과, 완전 사랑에 빠지는 사람.

러스트의 핵심은 그겁니다. 효율적으로 짜는 코드는 효율적으로 짜면서도, 타입안전할 수 있다.

- 나: 카이스트에선 시스템프로그래밍 수업이랑 동시성 프로그래밍 수업에서 Rust를 쓴대요
- 그분이 강지훈 교수님이라고 저한테서 박사받은다음 카이스트 부임하신 분이에요
- 나: 빨리 박사 한명 더 졸업시켜서 저희학교에도 Rust 수업 열어주세요 (??
- 제가 그분에게서 강의자료를 받아 수업을 열던가 해야게쬬 저는 러스트를 그렇게 잘하지는 못하지만 강지훈 교수님은 러스트를 아주 잘하셔요

타입추론: 타입을 일일이 명시 안해도 알아서 추론해주는거. 타입을 쓰는건 문서화의 기능도 하기때문에 일부러 쓰기도 함

### Parametric Polymorphicsm
```scala
// 귀찮
def idInt(x: Int): Int = x
def idDouble(x: Double): Double = x

// 조와
def id[A](x: A): A = x
```

여기서 `id`의 타입은 `[A](val x: A) => A`, id는 parametric expression이다. `id[T] _`는 `T=>T` 타입.

Note: 함수 타입은 폴리모피즘을 지원하지 않는다. Polymorphic한 function 값을 갖지는 못한다. 그러나 비슷한 기능을 수행하는 타입을 만들 수 있다.

```scala
def applyn[A](f: A=>A, n: Int, x: A): A = {
  n match {
    case 0 => x
    case _ => f(apply(f, n-1, x))
  }
}

// 이건 안됨
val f: [A](A=>A, Int, A) => A = applyn _

// 이건 됨, f가 함수인것처럼 f() 이렇게 쓰면 동작함
type Applyn = { def apply[A](f: A=>A, n: Int, x: A): A }
val f: Applyn = new { def apply[A](f: A=>A, n: Int, x: A): A = applyn(f, n, x) }
```

스칼라에선 `f.apply()`를 `f()` 이렇게 줄여 부를 수 있음. `apply`라는 함수 이름에 특별한 신태틱 슈거가 있음. 사실 스칼라에선 일반 함수도 클래스 오브젝트로 인코딩되어있다.

파라메트릭 폴리모피즘 외에도 여러 유형의 폴리모피즘이 있다.

&nbsp;

Week 6, Thu
========
> 2020-10-08

데이터 타입에도 파라메트릭 폴리모피즘 쓸수있숴

```scala
sealed abstract class MyList[A]
case class MyNil[A]() extends MyList[A]
case class MyCons[A](head: A, tail: MyList[A]) extends MyList[A]
```

Type alias에도 파라메트릭 폴리모피즘 쓸수있숴

```scala
type BSTree[A] = BTree[(Int, A)]
```

표준라이브러리에 있는 폴리모픽 타입들

- Option[T] = None | Some(x)
- List[T] = Nil | x::L

## Part 2. Object-Oriented Programming
### Subtype Polymorphism (concept)
```scala
type Name = { val name: String }
type NameHome = { val name: String; val home: String }
type NameMobile = { val name: String; val mobile: String }
```

이럴때에, NameHome과 NameMobile을 Name의 서브타입이 되게하고싶다

- T <: S
- NameHome <: Name
- NameMobile <: Name

객체 attribute set의 proper subset, All elements of T can be used as that of S

함수의 서브타입 관계

- (Name => String) <: (NameHome => String)

Name => String 함수는 모든 NameHome => String이 필요한 자리에 사용될 수 있음. 이 반대는 안된다.

두 서브타입의 종류

- Structural Subtype: 생긴게 서브타입이면 자동으로 그렇게 만들어줌, structural에선 recursive한 구조가 생길 수 없음
- Nominal Subtype: 명확하게 상속관계를 지정한 타입들에 한해서 서브타입 관계가 생김, 이 경우 recursive한 사이클이 있을 수 있음

스칼라에서 struct는 structural subtype, 클래스는 nominal subtype임.

### Structural Subtype
일반적으로 아래가 성립함

- reflexivity, 반사관계: 모든 T에 대해 아래가 성립함

  ```
  T <: T
  ```

- Transitivity: 모든 T, S, R에 대해 아래가 성립함

  ```
  T <: R   R <: S
  ===============
       T<:S
  ```


특별한 서브타입들에 대해 아래가 성립함

- Nothing: 공집합
- Any: 모든 값의 집합, 전체집합
- 임의의 타입 T에 대해 아래가 성립한다.

  ```
  Nothing <: T <: Any
  ```

레코드에 대해 아래가 성립함

- Permutation

  ```
  ===============
  {...; x: T1; y: T2; ...} <: {...; y: T2, x: T1; ...}
  ```

- Width

  ```
  ==============================
  {...; x: T; ...} <: {...; ...}
  ```

- Depth

  ```
  T <: S
  ====================================
  {...; x: T; ...} <: {...; x: S; ...>
  ```

튜플에 대해 아래가 성립

- Depth

  ```
  T <: S
  ==============================
  (..., T, ...) <: (..., S, ...)
  ```

함수에 대해 아래가 성립함

- Covariance, Contravariance

  ```
  T <: T'        S <: S'
  ======================
  (T' => S) <: (T => S')
  ```

&nbsp;

Week 7, Tue
========
> 2020-10-13

### Class
Class: Parameterized Record

```scala
class foo_type(_name: String, _age: Int) {
  if (_age < 0 || 200 <= _age) { throw new Exception("Out of range") }

  val name: String = _name
  val age: Int = _age

  def getPP(): String = name + " of age " + age.toString()
}

val foo: foo_type = new foo_type("Joe", 25)

foo.name
foo.age
foo.getPP
```

Class는 nominal subtype이다. structural subtype 허용 안함. 생긴게 같다고 해도 `<:` 관계가 성립하지 않음.

모든 Class는 Null이라는 base case를 가짐. 그래서 모든 클래스 타입에는 Null이 들어올 수 있음. Null 사용은 권장되지 않으나 딱히 타입체커가 있진 않음.

ADT처럼 recursive하게 만들 수 있음

```scala
class MyList[A](value_: A, next_: Option[MyList[A]]) {
  val value: A = value_
  val next: Option[MyList[A]] = next_
}

val list = Some(new MyList(3, Some(new MyList(4, None))))
```

Argument Member를 사용해 생성자 선언을 단순화할 수 있음. argument 부분에 val이 있는것 주목

```scala
class MyList[A](val value: A, val next: Option[MyList[A]]) { }

val list = Some(new MyList(3, Some(new MyList(4, None))))
```

빈 중괄호 생략 가능

```scala
class MyList[A](val value: A, val next: Option[MyList[A]])
```

Private class constructor가 있음

```scala
class Person private (name: String) { /* ... */ }
```

Week 7, Thu
========
> 2020-10-15

Companion Object로 이런거 하면 new 생략할 수 있음

```scala
class MyList[A](value_: A, next_: Option[MyList[A]]) {
  val value: A = value_
  val next: Option[MyList[A]] = next_
}

// val MyList = new { .. } 로 써도 됨
object MyList {
  def apply[A](value: A, next: Option[MyList[A]]) = {
    new MyList(value, next)
  }
}

val list = Some(new MyList(3, Some(new MyList(4, None))))
val list = Some(MyList(3, Some(MyList(4, None))))
```

### Nominal Sub Typing for Classes = Inheritance
```scala
class FooType(x: Int, y: Int) {
  val a: Int = x
  def b: Int = a + y
  def f(z: Int): Int = b + y + z
}

class GeeType(x: Int) extends FooType(x+1, x+2) {
  val c: Int = f(x) + b
}

// GeeType <: FooType

(new GeeType(30)).c
def test(f: FooType) = { f.a + f.b }
test(new FooType(10, 20))
test(new GeeType(30))
```

Overriding

```scala
class GeeType(x: Int) extends FooType(x+1, x+2) {
  override def f(z: Int) = super.b + super.f(z) * 2
  val c: Int = f(x) + b // b 는 override되지 않아 super.b와 동치
}
```

주의: 이건 오버라이딩이 아니라 오버로딩임. 함수 타입이 다름

```scala
class GeeType(x: Int) extends FooType(x+1, x+2) {
  def f(z: String) = 77
}
```

근데 함수 리턴타입을 subtype으로 지정하는 방식의 오버라이딩은 가능함

```scala
class GeeType(x: Int) extends FooType(x+1, x+2) {
  override def f(z: String): Nothing = ???
}
```

상속이 함수의 의미도 바꾸고, 가독성도 떨구고 여러가지 단점이 많아요. 그래서 최근에는 상속은 최대한 피하고 대신 인터페이스를 쓰세요.

OOP는 아름답지 못하다. Sum type을 구현하기위해 온갖 흑마법과 사파를 동원해야함.

`Option[MyList[A]]` 대신, 상속을 이용해 Sum type을 만들어봅시다.

```scala
class MyList[A]()
class MyNil[A]() extends MyList[A]
class MyCons[A](val hd: A, val tl: MyList[A]) extends MyList[A]

val t: MyList[Int] = new MyCons(3, new MyCons(4, new MyNil()))
// t를 사용하는것이 매우 힘듬. 자바 instanceof 같은걸 써야함
```

new 호출이 귀찮으니 companion object를 써보아요

```scala
class MyList[A]()
class MyNil[A]() extends MyList[A]
object MyNil { def apply[A]() = new MyNil[A]() }
class MyCons[A](val hd: A, val tl: MyList[A]) extends MyList[A]
object MyCons { def apply[A](hd: A, tl: MyList[A]) = new MyCons[A](hd, tl) }

val t: MyList[Int] = MyCons(3, MyCons(4, MyNil()))
// t를 사용하는것이 매우 힘듬. 자바 instanceof 같은걸 써야함
```

리스트를 만들긴 했지만 쓰는게 어렵네요. case class 문법을 쓰면 아래의 세가지가 변해요

1.  val arguments가 기본임. 생성자 argument에 `val` 안써도 됨
2.  companion object가 없어도 생성자 호출에서 `new` 생략가능
3.  패턴매치에 넣을 수 있게됨

OOP 언어에서 상속을 사용한 sumtype 구현은 사파의 무공인데, 이를 정파로 아름답게 만들어줄게 이게 바로 패턴매칭이에요.

```scala
class MyList[A]()
case class MyNil[A]() extends MyList[A]
case class MyCons[A](hd: A, tl: MyList[A]) extends MyList[A]

val t: MyList[Int] = MyCons(3, MyCons(4, MyNil()))

def length[A](x: MyList[A]): Int = {
  x match {
    case MyNil() => 0
    case MyCons(_, tl) => 1 + length(tl)
  }
}

length(t)

length(MyList[Int]()) // Runtime error: 허용되는 문제가 있음
```

abstract 키워드를 써서 MyList 생성을 막을 수 있음. sealed 키워드를 쓰면 이 소스파일 이외의 장소에서 해당 클래스를 추가적으로 확장하는것이 불가능해짐

```scala
sealed abstract class MyList[A]()

length(MyList[Int]()) // Compile error
```

Week 8, Tue
========
> 2020-10-20

중간고사는 파트 1까지. 인터넷이 끊겨있는 컴퓨터, 에디터, 강의 슬라이드가 준비되어있을것이다.

### Abstract Classes for Specification
Specification

```scala
abstract class Iter[A]() {
  def next(): Option[(A, Iter[A])]
}
```

기본 구현이 들어있을 수 있음

```scala
abstract class Iter[A]() {
  def next(): Option[(A, Iter[A])] = None
}
```

이미 배운 `extends`로 `abstract class` 확장 가능

```scala
abstract class Iter[A] {
  def next(): Option[(A, Iter[A])]
}

sealed abstract class MyList[A] extends Iter[A]

case class MyNil[A]() extends MyList[A] {
  override def next() = None
}

case class MyCons[A](value: A, rest: MyList[A]) extends MyList[A] {
  override def next() = Some(value, rest)
}

def forEach[A](iter: Iter[A], fn: A => ()): () = {
  iter.next() match {
    case None => ()
    case Some((value, rest)) => {
      fn(value)
      forEach(rest, fn)
    }
  }
}

val list = MyCons(10, MyCons(20, MyCons(30, MyCons(40, MyNil()))))
forEach(list, println)
// 10
// 20
// 30
// 40
```

필드가 함수가 아닐 경우, `val next`는 `def next`의 서브타입이어서 아래와 같은 식으로 abstract class를 구현할 수 있고, 이경우 매 호출마다 값이 다시 계산되지 않아 더 효율적이다.

```scala
abstract class Iter[A] {
  def next: Option[(A, Iter[A])]
}

sealed abstract class MyList[A] extends Iter[A]

case class MyNil[A]() extends MyList[A] {
  override val next = None
}

case class MyCons[A](value: A, rest: MyList[A]) extends MyList[A] {
  override val next = Some(value, rest)
}
```

### More on Abstract Classes
선형 타입이 아닌 MyTree에 in-order Iter를 구현해보자. 커서에 해당하는 데이터가 필요해져서 바로 구현하기는 어려워, Iterable이라는 추상클래스를 새로 만들면 간단하다.

```scala
// 이터레이터 추상클래스
abstract class Iter[A] {
  def next(): Option[(A, Iter[A])]
}

// 두 이터레이터 연결하기
// TODO: 꼬리재귀 안됨
case class Concat[A](earlier: Iter[A], later: Iter[A]) extends Iter[A] {
  override def next() = {
    earlier.next() match {
      case None => later.next()
      case Some((value, rest)) => Some(value, Concat(rest, later))
    }
  }
}

// MyList, 임의의 이터레이터를 만드는 용도로 응용할 수 있다
sealed abstract class MyList[A] extends Iter[A]
case class MyNil[A]() extends MyList[A] {
  override def next() = None
}
case class MyCons[A](value: A, rest: MyList[A]) extends MyList[A] {
  override def next() = Some(value, rest)
}

// 주어진 클래스로부터 Iterable한 객체를 뽑아낼 수 있는지
abstract class Iterable[A] {
  def iter(): Iter[A]
}

// MyTree, 이터러블한 객체를 반환할 수 있다
sealed abstract class MyTree[A] extends Iterable[A]
case class Empty[A]() extends MyTree[A] {
  override def iter() = MyNil()
}
case class Node[A](value: A, left: MyTree[A], right: MyTree[A]) extends MyTree[A] {
  override def iter() = Concat(Concat(MyCons(value, MyNil()), left.iter()), right.iter())
}
```

TODO: 슬라이드 145까지 필기했음, 혹시 다음시간에 진도 더 뒤에서 출발하면 빠진 내용은 혼자서 보자
