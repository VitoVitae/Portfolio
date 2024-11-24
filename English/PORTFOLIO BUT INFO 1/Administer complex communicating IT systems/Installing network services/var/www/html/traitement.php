<?php
    $db = new mysqli("localhost", "user", "resu", "paolo");

    $db->execute_query("set schema 'users';");

    function link_random_part($length = 13): string {
        if (function_exists("random_bytes")) {
            $bytes = random_bytes(ceil($length / 2));
        } elseif (function_exists("openssl_random_pseudo_bytes")) {
            $bytes = openssl_random_pseudo_bytes(ceil($length / 2));
        } else {
            throw new Exception("no cryptographically secure random function available");
        }
        return substr(bin2hex($bytes), 0, $length);
    }

    function generate_tokens(): array
{
    $selector = bin2hex(random_bytes(16));
    $validator = bin2hex(random_bytes(32));

    return [$selector, $validator, $selector . ':' . $validator];
}

    function login(string $user_id) {
        global $db;

        [$selector, $validator, $token] = generate_tokens();

        $query = <<<SQL
            insert into _user (user_id, selector, hashed_validator, expiry)
            values (?, ?, ?, ?, ?, ?, false);
        SQL;
        // https://www.phptutorial.net/php-tutorial/php-remember-me/
        $expired_seconds = time() + 86400 * 30; // stay logged in for 30 days.

        $sucess = $db->execute_query($query,
            [
                $user_id,
                $selector,// selector
                password_hash($validator, PASSWORD_DEFAULT),// hashed_validator
                date('Y-m-d H:i:s', time() + 5 * 3600) // expiry
            ]) !== false;

        setcookie('remember_me', $token, $expired_seconds);
    }

    function get_user(string $name): array|null {
        global $db;
        $query = <<<SQL
            select * from _user where name=?
        SQL;
        return $db->execute_query($query, [ $name ])->fetch_row();
    }  

    function register(string $name, string $email_address, string $first_name, string $last_name, string $password_hash) {
        global $db;
        $query = <<<SQL
        insert into _user (id, name, email_address, first_name, last_name, password_hash, validated)
        values (?, ?, ?, ?, ?, ?, false);
        SQL;
        
        $user_id = $name.'-'.link_random_part();

        $result = $db->execute_query($query,
            [
                $user_id,
                $name,
                $email_address,
                $first_name,
                $last_name,
                $password_hash
            ]);

        syslog(LOG_INFO, "register user $name: $result");
        
        login($user_id);
    }

    if (isset($_POST["Connexion_Test"]) || (isset($_POST["Inscription_Test"]))) {
    // Vérification du passage par la page de connexion

        if (isset($_POST["Connexion_Test"])) {
            $name = $_POST["id_conx"];
            $mdp = $_POST["mdp_conx"];

            $me = get_user($name);
            if ($me === null) {
                // todo: utilisateur non trouvé
            } else {
                
            }

            if (password_verify($_POST["conf_mdp_inscr"], $me['password_hash'])) {
                login($me->id);
            } else {
                // todo: mot de passe incorrect
            }

        } else {
            $password_hash = password_hash($_POST["mdp_inscr"], PASSWORD_DEFAULT);
            if (!password_verify($_POST["conf_mdp_inscr"], $password_hash)) {
                // todo: erreur: confirmation différente du mdp
            }

            register($_POST["id_inscr"], $_POST["email_inscr"], $_POST["prenom_inscr"], $_POST["nom_inscr"], $password_hash);
        }

    } else {
        // Si l'utilisateur a réussi à accéder à la page sans cliquer sur le bouton
        echo "Erreur : Vous n'avez pas la permission d'accès à cette page";
    }
?>