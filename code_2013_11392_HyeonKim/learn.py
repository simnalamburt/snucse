import gzip, os, time, cPickle
import numpy as np
import tool
from scipy.cluster.vq import kmeans, vq

start_time = time.time()

path = os.path.join(os.path.realpath('..'), "data", 'mnist.pkl.gz')
with gzip.open(path, 'rb') as f:
    train_set, _, _ = cPickle.load(f)

train_count = 1000
K = min(train_count, 100)

train_x, train_y = (train_set[0][:train_count], train_set[1][:train_count])

centroids, _ = kmeans(train_x, K)
groups, _ = vq(train_x, centroids)

mu      = np.zeros((K, train_x.shape[1]))
sigma   = np.zeros((K, train_x.shape[1], train_x.shape[1]))


#
# Training
#
for j in range(K):
    selected = train_x[groups[j]]
    mu[j] = sum(selected)/selected.shape[0]
    sigma[j] = np.cov(selected.transpose()) + 0.1 * np.eye(train_x.shape[1])


H = tool.get_H(train_x, mu, sigma)
Ht = H.transpose()
Y = tool.get_Y(train_y)
W = np.linalg.lstsq(Ht.dot(H), Ht.dot(Y))[0]

elapsed_time = time.time() - start_time
print 'Elapsed Time for Training: ', elapsed_time
