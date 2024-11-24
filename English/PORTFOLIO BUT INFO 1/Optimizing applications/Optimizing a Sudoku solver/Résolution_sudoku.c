// Merci de NE PAS placer dans ce fichier de scanf, de printf ou d'équivalents.
// Renommez ce fichier par le nom de votre équipe, en n'oubliant pas l'extension.


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


// Size constants - used for array definitions
#define N 5
#define TAILLE (N * N)

// equivalent global variables - used for array usage
int nn, ttaille;

/*pour utiliser ce sytème j'ai du faire des modifications ai fonctions exitantes*/
typedef struct {
    int valeur;
    int candidats[TAILLE];
    int nbCandidats;
} tCase1;

typedef tCase1 tGrille[TAILLE][TAILLE];

void loadGrid(tGrille, char[30]);
void generateAnswer(tGrille);

// TODO: Place your resolution function definition here
// ----------------------------------------------------
void resolution(tGrille g);

bool possible(tGrille g, int l, int c, int val);
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

int main(int argc, char **argv) {
    // Usage: cmd <grid> <size>
    // example: ./sudoku Grille1.sud 3

    // size of a subgrid. TODO: Replace "N" by "nn" in the array usage of your function
    nn = atoi(argv[2]);
    // size of the grid.  TODO: Replace "TAILLE" by "ttaille" in the array usage of your function
    ttaille = (nn * nn);
    
    tGrille grid;
    // load the named grid
    loadGrid(grid, argv[1]);

    // TODO: Place your resolution function call here
    // ----------------------------------------------
    resolution(grid);

    generateAnswer(grid);
    return EXIT_SUCCESS;
}

void loadGrid(tGrille grid, char filename[30]) {
    FILE *f;
    int openingGrid[TAILLE*TAILLE];

    f = fopen(filename, "rb");
    if (f == NULL) {
        printf("\nError occured opening %s\n", filename);
        exit(EXIT_FAILURE);
    }
    else {
        fread(openingGrid, sizeof(int), ttaille * ttaille, f);
        fclose(f);

        for (int l = 0; l < ttaille; l++) {
            for (int c = 0; c < ttaille; c++) {
                grid[l][c].valeur = openingGrid[l*ttaille+c];
            }
        }
    }
}

void generateAnswer(tGrille grid) {
    char buffer[TAILLE * TAILLE * 2] = "";
    
    FILE *f;
    f = fopen("answer.txt", "w");
    if (f == NULL) {
        printf("An error occured while generating answer.\n");
        exit(1);
    }
    
    // write the string based on the grid state
    for (int l = 0; l < ttaille; l++) {
        for (int c = 0; c < ttaille; c++) {
            sprintf(buffer+((l*ttaille+c)*2), "%.2d", grid[l][c].valeur);
        }
    }
    buffer[ttaille * ttaille * 2] = '\0';
    printf("%s\n", buffer);

    // write in the file
    fprintf(f, "%s\n", buffer);
    fclose(f);
}

/*My functions*/
void resolution(tGrille g)
{
    int nbCasesVides;
    bool progression=true;
    /*var singleton cache*/
    int nbrval, l, c, k, tmp; 
    
    nbCasesVides= CompteurCasesVides(g);
    initialiserCandidats(g);
    affecterCandidats(g);
    
   
    while ((nbCasesVides!=0)&&(progression))
    {
        progression = false;

        /*singleton nu*/
        for (int i = 0; i < ttaille; i++)
        {
            for (int j = 0; j < ttaille; j++)
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
            for (int i = 0; i < ttaille; i++)
            {
                for (int j = 0; j < ttaille; j++)
                {
                    
                    k=0;
                    while ((k< g[i][j].nbCandidats))
                    {
                        nbrval = 0;
                        l=0;
                        /*parcours ligne*/
                        while ((l < ttaille)&& (nbrval<2))
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
                        /*parcours colonne*/
                        while ((c < ttaille)&& (nbrval<2)) 
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
                        l=i-(i%nn);
                        c=j-(j%nn);
                        /*parcours le bloc*/
                        while ((l < (i-(i%nn) + nn))&& (nbrval<2))
                        {
                            while ((c < (j-(j%nn) + nn))&& (nbrval<2))
                            {
                                if ((estCandidat(g[l][c], g[i][j].candidats[k])))
                                {
                                    nbrval++;
                                }
                                c++;
                            }
                            c=j-(j%nn);
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
}

/*****/

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
    return res;
    
}

/**
 * \fn bool possLign(tGrille g, int l,int val)
 * \brief Verife une ligne de la grille de sudoku
 * \param g : grille de sudoku qui va être vérifiée
 * \param l : ligne de la grille de sudoku
 * \param val : valeur à insérer
 * \return Renvoie true si il est possible d'insérer val dans la ligne, sinon retourne false
 * 
 * Cette fonction est une sous fonction de possible utilisée pour vérifier une ligne de la grille de sudoku.
 * 
*/

bool possLign(tGrille g, int l,int val)
{
    bool res=true;
    int i=0;
    while ((i < ttaille)&& (res))
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
 * \brief Verife une colonne de la grille de sudoku
 * \param g : grille de sudoku qui va être vérifiée
 * \param c : colonne de la grille de sudoku
 * \param val : valeur à insérer
 * \return Renvoie true si il est possible d'insérer val dans la colonne, sinon retourne false
 * 
 * Cette fonction est une sous-fonction de possible pour utilisée vérifier une colonne de la grille de sudoku.
 * 
*/

bool possColn(tGrille g, int c,int val)
{
    bool res=true;
    int i=0;
    while ((i < ttaille)&& res) 
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
 * \brief Verife un bloc de la grille de sudoku
 * \param g : grille de sudoku qui va être vérifiée
 * \param l : ligne de la grille de sudoku
 * \param c : colonne de la grille d sudoku
 * \param val : valeur à insérer
 * \return Renvoie true si il est possible d'insérer val dans le bloc, sinon retourne false
 * 
 * Cette fonction est une sous-fonction de possible utilisée pour vérifier un bloc de la grille de sudoku.
 * 
*/

bool possBloc(tGrille g, int l,int c,int val)
{
    bool res=true;
    int i, j;
    i=l-(l%nn); /*i est initialisée à la coordonée de la la ligne de la case en haut à gauche du bloc*/
    j=c-(c%nn); /*j est initialisée à la coordonée de la la colonne de la case en haut à gauche du bloc*/
    /*Boucles vont faire le parcours du bloc dans laquelle se situe la case de ligne l est de collonne c*/
    while ((i < (l-(l%nn) + nn))&& res)
    {
        while ((j < (c-(c%nn) + nn))&& res)
        {
            if (g[i][j].valeur==val)
            {
                res=false;
            }
            j++;
        }
        j=c-(c%nn);
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
    while (i<ttaille)
    {
        while (j<ttaille)
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
    if (numeroCase == (ttaille * ttaille))
    {
        //on a traité toutes les cases, la grille est résolue
        resultat = true;
    }
    else{
        // On récupère les "coordonnées" de la case
        ligne = numeroCase / (ttaille*1);
        colonne = numeroCase % (ttaille*1);
        if(grille[ligne][colonne].valeur!=0)
        {
            // Si la case n’est pas vide, on passe à la suivante
            // (appel récursif)
            resultat = backtracking(grille, numeroCase+1);
        }
        else
        {
            for (int valeur = 1; valeur <= grille[ligne][colonne].nbCandidats; valeur++)
            {
                if (possible(grille,ligne,colonne,grille[ligne][colonne].candidats[valeur]))
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
    if ((*laCase).nbCandidats < ttaille)
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

    while ((i < ttaille)&&(!(fin)))
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
 * \param g : la grille de sudoku
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

    while ((i < ttaille) && (res))
    {
        if (g[l][i].valeur == val)
        {
            res=false;
        }
        i++;
    }

    i=0;
    while ((i < ttaille)&& (res))
    {
        if (g[i][c].valeur == val)
        {
            res=false;
        }
        i++;
    }

    i=l-(l%nn);
    j=c-(c%nn);
    while ((i < (l-(l%nn) + nn)) && (res))
    {
        while ((j < (c-(c%nn) + nn)) && (res))
        {
            if (g[i][j].valeur == val)
            {
                res=false;
            }
            j++;
        }
        j=c-(c%nn);
        i++;
    }
    return res;
}

/**
 * \fn void initialiserCandidats(tGrille g)
 * \brief initialise une grille de sudoku
 * \param g : la grille de sudoku a initialiser
 * 
 * Initialise chaque case de la grille de sudoku afin que le nombre de candidats soit a 0 et qu'il
 * n'y ait aucun candidat dans la liste des candidats
 * 
*/
void initialiserCandidats(tGrille g)
{
    for (int i = 0; i < ttaille; i++)
    {
        for (int j = 0; j < ttaille; j++)
        {
            for (int k =0; k<ttaille; k++)
            {
                g[i][j].candidats[k]=0;
            }
            g[i][j].nbCandidats=0;
        }
            
    }

}

/**
 * \fn void affecterCandidats(tGrille g)
 * \brief initialise une grille de sudoku
 * \param g : la grille de sudoku a affecter les candidats
 * 
 * Initialise chaque case de la grille de sudoku afin que le nombre de candidats soit a 0 et qu'il
 * n'y ait aucun candidat dans la liste des candidats
 * 
*/
void affecterCandidats(tGrille g)
{
    
    for (int i = 0; i < ttaille; ++i)
    {
        for (int j = 0; j < ttaille; ++j)
        {
            for (int val = 1; val < (ttaille+1); ++val)
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
 * \param g : la grille de sudoku a modifier
 * \param l : la ligne de la case d'origine
 * \param c : la colonne de la case d'origine
 * \param val : la valeur qui va etre retiree
 * \return le nombre de candidats elimines
 * 
 * Fonction sert a retirer les candidats val de la ligne colonne et bloc d'une grille de sudoku
 * 
*/
int retirerCandLCB(tGrille g, int l, int c, int val)
{
    int i=0, j, comp=0;
    while (i < ttaille)
    {
        if (estCandidat(g[l][i], val))
        {
            retirerCandidat(&g[l][i], val);
            comp++;
        }
        i++;
    }

    i=0;
    while (i < ttaille) 
    {
        if (estCandidat(g[i][c], val))
        {
            retirerCandidat(&g[i][c], val);
            comp++;
        }
        i++;
    }

    i=l-(l%nn);
    j=c-(c%nn);
    while (i < (l-(l%nn) + nn))
    {
        while (j < (c-(c%nn) + nn))
        {
            if (estCandidat(g[i][j], val))
            {
                retirerCandidat(&g[i][j], val);
                comp++;
            }
            j++;
        }
        j=c-(c%nn);
        i++;
    }
    return comp;
}

/**
 * \fn int retirerCandBloc(tGrille g, int l, int c, int val)
 * \brief retire val du bloc
 * \param g : la grille de sudoku a modifier
 * \param l : la ligne de la case d'origine
 * \param c : la colonne de la case d'origine
 * \param val : la valeur qui va etre retiree
 * \return le nombre de candidats elimines
 * 
 * Fonction sert a retirer les candidats val du bloc d'une grille de sudoku
 * 
*/
int retirerCandBloc(tGrille g, int l, int c, int val)
{
    int i, j, comp=0;

    i=l-(l%nn);
    j=c-(c%nn);
    while (i < (l-(l%nn) + nn))
    {
        while (j < (c-(c%nn) + nn))
        {
            if (estCandidat(g[i][j], val))
            {
                retirerCandidat(&g[i][j], val);
                comp++;
            }
            j++;
        }
        j=c-(c%nn);
        i++;
    }
    return comp;
}