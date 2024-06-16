## <span style="color:yellow">Le pipe</span>

> le pipe "|" permet de démultiplier les commandes

## <span style="color:yellow">STDIN/STDOUT</span>

"<" permet d'éxécuter une commande qui est dans un fichier : STDIN

">" retouren le résultat dans un fichier : STDOUT

> ex : ls < fichier : lit la commande du fichier

> ls > fichier : écrit le résultat dans le fichier

• Seule la 1ère commande peut avoir une redirection entrante de la forme : <

• Seule la dernière commande peut avoir une redirection sortante de la forme : >

ex : cmd1 < source | cmd2 | cmd3 | cmd4 > resultat

## <span style="color:red">Le Filtre</span>

• Un filtre réduit un ensemble de données en un sous-ensemble suivant des critères indiqués

• Un tri ordonne un ensemble de données suivant des critères indiqués. La quantité de données reste la même en sortie.

## <span style="color:yellow">WC</span>

> wc -l : Compte les lignes (l = lines )

> wc -c : Compte les caractères (c = characters)

> wc -w : Compte les mots (w = words)

cat lang prod | wc -l : affiche le nombre de ligne des fichiers lang et prod

Q1. cat lang prod | wc -c : le nombre de caractère

Q2. cat lang prod | wc -w : le nombre de mot

## <span style="color:yellow">Sort</span>

> "sort -t':' -k 3 < prod" : tri en utilisant le caractère : comme
> séparateur de champ et en triant sur le 3 ème champ (la couleur)

Q3. sort -t':' -k 5 < prod

Q4. sort -t':' -k 5,1 < prod

La virgule permet de trier d'abords la colonne de la provenance puis celle du nom

Q5. sort -t':' -k 2 < prod

Q6. sort -u -t':' -k 5 < prod

Q7. uniq -c < depts

## <span style="color:yellow">Uniq</span>

> "uniq < fichier" permet d'éliminer les lignes qui se répète dans le fichier

/!\ ne marche seulement avec les fichier trier

L'extension -d permet d'afficher seulemnt les lignes en doublon

L'extension -c permet d'afficher devant les lignes le nombre de fois qu'elle est en double

## <span style="color:yellow">Colrm</span>

> "colrm" permet de supprimer des colonnes de caractères dans ce qui est produit en sortie

Q8. colrm 1 5 < depts

## <span style="color:yellow">Cut</span>

> <b>"cut"</b> permet de couper les champs qu’on souhaite conserver dans ce qui est produit en sortie.
> L'inverse de uniq

Q9. cut -d':' -f 1,3 < prod

Q10. cut -d':' -f 2 < depts

## <span style="color:yellow">Head</span>

> <b>"head"</b> permet de produire en sortie les lignes se trouvant en tête de la source donnée en entrée.

Q11. head -n 3 < lang | sort -t' ' -k 1

## <span style="color:yellow">Tail</span>

> <b>"tail"</b> est le pendant de head mais cette fois-ci elle concerne les lignes de la fin de la source de données

<b>tail -'nb'</b> Produit en sortie une extraction des nb lignes de la fin de la
source d’entrée

<b>tail -f</b> tourner la commande sans fin pour
qu’elle puisse afficher ensuite toute nouvelle ligne qui
apparaîtra, au fil du temps

Q12. head -6 < depts | tail -3

## <span style="color:yellow">Tr</span>

> <b>"tr"</b> permet de convertir des caractères de la source de données en d’autres caractères.

> <b>"tr -s a-z A-Z < prod"</b> permet de remplacer les minuscules en majuscules du fichier prod

Q13. tr -s [a-z] [A-Z] < lorem

<span style="color:red">SUITE</span>

Fichier prod

Q1.afficher les lignes convertie en majuscule

<span style="color:orange">sort -t':' -k 1 < prod </span>|<span style="color:yellow"> tr -s a-z A-Z </span>|<span style="color:orange"> cut -d':' -f 1,3,5</span>

Q2. <span style="color:orange">sort -t':' -k 1 < prod </span>|<span style="color:yellow"> cut -d':' -f 1,2</span>

Q3. <span style="color:yellow">sort -t':' -k 3 < prod </span>| <span style="color:orange">cut -d':' -f 3 </span>|<span style="color:yellow"> uniq -c</sapn>

Q4. tr -s ' ' < lang | uniq

Q5. tr -s ' ' < lang | uniq | sort -t' ' -k 2,2

Q6. tr -s ' ' < lang | cut -d' ' -f 2 | colrm 1 2 | sort -k 1

Q7.
