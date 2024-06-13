#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import numpy as np
import numpy.linalg as alg

#####################################################
##########  Somme et produit par un scalaire ########


#############  Exemple 1 ###########################

#1. A+B=[[5,6,-1][0,3,7]]
#2. 2A=[[10,-2,0],[-4,4,6]]
#3. 3B=[[0,21,-3],[6,3,12]]
#4. 2A -3B =[[10,-23,3],[-10,1,-6]]

#############  Exercice 1 ###########################
"""
A=np.array([[5,-1,0],[-2,2,3]])
B=np.array([[0,7,-1],[2,1,4]])

op1=A+B
print(op1)
op2=2*A
print(op2)
op3=3*B
print(op3)
op4=op2-op3
print(op4)
print()
"""
#############  Exemple 2 ########################### 

#2. [[4, 2, 1]]x[[8],[3],[-2]]= 36

#############  Exercice 2 ###########################

def prodduitscalaire(A,B):
	""" Calcule le produit scalaire du vecteur ligne A par le vecteur colonne B """
	Taille=A.shape
	somme=0

	for i in range(Taille[0]):
			somme=somme+A[i]*B[i][0]
	return somme

M1=np.array([4,2,1])
M2=np.array([[8],[3],[-2]])
print(prodduitscalaire(M1,M2))
print()
M1=np.array([1,-3,2])
M2=np.array([[0],[4],[3]])
print(prodduitscalaire(M1,M2))
print()
#############  Exercice 3 ###########################
"""
[19,13]
[-2,13]
[-17,19]
"""

#############  Exercice 4 ###########################

def produitmatrice(A,B):
	""" Calcule le produit AB des matrices A et B s'il existe """
	TailleA=A.shape
	TailleB=B.shape
	
	#assert(TailleA[0]==TailleB[1])
	#assert(TailleA[1]==TailleB[0])
	
	Nouv=np.zeros((TailleA[0],TailleB[1]))
	somme=0

	for i in range(TailleA[0]):
		for j in range(TailleB[1]):
			for x in range(TailleA[1]):
				somme=somme+A[i][x]*B[x][j]
			Nouv[i][j]=somme
			somme=0
	return Nouv

M4=np.array([[2,3,-1],[1,-5,0]])
M5=np.array([[1,0],[4,-1],[-2,-3]])
print(produitmatrice(M4,M5))
print()


#############  Exercice 5 ###########################
A=np.array([[2, -1, -1,-2],[4, 4, 2, 0],[0, 4, 2, 0],[-1, -1, 0, -3]])
B=np.array([[-2, 2, 1,3],[1, -3, 0, -2],[2, -1, -2, 3],[-4, 3, 3, 3]])
C=np.array([[0, -4, 3,1],[4, 2, -4, 1],[1, -1, 3, 3],[4, 1, 4, -4]])
D=np.array([[-8, -6, 26,0],[4, -8, 0, -11],[10, -5, 26, -6],[-12, -23, 0, 38]])

#1) (A+B)^2=
print("(A+B)^2=\n",produitmatrice(A+B,A+B))
print()
#2) A^2 +2AB+B^2 =
print(" A^2 +2AB+B^2 =\n",produitmatrice(A,A)+2*produitmatrice(A,B)+produitmatrice(B,B))
print()
#3) Le produit matriciel ne marche pas avec l'identité remarquable

#4)  (C+D)^2=
print("(C+D)^2=\n",produitmatrice(C+D,C+D))
print()
#   C^2 + 2CD +D^2 = 
print("C^2 + 2CD +D^2\n",produitmatrice(C,C)+2*produitmatrice(C,D)+produitmatrice(D,D))
print()
# l'identité remarquable marche

#############  Exercice 6 ###########################

A=np.array([[4,5,6]])
B=np.array([[2],[3],[-1]])
print(produitmatrice(A,B))
print()

C=np.array([[2],[3],[-1]])
D=np.array([[4,5,6]])
print(produitmatrice(C,D))
print()

E=np.array([[1,2,3]])
F=np.array([[4,-6,9,6],[0,-7,10,7],[5,8,-11,-8]])
print(produitmatrice(E,F))
print()

G=np.array([[2,3,4],[1,5,6]])
H=np.array([[1],[2],[3]])
print(produitmatrice(G,H))
print()

I=np.array([[1,2,1],[4,0,2]])
J=np.array([[3,-4],[1,5],[-2,2]])
print(produitmatrice(I,J))
print()

#############  Exercice 7 ###########################

"""
???

1. (2A-In)(A + 3In) = 3A*A+ 2A*3In -A -3In

2. (A-4In)(2A+3In) = A*2A+ A*3In -4In*A -8In

3. (In-A)(In+A+A²) = In + A + A² - A - A² - A**3
				   = In - A**3

4. s(A+2In)² = A² + 2In*A + 2In*A + 4In  

5.

6.

7.

8.

9.


"""