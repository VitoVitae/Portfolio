<?php 
function query($link, $sql) {
    $sql=rtrim($sql);
    if (!($result=mysqli_query($link, $sql))) { 
        printf("<pre>".$sql." = "."error '%s'</pre>", mysqli_error($link));
	return;
    }

    echo '<pre>'.$sql." = ";
    var_dump($result);
    echo '</pre>';

}

$link = mysqli_connect('127.0.0.1', 'root', 'lannion') or die ('Error connecting to mysql: ' . mysqli_error($link).'\r\n'); 

//query($link, "create database paolo;");

query($link, "show databases;");

query($link, "use paolo;");

query($link, "create table etudiants (
    id int primary key,
    nom text not null,
    date_naissance date not null,
    classement int not null);");

query($link, "show tables;");

query($link, "insert into etudiants(id, nom, date_naissance, classement) values (0, 'Toe Paolo', '2005-02-27', 4), (1, 'Raphael Bardini', '2006-04-28', 4), (2, 'Kervadec Matto', '2005-12-12', '18');");

query($link, "select * from etudiants;");

query($link, "delete from etudiants where id=0;");

query($link, "select * from etudiants;");

query($link, "update etudiants set date_naissance='1990-01-01' where id=(select min(e.id) from (select * from etudiants) as e);");

query($link, "select * from etudiants;");

query($link, "delete from etudiants;");
?>