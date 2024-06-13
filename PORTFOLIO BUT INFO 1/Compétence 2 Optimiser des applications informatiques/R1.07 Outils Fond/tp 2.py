#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import numpy as np
import numpy.linalg as alg

#############  Exercice 1 ###########################

def absolue(x) :
	""" Calcule la valeur abslue de x """
	if x < 0:
		x=x*-1
		return x
	else:
		return x
	
print(absolue(-9))
print(absolue(9))
print()

def fact(n) :
	""" Calcule le produit n(n-1)(n-2)...2x1 """
	if n == 0:
		return 1
	else:
		return n*fact(n-1)
	
print(fact(4))
print(fact(0))
print()

def puissance(x,n) :
	""" Calcule x^n """
	puiss=1
	for i in range(1,n+1):
		puiss=puiss*x
	return puiss

print(puissance(2,3))
print(puissance(2,0))
print()



############ Exercice 2 #############################

def transpose(A) :
	""" retourne la transposée de la matrice A """
	E=A.shape
	Nouv=np.zeros((E[1],E[0]))

	for i in range(E[0]):
		for j in range(E[1]):
			Nouv[j][i]=A[i][j]
	
	return Nouv

M1= np.array([[1,2,3],[4,5,6]])
print(M1)
print(transpose(M1))
print()
	
def diagonale(A) :
	""" retourne une matrice de même dimension que A avec seulement les termes de la diagonale de A """
	E=A.shape

	Nouv=np.zeros((E[0],E[1]))

	for i in range(E[0]):
		for j in range(E[1]):
			if i==j:
				Nouv[i][j]=A[i][j]
	return Nouv

M2= np.array([[1,2,3],[4,5,6],[7,8,9]])
print(M2)
print(diagonale(M2))
print()

def trace(A) :
	""" Calcule la Trace de la matrice A """
	E=A.shape
	assert(E[0]==E[1])
	sum=0
	for i in range(E[0]):
		for j in range(E[1]):
			if i==j:
				sum=sum+A[i][j]
	return sum

M3= np.array([[1,2,3],[4,5,6],[7,8,9]])
print(M3)
print(trace(M3))
print()

def valeurmax(A) :
	""" Retourne la valeur max de A et la position du coefficient """
	E=A.shape

	max=A[0][0]
	imax=0
	jmax=0

	for i in range(E[0]):
		for j in range(E[1]):
				if A[i][j]>max:
					max=A[i][j]
					imax=i
					jmax=j
	return max, (imax,jmax)

M4= np.array([[1,80,3],[100,70,6],[7,8,9]])
print(M4)
print(valeurmax(M4))
print()#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# Par KERVADEC Mattéo 
# Fait le 9 octobre 2023

import numpy as np
import numpy.linalg as alg

#############  Exercice 1 ###########################

def absolue(x) :
	""" Calcule la valeur abslue de x """
	"""
	paramètre :

	x : int
	un entier qui peut être positif ou négatif

	return :
	x : int
	la valeur absolue de x
	"""
	if x < 0 :
		return -1 * x
	return x

# print("|-12| = ",absolue(-12))
# print("|12| = ",absolue(12))

assert absolue(-12) == 12
assert absolue(12) == 12

def fact(n) :
	""" Calcule le produit n(n-1)(n-2)...2x1 """
	"""
	paramètre :
	n : int
	
	retourne :
	le factoriel de n

	calcul le factoriel de n
	"""
	if n == 0 :
		return 1
	else :
		return n*fact(n-1)
	
# print("factoriel de 5 = ",fact(5))
# print("factoriel de 4 = ",fact(4))

assert fact(5) == 120
assert fact(4) == 24

def puissance(x,n) :
	""" Calcule x^n """
	"""
	paramètre :
	x : float
	un nombre réel quelquonque

	n : int
	la puissance de x

	retourne :
	retourne le résultat de x^n

	Calcul la puissance de x suivant n
	avec une boucle while et un compteur qui incrémente
	"""
	compteur = 0
	resultat = 1
	while compteur < n :
		resultat = resultat * x
		compteur += 1
	return resultat

# print("5^3 = ",puissance(5,3))
# print("2^2 = ",puissance(2,2))

assert puissance(5,3) == 5**3
assert puissance(2,2) == 2**2
############ Exercice 2 #############################

def transpose(A) :
	""" retourne la transposée de la matrice A """
	"""
	paramètre :
	A : Matrcice
	une matrice

	retourne :
	la matrice transposé

	Rentre une matrice de taille x,y et retourne sa matrice transposé
	"""
	liste = []
	for i in range(len(A[0])) :
		L = []
		for j in range (len(A)) : 
			L.append(A[j][i])
		liste.append(L)
	return np.array(liste)

# print("[[1,2,3],[4,5,6]] = ",transpose(np.array([[1,2,3],[4,5,6]])))

def diagonale(A) :
	""" retourne une matrice de même dimension que A avec seulement les termes de la diagonale de A """
	"""
	paramètre :
	A : Matrcice
	une matrice

	retourne :
	la matrice diagonale

	Rentre une matrice de taille x,y et retourne sa matrice diagonale
	"""
	liste = []
	lig = len(A[0])
	col = len(A)
	for i in range(col) :
		L = []
		for j in range(lig) :
			if i == j :
				L.append(A[i][j])
			else :
				L.append(0)
		liste.append(L)
	return np.array(liste)
	
# print(diagonale(np.array([[1,2,3],[4,5,6],[7,8,9]])))

def trace(A) :
	""" Calcule la Trace de la matrice A """
	"""
	paramètre :
	A : Matrcice
	une matrice

	retourne :
	somme : float
	La trace de A

	Rentre une matrice de taille x,x et retourne la trace de la matrice
	Soit la somme des valeurs de la diagonale principale
	"""
	somme = 0
	lig = len(A[0])
	col = len(A)
	for i in range(col) :
		for j in range(lig) :
			if i == j :
				somme += A[i][j]
	return somme

assert(trace(np.array([[1,2,3],[4,5,6],[7,8,9]]))) == 15

def valeurmax(A) :
	""" Retourne la valeur max de A et la position du coefficient """
	"""
	paramètre :
	A : Matrcice
	une matrice

	retourne :
	max : float
	valeur maximum de la matrice

	id_i : int
	indice de la colonne de la matrice A

	id_j : int
	indice de la ligne de la matrice A

	Rentre une matrice de taille x,y et retourne sa valeur maximum et sa position dans la matrice
	"""
	max = A[0][0]
	id_i, id_j = 0, 0
	lig = len(A[0])
	col = len(A)
	for i in range(col) :
		for j in range(lig) :
			if A[i][j] > max :
				max = A[i][j]
				id_i = i+1
				id_j = j+1
	return max, id_i, id_j

assert(valeurmax(np.array([[1,2,3],[4,5,6],[7,8,9]]))) == (9,3,3)
assert(valeurmax(np.array([[14,55,87,22,33,11],[99,2,16,35,48,5],[137-42,3,8,4,86,68],[0,1,2**8,3,4,5],[5,4,3,100,1,0],[65,780-779,2,65,4,0]]))) == (256,4,3)