import matplotlib.pyplot as plt
import numpy as np
from random import*

# nombre d'itérations :
nbpoints=10000

#point de départ :
p=np.zeros((2,1))

def transformation1(p):
    f = np.array([[0.,0.],[0.,0.16]])
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

def transforme(p):
    # Choix aléatoire (avec équiprobabilité) entre les 2 transformations de fonctions
    tirage=random()
    if (0 <= tirage <=0.01 ):
        res=transformation1(p)
    elif (0.01 < tirage <=0.85):
        res=transformation2(p)
    elif (0.85< tirage <=0.92):
        res=transformation3(p)
    elif (0.92< tirage <=1):
        res=transformation4(p)
    return res

def construction(p, nbpoints):
    x = [p[0,0]]
    y = [p[1,0]]
    for i in range(nbpoints):
        p = transforme(p)
        x.append(p[0,0])
        y.append(p[1,0])
    
# Représentation graphique
    plt.plot(x, y, 'o')
    plt.title('Fougère de Barnsley')
    plt.show()
    
construction(p,nbpoints)
