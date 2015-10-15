import gzip, os, cPickle
import numpy as np
import learn
import tool

path = os.path.join(os.path.realpath('..'), "data", 'mnist.pkl.gz')
with gzip.open(path, 'rb') as f:
    _, _, test_set = cPickle.load(f)

#
# Test
#
test_count = 2000
test_x, test_y = (test_set[0][:test_count], test_set[1][:test_count])

H = tool.get_H(test_x, learn.mu, learn.sigma)
Y = tool.get_Y(test_y)
f = H.dot(learn.W)
max_val = f.max(1)
max_idx = f.argmax(1)


# row: test_label
# col: estimate of the classifier
confusion_matrix = np.zeros((10,10))
for i in range(test_y.shape[0]):
    confusion_matrix[test_y[i], max_idx[i]] += 1

accuracy = np.diag(confusion_matrix).sum() / test_y.shape[0]
print accuracy
