<style>
    body {
        color : black;
        background-color : white;
    }
    h1{
        color : white;
        background-color : red;
    }
    h2{
        color : white;
        background-color : blue;
    }
    h3{
        color : white;
        background-color : green;
    }
    h4{
        color : white;
        background-color : orange;
    }     
</style>
# R1.04 - Système

## TP9 - Scripting PHP

### Manipuler le fichier

Balise d'un fichier php :

    #!/usr/bin/php
    <?php
        
    ?>

afficher un message :

    echo "message\n"

exécuter un fichier :

    php nomFichier

augmente les propriétés éxécutable du fichier

    chmod +x hello.php


execute le fichier

    ./hello.php

lancer un php avec un shell interactif : php -a

### type de donnée

- entier : 123
- flottant : 12.5
- chaines de caractère : "bon" ou 'nob'
- booléens : true
- Tableau : int vals[N];

### variable :

#### affectation :

    $variable = valeur;

#### lecture

    echo $var;
    echo "ABC" . $variable_inconnue . "DEF"

"." : une concaténation

### Opérateur

+ +
+ -
+ *
+ /
+ %(reste)
+ **(exposant)
+ ++$val
+ $val--
+ &&
+ ||
+ !

### Opérateur avec réaffectation

+ +=
+ -=
+ *=
+ /=
+ %=
+ .= (concaténation)

### Structure de contrôle

#### SI/SINON

    if (condition) {
        ...
    } else if (condition) {
        ...
    } else {
        ...
    }

#### FOR

    for ($boucle = 1; $boucle < 10; $boucle++) {
        echo $boucle . "\n";
    }

#### While

    while (condition) {
        ...
    }
    do {
        ...
    } while (condition);

### Comparaison

+ == 
+ != 
+ <=
+ ㅤ>= 
+ < 
+ ㅤ>

### Mixage des types

    if ((4 * 3) == "12") {
        echo "OK";
    }

    if ((4 * 3) == "00012ABC") {
        echo "OK";
    }

echo 10 * "1e2"; // Affiche 1000
echo 2 + "+1e-2"; // Affiche 2.01
echo 5 / ".1"; // Affiche 50

car 1e2 est une écriture de 100 en notation scientifique, +1e-2 est une écriture de 0.01 et .1 est une écriture de 0.1

    if ("" == false) {
        echo "OK";
    }

    if (0 == "") {
        echo "OK";
    }

    "0" == 0
    "" == 0
    "0" != ""

égalité stricte : ===

différence stricte : !==

### Tableau

#### Déclaration

    $tablo = array();
    $tablo2 = [];

#### Affectation

L’association de la clé et de sa valeur se fait par une flèche =>

    $depts = [
        22 => "Côtes d’Armor",
        29 => "Finistère",
        35 => "Ille-et-Vilaine",
        56 => "Morbihan",
    ];

print_r(tableau)

Les clés d’un tableau sont uniques

### Parcour

    foreach ($depts as $num => $nom) {
        echo "Le département " . $num . " s’appelle " . $nom . "\n";
    }

### Fichier

Charger le ficher

    file("nom_fichier");

    fopen()  // ouvrir
    fclose() // fermer
    fread()  // lire
    fwrite() // écrire
    feof()   // end of File 
    // déterminer si la position courante est en fin de fichier (de flux) ou non. 
    file_put_contents()
    file_get_contents()
    implode(sep,tab)

### Fonction interne

longueur d'une chaîne de caracter

    strlen(...);

supprimer tous les \n ou \r

    rtrim(...)
    
découper une chaîne de caractères sur un séparateur donnée et retourne un tableau

    explode()

permettent de connaître la taille d’un tableau

    count()
    sizeof()

permet d’arrondir une valeur flottante

    round() 

lire au clavier

    read()

lit tout ce qui arrive sur son STDIN, jusqu’à ce qu’il n’y ait plus rien, et pour chaque ligne lue, il affiche chaque mot de la ligne avec une majuscule en premier et des minuscules sur les autres lettres

     ucwords()