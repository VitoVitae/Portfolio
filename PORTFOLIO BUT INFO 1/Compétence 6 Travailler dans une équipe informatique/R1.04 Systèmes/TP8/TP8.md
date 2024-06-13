<style>
    b{
        color : lightgreen;
    }
    i {
        color : yellow;
    }
</style>

# R1.04 - Systèmes - TP8

## Scripting Bash

### Le bash

<b>Bash</b> est un langage, celui... du Bash, celui du shell. <b>Bash</b>, est un outil d’admistrateur. Les <b>programmes</b> qu’on écrit en bash s’appellent des <b>scripts</b>.

le <b>bsh</b>, <i>le Bourne shell</i> , du nom de son créateur, <i>Steve Bourne</i>. Bourne n’était pas barbu mais il avait fait barbu-2ème langue au Lycée.

### Variables

Une variable n’a <b>pas de type</b>, on y met ce qu’on veut. Pas besoin de déclaration.

    Une variable :
        + Doit commencer par une lettre ou un _
        + Peut contenir des lettres minuscules et majuscules, mais min et MAJ ne sont pas équivalentes.
        + Peut contenir des lettres chiffres
        + Peut contenir des _ (underscores)
        + Ne peut contenir aucun autre symbole

#### Affectation

<b>"nom=toto"</b> affecte toto à la variable nom

Pour lire une variable, on préfixe son nom d’un $ :

<b>"echo $nom"</b>

#### Concaténations

L’espace entre les deux variables est respecté à l’affchage.

>nom=peuplu

>prenom=jean

<b>"echo Nom:$nom"</b>

    Nom : peuplu

<b>"echo ${prenom}Neymar"</b>

    jeanNeymar

#### Guillemets et Apostrophes

" ", écrit le contenau des variable

' ', écrit le contenant des variables

"$nom", écrit peuplu

'$nom', écrit $nom

Q1. écrire 12$US avec la variable prix=12

    echo $prix'$US'

Ainsi pour afficher "" ou '' utiliser un <b>\ </b>

### Fichier script

<b>"chmod +x script1"</b> mettre le droit d'éxecuter sur le fichier script1

<b>"./script1"</b> pour exécuter

### Sortie

#### STDOUT

comme un printf
> echo "C'est fin, ca se mange sans fin"

#### STDERR

comme le <b>fprintf(stderr, ...)</b> en C

<b>&2 echo "Erreur"</b>

### Entrée - STDIN

<b>"read nom_variable"</b> commande comme dans le bash

<b>"echo -n"</b> Comme printf

<b>read prenom</b> Comme un scanf

### Paramètre

<b>"./script4 James Bond 007"</b> éxecute le fichier script4 puis entre en paramètre James, Bond et 007.

Q2. La variable <b>$0</b> contient /usr/bin/bash. C'est le nom du fichier que l'on éxecute

### Structure de contrôle

#### Tests

<b>"read -p"</b> est comme un input

<i>read -p "texte" variable</i>

On peut éxecuter des test avec <b>test</b> ou <b>[ ]</b>

La synthaxe avec est toujours :

    if test "$nom" = ""
    then
    ...
    else
    ...
    fi

+ <b>=</b> : pour <i>l’égalité</i> de <b>chaînes de caractères</b> (et non <b>pas ==</b> !!!)

+ <b>!=</b> : pour la <i>différence</i> de <b>chaînes de caractères</b>

+ <b>-eq</b> : pour <i>l’égalité</i> de <b>valeurs numériques</b>

+ <b>-ne</b> : pour la <i>différence</i> de <b>valeurs numériques</b>

+ <b>-gt</b>, <b>-ge</b>, <b>-lt</b> et <b>-le</b> : pour respectivement : <b>></b>, <b>≥</b>, <b><</b> et <b>≤</b> de <b>valeurs numériques</b>

#### test vs affection

+ <b>Affectation</b> de variable : <b>pas d’espace</b> devant ni derrière le =
+ <b>Test</b> de valeur : <b>un espace</b> devant et un espace derrière le =

### Boucle

La syntaxe de for ... in est toujours :

    for variable in liste_de_valeurs ...
    do
        ...
    done

Le joker <b>*</b> qui signifie
n’importe quel fichier

On pourrait tout aussi bien écrire ceci :

for fic in ../*

ou encore

for fic in ~/Documents/algo/TP3/*.c

### Redirection

Q4. <b>"$(wc -l < $0)"</b> S permet d'écrire une commande.Puis compte le nombre de ligne du fichier éxecuter

Q5. script10

Q6. script11

Q7. script12

Q8. script13
 
Q9. script14

Q10. script15

Q11. script16

