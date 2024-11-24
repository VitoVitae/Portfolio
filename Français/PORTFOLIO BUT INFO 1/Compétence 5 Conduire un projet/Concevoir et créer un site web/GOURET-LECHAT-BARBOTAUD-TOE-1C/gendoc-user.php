<?php
    function titre($line)
    {
        $line = explode(" ",$line);
        $res="";
        $nbr=0;
        foreach($line as $word){

            if (preg_match('(^(#{1,4}))',$word))
            {
                $word = rtrim($word);
                $nbr = strlen($word);
                $res = "$res" . "<h$nbr> ";
                
            }
            else
            {
                $word = rtrim($word);
                $res = "$res" . "$word ";
            } 
        }
        $res = "$res"."</h$nbr>\n";
        return $res;
    }

    function typetable($bloc)
    {
        $bloc = explode("\n",$bloc);
        $res="<table>\n";
        $td=false;
        $first=true;
        foreach($bloc as $i => $line)
        {
            if (($line!='')&&(!(preg_match("(\|-)",$line))))
            {
                $line = explode(" ",$line);
                foreach ($line as $j => $word) {
                    if ($j==0)
                    {
                        $res = "$res" . "\t<tr>\n";
                    }
                    if ($j != sizeof($line)-1)
                    {
                        if ($word=="|")
                        {
                            if ($first)
                            {
                                $res = $res . "\t\t<th> ";
                            }
                            else
                            {
                                $res = $res . "\t\t<td> ";
                            }
                            $td=true;
                        }
                        elseif ($td=true)
                        {
                            if ($first)
                            {
                                $res = "$res" . "$word </th>\n";
                            }
                            else
                            {
                                $res = "$res" . "$word </td>\n";
                            }
                            $td=false;
                        }
                        else
                        {
                            $res = "$res" . "$word ";
                        }
                    };
                }
                $res = "$res" . "\n\t</tr>\n\n";
                $first=false;
            }
        }
        $res = "$res"."</table>\n";
        return $res;
    }

    function typecode($bloc)
    {
        $bloc = explode("\n",$bloc);
        $code=false;
        foreach($bloc as $i => $line)
        {
            if (($line=="```")&&(!($code)))
            {
                $bloc[$i]="<pre><code>";
                $code=true;
            }
            elseif (($line=="```")&&($code))
            {
                $bloc[$i]="</code></pre>";
                $code=false;
            }
        }
        $res = implode("\n",$bloc);
        return $res;
    }

    function typelist($bloc)
    {
        $bloc = explode("\n",$bloc);
        $res="<ul>\n";
        $li=false;
        foreach ($bloc as $i => $line) {
            if ($line!='')
            {
                $line = explode(" ", $line);
                foreach ($line as $j => $word) {
                    if ($word=="-")
                    {
                        $res = $res . "\t<li> ";
                        $li = true;
                    }
                    else
                    {
                        $res = $res . "$word ";
                    }
                }
                /*vérifie  que la prochaine ligne est un tiret ou un retour à la ligne pour savoir si il faut fermer l'élément de liste*/
                if (($li) && ((preg_match("(^-)", $bloc[$i+1])) || ($bloc[$i+1]=='')))
                {
                    $res = $res . "</li>\n";
                    $li=false;
                }
            }
        }
        $res = $res . "</ul>\n";
        return $res;
    }
    function typemail($bloc)
    {
        return '<p><a href ="mailto: ' . $bloc .'">' . "$bloc</a></p>\n";
    }
    function typelien($bloc)
    {
        $chars = array("[","]","(",")");
        $replace= array("","|","","");     
        $bloc = str_replace($chars,$replace,$bloc);
        $bloc =  explode("|",$bloc);
        return '<p><a href="'. $bloc[1] .'">' . $bloc[0] . "</a></p>\n";
    }
/*fonction qui détermine le type du bloc */
    function typebloc($bloc)
    {

        $res= "";
        /*titres */
        if (preg_match('(^(#{1,4}))',$bloc))
        {
            $res = "$res" . titre($bloc) . "\n";
        }
        /*tableaux */
        elseif (preg_match('(\|)',$bloc))
        {
            $res = "$res" . typetable($bloc);
        }
        /*code */
        elseif (preg_match("((```))", $bloc))
        {
            $res = "$res" . typecode($bloc);
        }
        /*listes */
        elseif (preg_match("((- ))", $bloc))
        {
            $res = "$res" . typelist($bloc);
        }
        /*emails*/
        elseif (filter_var(trim($bloc),FILTER_VALIDATE_EMAIL))
        {
            $res = "$res" . typemail(trim($bloc));
        }
        /*liens */
        elseif (preg_match("(\[.+\]\(.+\))",$bloc))
        {
            $res = $res . typelien($bloc);
        }
        /*pour ne pas répéter les retours à la ligne */
        elseif ($bloc=="\n")
        {
            $res = "$res"."$bloc";
        }
        else
        {
            $res = "$res"."<p> " . $bloc . "</p>\n";;
        }
        
        return $res;
    }

/*début script */
    /*numéro de version est un paramètre */
    $version = $argv[1];
    $file = file("doc.md");
    /*$output = file("test.html");*/
    $outputfile = "doc-user-$version.html";
    $out = fopen($outputfile, 'w');

    

    $contenu = '<!DOCTYPE html>
<html lang="fr">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Documentation Technique - Version ' . "$version" . ' </title>
        <link rel="stylesheet" href="style.css">
        <style>
        pre {
          background-color: black;
          color: white;
          word-wrap: break-word;
          box-decoration-break: clone;
          padding: .3rem;
          border-radius: .2rem;
        }
        
        body {
          font-family: Arial, sans-serif;
        }
        
        section {
          margin-bottom: 20px;
        }
        
        h1, h2, h3, h4 {
          color: #333;
        }
        
        table {
          width: 100%;
          border-collapse: collapse;
          margin-bottom: 20px;
        }
        
        table, th, td {
          border: 1px solid #333;
        }
        
        th, td {
          padding: 10px;
          text-align: left;
        }
        
        
        li {
          margin-bottom: 5px;
        }
        
        pre {
          background-color: black;
          padding: 5px;
          overflow: auto;
        }
        
        code {
          font-family: "Courier New", Courier, monospace;
        }
    </style>
</head>
<body>
';

    fwrite($out,$contenu);
    $bloc="";
    foreach ($file as $i => $val){

        $bloc= "$bloc" . "$val";
        if ( ((strstr($val, PHP_EOL))&&($val=="\n")) ||(preg_match('(^(#{1,4}))',$val)) || ($i==sizeof($file)-1))
        {

            $bloc = typebloc($bloc);
            fwrite($out, $bloc);
            
            $bloc ="";
        }
        
    }

    fwrite($out, "</body>\n</html>");
    fclose($out);
/*voir expression régulières et fwrite*/
?>

