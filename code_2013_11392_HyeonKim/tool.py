# coding: utf-8
import numpy as np
from scipy.stats import multivariate_normal as mvn

def get_H(X, mu, sigma):
    hidden = np.zeros((X.shape[0], 10))
    for j in range(10):
        hidden[:,j] = mvn.pdf(X, mu[j], sigma[j])
    return hidden

def get_Y(y):
    return np.eye(y.shape[0])[y][:,:10]
