/**
 * \file Elimination_Version1.c
 * 
 * \brief Programme de résolution de sudoku
 * 
 * \author Paolo Toé
 * 
 * \version 1.0.0
 * 
 * \date 26/11/2023
 * 
 *  Programme de résolution de grille de sudoku utilisant les techniques
 *  de singleton nu, singleton caché, paire nu, et paire caché
 * 
*/


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define N 3
#define TAILLE (N*N)

typedef struct {
    int valeur;
    int candidats[TAILLE];
    int nbCandidats;
} tCase1;

typedef tCase1 tGrille[TAILLE][TAILLE];

int chargerGrille(tGrille g, char nomFichier[]);

void afficherGrille(tGrille g);

void initialiserCandidats(tGrille g);

void affecterCandidats(tGrille g);

int retirerCandLCB(tGrille g, int l, int c, int val);
int retirerCandBloc(tGrille g, int l, int c, int val);
bool verifValPoss(tGrille g, int val, int l, int c);


void ajouterCandidat(tCase1 *laCase, int val);
void retirerCandidat(tCase1 *laCase, int val);
bool estCandidat( tCase1 laCase, int val);
int nbCandidats(tCase1 laCase);



void afficherCand(tCase1 laCase, int i, int j)
{
    printf("Candidats Case %d %d : ", i+1, j+1);
    for (int k = 0; k < TAILLE; k++)
    {
        printf("%d ", laCase.candidats[k]);
    }
    printf("\n");
}

void afficherStats(char nomg[], int cr, int nbrCasesVides, int ce, int nbC);
void afficher_tCase1(tCase1 Case);

int main()
{
    tGrille sud;
    char nomGrille[30];
    bool progression=true;
    int nbCasesVides, CandElim = 0, nbCand = 0, Cases;

    /*var singleton cache*/
    int nbrval, l, c, k, tmp; 

    /*var paires cachee*/
    bool doublon;
    int indL, indC, comp, end;

    /*var paires cachee*/
    bool paire1, paire2;
    int L1,C1,L2,C2, valA, valB;

    /*time*/
    double tmpsCPU;
    clock_t debut,fin;

    printf("Nom du fichier ? ");
    scanf("%s", nomGrille);

    nbCasesVides = chargerGrille(sud, nomGrille);
    Cases=nbCasesVides;
    initialiserCandidats(sud);

    debut = clock();

    afficherGrille(sud);

    affecterCandidats(sud);

    for (int i = 0; i < TAILLE; i++)
    {
        for (int j = 0; j < TAILLE; j++)
        {
            nbCand = nbCand + sud[i][j].nbCandidats;
        }
    }
    
    while ((nbCasesVides!=0)&&(progression))
    {
        progression = false;

        /*singleton nu*/
        for (int i = 0; i < TAILLE; i++)
        {
            for (int j = 0; j < TAILLE; j++)
            {
                
                if (sud[i][j].nbCandidats==1)
                {
                    sud[i][j].valeur=sud[i][j].candidats[0];
                    nbCasesVides--;
                    CandElim = CandElim + retirerCandLCB(sud, i, j, sud[i][j].valeur);
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
                        while ((k< sud[i][j].nbCandidats))
                        {
                            nbrval = 0;
                            l=0;
                            while ((l < TAILLE)&& (nbrval<2))
                            {
                                if ((estCandidat(sud[l][j], sud[i][j].candidats[k])))
                                {
                                    nbrval++;
                                }
                                l++;
                            }

                            if (nbrval==1)
                            {
                                sud[i][j].valeur = sud[i][j].candidats[k];
                                nbCasesVides--;
                                CandElim = CandElim + retirerCandLCB(sud, i, j, sud[i][j].valeur); //retirer tous les cands de valeur
                                tmp=sud[i][j].nbCandidats;
                                for (int ind = 0; ind < tmp; ind++)
                                {
                                    if (sud[i][j].candidats[0]!=0)
                                    {
                                        retirerCandidat(&(sud[i][j]), sud[i][j].candidats[0]); //retire les candidats restants dans case
                                        CandElim++;
                                    }
                                }
                                progression=true;
                            }

                            nbrval = 0;

                            c=0;
                            while ((c < TAILLE)&& (nbrval<2)) 
                            {
                                if ((estCandidat(sud[i][c], sud[i][j].candidats[k])))
                                {
                                    nbrval++;
                                }
                                c++;
                            }
                            if (nbrval==1)
                            {
                                sud[i][j].valeur = sud[i][j].candidats[k];
                                nbCasesVides--;
                                CandElim = CandElim + retirerCandLCB(sud, i, j, sud[i][j].valeur); //retirer tous les cands de valeur
                                tmp=sud[i][j].nbCandidats;
                                for (int ind = 0; ind < tmp; ind++)
                                {
                                    if (sud[i][j].candidats[0]!=0)
                                    {
                                        retirerCandidat(&(sud[i][j]), sud[i][j].candidats[0]); //retire les candidats restants dans case
                                        CandElim++;
                                    }
                                }
                                progression=true;
                            }

                            nbrval = 0;
                            l=i-(i%3);
                            c=j-(j%3);
                            /*parcours le bloc*/
                            while ((l < (i-(i%3) + N))&& (nbrval<2))
                            {
                                while ((c < (j-(j%3) + N))&& (nbrval<2))
                                {
                                    if ((estCandidat(sud[l][c], sud[i][j].candidats[k])))
                                    {
                                        nbrval++;
                                    }
                                    c++;
                                }
                                c=j-(j%3);
                                l++;
                            }
                            if (nbrval==1)
                            {
                                sud[i][j].valeur = sud[i][j].candidats[k];
                                nbCasesVides--;
                                CandElim = CandElim + retirerCandLCB(sud, i, j, sud[i][j].valeur); //retirer tous les cands de valeur
                                tmp=sud[i][j].nbCandidats;
                                for (int ind = 0; ind < tmp; ind++)
                                {
                                    if (sud[i][j].candidats[0]!=0)
                                    {
                                        retirerCandidat(&(sud[i][j]), sud[i][j].candidats[0]); //retire les candidats restants dans case
                                        CandElim++;
                                    }
                                }
                                progression=true;
                            }
                            k++;
                        }
                }
            }
        }

        /*paires nu*/
        if (!(progression))
        {
            for (int i = 0; i < TAILLE; i++)
            {
                for (int j = 0; j < TAILLE; j++)
                {
                    doublon=false;
                    if (sud[i][j].nbCandidats==2)
                    {
                        comp=0;
                        l=i-(i%3);
                        c=j-(j%3);
                        while ((l < (i-(i%3) + N))&& (comp<3))
                        {
                            while ((c < (j-(j%3) + N))&& (comp<3))
                            {
                                if ( (sud[l][c].nbCandidats==2))
                                {
                                    comp=0;
                                    for (int k = 0; k < sud[i][j].nbCandidats; k++)
                                    {
                                        if (estCandidat(sud[l][c],sud[i][j].candidats[k])) //verifie que les candidats sont les memes
                                        {
                                            comp++;
                                        }
                                    }
                                    if (comp==2)
                                    {
                                        if ((l!=i)||(c!=j)) /*verifie que la paire est bien de deux cases differentes*/
                                        {
                                            doublon=true;
                                            indL=l;
                                            indC=c;
                                        } 
                                    }
                                    if (comp>2)
                                    {
                                        doublon =false;
                                    }
                                }
                                c++;
                            }
                            c=j-(j%3);
                            l++;
                        }
                        if (doublon)
                        {
                            end=CandElim;
                            for (int ind = 0; ind < sud[i][j].nbCandidats; ind++)
                            {
                                tmp=sud[i][j].candidats[0]; //garde le candidat qui va etre enlebve dans une variable intermediaire
                                
                                CandElim = CandElim + retirerCandBloc(sud, i, j, sud[i][j].candidats[0]);
                                
                                /*pour conserver candidats dans les cases paires*/
                                
                                ajouterCandidat(&sud[i][j],tmp);
                                CandElim--;
                                ajouterCandidat(&sud[indL][indC],tmp);
                                CandElim--;
                            }
                            if (end!=CandElim) /*verifie que des casndidats on bien ete elimines*/
                            {
                                progression=true;
                            } 
                        }
                    }
                }
            }
        }

        /*paire cachee*/
        if (!(progression))
        {
            for (int i = 0; i < TAILLE; i++)
            {
                for (int j = 0; j < TAILLE; j++)
                {
                    k=0;
                    paire1 =false;
                    paire2 =false;
                    while ((k<sud[i][j].nbCandidats)&&(!(paire1))&&(!(paire2)))
                    {
                        if (!(paire1)) // paire 1 pas encore trouvee
                        {
                            l=i-(i%3);
                            c=j-(j%3);
                            comp=0;
                            while ((l < (i-(i%3) + N))&& (comp<3))
                            {
                                while ((c < (j-(j%3) + N))&& (comp<3))
                                {
                                    if (estCandidat(sud[l][c], sud[i][j].candidats[k]))
                                    {
                                        comp++;
                                        if (comp==2) /*garde coords de la potentielle paire*/
                                        {
                                            L1=l;
                                            C1=c;
                                        }
                                            
                                    }
                                        
                                    c++;
                                }
                                c=j-(j%3);
                                l++;
                            }
                            if (comp==2) /*si valeur apparait seulement 2 fois une "paire" est confirmee*/
                            {
                                paire1=true;
                                valA=sud[i][j].candidats[k];
                            }
                        }
                        else
                        {
                            l=i-(i%3);
                            c=j-(j%3);
                            comp=0;
                            while ((l < (i-(i%3) + N))&& (comp<3))
                            {
                                while ((c < (j-(j%3) + N))&& (comp<3))
                                {
                                    if (estCandidat(sud[l][c], sud[i][j].candidats[k]))
                                    {
                                        comp++;
                                        if (comp==2) /*garde coords de la potentielle paire*/
                                        {
                                            L2=l;
                                            C2=c;
                                        }
                                    }
                                    c++;   
                                }
                                c=j-(j%3);
                                l++;
                            }
                            if (comp==2)
                            {
                                if ((L1==L2)&&(C1==C2)) /*verifie si c'est bien la meme case*/
                                {
                                    paire2=true;
                                    valB=sud[i][j].candidats[k];
                                }
                            }
                        }
                        k++;
                    }
                    if ((paire1)&&(paire2))/*si les deux paires existent*/
                    {
                        tmp=sud[i][j].nbCandidats;
                        for (int ind = 0; ind < tmp; ind++)
                        {
                            retirerCandidat(&sud[i][j],sud[i][j].candidats[0]);
                            CandElim++;
                        }
                        tmp=sud[L1][C1].nbCandidats;
                        for (int ind = 0; ind < tmp; ind++)
                        {
                            retirerCandidat(&sud[L1][C1],sud[L1][C1].candidats[0]);
                            CandElim++;
                        }
                        ajouterCandidat(&sud[i][j],valA);
                        CandElim--;
                        ajouterCandidat(&sud[i][j],valB);
                        CandElim--;
                        ajouterCandidat(&sud[L1][C1],valA);
                        CandElim--;
                        ajouterCandidat(&sud[L1][C1],valB);
                        CandElim--;
                        progression=true;
                    }              
                }
            }
        }
        /*fin paire cachee*/
    }
    /*fin boucle while*/

    afficherGrille(sud);
    afficherStats(nomGrille, Cases, nbCasesVides, CandElim, nbCand);
    fin = clock();

    tmpsCPU = (fin-debut)*1.0 / CLOCKS_PER_SEC;

    printf("Temps %lf\n", tmpsCPU);
}


/**
 * \fn int chargerGrille(tGrille g, char nomFichier[])
 * \brief charge le contenu d'un fichier
 * \param g : grille de sudoku vide
 * \param nomFichier : nom du fichier a charger
 * \return le nombre de cases vides
 * 
 * Charge le contenu d'une grille et le met dans une grille de sudoku
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
 * \param g : grille de sudoku qui sera afichée
 * 
 * Cette procédure réalise l’affichage à l’écran de la grille et de son contenu, 
 * conformément à l'exemple de l'annexe 2
 * 
*/

void afficherGrille(tGrille g)
{
    int i,j;

    printf("    1 2 3   4 5 6   7 8 9  \n");
    for (i = 0; i < TAILLE; i++)
    {
        if (i%3==0) /*si i est un mutiple de 3 afficher ligne*/
        {
            printf("  +-------+-------+-------+\n");
        }
        
        printf("%d ",i+1);
        for (j = 0; j < TAILLE; j++)
        {
            if (j%3==0) /*si j est un mutiple de 3 afficher ligne*/
            {
                printf("| ");
            }

            if (g[i][j].valeur==0) /*si élément de la grille est égale à 0 afficher "."*/
            {
                printf(". ");
            }
            else /*sinon afficher élément de la grille*/
            {
                printf("%d ",g[i][j].valeur);
            }
            
        }
        printf("|\n");
    }
    printf("  +-------+-------+-------+\n");
}

/**
 * \fn void afficherStats(char nomg[], int cr, int nbrCasesVides, int ce, int nbC)
 * \brief affiche les stats
 * \param nomg : nom de la grille
 * \param cr : cases a remplir
 * \param nbrCasesVides : nombre de cases vides
 * \param ce : candidats elimines
 * \param nbC : nombre total de candidats
 * 
 * Affiche les resultats d'une resolution de sudoku:
 * - le nombre de cases remplies
 * - le taux de remplissage
 * - le nombre de candidats elimines
 * - et le pourcentage d'elimination
 * 
*/

void afficherStats(char nomg[], int cr, int nbrCasesVides, int ce, int nbC)
{
    printf("**** RESULTATS POUR %s ****\n\n", nomg);
    
    printf("Nombre de cases remplies = %d sur %d    ",cr-nbrCasesVides, cr);
    printf("Taux de remplissage = %.3f %%\n\n", (cr-nbrCasesVides)/(cr*1.0)*100);
    
    printf("Nombre de candidats elimines = %d   ",ce);
    printf("Pourcentage d'elimination = %.3f %%\n\n", ce/(nbC*1.0)*100);
}

/**
 * \fn void afficher_tCase1(tCase1 Case)
 * \brief Affiche une case
 * \param Case : la case qui va etre affichee
 * 
 * 
*/
void afficher_tCase1(tCase1 Case)
{
    int i=0;
    printf("Valeur : %d     nbCandidats : %d \n", Case.valeur, Case.nbCandidats);
    printf("Candidat(s) : ");

    while ((i<TAILLE)&&(Case.candidats[i]!=0))
    {
        printf("%d ",Case.candidats[i]);
        i++;
    }
    printf("\n\n");
}

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

    i=l-(l%3);
    j=c-(c%3);
    while ((i < (l-(l%3) + N)) && (res))
    {
        while ((j < (c-(c%3) + N)) && (res))
        {
            if (g[i][j].valeur == val)
            {
                res=false;
            }
            j++;
        }
        j=c-(c%3);
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
 * \brief initialise une grille de sudoku
 * \param g : la grille de sudoku a affecter les candidats
 * 
 * Initialise chaque case de la grille de sudoku afin que le nombre de candidats soit a 0 et qu'il
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

    i=l-(l%3);
    j=c-(c%3);
    while (i < (l-(l%3) + N))
    {
        while (j < (c-(c%3) + N))
        {
            if (estCandidat(g[i][j], val))
            {
                retirerCandidat(&g[i][j], val);
                comp++;
            }
            j++;
        }
        j=c-(c%3);
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

    i=l-(l%3);
    j=c-(c%3);
    while (i < (l-(l%3) + N))
    {
        while (j < (c-(c%3) + N))
        {
            if (estCandidat(g[i][j], val))
            {
                retirerCandidat(&g[i][j], val);
                comp++;
            }
            j++;
        }
        j=c-(c%3);
        i++;
    }
    return comp;
}