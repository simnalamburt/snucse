import gzip, os, cPickle
import numpy as np
import tool

path = os.path.join(os.path.realpath('..'), "data", 'mnist.pkl.gz')
with gzip.open(path, 'rb') as f:
    train_set, _, _ = cPickle.load(f)

train_count = 10000
train_x, train_y = (train_set[0][:train_count], train_set[1][:train_count])

mu          = np.zeros((10, train_x.shape[1]))
sigma       = np.zeros((10, train_x.shape[1], train_x.shape[1]))


#
# Training
#
for j in range(10):
    selected = train_x[train_y==j]
    mu[j] = sum(selected)/selected.shape[0]
    sigma[j] = np.cov(selected.transpose()) + 0.1 * np.eye(train_x.shape[1])


H = tool.get_H(train_x, mu, sigma)
Ht = H.transpose()
Y = tool.get_Y(train_y)
W = np.linalg.inv(Ht.dot(H)).dot(Ht).dot(Y) # <- opt
