import numpy as np
import numpy.linalg as alg
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

def GaussJordan(M):
    B=np.eye(3)
    if alg.det(M) != 0:
        M = np.concatenate((M,B), axis=1)

        M = elimination(M,0,1,M[1][0]/M[0][0])
        M = elimination(M,0,2,M[2][0]/M[0][0])
        M = elimination(M,1,2,M[2][1]/M[1][1])

        M = multiplicationreel(M,0,1/M[0][0])
        M = multiplicationreel(M,1,1/M[1][1])
        M = multiplicationreel(M,2,1/M[2][2])

        M = elimination(M,2,1,M[1][2])
        M = elimination(M,2,0,M[0][2])
        M = elimination(M,1,0,M[0][1])

    return M[:,3:6]

A=np.array([[1.,-1.,-4.], [2.,-3.,4.], [0.,2.,8.]])
print(GaussJordan(A))

A=np.array([[-1.,2.,4.], [1.,0.,-2.], [-2.,2.,5.]])
print(GaussJordan(A))