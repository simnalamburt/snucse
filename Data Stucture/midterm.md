중간고사 시험공부
--------

> 스택, 큐, 소팅, 트리에서 큰문제는 거의 다 나온다

### 2014년 봄 중간고사
알고리즘의 시간/공간복잡도에는 Best case, Average case, Worst case가 각각 모두
있음. O(n)은 상한을 기술하는 표기법이므로, 누군가 나에게 아무런 제한조건 없이
asymptotic running time을 물어보면 최악의 경우를 대답하는게 맞음.

#### 1.
1. X - 퀵소트는 최악의 경우 O(n^2)이다.
2. O - 머지소트는 최선 최악 평균 세 모든 경우에도 O(nlogn)
3. O - k를 고정하면, radix sort는 O(n)에 포함되므로, O(nlogn)에도 포함된다고 볼
       수 있다.
4. X - MSD 래딕스 소트랑 LSD 래딕스 소트랑 서로 용도가 다름.

#### 2.
순서가 반대로 변한다.

#### 3.
```
int partition(A[], first, last) {
  pivot = A[first];
  lastS1 = first;

  for (i = first + 1; i <= last; ++i) {
    if (A[i] < pivot) {
      ++lastS1;
      swap(A[i], A[lastS1]);
    }
  }
  swap(A[first], A[lastS1]);
  return lastS1;
  }
```

위 코드를

```
int partition(A[], first, last) {
  pivot = A[last];
  lastS1 = last;

  for (i = last - 1; i >= first; --i) {
    if (A[i] < pivot) {
      --lastS1;
      swap(A[i], A[lastS1]);
    }
  }
  swap(A[last], A[lastS1]);
  return lastS1;
}
```

#### 4.
```java
public void insertFront(Object newItem) {
    if (!isFull()) {
        // 음수에 % 씌우지 않도록 주의!!
        front = (front - 1 + MAX_QUEUE) % MAX_QUEUE;
        items[front] = newItem;
        ++numItems;
    } else { exception 처리; }
}

public Object removeBack() {
    if (!isEmpty()) {
        Object ret = items[back];
        back = (back - 1 + MQX_QUEUE) % MAX_QUEUE;
        --numItems;
        return ret;
    } else { exception 처리; }
}
```

이와같이 바꾸면 된다.

#### 5.
```java
TreeNode deleteNode (TreeNode tNode) {
    if ( (tNode.getLeft() == null) && (tNode.getRight() == null) ) {
        return null;
    } else if (tNode.getLeft() == null) {
        return tNode.getRight();
    } else if (tNode.getRight() == null) {
        return tNode.getLeft();
    } else {
        tNode.setItem(maximum item of tNode's left subtree);
        tNode.setLeft(deleteMax(tNode.getLeft());
        return tNode;
    }

}

TreeNode deleteMax (TreeNode tNode) {
    if (tNode.getRight() == null) {
        return tNode.getLeft();
    } else {
        tNode.setRight(deleteMax(tNode.getRight());
        return tNode;
    }
}
```

#### 6.
1.  아래와 같다

    ```
    move(n, A, B, C)
    {
        match n {
            1 | 2 | 3 => { A에서 B로 디스크들을 옮긴다 }
            _ => {
                move(n-3, A, C, B)
                move(3, A, B, C)
                move(n-3, C, B, A)
            }
        }
    }
    ```

2.  2**ceil(n/3) - 1

#### TODO
- 알고리즘 익히기
- 알고리즘별 시간/공간복잡도 Best/Average/Worst 익히기 http://bigocheatsheet.com/
- Stable, Unstable sort 개념 익히기
