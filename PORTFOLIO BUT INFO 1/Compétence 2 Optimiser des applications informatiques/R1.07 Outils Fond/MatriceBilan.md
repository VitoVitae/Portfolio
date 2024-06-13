<style>
    body {
        color : black;
        background-color : white;
    }

    h1 {
        color : white;
        background-color : red;
    }

    h2 {
        color : white;
        background-color : blue;
    }

    h3 {
        color : white;
        background-color : green;
    }

    h4 {
        color : white;
        background-color : darkgreen;
    }

    .underline {
        border-bottom : 1px red solid;
    }

    .boite {
        color : black;
        border : 1px black solid;
    }
    img{
        width : 400px;
    }
    .grand{
        height : 350px;
    }
    pre {
        color : white;
    }
</style>

# R1.07 - outils Mathématiques fondamentaux

## Matrice

### Dimension

m \* n = <img src="image/DimensionMatrice.png" title="Dimension de matrice" alt="Dimension de matrice" class="grand">

### Type de Matrice

#### Matrice Ligne

Dimension :

M1 = 1\*n avec n ∈ N\*\\{1}

#### Matrice Colonne

Dimension :

M2 = n\*1 avec n ∈ N\*\\{1}

#### Matrice Carré

Dimension :

M3 = 2\*2

#### Matrice Rectangle

Dimension :

M4 = n\*m avec n et m ∈ N\* et n > m ou m > n

![Les différentes matrice](image/typeMatrice.png)

#### Matrice Identité

![matrice identité](image/identite.png)

#### Matrice Diagonale

Une matrice identité avec l'ensemble des valeurs différents de 1

![matrice diagonale](image/diagonale.png)

#### Matrice Triangulaire

![matrice Triangulaire](image/triangulaire.png)

#### Matrice Inverse

Une matrice multiplier par son inverse donne la matrice identité

M = n\*n

M \* M' = In

M' \* M = In

![matrice inverse](image/inverse.png)

Trouver la matrice inverse à partir du déterminant

![matrice inverse](image/inverseDet.png)

#### Déterminant

<span class="underline">Matrice 2\*2 : </span>

Une matrice possède un inverse si le déterminant est différent de 0

det(A) = (1.1 \* 2.2) - (2.1 \* 1.2)

![matrice déterminant](image/det2.png)

### Commande Python

bibliothèque : numpy et numpy.linalg

<span class="underline">numpy.`array`(liste) :</span>

<span class="boite">
Fabrique une matrice à partir d'une liste de liste
</span>

<span class="underline">numpy.`zeros`(n,m) :</span>

<span class="boite">
Fabrique une matrice remplis de 0 à partir de la dimension
</span>

<span class="underline">numpy.`ones`(n,m) :</span>

<span class="boite">
Fabrique une matrice remplis de 1 à partir des dimension n et m
</span>

<span class="underline">numpy.`diag`(liste) :</span>

<span class="boite">
Fabrique une matrice diagonale à partir d'une liste en 1 dimension
</span>

<span class="underline">numpy.`eye`(n) :</span>

<span class="boite">
Fabrique une matrice identité en n\*n à partir d'une dimension n
</span>

<span class="underline">M.`shape`() :</span>

<span class="boite">
Renvoie la dimension de la matrice : (n,m)
</span>

<span class="underline">M.`reshape`(m,n) :</span>

<span class="boite">
Redimensionne une matrice, sans modifier ses termes
</span>

<span class="underline">numpy.`concatenate`((M1, M2, ...,Mn), axis=0)</span>

<pre>
Créer une matrice par bloc

    axis=0 : par ligne

        M = array([[ 1., 1., 1.],
                    [ 1., 1., 1.],
                    [ 0., 0., 0.],
                    [ 0., 0., 0.]])

    axis=1 : par colonne

        array([[ 1., 1., 1., 0., 0., 0.],
                [ 1., 1., 1., 0., 0., 0.]])
</pre>

<span class="underline">numpy.`delete`(M,nb,axis=0)</span>

<span class="boite">
> Supprime un axe de la matrice
</span>

<pre>
    Supprime de la matrice M
    l'axe d'indice nb en ligne

    Donc numpy.delete(M,1,0)
    array([[ 1., 1., 1.],
            [ 0., 0., 0.],
            [ 0., 0., 0.]])
</pre>

### Indice

<img src="image/A.png" title="Matrice A" alt="Matrice A">

dimension : 3\*2

`A[1, 0]` # terme de la deuxieme ligne, premiere colonne

`A[0, :]` # premiere ligne sous forme de tableau a 1 dimension

`A[0:1, :]` # premiere ligne sous forme de matrice ligne

`A[ :, 1]` # deuxieme colonne sous forme de tableau a 1 dimension

`A[ :, 1 :2]` # deuxieme colonne sous forme de matrice colonne

`A[1:3, 0 :2]` # sous-matrice lignes 2 et 3, colonnes 1 et 2

### Calcul de Matrice

#### L'addition

![addition](image/addition.png)

#### La multiplication

M1 \* M2 != M2 \* M1

<span class="underline">Dimension :</span>

M1 = M2 \* M3 de dimension M2 = 5\*4 M3 = 4\*5

M1 = 5\*5

<span class="underline">L'opération :</span>

![multiplication](image/multiplication.png)
