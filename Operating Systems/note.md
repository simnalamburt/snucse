Week 1, Tue
========

ETL은 많이 안쓸거고 학교 홈페이지를 확인해주세요. 그리고 프로젝트 제출 용도로 https://sys.snu.ac.kr 서버를 쓸 예정이니 참고.

선수과목으로 논리설계, 컴퓨터구조, 시스템프로그래밍을 미리 듣고오세요. C, Linux, gcc, gdb, make, 어셈블리, RISC-V를 잘 익혀오세요. 수업 듣는데에 리눅스 혹은 macOS 머신이 필요합니다.

**이번 학기는 RISC-V 머신 위에서 돌아가는 OS를 만든다!**

### What is an OS?
하드웨어(CPU, Memory, IO) 위에서 곧바로 동작하면서 Application들을 위한 System call을 노출하면 뭐든지 OS다.

OS는 하드웨어를 여러 Application들이 공유할 수 있도록 나눠주는 역할도 하고, Application들이 하드웨어에 직접 접근하지 못하게 막는 역할도 한다.

새로운 하드웨어를 만들어서 동작하게 만들으려면 OS를 반드시 공부해야해요. OS를 더 낫게(기능 개선, 성능 개선, 신뢰성, 에너지 효율성) 만들으려면 OS를 배워야해요. 나 젊을적에는 OS 수업시간에 굉장히 추상적인 이야기만 하고 OS 코드를 제대로 보지도 않았는데, 요즘은 OS가 실제로 굉장히 중요한 문제가 되었어요. 당장 스마트폰을 만들어서 유저들에게 가져다 팔으려고 하기만 해도, 스마트폰에 있는 엑시노스같은 다양한 칩들을 다루는 OS가 필요해요.

OS-aware 하드웨어를 설계할때에도 OS를 배워야해요. 하드웨어와 소프트웨어를 따로 만드는 시대는 지났어요. 어디까지를 하드웨어로 할지, 어디까지를 소프트웨어로 할지를 결정해야해요. 예를들어 요즘 신경망 가속화 하드웨어를 만드는 일을 많이하는데 여기에서도 어디까지를 하드웨어로 할지 잘 결정하려면 OS를 공부해야해요.

여러분이 짠 헬로월드 소프트웨어가 정확히 어떤 과정을 통해서 여러분의 모니터에 출력되는지 정확하게 알기 위해서도 OS를 배워야해요.

Linux Torvalds, "Just For Fun", 재미로 배울수도 있어요

### Textbook
Operating Systems: Three Easy Pieces, http://ostep.org 에서 무료로 제공. 오픈소스 도서이다 https://github.com/remzi-arpacidusseau/ostep-projects 제목이 Three Pieces인 이유는? 리처드 파인만의 "Six Easy Pieces"라는 책에 영감을 받아, OS는 물리학보다 반정도 어려운것같으니 세 조각으로 이름을 붙였다.

약간 구버전인 0.91버전을 기준으로 한국어 번역도 존재하니 참고 https://github.com/remzi-arpacidusseau/ostep-translations

OSPP 라는 책도 참고하셈 http://ospp.cs.washington.edu/ 전병곤교수님 OS 강의는 이 책으로 함

MINIX 제작자가 만든 https://en.wikipedia.org/wiki/Modern_Operating_Systems 라는 책도 있어요.

시스템프로그래밍 공부가 필요하다면 CSAPP http://csapp.cs.cmu.edu/ 이 책 뒷부분도 참고하세요. 챕터 8 프로세스, 챕터 10 파일시스템을 주로 보시면 됨.

### Course Plan
강의 토픽은 주로 세개를 다룬다. 케이스 스터디로 Linux와 xv6를 다룬다.

- Virtualization: 프로세스, CPU 스케줄링, 버추얼메모리
- Concurrency: 스레드, 동기화
- Persistence: 스토리지, 파일시스템

프로젝트는 MIT에서 개발된 [xv6]의 멀티코어 RISC-V 버전으로 한다. xv6는 Sixth Edition Unix (v6)의 ANSI C 버전 포트인데, 원래는 멀티코어 x86 용 OS이다.

[xv6]: https://github.com/mit-pdos/xv6-public

교육용 OS가 아니라 오래 전에 쓰였던 역사적인 실제 OS로 공부하게될것이다! 27m LoC를 자랑하는 리눅스와 다르게 라인수가 6k 정도이다. QEMU로 쉽게 설치할 수 있다.

### 프로젝트
4~5개의 개인 프로젝트를 준비중이다. 5개의 "slip days"를 사용할 수 있음. 한학기동안 과제를 늦게 내출할 수 있는 총 5일의 여유가 있음. 프로젝트는 뒤로 갈수록 배점이 높아진다.

시험을 하나라도 안보면 F가 나간다. 2/3 이상 출석을 안하면 F가 나간다. 치팅도 F

임베디드 시스템, 클라우드 컴퓨팅, 분산 시스템, 보안 등 OS는 컴퓨터 연구개발 전반에 쓰이는 지식이에요. 역사적으로 OS는 힘든 과목으로 알려져있으니 각오하세용. Happy hacking!

### Why OS? What is an OS?
LAPD 경찰차를 보면 항상 [To protect and to serve](https://en.wikipedia.org/wiki/To_protect_and_to_serve) 라는 글자가 붙어있다. OS도 이것과 비슷하다. Application을 Protect하고 Serve한다.

Software that converts hardware into a useful form for Application.

OS도 소프트웨어다. OS는 CPU 점유율이 높지 않아야한다. 대부분의 CPU는 Application이 쓸 수 있도록 양보해야함.

OS가 항상 있어야하는건 아니다. 컴퓨터 안에 있는 어플리케이션을 모두 믿을 수 있을때엔 OS를 넣지 않을수도 있다. Application을 믿을 수 없을때엔 OS가 필요함. App으로부터 App을 보호하기도 해야하고, App으로부터 OS를 보호하기도 해야함.

리눅스 코드가 엄청 많다고 했는데, 사실 코드의 대부분은 Device Driver다. 하드웨어가 너무 많아서 그거 다 대응하느라 필요함.

#### Application 관점에서 본 OS
Application이 돌아갈 수 있는 환경을 제공해줘요. 그리고 CPU나 메모리와 같은 하드웨어들에 대한 abstract view를 제공해줘요.
- Processors → 프로세서와 스레드로 추상화
- Memory → Address space (virtual memory)로 추상화
- Storage → Volumes, Directories, Files로 초상화
- I/O Devices → Files (+ioctls)
- Networks → Files (sockets, pipes, ...)

&nbsp;

Week 1, Thu
========

#### System 관점에서 본 OS
CPU, RAM, IO 장치 등의 자원들을 여러 Application이 쓸 수 있게 나눠줘요

- Sharing
  - Time multiplexing: 시분할 공유. CPU 스케줄링, 등
  - Space multiplexing: 공간분할 공유. 버추얼메모리, 하이퍼스레딩, 등

공유할때에 중요한거

- Protection: 다른 프로세스의 메모리를 볼 수 있으면 안됨, 주어진것보다 더 많은 메모리를 쓸 수 있으면 안됨, etc
- Fairness: Starvation이 일어나면 안됨, etc
- Efficiency

#### Implementation 관점에서 본 OS
OS is highly-concurrent, event-driven software.

이벤트에는 두 종류가 있어요

- System calls: 어플리케이션에서 Trap 명령어로 호출하는 이벤트. 유저가 OS에 요청하는것
- Interrupts: 하드웨어 이벤트

이벤트들이 수도 많고, 동시에 발생하고, 처리하는 도중에 아무때나 발생하기때문에 굉장히 어렵다.

요즘은 어플리케이션에서도 멀티스레딩을 하지만, OS는 태초부터 컨커런시를 지원해야만 했기때문에, 스핀락이나 락같은 스레드 동기화기술들은 대부분 OS를 위해 처음 만들어진것들이다.

### OS의 역사
#### 처음엔 운영체제가 없었음
1세대 (1945 ~ 1955) 컴퓨터, 진공관과 Plugboard로 프로그래밍하던 시절. OS 없음, PL 없음, 어셈블리어도 없음

#### Batch System
2세대 (1955 ~ 1965) 컴퓨터, 트랜지스터와 메인프레임으로 프로그래밍하던 시절

- Batch System: One job at a time
- 천공카드, Tape drives, Line printers 사용
- OS는 메모리에 항상 상주하며, 거의 실행되지 않았다. 하는일이 거의 없기때문. IO가 병목이었기때문에 CPU는 underutilized 되었음

#### Multiprogramming system
3세대 (1965 ~ 1980) 컴퓨터, Integrated circuit(집적회로)가 만들어져서 컴퓨터가 싸지고 빨라짐, 디스크 드라이브도 발전함, On-line terminals도 생김

하드웨어 호환을 유지하기위해 "Computer Architecture"라는 개념이 처음 나옴. IBM System/360 Family, ISA 스펙이 정의된 처음의 컴퓨터

Multiprogramming systems이 등장함. IBM OS/360 (1964), 여러사람이 job을 submit하고 이 job들이 아주아주 긴 Queue에 등록되어있다.

이시절에 천공카드 코딩할때에 위에 마크를 해서 카드를 한곳에 쌓아놨을때에 정렬되었다는걸 바로 알 수 있게 하는게 중요한 노하우였다. 잘 안눌리는 글자 구멍 잘뚫는것도 노하우였음. Queue가 너무 기니까 하나 제출하고 다음날에 확인해봤더니 에러 하나 떠있고, 또 제출했더니 다음날에 다른 에러 하나 떠있고 이러는게 일상이었음.

이시절 OS의 기능

- Job scheduling
- 메모리 관리
- CPU 스케줄링
- 컨커런시
- Protection
- Spooling (Simultaneous Peripheral Operation On-Line): 출력하는동안 컴퓨터가 계속 프린터에 block되어있지 않아도 됨

#### Time-sharing system
Time-sharing systems가 등장함. 응답시간이 훨씬 좋아짐. MIT CTSS (1961), Multics (1965), Unix (1969), 등. 우리가 쓰고있는 OS의 거의 대부분의 기능은 이 시점에 개발되었다.

- 복잡하고 미세한 CPU 스케줄링
- 가상메모리, 스와핑
- 파일시스템
- 동기화
- IPC (프로세스간 통신)
- Interactive shell
- 더 많은 보호, etc

#### Modern OS
4세대 컴퓨터 (1980 ~ now), 마이크로프로세서(LSIs & VLSIs)가 나오면서 더 작고 빨라짐. 스토리지도 더 좋아짐. PC의 시대. GPU같은 I/O 장치들이 CPU의 계산을 돕기시작함

- GUI
- 멀티미디어
- 인터넷 & 웹
- 모바일, 네트워킹, 분산
- 가상머신, etc

### 유명한 OS들
- CTSS (1961, MIT)
  - Compatible Time-Sharing System
- OS/360 (1964, IBM)
- MULTICS (1965, MIT + Bell Labs + General Electric)
- Unix (1969, Bell Labs)
  - MULTICS를 탈퇴하고 나와서 만든 OS

#### MULTICS
- MULTiplexed Information and Computing Service
- Time-shared, Multi-processor 메인프레임. OS 대신 "Computing Facility"라는 말을 씀
- 너무 비싼 하드웨어(GE-645, 36비트 시스템)를 요구하고, 개발기간도 너무 늘어나서 실패함
- 2000-10-31 에 마지막 멀틱스가 꺼짐
- 멀틱스 때에 거의 대부분의 OS 기술들이 다 나옴
- Hierarchical file system: ACL, 긴 이름, 하드링크, 심볼릭 링크, Quota, 등
- Virtual memory, 세그멘테이션, 페이징
- User-level command shell
- 동적링킹, 공유메모리
- High-level language 구현 (PL/1), BCPL, APL, 포트란, 리습, C, 코볼, Algol, 파스칼 지원
- Logical Disk - Physical Disk 매핑
- Multics Relational Data Store (MRDS), Spreadsheets
- NSCS B2 등급 받음
- https://www.multicians.org/ 멀틱스 팬들이 있음

#### UNIX
MULTICS에서 Bell Labs가 탈퇴한 다음, MULTICS에서 돌아가던 Space travel이라는 게임을 연구소에 있던 DEC PDP-7라는 작은 머신에서 돌리고싶었다. MULTICS에서 기능을 많이 뺐다(emasculated)는 의미로 UNICS라고 이름을 붙였고 UNIX로 이름이 바뀜.

켄 톰슨의 아내가 캘리포니아로 휴가를 갔을때, OS짜는데에 1주, 셸 짜는데에 1주, 에디터 짜는데에 1주, 어셈블러 만드는데 1주 이렇게 한달만에 UNIX를 만듦

- Hierarchical file system
  - Special files, Everything is file description: Uniform I/O, naming, and protection
  - Removable file systems: mount/umount
  - i-node
- 프로세스 컨트롤
  - Fork, exec, wait, exit 등
  - Pipes for IPC
- 셸
  - Standard I/O, I/O 리디렉션
  - 필터, 커맨드 separators, 셸 스크립트
- 시그널

1973년 버전 4부터 C로 재작성됨. UNIX 가계도는 https://en.wikipedia.org/wiki/History_of_Unix#/media/File:Unix_history-simple.svg 참고

정식 UNIX 라이센스를 갖고있는 버전이 System-V 로 개발됨. 그리고 무료버전의 개발이 이어져서 만들어진것이 BSD계열, BSD 개발자들이 만든 상용 OS가 SunOS, Solaris.

네덜란드의 앤드루 타넨바움 교수가 교육용으로 Minix를 만들었고, 이것을 보고 다시 만들어진것이 리누스 토르발즈의 Linux.

Windows도 유닉스의 영향을 받았다고들 말한다. DEC이라는 회사에서 VMS라는 유닉스를 만들었었는데, 이 VMS 개발자들을 뽑아서 만든것이 Windows NT다. 그래서 초창기 Windows NT 메뉴얼은 VMS 메뉴얼과 이름만 다를정도로 유사했다.

Windows Desktop은 막장OS였지만 Windows NT는 굉장히 안정적이었다. 그래서 우스개로 흔히들 Windows Desktop과 머지되기 직전의 Windows NT가 제일 안정적이었다고들 함

#### Multics vs Unix
멀틱스
- 탑다운 어프로치
- 디자인&시스템프로그래밍에 150 Man-year, 기능개선을 위해 50 Man-year
- 너무 복잡하고 너무 비싼 하드웨어를 요구함
- 중요한 OS의 아이디어는 다 만들어졌다

Unix
- 바텀업 접근
- 2 Man-year: 단순함, 엘레강스함, 사용하기 편함
- Low cost hardware, 널리 adopt됨
- 현대 OS의 뿌리

첫번째 과제 나옴: https://github.com/snu-csl/os-pa1
