/**
 * \file Elimination_Version2.c
 * 
 * \brief Programme de résolution de sudoku
 * 
 * \author Stanislas Rolland
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

/* Definition des constantes symboliques */
#define N 3
#define TAILLE (N * N)

/* Definition des structures */
typedef struct {
    int valeur;
    bool candidats[TAILLE + 1];
    int nbCandidats;
} tCase2;

/* Definition des types */
typedef tCase2 tGrille[TAILLE][TAILLE];

/* Prototypes des fonctions et procedures */
int singletonNu(tGrille g);
int singletonCache(tGrille g);
int pairesNues(tGrille g);
int pairesCachees(tGrille g);
bool verifValPoss(tGrille g, tCase2 laCase, int val, int l, int c);
void ajouterCandidat(tCase2 *laCase, int val);
void retirerCandidat(tCase2 *laCase, int val);
bool estCandidat(tCase2 laCase, int val);
void initialiserCandidats(tGrille g);
int nbCandidats(tCase2 laCase);
int chargerGrille(tGrille g, char nomFichier[]);
void afficherStats(char nomg[], int cr, int nbrCasesVides, int ce, int nbC);

/*nouvelles fonctions*/
int retirerCandLCB(tGrille g, int l, int c, int val);
void affecterCandidats(tGrille g);
void afficherGrille(tGrille g);

void afficherCand(tCase2 laCase, int i, int j)
{
    printf("Candidats Case %d %d : ", i+1, j+1);
    for (int k = 0; k < TAILLE+1; k++)
    {
        if (laCase.candidats[k])
        {
            printf("%d ", k);
        }  
    }
    printf("\n");
}

/* Programme principal */
int main(){
    tGrille g;
    bool progression;
    int nbCasesVides, cr=0, ce=0, nbC=0;
    char nomGrille[30];

    printf("Nom du fichier ? ");
    scanf("%s", nomGrille);
    nbCasesVides=chargerGrille(g,nomGrille);

    cr=nbCasesVides; // pour guarder le nombre de cases a remplir
    initialiserCandidats(g);
    affecterCandidats(g); // crée les candidats
    /*compte le nombre de candidats*/
    for (int i = 0; i < TAILLE; i++)
    {
        for (int j = 0; j < TAILLE; j++)
        {
            nbC = nbC + g[i][j].nbCandidats;
        }
    }
    afficherGrille(g); // affiche grille avant les techniques
    progression=true;
    while ((nbCasesVides!=0)&&(progression)){
        progression=false;
        /*singleton nu*/
        for(int i=0; i < TAILLE; i++){
            for(int j=0; j < TAILLE; j++){
                if(g[i][j].nbCandidats==1){
                    for(int k=1; k <=TAILLE; k++){
                        if(g[i][j].candidats[k]){
                            g[i][j].valeur=k;
                            nbCasesVides--;
                            ce = ce + retirerCandLCB(g, i, j, k);
                            progression=true;
                        }
                    }
                }
            }
        }
        /*singleton caché*/
        for(int val=1; val<=TAILLE; val++){
            for(int ligne=0; ligne<TAILLE; ligne++){
                int compteur=0;
                int colonneCandidat=-1;
                for(int colonne=0; colonne<TAILLE; colonne++){
                    if(g[ligne][colonne].candidats[val]){
                        compteur++;
                        colonneCandidat=colonne;
                    }
                }
                if(compteur==1){
                    if(verifValPoss(g, g[ligne][colonneCandidat], val, ligne ,colonneCandidat)){
                        g[ligne][colonneCandidat].valeur=val;
                        nbCasesVides--;
                        ce = ce + retirerCandLCB(g, ligne, colonneCandidat, val);
                        progression=true;
                    }
                }
            }
            for(int colonne=0; colonne<TAILLE; colonne++){
                int compteur=0;
                int ligneCandidat=-1;
                for(int ligne=0; ligne<TAILLE; ligne++){
                    if(g[ligne][colonne].candidats[val]){
                        compteur++;
                        ligneCandidat=ligne;
                    }
                }
                if(compteur==1){
                    if(verifValPoss(g, g[ligneCandidat][colonne], val, ligneCandidat ,colonne)){
                        g[ligneCandidat][colonne].valeur=val;
                        nbCasesVides--;
                        ce = ce + retirerCandLCB(g, ligneCandidat, colonne, val);
                        progression=true;
                    }
                }
            }
            for(int blocLigne=0; blocLigne<N; blocLigne++){
                for(int blocColonne=0; blocColonne<N; blocColonne++){
                    int compteur=0;
                    int ligneCandidat=-1;
                    int colonneCandidat=-1;
                    for(int ligne=blocLigne%N; ligne<(blocLigne+1)*N; ligne++){
                        for(int colonne=blocColonne*N; colonne<(blocColonne+1)*N; colonne++){
                            if(g[ligne][colonne].candidats[val]){
                                compteur++;
                                ligneCandidat=ligne;
                                colonneCandidat=colonne;
                            }
                        }
                    }
                    if(compteur==1){
                        if(verifValPoss(g, g[ligneCandidat][colonneCandidat], val, ligneCandidat ,colonneCandidat)){
                            g[ligneCandidat][colonneCandidat].valeur=val;
                            nbCasesVides--;
                            ce = ce + retirerCandLCB(g, ligneCandidat, colonneCandidat, val);
                            progression=true;
                        }
                    }
                }
            }
        }
        /*paires nues ou évidentes*/
        bool paireIdentique=true;
        for(int blocLigne=0; blocLigne<N; blocLigne++){
            for(int blocColonne=0; blocColonne<N; blocColonne++){
                for(int i =blocLigne*N; i<(blocLigne+1)*N-1; i++){
                    for (int j=blocColonne*N; j<(blocColonne+1)*N;j++){
                        for(int i2=i+1; i2<(blocLigne+1)*N; i2++){
                            for(int j2=blocColonne*N; j2<(blocColonne + 1)*N; j2++){
                                for(int k=1; k<=TAILLE; k++){
                                    if(g[i][j].candidats[k]!=g[i2][j2].candidats[k]){ //on vérifie si les cases d'indices [i][j] et [i2][j2] ont la même paire de candidats
                                        paireIdentique=false;
                                        break;
                                    }
                                }
                                if(paireIdentique){ //on enlève les candidats des autres paires des autres cases
                                    for(int i3=blocLigne*N; i3<(blocLigne+1)*N; i3++){
                                        for(int j3=blocColonne*N; j3<(blocColonne+1)*N; j3++){
                                            if (((i3!=i)||(j3!=j))&&((i3!=i2)||(j3!=j2))){
                                                for(int k=1; k<=TAILLE; k++){
                                                    if((g[i][j].candidats[k])&&(g[i2][j2].candidats[k])){
                                                        retirerCandidat(&g[i3][j3], k);
                                                        ce+=2; //on élimine la paire de candidat
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        /*paires cachées*/
        bool paireIdentique2=true;
        bool autrePaireIdentique = false;
        for(int blocLigne=0; blocLigne<N; blocLigne++){
            for(int blocColonne=0; blocColonne<N; blocColonne++){
                for(int i=blocLigne*N; i<(blocLigne+1)*N-1; i++){
                    for(int j=blocColonne*N; j<(blocColonne+1)*N; j++){
                        for(int i2=i+1; i2<(blocLigne+1)*N; i2++){
                            for(int j2=blocColonne*N; j2<(blocColonne+1)*N; j2++){
                                for(int k=1; k<=TAILLE; k++){
                                    if(g[i][j].candidats[k]!=g[i2][j2].candidats[k]){ //on vérifie si les cases d'indices [i][j] et [i2][j2] ont la même paire de candidats
                                        paireIdentique2=false;
                                        break;
                                    }
                                }
                                if(paireIdentique2){ //si la paire est identique
                                    for(int i3=blocLigne*N; i3<(blocLigne+1)*N; i3++){
                                        for(int j3=blocColonne*N; j3<(blocColonne+1)*N; j3++){
                                            if(((i3!=i)||(j3!=j))&&((i3!=i2)||(j3!=j2))){
                                                for (int k=1; k<=TAILLE; k++){ //on cherche un autre paire identique aux précédentes
                                                    if(g[i][j].candidats[k]&&g[i2][j2].candidats[k]){
                                                        autrePaireIdentique=true;
                                                        break;
                                                    }
                                                }
                                                if(autrePaireIdentique){
                                                    break;
                                                }
                                            }
                                        }
                                        if(autrePaireIdentique){
                                            break;
                                        }
                                    }
                                    if(!autrePaireIdentique){ //si il n'y a pas d'autre paire identique
                                        for(int i3=blocLigne*N; i3<(blocLigne+1)*N; i3++){
                                            for(int j3=blocColonne*N; j3<(blocColonne+1)*N; j3++){
                                                if(((i3!=i)&&(i3!=i2))||((j3!=j)&&(j3!=j2))){
                                                    for(int k=1; k<=TAILLE; k++){
                                                        if((g[i][j].candidats[k])&&(g[i2][j2].candidats[k])){
                                                            retirerCandidat(&g[i3][j3], k);
                                                            ce+=2; //on élimine la paire de candidat
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        if(nbCasesVides==0){
            progression=false;
        }
    }
    afficherGrille(g); // affiche grille apres les techniques
    afficherStats(nomGrille,cr,nbCasesVides,ce,nbC);
    return EXIT_SUCCESS;
}
/**
 * \fn int chargerGrille(tGrille g, char nomFichier[])
 * \brief charge le contenu d'un fichier
 * \param g : grille de sudoku vide
 * \param nomFichier : nom du fichier a charger
 * \return le nombre de cases vides
 * Charge le contenu d'une grille et le met dans une grille de sudoku
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
 * \fn bool verifValPoss(tGrille g, tCase2 laCase, int val, int l, int c)
 * \brief retire le candidat val de la ligne colonne et bloc
 * \param g : grille de sudoku qui sera afichée
 * \param val : la valeur possible d'une case
 * \param l : l'indice de ligne d'une case
 * \param c : l'indice de colonne d'une case
 * \return le nombre de candidats elimines
 * Fonction sert à retirer les candidats val de la ligne colonne et bloc
*/
int retirerCandLCB(tGrille g, int l, int c, int val){
    int i=0, j, comp=0;
    while(i<TAILLE){
        if(estCandidat(g[l][i], val)){
            retirerCandidat(&g[l][i], val);
            comp++;
        }
        i++;
    }
    i=0;
    while(i<TAILLE){
        if(estCandidat(g[i][c], val)){
            retirerCandidat(&g[i][c], val);
            comp++;
        }
        i++;
    }
    i=l-(l%N);
    j=c-(c%N);
    while(i<(l-(l%N)+N)){
        while(j<(c-(c%N)+N)){
            if(estCandidat(g[i][j], val)){
                retirerCandidat(&g[i][j],val);
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
 * \fn bool verifValPoss(tGrille g, tCase2 laCase, int val, int l, int c)
 * \brief vérifie si une valeur peut être affectée à une case
 * \param g : grille de sudoku qui sera afichée
 * \param laCase : une case de la grille
 * \param val : la valeur possible d'une case
 * \param l : l'indice de ligne d'une case
 * \param c : l'indice de colonne d'une case
 * \return true si la val est un candidat possible pour la case de ligne l et colonne c, renvoie false sinon
 * Fonction verifie si une valeur est possible dans une grille (verifie si val est un candidat) 
*/
bool verifValPoss(tGrille g, tCase2 laCase, int val, int l, int c){
    bool res=true;
    int i=0, j;
    while((i<TAILLE)&&(res)){
        if(g[l][i].valeur==val){
            res=false;
        }
        i++;
    }
    i=0;
    while((i<TAILLE)&&res) {
        if(g[i][c].valeur==val){
            res=false;
        }
        i++;
    }
    i=l-(l%N);
    j=c-(c%N);
    while((i<(l-(l%N)+N))&&res){
        while ((j<(c-(c%N)+N))&&res){
            if (g[i][j].valeur == val){
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
 * \fn void ajouterCandidat(tGrille g)
 * \brief ajoute un candidat à la liste des candidtas possible pour une case
 * \param laCase : une case de la grille
 * \param val : la valeur possible d'une case
 * Cette fonction sert à ajouter une valeur à la liste des valeurs candidates pour une case d'une grille 
*/
void ajouterCandidat(tCase2 *laCase, int val){
    if(!(laCase->candidats[val])){
        laCase->candidats[val]=true;
        laCase->nbCandidats++;
    }
}

/**
 * \fn void retirerCandidat(tCase2 *laCase, int val)
 * \brief retire un candidat à la liste des candidtas possible pour une case
 * \param laCase : une case de la grille
 * \param val : la valeur possible d'une case
 * Cette fonction sert à retirer une valeur de la liste des valeurs candidates pour une case d'une grille si cette valeur n'est plus candidate 
*/
void retirerCandidat(tCase2 *laCase, int val){
    if(laCase->candidats[val]){
        laCase->candidats[val]=false;
        laCase->nbCandidats--;
    }
}

/**
 * \fn bool estCandidat(tCase2 laCase, int val)
 * \brief vérifie si une valeur est candidate pour une case
 * \param laCase : une case de la grille
 * \param val : la valeur possible d'une case
 * Cette fonction vérifie si une valeur est candidate pour une case d'une grille 
*/
bool estCandidat(tCase2 laCase, int val){
    return laCase.candidats[val];
}

/**
 * \fn int nbCandidats(tCase2 laCase)
 * \brief renvoie le nombre de candidats d'une case
 * \param laCase : une case de la grille
 *Cette fonction retourne le nombre de candidats pour une case d'une grille 
*/
int nbCandidats(tCase2 laCase){
    int compteCandidat=0;
    for(int i=1; i<=TAILLE; i++){
        if(laCase.candidats[i]){
            compteCandidat++;
        }
    }
    return compteCandidat;
}

/**
 * \fn void innitialiserCandidats(tGrille g)
 * \brief initialise tous les candidats d'une grille à false
 * \param g : grille de sudoku qui sera afichée
 * Cette fonction initialise les candidats de toutes les cases d'une grille 
*/
void initialiserCandidats(tGrille g){
    for(int ligne=0; ligne<TAILLE; ligne++){
        for(int colonne=0; colonne<TAILLE; colonne++){
            for(int i=0; i<=TAILLE; i++){
                g[ligne][colonne].candidats[i]=false;
            }
            g[ligne][colonne].nbCandidats=0;
        }
    }
}

/**
 * \fn void afficherStats(char nomg[], int cr, int nbrCasesVides, int ce, int nbC)
 * \brief 
 * \param nomg : nom de la grille
 * \param cr : cases a remplir
 * \param nbrCasesVides : nombre de cases vides
 * \param ce : candidats elimines
 * \param nbC : nombre total de candidats
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
 * \fn void affecterCandidats(tGrille g)
 * \brief ajoute un candidat à la liste des candidtas possible pour une case
 * \param g : grille de sudoku qui sera afichée
*/
void affecterCandidats(tGrille g){
    for (int i = 0; i < TAILLE; ++i){
        for (int j = 0; j < TAILLE; ++j){
            for (int val = 1; val < (TAILLE+1); ++val){
                if (g[i][j].valeur == 0){/*verifie que valeur de case est vide*/
                    if (verifValPoss(g, g[i][j], val, i, j)){/*verifie si val est un candidat possible a cette case*/
                        ajouterCandidat(&g[i][j],val);
                    }
                }
            }
        }
    }
}

/**
 * \fn void afficherGrille(tGrille g)
 * \brief Affiche une grille dans le fromat demandé par le client
 * \param g : grille de sudoku qui sera afichée
 * 
 * Cette procédure réalise l’affichage à l’écran de la grille et de son contenu, 
 * conformément à l'exemple de l'annexe 2
*/
void afficherGrille(tGrille g){
    int i,j;
    printf("    1 2 3   4 5 6   7 8 9  \n");
    for (i = 0; i < TAILLE; i++){
        if (i%N==0){ /*si i est un mutiple de 3 afficher ligne*/
            printf("  +-------+-------+-------+\n");
        }
        printf("%d ",i+1);
        for (j = 0; j < TAILLE; j++){
            if(j%N==0){/*si j est un mutiple de 3 afficher ligne*/
                printf("| ");
            }
            if(g[i][j].valeur==0){/*si élément de la grille est égale à 0 afficher "."*/
                printf(". ");
            }
            else{/*sinon afficher élément de la grille*/
                printf("%d ",g[i][j].valeur);
            }
        }
        printf("|\n");
    }
    printf("  +-------+-------+-------+\n");
}