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