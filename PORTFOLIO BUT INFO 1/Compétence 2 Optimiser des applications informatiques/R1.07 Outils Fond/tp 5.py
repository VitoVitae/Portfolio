import numpy as np
import numpy.linalg as alg

"""

A=np.array([[5. , 0. , -3. ], [3. , 4. , 1.], [1., -1., -1.]])

B=np.array([[-4.],[2.], [2.]])

if alg.det(A) != 0:
    print(alg.inv(A))
    X=np.dot(alg.inv(A),B)
    print(X)


A=np.array([[1. , 1. , 0. ], [2. , -3. , 0.], [-3., 1., 4.]])

B=np.array([[2.],[-5.], [0.]])

if alg.det(A) != 0:
    print(alg.inv(A))
    X=np.dot(alg.inv(A),B)
    print(X)


A=np.array([[-2. , 5. , -1. ], [1. , -1. , 2.], [3., 0., 4.]])

B=np.array([[4.],[12.], [20.]])

if alg.det(A) != 0:
    print(alg.det(A))
    print(alg.inv(A))
    X=np.dot(alg.inv(A),B)
    print(X)
"""

A=np.array([[1. , 2. , 3. ], [4. , 5. , 6.], [7., 8., 9.]])
B=np.array([[10.],[31.], [52.]])

if alg.det(A) != 0:
    print(alg.det(A))
    print(alg.inv(A))
    X=np.dot(alg.inv(A),B)
    print(X)

A=np.array([[-2. , 9. , -1. ], [-5. , 1. , 6.], [6., -8., 6.]])
B=np.array([[11.],[-7.], [8.]])

if alg.det(A) != 0:
    print(alg.det(A))
    print(alg.inv(A))
    X=np.dot(alg.inv(A),B)
    print(X)

A=np.array([[-2. , 9. , -1. ], [-5. , 1. , 6.], [6., -8., 6.]])
B=np.array([9. ,19., 2.])

if alg.det(A) != 0:
    print(alg.det(A))
    print(alg.inv(A))
    X=np.dot(B,alg.inv(A))
    print(X)