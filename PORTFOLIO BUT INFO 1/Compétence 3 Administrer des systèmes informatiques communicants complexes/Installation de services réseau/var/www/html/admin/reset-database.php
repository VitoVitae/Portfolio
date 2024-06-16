<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Script de création de la BDD utilisateurs</title>
</head>

<body>
    <pre>
<?php
mysqli_report(MYSQLI_REPORT_ERROR | MYSQLI_REPORT_STRICT);
$db = new mysqli("localhost", "root", "lannion", "paolo");

$sql = <<<SQL
drop schema if exists users cascade;
create schema users;
set schema 'users';

create extension citext;
create domain email as citext
  check ( value ~ '^[a-zA-Z0-9.!#$%&''*+/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*$' );

create domain user_id as varchar(269);

create table _user(
    id user_id primary key,
    name varchar(255) not null unique,
    email_address email not null unique,
    first_name text not null,
    last_name text not null,
    -- https://www.php.net/manual/fr/function.password-hash.php recommends 255 chars
    password_hash(255) text not null,
    validated boolean not null
);

create table _token (
    user_id user_id primary key,
    selector varchar(255) not null,
    hashed_validator varchar(255) not null,
    expiry timestamp not null,
    constraint fk_user
        foreign key (user_id)
        references _user(id);
);
SQL;

var_dump($db->execute_query($sql));
?>
</pre>
</body>

</html>
<?php
