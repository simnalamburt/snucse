이산수학
========

- [강의 홈페이지](http://bi.snu.ac.kr/Courses/dm2016spring/index.html)
- Logic and Proofs:
    [PDF<sup>1</sup>](https://bi.snu.ac.kr/Courses/dm2016spring/slides/Chapter1p1.pdf)
    [PDF<sup>2</sup>](https://bi.snu.ac.kr/Courses/dm2016spring/slides/Chapter1p2.pdf)
    [PDF<sup>3</sup>](https://bi.snu.ac.kr/Courses/dm2016spring/slides/Chapter1p3.pdf)
    [판서](https://bi.snu.ac.kr/Courses/dm2016spring/imgs/blackboard0312.JPG)
    [연습](https://bi.snu.ac.kr/Courses/dm2016spring/practice/practice1.pdf)
- Sets: [PDF](https://bi.snu.ac.kr/Courses/dm2016spring/slides/Chapter2_Sets.pdf)
- Functions: [PDF](https://bi.snu.ac.kr/Courses/dm2016spring/slides/Chapter2_Functions.pdf)
- Sequences:
    [PDF<sup>1</sup>](https://bi.snu.ac.kr/Courses/dm2016spring/slides/Chapter2_Sequences_and_Summations.pdf)
    [PDF<sup>2</sup>](https://bi.snu.ac.kr/Courses/dm2016spring/slides/Chapter2_Cardinality_of_Sets.pdf)
- Matrices: [PDF](https://bi.snu.ac.kr/Courses/dm2016spring/slides/Chapter2_Matrices.pdf)
- Algorithms: [PDF](https://bi.snu.ac.kr/Courses/dm2016spring/slides/Chapter3_Algorithms.pdf)
- The Growth of Functions: [PDF](https://bi.snu.ac.kr/Courses/dm2016spring/slides/Chapter3_The_Growth_of_Functions.pdf)
- Complexity of Algorithms: [PDF](https://bi.snu.ac.kr/Courses/dm2016spring/slides/Chapter3_Complexity_of_Algorithms.pdf)

<br>

필기
--------

<p align=right>첫날 ...</p>

거의 매주 숙제가 나갈겁니다. 교과서마다 챕터 끝에서 문제를 골라서 줄겁니다.
교재의 문제들을 풀면 시험공부에 도움이 될거에요.

Discrete Mathematics. 이산수학이 다루는 이산구조에는 어떤것이 있을까?

- 명제
- 수열
- 집합
- 관계, 그래프, 트리

이산수학을 공부하는것은, 생각하는법을 배우는것과 비슷합니다. 좋은 프로그램을
짜려면 좋은 로직을 디자인하는것이 중요하지요? 이산수학에선 바로 그러한것을
공부합니다.

Logic and Proofs
========
자연어와 프로그래밍 언어의 차이가 뭘까요?

자연어는 사람 사이의 커뮤니케이션에는 아주 좋은 도구이지만, 모호하기때문에
기계를 위해선 별로 좋지 않습니다. 그래서 저희는 프로그래밍 언어를 만들어서 쓰죠.

자연어에서 다루는 값, 실제세계의 문제는 모두 연속적입니다. 하지만 프로그래밍
언어에선 대부분의 값을 바이너리로, 이산적으로 만듭니다.

모든 랭귀지는 아래의 두 기준으로 나눌 수 있습니다.

- context-sensitive language
- context-free language

모든 자연어는 전자에 속합니다. 거의 대부분의 프로그래밍 언어는 후자에 속합니다.

expressiveness. 언어에 따라 표현력이 다릅니다. 그래서 우리는 여러가지 종류의
프로그래밍 언어를 갖고있습니다.

### Propositional Logic
자연어, 프로그래밍 언어와 마찬가지로 Proposition도 하나의 언어라고 볼 수 있다.
명제란 무엇인가?

> A proposition is a declarative sentence that is either *true* or *false*.

명제의 예시

- 달은 치즈로 만들어져있다.
- 서울은 한국의 수도이다.
- 1 + 1 = 1
- 0 + 0 = 2

명제가 아닌것의 예시

- 앉아라
- 지금이 몇시지?
- x + 1 = 2
- x + y = z

여러 명제들을 결합해서 또다른 명제를 만들 수 있다.

- Propositional Variables: p, q, r, s, ...
- Propositional Constants: **T** (Tautology), **F** (Contradiction)
- Compound Propositions
  - Negation 부정: `¬`, `!`
  - Conjunction: `∧`, `and`
  - Disjunction: `∨`, `or`
  - Implication: `⇒`, `->`
  - Biconditional: `⇔`, `==`
  - Exclusive disjunction: `⊕`, `xor`

###### Reference: https://en.wikipedia.org/wiki/List_of_logic_symbols

- Converse (역): p->q 를 q->p 로 바꾸는것
- Inverse (이): p->q를 !p->!q 로 바꾸는것
- Contrapositive (대우): p->q 를 !q -> !p 로 바꾸는것

논리연산자의 우선순위

오퍼레이터     | 우선순위
---------------|----------
`¬`, `!`       | 1
`∧`, `and`     | 2
`∨`, `or`      | 3
`⇒`, `if/then` | 4
`⇔`, `==`      | 5

### Applications of Propositional Logic
명제 논리를 배우면 뭐가 좋을까?

- 자연어를 논리로 바꿀때
- 시스템 스펙
- 고급검색 (boolean searching)
- 논리회로

### Propositional Equivalences
- Tautology
- Contradiction
- Contingency: 참, 거짓 둘중 하나로 항상 귀결되지 않고, 조건에 따라 값이 달라질
    수 있는것. (예: `p`)

Logically Equivalent: 두 boolean expression의 truth table이 같은 상황

- Disjunctive Normal Form
- Conjunctive Normal Form

Boolean expression을 정규화시키는, 두가지 방법.

<p align=right>셋째주 목요일 (3월 17일) ...</p>

> 교수님 안옴, 조교가 수업중

<p align=right>넷째주 화요일 (3월 22일) ...</p>

Basic Structures: Sets, Functions, Sequences, Sums, and Matrices
--------

기본적인 시간 자료구조들, 그 자료구조들에 적용시키는 기본적인 연산자들에 대해
배웠음.
