# -*- coding: utf-8 -*-

import numpy as np
import numpy.linalg as alg

# Fichier contenant tout les calculs de matrice
import classeMatrice as CM

A = np.array([[3,4],[-4,-5]])
B = np.array([[-5,-4],[4,3]])
# C = CM.produitMatrice(A,B) == CM.produitMatrice(B,A)
# La matrice B est la matrice inverse de A 

def MIdentite (longueur) :
    """
    créer la matrice identité suivant une longeur

    Paramètre :
    -----------
    longueur : int
    dimension de la matrice identité
    
    retourne :
    ----------
    I : Matrice
    la matrice identité
    """
    I = []
    compteur = 0
    for i in range (longueur) :
        temp = []
        for j in range (longueur) :
            if compteur == j:
                temp.append(1)
            else :
                temp.append(0)
        I.append(temp)
        compteur += 1
    return np.array(I)

def isinverse (A,B) :
    """
    Vérifie si le produit de deux matrices forment la matrice inverse

    Paramètre :
    -----------
    A : Matrice
    Matrice n°1
    
    B : Matrice
    Matrice n°2
    
    retourne :
    ----------
    Boolean : Bool
    True si le produit des deux matrices forment la matrice inverse
    False sinon
    """
    Boolean = True
    ligne = len(A)
    colonne = len(A[0])
    Identite = MIdentite(ligne)
    calc = CM.produitMatrice(A,B)
    for i in range (ligne) :
        for j in range (colonne) :
            if calc[i][j] != Identite[i][j] :
                Boolean = False
    return Boolean

assert isinverse(A,B) == True
assert isinverse(B,A) == True

"""
A = np.array([[1,2],[3,4]])
# det(A) = 1*4-2*3 = 4-6 = -2

# L'inverse de A est :
#   (-1/2)*[[4,-2],[-3,1]]
"""
A = np.array([[1,2],[3,4]])

def determinant2x2 (A) :
    """
    Calcul le déterminant de la matrice A

    Paramètre :
    -----------
    A : Matrice
    Matrice n°1
    
    retourne :
    ----------
    calc : int
    déterminant de A
    """
    calc = (A[0][0]*A[1][1])-(A[0][1]*A[1][0])
    return calc

def inverse2X2 (A) :
    """
    Calcul la matrice inverse de la matrice A

    Paramètre :
    -----------
    A : Matrice
    Matrice n°1
    
    retourne :
    ----------
    MInvers : Matrice
    Matrice inverse de A
    """
    MInvers = [[],[]]
    det = determinant2x2(A)
    if det != 0 :
        MInvers[0].append(det*A[1][1])
        MInvers[0].append(det*(-A[0][1]))
        MInvers[1].append(det*(-A[1][0]))
        MInvers[1].append(det*A[0][0])
        return np.array(MInvers)
    else :
        print("La matrice n'est pas inversible")

print(inverse2X2(A))

"""
Exercice 6

1. 
    A = [[3,4],[-4,-5]]
    B = [[-5,-4],[4,3]]

    det A = (3*-5)-(4*-4) = (-15)-(-16)=1
    A est inversible
    A*B = [[3*-5+4*4,3*-4+4*3],[-4*-5+-5*4,-4*-4+-5*3]] = [[1,0],[0,1]]
    B est la matrice inverse de A

2.
    A = [[1,1,-1],[2,0,2],[-2,2,-1]]
    B = 1/10*[[4,1,-2],[2,3,4],[-4,4,2]]
 
"""