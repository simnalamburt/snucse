Week 1, Tue
========

ETL은 많이 안쓸거고 학교 홈페이지를 확인해주세요. 그리고 프로젝트 제출 용도로 https://sys.snu.ac.kr 서버를 쓸 예정이니 참고.

선수과목으로 논리설계, 컴퓨터구조, 시스템프로그래밍을 미리 듣고오세요. C, Linux, gcc, gdb, make, 어셈블리, RISC-V를 잘 익혀오세요. 수업 듣는데에 리눅스 혹은 macOS 머신이 필요합니다.

**이번 학기는 RISC-V 머신 위에서 돌아가는 OS를 만든다!**

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

과제: https://github.com/snu-csl/os-pa3
