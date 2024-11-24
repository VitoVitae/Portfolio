# SAE 1.01 Partie 1

## Index

- [Pseudo code de l'algorithme principal](#pseudo-code-de-lalgorithme-principal)
- [Descriptons des procédures](#description-des-procédures)
- [Descriptons des fonctions](#description-des-fonctions)

t_grille est un nouveau type utilisé dasn ce programme, c'est une tableau à deux dimensions de taille 9*9 (tableau[9][9]).

## Pseudo code de l'algorithme principal

```
programme sudoku c'est
    /*creation type t-grille de taille 9 avec une constante N_GRILLE*/
    constante N_GRILLE :=9;
    type t_grille := tableau[N_GRILLE][N_GRILLE] de entier;

    /*decralation prototypes procédures*/
    procédure choixDifficulte(entF/sortF t_grille sdk);
    procédure afficheGrille(entF t_grille sdk);
    procédure inserer(entF entier col, entF entier lig, entF entier nbr, entF/sortF t_grille sk);

    /*decralation prototypes fonctions*/
    fonction verifier(entF entier var) delivre booléen;
    fonction endGame(entF t_grille sdk) delivre booléen;

    fonction verifierLigne(entF entier l, entF t_grille sdk) delivre booléen;
    fonction verifierColonne(entF entier c, entF t_grille sdk) delivre booléen;

    /*decralation constantes*/
    /*exemple de déclaration de grille*/
    constante t_grille FACILE := ((-9,0,-6, 0,0,-4, -3,-1,-5),(0,0,-8, -3,-5,0, -9,0,-6),(-3,0,-1, -6,-9,0, -8,-4,-2),(-6,0,0, -9,0,0, 0,-5,-1),(-2,-8,-7, -4,0,-5, -6,0,-3),(-5,-1,0, 0,-3,0, 0,-8,0),(0,0,0, -5,-2,-9, 0,-7,-8),(-8,0,0, -7,-4,0, -1,0,-2),(0,-4,-2, -1,-6,-8, -5,-3,-9));

    /*constante pour la fin du programme, pour faire la vérification finale*/
    constante entier FIN := -1;
    
début
    /*déclaration d'une grille sudoku vide avec le type t_grille*/
    sk : t_grille;
    /*déclaration de deux variables booléennes qui sont expliquées plus bas*/
    verif, gagne: booléen;
    /*déclaration des varaibles utilisées pour saisir des valeurs dans le programme*/
    /*x pour la ligne de la grille, y pour la colonne et val pour la valeur à insérer dans la grille*/
    x, y, val : entier;

    /*affectation initiale des valeurs pour éviter des erreurs plus tard (cas où l'utilisateur saisit immédiatement -1)*/
    x:=0;
    y:=0;
    val:=0;

    choixDifficulte(entE/sortE sk);
        
    gagne:=faux;
    
    /*boucle "tant que" qui s'effectue tant que la grille n'a pas été complétée correctement*/
    tant que (gagne!=vrai) faire

        afficheGrille(entE sk);
        
        /*boucle commence et se répète tant que la variable saisie est incorrecte*/
        faire
            ecrireEcran(">> Colonne: ");
            lireClavier(x);

            verif := verifier(entE x);
        tant que ( verif == Faux)

        /*vérifie si x==FIN (FIN=-1) afin de savoir si le programme va passer immédiatement à la vérification de fin*/
        si (x!=FIN) alors
            /*boucle commence et se répète tant que la variable saisie est incorrecte*/
            faire
                écrireEcran(">> Ligne: ");
                lireClavier(y);

                verif := verifier(entE x);
            tant que ( verif == Faux)
        finsi

        /*vérifie si y==FIN (FIN=-1) afin de savoir si le programme va passer immédiatement à la vérification de fin*/
        si (y!=FIN) alors
            /*dans la grille sudoku si une case a une valeure négative elle ne peut être modifiée car elle est une valeur initiale de la grille*/
            si (sk[x][y]>=0) alors
                /*boucle commence et se répète tant que la variable saisie est incorrecte*/
                faire
                    écrireEcran(">> Valeur: ");
                    lireClavier(val);

                    verif := verifier(entE x);
                tant que ( verif == Faux)*
            /*message d'erreur affiché quand une valeur initiale veut être modifiée par l'utilisateur*/
            sinon
                écrireEcran("Impossible de changer cette case\n");
            finsi

            /*si au moins une des variables est n'est pas égale à la varible de fin la valeur saisie âr l'utilisateur est insérée*/
            si ((x!=FIN)&&(y!=FIN)&&(val!=FIN))
                inserer(entE x,entE y,entE val,entE/sortE sk);
            sinon
                /*endGame renvoie vrai si la grille à été correctement complétée et faux sinon*/
                gagne:=endGame(entE sk);
            finsi
    finfaire
fin
```

## Description des procédures

### procédure choixDifficulte

prototype:
procédure choixDifficulte(entF/sortF t_grille sdk);

Cette procédure prend en paramètre d'entrée et sortie une variable t_grille vide de largeur et longeur 9 et la modifie selon la difficulté choisie par l'utilisateur.

L'utilisateur choisit une difficulté avec le prompt:
```
>> Quelle difficulte voulez vous ? (1,2,3) : 
```

l'utilisateur doit saisir 1,2 ou 3 sinon la procédure affiche:

```
<valeur> n'est pas une difficulté acceptée, réessayez.

>> Quelle difficulte voulez vous ? (1,2,3) : 

```
Ici valeur est la valeur incorrecte saisie.

### procédure afficheGrille

prototype:
procédure afficheGrille(entF t_grille sdk);

Cette procédure prend en paramètre d'entrée une variable t_grille de largeur et longeur 9 et l'affiche comme ceci:

```
 -----------------------
| 5 x x | x 7 x | x x x |
| 6 x x | 1 9 5 | x x x |
| x 9 8 | x x x | x 6 x |
 -----------------------
| 8 x x | x 6 x | x x 3 |
| 4 x x | 8 x 3 | x x 1 |
| 7 x x | x 2 x | x x 6 |
 -----------------------
| x 6 x | x x x | 2 8 x |
| x x x | 4 1 9 | x x 5 |
| x x x | x 8 x | x 7 9 |
 -----------------------

```
(Cette grille n'est qu'un exemple d'affichage)
Le x s'affiche dès que la valeur du tableau en paramètre a une valeur nulle (0)

### procédure inserer

prototype:
procédure inserer(entF entier col, entF entier lig, entF entier nbr, entF/sortF t_grille sk);

Cette procédure prend en paramètre d'entrée des variables entières col, lig et nbr et en paramètre d'entrée et sortie une variable t_grille de largeur et longeur 9.

Cette procédure remplace la valeur à la case de colonne **col** et de ligne **lig** aavec la valeur **nbr**


## Description des fonctions

### fonction verifier

protoype:
fonction verifier(entF entier var) delivre booléen;

Cette fonction prend en paramètre d'entrée un entier et renvoie un booléen.

La fonction renvoie **faux** si var est strictement supérieur à 9 ou strictement inférieur à -1, sinon la fonction renvoie **vrai**.

Cette fonction est utilisée pour vérifier que la valeur saisie par l'utilisateur est correcte

### fonction endGame

prototype:
fonction endGame(entF t_grille sdk) delivre booléen;

Cette fonction prend en paramètre d'entrée une variable t_grille de largeur et longeur 9 et elle renvoie un booléen.

La fonction renvoie **vrai** si sdk à bien été remplie selon les rêgles du sudoku sinon elle renvoie **faux**.

La fonction utilise les fonction verifierLigne et verifierColonne pour la vérification de toute la grille, si ces fonctions ,pour chacune des lignes et colonnes, revoie vrai, la grille a correctement été remplie et la fonction endGame renvoie **vrai**, mais si une instance de ces fonction renvoie faux, la fonction endGame renvoie **faux** car la grille n'est pa correcte.
 
### fonction verifierLigne

prototype:
fonction verifierLigne(entF entier l, entF t_grille sdk) delivre booléen;

Cette fonction prend en paramètre d'entrée une variable entière l et une variable t_grille de largeur et longeur 9 et elle renvoie un booléen.

La variable **l** correspond à une ligne de la grille, cette fonction fait une somme de toutes les valeurs de la ligne et si la somme est égale à 45 la fonction renvoie **vrai**, sion elle renvoie **faux**. La somme des valeurs de la ligne doit être égale à 45 car 1+2+3+4+5+6+7+8+9=45, et donc une ligne est correctement remplie si la somme de toutes ses valeurs est égale à 45.


### fonction verifierColonne

prototype:
fonction verifierColonne(entF entier c, entF t_grille sdk) delivre booléen;

Cette fonction prend en paramètre d'entrée une variable entière c et une variable t_grille de largeur et longeur 9 et elle renvoie un booléen.

La variable **c** correspond à une colonne de la grille, cette fonction fait une somme de toutes les valeurs de la colonne et si la somme est égale à 45 la fonction renvoie **vrai**, sion elle renvoie **faux**. La somme des valeurs de la colonne doit être égale à 45 car 1+2+3+4+5+6+7+8+9=45, et donc une colonne est correctement remplie si la somme de toutes ses valeurs est égale à 45.
