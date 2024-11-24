# TP

## Le service Web avec le serveur Apache

Dossier de partage VM : /mnt/hgfs/partageSAE/

### 2

`systemctl status apache2`

```text
...
     Active: active (running) since Tue 2024-05-14 11:03:23 CEST; 8min ago
...
    Process: 539 ExecStart=/usr/sbin/apachectl start (code=exited, status=0/SUCCESS)
    Process: 967 ExecReload=/usr/sbin/apachectl graceful (code=exited, status=0/SUCCESS)
   Main PID: 657 (apache2)
      Tasks: 6 (limit: 2285)
     Memory: 18.6M
        CPU: 336ms
...
```

### 3

DocumentRoot : définit le répertoire à partir duquel Apache va servir les fichiers comme les pages HTML et images.

Se trouve dans `/etc/apache2/sites-enabled/*.conf`.

Valeur dans `/etc/apache2/sites-enabled/000-default.conf` : `/var/www/html`

### 4

`type -a apache2` : `/usr/sbin/apache2`, `/sbin/apache2`

### 5

`apache2 -v`

```text
Server version: Apache/2.4.53 (Debian)
Server built:   2022-03-14T16:28:35
```

### 6

`apache2 -l`

```text
  core.c
  mod_so.c
  mod_watchdog.c
  http_core.c
  mod_log_config.c
  mod_logio.c
  mod_version.c
  mod_unixd.c
```

### 7

mod_log_config : Ce module apporte une grande souplesse dans la journalisation des requêtes des clients. Les journaux sont écrits sous un format personnalisable, et peuvent être enregistrés directement dans un fichier, ou redirigés vers un programme externe. La journalisation conditionnelle est supportée, si bien que des requêtes individuelles peuvent être incluses ou exclues des journaux en fonction de leur caractéristiques.

### 8

`apache2 -M`

```text
```

### 9

`apache2 -version`

Il n'y a pas de différence avec `apache2 -v`

Mais il peut y avoir un erreur (friendly warning) si il y a un problème dans le fichier de configuration

### Création d'une partie administration

Index.html&nbsp;:

```html

```

`source /var/apache2/envvars` pour initialiser les variables d'environnement en cas d'erreur de syntax du fichier de configuration.

#### Mise en place de l'authentification administrateur

`htpasswd -c /etc/apache2/pass testeur`

Puis ajouter dans le fichier de configuration du site (000-default.conf) :

```text
<Directory "/var/www/html/secret">
    AuthType Basic
    AuthName "Veuillez saisir votre mot de login/passe"
    AuthUserFile "/etc/apache2/pass"
    Require valid-user
</Directory>
```

Recharget pour appliquer la nouvelle configuration :

`service apache2 reload`

## Le module PHP

### 1

### 2

Il est recommandé de créer un dossier secret pour sécuriser le site. En effet si un utilisateur lambda peut voir les informations à caractère sensibles données par `phpinfo`, cela rend le site vulnérable.

### 3

`http://127.0.0.1/secret/phpinfo.php`

### 4

Oui car le PHP a fonctionné.

### 5

1. On voit que le module `php7.4` est présent dnas le dossier `mods-enabled`
2. TODO
3. TODO Ce n'est pas un fichier classique, c'est un lien symbolique.

### 6

\#|question|réponse
-|-|-
i.|La version exacte du module PHP utilisé par notre serveur Web|7.4.28
ii| Le dossier de configuration du module PHP utilisé par notre serveur Web|/etc/php/7.4/apache2
ii|. Le fichier de configuration de php pour le serveur Web |/etc/php/7.4/apache2/php.ini
b.|La valeur de l’étiquette appelée « short_open_tag » |Off
c.|À votre avis, dans quel fichier de configuration (chemin exacte) peut-on modifier la valeur de cette étiquette « short_open_tag » ? |/etc/php/7.4/apache2/php.ini
d.|Si on devrait modifier la valeur de cette étiquette dans un fichier de configuration, faut-il recharger/relancer le serveur Web pour que la nouvelle valeur soit prise en compte ?|Oui il faut faire un `service apache2 reload`

### 7

`whereis php` : `/usr/bin/php`

### 8

`a2dismod php7.4`

Le module php est désormais désactivé.

### 9

Oui

### 10

Le PHP ne fonctionne plus.

Il y a une vulnérabilité car les balises PHP ne sont plus substituées. L'utilisateur peut donc les voir dans la page finale.

Accès URL : on a une page vide qui contient le code PHP

Dossier propre à Apache? TODO (voir dans dossier config apache2 que le module n'est pas activé, voir dossier)

### 11

`a2enmod php7.4` puis rechargement du serveur.

Accès URL : ça marche correctement

Dossier propre à Apache? TODO (voir dans dossier "config" apache2 que le module est activé)

### 12

mapage.html&nbsp;:

```html
<?php echo "coucou, je suis une code php dans une page HTML ?>
```

### 13

Non

### 14

Dans le viewsource, on peut voir la balise PHP.

En effet, comme *mapage* a pour extension HTML et non PHP, elle n'est pas reconnue par le module PHP, et donc elle n'est pas exécutée.

### 15

Le fichier de configuration à modifier est

`/etc/apache2/mods-enabled/php7.4.conf`

C'est cette section qui nous intéresse&nbsp;:

```text
<FilesMatch ".+\.ph(ar|p|tml)$"> 
    SetHandler application/x-httpd-php 
</FilesMatch>
```

Il faut modifier l'expression régulière pour matcher les fichiers `*.html`

`.+\.(phar|php|p?html)`

### 16

On remarque que le PHP n'est pas exécuté (donc un document vide est affiché) et peut voit le code PHP dans le View Source.

### 17

Le fichier de configuration à modifier est

`/etc/apache2/mods-enabled/php7.4.conf`

C'est cette section qui nous intéresse&nbsp;:

```text
<FilesMatch ".+\.ph(ar|p|tml)$"> 
    SetHandler application/x-httpd-php 
</FilesMatch>
```

Il faut modifier l'expression régulière pour matcher les fichiers sans extension : `".+(.phar|.php|.p?html|)$"`

### 18

#### a

#### b

On ne remarque rien de particulier

#### c

Il faut que le paramètre `short_open_tag` soit activé pour que la syntaxe raccourcie soit reconnue.

## MySQL & PHP

### 1

`mysql_secure_installation`

On nous demande si on veut installer le module d'évaluation de mot de passe : NON

On nous demande si on veut changer le mot de passe *root* : NON

On nous demande si on veut supprimer les utilisateur anonymes : OUI car pour tester on peut se connecter en root donc on n'en a pas besoin. Cela permet de restreindre l'accès à la base et d'améliorer la sécurité

On nous demande si on veut interdire les connexsion en root à distance : OUI car on a pas besoin d'être root à distance et cela améliore la sécurité.

On nous demande si on veut supprimer la BDD de test auto-générée : NON car on peut l'enlever plus tard de toute façon, et comme ça quelquechose s'affichera lors du SHOW DATABASES qu'on fera bientôt

On nous demmande si on veut recharger la table des privillièges : OUI car cela permettra au changements d'être appliqués immédiatemenent

### 2

D'abord on se connecte à la CLI de MySql:

`mysql --user=root --password=lannion`

Ensuite la commande `status` permet d'obtenir des informations :

`mysql> status`

```text
mysql  Ver 8.0.29 for Linux on x86_64 (MySQL Community Server - GPL)

Connection id:  17
Current database: 
Current user:  root@localhost
SSL:   Not in use
Current pager:  stdout
Using outfile:  ''
Using delimiter: ;
Server version:  8.0.29 MySQL Community Server - GPL
Protocol version: 10
Connection:  Localhost via UNIX socket
Server characterset: utf8mb4
Db     characterset: utf8mb4
Client characterset: utf8mb4
Conn.  characterset: utf8mb4
UNIX socket:  /var/run/mysqld/mysqld.sock
Binary data as:  Hexadecimal
Uptime:   27 min 55 sec

Threads: 2  Questions: 11  Slow queries: 0  Opens: 130  Flush tables: 3  Open tables: 49  Queries per second avg: 0.006
```

### 3

`mysql -V`

```text
8.0.29
```

### 4

D'abord on se connecte à la CLI de MySql:

`mysql --user=root --password=lannion`

### 5

```text
mysql> SHOW DATABASES

+--------------------+
| Database           |
+--------------------+
| information_schema |
| mysql              |
| performance_schema |
| sys                |
+--------------------+
```

### 6

#### a

```text
<?php 
    $sql="SHOW DATABASES"; 
    $link = mysqli_connect('127.0.0.1', 'root', 'lannion') or die ('Error connecting to mysql: ' . mysqli_error($link).'\r\n'); 
    
    if (!($result=mysqli_query($link,$sql))) { 
            printf("Error: %s\n", mysqli_error($link)); 
    } 
    
    while( $row = mysqli_fetch_row( $result ) ){ 
            if (($row[0]!="information_schema") && ($row[0]!="mysql")) { 
                echo $row[0]."<br/>\r\n"; 
            } 
    } 
?>
```

#### b

il faut installer le package php7.4-mysql et sa dépendance pour faire fonctionner le code php

#### c

```text
root@SAE:/root# dpkg -i /usr/local/src/*
(Reading database ... 110643 files and directories currently installed.)
Preparing to unpack .../src/php-mysql_7.4+76_all.deb ...
Unpacking php-mysql (2:7.4+76) over (2:7.4+76) ...
Selecting previously unselected package php7.4-mysql.
Preparing to unpack .../php7.4-mysql_7.4.28-1+deb11u1_amd64.deb ...
Unpacking php7.4-mysql (7.4.28-1+deb11u1) ...
Setting up php7.4-mysql (7.4.28-1+deb11u1) ...

Creating config file /etc/php/7.4/mods-available/mysqlnd.ini with new version

Creating config file /etc/php/7.4/mods-available/mysqli.ini with new version

Creating config file /etc/php/7.4/mods-available/pdo_mysql.ini with new version
Setting up php-mysql (2:7.4+76) ...
Processing triggers for libapache2-mod-php7.4 (7.4.28-1+deb11u1) ...
Processing triggers for php7.4-cli (7.4.28-1+deb11u1) ...
```

### 7

```text
mysql> create database paolo;

mysql> show databases;
+--------------------+
| Database           |
+--------------------+
| information_schema |
| mysql              |
| paolo              |
| performance_schema |
| sys                |
+--------------------+
```

### 8

```text
connect paolo;

mysql> create table etudiants (
    -> id int primary key,
    -> nom text not null,
    -> date_naissance date not null,
    -> classement int not null);
Query OK, 0 rows affected (0.06 sec)


mysql> show tables;
+-----------------+
| Tables_in_paolo |
+-----------------+
| etudiants       |
+-----------------+
1 row in set (0.00 sec)

mysql> insert into etudiants(id, nom, date_naissance, classement) values (0, 'Toe Paolo', '2005-02-27', 4) (1, 'Raphael Bardini', '2006-04-28', 4), (2, 'Kervadec Matto', '2005-12-12', '18');

mysql> select * from etudiants;
+----+-----------------+----------------+------------+
| id | nom             | date_naissance | classement |
+----+-----------------+----------------+------------+
|  0 | Toe Paolo       | 2005-02-27     |          4 |
|  1 | Raphael Bardini | 2006-04-28     |          4 |
|  2 | Kervadec Matto  | 2005-12-12     |         18 |
+----+-----------------+----------------+------------+
3 rows in set (0.00 sec)
```

### 9

```text
mysql> delete from etudiants where id=0;
Query OK, 1 row affected (0.00 sec)

mysql> select * from etudiants;
+----+-----------------+----------------+------------+
| id | nom             | date_naissance | classement |
+----+-----------------+----------------+------------+
|  1 | Raphael Bardini | 2006-04-28     |          4 |
|  2 | Kervadec Matto  | 2005-12-12     |         18 |
+----+-----------------+----------------+------------+
2 rows in set (0.00 sec)

```

### 10

```text
mysql> update etudiants set date_naissance='1990-01-01' where id=(select min(e.id) from (select * from etudiants) as e);
Query OK, 1 row affected (0.01 sec)
Rows matched: 1  Changed: 1  Warnings: 0
```

### 11

Script php :

```php
$sql = "create database paolo;";

$sql = "show databases;";

$sql = "connect paolo;";

$sql = "create table etudiants (
    id int primary key,
    nom text not null,
    date_naissance date not null,
    classement int not null);";

$sql = "show tables;";

$sql = "insert into etudiants(id, nom, date_naissance, classement) values (0, 'Toe Paolo', '2005-02-27', 4) (1, 'Raphael Bardini', '2006-04-28', 4), (2, 'Kervadec Matto', '2005-12-12', '18');";

$sql = "select * from etudiants;";

$sql = "delete from etudiants where id=0;";

$sql = "select * from etudiants;";

$sql = "update etudiants set date_naissance='1990-01-01' where id=(select min(e.id) from (select * from etudiants) as e);";

$sql = "select * from etudiants;";

todo : mettre le script complet
```
