/**
 * \file goku.c
 * 
 * \brief programme de jeu de goku
 * 
 * \author Paolo Toé
 * 
 * \version 2.0.0
 * 
 * \date 27/11/2023
 * 
 * Ce programme est un programme de jeu de goku, un joueur doit choisir une grille de goku puis essayer de la compléter,
 * quand elle est complète le programme se termine.
 * 
 * grilles/Grille1.g
*/


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

/**
 * \def N
 * 
 * \brief constante pour définir la taille de N, elle correspond aussi à la largeur et longueur d'un bloc de goku
*/

#define N 4

/**
 * \def TAILLE
 * 
 * \brief constante pour la taille du tableau de TAILLE colonnes et lignes (Taille = N*N, ici N=4)
*/

#define TAILLE N*N

/**
 * \typedef tGrille
 * 
 * \brief type tableau à 2 dimensions de TAILLE*TAILLE entiers
*/

typedef struct {
    int valeur;
    int candidats[TAILLE];
    int nbCandidats;
} tCase1;

typedef tCase1 tGrille[TAILLE][TAILLE];


int chargerGrille(tGrille g, char nomFichier[]);
void afficherGrille(tGrille g);
void saisir(int *S);
bool possible(tGrille g, int l, int c, int val);
/*sous-fonctions de possible*/
bool possLign(tGrille g, int l,int val);
bool possColn(tGrille g, int c,int val);
bool possBloc(tGrille g, int l,int c,int val);

int CompteurCasesVides(tGrille g);

bool backtracking(tGrille grille, int numeroCase);


bool estCandidat(tCase1 laCase, int val);
void ajouterCandidat(tCase1 *laCase, int val);
void retirerCandidat(tCase1 *laCase, int val);
int nbCandidats(tCase1 laCase);
bool verifValPoss(tGrille g, int val, int l, int c);
void initialiserCandidats(tGrille g);
void affecterCandidats(tGrille g);
int retirerCandLCB(tGrille g, int l, int c, int val);
int retirerCandBloc(tGrille g, int l, int c, int val);

/**
 * \fn int main()
 * \brief Programme principal.
 * \return Code de sortie du programme (0 : sortie normale).
 * 
 * Le programme principal demande à l'utilisateur de choisir une grille puis le jeu de goku commence, le programme
 * se termine que si la grille est pleine
 * 
*/

int main()
{
    tGrille g;
    double tmpsCPU;
    clock_t debut,fin;
    char nomGrille[30];
    int nbCasesVides;


    bool progression=true;
    /*var singleton cache*/
    int nbrval, l, c, k, tmp; 

    printf("Nom du fichier ? ");
    scanf("%s", nomGrille);

    debut=clock();

    nbCasesVides = chargerGrille(g,nomGrille);
    printf("Grille initiale : \n");
    afficherGrille(g);
    
    initialiserCandidats(g);
    affecterCandidats(g);
   


    while ((nbCasesVides!=0)&&(progression))
    {
        progression = false;

        /*singleton nu*/
        for (int i = 0; i < TAILLE; i++)
        {
            for (int j = 0; j < TAILLE; j++)
            {
                
                if (g[i][j].nbCandidats==1)
                {
                    g[i][j].valeur=g[i][j].candidats[0];
                    nbCasesVides--;
                    retirerCandLCB(g, i, j, g[i][j].valeur);
                    progression = true;
                }
            }
        }

        /*singleton cache*/
        if (!(progression))
        {
            for (int i = 0; i < TAILLE; i++)
            {
                for (int j = 0; j < TAILLE; j++)
                {
                    
                    k=0;
                    while ((k< g[i][j].nbCandidats))
                    {
                        nbrval = 0;
                        l=0;
                        while ((l < TAILLE)&& (nbrval<2))
                        {
                            if ((estCandidat(g[l][j], g[i][j].candidats[k])))
                            {
                                nbrval++;
                            }
                            l++;
                        }

                        if (nbrval==1)
                        {
                            g[i][j].valeur = g[i][j].candidats[k];
                            nbCasesVides--;
                            retirerCandLCB(g, i, j, g[i][j].valeur); //retirer tous les cands de valeur
                            tmp=g[i][j].nbCandidats;
                            for (int ind = 0; ind < tmp; ind++)
                            {
                                if (g[i][j].candidats[0]!=0)
                                {
                                    retirerCandidat(&(g[i][j]), g[i][j].candidats[0]); //retire les candidats restants dans case
                                }
                            }
                            progression=true;
                        }

                        nbrval = 0;

                        c=0;
                        while ((c < TAILLE)&& (nbrval<2)) 
                        {
                            if ((estCandidat(g[i][c], g[i][j].candidats[k])))
                            {
                                nbrval++;
                            }
                            c++;
                        }
                        if (nbrval==1)
                        {
                            g[i][j].valeur = g[i][j].candidats[k];
                            nbCasesVides--;
                            retirerCandLCB(g, i, j, g[i][j].valeur); //retirer tous les cands de valeur
                            tmp=g[i][j].nbCandidats;
                            for (int ind = 0; ind < tmp; ind++)
                            {
                                if (g[i][j].candidats[0]!=0)
                                {
                                    retirerCandidat(&(g[i][j]), g[i][j].candidats[0]); //retire les candidats restants dans case
                                }
                            }
                            progression=true;
                        }

                        nbrval = 0;
                        l=i-(i%N);
                        c=j-(j%N);
                        /*parcours le bloc*/
                        while ((l < (i-(i%N) + N))&& (nbrval<2))
                        {
                            while ((c < (j-(j%N) + N))&& (nbrval<2))
                            {
                                if ((estCandidat(g[l][c], g[i][j].candidats[k])))
                                {
                                    nbrval++;
                                }
                                c++;
                            }
                            c=j-(j%N);
                            l++;
                        }
                        if (nbrval==1)
                        {
                            g[i][j].valeur = g[i][j].candidats[k];
                            nbCasesVides--;
                            retirerCandLCB(g, i, j, g[i][j].valeur); //retirer tous les cands de valeur
                            tmp=g[i][j].nbCandidats;
                            for (int ind = 0; ind < tmp; ind++)
                            {
                                if (g[i][j].candidats[0]!=0)
                                {
                                    retirerCandidat(&(g[i][j]), g[i][j].candidats[0]); //retire les candidats restants dans case
                                }
                            }
                            progression=true;
                        }
                        k++;
                    }
                }
            }
        }

    }
    if (nbCasesVides!=0)
    {
        backtracking(g, 0);
    }
    fin = clock();
    afficherGrille(g);
    
    
    
    tmpsCPU = (fin-debut)*1.0 / CLOCKS_PER_SEC;
    printf("Resolution de la grille en %lf sec\n", tmpsCPU);

    return EXIT_SUCCESS;
}

/**
 * \fn int chargerGrille(tGrille g, char nomFichier[])
 * \brief charge le contenu d'un fichier
 * \param g : grille de goku vide
 * \param nomFichier : nom du fichier a charger
 * \return le nombre de cases vides
 * 
 * Charge le contenu d'une grille et le met dans une grille de goku
 * 
*/

int chargerGrille(tGrille g, char nomFichier[])
{
    int nbCasesVides = 0;
    FILE * f;
    f = fopen(nomFichier, "rb");
    if (f==NULL)
    {
        printf("\n ERREUR sur le fichier %s\n", nomFichier);
    } 
    else 
    {
        for (int i = 0; i < TAILLE; i++)
        {
            for (int j = 0; j < TAILLE; j++)
            {
                fread((&g[i][j].valeur), sizeof(int), 1, f);
                if ((g[i][j].valeur)==0)
                {
                   nbCasesVides++;
                }
            }   
        }
    }
    fclose(f);
    return nbCasesVides;
}

/**
 * \fn void afficherGrille(tGrille g)
 * \brief Affiche une grille dans le fromat demandé par le client
 * \param g : grille de goku qui sera afichée
 * 
 * Cette procédure réalise l’affichage à l’écran de la grille et de son contenu, 
 * conformément à l'exemple de l'annexe 2
 * 
*/

void afficherGrille(tGrille g)
{
    int i,j;

    printf("      1  2  3  4    5  6  7  8    9 10 11 12   13 14 15 16 \n");
    for (i = 0; i < TAILLE; i++)
    {
        if (i%N==0) /*si i est un mutiple de N afficher ligne*/
        {
            printf("   +-------------+-------------+-------------+-------------+\n");
        }
        
        printf("%2d ",i+1);
        for (j = 0; j < TAILLE; j++)
        {
            if (j%N==0) /*si j est un mutiple de N afficher ligne*/
            {
                printf("| ");
            }

            if (g[i][j].valeur==0) /*si élément de la grille est égale à 0 afficher "."*/
            {
                printf(" . ");
            }
            else /*sinon afficher élément de la grille*/
            {
                printf("%2d ",g[i][j].valeur);
            }
            
        }
        printf("|\n");
    }
    printf("   +-------------+-------------+-------------+-------------+\n");
}

/**
 * \fn possible(tGrille g, int l, int c, int val)
 * \brief Vérifie si emplacement de valeur est possible
 * \param g : grille de goku qui va être vérifiée
 * \param l : ligne de la grille de goku
 * \param c : colonne de la grille d goku
 * \param val : valeur à insérer
 * \return Renvoie true si il est possible d'insérer val dans la , sinon retourne false
 * 
 * Cette fonction vérifie si une valeur peut être ajoutée dans une case particulière de la grille,
 * c’est- à-dire si cela respecte les règles du goku
 * 
 * Elle utilise les sous fonctons possLign, possColn et possBloc pour vérifier chque aspect de la grille
 * 
*/
bool possible(tGrille g, int l, int c, int val)
{
    bool res;
    res=(possLign(g,l,val) && possColn(g,c,val) && possBloc(g,l,c,val));
    return res;
    
}

/**
 * \fn bool possLign(tGrille g, int l,int val)
 * \brief Verife une ligne de la grille de goku
 * \param g : grille de goku qui va être vérifiée
 * \param l : ligne de la grille de goku
 * \param val : valeur à insérer
 * \return Renvoie true si il est possible d'insérer val dans la ligne, sinon retourne false
 * 
 * Cette fonction est une sous fonction de possible utilisée pour vérifier une ligne de la grille de goku.
 * 
*/

bool possLign(tGrille g, int l,int val)
{
    bool res=true;
    int i=0;
    while ((i < TAILLE)&& (res))
    {
        if (g[l][i].valeur==val) /*Boucle fait le parcours de la ligne l*/
        {
            res=false;
        }
        i++;
    }
    return res;
}

/**
 * \fn bool possColn(tGrille g, int c,int val))
 * \brief Verife une colonne de la grille de goku
 * \param g : grille de goku qui va être vérifiée
 * \param c : colonne de la grille de goku
 * \param val : valeur à insérer
 * \return Renvoie true si il est possible d'insérer val dans la colonne, sinon retourne false
 * 
 * Cette fonction est une sous-fonction de possible pour utilisée vérifier une colonne de la grille de goku.
 * 
*/

bool possColn(tGrille g, int c,int val)
{
    bool res=true;
    int i=0;
    while ((i < TAILLE)&& res) 
    {
        if (g[i][c].valeur==val) /*Boucle fait le parcours de la colonne c*/
        {
            res=false;
        }
        i++;
    }
    return res;
}

/**
 * \fn possBloc(tGrille g, int l,int c,int val)
 * \brief Verife un bloc de la grille de goku
 * \param g : grille de goku qui va être vérifiée
 * \param l : ligne de la grille de goku
 * \param c : colonne de la grille d goku
 * \param val : valeur à insérer
 * \return Renvoie true si il est possible d'insérer val dans le bloc, sinon retourne false
 * 
 * Cette fonction est une sous-fonction de possible utilisée pour vérifier un bloc de la grille de goku.
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
            if (g[i][j].valeur==val)
            {
                res=false;
            }
            j++;
        }
        j=c-(c%N);
        i++;
    }
    return res;
}

/**
 * \fn testGrillePleine(tGrille g))
 * \brief Compte nombre de cases vides
 * \param g : grille de goku qui va être analysée
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
            if (g[i][j].valeur==0)
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

bool backtracking(tGrille grille, int numeroCase){
    int ligne;
    int colonne;
    bool resultat;
    resultat = false;
    if (numeroCase == (TAILLE * TAILLE))
    {
        //on a traité toutes les cases, la grille est résolue
        resultat = true;
    }
    else{
        // On récupère les "coordonnées" de la case
        ligne = numeroCase / (TAILLE*1);
        colonne = numeroCase % (TAILLE*1);
        if(grille[ligne][colonne].valeur!=0)
        {
            // Si la case n’est pas vide, on passe à la suivante
            // (appel récursif)
            resultat = backtracking(grille, numeroCase+1);
        }
        else
        {
            for (int valeur = 1; valeur <= TAILLE; valeur++)
            {
                if (possible(grille,ligne,colonne,valeur))
                {
                    // Si la valeur est autorisée on l'inscrit
                    //dans la case...
                    grille[ligne][colonne].valeur = valeur;
                    // ... et on passe à la suivante : appel récursif
                    // pour voir si ce choix est bon par la suite
                    if (backtracking(grille,numeroCase+1))
                    {
                        resultat = true;
                    }
                    else
                    {
                        grille[ligne][colonne].valeur = 0;
                    }
                }
            }
        }
    }
    return resultat;
}

/**************************/

/**
 * \fn bool estCandidat(tCase1 laCase, int val)
 * \brief verifie si une valeur est un candidat
 * \param laCase : la case qui va etre testee
 * \param val : la valeur qui va etre testee
 * \return true si val est un candidat et false sinon
 * 
*/
bool estCandidat(tCase1 laCase, int val)
{
    bool res = false;
    int i = 0;

    while( (i < laCase.nbCandidats) &&(!(res)))
    {
        if (laCase.candidats[i]==val)
        {
            res=true;
        }
        i++;
    }
    return res;
}

/**
 * \fn ajouterCandidat(tCase1 *laCase, int val)
 * \brief ajoute une valeur a une case
 * \param laCase : la case qui va etre modifiee
 * \param val : la valeur qui va etre ajoutee
 * 
*/
void ajouterCandidat(tCase1 *laCase, int val)
{
    bool existe=false;
    int i=0, tmp;
    if ((*laCase).nbCandidats < TAILLE)
    {
        
        existe=estCandidat(*laCase,val);

        if (!(existe))
        {
            while (i <= (laCase->nbCandidats))
            {
                if ((val <= (*laCase).candidats[i])||((*laCase).candidats[i]==0)) //insère val dans le tableau (*laCase).candidats
                {
                    tmp = val;
                    val = (*laCase).candidats[i];
                    (*laCase).candidats[i] = tmp;
                }
                i++;
            }                
            (*laCase).nbCandidats++;
        }
    }
    
}

/**
 * \fn void retirerCandidat(tCase1 *laCase, int val)
 * \brief retire une valeur a une case
 * \param laCase : la case qui va etre modifiee
 * \param val : la valeur qui va etre retiree
 * 
*/
void retirerCandidat(tCase1 *laCase, int val)
{
    bool existe=false;
    int ind=0;
    for (int i = 0; i < (*laCase).nbCandidats; i++) //besoin de boucle pour trouver l'indice de val
    {
        if ((*laCase).candidats[i]==val)
        {
            existe=true;
            ind=i;
        }
        // verifie si valeur existe dans les candidats et 
    }

    if (existe)
    {
        for (int i = ind; i < (*laCase).nbCandidats-1; i++)
        {
            (*laCase).candidats[i]=(*laCase).candidats[i+1]; // decale les candidats supérieurs pou effacer val (ecrase val)
        }
        
        (*laCase).candidats[(*laCase).nbCandidats-1]=0;
        (*laCase).nbCandidats--;
    }
}

/**
 * \fn int nbCandidats(tCase1 laCase)
 * \brief compte le nombre de candidats dans une case
 * \param laCase : la case qui va etre comptee
 * \return le nombre de candidats
 * 
*/
int nbCandidats(tCase1 laCase)
{
    bool fin=false;
    int comp=0, i=0;

    while ((i < TAILLE)&&(!(fin)))
    {
        if(laCase.candidats[i]!=0)
        {
            comp++;
        }
        else
        {
            fin = true;
        }
        i++;
    }
    
    return comp;
}

/**
 * \fn bool verifValPoss(tGrille g, int val, int l, int c)
 * \brief verifie si une valeur est possible
 * \param g : la grille de goku
 * \param val : la valeur qui va etre testee
 * \param l : la ligne de la case dont on verifie la valeur
 * \param c : la colonne de la case dont on verifie la valeur
 * \return true si la val est un candidat possible pour la case de ligne l et colonne c, renvoie false sinon
 * 
 * fonction verifie si une valeur est possible (est un candidat) dans une grille (verifie si val est un candidat)
 * 
*/
bool verifValPoss(tGrille g, int val, int l, int c)
{
    bool res=true;
    int i=0, j;

    while ((i < TAILLE) && (res))
    {
        if (g[l][i].valeur == val)
        {
            res=false;
        }
        i++;
    }

    i=0;
    while ((i < TAILLE)&& (res))
    {
        if (g[i][c].valeur == val)
        {
            res=false;
        }
        i++;
    }

    i=l-(l%N);
    j=c-(c%N);
    while ((i < (l-(l%N) + N)) && (res))
    {
        while ((j < (c-(c%N) + N)) && (res))
        {
            if (g[i][j].valeur == val)
            {
                res=false;
            }
            j++;
        }
        j=c-(c%N);
        i++;
    }
    return res;
}

/**
 * \fn void initialiserCandidats(tGrille g)
 * \brief initialise une grille de goku
 * \param g : la grille de goku a initialiser
 * 
 * Initialise chaque case de la grille de goku afin que le nombre de candidats soit a 0 et qu'il
 * n'y ait aucun candidat dans la liste des candidats
 * 
*/
void initialiserCandidats(tGrille g)
{
    for (int i = 0; i < TAILLE; i++)
    {
        for (int j = 0; j < TAILLE; j++)
        {
            for (int k =0; k<TAILLE; k++)
            {
                g[i][j].candidats[k]=0;
            }
            g[i][j].nbCandidats=0;
        }
            
    }

}

/**
 * \fn void affecterCandidats(tGrille g)
 * \brief initialise une grille de goku
 * \param g : la grille de goku a affecter les candidats
 * 
 * Initialise chaque case de la grille de goku afin que le nombre de candidats soit a 0 et qu'il
 * n'y ait aucun candidat dans la liste des candidats
 * 
*/
void affecterCandidats(tGrille g)
{
    
    for (int i = 0; i < TAILLE; ++i)
    {
        for (int j = 0; j < TAILLE; ++j)
        {
            for (int val = 1; val < (TAILLE+1); ++val)
            {
                
                if (g[i][j].valeur == 0) /*verifie que valeur de case est vide*/
                {
                    
                    if (verifValPoss(g, val, i, j)) /*verifie si val est un candidat possible a cette case*/
                    {
                        ajouterCandidat(&g[i][j],val);  
                    }
                }
            }
        }
        
    }
}

/**
 * \fn int retirerCandLCB(tGrille g, int l, int c, int val)
 * \brief retire val de la ligne colonne et bloc
 * \param g : la grille de goku a modifier
 * \param l : la ligne de la case d'origine
 * \param c : la colonne de la case d'origine
 * \param val : la valeur qui va etre retiree
 * \return le nombre de candidats elimines
 * 
 * Fonction sert a retirer les candidats val de la ligne colonne et bloc d'une grille de goku
 * 
*/
int retirerCandLCB(tGrille g, int l, int c, int val)
{
    int i=0, j, comp=0;
    while (i < TAILLE)
    {
        if (estCandidat(g[l][i], val))
        {
            retirerCandidat(&g[l][i], val);
            comp++;
        }
        i++;
    }

    i=0;
    while (i < TAILLE) 
    {
        if (estCandidat(g[i][c], val))
        {
            retirerCandidat(&g[i][c], val);
            comp++;
        }
        i++;
    }

    i=l-(l%N);
    j=c-(c%N);
    while (i < (l-(l%N) + N))
    {
        while (j < (c-(c%N) + N))
        {
            if (estCandidat(g[i][j], val))
            {
                retirerCandidat(&g[i][j], val);
                comp++;
            }
            j++;
        }
        j=c-(c%N);
        i++;
    }
    return comp;
}

/**
 * \fn int retirerCandBloc(tGrille g, int l, int c, int val)
 * \brief retire val du bloc
 * \param g : la grille de goku a modifier
 * \param l : la ligne de la case d'origine
 * \param c : la colonne de la case d'origine
 * \param val : la valeur qui va etre retiree
 * \return le nombre de candidats elimines
 * 
 * Fonction sert a retirer les candidats val du bloc d'une grille de goku
 * 
*/
int retirerCandBloc(tGrille g, int l, int c, int val)
{
    int i, j, comp=0;

    i=l-(l%N);
    j=c-(c%N);
    while (i < (l-(l%N) + N))
    {
        while (j < (c-(c%N) + N))
        {
            if (estCandidat(g[i][j], val))
            {
                retirerCandidat(&g[i][j], val);
                comp++;
            }
            j++;
        }
        j=c-(c%N);
        i++;
    }
    return comp;
}