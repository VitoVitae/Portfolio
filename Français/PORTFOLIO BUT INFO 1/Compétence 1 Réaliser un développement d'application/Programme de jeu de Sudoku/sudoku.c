/**
 * \file sudoku.c
 * 
 * \brief programme de jeu de sudoku
 * 
 * \author Paolo Toé
 * 
 * \version 2.0.0
 * 
 * \date 27/11/2023
 * 
 * Ce programme est un programme de jeu de sudoku, un joueur doit choisir une grille de sudoku puis essayer de la compléter,
 * quand elle est complète le programme se termine.
 * 
 * grilles/Grille1.sud
*/


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/**
 * \def N
 * 
 * \brief constante pour définir la taille de N, elle correspond aussi à la largeur et longueur d'un bloc de sudoku
*/

#define N 2

/**
 * \def TAILLE
 * 
 * \brief constante pour la taille du tableau de TAILLE colonnes et lignes (Taille = N*N, ici N=2)
*/

#define TAILLE N*N

/**
 * \typedef tGrille
 * 
 * \brief type tableau à 2 dimensions de TAILLE*TAILLE entiers
*/

typedef int tGrille[TAILLE][TAILLE];



void chargerGrille(tGrille g);
void afficherGrille(tGrille g);
void saisir(int *S);
bool possible(tGrille g, int l, int c, int val);
/*sous-fonctions de possible*/
bool possLign(tGrille g, int l,int val);
bool possColn(tGrille g, int c,int val);
bool possBloc(tGrille g, int l,int c,int val);

int CompteurCasesVides(tGrille g);


/**
 * \fn int main()
 * \brief Programme principal.
 * \return Code de sortie du programme (0 : sortie normale).
 * 
 * Le programme principal demande à l'utilisateur de choisir une grille puis le jeu de sudoku commence, le programme
 * se termine que si la grille est pleine
 * 
*/

int main()
{

    int numLigne, numColonne, valeur, nbrCasesVides;
    
    tGrille grille1 = { {1,2,3,0},
                    {3,0,1,0},
                    {2,1,4,3},
                    {0,0,2,1}};

    char action;
    bool undo=false; /*variable pour savoir si il est possible de de effacer la dernière valeur*/

    nbrCasesVides=CompteurCasesVides(grille1); /*Nombre de cases vides initialisées*/
    while (nbrCasesVides>0)
        {
            afficherGrille(grille1);

            printf("Action (A ou Z) ? ");
            scanf(" %c",&action);

            if ((action=='Z')&&(undo))
            {
                if (grille1[numLigne-1][numColonne-1] != 0)
                {
                    grille1[numLigne-1][numColonne-1] = 0;
                    nbrCasesVides++;
                }
                
            }
            else if (action=='A')
            {
                printf("Numéro de ligne ? ");
                saisir(&numLigne);
                printf("Numéro de colonne ? ");
                saisir(&numColonne);
                if (grille1[numLigne-1][numColonne-1]!=0) /*-1 aux indices pour que les coordonées correspondent au tableau*/
                {
                    printf("Impossible, la case n'est pas libre.\n");
                    undo=false;
                }
                else
                {
                    printf("Valeur à insérer (entre 1 et 4): ");
                    saisir(&valeur);
                    if (possible(grille1,numLigne-1,numColonne-1,valeur))
                    {
                        grille1[numLigne-1][numColonne-1] = valeur;
                        nbrCasesVides--; /*Quand une case est remplie le nombre de cases vides diminue*/
                        undo=true;
                    }
                }
            }
        }
    printf("Grille pleine, fin de partie\n"); /*Jeu est finit si il n'y a plus de cases vides*/
}

/**
 * \fn void chargerGrille(tGrille g)
 * \brief Prend les donneées d'un fichier .sud et affecte chaque chiffre à la grille vide en paramètre
 * \param g : grille de sudoku vide
 * 
 * Cette procédure permet de charger en mémoire une grille de sudoku existante à partir d’un fichier dont le nom est lu au clavier.
*/

void chargerGrille(tGrille g)
{
    char nomFichier[30];
    FILE * f;
    printf("Nom du fichier ? ");
    scanf("%s", nomFichier);
    f = fopen(nomFichier, "rb");
    if (f==NULL)
    {
        printf("\n ERREUR sur le fichier %s\n", nomFichier);
    } 
    else 
    {
        fread(g, sizeof(int), TAILLE*TAILLE, f);
    }
        fclose(f);
}

/**
 * \fn void afficherGrille(tGrille g)
 * \brief Affiche une grille dans le fromat demandé par le client
 * \param g : grille de sudoku qui sera afichée
 * 
 * Cette procédure réalise l’affichage à l’écran de la grille et de son contenu, 
 * conformément à l'exemple de l'annexe 2
 * 
*/

void afficherGrille(tGrille g)
{
    int i,j;

    printf("    1 2    3 4   \n");
    for (i = 0; i < TAILLE; i++)
    {
        if (i%N==0) /*si i est un mutiple de 2 afficher ligne*/
        {
            printf("  +-----+-----+\n");
        }
        
        printf("%d ",i+1);
        for (j = 0; j < TAILLE; j++)
        {
            if (j%N==0) /*si j est un mutiple de 2 afficher ligne*/
            {
                printf("| ");
            }

            if (g[i][j]==0) /*si élément de la grille est égale à 0 afficher "."*/
            {
                printf(". ");
            }
            else /*sinon afficher élément de la grille*/
            {
                printf("%d ",g[i][j]);
            }
            
        }
        printf("|\n");
    }
    printf("  +-----+-----+\n");
}

/**
 * \fn void saisir(int S)
 * \brief permet de saisir un chiffre valide pour la grille
 * \param S: paramètre de sortie de la valeur lue, un entier compris entre 1 et 2**2 (= Taille)
 * 
 * Cette procédure est chargée de lire au clavier une valeur. 
 * La saisie se répète tant que la valeur n’est pas valide. 
 * En effet, la valeur lue doit être un entier, et cet entier doit être compris entre 1 et 3**2.
 * Les messages d’erreur devront être explicites.
 * Cette procédure sert aussi bien à saisir une numéro de ligne ou un numéro de colonne qu’à saisir une valeur à insérer dans la grille.
 *
*/

void saisir(int *S)
{
    *S=0;
    char rep[100];
    
    while (((*S<1)||(*S>TAILLE)))
    {
        scanf("%s",rep);
        if ((atof(rep)==atoll(rep))&&(sscanf(rep, "%d", S) !=0)) /*Vérifie si la valeur saisie est bien un entier pas un float ET si la valeur saisie n'est pas un caratère ou une chaine de caratères*/
        {
            if ((*S<1)||(*S>TAILLE))
            {
                printf("valeur Eronée, ressaisir: "); /*Si la valeur saisie est un entier mais pas entre 1 et 9 (TAILLE), la vfonction renvoie un message d'erreur*/
            }
        } 
        else 
        {
            printf("valeur Eronée, ressaisir: "); /*Si la valeur saisie n'est pas un entier*/
        }
    }
}

/**
 * \fn possible(tGrille g, int l, int c, int val)
 * \brief Vérifie si emplacement de valeur est possible
 * \param g : grille de sudoku qui va être vérifiée
 * \param l : ligne de la grille de sudoku
 * \param c : colonne de la grille d sudoku
 * \param val : valeur à insérer
 * \return Renvoie true si il est possible d'insérer val dans la , sinon retourne false
 * 
 * Cette fonction vérifie si une valeur peut être ajoutée dans une case particulière de la grille,
 * c’est- à-dire si cela respecte les règles du sudoku
 * 
 * Elle utilise les sous fonctons possLign, possColn et possBloc pour vérifier chque aspect de la grille
 * 
*/
bool possible(tGrille g, int l, int c, int val)
{
    bool res;
    res=(possLign(g,l,val) && possColn(g,c,val) && possBloc(g,l,c,val));


    if (!(res))
    {
        printf("Impossible d'insérer %d\n",val);
    }
    return res;
    
}

/**
 * \fn bool possLign(tGrille g, int l,int val)
 * \brief Verife une ligne de la grille de Sudoku
 * \param g : grille de sudoku qui va être vérifiée
 * \param l : ligne de la grille de sudoku
 * \param val : valeur à insérer
 * \return Renvoie true si il est possible d'insérer val dans la ligne, sinon retourne false
 * 
 * Cette fonction est une sous fonction de possible utilisée pour vérifier une ligne de la grille de Sudoku.
 * 
*/

bool possLign(tGrille g, int l,int val)
{
    bool res=true;
    int i=0;
    while ((i < TAILLE)&& (res))
    {
        if (g[l][i]==val) /*Boucle fait le parcours de la ligne l*/
        {
            res=false;
        }
        i++;
    }
    return res;
}

/**
 * \fn bool possColn(tGrille g, int c,int val))
 * \brief Verife une colonne de la grille de Sudoku
 * \param g : grille de sudoku qui va être vérifiée
 * \param c : colonne de la grille de sudoku
 * \param val : valeur à insérer
 * \return Renvoie true si il est possible d'insérer val dans la colonne, sinon retourne false
 * 
 * Cette fonction est une sous-fonction de possible pour utilisée vérifier une colonne de la grille de Sudoku.
 * 
*/

bool possColn(tGrille g, int c,int val)
{
    bool res=true;
    int i=0;
    while ((i < TAILLE)&& res) 
    {
        if (g[i][c]==val) /*Boucle fait le parcours de la colonne c*/
        {
            res=false;
        }
        i++;
    }
    return res;
}

/**
 * \fn possBloc(tGrille g, int l,int c,int val)
 * \brief Verife un bloc de la grille de Sudoku
 * \param g : grille de sudoku qui va être vérifiée
 * \param l : ligne de la grille de sudoku
 * \param c : colonne de la grille d sudoku
 * \param val : valeur à insérer
 * \return Renvoie true si il est possible d'insérer val dans le bloc, sinon retourne false
 * 
 * Cette fonction est une sous-fonction de possible utilisée pour vérifier un bloc de la grille de Sudoku.
 * 
*/

bool possBloc(tGrille g, int l,int c,int val)
{
    bool res=true;
    int i, j;
    i=l-(l%N); /*i est initialisée à la coordonée de la la ligne de la case en haut à gauche du bloc*/
    j=c-(c%N); /*j est initialisée à la coordonée de la la colonne de la case en haut à gauche du bloc*/
    /*Boucles vont faire le parcours du bloc dans laquelle se situe la case de ligne l est de collonne c*/
    while ((i < (l-(l%N) + N))&& res)
    {
        while ((j < (c-(c%N) + N))&& res)
        {
            if (g[i][j]==val)
            {
                res=false;
            }
            j++;
        }
        i++;
    }
    return res;
}

/**
 * \fn testGrillePleine(tGrille g))
 * \brief Compte nombre de cases vides
 * \param g : grille de sudoku qui va être analysée
 * \return La fonction renvoie un entier qui correspond au nombre de cases vides
 * 
 * Cette fonction compte le nombre de cases vides dans une grille "g" et renvoie un entier correspondant 
 * à ce nombre, pour compter le nombre des cases vides, la fontion compte le nombre d'occurences de 0 dans
 * la grille "g".
 */
int CompteurCasesVides(tGrille g)
{
    int res=0;
    int i=0, j=0;

    /*Boucle fait le parcours du tableau à deux dimensions*/
    while (i<TAILLE)
    {
        while (j<TAILLE)
        {
            if (g[i][j]==0)
            {
                res++;
            }
            j++;
        }
        i++;
        j=0;
    }
    return res;
}