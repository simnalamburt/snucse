Deep Learning from Scratch
========
> 남들 다 할줄아는 딥러닝을 나도 하기위해, 만학의 꿈에 도전하는 김젼

```bash
# Install dependencies
pipenv install

# Execute jupyter notebook
pipenv run jupyter -- notebook --no-browser \
  --ip=$(dig +short myip.opendns.com @resolver1.opendns.com)
```

![책 표지](https://raw.githubusercontent.com/oreilly-japan/deep-learning-from-scratch/images/deep-learning-from-scratch.png)

- 예시 코드 : https://github.com/WegraLee/deep-learning-from-scratch

### Peers
- @simnalamburt
- [@pinkrespect](https://github.com/pinkrespect/DeepLearningFromScratch)
- [@JungWinter](https://github.com/JungWinter/Code_Study/tree/master/Book/DeepLearningFromScratch)
- [@malkoG](https://github.com/malkoG/academic/tree/master/data-science/deep-learning-from-scratch)
- [@initNirvana](https://github.com/initNirvana/LifeCoding/tree/master/DeeplearningScratch)
- [@Cura-inthelab](https://github.com/Cura-inthelab/deep-learning)
- [@nellaG](https://github.com/nellaG/dlfs)
- [@VanilaJelly](https://github.com/VanilaJelly/ddl)

### 해볼만한 발표주제
- (챕터 1 관련) numpy가 빠른이유
- (챕터 1 관련) http://www.labri.fr/perso/nrougier/from-python-to-numpy/#memory-layout
- (챕터 2 관련) imshow로 퍼셉트론 시각화하기
- (챕터 2 관련) 다층 퍼셉트론만으로 함수 만들어보자
- (챕터 3 관련) 텐서를 쓰는 이유
- (챕터 3 관련) `@` 연산자 오버로딩
- (챕터 4 관련) 에러함수 해석적으로 미분 안하는 이유
- (챕터 4 관련) Cross Entropy Error를 쓰는 이유
- (챕터 2, 4 관련) 퍼셉트론, 미분, 편미분, 그래디언트를 함수로 표현해보자
- (챕터 4 관련) 오탈자
- (챕터 4 관련) https://docs.scipy.org/doc/numpy/reference/generated/numpy.einsum.html
- (챕터 5 관련) k-fold cross-validation
- (챕터 5 관련) http://playground.tensorflow.org
- [Vanishing gradient problem](https://en.wikipedia.org/wiki/Vanishing_gradient_problem)
- [Dying Relu problem], [LReLUs]
- 시그모이드 다음에 CEE 바로쓰면 그래디언트 계산 안좋게됨
- [sigmoid_cross_entropy_with_logits](https://www.tensorflow.org/api_docs/python/tf/nn/sigmoid_cross_entropy_with_logits)
- d_step g_step 비율을 1:1이 아닌걸로 해야 잘된대
- 내가 만든 뉴럴넷 웹서비스로 올리자
- 소프트맥스-CEE 미분

[Dying Relu problem]: https://en.wikipedia.org/wiki/Rectifier_(neural_networks)#Potential_problems
[LReLUs]: https://en.wikipedia.org/wiki/Rectifier_(neural_networks)#Leaky_ReLUs
