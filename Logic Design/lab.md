Week 1
========
매주 과제가 나가고, 다음주 전까지 해야한다. `LDLAB_YYMMDD_team#_NAME_학번` 포맷의 이름을 써달라. 문서는 PDF로 만들어달라. 보고서는 짧을수록 좋다. 최대 2장 추천.

이메일을 보낼때엔 `[LDLAB]`를 제목에 붙여달라, 학생이 누구인지 구별할 수 있는 정보를 이메일에 포함시켜달라.

실습이 끝난 뒤, 테이블이 정리정돈이 안되어있는 등의 행동이 있으면 1스트라이크를 받는다. 3스트라이크가 쌓이면 해당 랩은 20% 감점.

나는 27조.

### 첫 실습
매 실습을 할때마다 실제 PCB 기판을 만드는건 너무 비싸고 시간이 오래 드니, Breadboard와 Universal Board라는 만능기판으로 프로토타이핑을 할것이다.

Breadboard는 기판 내부적으로 와이어링이 되어있다. Universal board는 납땜과 와이어링을 직접 해줘야한다.

NAND, NOR와 같은 Logic Gates 또한 사용하게될것이다.

컴퓨터 시뮬레이션도 할것이다. Schematic Design과 Hardware Description Language(HDL)를 다룰것임

그리고 바이러스가 잠잠해지면 FPGA 보드로도 실습을 할것이다.

### Breadboard
가로로 연결된 부분들과 세로로 연결된 부분들이 있음. 빨간 가로선은 양극, 파란 가로선은 음극으로 쓰는 컨벤션이 있음. 실제로 납땜을 해보기 전에 빵판에서 편리하게 테스트를 할 수 있다.

전선 벗기기! 어렵다!

IC Chip extractor: 손으로 뽑으면 재사용이 불가능해질 수 있으니 이런걸 써요.

https://www.tinkercad.com 웹기반 빵판 홈페이지인데, 이걸로 실습을 대체할것이다!

학교에서 채점용 계정을 나눠줄텐데, 연습은 개인계정을 만들어서 하세요. 채점용 계정의 닉네임은 비밀번호나 다름없으니 닉네임은 잘 보관하세요.

숙제:
1. DC Power Supply, Multimeter, Function Generator, Oscilloscope 네개를 각각 간략하게 설명하세요
2. 저항이 색깔에 따라 어떤 의미를 갖는지 설명해주세요

프로젝트, 숙제와 보고서는 모두 개인이고 팀은 실습시간을 위해서만 있는것이다.

&nbsp;

Week 2
========
TinkerCad로 아래 두개의 실습을 하면 갈 수 있다.

1.  빵판에서 Pull-up and pull-down resistor 구현하기. 330Ohm 저항 사용이 권장되며, 인버터와 LED로 테스트하라. 입력 전압은 Multimeter로 체크
2.  빵판에서 Half adder 구현하기. LED로 정상동작여부를 확인하고, 주석(comment)으로 input과 output을 문서화하라.

풀업 레지스터와 풀다운 레지스터는, 플로팅 상태가 된 회로의 전압을 정규화하기 위해 사용한다. 인터넷에 [설명글이 많으니](https://kocoafab.cc/tutorial/view/526) 참고.

숙제

1.  TinkerCad Breadboard로 1-bit full adder 구현하기
2.  TinkerCad Breadboard로 2-bit full adder 구현하기
3.  PPT에 있는 서킷 다이어그램의 Truth table 만들기
4.  PPT에 있는 서킷 다이어그램을 NOT 1개, AND 2개, OR 1개만으로 표현하기. Logisim을 활용하라.
