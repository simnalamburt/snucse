#!/usr/bin/env python2
import gzip, os, cPickle
import numpy as np
from scipy.stats import multivariate_normal as mvn

path = os.path.join(os.path.realpath('..'), "data", 'mnist.pkl.gz')
with gzip.open(path, 'rb') as f:
    train_set, valid_set, test_set = cPickle.load(f)

train_count = 10000
test_count = 200

train_x, train_y = (train_set[0][:train_count], train_set[1][:train_count])

probability = np.zeros(10)
mu          = np.zeros((10, train_x.shape[1]))
sigma       = np.zeros((10, train_x.shape[1], train_x.shape[1]))

#
# Training
#
for j in range(10):
    selected = train_x[train_y==j]
    probability[j] = 1.0 * selected.shape[0] / train_x[j].shape[0]
    mu[j] = sum(selected)/selected.shape[0]
    sigma[j] = np.cov(selected.transpose()) + 0.1 * np.eye(train_x.shape[1])

def get_hidden(X):
    hidden = np.zeros((X.shape[0], 10))
    for j in range(10):
        hidden[:,j] = mvn.pdf(X, mu[j], sigma[j])
    return hidden

def get_Y(y):
    return np.eye(y.shape[0])[y][:,:10]

hidden = get_hidden(train_x)
hidden_t = hidden.transpose()
Y = get_Y(train_y)
W = np.linalg.inv(hidden_t.dot(hidden)).dot(hidden_t).dot(Y) # <- opt


#
# Test
#
test_x, test_y = (test_set[0][:test_count], test_set[1][:test_count])

hidden = get_hidden(test_x)
Y = get_Y(test_y)
f = Y.dot(W)
max_val = f.max(1)
max_idx = f.argmax(1)


# row: test_label
# col: estimate of the classifier
confusion_matrix = np.zeros((10,10))
for i in range(test_y.shape[0]):
    confusion_matrix[test_y[i], max_idx[i]] += 1

accuracy = np.diag(confusion_matrix).sum() / test_y.shape[0]
print accuracy
