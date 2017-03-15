Stack Calculator
========
[숙제 페이지](http://soar.snu.ac.kr:8080/assignments/3) |
[FAQ](http://soar.snu.ac.kr/course/board/ds2016/1623076)

> **Note!** 여기엔 코드가 Java 8로 짜여져있지만, 당시엔 Java 7 코드가 아니면
> 채점을 해주지 않았어서 실제 과제 제출은 Java 7 코드로 이뤄졌었다. Java 7 버전
> 소스코드를 보고싶으면 [`0a9eb4c1`] 클릭.

[`0a9eb4c1`]: https://github.com/simnalamburt/snucse/tree/0a9eb4c16b029c981fd73e9cc44ff650f4d324e0/Data%20Stucture/Stack%20Calculator

```bash
# Execute program
make run

# Automatic test
make test

# Remove build results
make clean
```

Description
--------
본 프로그램은 크게 아래 세 단계를 거쳐 실행된다.
만약 아래의 세 단계중 하나라도 문제가 생기면, `ERROR`만을 출력하고 그 외에 어떤
메세지도 출력하지 않는다.

1.  **Tokenizing** - 스트링을 토큰들로 나눈다.
2.  **Parsing** - 토큰들로 식을 파싱한다. 이 때 내부적으로 infix인 수식을
    postfix로 변환한다.
3.  **Evaluation** - Stack을 써서 postfix expression을 실행한다.

위의 세 단계를 거쳐서, 입력이 하나 주어지면 아래의 두 결과를 출력한다.

- Infix Expression을 Postfix Expression으로 변환한 결과
- 그리고 그 수식을 계산한 결과

### 1. Tokenizing
주어진 문자열을 토큰들로 나눈다. 사용되는 글자는 모두 아래와 같다.
아래의 목록에 있지 않은 글자가 주어진경우, 에러를 낸다.

`0`, `1`, `2`, `3`, `4`, `5`, `6`, `7`, `8`, `9`,
`+`, `-`, `*`, `/`, `%`, `^`, `(`, `)`, <code> </code><sup>(space)</sup>, `\t`

토크나이징은 <code> </code><sup>(space)</sup>와 `\t`, 두 공백문자를 써서
이뤄지며, 이 공백문자들은 파서에게 전달되지 않는다.
그리고 `0`...`9`에 해당하는 숫자들의 경우, 공백문자로 구분되지 않았을 경우
하나의 토큰으로 붙어서 파서에게 전달된다. 숫자의 규칙은 아래와 같다.

```bnf
 <digit> ::= "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
<number> ::= <digit> | <digit><number>
```

> **Note**: FAQ를 보면 입력이 0으로 시작하지 않는다고 주어지긴 했지만, 스펙에
> leading-zero는 에러로 처리해야한다는 규정이 있는것도 아니고, leading-zero가
> 있다고해서 계산에 문제가 생기는것도 아니어서 받아들이기로 하였습니다.

### 2. Parsing
아래의 규칙에 맞춰서 재귀하향파서를 구현하였다.

```bnf
         <expr> ::= <term> | <term> <add-op> <expr>
         <term> ::= <signed-factor> | <signed-factor> <mult-op> <term>
<signed-factor> ::= <factor> | "-" <signed-factor>
       <factor> ::= <element> | <element> "^" <factor>
      <element> ::= "(" <expr> ")" | <number>

       <add-op> ::= "+" | "-"
      <mult-op> ::= "*" | "/" | "%"
```

괄호의 짝이 맞지 않는 등의 틀린 문법으로 인해 파싱이 불가능할경우 에러를 낸다.

파서는 위의 규칙대로 Infix Expression을 파싱하여, Postfix Expression으로
변환하여 Evaluator에게 넘겨준다. 이때 Postfix Expression의 문법은 아래와 같다.

```bnf
  <postfix> ::= <number>
              | <postfix> " " <postfix> " " <binary-op>
              | <postfix> " " <unary-op>

<binary-op> ::= "+" | "-" | "*" | "/" | "%" | "^"
 <unary-op> ::= "~"
```

Infix Expression에선 `-`가 쓰이는 위치에 따라 binary operator일수도 있고, unary
operator일수도 있었지만, Postfix Expression에서의 `-`는 무조건 binary
operator이고, unary operator는 `~`로 표시된다.

### 3. Evaluation
Postfix Expression을 받아, 스택을 사용하여 실행한다. 구현방법은 자명하므로
생략한다.

이때 Divide by zero 등의 이유로 실행이 불가능한 수식이 Evaluator에게 전달되었을
경우, 에러를 낸다. 실행이 불가능한경우는 아래 세가지이다.

- `n 0 /`
- `n 0 %`
- `0 <음수> ^`

여기서 특기할만한 점은, 스펙상 `0 0 ^`을 `1`로 처리해야한다는 점이다.

> **Note**: Evaluation 단계에서 에러가 발생한경우, 실행이 불가능한것이지 파싱은
> 가능하므로 postfix expression을 출력한 뒤 ERROR를 발생한다고 생각할 수 있지만,
> 그래선 안된다. FAQ 참고.
