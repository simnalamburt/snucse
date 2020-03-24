Week 1, Tue
========

옵셔널 텍스트북:

- Deep learning, Ian Goodfellow and Yoshua Bengio and Aaron Courville, MIT Press-2016, free online
- Introduction to Probability by Bertsekas and Tsitsiklis

선형대수, Multivariate calculus, 확률, 통계, Numpy 혹은 다른 행렬계산이 가능한 프로그래밍 언어

숙제는 반드시 LaTeX으로 만든 PDF여야한다. 딜레이된 숙제는 받지 않는다.

TF/Caffe/Theano/Torch 사용법을 배우는게 아니라, 딥러닝에 깔려있는 기초 알고리즘, 수학, 이론들에 대해 배울것이다.

ML은 멀까? 데이터 x로부터 배우는 알고리즘 f(x) 에 대한 연구이다. Vision, NLP, 음성인식, 로보틱스 등은 Application임.

ML의 브랜치로는 뭐가 있을까? DL, RL, 지도학습, 비지도학습, Representation learning 등이 있을것이다. 이 수업에선 ML과 저 브랜치들에 대해 배울 수 있을것이다.

#### Supervised Learning
1.  Binary/Multiclass classification

    x가 주어지면, {1, ..., K} 중 하나인 y 찾기

    ex: 사진 -> {고양이, 개, 새, ...} 중 하나

2.  Regression (회귀분석)

    x가 주어지면 R^d 공간 안에있는 y 찾기

3.  Sequence annotation

    x1, x2, ... xn 으로부터 y1, y2, ... yn 찾기

    ex: "I am a student" -> "나는 학생입니다."

4.  Prediction

    xt와 y1, ... yt-1 로부터 yt 찾기

#### Unsupervised Learning
1.  Clustering

    Find a set of prototypes representing the data. 클러스터링에서 프로토타입은 클러스터의 중심을 뜻함

    ex: normalized cuts(=image segmentation)

2.  Sequence Analysis

    Find a latent casual sequence for observations (HMM, Kalman Filter, etc)

    ex: 시간에 따라 노이지한 데이터가 들어오는 상황에서 그걸로 미래의 데이터 예측하기

3.  [Independent components analysis]/dictionary learning

    Find a set of factors for observation. 여러 신호가 섞여있을때에, 통계적으로 독립적인 여러 하부 성분으로 분리해줌.

    예를들어 라이브 공연 소리에서 관객의 소리와 노래소리를 분리하는것이 Independent components analysis임.

    [Independent components analysis]: https://en.wikipedia.org/wiki/Independent_component_analysis

4.  Novelty detection

    비정상 탐지

    ex: 신용카드 이상거래 탐지

[Principal component analysis](https://en.wikipedia.org/wiki/Principal_component_analysis)도 비지도학습의 예시임. 데이터를 플롯한다음 이 데이터가 몇개의 Principal Component로 표현될 수 있는지 계산해서, 고차원의 데이터를 저차원의 데이터로 바꾸는 작업

#### Interaction with Environments
1.  Online Learning

    Observe xt, predict f(xt), observe yt

    모든 셋의 데이터를 한번에 다 갖고 학습하는게 아니라, 한번에 하나의 데이터만 보면서 학습함

2.  Active Learning

    Query yt for xt, improve model, pick new x

    사람이 주는 데이터만 가지고 학습하는게 아니라, 어떤 데이터로 학습할지 모델이 액티브하게 사람에게 질문을 함. 질문을 아주 많이 하면 감독학습이랑 차이가 없어짐. 그래서 보통 쿼리할 수 있는 횟수에 제한을 둬서, 불확실한 입력들 위주로 질문하게끔 만듦.

3.  Bandits problem

    Pick arm of slot machine, get reward, pick new arm

    "K대의 서로 다른 슬롯머신이 있을때에, 어느 슬롯머신이 가장 많은 리워드를 줄까?"가 이런것에 해당함. One-state Reinforcement learning 혹은 Stateless RL라고도 생각할 수 있음

4.  Reinforcement Learning

    Take action, environment responds, take new action. 내가 하는 행동이 환경에 영향을 주는 상황에서, 최고의 액션이 뭔지 찾기

    ex: 알파고, 게임 인공지능, Robot locomotion(어떻게 관절을 움직여야 앞으로 갈 수 있을까)

    알파고도 그렇고 게임 인공지능도 그렇고, State 공간의 [Cardinality](크기)와 Action공간의 크기가 크다.

    [Cardinality]: https://en.wikipedia.org/wiki/Cardinality

#### Discriminative vs Generative

(TODO)

Q: casual sequence가 뭔소리임
Q: dictionary learning이 뭐임
