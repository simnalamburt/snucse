import numpy as np

# Numpy basics
x = np.array([1, 2, 3])
y = np.array([2, 4, 6])
z = np.array([0.1, 0.2, 0.3, 0.4])

print(type(x))
print(x.dtype)
print(x)
print()

# Element-wise arithmetic
print(x + y)
print(x * y)
print(x / y)
try:
    print(x + z)
except ValueError as e:
    print(e)
print()

# Scalar arithmetic
print(2 * x)
print(y * 2)
print(x / 2)
print(x + 2)
print(x % 2 == 0)
print()

# Multi-dimensional
A = np.array([
    [1, 2],
    [3, 4],
])
B = np.array([
    [5, 6],
    [7, 8],
])
print(A)
print(A * B)
print(A.shape)
print(A.dtype)
print()

# Broadcast
A = np.array([
    [1, 2],
    [3, 4],
])
B = np.array([10, 100])
print(A*B)
print()

# Access
A = np.array([
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 9],
    [10, 11, 12],
])
B = A.flatten()
print(A)
print(B)
print(A[0])
print(A[0][0])
print(A[0, 0])
print('-'.join([str(row) for row in A]))
print(B[[0, 2, 4]])
print(B[np.array([0, 2, 4])])
print()

# Trick
a = np.array([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19])
print(a)
print(a > 10)
print(a[a > 10])
print(a[2:10])
print(a[2:10:2])
print(a[10:2:-1])
print(a[10:])
print(a[10::-1])
print(a[:10])
print(a[:10:-1])
print()

# Column
A = np.array([
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 9],
    [10, 11, 12],
])
print(A)
print(A.transpose())
print(A[0])
print(A[...,0])
print(A[...,1])
print(A[...,2])
