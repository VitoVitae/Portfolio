# TP6

## Regex & Grep

Une Regex s’appelle aussi un motif ou pattern en anglais.

> Regex : grep (Globally search Regular Expression and Print)

    egrep : une version amélioré de grep

## La commande egrep

<b>egrep</b> recherche la présence d’un motif dans une source de données texte.

Différente façon d'utiliser <b>egrep</b>

> egrep motif fichier_de_données

> egrep motif < fichier_de_données

> une_commande ... | egrep motif

> une_commande ... | egrep motif | une_autre_commande ...

Les extensions :

> -i : ne fait pas de différence entre minuscules et majuscules

> -l : n’affiche pas les lignes qui matchent mais affiche juste les noms des fichiers dans lesquels egrep a trouvé au moins une ligne qui matche le motif

> -v : inversion/négation du match. Affiche les lignes qui ne matchent pas

> -c : affiche simplement le nombre de lignes qui ont matché le motif

"egrep machine < lang" permet d'afficher toute les lignes du fichier lang qui possède le terme machine

- Q1. <b>"egrep blanche < prod"</b> permet d'afficher les lignes deprod contenant blanche

- Q2. <b>"egrep blan < prod"</b> renvoie le même résultat mais est un peu moins précis.

- Q3. <b>"egrep lan < ../TP5/prod"</b> affiche les lignes des pas précis. Elle affiche des lignes qui ne correspondent à un fruit et à un pays

"alias egrep='egrep --color'" Permet de mettre en évidence le motif. avant l'exécution d'une commande grep

- Q4. <b>"egrep [7-9] < prod"</b> affiche les lignes possédant 7,8 et/ou 9

- Q5. <b>"egrep -v [7-9] < prod"</b> affiche les lignes ne possédant pas les chiffres 7, 8 et 9.

- Q6. <b>"egrep -i [aeiouy] < prod"</b> affiche les lignes qui contient une voyelle

- Q7. <b>"egrep -i [aeiouy][aeiouy] < prod"</b> affiche les lignes avec des voyelles consécutifs

- Q8. <b>"egrep -vi [aeiouy][aeiouy] < prod"</b> affiche les lignes dont les mots ne possèdent pas de voyelles consécutifs

- Q9. <b>"egrep [-AY] < ../TP5/depts"</b> affiche les lignes qui possède A,- ou Y

### Caractère quelconque

Avec Regex, le '?' ne fonctionne pas, il faut utilisé <b>'.'</b>

ex : egrep :.: < prod

- Q10. <b>"egrep 9...C < ../TP5/depts"</b> affiche les lignes qui contiennent 9 suivit de 3 caractères puis C

- Q11. <b>"egrep a..e < murphy"</b>

- Q12. <b>"egrep -i [.][.][.] < murphy"</b> affiche les lignes qui contient ...

- Q13. <b>"egrep "machine virtuelle" < ../TP5/lang"</b> affiche les lignes qui contiennent machine virtuelle

### Quantificateurs

Quantifier signifie indiquer quel nombre de fois le truc qui précède le quantificateur peut apparaître.

"egrep A[0-9]*B < quant" signifie un A, suivi d’une quantité quelconque (y compris nulle) de chiffres, suivie d’un B.

- Q14. <b>"egrep b[a-z]*e < prod"</b> affiche un b suivi d’un nombre quelconque de
  minuscules, suivi d’un e.

- Q15. <b>"egrep b[a-z]*e: < prod"</b> même chose mais il y a ':' après le 'e'.

Le caractère + est le quantificateur qui signifie une fois ou plus le truc qui est avant le +

Exemple : egrep A[0-9]+B < quant

> signifie un A, suivi d’une quantité quelconque (non nulle) de chiffres, suivie d’un B

- Q17. <b>"egrep [aeiouy]l+e < ../TP5/depts"</b>

### Zéro ou une fois

Le caractère <b>?</b> est un quantificateur, qui signifie <b>la présence de zéro ou une fois le truc qui est avant le ?</b>
On peut aussi dire : le truc avant le ? peut être présent mais ce n’est pas une obligation

exemple : <b>egrep AB?C < quant</b>

- Q18. <b>egrep 97?0 < lang</b> affiche les lignes qui contiennent un 9 suivi éventuellement d’un 7 et suivi d’un 0

- Q19. <b>egrep t" "?, < murphy</b> affiche les lignes qui finissent par t puis un éventuel espace

### Exactement X fois

L’expression <b>{X}</b> est un quantificateur qui signifie la présence d’exactement X fois le truc qui est avant.

Exemple : egrep AB{3}C < quant

- Q20. <b>egrep r{2}i < ../TP5/depts</b> affiche les lignes qui contiennent exactement 2 r consécutifs, suivis d’un i.

- Q21 <b>egrep n{2}e < ../TP5/depts</b> affiche les lignes qui contiennent exactement 2 n consécutifs, suivis d’un e.

### Entre X et Y fois

L’expression <b>{X,Y}</b> est un quantificateur qui signifie <b>la présence de X à Y fois le truc qui est avant</b>.

Exemple : egrep AB{2,3}C < quant

#### Positionneurs

### Début

Pour indiquer que le motif est attendu en début de ligne, on utilise le ^(circonflex )

Exemple : egrep ^A < quant

signifie un A en début de ligne.

- Q22 <b>egrep ^L < murphy </b> affiche les lignes qui commencent par un L majuscule

#### Fin

Pour indiquer que le motif est attendu en fin de ligne, on utilise le <b>$</b> (dollar)

Exemple : egrep A$ < quant

signifie un A en fin de ligne.

- Q23 <b>egrep [.]$ < murphy</b> affiche les lignes qui se terminent par un .

<b>egrep [^A-Z] < prod</b> signifie qu’on souhaite le complément de [A-Z], c'est-à-dire tout sauf [A-Z]

- Q24 <b>egrep [^a-zA-Z0-9" ":]< depts</b> Affichez les lignes de depts qui contiennent autre chose que des minuscules, des majuscules, des chiffres, des espaces et des :

### Groupage

En utilisant des () (parenthèses), on peut opérer un groupage qui permet de résoudre
ce problème : <b>egrep (AB){2} < quant</b> Cette fois-ci on cherche la présence de AB deux fois consécutives.

- Q25 <b>egrep (AB)\* < prod</b>

On peut imbriquer des groupes dans des groupes, de cette façon : <b>egrep (A{3}(XY)+){2} < quant</b>

### Répétition d’un groupe

> egrep ([A-Z]{2})\1\1 < quant

Si plusieurs groupes sont imbriqués, la valeur de X dans un \X est donnée en comptant le numéro de la parenthèse ouvrante du groupe visé. 

Exemple :

egrep (A{3}(XY)+)\2\1 < quant

- Q26 <b>egrep (.{2})\1 < prod</b>

### <span style="color:red">Alternatives</span>

> ? permet de représenter une alternative

le truc qui précède peut être présent ou absent. 

egrep '7[0-9]| m' < lang

permet d’afficher les lignes de lang qui contiennent soit un 7 suivi d’un chiffre
quelconque, soit un espace suivi d’un m.

- Q27 <b>wc -l | egrep '^[ck]|c+e$' < ../TP5/prod</b>