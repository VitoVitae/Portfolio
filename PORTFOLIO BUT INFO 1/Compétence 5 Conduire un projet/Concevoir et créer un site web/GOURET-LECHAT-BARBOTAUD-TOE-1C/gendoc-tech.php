<?php

    $versionFile = "version.txt";
    $currentVersion = file_get_contents($versionFile);

    $newVersion = $currentVersion + 1;

    file_put_contents($versionFile, $newVersion);
    $fichier= ['src1.c', 'src2.c', 'src3.c'];

    function retirerCommentaire($contenu) {
        // Fonction qui retire tous les commentaires du code
        return preg_replace('/\/\*\*.*?\*\//s', '', $contenu);
    }

    function retirerCommentaireStructure($contenu) {
        // Fonction qui retire tous les commentaires de la structure du code
        return preg_replace('/\/\*\*.*?\*\//s', '', $contenu);
    }



    function retirecom($commentaire) {
        //supprime les différents motifs liés aux commentaires
        return str_replace(['/**', '*', '*/', '/', '\\', '/*'], '', $commentaire);
    }


    function getCommentaire($structure) {
        // Fonction qui extrait le commentaire 
        preg_match('/\/\*\*([^*]|[\r\n]|(\*+([^*\/]|[\r\n])))*\*+\//', $structure, $result);
        
        if (isset($result[0])) {
            return retirecom(trim($result[0]));
        }
        return '';
    }



    function getEntete($contenu) {
        // Fonction qui obtient le debut du code
        $debut = strpos($contenu, '/**');
        $fin = strpos($contenu, '*/', $debut);
        if ($debut !== false && $fin !== false) {
            $taille = $fin + strlen('*/') - $debut;
            return retirecom(trim(substr($contenu, $debut, $taille)));
        }
    }

    function getDefines($contenu) {
        // Fonction qui obtient toutes les define du code
        $debut = strpos($contenu, '#define');
        $defines = array();
        while ($debut !== false) {
            $finLigne = strpos($contenu, "\n", $debut);
            $ligneDefine = substr($contenu, $debut, $finLigne - $debut);
            $defines[] = trim($ligneDefine);
            $debut = strpos($contenu, '#define', $finLigne);
        }
        return $defines;
    }

    function getVarGlobal($contenu) {
        // Fonction qui obtient toutes les variables globales du code
        $debut = strpos($contenu, 'const');
        $varGlobal = array();
        while ($debut !== false) {
            $finLigne = strpos($contenu, "\n", $debut);
            $ligneVarGlobal = substr($contenu, $debut, $finLigne - $debut);
            $varGlobal[] = trim($ligneVarGlobal);
            $debut = strpos($contenu, 'const', $finLigne);
        }
        return $varGlobal;
    }

    function getStructures($contenu) {
        // Fonction qui obtient toutes les structures du code
        $debut = strpos($contenu, 'typedef struct');
        $structures = array();
        while ($debut !== false) {
            // la fin est : "} nomStructure; /**Commentaire*/" je dois prendre toute la ligne
            $fin = strpos($contenu, '}', $debut);
            $fin = strpos($contenu, ';', $fin);
            $fin = strpos($contenu, '*/', $fin);
            $finLigne = strpos($contenu, "\n", $fin);
            $ligneStructure = substr($contenu, $debut, $finLigne - $debut);
            $structures[] = trim($ligneStructure);
            $debut = strpos($contenu, 'typedef struct', $finLigne);
        }
        return $structures;
    }


    function formateStructure($contenu) {
        $commentaire = [];
        $listeVariables = [];
        $commentaireFinal = [];
        preg_match_all('/\\s+([^\\s]+)\\s*;/', $contenu, $result);
        if (isset($result[1])) {
            foreach ($result[1] as $match) {
                $listeVariables[] = trim($match);
            }
        }
        //retire la dernière variable qui est le nom de la structure
        array_pop($listeVariables);

        // obtient tout les commentaires de la structure qui sont : "/** .. */"
        preg_match_all('/\/\*\*([^*]|[\r\n]|(\*+([^*\/]|[\r\n])))*\*+\//', $contenu, $result);
        if (isset($result[0])) {
            foreach ($result[0] as $match) {
                $commentaire[] = retirecom(trim($match));
            }
        }
        // on veut mettre le nom de la variable devant le commentaire tel que : "nomVariable : commentaire" sauf pour la dernière ligne
        foreach ($listeVariables as $clef => $variable) {
            if (isset($commentaire[$clef])) {
                $commentaireFinal[] = $variable . ' : ' . $commentaire[$clef];
            }
        }
        // ajoute le commentaire de la dernière ligne
        if (isset($commentaire[$clef + 1])) {
            $commentaireFinal[] = $commentaire[$clef + 1];
        }
        return $commentaireFinal;
    }



    function trouverFinCode($contenu, $debutCode) {
        $level = 0;
        $pos = $debutCode;
        do {
            $char = $contenu[$pos];
            if ($char === '{') {
                $level++;
            } elseif ($char === '}') {
                $level--;
            }
            $pos++;
        } while ($level > 0 && $pos < strlen($contenu));

        return $pos;
    }


    function getFonctions($contenu) {
        $debut = strpos($contenu, '/**');
        $fonctions = array();

        while ($debut !== false) {
            // Trouver la fin du commentaire (marquée par '*/')
            $finCommentaire = strpos($contenu, '*/', $debut);
            
            // Trouver le début du code (marqué par '{')
            $debutCode = strpos($contenu, '{', $finCommentaire);

            // Trouver la fin du code (marquée par '}')
            $finCode = trouverFinCode($contenu, $debutCode);

            // Extraire les commentaires de la fonction
            $commentaire = substr($contenu, $debut, $finCommentaire - $debut + 2); // +2 pour inclure '*/'

            // Extraire le header de la fonction
            $headerFonction = substr($contenu, $finCommentaire + 2, $debutCode - $finCommentaire - 2);

            // Extraire le début de la fonction (y compris la déclaration de la fonction)
            $debutFonction = substr($contenu, $debutCode, $finCode - $debutCode + 1); // +1 pour inclure '}'

            // Ajouter au tableau
            $fonction = trim($commentaire . $headerFonction . $debutFonction);
            $fonctions[] = $fonction;

            // Trouver la prochaine occurrence de '/**'
            $debut = strpos($contenu, '/**', $finCode);
        }

        return $fonctions;
    }

    function retirerCommentaireFonction($contenu) {
        // Utiliser une expression régulière pour retirer le commentaire
        $contenu = preg_replace('/\/\*\*(.*?)\*\//s', '', $contenu);
        return $contenu;
    }

    function retourneFonction($contenu) {
        // Utiliser une expression régulière pour extraire le retour
        preg_match('/\\s*\\breturn\\b(.+?);/', $contenu, $result);
        return isset($result[1]) ? trim($result[1]) : null;
    }

    function parametresFonction($contenu) {
        // Utiliser une expression régulière pour extraire les paramètres
        preg_match_all('/\\s*\\bparam\\b(.+?);/', $contenu, $result);
        return isset($result[1]) ? array_map('trim', $result[1]) : null;
    }

    function briefFonction($contenu) {
        // Utiliser une expression régulière pour extraire le brief
        preg_match('/\\s*\\bbrief\\b(.+?)\\n/', $contenu, $result);
        return isset($result[1]) ? trim($result[1]) : null;
    }


    function ajouterCommentaireReturn($contenu) {
        
        preg_match_all('/\breturn\s+(\w+)\s*;/', $contenu, $result);

        if (isset($result[1])) {
            foreach ($result[1] as $variable) {
                $contenu = str_replace("return $variable;", "return: $variable;", $contenu);
            }
        }

        return $contenu;
    }

    function ajouterCommentaireParametre($contenu) {
        preg_match_all('/\bparam\s+(\w+)\s*:\s*([^\*\n\r]+)/', $contenu, $result);

        if (isset($result[1]) && isset($result[2])) {
            foreach ($result[1] as $index => $parametre) {
                $commentaire = trim($result[2][$index]);
                $contenu = str_replace("param $parametre:", "param $parametre: $commentaire", $contenu);
            }
        }

        return $contenu;
    }

    // Ouvrir le fichier en mode écriture
    $outputfile = "doc-tech-$newversion.html";
    $fh = fopen($outputfile, 'w');

    $i=0;
    $contenu = '
    <!DOCTYPE html>
    <html lang="fr">
        <head>
            <meta charset="UTF-8">
            <meta name="viewport" content="width=device-width, initial-scale=1.0">
            <title>Documentation Technique - Version ' . $newVersion . '</title>
            <link rel="stylesheet" href="style.css">
        </head>
        <body>
            <header>
                <h1>Documentation Technique</h1>
                <p>Version ' . $newVersion .' '. date("d/m/Y ") . ' : <?php echo date("d/m/Y"); ?></p>
            </header>';
    fwrite($fh, $contenu);            
        
    foreach ($fichier as $sourceFile) {
        $i=$i+1;

        $contenu = file_get_contents($sourceFile);
        $definesContent=getDefines($contenu);
        $enTeteDeCodeContent=getEntete($contenu);
        $structuresContent=getStructures($contenu); 
        $varGlobalContent=getVarGlobal($contenu);
        $fonctionsContent=getFonctions($contenu);
        $outputfile = "doc-tech-1.html";
        $fh = fopen($outputfile, 'a');

        if ($fh) {
            // Début du contenu HTML
            $contenu = '
            <h1>' .basename($sourceFile). '</h1>
            <nav>
                <ul>
                    <li><a href="#en-tete'.$i.'">En-tête de code</a></li>
                    <li><a href="#defines'.$i.'">#define</a></li>
                    <li><a href="#variablesglobales'.$i.'">Variables Globales</a></li>
                    <li><a href="#structures'.$i.'">Structures</a></li>
                    <li><a href="#fonctions'.$i.'">Fonctions</a></li>
                </ul>
            </nav>';

            // Écrire le contenu dans le fichier
            fwrite($fh, $contenu);

            // Section En-tête de code
            $contenu = '
                <section id="en-tete'.$i.'">
                    <h2>En-tête de code</h2>
                    <figure>
                        <pre>' . htmlspecialchars($enTeteDeCodeContent) . '</pre>
                    </figure>
                </section>';

            // Écrire le contenu dans le fichier
            fwrite($fh, $contenu);

            // Section #define
            $contenu = '
                <section id="defines'.$i.'">
                    <h2>#define</h2>';
                    
            fwrite($fh, $contenu);

            foreach ($definesContent as $define) {
                $contenu = '
                    <figure>
                        <h3>' . getCommentaire($define) . '</h3>
                        <pre>' . htmlspecialchars(retirerCommentaire($define)) . '</pre>
                    </figure>';
                fwrite($fh, $contenu);
            }
            $contenu = '
                </section>';
            fwrite($fh, $contenu);

            // Section Variables Globales
            $contenu = '
                <section id="variablesglobales'.$i.'">
                    <h2>Variables Globales</h2>';

            fwrite($fh, $contenu);

            foreach ($varGlobalContent as $global) {
                $contenu = '
                <figure>
                    <h3>' . getCommentaire($global) . '</h3>
                    <pre>' . htmlspecialchars(retirerCommentaire($global)) . '</pre>
                </figure>';
                fwrite($fh, $contenu);
            }

            $contenu = '
                </section>';

            fwrite($fh, $contenu);

            // Section Structures
            $contenu = '
            <section id="structures'.$i.'">
                <h2>Structures</h2>';

            fwrite($fh, $contenu);

            foreach ($structuresContent as $structure) {
                $commentaire = formateStructure($structure);
                $contenu = '
                <figure>
                    <h3>' . end($commentaire) . '</h3>
                    <pre>' . htmlspecialchars(retirerCommentaireStructure($structure)) . '</pre>';

                foreach ($commentaire as $comment) {
                    if ($comment !== end($commentaire)) {
                        $contenu .= '<p>' . $comment . '</p>';
                    }
                }

                $contenu .= '</figure>';
                if ($structure !== end($structuresContent)) {
                    $contenu .= '<hr>';
                }

                fwrite($fh, $contenu);
            }

            $contenu = '
            </section>';

            fwrite($fh, $contenu);

            // Section Fonctions
            $contenu = '
            <section id="fonctions'.$i.'">
                <h2>Fonctions</h2>';

            fwrite($fh, $contenu);

            foreach ($fonctionsContent as $fonction) {
                $return = retourneFonction($fonction);
                $parametres = parametresFonction($fonction);
                $brief = briefFonction($fonction);

                $contenu = '
                <figure>
                    <h3>' . $brief . '</h3>
                    <pre>' . htmlspecialchars(retirerCommentaireFonction($fonction)) . '</pre>';
                        
                if ($parametres !== null) {
                    $contenu .= '<p>Paramètres : ';
                    foreach ($parametres as $parametre) {
                        $contenu .= '<p>' . $parametre;
                        $contenu = ajouterCommentaireParametre($contenu);
                        $contenu .= '</p>';
                    }
                    $contenu .= '</p>';
                }
                if ($return !== null) {
                    $contenu .= '<p>Retourne : ' . $return;
                    $contenu = ajouterCommentaireReturn($contenu);
                    $contenu .= '</p>';
                }
                $contenu .= '</figure>';

                if ($fonction !== end($fonctionsContent)) {
                    $contenu .= '<hr>';
                }

                fwrite($fh, $contenu);
            }


            $contenu = '
                </section>';

            fwrite($fh, $contenu);   

            // Fin du contenu HTML
                $contenu = '
                    </body>
                </html>';

            // Écrire le contenu dans le fichier
            fwrite($fh, $contenu);

            // Fermer le fichier
            fclose($fh);
                
            echo "Le fichier HTML a été créé avec succès.";
            
        }else {
            echo "Erreur lors de l'ouverture du fichier.";
        }
    }      
        
?>
