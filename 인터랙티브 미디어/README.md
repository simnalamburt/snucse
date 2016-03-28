인터랙티브 미디어
========
**14조** ― 김지현, [norang](https://github.com/norangLemon)
```bash
# Prerequisites
brew install platformio
brew cask install fritzing
```
- **[아두이노를 파괴하는 10가지 방법](http://arduinomidi.com/xe/BlogBoard/2167)**
- 전자부품 쇼핑몰 ― [센서], [쉴드] <sup>[쉴드란?]</sup>
- [하드카피월드][hdcp] ― 재밌는 글들이 많이 올라옴.
    - [DIY 스마트워치](http://www.hardcopyworld.com/ngine/aduino/index.php/archives/376)

[센서]: http://eleparts.co.kr/front/productlist_morning.php?code=005
[쉴드]: http://eleparts.co.kr/front/productlist_morning.php?code=017031017000&listnum=&sort=&block=&gotopage=
[쉴드란?]: https://ko.wikipedia.org/wiki/%EC%95%84%EB%91%90%EC%9D%B4%EB%85%B8#.EC.89.B4.EB.93.9C
[hdcp]: http://www.hardcopyworld.com/

**Note** 쉴드를 쓸경우, 한 핀에 입력이 여러개 들어갈경우 아두이노 기판이 손상될
수 있다. 조심해야함.

<br>

<br>

<br>

<p align=right>3주차 (3월 14일) ...</p>

#### 아두이노
> 자기를 믿지 마세요. 기계*(테스터기)*를 믿으세요.

전기에 대한 설명을 열심히 하고계심. 난 전전회를 들었으니 건성건성 들어야지.
도체, 부도체, 그라운드, 직류, 교류 이야기하시는중

- Terminal Strip
- Bus Strip: 전원공급

아두이노의 전원에는 두가지 종류가 있다.
- USB 전원. 외부 어댑터가 없을때에만 쓰임. 저용량 (5V, 500mA)
- 외부 어댑터 전원. 용량이 훨씬 큼. (7~12V, 0.5~4A)

<p align=right>4주차 (3월 21일) ...</p>

시리얼 통신에 대한 설명을 해주심. 8bit 단위의 통신. 구시대의 유물이라고 한다.

스위치를 받았다. 이걸로 유저입력을 받을 수 있음.

기본적인 IO 연습을 해보았음

<p align=right>5주차 (3월 28일) ...</p>

- 포텐시오미터 써보기
- LED 써보기

LED 사용할때에, 저항 없이 바로 연결하지 않도록 주의! 칩마다 주어진 허용
전압/전류를 체크하자
