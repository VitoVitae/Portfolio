#!/usr/bin/php






<?php 
$user = exec('whoami'); 
?>

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="style.css" type="text/css">
    <title>Météo</title>
</head>

<body>
    <header id="connecté">
        <h2>page d'acceuil SAE 2.03</h2>
        <?php  
        if(array_key_exists('button1', $_POST)) { 
            button1(); 
            }  
        function button1() { 
            echo "This is Button1 that is selected";
            } 
            ?>

        <a href="index.html">se deconnecter</a>
        <input type="submit" name="button1" class="button" value="Button1" />

    </header>
    <main id="acceuil">

        <h1>Bienvenue administrateur <?php echo $user ?> </h1>
        <div id="pub">
            <div id="404">
                <p>ceci est une page qui vous interesse</p>
                <a href="https://www.federationpeche.fr/" target="_blank"><img src="yeux-merlan-frit-064009.jpg"
                        alt=""></a>
            </div>
            <div id="meteo_monde">
                <p>la météo dans le monde</p>
                <a href="https://meteofrance.com/meteo-monde" target="_blank"><img src="météo_monde.png" alt=""></a>
            </div>
        </div>





    </main>
    <footer>
        <address>
            <a href="https://github.com/Matteo-K" target="_blank">
                <img src="images/logo/github.png" alt="github Matteo-K">
                Matteo-K
            </a>
        </address>
        <address>
            <a href="https://github.com/5cover" target="_blank">
                <img src="images/logo/github.png" alt="github Scover">
                Scover
            </a>
        </address>
        <address>
            <a href="https://github.com/mariuschartier" target="_blank">
                <img src="images/logo/github.png" alt="github mariuschartier">
                mariuschartier
            </a>
        </address>
        <address>
            <a href="https://github.com/VitoVitae" target="_blank">
                <img src="images/logo/github.png" alt="github VitoVitae">
                VitoVitae
            </a>
        </address>
    </footer>
</body>

</html>