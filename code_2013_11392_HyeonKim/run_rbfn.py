#!/usr/bin/env python2
import gzip, os, cPickle
import numpy as np
from scipy.stats import multivariate_normal as mvn

path = os.path.join(os.path.realpath('..'), "data", 'mnist.pkl.gz')
with gzip.open(path, 'rb') as f:
    train_set, valid_set, test_set = cPickle.load(f)

train_count = 1000
test_count = 100

train_x, train_y = (train_set[0][:train_count], train_set[1][:train_count])
test_x, test_y = (test_set[0][:test_count], test_set[1][:test_count])

p_class     = np.zeros(10)
train_subx  = [None] * 10
mu          = [None] * 10
sigma       = [None] * 10

#
# Training
#
for j in range(10):
    train_subx[j] = train_x[train_y==j];
    mu[j] = sum(train_subx[j])/train_subx[j].shape[0]
    sigma[j] = np.cov(train_subx[j].transpose()) + 0.1 * np.eye(train_x.shape[1])
    p_class[j] = 1.0 * train_subx[j].shape[0] / train_x[j].shape[0]

# row: test_label
# col: estimate of the classifier
confusion_matrix = np.zeros((10,10));

p_likelihood = np.zeros((10, test_x.shape[0]));

for j in range(10):
    p_likelihood[j] = p_class[j] * mvn.pdf(test_x, mu[j], sigma[j]);

max_val = p_likelihood.max(0)
max_idx = p_likelihood.argmax(0)

#
# Test
#
for i in range(test_y.shape[0]):
    confusion_matrix[test_y[i], max_idx[i]] += 1

accuracy = np.diag(confusion_matrix).sum() / test_y.shape[0]
print accuracy
