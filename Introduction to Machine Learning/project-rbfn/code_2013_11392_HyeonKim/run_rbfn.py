# coding: utf-8
import learn
import gzip, os, cPickle
import numpy as np
import tool
from time import time
from config import *

t0 = time()

#
# Loading
#
print '테스트 데이터 로딩 및 PCA 적용',

path = os.path.join(os.path.realpath('..'), "data", 'mnist.pkl.gz')
with gzip.open(path, 'rb') as f:
    _, _, test_set = cPickle.load(f)

test_x, test_y = (test_set[0][:test_count], test_set[1][:test_count])

# PCA
test_x = learn.pca.dot(test_x.transpose()).transpose()
test_count = learn.dimension

t1 = time()
print '완료 (%f seconds)' % (t1 - t0)

#
# Test
#
print '퍼포먼스',

H = tool.get_H(test_x, learn.mu, learn.sigma)
Y = tool.get_Y(test_y)
f = H.dot(learn.W)
max_val = f.max(1)
max_idx = f.argmax(1)

t2 = time()
print '완료 (%f seconds)' % (t2 - t1)

#
# Grade
#
print '채점',

confusion_matrix = np.zeros((10,10))
for i in range(test_y.shape[0]):
    confusion_matrix[test_y[i], max_idx[i]] += 1

accuracy = np.diag(confusion_matrix).sum() / test_y.shape[0]

t3 = time()
print '완료 (%f seconds)' % (t3 - t2)


print ''
print '퍼포먼스에 쓰인 총 시간: %f seconds' % (t3 - t0)
print '정확도: %f%%' % (accuracy * 100.0)
print ''
