import matplotlib.pyplot as plt
import numpy as np
from random import*

# nombre d'itérations :
nbpoints=10000

#point de départ :
p=np.zeros((2,1))
 
def transformation1(p):
    f1 = np.array([[0.5,-0.5],[0.5,0.5]])
    res = np.dot(f1,p)
    return res

def transformation2(p):
    f2 = np.array([[-0.5,-0.5],[0.5,-0.5]])
    u = np.array([[1],[0]])
    res = np.dot(f2,p)
    res = res + u
    return res

def transforme(p):
    # Choix aléatoire (avec équiprobabilité) entre les 2 transformations de fonctions
    tirage=random()
    if tirage <1/2 :
        res = transformation1(p)
    else :
        res = transformation2(p)
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
    plt.title('Dragon de Heighway')
    plt.show()
    
construction(p,nbpoints)
