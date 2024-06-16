# TP4 - fichier de redirection

Q1/ la command "ls -l > mes_fichiers" permet de faire la commande ls -l et d'afficher le résultat dans un nouveau fichier nommé mes_fichiers

Q2/ la commande "ls -l nom_fichier > autre_fichier" permet d'inscrire dans le fichier autre_fichier les résultats de ls -l sur le fichier nom_fichier

Q3/ le rajout de 2 avant > "2>" ne redirige pas STDOUT mais STDERR. Donc cela va écrire un fichier mais vide et écrire le résultat dans le terminal

Q4/Dans le fichier errors, on nous renvoie le STDERR et dans le fichier list_user, on nous renvoie le STDOUT

Q5/ en inversant > list_users  et 2> errors, les commandes retourne la même chose

Q6/ avec > nom_fichier 2>&1, il renvoie les résultats de STDOUT et STDERR dans le fichier, il affiche le même résultat que la commande innitiale mais dans un fichier et non dans le terminal

Voici comment il faut comprendre la syntaxe : > nom_fic 2>&1
    Chaque partie est à prendre séquentiellement de gauche à droite
        ● Le > doit se lire ainsi :
            Envoie le canal 1 (STDOUT)
            vers ... et ce qui suit donne la
            destination : ici il s’agit d’un fichier nommé nom_fic
        ● Le 2> doit se lire ainsi :
            Envoie le canal 2 (STDERR)
            vers ... et ce qui suit donne la
            destination : ici il s’agit de &1, une façon de dire qu’il s’agit du même canal que le
            n°1. Dans notre exemple, le canal 1 (STDOUT) vient juste d’être redirigé vers le
            fichier nom_fic, il en sera donc de même pour le canal 2 (STDERR)

Q7/ si on inverse, "> et 2>&1" cela ne marchera pas comme il faut car
        dans un permier temps, il dirige vers le canal 2 et vers le canal 1 déjà existant sauf qu'il n'est pas encore existant vu qu'il est définit après 

Attention à ne pas confondre le sens des < et >. Un > créera ou écrasera le fichier, un < lira dans le fichier, qui doit donc exister.

Q8/ Pour pouvoir executer la commande "./moy < fichier.txt", il faut remplir le fichier de valeur pour qu'il l'execute et puisse répondre au besoin des scanf.
    il faut afficher les valeurs les unes en dessous des autres

Ainsi on peut tout fusionner "./moy < vals.txt > result 2> errors"

"seq 1 x 100" permet d'afficher la suite des chiffres entre 1 et 1000, x est un chiffre qui définit un pas entre les nombres
"wc -l" compte le nombre de ligne 
par exemple : "seq 1 17 100 | wc -l", il compte le nombre de ligne que fait la commande "seq 1 17 100"

less < val.txt et less val.txt font la même chose

Le | permet de faire deux fonction en même temps