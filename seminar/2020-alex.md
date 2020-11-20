ALEX: An Updatable Adaptive Learned Index
========
https://github.com/microsoft/ALEX

https://jiayuasu.github.io/files/paper/alex-sigmod2020.pdf

ML, AI 테크닉을 DBMS나 네트워크, OS, 모바일 시스템 최적화에도 적용시킬 수 있다.

MS에서 DB 프로젝트를 한적이 있었는데, 유저에게 드러나지 않은 코드로 컨트롤되는 파라미터가 500가지 가까이 되었었다. 근데 그 파라미터들 대부분이 20년전의 느린 HDD와 같이, 오래 전의 시스템에 맞춰서 세팅되어있고 새로운 시스템에 맞춰져있지 않았다. 그 파라미터를 개발한 사람이 퇴사하면 그 파라미터가 어떤 역할을 하는지 알기 힘들기도 하고, DB를 주기적으로 다시 릴리즈해야해서 새로 만드는 기능을 고치기도 어려운데 기존의 파라미터들을 모두 revisit하기도 힘든것이 현실이었다.

여기에서 이 500가지가 되는 DB의 파라미터들을 ML로 최적화할 수 있지 않을까 하는 생각에 프로젝트를 시작하게 되었다.

지금 Azure Marketplace에 가면, 현재 DB 관련 어플리케이션이 2000개 가까이 되는것을 확인할 수 있다. 근데 이 분야의 전문가가 아닌 이상 뭘 골라야 성능이 제일 잘 나올지 단박에 알기 힘들다. 또한 한번 세팅하면 바꾸기도 굉장히 힘들다.

이 선택과 변화의 고통이 없는 DBMS 시스템을 만들어보자!

Instance-optimized database system: Database system "tailored" to the *initial* requirements, and "adapts" to chaing requirements. Eliminates the pain of *choice* and *change*

State of DBMS today: 한가지 솔루션으로 모든 문제를 풀 수 없다. 여러 솔루션을 섞어서 풀어야함

Instance Optimized DBMS: 디비의 각 컴포넌트 모두에 ML을 적용할 수 있다.

- Learned scheduler
- Learned query optimizer
- Learned runtime
- Learned buffer manager
- Learned storage & indexes

DB 시스템의 가장 기본: B-Tree. 이거를 어떻게 Leearned index structure로 바꿀 수 있을까?

B+ Tree: 제너럴한 자료구조여서 데이터가 무엇인지에 따라 최소 성능이 보장된다. 근데 동시에 데이터가 어떤 성질을 갖고있는지 알고있어도, 그 성질을 활용하지 못하기도 한다.

Learned Index, Kraska et al., 2018: 얘도 tree-like structure를 가짐, Leaf 노드에 가기까지 어느 노드를 타고 갈지는 모델이 결정해줌, 모델이 지정하는 위치에 데이터가 없을수도있는데, 일정 error bound 이내에 데이터가 위치할것을 보장해준다. Static RMI. (RMI = recursive model index)

모델은 굳이 딥러닝이 아니라 리니어 리그레션과 같이 간단한 모델이여도 자료구조가 꽤 잘 동작한다.

Learned Index의 장점: B+ Tree보다 훨씬 작은 인덱스 사이즈로 문제를 풀수도 있고, CPU보다 더 효율적일 수 있다. 읽기속도가 훨씬 빠르다

Learned Index의 단점: 쓰기성능이 나쁘다. insert할때에 배열 전체를 shift해야하는데 이게 비싸다.

Ineffficient key-space parition with Static RMI: 키가 많아지면 퍼포먼스가 non-linear하게 변함

ALEX: update, insert도 효율적으로 처리하면서 B+ Tree보다 좋은 learned index를 만들어보자!

목표:
- Writes competitive with B+ Tree
- Reads faster than B+ Tree and Learned Index
- Index size smaller than B+ Tree and Learned Index
- Support OLTP-style mixed worklods

Core structure:
- Dynamic tree structure, Adaptive RMI: 맨 처음에 depth와 각 가지별 모델 수가 고정되어있는게 아니라, 동적으로 합쳐지고 쪼개지거나 깊어질 수 있다.
- Models

아직 갖고있는 한계:
- In memory만 지원
- Arithmetic data types만 키로 지원
- 싱글스레드

아이디어: Gapped Array. 중간에 뭐 insert할때에 전체를 shift해버리지 않아도 되게 만들자.

Model-based index: 모델이 가리키는 인덱스가 실제 인덱스와 약간의 오차가 있을 수 있음. error range를 작게 유지해줘야한다.

Exponention Search instead of Binary Search: 에러 크기가 크면 바이너리서치가 더 빠르지만, 대부분의 경우에는 exponential search가 더 좋았다.

Adaptive Structure: B+ Tree처럼 한 노드가 꽉차면 좌우로 쪼개지기도 하고, 심지어 B+ Tree는 하지 못하지만 특정 노드의 깊이를 늘릴수도 있다. 그리고 노드를 쪼개는 대신 한 노드가 담당하는 key space의 길이를 그냥 늘리기도 한다. 머지하기도 하고 축소하기도 한다.

이런 decision들은 모두 성능을 maximize하는 방향으로 수행한다. 통계를 기반으로 자동으로 decision이 이뤄진다.

Longitudes, Longlat, Lognormal, YCSB 이 네 데이터셋으로 평가했다. 키에 따른 CDF를 측정했고, 이것이 linear할수록 성능이 좋은것. 모두 B Tree보다 좋았다.

YCSB는 아주 심플한 워크로드임에도 불구하고, B+ Tree에서 하면 depth가 5인데 여기서는 depth가 1이다. 이 논문의 큰 의의중 하나임.

Result: ALEX가 Learned Index, B+ Tree, Model B+ Tree, ART보다 좋았음

Model B+ Tree: B Tree에서 트리부분에만 모델 적용, ART: Adaptive Radix Tree

성능이 가장 잘 나오는 페이지 사이즈도 데이터기반으로 자동으로 고를 수 있었음

이런 learning based index는 worst case 개런티가 없어서 SLA 보장을 못하기때문에 기존 솔루션을 완벽하게 대체하진 못한다. worst case 개런티가 없는경우에 한해 쓰일것같다.

- 김진수 교수님 Q: 실제 워크로드가 테스트 워크로드보다 복잡하는 상황이 우려가 되는건가요?
- A: 단순할까봐 우려가 됩니다. 워크로드가 복잡할수록 러닝 기반 인덱스의 성능이 뛰어나지는데, 워크로드가 단순할수록 굳이 러닝 기반 인덱스를 안 써도 되는 상황이 오거든요
- 김진수 교수님 Q: worst case 퍼포먼스의 bound가 중요하다 하셨는데, ALEX가 어느때에 worst case를 내게되나요?
- A: 모델의 accuracy가 틀린 경우
- 김진수 교수님 Q: 원래 learned index는 worst case 개런티가 있는데 여기엔 없는 이유는?
- A: learned index는 depth 고정, 에러바운드가 고정이여서 worst case 개런티를 보장하나 여기서는 못한다.
- 다른분 Q: 못보던 스타일의 워크로드에는 잘 adapt하나?
- A: 처음에는 떨어지긴 하는데 쿼리를 계속 받으면 패턴을 배워서 잘 적응한다

프로덕트 팀의 리서치로 있으면, 연구주제에 제한은 좀 있지만 실 제품에 적용되는 연구를 하기 훨씬 쉬움, 프로덕트 팀보다 돈이 훨 많아서 사람 뽑기도 좋고. 반면 MSR에 있으면 연구주제는 보다 자유로움

- 김젼 Q: 발표 너무 잘들었습니다. ALEX 이후에, 발표자분이나 발표자분의 팀에서 다음 연구주제로 관심갖는 주제가 있다면 소개를 듣고싶습니다.
- [LSM](https://en.wikipedia.org/wiki/Log-structured_merge-tree)에 learned index를 적용할 수 있을거같다. compaction 하는 operation이 정말 비싸기때문에.. 이걸 하면 남는 CPU를 써서 IO를 최적화하는 트레이드오프가 됨. 분산디비같은데에서 데이터 어떻게 저장할지, 데이터 레이아웃에도 적용시킬 수 있을거같다. Range partitioning 말고, 다른 워크로드가 들어올때에 더 좋은 방법을 찾을 수 있을것같다.
