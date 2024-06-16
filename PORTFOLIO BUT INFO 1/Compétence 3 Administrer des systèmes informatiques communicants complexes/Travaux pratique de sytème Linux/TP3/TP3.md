Q1 - La commande "which ls" affiche le chemin d'ou se situe la commande ls "/user/bin/ls"

Q2 - la commande "which abcd" n'affiche rien car la commande n'existe pas
	la commande "which cd" n'affiche rien pourtant la commande existe (elle sert à se déplacer)

Q3 - La commande "ps" indique la liste de processus de la session ouverte
	"ps -edf" est la commande qui affiche tout les processus

Q4 - "155403" et "155421" sont des processus lancer par l'utilisateur

Q5 - Le PPID du processus de la commande "ps" est 155421 

Q6 - Le PID de l'application Geany est 165929

Q7 - Le processus geany à deux sous-processus (bash et 2*[{geany}])

Q8 - Ce qui permet d'identifier un processus est son PID

"kill -<signal> <PID>" permet de tuer un processus donc de l'arrêter
"kill -L" permet d'afficher tout les signals

Q9 - En utilisant ls, on n'obtient pas un ls du fichier courant	

Q10 - avec le & on obtient un ls du fichier courant

Q11 - avec le ctrl+c avec ./tictac & on ne peut pas arrêter le processus
