#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import numpy as np
import numpy.linalg as alg

class Matrice () : 

    def __init__(self, matrice) :
        self.matrice = np.array(matrice)

    def affiche(self) :
        """
        retourne la matrice
        """
        return self.matrice
    
    def tailleLigne (self) :
        """
        retourne le nombre de ligne de la matrice
        """
        return len(self.matrice)
    
    def tailleColonne (self) :
        """
        retourne le nombre de colonne de la matrice
        """
        return len(self.matrice[0])
    
    def determinant2x2 (self) :
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
        calc = (self.matrice[0][0]*self.matrice[1][1])-(self.matrice[0][1]*self.matrice[1][0])
        return calc
    
    def inverse2X2 (self) :
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
        det = self.determinant2x2(self.matrice)
        if det != 0 :
            MInvers[0].append(det*self.matrice[1][1])
            MInvers[0].append(det*(-self.matrice[0][1]))
            MInvers[1].append(det*(-self.matrice[1][0]))
            MInvers[1].append(det*self.matrice[0][0])
            return np.array(MInvers)
        else :
            print("La matrice n'est pas inversible")


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
    calc = produitMatrice(A,B)
    for i in range (ligne) :
        for j in range (colonne) :
            if calc[i][j] != Identite[i][j] :
                Boolean = False
    return Boolean

######################
# Fonction opérateur #
######################

def sommeMatrice(A,B):
    """
    Calcul la somme de deux matrices

    Paramètre :
    -----------
    A : Matrice
    Matrice n°1
    
    B : Matrice
    Matrice n°2
    
    retourne :
    ----------
    C : Matrice
    la somme des matrices A et B
    """
    C = []
    lig = len(A[0])
    col = len(A)
    if lig == len(B[0]) and col == len(B) :
        for i in range(col) :
            liste = []
            for j in range(lig) :
                liste.append(A[i][j]+B[i][j])
            C.append(liste)
        return np.array(C)
    else :
        return "Erreur | problème de taille de matrice"

def differenceMatrice(A,B):
    """
    Calcul la différence entre deux matrices

    Paramètre :rtM
    -----------
    A : Matrice
    Matrice n°1
    
    B : Matrice
    -----------
    Matrice n°2
    
    retourne :
    ----------
    C : entier
    la différence des matrices A et B
    """
    C = []
    lig = len(A[0])
    col = len(A)
    if lig == len(B[0]) and col == len(B) :
        for i in range(col) :
            liste = []
            for j in range(lig) :
                liste.append(A[i][j]-B[i][j])
            C.append(liste)
        return np.array(C)
    else :
        return "Erreur | problème de taille de matrice"

def produitScalaire(A,B) :
    """
    Calcule le produit scalaire du vecteur ligne A par le vecteur colonne B 

    Paramètre :
    -----------
    A : Matrice
    ligne de la matice 1
    
    B : Matrice
    colonne de la matrice 2 
    
    retourne :
    ----------
    C : Matrice
    le produit scalaire de A et B
    """
    if len(A) == len(B) :
        C = 0
        for i in range (len(A)) :
            C = C + A[i] * B[i]
        return C
    else :
        print("Erreur | problème de taille de matrice")

def produitMatrice(A,B) :
    """ 
    Calcule le produit AB des matrices A et B s'il existe 

    Paramètre :
    -----------rtM
    A : Matrice
    Matrice n°1
    
    B : Matrice
    -----------
    Matrice n°2
    
    retourne :
    ----------
    C : Matrice
    produit de A et B
    """
    C = []
    for i in range (len(A)) :
        liste = []
        for j in range (len(B[0])) :
            lB = []
            # Prend la colonne de B
            for k in range (len(B)) : 
                lB.append(B[k][j])
            liste += [produitScalaire(A[i],lB)]
        C.append(liste)
    return np.array(C)

def puissanceMatrice(A,n) :
    """
    calcul 
    Paramètre :
    -----------
    A : Matrice
    Matrice n°1def MIdentite (longueur) :
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
    
    B : Matrice
    -----------
    Matrice n°2
    
    retourne :
    ----------
    C : entier
    la puissance de la matrice A par n

    """
    if n == 0 :
        return np.identity(len(A))

    C = A        
    while n != 1 :
        A = produitMatrice(C,A)
        n -= 1
    return A
        

"""
# exemple :

M = Matrice([[1,2],[2,3]])
Matrice.affiche(M)
sommeMatrice(Matrice.affiche(M),Matrice.affiche(M))
differenceMatrice(Matrice.affiche(M),Matrice.affiche(M))
produitMatrice(Matrice.affiche(M),Matrice.affiche(M))

a = np.array([[2,-3],[1,4]])
puissanceMatrice(a,0)
puissanceMatrice(a,1)
puissanceMatrice(a,2)
puissanceMatrice(a,3)
"""
