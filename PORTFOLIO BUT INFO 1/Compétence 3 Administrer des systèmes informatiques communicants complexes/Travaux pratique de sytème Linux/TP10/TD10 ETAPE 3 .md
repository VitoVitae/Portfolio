## Binôme

ls -ld

### 1

ls ../rbardini

il faut avoir x et r pour groupe ou other (selon si sa beuge)

### 2

enlève r pour milou

### 3

on enlève le r du dossier

il est possible d'afficher sans connaitre le nom du fichier en utilisant les jokers

### 4

on joue avec le w

### 5

need r rights

### 6

il faut avoir le w du dossier et le r du fichier

### 7

il faut avoir la permisson w du dossier

### 8

non car pour empeicher une suppression il faut elever le droit de lecture et donc sela fait qu'aucun fichier ne peut être suppimé

solution:

faire un sous dossier pour les modifiables, ou on peut modifier ou supprimer le contenu

### 9

il faut donner les droits w et x


## ETAPE 4

### a

projet : r

### b

actuels : w

doc.txt : r

### c

actuels : x

projet1 : x

### d

actuels : r et x

projet : r

### e

actuels : x

projet : r

### f

actuels : w et x

### g

anciens : w et x

lisezmoi.txt : rien

actuels : w et x

### h

anciens : w et x

projet1 : r et w

actuels : w et x

### i

actuels : r

doc.txt : w

### j

projets : w

p2.c : r

---


### 1

- U-rwx : Ben
- G-r-x : tech
- O-r-x 

### 2

- U-rwx : Ada
- G-r-x : biz
- O----

### 3

- U--wx : Carl
- G-r-x : tech
- O-r-x

### 4

- U-rwx : Carl
- G-rwx : tech
- O---x


## Sticky bit

drwxrwsrwx 6 clsimon INFO-Enseignants 8192  8 déc.  14:26 /FILER/anonymous/SYS2017/tmps

/FILER/ano*/SYS2017/tmps a un s dans les droits du groupe

oui on peut supprimer les fichiers des autres

s est le Droit SUID. Ce droit s'applique aux fichiers exécutables, il permet d'allouer temporairement à un utilisateur les droits du propriétaire du fichier, durant son exécution.