#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import numpy as np
import numpy.linalg as alg

#############  Question 1 ###########################
M1= np.array([[5,6,7,8,9]])
M2= np.array([[1,1,1,1,1]])
M3= np.array([[1],[2],[3]])
M4= np.array([[1,2,4],[-1,2,3],[1,8,9]])
############ Question 2 #############################

A= np.array([[2,2.3,2.4],[9,-8,9.81],[22,1,0.145]])
#print("A = ",A)

a = A[1:3,:]
#print("a = ",a) # Affichage des lignes 2 et 3 de la matrice A :

b = A[1:3,1:3]
#print("b = ",b) # Affichage du bloc composé des lignes 2 et 3 et des colonnes 2 et 3 de la matrice A :

########### Question 3 ##############################

M5= np.concatenate((M1,[[10]]),1)
#print("M5 = ",M5)
M6= np.concatenate((M2,M1),1)
#print("M6 = ",M6)
M7= np.concatenate((M1,M2),0)
#print("M7 = ",M7)
M8= np.concatenate((M3,[[4]]),0)
#print("M8 = ",M8)
M9= np.concatenate((M4,np.array([[1],[7],[4]])),1)
#print("M9 = ",M9)
M10= np.concatenate((M4,M3),1)
#print("M10 = ",M10)
#M11= np.concatenate((M4,M3), axis = 0)
#print("M11 = ",M11)
# ########### Question 4 ##############################

M12= np.concatenate((np.array([[2]]),M2),1)
#print("M12 = ",M12)
M13= np.concatenate((np.array([[9]]),M3,np.array([[8]])),0)
#print("M13 = ",M13)
M14= np.delete(M4,1,0)
#print("M14 = ",M14)
M15= np.delete(M1,0,1)
#print("M15 = ",M15)
M16= np.concatenate(([[8]],M1),1)
#print("M16 = ",M16)
M17= np.delete(M4,2,1)
#print("M17 = ",M17)
# #############  Produits de matrices ###########################


# #############  Question 1 ###########################
# M4.M3 =
# M3.M4 =
# M7.M1 =
# M1.M7 =
# M11.M3 =
# M3.M11 =
# M1.M13 =
# M13.M1 =

# #############  Question 2 ###########################

# (a) (A+B)^2=
# (b) A^2 +2AB+B^2 =
# (c)
# (d)  (C+D)^2=
#    C^2 + 2CD +D^2 = 
   
#   #############  Question 3 ########################### 

#  C=

# #############  Question 4 ###########################

# M=


# #############  Question 5 ###########################

#   a=

#   b=

#   c=

# #############  Question 6 ###########################

# D=
