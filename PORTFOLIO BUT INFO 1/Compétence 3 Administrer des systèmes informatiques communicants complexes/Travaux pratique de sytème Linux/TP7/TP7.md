# TP7

## Synthèse sur les filtres

 egrep --color : pour mettre en avant le motif

L'ensemble des questions traitent du fichier <b>access.log</b> 

 - Q1. Comptez les (3607) lignes du 24 décembre 2020.

> <b>egrep --color 24/Dec/2020 < access.log | wc -l</b>

---

- Q2. Comptez les (67) lignes du 24 décembre 2020 de l’intervalle horaire [18:00 , 19:00[.

> <b>egrep --color 24/Dec/2020:18 < access.log | wc -l</b>

---

- Q3. Comptez les (875) lignes de l’intervalle horaire [18:00 , 19:00[, quelle que soit la date.

> <b>egrep --color 2020:18 < access.log | wc -l</b>

---

- Q4. Comptez les (436) lignes de l’intervalle horaire [18:00 , 18:30[, quelle que soit la date.

> <b>egrep --color 2020:18:[0-2] < access.log | wc -l</b>

---

- Q5. Comptez les (384) lignes de l’intervalle horaire [09:00:00 , 09:30:00], quelle que soit la date

> <b>egrep --color "(09:[0-2]|09:30:00)" < access.log | wc -l</b>

---

- Q6. Affichez la liste des (7) dates uniques (Jour, Mois, Année) présents dans le fichier. N’affichez aucune autre information que les dates.

> <b>cut -d' ' -f 4 < access.log | cut -d':' -f 1 | colrm 1 1</b>

---

- Q7. Affichez la liste des (7) dates uniques (Jour, Mois, Année) avec le nombre de requêtes pour chaque jour, triés par nombre de requêtes décroissant.

> <b>cut -d' ' -f 4 < access.log | cut -d':' -f 1 | colrm 1 1 | uniq -c</b>

---

- Q8. Affichez l’adresse IP ayant fait le plus de requêtes. N’affichez que l’IP (45.144.0.179) et le nombre de requêtes faites (946).

> <b>cut -d' ' -f 1 < access.log | egrep 45[.]144[.]0[.]179 | uniq -c</b>

---

- Q9. Affichez les (2) lignes dont les adresses IP ont le même nombre en 1ère et 3ème positions (999.999.999.999).

> <b>egrep ^"([0-9]+)\.([0-9]+)\.\1\." < access.log | wc -l</b>

---

- Q10. Comptez les (18581) requêtes ayant abouti à un code 200.

> <b>cut -d' ' -f 9 < access.log | egrep 200 |wc -l</b>

---

- Q11. Affichez la liste des (4) codes des requêtes ayant abouti à un code autre que 200, et comptez le nombre de requêtes pour chaque code (somme totale = 1419).

> <b>cut -d' ' -f 9 < access.log | egrep -v 200 | wc -l</b>

---

- Q12. Affichez les (3) lignes des requêtes qui ont été faites à un moment où Heures, Minutes et Secondes était un nombre identique (ex : 12:12:12).

> <b></b>

---

- Q13. Affichez les (7) lignes des requêtes qui ne sont ni GET ni POST. Quelle est la taille des réponses ? Allez voir le lien, donné précédemment, concernant le protocole HTTP. Comprenez-vous pourquoi les tailles sont ainsi dans les réponses ? Demandez de l’aide à votre enseignant.e si besoin.

> <b>cut -d' ' -f6 < access.log | colrm 1 1 | egrep --color -v '(GET)|(POST)' | wc -l</b>

---

- Q14. Affichez les (18) lignes des requêtes faites par des personnes clairement identifiées.

> <b>cut -d' ' -f3 < access.log | egrep --color -v '-' | wc -l</b>

---

- Q15. Pour chacune des ces (18) personnes clairement identifiées, affichez ces informations (et uniquement celles-là), une par ligne, séparées par des espaces et triées par taille de ressource :
    Nom de la personne
    Méthode de la requête
    Ressource demandée (URL)
    Taille de la ressource renvoyée

> <b></b>

---

- Q99. Calculez la taille totale (487775629 octets) des réponses aux requêtes ayant abouti àun code 200. Ce problème n’est pas évident et vous aurez besoin d’utiliser la commandebc (basic calculator). C’est aussi un filtre. Voici un exemple : echo '1+2+3' | bc. Vous aurez aussi, sans doute, besoin d’un petit coup de pouce de votre enseignant.e !

Bonus : modifiez votre commande pour exprimer le résultat en Mo. (465)

> <b></b>

