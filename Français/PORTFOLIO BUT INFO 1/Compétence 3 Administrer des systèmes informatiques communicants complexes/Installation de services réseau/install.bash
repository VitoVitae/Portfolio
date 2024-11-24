#!/bin/env bash

# Script de mise en place du serveur (à compléter)

source /etc/apache2/envvars

htpasswd -c /etc/apache2/pass testeur

 >> /etc/apache2/apache2.conf echo 'ServerName 127.0.0.1'

a2enmod php7.4 mime headers

# Modification du PHP.conf pour accepter les .html et les fichiers sans extension
readonly match='
<FilesMatch ".*"> 
    SetHandler application/x-httpd-php 
</FilesMatch>'
readonly replace='
<FilesMatch ".+(.phar|.php|.p?html|)$"> 
    SetHandler application/x-httpd-php 
</FilesMatch>'
sed -ie "s/$match/$replace/" /etc/apache2/mods-enabled/php7.4.conf

# does not work at this time
# mysql_secure_installation -p 'lannion' <<< 'n n y y n y'

dpkg -i /usr/local/src/*

>> /var/www/html/.htaccess echo '<IfModule mod_mime.c>
    <FilesMatch "[^.]+\.css$">
        Header set Content-Type: "text/css"
    </FilesMatch>

    <FilesMatch "[^.]+\.js$">
        Header set Content-Type: "text/javascript"
    </FilesMatch>
</IfModule>'

systemctl restart apache2

