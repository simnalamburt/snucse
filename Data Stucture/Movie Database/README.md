# MovieDatabase

이 문서는 2016년 1학기 자료구조 과제 2번을 수행하기 위한 몇 가지 팁을 제공한다.

## Skeleton

주어진 스켈레톤 코드는 코드를 구조화할 수 있는 한 가지 방법을 보여주고 있다.
과제를 완료하기 위해 `FIXME`로 표시된 부분의 코드를 채워 넣는 것으로 동작하는 프로그램을 만들 수 있다.
필요하다면 `FIXME`로 표시되지 않은 부분에 코드를 추가하는 것도 가능하다.
스켈레톤 코드는 과제를 시작하는 시작점을 제공할 뿐이다.

빠른 피드백 루프를 위해 테스트를 단계별로 수행하는 것이 유용하다.
이를 위해 일부 테스트 코드가 `AssignmentGuide.java` 파일에 제공되어 있다.

## Compilation and Execution

### Compilation

컴파일은 아래와 같이 할 수 있다.

```
javac *.java
```

### Execution

과제 채점은 다음과 같이 이루어진다.

```
java MovieDatabaseConsole
```

### Test

과제 코드를 작성하며 도움이 될만한 테스트 몇 개가 준비되어 있다. 이는 아래와 같이 실행한다.

```
java -ea AssignmentGuide
```

`-ea` 옵션은 `assert` 문을 사용하기 위해 필요하다.

### Eclipse

이클립스에서 스켈레톤 코드를 임포트하는 방법은 아래와 같다.

- File - New Project
- Java - Java Project - Next
- Project name을 정한다 - 적당한 Location을 정한다 - Project layout의 Use project folder as root for sources and class files을 선택한다 - Next
- Finish
- 프로젝트 이름 (가령 MovieDatabase) 우클릭 - Import
- General - File System
- From directory에서 스켈레톤 코드가 위치한 디렉토리를 선택한다 - `.java` 파일을 모두 선택한다 - Finish

## Usage

반드시 수정해야 하는 파일 목록은 아래와 같다.

- `MovieDB.java`
- `Node.java`

기초적인 링크드리스트는 `MyLinkedList`에 구현이 되어있다. 이를 참조하여 `MovieDB`를 완성할 수 있다.

## Contributors

This project is contributed by the following people (in order of contribution).

- stania <stania.pe.kr AT gmail DOT com>
- shurain <shurain AT gmail DOT com>
- wookayin <wookayin AT gmail DOT com>
- ipkn <ipknhama AT gmail DOT com>
