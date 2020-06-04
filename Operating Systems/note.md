Week 1, Tue
========

ETL은 많이 안쓸거고 학교 홈페이지를 확인해주세요. 그리고 프로젝트 제출 용도로 https://sys.snu.ac.kr 서버를 쓸 예정이니 참고.

선수과목으로 논리설계, 컴퓨터구조, 시스템프로그래밍을 미리 듣고오세요. C, Linux, gcc, gdb, make, 어셈블리, RISC-V를 잘 익혀오세요. 수업 듣는데에 리눅스 혹은 macOS 머신이 필요합니다.

**이번 학기는 RISC-V 머신 위에서 돌아가는 OS를 만든다!**

&nbsp;

### 1. What is an OS?
하드웨어(CPU, Memory, IO) 위에서 곧바로 동작하면서 Application들을 위한 System call을 노출하면 뭐든지 OS다.

OS는 하드웨어를 여러 Application들이 공유할 수 있도록 나눠주는 역할도 하고, Application들이 하드웨어에 직접 접근하지 못하게 막는 역할도 한다.

새로운 하드웨어를 만들어서 동작하게 만들으려면 OS를 반드시 공부해야해요. OS를 더 낫게(기능 개선, 성능 개선, 신뢰성, 에너지 효율성) 만들으려면 OS를 배워야해요. 나 젊을적에는 OS 수업시간에 굉장히 추상적인 이야기만 하고 OS 코드를 제대로 보지도 않았는데, 요즘은 OS가 실제로 굉장히 중요한 문제가 되었어요. 당장 스마트폰을 만들어서 유저들에게 가져다 팔으려고 하기만 해도, 스마트폰에 있는 엑시노스같은 다양한 칩들을 다루는 OS가 필요해요.

OS-aware 하드웨어를 설계할때에도 OS를 배워야해요. 하드웨어와 소프트웨어를 따로 만드는 시대는 지났어요. 어디까지를 하드웨어로 할지, 어디까지를 소프트웨어로 할지를 결정해야해요. 예를들어 요즘 신경망 가속화 하드웨어를 만드는 일을 많이하는데 여기에서도 어디까지를 하드웨어로 할지 잘 결정하려면 OS를 공부해야해요.

여러분이 짠 헬로월드 소프트웨어가 정확히 어떤 과정을 통해서 여러분의 모니터에 출력되는지 정확하게 알기 위해서도 OS를 배워야해요.

Linux Torvalds, "Just For Fun", 재미로 배울수도 있어요

#### Textbook
Operating Systems: Three Easy Pieces, http://ostep.org 에서 무료로 제공. 오픈소스 도서이다 https://github.com/remzi-arpacidusseau/ostep-projects 제목이 Three Pieces인 이유는? 리처드 파인만의 "Six Easy Pieces"라는 책에 영감을 받아, OS는 물리학보다 반정도 어려운것같으니 세 조각으로 이름을 붙였다.

약간 구버전인 0.91버전을 기준으로 한국어 번역도 존재하니 참고 https://github.com/remzi-arpacidusseau/ostep-translations

OSPP 라는 책도 참고하셈 http://ospp.cs.washington.edu/ 전병곤교수님 OS 강의는 이 책으로 함

MINIX 제작자가 만든 https://en.wikipedia.org/wiki/Modern_Operating_Systems 라는 책도 있어요.

시스템프로그래밍 공부가 필요하다면 CSAPP http://csapp.cs.cmu.edu/ 이 책 뒷부분도 참고하세요. 챕터 8 프로세스, 챕터 10 파일시스템을 주로 보시면 됨.

#### Course Plan
강의 토픽은 주로 세개를 다룬다. 케이스 스터디로 Linux와 xv6를 다룬다.

- Virtualization: 프로세스, CPU 스케줄링, 버추얼메모리
- Concurrency: 스레드, 동기화
- Persistence: 스토리지, 파일시스템

프로젝트는 MIT에서 개발된 [xv6]의 멀티코어 RISC-V 버전으로 한다. xv6는 Sixth Edition Unix (v6)의 ANSI C 버전 포트인데, 원래는 멀티코어 x86 용 OS이다.

[xv6]: https://github.com/mit-pdos/xv6-public

교육용 OS가 아니라 오래 전에 쓰였던 역사적인 실제 OS로 공부하게될것이다! 27m LoC를 자랑하는 리눅스와 다르게 라인수가 6k 정도이다. QEMU로 쉽게 설치할 수 있다.

#### 프로젝트
4~5개의 개인 프로젝트를 준비중이다. 5개의 "slip days"를 사용할 수 있음. 한학기동안 과제를 늦게 내출할 수 있는 총 5일의 여유가 있음. 프로젝트는 뒤로 갈수록 배점이 높아진다.

시험을 하나라도 안보면 F가 나간다. 2/3 이상 출석을 안하면 F가 나간다. 치팅도 F

임베디드 시스템, 클라우드 컴퓨팅, 분산 시스템, 보안 등 OS는 컴퓨터 연구개발 전반에 쓰이는 지식이에요. 역사적으로 OS는 힘든 과목으로 알려져있으니 각오하세용. Happy hacking!

#### Why OS? What is an OS?
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

#### OS의 역사
##### 처음엔 운영체제가 없었음
1세대 (1945 ~ 1955) 컴퓨터, 진공관과 Plugboard로 프로그래밍하던 시절. OS 없음, PL 없음, 어셈블리어도 없음

##### Batch System
2세대 (1955 ~ 1965) 컴퓨터, 트랜지스터와 메인프레임으로 프로그래밍하던 시절

- Batch System: One job at a time
- 천공카드, Tape drives, Line printers 사용
- OS는 메모리에 항상 상주하며, 거의 실행되지 않았다. 하는일이 거의 없기때문. IO가 병목이었기때문에 CPU는 underutilized 되었음

##### Multiprogramming system
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

##### Time-sharing system
Time-sharing systems가 등장함. 응답시간이 훨씬 좋아짐. MIT CTSS (1961), Multics (1965), Unix (1969), 등. 우리가 쓰고있는 OS의 거의 대부분의 기능은 이 시점에 개발되었다.

- 복잡하고 미세한 CPU 스케줄링
- 가상메모리, 스와핑
- 파일시스템
- 동기화
- IPC (프로세스간 통신)
- Interactive shell
- 더 많은 보호, etc

##### Modern OS
4세대 컴퓨터 (1980 ~ now), 마이크로프로세서(LSIs & VLSIs)가 나오면서 더 작고 빨라짐. 스토리지도 더 좋아짐. PC의 시대. GPU같은 I/O 장치들이 CPU의 계산을 돕기시작함

- GUI
- 멀티미디어
- 인터넷 & 웹
- 모바일, 네트워킹, 분산
- 가상머신, etc

#### 유명한 OS들
- CTSS (1961, MIT)
  - Compatible Time-Sharing System
- OS/360 (1964, IBM)
- MULTICS (1965, MIT + Bell Labs + General Electric)
- Unix (1969, Bell Labs)
  - MULTICS를 탈퇴하고 나와서 만든 OS

##### MULTICS
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

##### UNIX
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

&nbsp;

Week 2, Tue
========
### 2. Architectural Support for OS
컴퓨터에 특정 기능이 있다면 OS를 훨씬 효율적으로 만들 수 있다. 아키텍처가 OS를 위해 어떤 서포트를 해줘야하는지 알아보자

#### Issue 1. I/O
컴퓨터에는 IO장치가 무지 많이 달려있다. 각 IO장치는 CPU와 별개로 컨커런트하게 동작하며, IO장치별 버퍼가 따로 존재한다. CPU는 I/O장치를 위한 특별한 명령어를 실행시켜주고, 주기적으로 메인메모리와 I/O 로컬 버퍼 사이의 데이터를 옮겨줘야함.

CPU는 귀중한 자원이기때문에 I/O장치를 처리하다가 CPU를 너무 많이 낭비하면 안됨. I/O를 어떻게 하면 효율적으로 처리할 수 있을까?

##### Interrupt
- Polling
- Interrupt

I/O가 완료되었는지, I/O장치에 입력된 데이터 등을 알아내려면, CPU가 I/O 장치를 지속적으로 점검해야한다 (Polling) 근데 이러면 CPU가 I/O장치 확인하느라 시간을 너무 많이 써야해서 비효율적임.

하드웨어 인터럽트가 있으면 I/O가 CPU를 깨울 수 있다. 이러면 CPU가 I/O를 주기적으로 폴링할 필요가 없어짐. 그리고 인터럽트도 효율적으로 받기 위해 CPU 바깥에 Interrupt controller를 따로 붙임. I/O 장치는 Interrupt controller에 인터럽트를 보내고, 인터럽트 컨트롤러가 CPU에 인터럽트를 한번에 하나씩 보내는 방식으로 동작함.

CPU에도 exception을 처리하는 기능이 존재함. Divide by zero 혹은 IIllegal instruction같은게 있기때문에. 파이프라인의 맨 마지막 단계에서 매번 익셉션이 발생했는지 체크하고, 익셉션이 있었다면 프로그램 카운터를 바꿔서 미리 지정한 코드를 실행시키는 기능이 존재하고 이런걸 Exception handling이라고 함.

Interrupt Handling도 익셉션이랑 매우 비슷하게 동작함. 파이프라인의 맨 마지막 단계에서 매번 익셉션이 존재하는지 체크할뿐만 아니라 인터럽트가 존재했는지도 체크함. 인터럽트가 있었다면 실행중이던 파이프라인을 버리고, state(스택, 레지스터, 등)을 모두 저장함. 어느 디바이스가 인터럽트를 만들었는지 (인터럽트 유형이 뭔지) 알아냄. 그 다음 Interrupt service routine(ISR) 혹은 인터럽트 핸들러로 실행흐름을 옮김.

인터럽트가 있었을때 누가 인터럽트를 발생시켰는지도 알아내야함.

- Polling
- Vectored interrupt system

누가 인터럽트를 걸었는지 각 I/O장치별로 체크할수도 있지만 (Polling) 비효율적임. 그래서 인터럽트를 걸 때 누가 인터럽트를 걸었는지 정보도 CPU에 같이 알려주는 Vectored interrupt system이 필요함.

##### Data Transfer Modes
- Programmed IO
- Direct Memory Access (DMA)

제일 무식한 방법으로는 CPU가 I/O장치의 버퍼에 있는 메모리와 RAM에 있는 데이터를 주기적으로 교환해주는 방법이 있을것이다. 근데 이러면 CPU가 낭비하는 시간이 너무 커짐. 그래서 DMA가 필요함

메모리 복사를 CPU가 직접하는게 아니라 DMA Controller가 메모리 복사를 함. CPU가 DMA Controller에게 요청을 하여, CPU가 안보고있을때 IO장치의 메모리와 RAM의 내용물을 교환해줌. 메모리 입장에선 CPU가 읽어가는건지, DMA가 읽어가는건지 알 수 없음.

예시: SATA. SATA Controller 안에 DMA controller가 들어있음.

1.  CPU가 Z370 Chipset에 read command를 날림. (Chipset은 IO장치가 달라붙는 장치임. 옛날에는 IO장치는 죄다 칩셋에 붙었었는데, 요즘은 PCIe같은게 생겨서 CPU에 IO 장치들이 직접 붙음)
2.  Chipset이 SATA controller를 통해 디스크에 read command를 enqueue하고, 큐가 잘 되었다는 ACK을 받는다.
3.  SATA Controller가 CPU에게 커맨드 큐가 잘 되었다는 ACK을 전달한다.
4.  디스크가 읽기작업을 시작한다
5.  디스크는 읽기작업의 결과물을 디스크 내부의 Buffer에 저장한다
6.  디스크가 SATA Controller에 읽기가 끝났다는 사실을 Notify한다
7.  DMA setup
8.  디스크가 RAM에 작업 결과물을 DMA한다.
9.  SATA Controller가 CPU에 인터럽트를 보내, I/O가 끝냈다는 사실을 공지한다.

I/O 유형들마다 DMA Controller가 따로 존재한다. SATA같은경우는 메인보드의 SATA Controller에 DMA Controller가 들어있고, NVMe같은경우 SSD가 외부 도움 없이 자체적으로 DMA를 할 수 있다.

결론: 아키텍처는 OS를 위해 인터럽트를 지원해야한다!

#### Issue 2. Protection
유저가 시스템을 망치는것을 어떻게 막을것인가? 여기에선 하드웨어의 도움이 반드시 필요해진다.

- Application이 디스크에 직접 접근하려고하면 어떻게 막을것인가?
- Application이 HLT(CPU를 멈추는 명령어)를 실행하는것을 어떻게 막을것인가?

"Protected or privileged instructions"들이 따로 정의되어있다. ALU 명령어, 로드 스토어, 브랜치 점프같이 유저가 실행해도 되는 명령어들과 다르게 유저가 실행하지 못하게 막혀있는 명령어들임.

- `HLT` 명령어
- Direct I/O에 필요한 명령어들, x86의 `in`, `out` 같은것들
- 특별한 시스템 레지스터들도 유저가 쓰지 못하게 막혀있음. Control registers, System table locations, Special bits
- Memory state management도 유저가 쓰지 못함. Page table updates, page table base address, TLB loads, etc

Modes of Operation. CPU가 현재 저런 privileged instructions를 실행할 수 있는지 없는지 상태를 구분시킬 필요가 있어서 만들어졌음. 최소 Kernel mode, User mode 이렇게 두개의 모드가 필요함.

- IA-32: 네개가 존재함. Ring 0 > 1 > 2 > 3. Ring 0이 커널모드, Ring 3가 유저모드. Ring 1과 2는 잘 안씀
- ARM: 네개가 존재함. EL3 > EL2 > EL1 > EL0
- RISC-V: 세개가 존재함. Machine > Supervisor > User, Machine 모드는 부팅직후에만 잠깐 쓰고 Supervisor를 커널모드로 씀.

현재 모드가 뭔지 알아내는법

- IA-32: Current Privilege Level (CPL) in CS register
- ARM: CPSR 레지스터의 Mode 필드
- RISC-V: 없음

옛날에 커널을 아무리 잘 짜도 커널에 붙는 디바이스 드라이버때문에 컴퓨터가 죽는 경우가 많았음. 그래서 디바이스 드라이버의 권한을 축소시키려고 Ring 1, Ring 2같은게 만들어졌음. 근데 굉장히 복잡하고 성능이 안좋아서 이렇게 세밀하게 권한을 구분하는 경우가 적음. 윈도우와 리눅스 모두 두 모드만을 사용함.

커널의 엄밀한 정의: 커널모드로 실행되는 코드를 커널코드라고 한다.

결론: 아키텍처는 OS를 위해 커널모드, 유저모드 구분을 나눠줘야한다!

#### Issue 3. Servicing Requests
이렇게 유저모드/커널모드 구분을 통해 유저가 아무것도 하지 못하게 막고, 시스템콜을 통해서만 일을 할 수 있게 만들어놨다. 시스템콜을 어떻게 만들까?

A system call is a protected procedure call. 시스템콜은 호출하는순간 CPU가 커널모드로 바뀌기 때문에 조심해야한다. 유저가 이상한 입력을 시스템콜로 보내면 다 잘 걸러내도록 커널을 구현해야함.

CPU에선 시스템콜을 어떻게 구현할까? Exception으로 구현함. 인터럽트랑 처리과정이 똑같음. 실행하면 콜러의 상태(레지스터, mode bits)를 저장한 뒤, 커널모드로 바뀌고 커널코드의 핸들러로 점프한다. 이런 일을 하는 특별한 익셉션을 "OS Trap"라고 부름.

##### Exceptional Events
-   Interrupts
    - 하드웨어에 의해 생긴것
    - IA-32에선 INTR 시그널이나 NMI 핀으로 발생함
    - Asynchronous
-   Exceptions
    - 소프트웨어에 의해 발생함
    - Unintentional exception: Divide by zero, ...
    - Intentional exception: IA-32의 `int 80h` 혹은 `syscall` 명령어, RISC-V의 `ecall`
    - Synchronous

RISC-V에선 인터럽트가 오던 익셉션이 오던 한곳으로 점프하게된다. 그래서 거기에서 익셉션이 있었던건지 인터럽트가 있었던건지 구분해야함.

##### Exceptions in x86
Exception, interrupt, fault, trap, abort 등 비슷한걸 뜻하는 용어들이 여러개 있는데 x86에선 이 단어들을 잘 정의해놨다.

-   Trap
    - Intentional
    - ex: System call, breakpoint, 그 외 특수한 명령어들
    - `next` 명령어로 제어흐름을 반환함
-   Fault
    - Unintentional & possibly recoverable
    - ex: Page faults (recoverable), protection faults (unrecoverable), 등
    - `current` 명령어로 폴트를 다시 일으키거나 abort하게됨
-   Abort
    - Unintentional & Unrecoverable
    - ex: 패리티 에러, 머신 체크, 등
    - 정말 심각한 상황을 부름

이 단어는 CPU마다 용어가 다르니 유의하자.

&nbsp;

Week 3, Thu
========
시스템콜을 구현해보자!

유저는 정해진 프로토콜에 따라 지정된 레지스터에 파라미터들과 시스템콜 번호를 입력한 뒤, `ecall` 명령어를 실행한다.

`ecall` 명령어가 실행되면 Trap Handler가 실행됨. Trap Handler의 주소는 `stvec` 레지스터에 미리 지정이 되어있어야한다. 시스템콜이 끝난 뒤 돌아갈 장소의 주소가 어딘가에 저장이 되어야 하는데, 이건 `sepc`(Supervisored Exception Program Counter) 레지스터에 저장됨. (`mepc`, `hepc`라고 Machine Exception Program Counter, Hypervisor Exception Program Counter는 또 따로 있음)

문제는 RISC-V와 같은 경우 OS Trap이든, 소프트웨어 익셉션이든 (divide by 0, illegal instruction, ...) 하드웨어 인터럽트든 모두 같은 Trap Handler로 진행하기떄문에, 이걸 구분해주는 작업을 먼저 해야한다.

Trap Handler가 호출되면 일단 모든 유저의 레지스터들을 Trap Frame에 저장한다. 그럼 이제부터 모든 레지스터들은 커널이 사용할 수 있다. 그리고 `scause`라는 레지스터에 Trap Handler가 호출된 원인이 저장되어있는데, 그걸 읽는다.

`scause`를 읽어서 원인이 시스템콜이었을 경우, Systemcall Table을 읽는다. Systemcall Table에는 각 시스템콜별로 어느 커널 함수를 호출해주면 되는지가 씌여있다.

시스템콜이 끝난 뒤엔 Trap Frame으로부터 유저의 레지스터들을 복구한 뒤, 프로그램 카운터를 `sepc`에 저장되어있는 주소로 복구시켜서 유저 코드로 돌아간다. 이걸 손으로 하는게 아니라 `sret`이라는 명령어를 쓴다. `sret`을 쓰면 프로그램 카운터가 복구되면서 CPU 모드가 유저모드로 바뀌게된다.

결론: 아키텍처는 OS를 위해 Trap 명령어를 만들어줘야한다!

#### Issue 4. Control
OS가 시간을 많이 쓰면 안좋은게 맞긴 한데, OS도 소프트웨어이기때문에 중간중간 OS가 CPU시간을 써야한다. OS도 휴먼이야 휴먼

근데 유저프로세스가 시스템콜도 안부르고, 인터럽트도 없이 유저프로세스가 무한루프를 돌면 어떻게될까? 다른 프로세스들에 스케줄링도 못해주고 컴퓨터가 Hang된다! 안돼!

OS가 CPU를 유저한테 주는건 쉽다. 다시 뺏어오는건 어렵다. 어떻게 뺏어올 수 있을까?

1.  Cooperative Approach

    유저 프로세스가 주기적으로 `yield()`같은 시스템콜을 호출하게 해서 알아서 양보하게 시키기. 프로세스의 협조가 필요하다. 프로세스가 협조하지 않고 양보를 전혀 안해주면..? 으앙

    타이머 하드웨어가 없을때엔 이런 접근을 써야함. 임베디드 환경과 같이, 컴퓨터 안에 돌아가는 모든 소프트웨어를 직접 작성하는 경우에는 이런 접근을 많이 씀.

    Can be used when OS trusts user applications.

2.  Non-cooperative Approach

    CPU 밖에 타이머 하드웨어를 둬서, 주기적으로 무조건 하드웨어 인터럽트가 발생하도록 세팅한다! 프로세스의 협조가 필요 없다.

타이머는 privileged자원이여서 OS만 사용할 수 있게 세팅한다. 그리고 OS는 타이머에 미리 어느 주기로 인터럽트가 발생할지 주기를 세팅한다. Linux 2.4는 10ms, Linux 2.6은 1ms, Linux 5.5는 4ms, xv6는 10ms.

어떤 프로그램이 무한루프에 빠졌는지 안빠졌는지 판단하는건 굉장히 어려운 문제에요. Halting Problem이라고 들어보셨나요? 옛날에 삼성에서 무한룹에 빠진 앱 죽이는거 가능하냐고 물어본적도 있었는데 어려웠다.

결론: 아키텍처는 OS를 위해 타이머 하드웨어를 줘야한다!

#### Issue 5. Memory Protection
어플리케이션이 아무 메모리를 쓸 수 있으면 안된다. 어떻게 하면 좋을까?

어플리케이션이 메모리 액세스도 시스템콜로 한다면? 매우 느릴것이다 ㅠ

간단한 접근: CPU에 special한 레지스터 두개를 둔다. `base` 레지스터에 접근할 수 있는 메모리의 시작주소가 써있고, `limit` 레지스터에 접근할 수 있는 메모리의 끝 주소가 써있다. 그리고 OS는 유저 어플리케이션을 실행할때마다 레지스터에 "이 어플리케이션은 어느 메모리까지 접근할 수 있다"를 지정해준다. 이렇게 하면 OS의 개입 없이도 CPU가 금지된 메모리 액세스를 빠르고 효율적으로 막아준다. 간단한 임베디드 환경에선 이렇게 구현한다.

실제로는 접근할 수 있는 메모리 영역이 연속적이진 않기때문에 Virtual Memory를 쓴다. MMU(Memory Managemnt Unit)에서 privileged option을 지원한다.

결론: MMU가 있어야하고, MMU가 메모리 권한제어도 해줘야한다!

#### Issue 6. Synchronization
여러 인스트럭션들이 아토믹하게 실행되게 하고싶다. 락을 어떻게 구현하면 좋을까?

싱글코어 CPU에서는 그냥 잠깐 인터럽트를 껐댜 켜면 그게 락이다. 멀티코어에선 이 접근을 쓸 수 없다.

스핀락을 구현하면 되긴 하는데 이러면 오버헤드가 엄청나기때문에 하드웨어의 Atomic 명령어가 필요하다.

- Read-Modify-Write (INC, DEC)
- Test-and-Set
- Compare-and-Set
- LOCK in IA-32
- LL (Load Locked) & SC (Store Conditional) in MIPS

RISC-V에는 "A" instruction set이 있다.

- LR(Load Reserved) & SC(Store Conditional)
- AMO (Atomic Memory Operation)

#### 요약
좋은 OS를 만들으려면 CPU 아키텍처의 도움이 필요하다. (MS-DOS/8086에서 멀티프로세싱 하기?)

CPU 아키텍처의 도움이 있으면 OS를 훨씬 간단하고 효율적으로 만들 수 있다. (인터럽트, DMA, 아토믹, ...)

대부분의 유명한 OS들은 이런 아키텍처 서포트를 염두에 두고 만들어져있다.

- SPARC 위의 SunOS/Solaris
- PPC 위의 IBM AIX
- PA-RISC 위의 HP-UX

두번째 과제: `setpgid`, `getpgid` 시스템콜 구현하기! https://github.com/snu-csl/os-pa2 참고

대부분의 UNIX에는 프로세스 그룹이라는게 있어서 pgid를 고치고 읽는게 가능한데, xv6에는 지금 그 기능이 없다. 이걸 만들어보자.

그리고 지금 xv6에선 <kbd>Ctrl</kbd>+<kbd>P</kbd>를 누르면 현재 실행중인 프로세스 목록이 찍힌다. 그떄 PID뿐만 아니라 PGID도 같이 찍히게 만들면 된다.

setpgid 호출하는 프로그램 유틸리티로 만들어져있으니 그걸로 테스트하면 된다.

&nbsp;

### 3. Process
여러분들 다 아시죠? 후루룩 빠르게 넘어갑시다

What is a Process? An instance of a program in execution. 그리고 Protection의 최소단위이기도 하다.

자바로 비유하면 Class : Object = Program : Process.

프로세서별로 고유한 정수 ID인 PID가 있어야한다. 그리고 프로세스별로 CPU context, address space, open file table, 등등을 따로 가진다.

&nbsp;

Week 3, Tue
========
프로그램에는 Code와 Data가 들어있다. 프로그램이 실행되면 프로그램이 모두 메모리에 올라가서 Code와 Data가 램에 상주하게되고, Heap 메모리와 Stack 메모리가 생기게 된다. Program Counter 레지스터는 Code 영역중에서 현재 실행중인 장소를 가리키고, Stack Pointer 레지스터는 현재 스택의 맨 위가 Stack 영역중에서 어디인지를 가리킨다. 프로세스의 실행은 Mem[PC]를 Fetch하고, Decode하고, Execute한 뒤 PC를 Update하는 과정의 연속이다. 멀티스레드 프로그램일 경우 스택이 여러개가 됨.

근데 실제로는 한 코어가 여러개의 프로세스를 interleave하게 실행할 수 있어야한다. 한 코어가 여러 프로세스를 왔다갔다하며 실행할 수 있어야함. OS는 한정된 자원인 CPU를 여러 프로세스에 분배시켜주면서, 각각의 프로세스에는 각 프로세스가 자신만의 한개의 CPU를 가진것처럼 동작하도록 해주는데 (virtualizing the CPU) 이를 스케줄링이라고 한다.

#### Process Hierarchy
UNIX에선 `fork()`로만 프로세스를 만들 수 있다. (fork 동작원리, 사용법, 구현방법 생략) fork는 한번 호출되고 두번 리턴되는 함수.

포크로만 프로세스를 만들기때문에 프로세스들끼리 부모자식 관계가 생긴다. (Process Hierarchy) Process Group도 만들 수 있음.

`exec()`은 현재 실행중인 프로세스를 다른 프로세스로 변신시켜주는 함수. 한번 호출되고, (에러를 제외하면) 리턴되지 않는 함수.

UNIX에서 새 프로세스를 실행하려면 fork()를 부른 뒤 exec()을 호출해야한다. 왜 UNIX에선 프로세스를 만들때에 fork()와 exec()을 두번 하게 만들었을까? 이게 사실 되게 생각하고 만든거다. fork()와 exec()를 나눴기때문에 자식 프로세스가 로딩되기 전에 IO를 파이프한다던가 하는 행위가 가능함.

윈도우는 fork()로 프로세스를 만드는것도 아니고, 프로세스 그룹이라는 개념도 없음. 윈도우에는 CreateProcess가 있는데 fork()와 exec()을 합친것.

왜 윈도우는 이렇게 대충배우나요? 전세계에서 생산되는 인텔 CPU 비율이 얼마일까? 2~3%밖에 안됨. 윈도우도 마찬가지임. 일반 사용자용 OS나 윈도우가 많고 심지어 요즘은 스마트폰 때문에 일반 사용자용 조차도 UNIX가 더 많다. 윈도우 몰라도 돼요.

김진수 교수님께선 vi를 좋아하신다!

#### Process Termination
프로세스가 죽는 경우

- 자발적으로 꺼지는 경우
- 에러나 발생해서 자발적으로 꺼지는 경우
- OS에 의해 비자발적으로 죽는 경우
  - Segmentation Fault, 잘못된 메모리 접근
  - Protection Fault
  - Exceeded allocated resources
  - etc
- 다른 프로세스에 의해 죽임당하는 경우
  - Signal을 받은 경우

Zombie process: Terminated, but not removed. 모든 리소스들(메모리, 오픈 파일, 등)을 다 반환해서 죽은거나 다름이 없는 상태이고, 왜 죽었는지 정보만 남아있음. `waitpid()` 이런 시스템콜을 써서 parent나 다른 프로세스들이 그 프로세스가 왜 죽었는지 정보를 읽어가면 좀비가 사라짐. 자식 프로세스가 죽으면 `SIGCHILD` 시그널이 발생한다. 저걸 써서 `waitpid()` 처리를 효율적으로 할 수 있다.

#### Process State Transitions
Time slice, Time quantum: 프로세스가 실행될 수 있는 허용된 최대의 시간.

Process는 항상 아래의 세 state중 하나를 가진다

- Ready
  - 실행될 수 있는 상태
  - Ready state인 프로세스들은 Ready Queue에 들어가서, 스케줄링의 대상이 된다.
  - 프로세스가 생성된 직후에 이 상태가 된다
- Running
  - 실행중인 상태. 시스템 콜 때문에 커널 코드를 실행중인 프로세스도 Running 상태이다.
  - 이 상태에 너무 오래 머물러서 Time slice를 모두 소진하면 (time slice exhausted) OS가 실행을 멈추고 Ready 상태로 돌려버린다.
- Blocked
  - 프로세스가 IO를 하거나 이벤트를 기다리느라 Block되어버리면 이 상태가 된다
  - Blocked 상태인 프로세스들은 Ready Queue에서 빠져서, 스케줄링되지 않는다.
  - IO가 끝나거나 대기가 끝나면 다시 Ready 상태로 넘어간다.

보통 Time slice가 Timer inturrupt의 주기(tick 주기)의 배수이다.

#### Process 구현하기
Process Control Block(PCB) 혹은 Process Descriptor에 그 프로세스에 관한 모든 정보가 있어야한다. 하나의 PCB는 하나의 프로세스

- CPU 레지스터
- PID, PPID, PGID, priority(nice), 프로세스 상태, 시그널, 등
- CPU 스케줄링 관련 정보
- 메모리 관리 관련 정보
- Accounting information: CPU 사용량이 얼마인지, IO를 얼마나 했는지 등의 통계
- File management 관련 정보
- I/O 상태 관련 정보
- Credentials: 프로세스들이 갖고있는 접근권한들. UID, GID.

리눅스 4.15.0-91 기준으로 `struct task`의 크기는 6016 바이트. xv6의 `struct proc`은 360바이트. OS 입장에선 프로세스 하나 만드는게 부담이 큰 일이다.

#### Context Switch
한 코어가 실행하던 프로세스에서 다른 프로세스로 넘어가는 과정. 컨텍스트 스위치가 많아지면 Administrative overhead가 커지기때문에 가능한 한 아껴야함.

- 레지스터들, 각종 메모리 맵들 저장/복구하기
- TLB와 같은 메모리 Cache Flush/리로딩하기
- 각종 테이블과 리스트들 업데이트하기

하드웨어마나 컨텍스트스위치 오버헤드가 다르다.

- UltraSPARC에선 레지스터 셋이 여러개가 있어서 함수 호출할때의 레지스터 저장/리로드 오버헤드는 비교적 적었지만, 레지스터가 너무 많아서 컨텍스트 스위치 오버헤드는 오히려 늘었다.
- Advanced memory management 기술을 적용한 경우 컨텍스트 스위치를 할때에 저장해야하는 정보가 늘어날 수 있다.

컨텍스트 스위치는 보통 1초에 수백번에서 수천번 일어난다. 커널모드에 있더라도 컨텍스트 스위치가 발생한다. 이 횟수는 70~80년대와 크게 차이가 없다. 이정도 횟수면 사람이 작업이 동시에 느껴진다고 느끼기에 충분해서, 더 많이 할 필요가 없음.

커널 안에선 Atomic한 실행이 필요하거나 락이 필요한 경우를 위해, 잠시 컨텍스트 스위치를 막아주는 기능을 쓸 수 있음.

xv6에선 레지스터들을 trapframe에 저장함. Trapframe이 왜 있는가? 요즘은 유저모드일때 접근 가능한 메모리와 커널모드일때 접근 가능한 메모리를 완전히 나누는게 유행이다. 각종 CPU 취약점때문에.. 근데 유저모드일때와 커널모드일때 모두 접근 가능한 메모리 영역이 Trapframe임.

트램폴린 페이지: 커널이 유저모드의 프로세스에 데이터를 전달할 일이 있을때 쓰는 작은 메모리 영역

&nbsp;

Week 3, Thu
========
컨텍스트 스위치 회수 세는법

```bash
# 컴퓨터가 부팅된 이후 흐른 시간을 초로 표현한것
awk '{print $1}' /proc/uptime
# 컴퓨터가 부팅된 이후 있었던 컨텍스트 스위치 횟수
awk '/^ctxt/ {print $2}' /proc/stat

# 아래 숫자를 코어 수로 나누면 코어당 컨텍스트 스위치 횟수가 나옴
python <<< "print( \
  $(awk '/^ctxt/ {print $2}' /proc/stat) / \
  $(awk '{print $1}' /proc/uptime) / \
  $(awk '/^cpu cores/ {print $4}' /proc/cpuinfo | uniq)
)"
```

xv6에서의 컨텍스트 스위치 과정

1.  시간이 지나 하드웨어로부터 Timer interrupt가 발생함
2.  RISC-V
    - PC 백업함: `sepc ← pc`
    - 인터럽트 비활성화
    - 커널모드로 전환시킴
    - `stvec`에 있는 트랩 핸들러로 점프
3.  xv6
    - 유저 레지스터를 A의 트랩프레임에 저장
    - 커널 페이지 테이블로 바꿈
    - 프로세스 A를 Runnable 상태로 바꿈
    - 프로세스 B를 Running 상태로 바꿈
    - B의 컨텍스트를 PCB로부터 읽어옴
4.  xv6
    - 유저 페이지 테이블로 바꿈
    - 유저의 레지스터를 B의 트랩프레임으로부터 읽음. 이 과정에서 `sepc`가 프로세스 B의 것이 되기때문에, 트랩 프레임을 종료하면 프로세스 B로 시작하게된다.
    - `return-from-trap` 실행, 트랩 핸들러 종료
5.  RISC-V
    - 유저모드로 바꿈
    - PC 복구함: `pc ← sepc`
6.  프로세스 B가 실행되기 시작한다!

컨텍스트 스위칭을 당한 프로세스들 입장에선, 인터럽트가 와서 다른것들을 처리하다가 온 것 처럼 느껴짐.

OS는 켜져있는 모든 프로세스들의 상태를 나타내는 큐들을 관리해야한다

- Ready Queue, Runnable Queue: 스케줄링될 준비가 된 프로세스
- Wait Queues: Device, Timer, Message등 이벤트 유형마다 Wait Q가 하나씩 존재한다

각 PCB는 항상 현재 상태를 나타내는 하나의 큐에 들어가있어야한다. 프로세스의 상태가 바뀌면 큐를 바꿔야한다.

#### `fork()` 구현하기
- 새 PCB를 만들고 내용물 초기화
- 새 Address Space 만들고 초기화
- Address Space의 내용물들을 부모 프로세스의 것을 보고 모두 복사하는 방식으로 초기화
- Open Files와 같은 커널 리소스들도 부모 프로세스의 것을 보고 모두 같은 곳을 가리키도록 초기화
- PCB를 ready queue에 넣음
- 레지스터를 조작하여, 부모 프로세스에선 자식프로세스의 PID를 리턴하고, 자식 프로세스에선 0을 리턴함

#### `exec()` 구현하기
- 현재 프로세스를 멈춤
- 새로 실행할 프로세스의 Address Space를 로드함
- 새 프로그램을 위한 하드웨어 컨텍스트와 `args`를 초기화함
- PCB를 ready queue에 넣음

`exec()` 함수는 에러가 난 경우에만 리턴한다.

#### Policy vs Mechanism
OS 분야에서 Policy와 메커니즘이라는 용어가 쓰이는데, 의미를 구분하여 사용하므로 주의해야한다.

- Policy, 정책
  - 무엇이 일어나야 하는가
  - 모든 자원 할당과 스케줄링을 할때에 항상 정책이 있어야한다.
  - ex: Priority가 항상 제일 높은 프로세스를 스케줄링해주자
- Mechanism, 메커니즘
  - 어떻게 해야하는가
  - 이 정책들을 어떻게 구현할것인가를 의미함
  - ex: 그러려면 PCB에 priority 정보가 있어야하고, priority queue같은 자료구조를 OS 내에 구현해야한다.

OS 디자인의 핵심철학이 "Separating Policy from Mechanism"이다. Policy는 해결하고싶은 문제나 workload에 따라 변할 수 있다. 메커니즘은 최대한 General하게 만들어서 Policy가 변한다고 OS 코드가 바뀌지 않게 만들면, 모듈러한 OS를 만들 수 있다.

&nbsp;

### 4. CPU Scheduling
스케줄링: 컨텍스트 스위치가 일어나서 프로세스 하나가 일시중지되었다. 이제 뭘 켤까? 에 대한 정책

스케줄링은 아주 빠르게 해야함. 스케줄링은 자주 일어나기때문에 빨리 끝내야한다.

- Scheduling Policy: 언제 전환할까? 누구로 전환할까?
- Scheduling Mechanism: 어떻게 전환할까?

#### Basic Approaches
- Non-preemptive scheduling, Cooperative scheduling
  - 프로세스가 자발적으로 yield할때까지 스케줄링이 발생하지 않음
  - 프로세스의 협조가 필요함
- Preemptive scheduling
  - 스케줄러가 실행중인 프로세스를 강제로 멈추고 컨텍스트 스위칭을 강제할 수 있음

실행되는 모든 프로세스를 믿을 수 있고, 하드웨어 지원이 작은 임베디드 기계에선 Cooperative scheduling도 쓰기도 하나 보통은 Preemptive scheduling을 씀

Preemptive scheduling에선 이런 문제가 발생함

- 공유 데이터를 업데이트 하던 도중 preempt 당하면 어쩌지?
- 시스템 콜이 preempt 당하면 어쩌지?

용어 정리

- Workload: Job의 descriptions들. Arrival time, Run time, 등
- Scheduler: Job이 언제 실행될지 결정시켜주는 로직
- Metric: Scheduling이 얼마나 잘되고있는지를 측정하기 위해 사용하는 Measurement. Turnaround time, response time, fairness, 등

#### FIFO
만약 워크로드에 아래와 같은 가정이 걸려있다면 어떤 스케줄링 알고리즘이 제일 좋을까? (사실 내용을 보면 말도안되는 가정인데 문제를 단순화하기 위해 하는거임)

1.  각 job들은 같은 시간만큼 실행된다
2.  모든 job들은 같은 시간에 도착한다
3.  시작하면, 끝날때까지 실행된다
4.  모든 job들은 CPU만 씀 (IO 안함)
5.  각 job이 얼마나 실행될 예정인지 (run time) 이미 알고있음

메트릭은 Turnaround Time이다. `T_turnaround = T_completion - T_arrival`

이러면 FIFO가 제일 좋다.

먼저온거 먼저 처리하기. 도착하는 순서대로 스케줄링됨. 마치 슈퍼마켓 계산대에서 줄을 선 사람들처럼. 새치기가 불가능하므로 Non-preemptive이고, 모두 언젠가는 실행되므로 Starvation이 없다.

단점: Convoy effect: 맨 앞놈이 너무 느리면 그 다음 job들이 단체로 느려진다

#### SJF: Shortest Job First
Assumption 1 relaxed: 만약 각 job들이 실행되는 시간이 각각 다르면 어떤게 제일 좋을까? SJF가 제일 좋다

가장 빨리 실행되는 job을 가장 먼저 실행함. 이렇게 할때의 Turnaround Time이 가장 작다는게 증명이 가능하다.

단점: Starve 가능성이 있다

#### (Non work-conserving scheduler)
Assumption 2 relaxed: 만약 job들이 모두 동시에 도착하는게 아닐경우 어떻게 될까? 이경우 SJF가 최적해가 아니게된다.

Job들이 도착하는 시간이 모두 같지 않을경우 어떻게 하면 될까? 긴 job이 도착할경우 짧은 job이 도착할수도 있으니 잠깐 일을 안하고 기다리는것도 방법이다. 이렇게 노는 시간을 허용하는가에 따라 스케줄러를 아래의 두개로 분류하기도 한다

- Work-conserving scheduler: 항상 일을 하는 유형의 스케줄러, 보통 이거
- Non work-conserving scheduler: 어떤 이유로든 노는 시간을 허용하는 스케줄러

#### STCF: Shortest Time-to-Completion First
Assumption 3 relaxed: 만약 Preemption이 가능하다면 어떤 정책이 제일 좋을까?

가장 빨리 끝나는 작업 먼저. 새 Job이 도착했을 때, 새 Job이 원래 Job보다 더 빨리 끝난다면 새 Job으로 preempt해버린다.

#### (New metric in time sharing system)
요즘은 제출하고 끝날 때 까지 기다리는게 아니라, 타임 셰어링 시스템이기 때문에 Turnaround Time은 부적절한 메트릭이 되었다. 그러면 어떤 메트릭이 제일 좋을까? Response Time이다. `T_response = T_firstrun - T_arrival`

#### RR: Round Robin
FIFO의 Time Sharing 버전. 원형 FIFO Queue를 만들어서 그냥 모든 job을 순서대로 실행한다.

각 Job은 허용된 time slice(=Scheduling Quantum를 갖는다. 모든 Job이 다 똑같은 Time Slice를 실행한 뒤 다음 잡으로 넘어감.

- Timer-interrupt period 혹은 Timer tick의 정수배
- 너무 짧으면: 스케줄링 오버헤드가 커짐
- 너무 길면: Response Time이 커짐
- 보통 10 ~ 100ms

Preemptive하고, 공평하게 실행하므로 Starvation이 없다.

RR은 SJF보다 Turnaround Time이 높지만, Response Time이 훨씬 좋기 때문에 Time-sharing 시스템에 좋다.

&nbsp;

Week 4, Tue
========
#### Static/Dynamic Priority Scheduling
Job들마다 static/Dynamic priority를 갖고있다.

Dynamic Priority는 `nice()`, `renice()`, `setpriority()`, `getpriority()` 등의 함수로 런타임에 priority를 바꾸는게 가능함. UNIX에선 nice 값이 기본이 0이고 [-20, 20) 으로 총 40개의 단계를 갖고있음. 스스로 Priority를 낮추는것은 가능하나, Priority를 올리려면 관리자 권한이 있어야만 한다.

가장 Priority가 높은 Job을 다음에 실행함. Round-Robin과 FIFO는 모든 프로세스의 Priority가 동일한 것이라고 볼 수 있음.

Preemptive하게 만들수도 있고, Non-preemptive하게 만들수도 있다.

Starvation problem: 높은 Priority의 Job이 끝없이 제공되면, 낮은 Priority의 Job은 절대 실행되지 못한다!

#### Incorporating I/O
Assumption 4 relaxed: 중간중간에 I/O를 한다면 어떻게될까?

프로세스는 CPU를 많이 쓰는 CPU-bound process와 IO-bound process가 있다. IO-bound process는 Interactive Process와 Non-interactive process로 나뉨

IO때문에 프로세스가 멈춰있는동안 다른 프로세스를 실행해도 문제가 없다. 한 프로세스가 CPU-burst 하는 시간과, I/O-burst 하는 시간을 구분해 둘을 독립된 job으로 취급하자. 한 프로세스가 I/O를 하느라 점유되어있는 시간동안 다른 job을 실행하면 됨.

ex: I/O-aware STCF, 프로세스가 I/O를 하는동안 다른 job을 실행하고있다가, I/O가 끝나면 원래 job으로 돌아옴.

#### Towards a General CPU Scheduler
Assumption 5 relaxed: 현실에선 Job들이 실행되는 시간을 미리 알 수 없다.

목표

1. Turnaround Time 최소화
2. Interactive Job들은 Minimize response time

그리고 CPU를 놀게두지말고, 최대한 CPU를 Utilize 해야한다. 스케줄러가 어떻게 특정 프로세스가 Interactive Process인지, Non-interactive process인지 등의 특징을 구분할 수 있을까? 과거의 행동을 모니터링해서 유추한다.

이 경우엔 어떻게 만들어야할까?

#### MLFQ: Multi-Level Feedback Queue
각 Priority Level별로 여러개의 Queue가 존재함. 가장 높은 Priority Queue부터 차례대로 실행하고, 같은 Priority에 Job이 여럿 있으면 같은 Priority끼리는 Round-Robin 한다. 가장 높은 Priority Queue가 비어야 다음 Job이 실행될 수 있다.

규칙

1. Priority(A) > Priority(B) 이면, A가 실행되고 B는 실행되지 않는다.
2. Priority(A) == Priority(B) 이면, A와 B는 Round-Robin으로 실행됨.

Priority는 스케줄러가 Job의 행동을 보고 다양하게 메겨준다. Priority를 어떻게 메겨주면 될까.

대부분의 Job은 아래 두 유형중 하나이다.

- Interactive Jobs: 짧게 실행되고, 빠른 응답속도를 요구함
- CPU-intensive Jobs: 긴 CPU 시간을 요구하고, 응답속도가 별로 중요하지 않음

##### Attempt 1
- Job이 맨 처음 실행되면, 일단 가장 높은 Priority에 둠
- Time Slice가 끝나기 전에 CPU를 반환하면, Priority를 유지함 (Interactive Job인가보다)
- Time Slice가 끝날떄까지 CPU를 반환하지 않으면, Priority를 한단계씩 낮춤 (CPU-intensive Job인가보다)

얘의 문제

- Interactive Job이 너무 많으면 오래 실행되는 job은 starve할 수 있음
- Time Slice가 다 되기 전에 일부러 CPU를 놓으면, 높은 Priority가 유지됨
- Priority가 한번 떨어지면 복구가 안됨

##### Attempt 2
Attempt 1이랑 똑같이 하되 주기적으로 Priority를 초기화하면 되겠네!

Starvation은 막을 수 있을지 모르겠으나, 일부러 Priority를 유지시키는 악의적인 사용자는 막을 수 없음.

##### Attempt 3
Time Slice가 끝나기 전에 CPU를 반환했는지 안했는지 여부가 아니라, 총 실행된 시간 총합을 기준으로 우선순위를 결정한다면 어떨까

#### Summary: Unix Scheduler
실제 UNIX에선 이런식의 휴리스틱이 아주 복잡하게 붙어있음. (Many ugly heuristics for voo-doo constants)

기본적으로 MLFQ다.

- Preemptive, Dynamic Priority Scheduling
- Time-shared based on time slice
- 3~4 classes spanning ~170 priority levels (Solaris 2)
  - kernel 안에서의 priority, 유저모드에서의 priority 이렇게 class를 여러개 구분시켜놨음

Interactive Process를 CPU-bound Process보다 선호함. Starvation을 막기위해 aging 기법을 쓴다. Wait Time이 커질수록 우선순위가 올라가고, CPU Time이 커질수록 우선순위가 내려감.

Priority와 Time Slice는 서로 관계가 없어도 무방할것같은데, 많은 OS들은 Priority가 높아지면 Time Slice도 길어짐. UNIX가 그러함. 반면 Windows는 Priority를 높이는것과, Time Slice를 늘리는걸 독립적으로 할 수 있음.

&nbsp;

### Linux CFS (Completely Fair Scheduler)
리눅스의 스케줄러!

Linux 2.4: Epoch-based Priority Scheduling, O(n). 프로세스들에 식권을 하나씩 나눠주고, Priority 순서대로 실행한다. 그리고 Timer Tick마다 식권을 모두 나눠준다. 그리고 모든 프로세스의 식권이 사라지면 다시 모든 프로세스에 식권을 하나씩 준다.

Linux 2.6 ~ 2.6.22: 2.4 스케줄러와 동일한 알고리즘을 효율적으로 구현했음.

Linux 2.6.23 ~: Ingo Molnar가 CFS 구현함

스케줄링 클래스가 여러개 있는데 크게 중요하지 않음.

왜 CFS이냐? 우선순위에 정확하게 비례하게 CPU Time을 쓰게 만들어줘서.

#### Linux Task Priority
[0, 140)으로 총 140 레벨이 존재함. 작은 값일수록 높은 우선순위를 가짐.

일반 유저 프로세스는 [100, 140)의 Priority를 갖고, nice 명령어를 사용해서 이를 [-20, 20) 범위에서 조절 가능. (nice = priority - 120)

#### Proportional Share Scheduling
기본 개념: Task마다 Weight Value가 존재함. Weight에 정비례해서 CPU를 사용하게 만들고싶음.

#### Nice to Weight
리눅스 개발자는 Nice 값이 하나 차이날때마다, CPU Time이 10% 차이가 나게 해줬다.

Nice 0은 1024로 두고, Nice 1 = 820, Nice -1 = 1277 이런식으로 Nice 값마다 Weight 차이가 나게 만들었음.

#### Virtual Runtime
Nice 값이 0인 프로세스를 기준으로 실행시간을 정규화한다.

VR(T) = PR(T) * Weight0 / Weight(T) = (PR(T) * (2**32)/Weight(T) * Weight0) >> 32

- Weight0: Nice가 0인 프로세스의 Weight (1024)
- Weight(T): T의 Weight-
- PR(T): T의 실제 Runtime
- VR(T): T의 Virtual Runtime (vruntime)

Priority가 높은 Task는, vruntime이 천천히 증가하고, Priority가 낮은 Task는, vruntime이 빠르게 증가한다.

왜 2**32를 곱했다가 다시 나누나요? 커널은 가급적이면 floating point 계산을 안하려고함. floating point 레지스터를 유저랑 나눠쓰는것도 피곤하고, floating point 계산기가 없는 컴퓨터에서도 동작해야하니까.

#### Runqueue
CFS는 모든 runnable tasks를 vruntime에 따라 정렬시킨 Red-Black Tree를 관리한다. O(log N)으로 vruntime이 가장 작은 Task를 고를 수 있음. 트리 관리하는 비용 때문에 Heap을 안쓰고 RBTree를 쓴다.

새로 들어온 Task의 vruntime은 현재 모든 task의 vruntime중 가장 작은 값으로 둔다.

마찬가지로 IO같은 이유로 자다가 깨어난 프로세스들도 runqueue에서 빠졌다가 다시
들어오게 되는데, 이런 프로세스들도 minimum vruntime 값을 가지며 시작함. 다만 맨
처음 한번은 min vruntime보다 약간 작은 값으로 보정을 하는 부분이 있음.

Time Slice는 가변적임. Task가 많으면 Time Slice가 작아지고, Task가 적으면 Time Slice가 커짐.

vruntime이 작으면, 이 태스크가 실제 실제 실행되어야하는것보다 덜 실행되었다 이렇게 이해하면 됨.

CFS는 비교할때에 64bit 정수 오버플로우가 나더라도 정상적으로 동작하도록 설계해놓았다. 64bit 2의 보수가 길이 2**64 짜리 Cyclic Group이라는 성질을 사용했음. https://github.com/torvalds/linux/blob/5d30bcacd91af6874481129797af364a53cd9b46/include/linux/jiffies.h#L103 참고

과제: https://github.com/snu-csl/os-pa3

&nbsp;

Week 4, Thu
========
CFS를 하면 프로세스별로는 CPU share가 잘 맞지만, 유저별로, Session groups, cgroups 들끼리 비교해도 fair 하지는 않다. 그래서 이걸 맞춰주는 기능이 후에 추가됨.

여러 CPU에 고르게 퍼트리는 기능도 필요함. Loziet al., The Linux Scheduler: a Decade of Wasted Cores, EuroSys, 2016.

여러 CPU에 고르게 스케줄링을 할 때 가장 무식한 방법은, CPU 각각마다 Queue를 갖게하는것이다. 근데 특정 CPU에만 job이 쏠리고, 특정 CPU에는 job이 모자라고 이러면 노는 코어가 생김. 그래서 리눅스에는 각 CPU의 로드를 측정한 뒤, CPU들 사이에서 task를 옮기는 기능이 있음. 근데 이 기능이 완벽하지 않다.

&nbsp;

### 5. Virtual Memory
가상메모리의 목표

추상화

- 프로그래머들을 위해 메모리 공간을 abstract 해주자!
- 메모리 조각이 여기저기 흩어져있더라도, 프로그래머가 보기에는 하나로 붙어있는것처럼 쓸 수 있게 해주자!

ㄸㄹ랴챠두쵸

- Variable-sized request로 인한 파편화를 최소화하자. 특히 external fragmentation을 막자
- 하드웨어 서포트도 좀 받자

Protection (하드웨어 서포트가 필요함)

- 프로세스가 다른 프로세스나 OS를 망치는것을 막자
- Isolation: a process can fail without affecting other processes
- 두 프로세스가 원하면 메모리의 일부를 공유할 수 있게 만들자

커널이 쓰는 메모리도 Virtual Memory이다. 컴퓨터가 켜진 직후에는 Virtual Memory가 꺼진 상태로 시작하다가, Paging을 켜는 순간 커널이 쓰는 메모리든 유저가 쓰는 메모리든 모든 Virtual Memory가 된다. 다만 커널은 원하면 Page Table이 순서대로 기입되어있는 식으로, Physical memory를 접근할 수 있게 만들어져있다.

#### Linux Virtual Address Space의 구조
0부터 양수 방향으로 차례대로

- Read-only segment (.init, .text, .rodata)
- Read/write segment (.data, .bss)
- Run-time heap (malloc 호출해서 받은것), 힙의 경계선이 brk

메모리 맨 끝부터 음수 방향으로 차례대로

- Kernel virtual memory (코드, 데이터, 힙, 스택) 유저코드에선 볼 수 없다
- 유저 스택, 런타임에 생성됨

Meltdown attack이 있고나서, 대부분의 운영체제들이 kernel virtual memory를 단순히 못보는게 아니라 별도의 위치에 따로 잡아서 아예 유저모드에선 없어지게 만들었다.

xv6는 리눅스와 다르니 유의

각 프로세스는 모두 자기만의 가상메모리를 가짐. 가상메모리는 만드는 비용도 상당하고, Address translation 비용을 런타임에 계속 지불해야하기때문에 꽤 비싸지만, 가져다주는 이득이 너무 많아서 대부분의 컴퓨터가 쓰고있다.

가상메모리를 쓰면 Lazy Allocation이 가능함. 유저가 큰 메모리를 요구한 즉시 바로 큰 메모리를 할당해서 주는게 아니라, 일단 메모리 할당을 했다고 치고 유저가 메모리를 사용할 때 Page Fault를 일으킨 뒤 그제서야 메모리를 할당하기.

#### Static Relocation
OS가 매 프로그램을 로딩하기 전에 프로그램 안에있는 모든 메모리 주소를 바꿔쓰기

- 장점: 하드웨어 서포트 필요 없음
- 단점: Protection 수단 부재, 소프트웨어가 일단 메모리에 올라가면 address space를 바꿀 수 없음

단점이 많아 Static Relocation은 거의 안씀

#### Fixed partition
Physical Memory를 여러개의 fixed partition으로 나눈다. 그리고 각 partition마다 프로세스를 한개씩 배정한다.

파티션의 시작주소를 base register에 저장해놓아서, 프로세스가 메모리에 접근할때마다 파티션의 시작주소를 더하게 만드는 방식으로 virtual memory를 구현한다. 남의 파티션에 접근하려고 시도하면 실패하게 만든다.

파티션의 수 만큼 프로세스를 띄울 수 있다.

- 하드웨어 요구조건: base register만 있으면 됨
- 장점: 구현하기 쉬움, 빠른 context switch
- 단점: Internal fragmentation, 파티션 하나 안에 프로세스가 다 들어가지 않을 수 있음

두 종류의 Fragmentation

- External fragmentation: 프로세스 바깥의 메모리공간이 파편화되는 경우. 여러 프로세스들의 메모리 조각이 흩어져있음
- Internal fragmentation: 프로세스 안의 메모리공간이 파편화되는 경우. OS로부터 할당받은 메모리를 너무 비효율적으로 써서, 낭비되는 공간이 너무 많아짐

#### 여러 크기의 Fixed partition
60~70년대 OS인 IBM OS/MFT에서 쓰인 방식. 다양한 크기의 고정 파티션을 준비해놓고, 각자 맞는 크기의 파티션을 써요.

#### Variable Partition
IBM OS/MVT에서 쓰임. 프로세스가 원하는 크기의 파티션을 동적으로 할당해주자.

Limit Register를 두어 메모리 상한을 체크하고, Base Register를 두어 파티션을 찾아가게 만든다.

- 하드웨어 요구조건: base register, limit register
- 장점: 구현하기 쉬움, Internal Fragmentation 없음
- 단점: External Fragmentation 존재, 프로세스간 메모리 공유 불가

External Fragmentation을 해소하기위해 프로세스들을 메모리상에서 한 위치로 모아주는 compaction을 수행해야함.

#### Segmentation
애초에 프로세스에게 메모리를 보여줄 때, 연속된 한 덩어리의 메모리를 주는게 아니라 여러개의 독립된 segment를 쓰는 방식으로 보여주자.

세그먼트들은 다양한 크기를 가질 수 있고, 세그먼트들 사이의 순서는 없음. "Segment Number + Offset"이 Virtual Address가 됨

Intel CPU가 이 Segementation을 가정하고 만들어진 CPU여서, CPU에 세그먼트 관련 레지스터들이 있음. 이제는 세그멘테이션을 안쓰기때문에 노는 레지스터들이 됨

Segment table이 있어서 세그먼트별로 Base, Limit, Direction(위/아래 방향), Protection(RO/RW/실행가능 등), Valid bit 등의 정보들이 있음. Virtual Address 맨 위의 몇 비트를 Segment table을 가리키는 index로 쓰자.

- 장점
  - Sparse allocation 가능. 스택과 힙이 독립적으로 자란다!
  - Valid bit과 같은 정보로 세그먼트를 보호하기 쉬움
  - 특정 세그먼트를 공유하기 좋음
  - 각 세그먼트를 dynamic relocate할 수 있음
- 단점
  - 하나의 세그먼트는 연속적으로 붙어있어야함
  - 세그먼트 테이블이 크고 RAM에 있어야해서 느림. 캐싱을 활용해서 최적화할수도 있다
  - Cross-segment address가 어려움. 세그먼트 번호가 변한다면 어떻게 될 까?

&nbsp;

Week 5, Tue
========
요즘의 ARM에도 세그먼트 하드웨어 지원이 있음.

ARM에 크게 Cortex-A, Cortex-R, Cortex-M, 이렇게 ARM 세개가 있다. Cortex-A가 제일 High performance이고 스마트폰에 들어감. Cortex-R은 중간, Cortex-M은 제일 Low performance.

Cortex-A에는 모든 Virtual Memory 기능이 있고, Cortex-M에는 Virtual Memory 기능이 없음. Cortex-R에는 Memory Protection Unit이라는게 있어서 이것이 segmentation과 비슷한 기능을 함. Physical Memory를 몇개의 파티션으로 설정한 뒤, 파티션별로 권한을 설정시킴. Full virtual memory 기능을 탑해자면 너무 비싸서 그런 기능을 담지는 못하지만, 간단한 보호 기능을 갖고싶을때 이런걸 함.

&nbsp;

### 7. Paging
Paging이 특히 CPU의 하드웨어 서포트가 필요하다. Paging은 특히 OS와 CPU 하드웨어의 협업이 중요하므로, 어디부터 어디까지가 OS가 하는거고 어디까지가 하드웨어가 하는건지 잘 구분해서 공부해야한다.

이제부터 당분간은 하드웨어가 하는 일만 공부한다.

Virtual memory를 고정된 크기의 페이지들로 나누고, Physical memory를 같은 고정된 크기의 블록들로 나누고, 페이지와 프레임들을 1:1로 매핑한다. 크기는 보통 512B ~ 8KB로 power of 2이고, 리눅스에선 기본으로 4KB임.

가상메모리 상에선 연속된 메모리여도, Physical memory여도 연속되지 않게된다. External Fragmentation이 없어짐. 작지만 한 Page 안의 internal fragmentation은 생길 수 있는데, 페이지 크기를 줄이면 internal fragmentation은 작아진다.

OS는 모든 놀고있는 frame을 관리해야하고, 어떤 페이지가 어떤 frame에 대응되는지 page table을 관리해야함.

#### Page translation
한 페이지가 어느 프레임에 해당되는지 찾는 과정이 Page translation임.

페이지 크기가 4KB라고 치면 4KB = 2**12B이다. 메모리주소가 하나 있다고 치면, 하위 12비트는 고칠 필요가 없다. Page 주소만 바꾸면 되는거지 Page 안에서의 offset은 변하지 않으니까. 나머지 비트만 고치면 됨.

- Virtual Address = (Virtual Page Number, Offset)
- Physical Address = (Physical Frame Number, Offset)

Usually, |VPN| >= |PFN|. 하지만 i686에서 PAE 켜고 이런 상황에선 |VPN| < |PFN| 일 수 있다.

VPN을 PFN으로 매핑하는것이 Page Table이다. Page Table의 한 행은 PTE, Page Table Entry라고 부른다. OS가 관리한다.

레지스터중 하나가 Page Table의 시작주소를 가리키고있어야 한다. x86에선 `CR3` RISC-V에선 `satp` 레지스터.

virtual address 길이, physical address 길이, page size 등이 주어졌을 때 가능한 최대 physical memory 크기, Page Table의 최대 크기 등을 예제로 계산해보자.

#### Protection
각 프로세스별로 별도의 page table을 갖고있다. 컨텍스트 스위치 때에 `CR3` 혹은 `satp`를 잘 바꿔주기만 하면 겹칠 일이 없다.

Segment와 비슷하게, Page table entry에 valid bit, 권한 비트를 넣어놓고 page translation 할때 권한 체크도 같이 하도록 한다. 어차피 페이지를 읽으려면 page table을 반드시 봐야하니까 이렇게 구현해도 됨.

#### Page Table Entry
PTE에는 이런 Valid bit, protection 정보, PFN 말고도 이 PTE가 얼마나 최근에 access 되었는지 정보를 담기도 함.

- Reference, R: 얼마나 최근에 접근되었는가
- Modify, M: 얼마나 최근에 수정되었는가

OS는 주기적으로 R비트와 M비트를 클리어시킴. 더 많은 정보는 줘봤자 쓰지도 못해서 보통은 저렇게 1비트정도만 준다. 저런 R, M 비트가 없는 경우도 있다. 이런것은 CPU 아키텍처에 달려있음.

#### Demand Paging
모든 Page를 만들어달라고 해서 즉시 준비하는게 아니라, 프로세스가 실제로 이 페이지를 읽거나 쓰려 할 때 lazy하게 로드하는것. 그리고 잘 안 쓰이는 페이지는 evict시켜서 스왑영역으로 보내버리기도 한다. 프로세스 입장는 이런 일이 일어나고있다는걸 몰라도 됨.

xv6는 fork할 때 모든 메모리를 실제로 카피하고, exec을 할 때 모든 메모리를 다 로드한다. 근데 리눅스를 포함한 대부분의 OS들은 demand paging이라는걸 함.

#### Page Fault
Invalid PTE에 접근했을 때 CPU에 의해 발생하는 exception

- Mage page faults: 유효하지만 메모리에 로드 안된 페이지에 접근함
  - OS가 이런 페이지들을 어디서 불러와야하는지 정보를 관리하고있음
  - Disk IO 필요함
- Minor page faults: 디스크 IO 없이 해결될 수 있는 Page Fault
  - Lazy Allocation이 이런 경우
  - Accesses to prefetched pages (파일 IO할때 유저가 요청 안했어도 먼저 읽은 것들). etc
- Invalid page faults: 정말로 없는 페이지에 접근함

core dumped라는게 무슨 뜻일까? 그냥 메모리를 덤프했다는 뜻이다. 옛날에는 [Core Memory]라는게 있었음

[Core Memory]: https://en.wikipedia.org/wiki/Magnetic-core_memory

#### 장점
- No external fragmentation
- 할당/해제 빠름
  - A list or bitmap for free page frames
  - 할당: 연속된 메모리 영역을 찾을 필요가 없음
  - 해제: 인접한 free space와 Coalescing을 안해도 됨
- 메모리의 일부분을 Disk로 "page out"하기 쉬움
  - Page size는 disk block size의 배수로 정해짐
  - "paged out" 여부를 valid bit로 표시함
  - 일부 페이지가 디스크로 내려가있어도 프로세스는 정상동작함
- 페이지를 보호하거나 공유하기 쉬움

#### 단점
- Internal fragmentation은 못막음
  - 페이지 크기가 커지면 internal fragmentation이 더 커짐
- Memory reference에 기본 overhead가 생김
  - virtual memory reference 1회마다 physical memory reference가 2회 발생함
  - Solution: TLB로 해소 가능
- Page Table을 저장하기 위한 저장소가 필요함
  - Address space가 커지면 Page Table 크기가 몹시 커짐
  - 32bit address, 4KB page size, 4byte per PTE = 2**20 * 4B = 4MB
  - Solution: Valid PTE만 저장하거나, Page Table을 Paging한다

&nbsp;

Week 5, Thu
========
## Page Tables
페이지 테이블의 공간 오버헤드가 너무 크다. 대부분의 PTE는 invalid하니까, valid한것만 모아두자.

### Paging with Segmentation
각 가상 주소 공간을 segment로 먼저 나누고, 각 segment 안을 page들로 나누자.

Multics OS가 이렇게 되어있음.

장점

- 페이지테이블 크기 줄어듦
- Reshuffling 없이 세그먼트가 커질 수 있음
- 일부 페이지를 디스크로 스왑한채로 실행 가능
- Sharing의 flexibility가 커짐. 일부 페이지만 공유하거나, 세그먼트 전체를 공유할 수 있음

단점

- 페이지 테이블이 커질 수 있음. 예를들어 유저가 힙을 많이 할당해놓고 sparse하게 쓰면 페이지테이블 낭비가 큼
- page tables로 인한 external fragmentation. 각 페이지테이블은 연속적으로 할당되어야함.

### Multi-level Page Table
대부분의 PTE은 invalid이다. Multi-level Page Table을 쓰면, 연속된 invalid PTE들을 없애버릴 수 있다.

Multi-level Page Table을 쓰면, 여러 페이지테이블이 연속적으로 할당될 필요가 없어진다.

#### Multi-level Page Table: IA-32
32-bit address space, 4KB pages, 4bytes/PTE.

Page directory, Page table 이렇게 2-level로 구성되어있다.

Virtual Address = <10bit: Page directory number, 10bit: Page table number, 12bit: Page offset>

Page directory에 10bit를 쓴다. Page directory에는 1024개의 원소가 있음. Page directory의 Physical Address는 `CR3` 레지스터로 기록함. 크기가 4KB라서 한 페이지 안에 들어감.

Page table에도 10bit를 쓴다. 각 Page table에도 1024개의 원소가 있음. 크기가 4KB여서 한 페이지 안에 들어감.

남은 12bit는 Page offset임.

Page directory나, Page table 하나의 크기가 한 페이지 크기를 넘어가게될 수 있다. 32bit ARM이나 PAE가 켜진 IA-32. 이러면 어떻게 할까? 페이지 테이블이 여러 페이지로 쪼개지더라도 Physical memory 상에서 연속하게 위치하도록 OS가 잘 배치하면 된다.

`CR3`에는 Physical Address(PA)를 저장해야하는데, OS는 특정 Virtual Address(VA)의 Physical Address를 알아낼 수 있는 방법이 없다. 무슨 수로 PA를 알아낼까?

한 VA가 어느 PA로 매핑되는지는 알 수 없지만, Virtual Address Mapping을 하는 주체는 OS다. 특정 VA를 PA와 동일하게 매핑하면 된다. 예를들어 메모리영역 0부터 128MB까지는 VA i == PA i 라고 약속하기.

컴퓨터는 맨 처음 켜질때엔 Virtual Memory가 꺼진 채로 부팅되다가 특정 시점 이후에 켜지게된다. Virtual Memory가 켜지기 전에 저자한 메모리를 그대로 Virtual Memory를 켠 뒤에 사용할 수 있게 전달해야만 한다. xv6는 저 메모리 영역의 VA가 모두 PA와 동일해지도록 세팅한다. 리눅스는 아예 동일하지는 않고 특정 offset만큼 shift되게 해놨다.

#### Multi-level Page Table: AMD64
AMD64에서의 address translation: 48bit virtual address -> 52bit physical address. 4KB page

Virtual Address = <\
  9bit: Page Map Level 4 (PML4), \
  9bit: Page Directory Ptr (PML3), \
  9bit: Page Directory (PML2), \
  9bit: Page Table (PML1), \
  12bit: Page Offset>

64bit CPU가 되어서, 이제 PTE 하나의 크기는 4바이트가 아니라 8바이트이다. PTE 갯수가 512개여야만 페이지 테이블 전체가 4KB가 된다.

Intel CPU는 맨 처음에 세그먼트를 기준으로 만들어졌다. 세그먼트 레지스터같이 그때의 잔재가 남아있음. 386때 페이징이 추가되었다. 그래서 기능을 쓰고자 하면 segmentation과 page를 둘 다 쓸 수 있음. segment들을 virtual address spage (linear address spage) 상에서 겹치지 않게 둔 뒤, 그 세그먼트들을 나눈다.

요즘 OS들은 segmentation이 귀찮기만 하니까 그냥 하나의 단일 segment가 아주 큰것처럼 만들어놨다.

#### Multi-level Page Table: RISC-V
Virtual Address 모드가 여러개 있음. xv6는 Sv39를 쓴다

- Sv32: 32bit virtual address → 32bit physical address
- Sv39: 39bit virtual address → 56bit physical address
- Sv48: 48bit virtual address → 56bit physical address

### Multi-level Page Table 장단점
장점

- Sparse address space도 작게 표현 가능
- Physical memory 관리 편리함
- 하드웨어가 page table walk하기 쉬움
- No external fragmentation

단점

- TLB miss시 memory access가 너무 많아짐. AMD64는 다섯번이나 액세스해야함
- 복잡함

Q: 페이지테이블이 페이지 하나보다 커지면 어케한다고?

### Inverted Page Table
보통은 Virtual Address에서 Physical Address로 가는 forward mapping을 저장한다.

근데 virtual address는 크지만, 실제 매핑 수는 physical memory 위의 frame 갯수로 제한되어있다. 그러니, 이 physical address가 어느 virtual address와 연결되어있는지 backward mapping을 저장하는것이 inverted page table.

문제는 Address translation이 어려움.

Backward mapping이 언제 필요할까? Swap out 할 때 알아야함.

&nbsp;

Week 6, Tue
========

### Paging Page Tables
Multi-level page table 구조에서, Page Table을 가리키는것 조차 Physical Address가 아니라 Virtual Address를 쓰게 하면 가능하다.

근데 이러면 Nested Page Fault같은것도 처리해야하고 복잡해져서, 대부분의 OS들은 Page Table은 그냥 항상 메모리에 상주하게 만든다.

Kernel code와 data도 paging할 수 있다. Paging Page Tables보다 더 쉽게 가능함. 근데 얘도 역시 항상 메모리에 상주하게 한다. 커널에 쓰이는 코드와 데이터의 크기가 별로 크지 않아서.

&nbsp;

## 8. TLB: Translation Lookaside Buffer
Multi-level Page Table같은걸 쓰면 공간적인 오버헤드는 줄지만 시간적인 오버헤드는 더 커진다. 메모리 액세스를 너무 많이 해야해서 너무 느려짐.

캐싱을 해서 시간적인 오버헤드를 줄이는것이 TLB다.

- Temporal Locality
- Spatial Locality

코드의 로컬리티가 데이터의 로컬리티보다 높다. 코드는 순차적으로 접근하고 루프도 돌고 그러므로. 데이터의 로컬리티는 경우에 따라 다르다.

TLB는 하드웨어로 구현함. 엔트리 수가 크지 않아도 굉장히 효율적임. 왜냐면 TLB 한 엔트리가 커버하는 Memory 영역이 Page Size만큼 넓기 때문이다. 보통 엔트리가 16~256개 있다.

보통 Fully Associative하다. Write-back 캐시임

- All entries looked up in parallel
- 레이턴시를 줄이기 위해 set associative하게 만들기도 한다

Cache의 코스트가 아깝다고 Cache가 없는 CPU가 있다. Paging을 아예 안하는 CPU는 있어도, Paging을 하면서 TLB가 없는 CPU가 없다. 아주 조금만 있어도 극도로 효율적이여서.

Pseudo-LRU(Least Recently Used)로 오래된것부터 밀어냄. 보통 PFN만 캐싱하는게 아니라 PTE 전체를 캐싱하고있음. Valid bit, protection 정보들도 항상 다같이 읽어야 하니까.

### Handling TLB Misses
Software-managed TLB

- TLB miss때에 CPU trap이 발생함
- OS가 직접 Page table을 walk하고 TLB를 채워야함
- TLB 조작을 위한 privileged instruction이 제공됨
- OS가 원하는 아무 형식으로 페이지 테이블을 만들 수 있음

Hardware-managed TLB

- CPU가 페이지 테이블이 어디에 있는지 알고있음
- TLB miss때에, CPU가 자동으로 page table을 walk하고 TLB를 채워줌
- Page table이 CPU가 정한 포맷으로 만들어져있어야함

요즘 우리가 쓰는 대부분의 CPU는 Hardware-managed TLB이다.

### TLB opn Context Switches
Context Switch를 할 때마다, TLB를 비워야한다. Virtual Address space가 바뀌기 때문이다. CR3 레지스터를 쓸 때마다 TLB가 비워진다. 심지어 같은 값을 또 써도 TLB가 비워진다.

예전에는 Process의 Virtual Address space중 일부를 커널이 쓰기위한 region으로 예약해놨었다. 모든 프로세스들이 저 커널 메모리 영역은 공유하도록. 이러면 컨텍스트 스위칭을 하더라도 TLB에서 커널부분은 날리고싶지 않을 수 있다. 그래서 MIPS, Intel같은 일부 아키텍처들은 TLB에서 일부 Entry는 flush 안되게 막을 수 있다. 다만 요즘은 커널이랑 프로세스랑 다른 Address space를 쓰게해놔서 의미는 없음.

TLB가 날아가면 TLB miss가 속출해서, 굉장히 느려진다. 컨텍스트스위칭을 하더라도 TLB를 flush하지 않을수는 없을까? TLB에 프로세스들을 구분해줄 수 있는 정보롤 같이 담으면 되겠다. PID는 32bit 이상이여서 오버헤드가 너무 크니, 8bit 짜리 Address Space ID (ASID)를 작게 담는다.

켜져있는 프로세스가 256개보다 더 많아지면 어떻게 할까? 대부분의 CPU는 idle 할것이므로, Active한 프로세스에게만 ASID를 주고, 만약 그러고도 모자르면 TLB 일부를 flush하면서 넘치는 갯수만큼 없애야함.

리눅스가 예전엔 PID가 16bit였는데, IBM에서 CPU가 엄청 많이 달린 NUMA 머신을 만든적이 있었다. 이 때 부팅할 때 코어 수에 정비례해서 스레드가 켜져야만 했었는데, 부팅하기만 해도 16bit PID가 모조리 동나서 32bit로 키웠었다.

### TLB on Multi-core
TLB는 CPU 코어들마다 따로 있다. 일반 캐시는 하드웨어들이 캐시가 항상 최신상태를 유지하도록 하드웨어가 coherence protocol로 관리해주는데, TLB에 대해선 그짓을 안한다. OS가 TLB coherence를 복구시켜줘야한다.

TLB Shootdown

- 어떤 코어에서 Page Table이 변화되면, 고친 코어가 다른 코어들에게 Inter-Processor Interrupt(IPI)를 쏴서 페이지 테이블이 변화했다는 사실을 알린다
- 그 메세지를 받은 CPU는 적절하게 TLB를 invalidate시킨다
- IPI는 수백사이클정도 걸릴 수 있다.

Cache는 Physical Address만 보면 되는데, TLB는 Process의 context가 있어야해서 CPU가 자동으로 해줄 수 없음.

### TLB Performance
TLB 퍼포먼스가 프로그램 전체 퍼포먼스의 병목인 경우가 있다. 메모리 액세스 헤비한 프로그램들이 보통 그러함. 보통 Hit rate, Lookup latency를 TLB 퍼포먼스 메트릭으로 씀.

TLB 퍼포먼스를 어떻게 올릴까

1.  Increase TLB coverage, Increase TLB reach

    Superpages를 써서 페이지 크기를 늘리면 TLB 크기가 올라간다. Intel 64는 2MiB Page, 1GiB Page를 지원한다.

    다만 Superpages를 쓰면 internal fragmentation, external fragmentation이 심해지고, Swap-out 해야하는 크기도 너무 커짐. Swap-out 오버헤드를 줄이기 위해 superpage 전체를 swap-out하는게 아니라 demotion, promotion 이라는 동작을 도입해 페이지 일부를 swap-out 하기도 한다.

2.  Use multi-level TLB

    Intel Haswell은 아래의 멀티레벨 TLB를 지원한다

    - L1 ITLB, 128 entries, 4-way
    - L1 DTLB, 64 entries, 4-way
    - L2 STLB, 1024 entries, 8-way

3.  알고리즘과 자료구조를 TLB-friendly하게 바꾸기

과제 나왔음!

&nbsp;

Week 6, Thu
========
### From CPU to Memory
1. TLB hit/miss
2. Page hit/fault

### VM + Cache
Physically addressed cache

- TLB 뒤에 Cache가 있어야함
- Address translation is on the critical path

Virtually addressed, virtually tagged cache

- Homonym problem: 동명이인 문제. 여러 프로세스에, 다른 Physical Address인데 Virtual address가 같은 경우가 존재 가능
- Address synonym or aliases problem: 같은 Physical Address인데 Virtual Address가 다른 경우 존재 가능

Virtually addressed, physically tagged cace

- Page Size (~4KiB) > Cache block size (32~64B) 이므로, TLB lookup과 Cache lookup을 동시에 할 수 있음. Cache lookup을 한 뒤 TLB lookup의 결과로 PFN이 날아오면 그것과 Cache의 PFN이 같은지 비교한다.
- 'Physically addressed cache'와 비교하면 레이턴시가 약간 줄어듦

&nbsp;

## 9. Memory Mapping
Virtual Address space is a resource. 64bit CPU에선 별 문제 안되지만, 32bit CPU에선 문제가 되기도 했음. Virtual Address space 4기가중 1기가는 커널로 예약하던 시대이다보니, 쓸 수 있는게 3기가밖에 없었음.

Virtual Address 0번 주소 근처는 일부러 비워둔다. 0번지에 유의미한 데이터를 넣으면, 실수로 Null pointer access를 한건지 의도적으로 접근한건지 구분이 안 가기 때문이다.

`brk()`, `sbrk()` 시스템 콜로 Heap의 크기를 조정할 수 있었다.

### `mmap()`
Backing store의 일부를 메모리에 map 하는 기능. Backing store의 예시로는 아래가 있다

- File: load/store 명령어로 파일을 읽고 쓸 수 있음
- Device memory
- Shared memory
- None. Anonymous mapping

Anonymous mapping엔 Zero-page mapping 기능이 있음. 처음 읽으면 걍 0만 가득차있는 페이지를 return하고, 쓰기 시작하면 그제서야 새 메모리를 할당하는 기술

### Shared vs Private mapping
Shared mapping: 여러 프로세스가 하나의 자원을 공유해 mapping할 수 있음. 이 경우 한 프로세스의 수정이 다른 프로세스에 전파됨

Private mapping: 한 프로세스의 수정이 다른 프로세스에 알려지지 않음. Copy-on-write

### `mmap()` syscall 사용법
PPT, `man 2 mmap` 참고

### Memory-mapped file
처음엔 모든 영역이 invalid로 mark되어있음. Invalid한 page가 액세스되었을 때 파일 IO를 시작함. Virtual Address는 파일 데이터의 주소로 매핑되어있음.

프로그램 실행할 때 executable에 들어있는 code와 data를 읽어 메모리로 올리는데, 이게 사실 mmap으로 구현되어있음.

&nbsp;

Week 7, Tue
========
중간고사는 아마 안 보아야 할 것 같고, 기말고사 하나로 정해야할 것 같다. 중간30 기말30 프로젝트40 이렇게 정해져있는데, 배점을 기말40~50 프로젝트50~60 이런식으로 조정해야할 듯 하다.

시험공부는 교재로 미리미리 해보세요.

memory-mapped file과 memory-mapped I/O는 다르다. memory-mapped I/O는 메모리 load store 명령어만으로 주변장치에 입력으로 들어가는 레지스터/pin 입력을 바꾸는것임.

### File I/O vs Memory-mapped File
`mmap()`으로 하면 memcpy 횟수가 줄어든다!

File I/O와 비교했을 때, mmap 장점

- 파일, 메모리 가리지 않고 포인터로 uniform 하게 접근 가능
- 복사를 덜 할 수 있다
- 여러 프로세스가 같은 map을 공유할 수 있다

File I/O와 비교했을 때, mmap 단점

- 프로세스가 데이터 이동을 control할 수 있는 범위가 준다
- Streamed I/O (pipes, sockets, etc) 로 일반화가 불가능하다

그냥 File I/O를 하더라도 파일의 특정영역이 커널의 페이지에 올라오게된다. 이런 페이지들을 unmapped page라고 부른다.

### Shared Memory with `mmap()`
두 프로세스의 page table에, 같은 physical address를 가리키는 PTE가 양쪽에 있으면 된다. 같은 Physical frame을 가리킬것만이 요구되고, protection value는 달라도 된다. 단 Page가 invalid해질경우 두 PTE를 모두 업데이트시켜야 한다.

Shared 메모리를 쓰면 두 메모리가 같은 physical address를 쓰겠지만, 같은 virtual address를 쓰지는 못할 수 있다. Virtual address가 충돌한다던가 등의 이유로. Virtual address가 같으면 shared pointer가 유효하지만, virtual address가 다르면 shared pointer가 유효하지 못하다.

### CoW: Copy-on-Write
메모리 카피를 최대한 늦추는 테크닉. `fork()`가 제일 대표적인 사용 예시다.

&nbsp;

## 10. Swap
Consider physical memory as a cache for disks. 어떻게 스왑을 구현하는지 알아보자.

### Memory Hierarchy
메모리 크기와 코스트는 서로 트레이드오프 관계에 있다.

### How to Swap
옛날 방식: Overlay

- Programmers manually move pieces of code or data in and out of memory as they were needed
- OS 지원 없이 프로그램이 지혼자 알아서 함

Process-level swapping

- 잘 안쓰이는 프로세스를 통째로 빼버리는 방식 (swap-out, swap-in)

Page-level swapping

- 잘 안쓰이는 페이지 단위로 빼내는 방식 (swap-out, swap-in)
- Page-level swapping을 특별히 page-out, page-in이라고 부르기도 한다.

### Where to Swap
윈도우에선 스왑 파일 방식을 쓴다. 디스크 드라이브 안에 `pagefile.sys` 라는 파일이 생김

리눅스에선 스왑 파일 외에도 스왑 파티션 방식도 쓸 수 있다. 스왑 파티션 방식은 특정 파티션을 통째로 스왑으로 쓰는건데 살짝 더 빠름

Swap space에서 메모리로 swap-in 할때에, 바로 해당 영역을 없애진 않는다. 그 영역을 또 swap-out 할 일이 생기게된다면 공짜로 할 수 있으니까.

### When to Swap
메모리가 꽉차버릴때까지 스왑아웃을 안하고 기다리면, 디스크 IO 성능으로 컴퓨터 메모리 액세스 성능이 병목에 걸려버린다. 그래서 보통은 꽉차버리기 전에 미리 스왑아웃을 시킨다.

Proactively based on two thresholds values: High watermark (HW), Low watermark (LW)

Free memory 비율이 LW에 도달하면, HW에 도달할떄까지 swap out 시킴.

Allocation speed가 reclamation speed보다 빠르다면 어떻게할것인가?

#### Swapping in Linux
low_wmark_pages에 kswapd(swapping daemon)이 깨어나서 스와핑을 하기시작했는데도, allocation이 너무 빨라서 메모리가 모자르다고 쳐보자. 어떻게 할 까?

리눅스는 low, high watermark 말고 더 낮은곳에 min_wmark_page가 하나 더있음. 그래서 low_wmark_pages에 kswapd가 깨어난 뒤에 free pages 수가 min_wmark_page에 도달하는 순간, synchronous하게 free page를 allocate하기 시작해 min_wmark_page 밑으로는 더 못내려가게 막는다. 다만 커널이 급하게 할당하는 GFP_ATOMIC allocation은 min_wmark_page 밑으로 내려갈 수 있다. 그러다가 high_wmark_pages에 도달하면 kswapd가 꺼진다.

### What to Swap
Physical memory에 있는 녀석들 유형별로 스왑 가능여부가 다르다

- Kernel code: Not swapped
- Kernel data
- Page tables for user processes: Not swapped
- Kernel stack for user processes
- User code pages: Dropped
- User data pages
- User heap/stack pages: Swapped
- User mmap-ed pages
- Page cache (I/O의 캐시): Dropped or go to file system

Page replacement policy가 어떤 page를 evict할지 결정한다.

&nbsp;

Week 8, Thu
========
**TODO**

Page Replacement부터 쓰래싱, 등 PPT 10 끝까지 했음.

&nbsp;

Week 9, Tue
========
오늘 과제 나감. fork()에서의 CoW 구현임. Reference Count를 꼼꼼하게 잘 해서 릭이 나지 않도록 잘 짜보세용.

기말고사는 종강하는 주의 목요일에 볼것같은데, 학교방침은 그것보다 일찍하라고함. 6월 18일 (6월 3주차 목요일) 로 예정되어있으나 정확히는 모름

## 11. Virtual Memory Implementations

### Linux Virtual Memory System
리눅스의 Virtual Memory System에 대해 알아보자

#### VMA: Virtual Memory Area
`cat /proc/self/maps`를 하면 `cat` 프로세스가 가상메모리를 어떻게 쓰는지 알 수 있음. `vm_area_struct` 하나가 Virtual address space 안에있는 연속된, page-aligned된 세그먼트 하나를 의미함.

Page Fault가 일어나면 OS는 어느 페이지를 액세스했다가 page fault가 났는지 알아내야함. 없는 세그먼트에 액세스한거면 SIGSEGV를 일으켜야하고, 있는 세그먼트에 액세스했다면 스택을 할당하던가 스왑을 하던가 등등. 그래서 OS는 특정 주소가 어느 VMA에 해당하는지 알아내야해서, VMA들은 red-black tree로 관리가되고있음.

PPT 4번 슬라이드에 구조가 나와있다. `task_struct`은 xv6의 `struct proc` 같은거임. `vm_area_struct` 안에 `vm_rb`라는 필드가 있는데 이게 RBtree임.

#### Paging in Linux
x86_64 머신은 대부분 48-bit virtual address를 쓴다. 최근에 인텔 Ice Lake 아키텍처가 나왔는데 얘는 57-bit virtual address를 지원해서 5-level paging을 지원한다.

- 32bit VA: 10*2 + 12
- 48bit VA: 9*4 + 12
- 57bit VA: 9*5 + 12

리눅스 실제 구현은 매크로를 아주 잘 써놓아서, 5-level paging 구현을 다 만들어놓고 32bit VA에선 2 level만, 48bit VA에선 4 level만 쓰게 해놨음.

#### Managing Physical Memory (32-bit)
4GB virtual address중 유저한테는 0x00000000 ~ 0xC0000000(PAGE_OFFSET) 3기가만 주고, 나머지 1기가는 커널과 공유하게 되어있음.

유저모드에서의 커널메모리인 0xC0000000 ~ 0xffffffff 영역은 커널모드에선 0x00000000 ~ 0x3fffffff로 매핑되게 해놨음.

High memory 영역을 액세스하고싶으면 페이지테이블을 먼저 매핑한다음에 접근해야만 함. 커널이 사용할때엔 Low Memory를 먼저 쓰고, mmap처럼 어차피 페이지테이블을 고쳐야하는 메모리 할당을 할때엔 High memory를 씀.

근데 64bit CPU가 쓰이면서 이런 High memory 구분같은게 다 필요 없어짐

#### KPTI: Kernel Page-Table Isolation
멜트다운 취약점때문에 리눅스 4.15부터는 `CONFIG_PAGE_TABLE_ISOLATION=y`라는게 생겨서 더이상 유저모드일때와 커널모드일때에 같은 페이지를 불필요하게 많이 공유하지 않게되었음.

ASID (Address Space Identifier) becomes critical to the performance.

#### Page Cache
리눅스에 파일을 캐시할때, inode들로 잘라서 캐시한다. 그리고 같은 inode를 공유하는 캐시는 group한다.

inode들의 Radix tree로 관리하고있음. 한 노드당 최대 자식수 (fanout)은 64개인데, 작은 시스템에선 16개일수도 있음.

#### Linux Page Replacement (v5.x)
클락알고리즘 이런건 naive한 알고리즘이고, 실제로는 훨씬 복잡한 알고리즘을 씀.

map된 페이지들은 load, store 명령어로 접근하는거라 어떤 순서대로 접근이 발생했는지 알기 힘들다. 이 경우 reference bit을 사용해 근사함.

저거 말고 그냥 read(2), write(2) 시스템콜로 접근하는 경우는 IO를 OS가 하는거니까 OS가 접근 순서를 정확하게 알 수 있다. 이렇게 순서를 아는 경우엔 LRU list 만드는게 그리 어려운 일이 아님.

mmap으로 읽는 경우보다 read/file로 읽는게 더 흔하기때문에 페이지캐시중 상당수는 OS가 순서를 정확하게 알 수 있다.

anonymous page를 위한 LRU 리스트와, file-backed page를 위한 LRU 리스트 두개를 따로 관리한다. 그리고 한 리스트 안에서도 Active list와 Inactive list를 각각 따로 관리한다. Inactive list에 들어있다가 reference가 도면 active list로 돌아가고, inactive list에서도 접근되지 않고 밀려나버리면 스왑해버린다. anonymous page는 swap으로 스왑하고, file-backed page는 파일시스템으로 스왑하고.

File-backed page가 양이 훨씬 많아서 file-backed page를 훨씬 자주 참조함.

스마트폰같은 경우 메모리가 모자라면 스왑을 안하고 걍 앱을 죽여버린다.

LRU는 "특정 메모리를 한번만 쓰고 버리기" 이런 상황에 취약하다. 특히 파일 읽기, 동영상 재생 이런거 할때 저렇게 한번 읽고 버리는게 많다. 그래서 File-backed page는 레퍼런스가 2번 이상인것만 active list로 올림.

file-backed page중에서 code의 경우 특수처리함.

### xv6 Virtual Memory System
#### RISC-V paging hardware
Sv39: page-based 39-bit virtual addressing

- VA 39bit = 9*3 + 12
- => PA 56bit = 44 + 12

multilevel paging하면서 더 많은 PPN을 표현하는 방식으로 superpage support가 있긴 한데, xv6는 저걸 안쓴다.

#### Process Address Space
xv6는 39bit VA중 38bit만 쓴다.

(VA 레이아웃은 PPT 참고)

- Guard page: 스택오버플로 감지
- Trampoline page: 트랩 핸들러 코드
- Trapframe page: 유저 레지스터 저장

커널모드로 바꾼 순간, 모드는 바뀌더라도 페이지테이블은 여전히 유저의 페이지테이블을 쓰고있고, 레지스터도 여전히 유저의 레지스터를 쓰고있는 상태로 남아있기때문에 이걸 보존해줘야한다. 그래서 트램폴린과 트랩프레임이 필요하다.

커널은 유저 레지스터를 모두 백업해줘야하는데, xv6 스펙상 커널모드로 바뀐 직후에 커널이 자유롭게 쓸 수 있는 레지스터가 `sscratch` 하나밖에 없음. 그래서 `sscratch`에 트랩프레임 주소를 저장한다음, 트랩프레임에 유저 레지스터를 모조리 백업하는거임.

#### Kernel Address Space
xv6 uses KPTI.

(PPT 참고)

#### Physical Address Space
xv6는 physical memory 사용이 128MB로 제한되어있음. 0x80000000 부터 PHYSTOP은 kernel address space에 리니어하게 매핑해놨음.

(PPT 참고)

&nbsp;

Week 9, Thu
========
기말고사: 6월 18일 목 11시~1시
보강: 5월 18일 7시

## 12. Threads
Concurrency: 유저프로그램도 멀티스레드로 실행되고, 커널도 그러하다.

과거에는 멀티스레드가 없었다. 그러다가 하나의 프로세스가 여러개의 CPU를 활용할 수 있게할 필요가 생겼다.

과거에도 멀티프로세싱은 가능했으나, 여러 프로세스가 서로 협력하면서 실행하게 만드는것은 매우 번거로웠고, 프로세스 생성비용, 프로세스간 통신 비용, 프로세스간 컨텍스트 스위치 비용은 매우 비쌌다. 그래서 프로세스 안에서 실행 흐름을 여러개 만들 필요가 생겼다.

80년대 초반에 SunOS(후에 Solaris로 이름 바뀜)에서 처음 스레드가 생김. UNIX는 맨 처음 만들어진 이후 추가된것들이 많지 않은데, 스레드는 그 이후 추가된것중 가장 중요한것중 하나다.

원래 "Thread of control", "실행의 흐름" 라는 말을 썼었고 이를 줄여서 스레드라고 부르게 되었다.

스레드는 빠르게 새로 만들 수 있도록 설계되었다. Share할 수 있는건 다 share하고, 새로운 실행흐름을 만들 때 필수적으로 따로 있어야 하는것만 갖고있다.

- Thread ID
- Set of registers (PC, SP 포함)
- Stack

과거 스레드가 없던 시절은, 프로세스 하나당 스레드가 하나로 강제되는것으로 볼 수 있음.

Protection의 단위는 여전히 프로세스이지만, 이제 스케줄링/실행의 단위는 스레드임.

#### Address space with threads
이제 스택이 여러개가 되었음. 스택메모리들 사이의 위치와 스택이 자라는 방향때문에 스택마다 최대의 크기가 존재해야만 하게 되었고, 리눅스는 2MB임

#### Processes vs Threads
- 스레드:프로세스 = n:1
- 스레드간 데이터 공유는 저렴함, 같은 프로세스 내 스레드는 같은 address space를 보고있음
- 스레드는 스케줄링의 단위, 프로세스는 프로텍션의 단위
  - PID, address space, uid, gid, open fd, cwd 등은 모두 프로세스 자원
- 프로세스는 정적 entities, 스레드는 동적 entities

#### Benefits of Multi-threading
- 저렴하게 컨커런시 달성 가능
- 프로그램 구조가 좋아짐: 하나의 큰 task를 여러개의 작은 스레드에 분산시켜줄 수 있음
- 프로세스 스루풋이 좋아짐: I/O와 computation을 동시에!
- 프로세스 응답성이 좋아짐: 여러 concurrent event를 동시에 처리 가능
- Resource sharing
- 멀티코어 활용 가능: 병렬 프로그램 작성 가능

#### Thread interface
pthread: POSIX (IEEE 1003.1c) 표준에 정의된 스레드 및 스레드 동기화 API 및 동작 스펙. Linux, macOS, Solaris, FreeBSD, NetBSD, OpenBSD 등 UNIX-like OS들에 모두 pthread 구현체가 있다.

Win32/Win64 Threads: 윈도우는 자체 스레드 API를 가짐

#### pthread
POSIX 스레드 API 표준. `pthread_create`, `pthread_exit`, `pthread_join` 등의 명령으로 스레드를 생성하고 관리한다. `pthread_mutex_*`, `pthread_cond_*` 등의 동기화 객체가 제공된다.

### Threading Issue: fork(), exec()
멀티스레드로 동작중이던 프로세스에서 fork() 호출이 발생하면... 어떻게 해야할까?

1. fork() 호출을 한 스레드 하나만 분기한다
2. 모든 스레드를 분기한다

구현체마다 동작이 다르다

- pthreads에선 fork()를 호출한 스레드만 분기한다 (1)
- Unix international standard에선 fork()는 모든 스레드를 분기하고 (2), fork1()는 호출한 스레드마 분기한다 (1)

exec() 호출은 보통 모든 프로세스를 교체해버린다.

### Threading Issue: Thread Cancellation
스레드가 작업을 마치기 전에 스레드를 없애는 문제. 그냥 끄면 되는거 아닌가 라고 생각할 수 있지만, 스레드가 락을 잡고있었다던가 할 수 있기 떄문에, 마구 끄면 위험하다.

1. Asynchronous cancellation: 즉시 끄기. 리소스를 락 하고 있었다던가, 공유 자원을 업데이트하던중이면 어떻게될까?
2. Deferred cancellation: cancellation points에 종료됨. target thread는 자신이 종료되어야 하는지 주기적으로 체크

pthread는 1 2 둘다 지원함

### Threading Issue: Signal Handling
프로세스에 시그널이 오면, 어느 스레드가 처리해야하는가?

1.  Synchronous signal 한정: signal을 유발한 스레드가 정해져있으므로, 해당
    스레드가 signal handler를 수행하도록 함
2.  프로세스 안의 모든 스레드에게 전달
3.  시그널 처리를 전담하는 특정 스레드 하나에 모두 전달
    - Solaris 2: 한 스레드가 모든 시그널을 맡았다
4.  일정 규칙으로 특정 스레드들에 모두 전달
    - 스레드별로 시그널 마스크를 설정해서, 이 스레드가 이 시그널을 받을 수 있는지 없는지 명시하는 방식도 쓰고, 여러 방법을 사용
    - 보통은 프로세스 안에 시그널을 막지 않는 스레드가 하나만 있어서, 그 스레드가 받게 해놓음
    - pthread: per-process pending signals, per-thread blocked signal mask

이 멀티스레드 프로그램이 시그널 처리하는 방법이 OS마다 달라서, portability issue가 존재한다.

#### Threading Issue: Global variable
전역변수, 전역 state를 쓰는 함수들에 문제가 생겼음

- Global `errno` variable → `errno` variable in thread-local storage
- `strtok(3)` → `strtok_r(3)`

C library argument들의 format을 조금 바꿔서, strtok_r과 같이 multithread-safe (MT-safe) 버전 라이브러리들이 생겨났다.

### Implementing Thread
유저스레드/커널스레드: 스레드를 유저가 필요해서 만들었는지 or 커널에서 이벤트에 의해 만들어졌는지
 
유저레벨스레드/커널레벨스레드: 스레드 구현이 유저레벨에서 이뤄졌는지 or 커널레벨에서 이뤄졌는지

### Kernel-level Threads
OS-managed threads: OS에 의해 만들어지고 관리되는 스레드

- 생성/관리에 시스템콜 필요함
- OS가 스케줄링함
- 프로세스 생성보다 쌈
- Windows, Linux, macOS, AIX, HP-UX, ...

단점:
- 프로세스보다는 싸지만 여전히 비쌈
- 시스템콜을 매번 해야함
- 커널이 스레드를 관리해야함, OS 전체에 스레드 전체 갯수 제한이 걸릴 수 있음
- OS 구현체가 스레드 수에 비례해 스케일링이 잘 되어야 한다.
- 커널레벨 스레드가 프로그래머, 언어, 런타임의 니즈를 모두 충족할 수 있을 정도로 충분히 general 해야한다.

### User-level Threads
커널의 도움 없이 유저가 유저레벨에서 지 힘으로 만든 스레드. 두 목적이 있다

1. 스레드 지원 없는 OS에서 스레드를 쓰고싶을때가 있었음
2. 커널 스레드도 비싸서 일부러 쓰기 싫음

유저레벨 스레드는 유저가 알아서 관리해야한다. User-level threads에 대한 정보는 OS가 알아낼 수 없다.

시스템콜 없이 함수호출만으로 스레드 오퍼레이션이 이뤄지기 때문에, 커널스레드보다 작고 빠르다. 커널레벨스레드보다 10~100배 빠름. 포터블하고, 어플리케이션 요구사항에 맞춰 자유롭게 튜닝할 수 있다.

그린스레드, goroutine, ...

단점:
- 유저스레드중 하나가 시스템콜을 하면, 하나의 커널 스레드를 공유하는 모든 유저스레드들이 단체로 멈춤, nonblocking IO, async IO 사용이 강제됨
- OS가 유저 스레드에 대해 아는게 없어서, OS가 poor decision을 내려버릴 수 있음
  - Scheduling a process with only idle threads
  - Unscheduling a process with a thread holding a lock
- 유저스레드로는 preemptive scheduling을 구현하기 어렵기 때문에, 보통은 non-preemptive scheduling으로 구현해야함
- 여러 CPU를 사용한 컨커런시 구현은 불가능

&nbsp;

Week 10, Mon (보강)
========
user-level thread에서 mutex가 필요하면 어떻게 하나요: 커널 도움이 필요함. 커널 도움 없이 mutex 만들으려고 하면 비효율적으로 구현해야함.

user-level thread를 

### Threading Model: One-to-One
1개의 커널레벨 스레드는 1개의 유저레벨 스레드에 대응됨. 제일 흔한 스레딩 모델

Windows XP/7/8/10, OS/2, Linux, Solaris 9+, ...

### Threading Model: Many-to-One (N:1)
여러 유저 스레드가 1개의 커널레벨 스레드로 구현된 경우. 커널 스레드 지원이 없는 경우에 사용됨

Solaris Green Threads, GNU Portable Threads, ...

### Threading Model: Many-to-Many (M:N)
M개의 유저 스레드가 N개의 커널레벨 스레드로 구현되는 경우

Solaris prior to v9, IRIX, HP-UX, Tru64

요즘에 사용되는 예시: Goroutine, Erlang greenthread 등의 그린스레드

Solaris같은경우는 v9 이전까진 이 방식을 쓰다가, 코어 수가 많아지니까 구현이 너무 복잡해져서 걍 1:1 모델로 바뀌었음.

UNIX 만든 켄 톰슨이 구글에 가서 Golang 만들고있다.

### Linux Thread implementation
리눅스에서는 기본적인 실행 단위가 "task"이다. In a program that only calls fork() and/or exec(), a task is identical to a process.

리눅스 스레드 모델: One-to-One model. clone() 시스템콜로 task를 만들면, 스레드가 생긴다.

리눅스는 스레드 구현이 특이하다.

일반적인 OS들은 PCB(Process Control Block) 안에 TCB를 여러개 둬서, 여러 스레드들이 share 해야하는 정보는 모두 PCB에 놓고 스레드별로 달라지는 정보만 TCB에 두는 방식으로 구현을 한다. Windows가 이렇게 되어있다.

근데 리눅스는 프로세스와 스레드를 전혀 구분하지 않고, fork()를 하든 clone()을 하든 무조건 새 `struct task`가 만들어지게 해놨다. 단 fork()를 하면 메모리를 비롯한 각종 자원들이 CoW로 복사되지만, 스레드에선 그런것들이 모두 share가 됨. clone() 시스템콜을 할 때 어디부터 어디까지 share할지를 유저가 직접 지정할 수 있다.

리눅스 구현이 영리해보이지만, 만들어진 직후엔 문제가 심각했다. 예를들어 과거에는 Task ID를 PID로 썼었는데, clone()을 하면 새 스레드의 PID가 원래 스레드의 PID와 달랐음. 이 외에도 스레드들끼리 share해야하는 정보들이 share되지 않는것들이 많았음.

일반적인 OS의 구현이 기본적으로 모두 share하고, share하지 않을것만 별도로 지정해주는 blacklisting 방식이라면, 리눅스의 구현은 기본적으로 다 share 안하고, 별도로 지정하는것만 share하는 whitelisting 방식임.

반면 POSIX 스레드는 스레드들끼리 CPU 레지스터, 유저 스택, blocked 시그널 마스크 등의 정보를 share해야 한다고 명확하게 요구하고있음. 이때문에 리눅스 스레드와 POSIX thread 사이의 호환성 문제가 발생했음. signal handling, exit(), exec() 등의 operation들이 리눅스에선 기존에 Task() 단위로 이뤄지고있었기때문에 exit해도 스레드 하나만 죽는다던가, exec 해도 스레드 하나만 exec 된다던가 이런일이 발생했다. 이때문에 나중에 스레드 그룹, 스레드 그룹 같은 개념이 리눅스에 도입되는 등 호환레이어가 리눅스 코드에 씌여졌음. 그러나 내부에서는 여전히 과거와 같은 방식으로 동작한다.

### Summary: OS Classification
프로세스 abstraction이 있어야하는 이유

1. 우리가 여러 프로그램을 만들어놓았을 떄, 원하는 프로그램들을 로딩해서 실행하기위해 프로세스가 필요하다.
2. 돌아가는 프로세스들 사이의 메모리 보호가 필요해서

만약

1. 내가 실행할 프로그램이 이미 정해져있고
2. 돌아가는 프로세스들 사이의 메모리 보호가 필요 없으면

프로세스가 필요 없다.

여러 실행흐름을 동시에 돌리는것만이 목적이라면, 프로세스 없이 스레드만 있어도 된다. 그래서 임베디드 시스템이나, Real-time system같은곳에선 스레드만 지원하고 프로세스를 지원하지 않는 경우가 많다. 심지어 이런 환경에선 Virtual memory가 없는경우도 많음

프로세스를 지원하지 않는다는것은, Address space가 한개라는 뜻. 프로세스를 지원한다는것은 Address space가 여러개라는 뜻.

스레스수 per address space \ address space 수 | One | Many
---------------------------------------------|-----|------
One | 원시적인 OS (MS DOS, 초기 매킨토시) | Traditional UNIX, xv6
Many | 대부분의 embedded OS (VxWorks, uClinux) | Mach, OS/2, Linux, Windows, macOS, Solaris, HP-UX

이런 측면에서 보면 OS에서 가장 기본적인 기능은 프로세스가 아니라 스레드와 스케줄링이라고 볼 수 있다. 그 다음 메모리, 동기화 이런것들이 들어가는것임

&nbsp;

## 13. Locks
스레드 만들때엔 좋았지?! 이제 귀찮은 일이 발생하기 시작한다.

### The Classic Example
김젼이 김젼은행 ATM 출금을 아래와 같이 구현했다고 쳐보자.

```java
balance = get_balance(account);
balance = balance - amount;
set_balance(account, balance);
```

리락쿠마와 코리락쿠마가 김젼은행에서 모임통장을 만들었다. 리락쿠마와 코리락쿠마가 두 ATM에서 동시에 10만원을 출금한다고 해보자. 위의 코드가 atomic하게 실행되지 못하고 아래와 같이 interleave하게 실행되었다.

```java
// 리락쿠마
balance = get_balance(account);
balance = balance - amount;
        // 코리락쿠마
        balance = get_balance(account);
        balance = balance - amount;
        set_balance(account, balance);
set_balance(account, balance);
```

교수님: 개이득 상황이 되는거져. 100만원 통장에서 10만원을 두번 뽑았는데 90만원이 남는거져.

락이 필요한 예시입니다

### The Real Example
```c
extern long g;
void inc() { ++g; }
```

위 코드의 inc() 함수 본체가 아래와 같이 컴파일되었다.

```asm
ld    a0, 0(s1)
addi  a0, a0, 1
sd    a0, 0(s1)
```

위 어셈블리 코드를 아래의 두 스레드가 실행하는데, 실행도중 컨텍스트 스위치가 발생했다고 해보자.

```asm
// Thread T1
ld    a0, 0(s1)
addi  a0, a0, 1
        // Thread T2
        ld    a0, 0(s1)
        addi  a0, a0, 1
        sd    a0, 0(s1)
sd    a0, 0(s1)
```

이것도 락이 필요한 예시. 언제 스케줄링이 일어나느냐에 따라가 값이 비결정적(non-deterministic)하게 변한다.

Preemptive scheduling 특성상, 실행하는 코드가 어디에서 preemption 당할지 알 수 없다. 어쩌면 좋을까!

### Sharing Resources
지역변수는 스레드들 사이에 공유되진 않는다. 지역변수는 스택에 있고, 스레드마다 스택이 하나씩 따로 있으니.

전역변수가, heap에 생성된 dynamic objects를 여러 스레드들이 공유하는 경우 문제가 된다. 그리고 꼭 스레드를 안쓰더라도 여러 프로세스가 메모리를 공유하는 경우에도 문제가 될 수 있다.

이 문제를 Synchronization Problem이라고 한다.

### Synchronization Problem
Concurrency로 인해, 비결정적(non-deterministic)인 결과가 나온다.

- 복수개의 concurrent thread가 공유된 자원에 접근할경우, race condition이 생긴다.
- 결과가 비결정적이기 때문에, 입력이 같아도 타이밍에 따라 다른 결과가 나올 수 있다
- 디버깅하기 힘들다 (Heisenbugs)

공유자원에 대한 접근을 제어하기위해, 동기화 메커니즘이 필요하다

- Synchronization restricts the concurrency
- Scheduling is not under programmer's control

### Concurrency in the Kernel
컨커런시와 동기화 문제는 1950~1960년대에 이미 OS 분야에서 큰 문제였다. OS는 태생적으로 컨커런트한 소프트웨어여서 그렇다. 프로세스들끼리 아무 컨커런시가 없다 하더라도, 여러 프로세스들이 동시에 시스템콜을 쏘고, 동시에 하드웨어들도 시도떄도 없이 여러종류의 인터럽트를 발생시켜서, OS에선 아주 오래 전부터도 컨커런시와 동기화가 중요했다.

OS에서 공유자원을 보호하기 위해 쓰는 방법을 알아보자

&nbsp;

Week 10, Tue
========

### Critical Section
임계영역, 여러 스레드가 동시에 실행하면 안되는 코드영역. 한 자원을 읽거나 고치는 코드는 critical section일 가능성이 높다. 자원을 읽기만 하는 코드여도, 다른 코드가 그 자원을 업데이트한다면 critical section이 될 수 있음.

Critical section에 대해서 mutual exclusion을 할 필요가 있다

- Atomic하게 critical section을 실행할 필요가 있음 (all-or-nothing)
- 한 스레드만 critical section를 실행해야
- 다른 스레드는 critical section 시작점에서 대기해야
- critical section을 실행중이던 스레드가 critical section을 나오면, 대기중이던 스레드중 하나가 진입

### Locks
Lock은 다음의 두 연산으로 mutex를 지원하는 메모리상의 객체다.

- acquire(): Wait until lock is free, then grab it
- release(): unlock and wake up any thread waiting in acquire()

락 쓰는법

- 락은 맨 처음에 열려있다
- critical section에 진입하기전에 acquire()를 부르고, 나온 뒤 release()를 불러야한다
- acquire()는 락을 잡을때까지 리턴하지 않는다
  - 락을 잡을때까지 Busy wait 하는거: spinlock
  - 락을 잡을때까지 block 하는거: mutex
- 락을 잡고있는 스레드는 최대 한개

락의 요구조건

- Correctness
  - Mutual exclusion: 임계영역에 스레드가 두개 이상 동시 진입하면 안됨
  - Progress (deadlock-free): 기다리는 스레드가 있다면, 임계영역에 스레드가 최소한 하나는 진입해야함
  - Bounded waiting (starvation-free): 모든 스레드가 언젠가 진입해야함
- Fairness: 모든 스레드가 락 acquire 기회를 공평하게 받는다
- Performance: contention이 많더라도 오버헤드가 적어야함

### Implementing spinlocks: An initial attempt
락 구현이 쉽지않다. 락 구현 자체도 critical section을 필요로 하기 때문이다. 아래는 잘못된 예제이다

```c
struct lock { int held = 0; }

void acquire(struct lock *l) {
  while (l->held);
  l->held = 1;
  // NOTE: 여기서 atomic 보장 안됨!!!!!
}

void release(struct lock *l) {
  l->held = 0;
}
```

### Lock 구현 사례들
- Software-only
  - 1962: Dekker's algorithm, 스레드가 두개일 때
  - 1981: Peterson's algorithm, 스레드가 두개일 때
  - 1974: Lamport's Bakery algorithm, 스레드가 복수개일 때, 들어가는 순서대로 번호표를 뽑는 방식이어서 bakery algorithm이다
- Hardware atomic instructions
  - Test-and-set, compare-and-swap, load-linked, store-conditional, fetch-and-add, ...
- Controlling interrupts (CPU가 하나일때에만 사용 가능)

Software-only는 너무 복잡하고 어려워, 보통은 hardware atomic instruction을 활용한다

### Implementing spinlocks: the second attempt
스레드가 두개뿐이라고 가정하고, Software-only Algorithm으로 구현해보자. 아래 코드는 위 예시를 강화한건데 여전히 문제가 있다.

```c
int interested[2];

void acquire(int process) {
  int other = 1 – process;
  interested[process] = TRUE;
  // NOTE: 여기서 스케줄링된다면?!
  while (interested[other]);
}

void release(int process) {
  interested[process] = FALSE;
}
```

둘 다 들어가지는 현상은 막을 수 있다: mutex는 보장한다. 문제는 주석친곳에서 스케줄링되면, 스레드 두개가 서로 양보하려고만 하면서 데드락에 빠질 수 있다: progress 조건을 만족 못한다.

### Implementing spinlocks: Peterson's Algorithm
`turn` 변수를 만들면 된다.

```c
int turn, interested[2];

void acquire(int process) {
  int other = 1 – process;
  interested[process] = TRUE;
  turn = other;
  while (interested[other] && turn == other);
}

void release(int process) {
  interested[process] = FALSE;
}
```

turn: 두 스레드 간 contention이 존재하는 상황에서, 어떤 스레드가 임계영역에 진입할지를 결정하는 변수.

요즘은 메모리 리오더링을 많이해서, 이런 코드가 제대로 동작하지 않을 수 있다.

### Atomic instructions
메모리에 있는것을 read-modify-write 하는 과정이 atomic하게 실행되는것을 보장해주는 명령어. 여러 종류가 있는데, 제일 유명한건 test-and-set 이다.

Test-And-Set: x86의 `xchg`, RISC-V의 `amoswap`, 메모리주소와 레지스터를 교환해주는 명령어

### Implementing spinlocks: using test-and-set
훨씬 쉽다. xv6 spinlock이 이렇게 구현되어있음. spinlock.c 참고.

```c
struct lock { int held; };

void acquire(struct lock *l) {
  while (TestAndSet(&l->held, 1));
}

void release(struct lock *l) {
  l->held = 0;
}
```

### Implementing spinlocks: using compare-and-swap
x86의 `cmpxchg`. Sparc를 비롯해 여러 CPU에 널리 존재함

swap(test-and-set)과 비슷한데, 항상 스왑하는게 아니라 메모리에 있는 값이 expected와 같을 떄에만 스왑함.

```c
struct lock { int held; };

void acquire(struct lock *l) {
  while (CompareAndSwap(&l->held, 0, 1));
}

void release(struct lock *l) {
  l->held = 0;
}
```

### Implementing spinlocks: using LL & SC
MIPS, Alpha, PowerPC, ARM, RISC-V 등에서 지원됨

- Load-Locked, LL: 메모리에서 값 읽어옴
- Store-Conditional, SC
  - 직전 LL과 SC 사이에 해당 메모리에 intervention이 없었다면 값을 잘 저장하고 1을 반환
  - 직전 LL과 SC 사이에 intervention이 있었다면 값을 저장하지 않고 0을 반환

```c
struct lock { int held; };

void acquire(struct lock *l) {
  while (1) {
    while (LL(&l->held));
    if (SC(&l->held, 1)) { return; }
  }
}

void release(struct lock *l) {
  l->held = 0;
}
```

TAS, CAS는 비관적(pessimistic)인 방법, intervention이 있을거라고 가정하고 모든 행동을 조심스럽게

LL+SC는 낙관적(optimistic)인 방법, intervention이 없을거라고 가정하고 일단 진행한 뒤 intervention이 있었다면 다시 실행

intervention이 있었는지 여부를 어떻게 체크하나? 보통은 Cache 수준에서 모니터링 한다. Cache 코히어런스 프로토콜이 어차피 돌고있기때문에.. 그걸 사용해 모니터링 할 수 있다.

요즘은 하드웨어 트랜잭셔널 메모리라고 LL+SC보다 확장된게 있다. LL+SC는 메모리 위치 하나만 감시하는건데, `xbegin` `xend` 이렇게 트랜잭션을 펼쳐서 트랜잭션 사이에 조작된 모든 메모리를 감시하는 기능도 있음.

### Implementing spinlocks: using fetch-and-add
x86의 `xadd`, RISC-V 등에서도 지원됨.

원자적으로 메모리에 값을 더하면서, 동시에 옛날 값을 리턴함. 이걸로 Bounded waiting을 구현할 수 있음.

ticket lock: 들어가는 순서대로 티켓을 받고, 내 차례가 오면 크리티컬섹션에 진입한다.

```c
struct lock { int ticket, turn };

void acquire(struct lock *l) {
  int myturn = FetchAndAdd(&l->ticket, 1);
  while (1->turn != myturn);
}

void release(struct lock *l) {
  l->turn += 1;
}
```

### Controlling interrupts
커널 안일때, 그리고 싱글코어 CPU일때 쓸 수 있는 트릭

```c
void acquire(struct lock *l) {
  cli(); // disable interrupts (clear interrupt flag)
}

void release(struct lock *l) {
  sti(); // enable interrupts (set interrupt flag)
}
```

싱글코어 CPU일 경우, 시스템콜을 실행하다가 인터럽트가 걸리거나, 인터럽트 핸들러가 실행되다가 인터럽트가 걸리거나, 이런 경우에만 동기화 문제가 생긴다.

그래서 싱글코어 CPU일 경우, 그냥 인터럽트를 끄는것으로 lock을 구현할 수 있다. 락에 연관된 다른 state가 없다.

멀티코어에서 못 쓰는 이유: 코어마다 인터럽트 플래그가 따로 있음.

xv6의 `intr_off()` + `intr_on()` vs `push_off()`, `pop_off()`: push_off pop_off를 쓰면 인터럽트를 무조건 끄고 켜는것이 아니라, 인터럽트 켜고 끄기를 nesting하여 처리할 수 있다.

- 장점
  - 심플
  - 싱글코어에서 유리
- 단점
  - 커널만 쓸 수 있음: 유저가 인터럽트를 마구 켜고 끄면 안되니까..
  - 멀티코어에서 못 씀
  - 크리티컬 섹션이 길어지면, 중요한 인터럽트를 놓칠 수 있음 (타이머 인터럽트, 디스크 인터럽트)
  - 현대 CPU에선 아토믹 쓰는게 더 빠를 수 있음

### 요약
스핀락은 몹시 낭비가 심하다. 스핀락을 돌고있는동안은 아무 진행도 못하고, CPU 사이클도 낭비한다. busy waiting하고있는 스레드들이 CPU 사이클을 낭비하는 동안, 정작 실행되어야하는 락을 들고있는 스레드의 실행이 늦어질 수 있다.

모든 락을 스핀락으로 구현하면 안된다. 스핀락은 잠깐잠깐 도는 작은 락에만 쓰는거다. 길게 실행되는 락이 필요하면, 제대로된 block 되는 버전의 락을 만들어야한다. 스핀락을 primitive synchronization mechanism으로 써서, 이런 higher-level 동기화 객체를 만들어야 한다.

&nbsp;

Week 10, Thu
========
기말고사 일정 확정

- 6월 18일 11:00 ~ 12:50
- 302동 106호(짝수) 107호(홀수)
- 범위
  - Textbook Ch 2, 4~8, 13~16, 18~23, 26~28, 30~31, 36~37, 39~42, 44
  - xv6 (디자인 문서, 구현체, 등)
  - 강의 슬라이드
- 치트시트 허용. A4용지 하나 양면, 손으로쓴것만 가능

성적 정책

- 시험: 50%
- Projects: 50
  - PA1 01%: hello, world!
  - PA2 02%: syscall
  - PA3 06%: ^C
  - PA4 09%: Scheduler
  - PA5 12%: Virtual memory
  - PA6 20%: ???

## 14. Semaphores
busy-wait하는게 아니라, block 되는 버전의 동기화 객체가 필요하다.

- Mutual exclusion: 임계영역 안에 하나의 스레드만 진입
- Waiting for events: 한 스레드가 더 진행하기 전에 다른일이 완료되기를 대기함
  - producer/consumer: MPMC가 존재할 수 있음
  - pipeline: a series of producer and consumer
  - defer work with background thread: non-critical work in the background when CPU is idle

"자꾸 더러운 예시를 들어서 죄송한데... 상호배제는 집의 화장실이라고 할 수 있어요. 화장실은 혼자서 쓰는거니까요. 근데 화장실에 휴지가 없으면 어떻게 해요? 만약 mutex밖에 없다면, 화장실에 휴지가 생길때까지 계속 화장실에 무한히 들어갔다 나왔다를 반복해야해요. (busy wait) 화장실을 들어가지 않고 화장실 앞에서 기다리고있다가, 다른사람이 화장실에 휴지가 생겼을때 깨워주면 좋지 않을까? (waiting for events)"

### Higher-level synchronization
스핀락과 인터럽트 끄기로는 불충분하다. 아주 짧은 임계영역을 관리하는 용도로만 써야함. Higher-level 동기화 메커니즘이 필요하다

- 세마포어
  - 간단하지만 강력하다
  - 프로그래밍하기 힘들다
- 뮤텍스 + condition variables
  - pthread에 쓰인다

### Semaphore
철도 교차로에 있는 신호기를 세마포어라고 한다. 교차로에 들어갈 수 있는지 없는지 알려주는 신호기.

Dijkstra씨가 1968에 THE OS라는 OS도 개발하셨었는데, 거기에 들어갔음. Busy-wait가 아니라 block 하는 동기화 객체임. 세마포어 객체 안에 정수 state가 있고, 이 정수 state는 외부에서 직접 접근이 불가능하지만 세마포어의 동작을 결정해준다.

두개의 연산을 지원함

- Wait(), down(), sem_wait()
  - state를 1 줄이고, state가 양수가 될때까지 대기
  - 네덜란드어 Test의 앞글자를 따 P 라고도 부름
- Signal(), up(), sem_post()
  - state를 1 늘리고 기다리고있던 스레드 하나를 깨움
  - 네덜란드어 increment의 앞글자를 따 V 라고도 부름

PV 세마포라고도 부름.

Initial state가 1인 세마포는 스핀락이랑 동치이나, busy-wait 하지 않아서 더 좋음. 그리고 spinlock과 다르게 initial state가 0, 2, 3, 4 등 다양한 숫자가 될 수 있음. 음수 state도 가능함.

```c
struct semaphore {
  int value;
  struct process *Q;
  struct spinlock lock;
};

void wait(struct semaphore *S) {
  acquire(S->lock);
  S->value--;
  if (S->value < 0) {
    add this process to S->Q;
    release(S->lock);
    block();
    return;
  }
  release(S->lock);
}

void signal(struct semaphore *S) {
  acquire(S->lock);
  S->value++;
  if (S->value <= 0) {
    remove a process P from S->Q;
    release(S->lock);
    wakeup(P);
    return;
  }
  release(S->lock);
}
```

위의 코드에서, wait()과 signal() 함수의 본문은 크리티컬 섹션이다. 왜냐하면 공통된 S->value, S->Q 에 접근하기 때문이다. 그래서 wait() signal() 함수 본체만 스핀락으로 보호해, wait() signal() 함수 호출할때에만 잠깐잠깐 스핀락이 돌도록 한다.

- Binary semaphore (=mutex)
  - 초기값이 1인 세마포어
- Counting semaphore
  - 초기값이 1이 아닌 세마포어
  - 임계영역에 스레드가 최대 N개가 진입할 수 있음
- 초기값이 0인 세마포어는 기본으로 아무도 진입 못하다가, 다른 스레드에서 시그널을 날릴떄에만 진입가능

Lock은 acquire한애가 항상 release해야함. 근데 세마포어는 wait 한애가 나올떄 signal을 의도적으로 안하기도 함.

### Bounded Buffer Problem
환형큐가 하나 있고, 걔에 데이터를 넣는 producer와 걔에서 데이터를 뽑는 consumer가 있다고 하자.프로듀서와 컨슈머가 여럿 있는 MPMC 상황이다. 얘네 동기화를 어케할까?

네개의 세마포어를 아래와 같이 초기화하고

- mutex_in = 1
- mutex_out = 1
- empty = N
- full = 0

그리고 아래와 같이 코딩하면 된다.

```c
void produce(data) {
  wait(&empty); // 버퍼에 빈자리가 하나라도 있을경우 통과, 빈자리 없으면 진입 못함
  wait(&mutex_in); // enqueue는 한번에 하나만
  buffer[in] = data;
  in = (in+1) % N;
  signal(&mutex_in); // 다음 enqueue 시작
  signal(&full); // 큐에 데이터 하나 새로 생겼음, full 세마포어에 시그널
}

void consume(data) {
  wait(&full); // 버퍼에 데이터가 하나라도 있을경우 통과, 데이터 없으면 진입 못함
  wait(&mutex_out); // dequeue는 한번에 하나만
  data = buffer[out];
  out = (out+1) % N;
  signal(&mutex_out); // 다음 dequeue 시작
  signal(&empty); // 큐에서 하나 빠져서 버퍼에 빈자리가 하나 생겼음, empty 세마포어에 시그널
}
```

세마포어 문제가 이거임. 남이 쓴거 이해하는거는 괜찮은데, 나보고 이걸 창작하라고 하면 너무 어려움.

### Readers-writers problem
공유 자원이 있고, 어떤 스레드는 이걸 읽기만 하고 어떤 스레드는 이걸 쓰기만 함.

- 읽기는 중첩 실행 허용됨
- 쓰기는 한번에 하나만 가능

```c
// number of readers
int readcount= 0;

// mutex for readcount
Semaphore mutex = 1;

// mutex for reading/writing
Semaphore rw= 1;

void Writer() {
  wait(&rw);
  ...
  // Write
  ...
  signal(&rw);
}

void Reader() {
  wait(&mutex);
  readcount++;
  if (readcount == 1) {
    // 쓰기가 진행되고있었을 수 있음, 대기 시작
    wait(&rw);
  }
  signal(&mutex);
  ...
  // Read
  ...
  wait(&mutex);
  readcount--;
  if (readcount == 0) {
    // 모든 읽기가 끝났음, rw 에 시그널
    signal(&rw);
  }
  signal(&mutex);
}
```

이 구현은 Reader가 끊이지 않으면 Writer에 starvation이 일어나지 않음. Reader에 flavor가 있는 구현임.

Writer에 starvation 안일어나게 하는 구현은 조금 더 복잡함

&nbsp;

Week 10, Tue
========
드디어 Virtualization과 Concurrency를 마치고, Persistence 에 들어간다. Three pieces 중 마지막이다.

## 13. Hard Disk Drives
주변장치를 다룰때엔, 하드웨어의 특성을 잘 신경써서, 어떻게하면 효율적이고 reliable하게 다룰 수 있는지를 고민해야함.

컴퓨터에 주변장치는 이것저것 많다. 네트워크와 같은 대부분의 주변장치는 나중에 OS에 붙은 반면, HDD는 아주 초창기부터도 쓰였다. 스토리지가 없으면 컴퓨터 재부팅할때마다 모든게 사라지니까.

스토리지는 너무 느렸기 때문에 OS에서 아주 신경써서 다뤄야했다. 특히 스토리지에는 에러도 많이 나고, 쓰다가 갑자기 뽑는다던가 쓰다가 갑자기 power가 나간다던가 이런 상황이 다양하게 발생한다. OS가 이런 문제에 잘 대처해야, USB를 쓰다가 뽑았더니 인식이 안되거나, 정전때문에 컴퓨터가 다시 켜졌더니 file system이 마운트되지 않는다던가 이런 문제들로부터 해방될 수 있다.

### Modern System Architecture
요즘 컴퓨터는 이렇게 생겼다.

(PPT 참고)

여러 코어의 CPU들과, CPU에 직결되어있는, DDR4 RAM, PCIe 3.0 lanes 들이 있다. 직접 붙어있는 CPU와 통신할때 가장 빠르고, 다른 CPU에 붙어있는 장치에 액세스할때엔 약간 느려짐.

그리고 PCH(Platform Controller Hub, 옛 south bridge)에 연결된 USB 3.0/2.0 포트들, SATA, PCIe 2.0 포트들, 이더넷 컨트롤러

노스브리지는 사라졌다.

### A typical I/O device
- Control
  - Special instructions (x86의 `in`, `out`): I/O 전용 특수 명령어 만들기, 최근에는 잘 안쓰임
  - Memory-mapped I/O (load & store): 보통 이 방법이 쓰임
- Data transfer
  - Programmed I/O (PIO): CPU가 하나하나 복사해주는거, 느림
  - DMA: Memory bus를 통해 자동으로 복사되는 모델, 훨씬 빠름
- Status check
  - Polling
  - Interrupts

주변장치도 작은 컴퓨터다. 애플 스마트 키보드에도 72MHz 32-bit ARM Cortex-M CPU가 박혀있음. HDD에도 CPU가 들어가있고, 요즘 SSD에도 CPU가 3~4개씩 들어있음

- Device interface
  - Registers (Status, Command, Data)
- Hidden internals
  - Micro-controller (CPU)
  - Memory (SRAM, DRAM, 혹은 둘 다)
  - Firmware
  - Other device specific mechanical/electronic components

CPU와 코드 없이 모조리 하드웨어로 할수도 있지만, 요즘은 하드웨어로 와어링하는 대신 로직을 firmware 코드로 넣은 뒤 CPU가 컨트롤하게 하는 방식을 많이 쓴다. 고치기 쉬우니까. Firmware는 하드웨어와 소프트웨어의 중간을 지칭하는 말.

### Classifying I/O Devices
- Block device
  - Fixed size block들에 정보를 저장, 자체 block address space를 갖는다
  - 보통 블럭 하나는 512B ~ 4KiB
  - 블럭 단위로 읽고 쓸 수 있다
  - HDD, SSD, CD, DVD, tapes, 등
- Character device
  - Byte stream으로 주고받는 디바이스
  - Addressable하지 않음, seek 지원하지 않음
  - 프린터, 네트워크, 마우스, 키보드

여러분들은 테이프디스크 안써보셨죠? 플로피디스크도 안써보셨죠? 플로피디스크 많이들 아시네요. 생각보다 그렇게 신세대는 아니네요. 저랑 좀 더 가까운것같군요. 5.25 플로피디스크도 아세요? 이것도 알면 정말 가까운건데.

자기테이프(테이프드라이브)는 죽을거라고 사람들이 생각했는데, 안죽고 아직도 많이 쓰이고있어요. 저렴하게 높은 집적도로 데이터를 백업하는 용도로 쓰고있어요. 그리고 수 페타바이트의 엄청난 용량의 데이터를 데이터센터 사이에서 옮길때에도 자기테이프에 담아서 써요.

### I/O Stack
(PPT 참고)

I/O Device는 종류가 몹시 많다. 커널 코드의 대부분은 수많은 I/O 장치에 대응하는데에 사용된다.

리눅스에선 장치도 file descriptor로 만든다. 유저 프로세스가 디바이스 FD에 read/write 하면 장치에 I/O 할 수 있음.

여러 장치들에 대해 공통적으로 수행될 수 있는 코드가 있는데, 이것이 device-independent softwares

Device driver와 interrupt handle는 각 I/O 장치에 특화된 코드. 종류가 매우 많다.

### Device drivers
각 I/O 장치를 컨트롤하기 위한 Device-specific code.

드라이버 로딩하는법

- Static link
  - 드라이버 바꾸려면 커널 재빌드해야함
- Selectively loaded during boot time
  - 이러면 컴퓨터 켜지고나서 장치를 바꿔끼기 곤란함
- Dynamically loaded during run time
  - Hot pluggable device를 관리하기에 편리함

최대한 많은 장치에 대해 구현을 해줘야하는데, 이것이 몹시 어렵다.

많은 드라이버들은 각 드라이버에 대한 대응팀이 있다. 그렇게 대응 팀을 따로 보고, 커널문제인지 하드웨어문제인지 디바이스문제인지 찾아, 빠르게 처리한다.

여전히 OS의 크래시가 대부분 드라이버 코드에서 발생한다. Windows XP 크래시의 85%는 드라이버였음. 리눅스에선 드라이버 코드가 커널의 7배임.

5%의 윈도우는 매일 크래시된다. 민감한곳에선 이런 크래시의 결과가 심각해짐.

OS extensions are increasingly prevalent. 리눅스 코드의 70%가 확장임. less experience programmer에 의해 작성됨.

### Secondary storage
Primary memory 이외의 모든 스토리지는 모두 보조기억장치.

Sector의 배열로 추상화되어있음. 호환성을 위해 512B 섹터도 지원하나, 보통은 4KiB 단위로 읽고씀.

HDD의 특징

- 큼: 100GiB 이상
- 저렴함: 2020년 5월 기준으로 8TiB SATA3 HDD가 27만원
- 퍼시스턴트: 전원이 날아가도 데이터가 보존됨
- 느림: 액세스에 수 밀리초 소요됨

### HDD Architecture
Platter의 앞면/뒷면 surface에 데이터를 기록함. 플래터는 여러개일 수 있음. Arm assembly에 붙어있는 read-write head가 동시에 움직임.

여러 Platter에 걸쳐있는, 여러 같은 동심원상의 트랙 데이터들의 묶음은 cylinder라고 부름. 한 실린더에 있는 데이터들은 동시 접근이 용이함.

바깥쪽 원으로 갈수록 동심원당 track 길이가 커져서 bandwidth가 달라짐. 바깥쪽 동심원에 있는 데이터를 더 빨리 읽을 수 있음.

섹터 크기랑 블럭 크기랑 다름. 섹터크기는 디스크가 지원하는 I/O의 단위, 블록은 소프트웨어가 보는 컴퓨터와 디스크가 통신하는 크기의 단위. 섹터크기와 블럭크기가 같을 수 있으나, 블록 크기가 섹터 크기의 정수배일수도 있다. 블럭이라는 용어가 여기저기에서 많이 쓰여서 맥락을 잘 확인하고 쓰자. 예를들어 파일시스템에서도 블럭이라는 용어를 쓴다.

SSD는 HDD보다 훨씬 레이턴시가 빠르지만 DRAM같은것들보단 훨씬 느림. 그리고 SSD는 Block device여서 DRAM을 대체할수는 없다.

질문을 항상 하는사람들만 하는데, 닉네임을 바꾸셔도 되니까 주저하지 말고 질문을 해주세요.

&nbsp;

Week 10, Thu
========
하드디스크가 50년대 말부터 2000년도까지 항상 보조기억장치로 쓰였었음. 거의 60년 가까이 보조기억장치 = 하드디스크 였음. 지금은 SSD도 같이 쓰이고있지만, 용량 대비 가격때문에 여전히 하드디스크는 중요하게 쓰이고있음.

문제는 수 ms 단위의 느린 접근시간, 레이턴시였음. 불량도 많이 났고. 그럼에도 불구하고 계속 쓸 수밖에 없어서, OS 입장에선 매우 귀찮은 존재였음. 그래서 OS들은 어떻게하면 하드디스크를 더 빠르게 쓸 수 있을까 이런 고민을 많이 했음.

최근엔 OS가 "어차피 하드디스크는 느리니까.."하면서 방만하게 만들었던 것들이, SSD로 바뀌면서 문제가 되기 시작했음.

### 모던 HDD
(PPT 참고)

- 8개의 헤드(=플래터의 한쪽 면, 서페이스), 4개의 디스크
- 트랙당 64섹터, 16383개의 실린더
- 평균 Track density (반지름 상에서 단위길이당 트랙 밀도): 540K TPI (tracks/inch)
- 평균 Areal density (단위면적당 정보 밀도): 1203 Gbits/sq.inch
- Spindle speed: 5400 RPM (11.1ms/rotation)
- Internal cache buffer: 256MiB
- Average Latency: 6.0ms (옛날엔 평균 15.0ms였음)
- Max I/O data transfer rate: 600 MiB/s (SATA3)
- Max data transfer rate: 190 MiB/s
- Power-on to ready: under 15 seconds

이걸 보면 HDD도 엄청난 하이테크 기술임을 알 수 있다.

Barracuda 시리즈가 원래 7200RPM이었는데, 5400RPM으로 낮췄어요. 제 대학 동기중에 저런 하드디스크 펌웨어만 수십년 만든 하드디스크 장인이 있다. 하드디스크 뜯으면 나오는 녹색 기판에 시리얼 연결하고 하드디스크를 켜면, 하드디스크 부팅할때에 나오는 디버그 메시지를 볼수있다고.

HDD에 DRAM cache가 있다. 근데 얘가 write cache 역할을 해서, HDD가 썼다고 응답까지 했는데도 실제로는 DRAM에 상주해있다가, 미처 디스크에 쓰기 전에 HDD가 꺼지는 경우가 있다. 근데 OS 입장에서 "이 데이터는 반드시 써야 퍼시스턴시가 보장됨" 이런경우가 있다. 그 경우 flush cache 커맨드를 하드디스크한테 따로 날린다.

원래는 Average seek time이라는 메트릭을 썼는데, 이게 슬그머니 사라지고 average latency라는 뭔지 잘 모르겠는 메트릭으로 바뀌었다. average seek time이 full stroke 시간의 반일것 같지만 full stroke의 1/3이라는걸 적분기호까지 써가며 증명한게 있다. 근데 여기에다가 디스크 도는 주기까지 추가해야 실제 레이턴시가 나온다.

power-on to ready 시간이 긴데, 물리적으로 디스크가 켜져서 가속하는데에 시간이 필요해서 이 시간이 길 수 있다.

하드디스크 헤드가 하드디스크에 붙었다 떨어졌다를 반복해야하는데, 이게 얼마나 정말하게 움직이냐면, 과거 비유로 지구를 25초에 한바퀴씩 도는 비행기가 지면에서 1mm 높이로 붙었다 떨어졌다를 반복하는 정도라고 한다.

### Interfacing with HDD
굉장히 수동적인 device임. OS가 읽으라고 시켜야 읽고 쓰라고 시켜야 쓴다. 심지어 과거에는 한번에 하나의 command만 처리할 수 있었음. 쓰는건 buffer에만 쓰면 되니까 좀 빠를 수 있지만, read는 buffer에 있을 확률이 적어 좀 느렸음.

- Cylinder-Head-Sector (CHS) scheme

  OS가 어디에 쓰라고 모조리 지정해주는 방식. OS가 디스크의 실린더가 몇개, 헤드가 몇개, 섹터가 몇개 이런식으로 디스크의 물리적인 정보를 다 알아야만 했음.

- Logical block addressing (LBA) scheme

  SCSI에서 도입됨. 하드디스크가 [0, 1, 2, ..., N-1] 이렇게 블록의 배열로 추상화되어있고, 이걸 LBA라고 부름. 디스크가 LBA를 물리적으로 어떻게 mapping할지 결정함. 디스크의 물리적인 정보는 OS로부터 숨겨짐.

CHS시절에는 디스크의 물리적인 정보가 미리 컴퓨터 BIOS에 입력되어있어야만 했음. BIOS에 해당 하드디스크 정보가 미리 입력되어있지 않으면, 손으로 쳐줘야만 했음.

CHS시절에는 OS가 하드디스크의 물리적인 정보를 다 알 수 있으니까, 인접한 데이터는 한 실린더 상에 밀집시킨다던가 이런 테크닉도 쓸 수 있었음.

SCSI는 엔터프라이즈용 인터페이스. 일반 사용자는 ATA(PATA) 썼음. SCSI, PATA 둘다 parallel 인터페이스였음. 요즘은 다 SCSI랑 ATA 둘다 serial interface 버전인 SAS(Serial attached SCSI), SATA로 바꿨음.

왜 parallel 인터페이스보다 serial interface가 빠른가? clock rate를 아주 많이 올렸더니, parallel 하게 보내도 lane간의 딜레이 차이가 발생해서 빠른 clock rate를 활용하지 못하는 문제도 있고, lane들끼리 전기적으로 간섭해서 데이터가 깨지는 문제도 발생한다. 케이블도 커지고. 그래서 단순한 serial interface가 clock rate를 올리는데에 오히려 더 유리했다.

SAS를 지원하는 HDD는 SATA보다 훨씬 비싸용. 그리고 SAS는 용량이 아니라 속도와 신뢰성으로 승부하는애라, 용량이 적은대신 10000RPM 이상의 높은 속도를 갖는다.

### HDD Performance factors
- Seek time (T<sub>seek</sub>)

  Disk arm이 맞는 실린더에 가기까지의 시간. 실린더 거리에 달려있고, linear한 cost가 아니다. 적분 해서 계산해보면 Full seek time (맨 안쪽 실린더에서 제일 바깥 실린더까지의 시간)의 1/3 이다.

- Rotational delay (T<sub>rotation</sub>)

  head가 맞는 sector에 도달할때까지 기다리는 시간. RPM에 의존한다.

- Transfer time (T<sub>transferk</sub>)

위 세개의 지표로 Random Read/Write, Sequential Read/Write 딜레이를 계산할 수 있다.

### HDD Performance comparison
(PPT 참고)

SAS 하드디스크가 용량을 많이 키우지 않는 이유가 이거다. Seek time을 줄이려고.

Unwritten Contract: 문서화되어있지는 않지만, 디스크 만드는 사람도 보장하고, OS 만드는 사람도 사용하는 약속.

HDD에서의 unwritten contract: LBA 상에서 데이터를 연속하게 배치할 경우, 실제 물리적으로도 sequential하게 access할 수 있게 보장해줌.

하드디스크를 위해 OS가 하는 최적화: 가급적이면 같이 쓰는 데이터는 sequential하게 인접하게 두자.

요즘 LevelDB, RocksDB 이런애들이 HDD를 위해 하는 일이 있는데 걍 그게 다 디스크 상에 모두 시퀀셜하게 저장하는거임.

### Disk Scheduling
요즘은 큰 의미는 없지만, 과거에는 중요했음. 디스크가 `seek()`가 너무 많아지면 arm 움직이느라 발생하는 OS의 시간 낭비가 커서, seek를 어디부터 할 지 스케줄링을 시켰음

얘도 CPU처럼 이렇게 나뉨

1.  Work conserving scheduler: 항상 무슨 일을 하려고 시도
2.  Non-work conserving scheduler: 잠깐 쉬는게 더 빠를수도 있다. 특히 IO는 CPU와는 다르게 preemption이 불가능해서 더 그러함.

아래와 같은 종류가 있음

- FCFS: First-Come First-Served
  - No scheduling
- SSTF: Shortest Seek Time First
  - 가운데의 block을 불공평하게 선호함
  - 하드디스크 지오메트리가 OS에 available하지 않을경우, NBF(Nearest-Block-First)
- SCAN
  - 엘리베이터 알고리즘. 일단 한 방향으로 가면 쭉 그 방향으로 가기
  - 가운데 친구들에게 유리함
- F-SCAN
  - sweep을 하는 동안은 queue를 freeze함, far-away requests가 starvation되는것을 막을 수 있음
- Circular SCAN
  - 한쪽 방향으로 가는 SCAN 알고리즘
  - Uniform wait times

### Modern disk scheduling
이제 OS는 디스크의 지오메트리 정보를 알 수 없음. 시퀀셜하게 액세스하는것이 빠르다는것밖에 알 수 없다.

- 디스크 스루풋 증가
  - HDD에 요청을 보낼 때, request들을 merge할 수 있으면 merge함
  - Disk seek time을 줄이기 위해 request를 정렬해서 보냄
- 스타베이션 방지
- Fairness
  - CFQ: Completely Fair Queue, CFS의 HDD 버전
  - 각 프로세스마다 Disk I/O Queue를 따로 제공하고, round robin 순서대로 돌면서 정해진 time slice 내에서 각 프로세스의 I/O를 처리함

&nbsp;

Week 11, Tue
========
**TODO**

- Q: 오늘 SSD 펌웨어가 배경에서 하는 다양한 일들을 잔뜩 배웠는데, 이게 SSD 성능에 어느정도로 영향을 주나요?
- A: 성능에 엄청난 옇양을 줍니다. 4TB면 4GB의 DRAM이 필요하고 아까 했는데, 이거 다 FTL이 페이지매핑 유지하느라 필요한거임. 페이지매핑 테이블은 멀티레벨 안하고 리니어하게 들고있는데, 멀티레벨 테이블로 하면 성능을 너무 많이 깎아서 그럼. FTL이 성능에도 영향을 주지만 신뢰도에도 영향을 많이 줍니다.

NVMe에선 커맨드들을 받아들이는 Doorbell Register가 존재함. SATA 시절에는
복수개의 커맨드 레지스터 하나하나에 커맨드를 써야했는데, 지금은 커맨드를 큐로
만든 뒤 큐의 시작주소를 doorbell register에 등록하면 알아서 커맨드를 읽어간다.

FPGA로 SSD 펌웨어 가속하고 이런것도 해볼 수 있을까

&nbsp;

Week 11, Thu
========
> 2020-06-04

NAND flash. 절연된 방에 전자가 몇개 있는지로 0, 1 여부를 판단.

- Seek time 없음
- Read/write access time이 비대칭
  - read: ~50µs
  - write: 수백 µs ~ 0.5ms
  - erase: ~3ms
  - Cell이 손상될수록 write 속도가 빨라진다. 그래서 write 시간을 재서 cell의 손상 정도를 알수도 있다.
- No in-place update, FTL이 필요함
- sequential read/write, random read 좋음, random write 나쁨
- SSD에 writable한 블록 수가 줄수록 GC로 인해 random write 성능이 급락한다
- Wear-leveling

전통적인 OS들은 HDD에 최적화되어있다. SSD를 지원하기위해선 OS들이 변해야한다.

Physical Block size와 Logical Block size에 차이가 있을 수 있는데, 이경우 보통 Physical Block size를 기준으로 매핑함. Logical Block size 크기가 더 큰데 logical block size 기준으로 매핑하면, write할때 오버헤드가 커져서.

### SSD Support in OS
SSD를 잘 쓰려는 노력이 다방면으로 존재한다.

- SSD 대상으로는 defragmentation 비활성화
  - SSD는 파일이 한곳에 있으나 멀리 떨어져있으나 성능에 큰 영향이 없음. 괜히 조각모음 하면 write 수가 더 늘어남.
- New "TRIM" or "discard" command: Remove-on-delete
  - 삼성과 MS가 열심히 일해서 만듦
  - HDD시절에는 파일 삭제가 필요하면 그 파일 메타데이터만 지웠지 파일이 들어있는 영역을 하나하나 지우지는 않았음
  - 그러나 SSD에서는 그 파일 블락이 삭제되었다고 SSD에 알려주지 않으면, SSD가 해당 영역을 GC하지 못하고 계속 들고있어야함
  - 그래서 새 커맨드가 추가되었음
- Simpler I/O scheduler
  - NVMe SSD를 쓰면 I/O scheduler를 거의 bypass하고, NVMe queue에 바로 집어넣게된다.
  - 요즘 심지어 read() 시스템콜에서 sleep 하는게 NVMe SSD에서 불필요하게 느려서 read()에서 busy wait하도록 구현하는 경우도 있음
- Align file system partition with SSD layout
  - SSD 블록의 시작점 (4KiB의 배수)가 아니라 SSD 블록 중간에서 파티셔닝을 해서 SSD 블록과 logical block address가 align이 안맞으면, 문제가 너무 많아짐. Write도 너무 많아질 수 있고.
  - Align을 항상 맞춰줘야함.
  - 김진수 교수님 연구소 대학원에서 불과 몇주 전에 겪은 문제
- Flash-aware file system (ex: F2FS in Linux)
  - 삼성에서 F2FS 를 개발함. 안드로이드 최근 기본 파일시스템으로 F2FS가 됨. 개발한 사람은 최근 구글갔음
  - 기존 파일시스템은 overwrite기반인데, f2fs는 append 기반(log structured file system)임. File system 수준에서도 GC를 함.
- Larger block size (4KiB)
- New "multi-stream" interface
  - 삼성에서 제안하여 NVMe SSD에 표준화됨
  - SSD 성능에 영향을 제일 많이 주는건 GC의 존재다. 그리고 GC할 때 copy해줘야하는 live data가 적을수록 GC 성능이 좋아진다. 그래서 SSD를 쓸때에 항상 같이 죽을 데이터를 한 블럭 안에 놓으려고 노력한다. live data copy 없이 block을 한번에 erase하고싶어서. 근데 SSD는 어느 데이터들이 한 파일 안에 묶인 데이터인지 이런 메타데이터 정보를 하나도 알 수 없음
  - SSD에 write를 할 때 stream id라는 추가적인 정보를 제공하여, stream id가 같은 데이터는 한 physical한 block에 모으도록 함
  - 현재 stream id의 갯수가 16개정도밖에 지원 안함. 스펙상으로는 수만개도 지원하는데, stream id가 너무 많아지면 또 FTL이 할 일이 너무 많아짐. 그래서 파일시스템이 하기는 무리고 유저가 해야함.

### Beauty and the Beast: SSD의 양면
- 좋은점: 작음, 가벼움, robust, 저렴, 저전력, non-volatile
- 나쁜점: in place update 없음, program/erase 훨씬 느림, erase unit 크기가 read/write unit보다 큼, bit error, limited lifetime

성능과 안정성을 위해 소프트웨어 서포트가 필요하다. 삼성에 SSD 펌웨어 만드는 직원 1000명짜리 실이 하나 있는데, 거기에 상무로 우리과 선배가 세명정도 있다.

김진수 교수님 연구실이 이 SSD만 10년 넘게 하고있는데 아직도 할게 많다.

&nbsp;

File System
--------
SATA는 SCSI의 subset. SATA, SCSI, NVMe와 같은 block interface를 감싸 Generic Block Layer를 노출하고, Generic Block Interface 위에 File system이 올려진다.HDD나 SSD가 아니라 RAM이나 네트워크여도, block layer만 노출하면 다 file system을 올릴 수 있다.

open, read, write, close 이런게 다 File system API다. File system을 쓰면, 유저가 어느 블록을 읽고쓸지를 신경쓰지 않아도, 파일들에 이름만 붙여줘도 스토리지를 사용할 수 있다.

### Storage: A Logical View
스토리지는 Block의 배열이다. 아래의 세 연산을 지원함

- Identify(): 스토리지 정보 반환
- Read(start sector #, # of sectors, buffer addresses)
- Write(start sector #, # of sectors, buffer addresses)

### Abstraction for storage
파일: 이름이 붙어있는 바이트의 집합. 모든 file에는 고유한 ID인 inode number가 붙는다. inode는 파일시스템 내에서 유니크함

디렉토리: Special한 file. 내용에 "file name, inode number" tuple의 배열이 들어있음.

### File System Components
- File contents (data)
  - 바이트열
- File attributes (metadata or inode)
  - File size
  - block locations: 파일이 여러 블락으로 흝어져있을거라 배열 형태임. 파일 용량이 커지면 block locations 용량도 커짐.
  - owner, group, ACL, atime, mtime, ...
- File name

### File System: A Mapping Problem
(filename, data, metadata) -> (a set of blocks)

위 매핑 관리만 해주면 그게 파일시스템이 되는건데, 위 문제를 푸는 방법이 정말 다양함. 파일시스템이 거의 AFS부터 ZFS까지 다있음 (AFS, BFS, CFS, DFS, ..., XFS, ZFS)

### File System Design Issue
컴퓨터를 쓰다가 갑자기 정전이 나도, 하드디스크가 망가지지 않았으면 좋겠다.

- 목표: (가장 우선순위가 높음) Reliability, (2) Performance, (3) Scalability, ...

보통 파일시스템은 reliability가 제일 중요해서, 보수적인 결정을 많이 함. 안드로이드 기본 fs를 ext4를 f2fs로 바꾸는것도 큰 일이었음. 그래서 파일시스템 개발자들은 보통 자기가 만든 fs를 항상 쓰면서 "내가 몇달동안 썼는데 문제가 없었다" 이렇게 데모를 한다.

Scalability: CPU 코어 수에 따른 성능이 리니어하게 증가하는지? 충분히 많은 파일에 대해서도 잘 scale하는지? 충분히 큰 파일에 대해서도 잘 scale하는지? 충분히 큰 디스크에서도 잘 쓸 수 있는지? FAT32 같은 파일시스템은 4GiB 이상의 파일을 저장 못함.
