# -*- coding: utf-8 -*-
from time import time
t0 = time()

#
# Loading
#
print 'numpy, 데이터 로딩',

import gzip, os, cPickle
import tool
import numpy as np
from scipy.cluster.vq import kmeans, vq

path = os.path.join(os.path.realpath('..'), "data", 'mnist.pkl.gz')
with gzip.open(path, 'rb') as f:
    train_set, _, _ = cPickle.load(f)

train_count = 5000
train_x, train_y = (train_set[0][:train_count], train_set[1][:train_count])

t1 = time()
print '완료 (%f seconds)' % (t1 - t0)

#
# PCA
#
print 'PCA 수행',
dimension = 100
_, vec = np.linalg.eig(np.cov(train_x.transpose()))
vec = np.real(vec)
pca = vec.transpose()[:dimension]

train_x = pca.dot(train_x.transpose()).transpose()
train_count = dimension

t2 = time()
print '완료 (%f seconds)' % (t2 - t1)

#
# Clustering
#
print 'K-means 클러스터링',
K = min(train_count, 250)
centroids, _ = kmeans(train_x, K)
groups, _ = vq(train_x, centroids)

mu      = np.zeros((K, train_x.shape[1]))
sigma   = np.zeros((K, train_x.shape[1], train_x.shape[1]))

t3 = time()
print '완료 (%f seconds)' % (t3 - t2)

#
# Training
#
print '평균, 표준편차, Weight 행렬 계산',
for j in range(K):
    selected = train_x[groups[j]]
    mu[j] = sum(selected)/selected.shape[0]
    sigma[j] = np.cov(selected.transpose()) + 0.1 * np.eye(train_x.shape[1])

H = tool.get_H(train_x, mu, sigma)
Ht = H.transpose()
Y = tool.get_Y(train_y)
W = np.linalg.lstsq(Ht.dot(H), Ht.dot(Y))[0]

tEnd = time()
print '완료 (%f seconds)' % (tEnd - t3)


print ''
print '학습에 쓰인 총 시간: %f seconds' % (tEnd - t0)
print ''
