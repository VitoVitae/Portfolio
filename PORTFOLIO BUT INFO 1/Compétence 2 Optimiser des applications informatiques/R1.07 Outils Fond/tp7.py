"""
Question 1 : 
"""
import numpy as np
import numpy.linalg as alg

def mineur(A, i, j):
    B = A[:, 0:j-1] 
    C = A[:, j:]
    res=np.concatenate((B,C),axis=1) #coupe la matrice en deux sur l'axe y
    B = res[0:i-1,:]
    C = res[i:, :]
    res=np.concatenate((B,C),axis=0) #coupe la matrice en deux sur l'axe x

    return res
A=np.array([[-1.,1.,3.], [2.,3.,2.], [0.,4.,2.], [2.,1.,2.]])
print(mineur(A,1,3))

"""
Question 2 :
"""
def multiplicationreel(M,i,k):
    taille=np.shape(M)
    for j in range(taille[1]):
        M[i][j]=M[i][j]*k
    return M

def elimination(M,i,j,k):
    taille=np.shape(M)
    for c in range(taille[1]):
        M[j][c]=M[j][c]-(M[i][c]*k)
    return M

def det2(M):
    det = M[0][0]*M[1][1]-M[0][1]*M[1][0]
    return det

def det(M):
    S=M.shape
    deter=0
    if (S[0]!=2):
        A=M
        for i in range(1, S[0]):
            M=elimination(M,0,i,M[i][0]/M[0][0])
        D=M[0][0]
        M=mineur(M,1,1)
        deter=D*det(M)
    else:
        deter=det2(M)

    return deter


A=np.array([[1.,1.,1.], [1.,-1.,2.], [-1.,2.,1.]])
print(det(A))
"""
Question 3 :
"""
def colonne(A):
    S=A.shape
    for i in range(1, S[0]):
        A=elimination(A,0,i,A[i][0]/A[0][0])
    return A

A=np.array([[1.,2.,2.], [1.,3.,-2.], [3.,5.,8.]])
print(colonne(A))

"""
Question 2 :
"""

def determinant(M):
    S=M.shape
    deter=0
    if (S[0]!=2):
        colonne(M)
        return M[0][0]*determinant(mineur(M,1,1))
    else:
        deter=det2(M)

    return deter

A=np.array([[1.,1.,1.], [1.,-1.,2.], [-1.,2.,1.]])
print(determinant(A))