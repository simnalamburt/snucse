자료구조
========

[페이지](http://soar.snu.ac.kr/course/ds/20161/) |
[게시판](http://soar.snu.ac.kr/course/board/ds2016) |
[숙제](http://soar.snu.ac.kr:8080/)

#### Test cases
- [SNUCSE](http://www.snucse.org/374693)
- [Jhuni0123/DSHWTC](https://github.com/Jhuni0123/DSHWTC)
- [kalakuthien/DataStructure](https://github.com/kalaluthien/DataStructure)

<br>

필기
--------

<p align=right>첫주 (3월 2일) ...</p>

- Administration
    - Java 프로그래밍 숙제가 총 6회 2주 간격으로 나옴. 학기 초에 미리 주어진다.
    - 금요일에 있는 실습수업은, 금요일 오후 6시 30분부터 시작할 예정 (30분 당겨짐)
    - 중간고사 (4월 마지막주쯤)
    - 기말고사

시험은 오픈북이다.

- 교재: Data Abstraction and Problem Solving, Carrano, Pearson

> 성주는 이제 가도 좋아

### Data Structures 란?
복잡한 자료를 어떻게 추상화할지 배우고, 크게는 Computational Thinking을 배움.

Computational Thinking. 요즘 저희학교에서도 코딩교육을 전교생에게 하려고
교재연구를 하고있죠? 자료구조를 공부하면 Computational Thinking을 익히는데에
도움이 많이 되어요.

자료구조의 예시를 들어보자

- Array
- Linked list
- Stack
- Queue
- Tree, BST
- B-tree
- Hash Table

함수 호출스택도 Stack 자료구조로 만들어져있죠. Queue는 마트에서 줄설 때 많이
보입니다. BST는 저장/검색을 할 때 색인(index)을 할 때 자주 쓰죠. 배열로도 색인을
할 수 있지만, BST는 중간에 삽입하는 비용이나, 검색하는 비용이 더 싸죠?

B-tree는 자식노드가 2개 이상인 트리입니다. 데이터베이스에서 많이 쓰죠. 트리가
너무 커서 램에 전부 저장하지 못하는 경우에도 사용합니다.

HashTable은 메모리를 많이 쓰는 대신, 액세스를 상수시간에 할 수 있도록
만든것입니다.

### Inductive thinking ~ recursion
Inductive thinking은 크기가 다른 문제들 사이의 관계를 파악하여, 전체 문제를
해결하려는 사고방식.

> 세살버릇이 여든까지 간다는걸
수학적 귀납법으로 어떻게 증명할까요?
세살에 버릇이 있음을 증명하고,
올해 가진 버릇이 내년에 없어지지 않음을 증명하면
되겠죠?

> 하지만 반대로 여든에 버릇이 있음을 보이고, 올해 버릇이 있었다면 작년에도
버릇이 있었음을 보여도 되겠죠?

```rust
fn factorial(n: int): int {
    if n == 1 { 1 }
    else { n * factorial(n-1) }
}
```

그래서 알고리즘 수업을 가면 이 내용이 *Dynamic Programming*이라는 이름으로 더욱
심화되어 나옵니다.

> 시험은 오픈북입니다. 여러분들이 아직 서울대 입시경쟁에서 헤어나오지 못했기
때문에, 오픈북을 안하면 여러분들이 책에있는 내용을 달달 외우기만 하려고 해요.
제가 아무리 그런거 안나온다고 해도 이 자료구조의 특징 일곱가지 있으면 앞글자만
따서 달달 외웁니다. 그래서 오픈북으로 합니다.

<p align=right>2주차는 일식보느라 빠짐 ...</p>

<p align=right>3주차 (3월 14일) ...</p>

알파고 이야기를 조금 함.

> 알파고 거 봐라 한번 지지 않느냐 알파고 단점이 어떠어떠하다.

구조적 프로그래밍의 중요성에 대해 설명하심.

> 구조적 프로그래밍 잘하는거 중요하다. 예전에 내 제자가 병특해서 회사가서 코딩하는걸 봤는데 함수 안쓰고 매크로만 쓰는걸 자랑처럼 이야기하더라. 그렇게하니까 변수 하나 고치니까 400라인 고쳤다고 하더라. 문서화 잘하는것도 코딩의 일부다. 코딩만 잘한다고 되는게 아니다.

#### Big-Oh Notation
알고리즘 수행시간의 **상한**이다. 상한이기때문에, 어떤 알고리즘의 *O( )*을
구하라 이런 문제가 나오면 엄청 크게 쓰면 무조건 맞음.

저거 외에 빅오메가(하한), 빅세타(상한+하한)이 있음

#### Binary Search
