"""
## Questions préliminaires

### 1.

A = (2,4) et B = (5,3)

A' = A * T

T = 
[cos(pi/3)   -sin(pi/3)]
[sin(pi/3)   cos(pi/3)]

alors T =

[   1/2      -sqrt(3)/2]
[sqrt(3)/2      1/2    ]

donc A' = ( 1-[ (4*sqrt(3))/2 ], sqrt(3)+2 )

### 2.

B = (5,3)
alors B' = (5+5,3+3) = (10,6) 

"""
import numpy as np
import numpy.linalg as alg
import random as r
# Dragon de Heighway

# 1.

def transformation1(p):
    f1 = np.array([[0.5,-0.5],[0.5,-0.5]])
    res = np.dot(f1,p)
    return res

# 2.

def transformation2(p):
    f2 = np.array([[-0.5,-0.5],[0.5,-0.5]])
    u = np.array([[1],[0]])
    res = np.dot(f2,p)
    res = res + u
    return res

# 3.

O=np.array([[0], [0]])
for i in range(1):
    R = r.randint(0,1)
    if R==0:
        O=transformation1(O)
    else:
        O=transformation2(O)

    print(O)

# Foug`ere de Barnsley
    
def transformation1(p):
    f = np.array([[-0.5,-0.5],[0.5,-0.5]])
    u = np.array([[0],[0]])
    res = np.dot(f,p)
    res = res + u
    return res

def transformation2(p):
    f = np.array([[0.85,0.04],[-0.04,0.85]])
    u = np.array([[0],[1.6]])
    res = np.dot(f,p)
    res = res + u
    return res

def transformation3(p):
    f = np.array([[0.2,-0.26],[0.23,0.22]])
    u = np.array([[0],[1.6]])
    res = np.dot(f,p)
    res = res + u
    return res

def transformation4(p):
    f = np.array([[-0.15,0.28],[0.26,0.24]])
    u = np.array([[0],[0.44]])
    res = np.dot(f,p)
    res = res + u
    return res

O=np.array([[0], [0]])
for i in range(10):
    R = r.random()
    if (0 <= R <=0.01 ):
        O=transformation1(O)
    elif (0.01 < R <=0.85):
        O=transformation2(O)
    elif (0.85< R <=0.92):
        O=transformation3(O)
    elif (0.92< R <=1):
        O=transformation4(O)