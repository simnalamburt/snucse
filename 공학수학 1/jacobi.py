import numpy as np

#     |u11|
# U = |u21|
#     |u12|
#     |u22|
#
# U = AU + B

A = np.array([
    [0.00, 0.25, 0.25, 0.00],
    [0.25, 0.00, 0.00, 0.25],
    [0.25, 0.00, 0.00, 0.25],
    [0.00, 0.25, 0.25, 0.00],
])

B = np.array([
    50.,
    50.,
    25.,
    25.,
])

# Initial values
U = np.array([0., 0., 0., 0.])
print(f'U = {U}')

for _ in range(20):
    V = A@U + B
    U = A@V + B
    print(f'U = {U}')
