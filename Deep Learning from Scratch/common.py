import numpy as np

def sigmoid(x):
    return 1/(1 + np.exp(-x))

def gradient_sigmoid(x):
    return (1.0 - sigmoid(x)) * sigmoid(x)

def softmax(A):
    extend = (lambda x:x) if A.ndim == 1 else (lambda x: x[..., np.newaxis])
    ExpA = np.exp(A - extend(A.max(axis=-1)))
    return ExpA / extend(ExpA.sum(axis=-1))

def cross_entropy_error(expected, actual):
    epsilon = 1E-7
    return -(actual * np.log(expected + epsilon)).sum(axis=-1)

def cross_entropy_error_batch(*args):
    return cross_entropy_error(*args).mean()
