import matplotlib.pyplot as plt
import numpy as np
from random import*
from math import*

# nombre d'itérations :
nbpoints=10000

#point de départ :
p=np.zeros((2,1))

def transformation1(p):
    c = 0.255 
    f = np.array([[0.,0.],[0.,c]])
    u = np.array([[0.5],[0]])
    res = np.dot(f,p)
    res = res + u
    return res

def transformation2(p):
    c = 0.255 
    r = 0.75 
    q = 0.625
    T = -pi/8
    f = np.array([[r*cos(T),-r*cos(T)],[r*sin(T),r*cos(T)]])
    u = np.array([[0.5-0.5*r*cos(T)],[c-0.5*r*sin(T)]])
    res = np.dot(f,p)
    res = res + u
    return res

def transformation3(p):
    c = 0.255 
    r = 0.75 
    q = 0.625
    T = -pi/5
    f = np.array([[q*cos(T),-r*sin(T)],[q*sin(T),r*cos(T)]])
    u = np.array([[0.5-0.5*q*cos(T)],[0.6*c-0.5*q*cos(T)]])
    res = np.dot(f,p)
    res = res + u
    return res

def transforme(p):
    # Choix aléatoire (avec équiprobabilité) entre les 2 transformations de fonctions
    tirage=randint(0,2)
    if (tirage==0):
        res=transformation1(p)
    elif (tirage==1):
        res=transformation2(p)
    else:
        res=transformation3(p)
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
    plt.title('Fractale en forme d’arbre')
    plt.show()
    
construction(p,nbpoints)
