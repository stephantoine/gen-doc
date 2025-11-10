<?php

$config = 'config.txt'

$fichier_html = 'technique.html';

$entete = '<!DOCTYPE html>
<html>
    <head>
        <link rel="stylesheet" href="style.css">
        <meta charset="utf-8" />
        <title>Documentation technique html</title>
    </head>
    <body>
        <nav class="menu">
            <ul>
                <li><a href="#1er fichier">Fichier 1</a></li>
                <li><a href="#2eme fichier">Fichier 2</a></li>
                <li><a href="#3eme fichier">Fichier 3/a></li>
            </ul>
        </nav>
        <header>';

function commentaires($code) {
    // Utilisez une expression régulière pour extraire les commentaires
    preg_match_all('/\/\*(.*?)\*\//s', $code, $matches);
    return $matches[1];
}

function ranger($comments) {
    $commentaires = array(
        'entete' => array(),
        'constantes' => array(),
        'structures' => array(),
        'globales' => array(),
        'fonctions' => array(),
    );
    
    
    foreach ($comments as $comment) {
        // Utilisez des expressions régulières pour identifier le contexte du commentaire
        if (preg_match('/\bpage\b/i', $comment)){
            $range['entete'][] = $comment;
        } elseif (preg_match('/\bdef\b|\bconst\b/i', $comment)){
            $range['constantes'][] = $comment;
        } elseif (preg_match('/\bstruct\b/i', $comment)){
            $range['structures'][] = $comment;
        } elseif (preg_match('/\bvar\b/i', $comment)){
            $range['globales'][] = $comment;
        } elseif (preg_match('/\bfunction\b|\bvoid\b|\bint\b|\bfloat\b|\bchar\b/i', $comment)) {
            $range['fonctions'][] = $comment;
        }
    }
    return $range;
}


function creer_doc($fichier, $i){
    
    
    $code = file_get_contents($fichier); // on récupère le contenu du fichier
    
    $comments = commentaires($code); // on ne garde que les commentaires
    $tri = ranger($comments); // on trie les commentaires
    
    // PAGE D'ACCUEIL et ENTETE//
    
    // $author = "";
    // $version = "";
    // $date = "";
    // $page = "";
    // $ent = "";
    
    // $liste_ent = explode("\\", trim($tri['entete'][0]));
    // foreach($liste_ent as $key => $value){
    //     $position1 = strpos($value[0], "a");
    //     $position2 = strpos($value[1], "u");
    //     $position3 = strpos($value[2], "t");
    //     if ($position1 !== false and $position2 !== false and $position3 !== false){
    //         $res = explode(" ", $value);
    //         for ($i = 1; $i < count($res); $i++){
    //             $pos = strpos($res[$i], "*");
    //             if($pos !== false){
    //                 $author = $author . substr($res[$i], 0, -1) . " ";
    //             }
    //             else{
    //                 $author = $author . $res[$i] ." ";
    //             }
    //         }
    //     }
    
    //     $position1 = strpos($value[0], "d");
    //     $position2 = strpos($value[1], "a");
    //     $position3 = strpos($value[2], "t");
    //     if ($position1 !== false and $position2 !== false and $position3 !== false){
    //         $res = explode(" ", $value);
    //         for ($i = 1; $i < count($res); $i++){
    //             $pos = strpos($res[$i], "*");
    //             if($pos !== false){
    //                 $date = $date . substr($res[$i], 0, -1) . " ";
    //             }
    //             else{
    //                 $date = $date . $res[$i] ." ";
    //             }
    //         }
    
    //         $da = explode(" ", $date);
    //         $d= substr($da[2], 0, 4);
    
    
    //         $date = $da[0]." ".$da[1]." ".$d;
    
    //         for ($i = 3; $i < count($da); $i++){
    //             $ent = $ent.trim($da[$i])." ";
    //         }
    //     }
    
    //     $position1 = strpos($value[0], "p");
    //     $position2 = strpos($value[1], "a");
    //     $position3 = strpos($value[2], "g");
    //     if ($position1 !== false and $position2 !== false and $position3 !== false){
    //         $res = explode(" ", $value);
    //         for ($i = 1; $i < count($res); $i++){
    //             $pos = strpos($res[$i], "*");
    //             if($pos !== false){
    //                 $page = $page . substr($res[$i], 0, -1) . " ";
    //             }
    //             else{
    //                 $page = $page . $res[$i] ." ";
    //             }
    //         }
    //     }
    
    //     $position1 = strpos($value[0], "v");
    //     $position2 = strpos($value[1], "e");
    //     $position3 = strpos($value[2], "r");
    //     if ($position1 !== false and $position2 !== false and $position3 !== false){
    //         $res = explode(" ", $value);
    //         for ($i = 1; $i < count($res); $i++){
    //             $pos = strpos($res[$i], "*");
    //             if($pos !== false){
    //                 $version = $version . substr($res[$i], 0, -1) . " ";
    //             }
    //             else{
    //                 $version = $version . $res[$i] ." ";
    //             }
    //         }
    //     }
    // }
    // $author = trim($author);
    // $version = trim($version);
    // $page = trim($page);
    
    $f = fopen($config);
    $fd = file_get_contents($f);
    foreach ($fd as $key => $ligne){
        $lig = explode("=", $ligne);
        if ($lig[0]=== "CLIENT"){
            $author = $lig[1];
        }
        if($lig[0]==="PRODUIT"){
            $produit = $lig[1];
        }
        if($lig[0]==="VERSION"){
            $version = $lig[1];
        }
    }
    
    // on vérifie si le fichier peut être ouvert et si il peut être modifié
    
    if (is_writable($fichier_html)) {
        if (!$fp = fopen($fichier_html, 'w+')) {
             echo "Impossible d'ouvrir le fichier ($fichier_html)";
             exit;
        }
    
        if (fwrite($fp, $entete) === FALSE) {
            echo "Impossible d'écrire dans le fichier ($fichier_html)";
            exit;
        } else {
            // affichage
    
            //page d'accueil
            fwrite($fp, "\n            <h1 id='$fichier"." ".$i."'>Documentation technique $fichier </h1>\n");
            fwrite($fp, "            <h3>$author</h3>\n");
            fwrite($fp, "            <h3>$page</h3>\n");
            fwrite($fp, "            <h3>Verion : $version</h3>\n");
            fwrite($fp, "            <h3>$date</h3>\n");
            fwrite($fp, "         </header>\n");
            //entete
            fwrite($fp, "         <article>\n");
            fwrite($fp, '            <h2>En-tête</h2>');
            fwrite($fp, "\n            <p>$ent</p>\n");
            fwrite($fp, "         </article>\n");
            //define
            fwrite($fp, "         <article>\n");
            fwrite($fp, '            <h2>Define</h2>');
            fwrite($fp, "            <ol>\n");
    
            // constantes//
    
            $nbdefine = 0;
            $indice = 0;
            $define = "";
            $constantes = [];
    
        
            $tab_const = $tri['constantes'];
            foreach ($tab_const as $key => $value){ // pour chaque constante
                $nbdefine++;
                $const = explode("\\", $tab_const[$indice]);
                foreach($const as $key => $ligne){ //pour chaque ligne
                    $ligne = trim($ligne);
                    $res = explode(" ", $ligne);
                    for ($i = 1; $i < count($res); $i++){
                        $pos = strpos($res[$i], "*");
                        if($pos !== false){
                            $define = $define . substr($res[$i], 0, -1) . " ";
                        }
                        else{
                            $define = $define . $res[$i] ." ";
                        }
                    }
                }
                $constantes[$indice] = $define;
                $define = "";
                $indice++;
            }
    
            for ($i = 0; $i < $nbdefine; $i++){
                fwrite($fp, "               <li>$constantes[$i]</li>\n");
                fwrite($fp, "               <br>\n");
            }
            fwrite($fp, "            </ol>\n");
            fwrite($fp, "         </article>\n");
    
    
            //structures
    
            fwrite($fp, "         <article>\n");
            fwrite($fp, '            <h2 id="structures">Structures</h2>');
            fwrite($fp, "            <ol>\n");
    
            $nbstruct = 0;  
            $indice = 0;
            $struct = "";
            $structures = [];
    
            $tab_stru = $tri['structures'];
            foreach ($tab_stru as $key => $value){ // pour chaque structure
                $nbstruct++;
                $struc = explode("\\", $tab_stru[$indice]);
                foreach($struc as $key => $ligne){ //pour chaque ligne
                    $ligne = trim($ligne);
                    $res = explode(" ", $ligne);
                    for ($i = 1; $i < count($res); $i++){
                        $pos = strpos($res[$i], "*");
                        if($pos !== false){
                            $struct = $struct . substr($res[$i], 0, -1) . " ";
                        }
                        else{
                            $struct = $struct . $res[$i] ." ";
                        }
                    }
                }
                $structures[$indice] = $struct;
                $struct = "";
                $indice++;
            }
    
            for ($i = 0; $i < $nbstruct; $i++){
                fwrite($fp, "               <li>$structures[$i]</li>\n");
                fwrite($fp, "               <br>\n");
            }
            fwrite($fp, "            </ol>\n");
            fwrite($fp, "         </article>\n");
    
            // globales //
    
            fwrite($fp, "         <article>\n");
            fwrite($fp, '            <h2>Globales</h2>');
            fwrite($fp, "            <ol>\n");
    
            $nbglobales = 0;  
            $indice = 0;
            $glob = "";
            $globales = [];
    
            $tab_glob = $tri['globales'];
            foreach ($tab_glob as $key => $value){ // pour chaque variable globale
                $nbglobales++;
                $glo = explode("\\", $tab_glob[$indice]);
                foreach($glo as $key => $ligne){ //pour chaque ligne
                    $ligne = trim($ligne);
                    $res = explode(" ", $ligne);
                    for ($i = 1; $i < count($res); $i++){
                        $pos = strpos($res[$i], "*");
                        if($pos !== false){
                            $glob = $glob . substr($res[$i], 0, -1) . " ";
                        }
                        else{
                            $glob = $glob . $res[$i] ." ";
                        }
                    }
                }
                $globales[$indice] = $glob;
                $glob = "";
                $indice++;
            }
    
            for ($i = 0; $i < $nbglobales; $i++){
                fwrite($fp, "               <li>$globales[$i]</li>\n");
                fwrite($fp, "               <br>\n");
            }
            fwrite($fp, "            </ol>\n");
            fwrite($fp, "         </article>\n");
    
            // fonctions //
    
            fwrite($fp, "         <article>\n");
            fwrite($fp, '            <h2>Fonctions et Procédures</h2>');
            fwrite($fp, "            <ol>\n");
    
            $nbfonctions = 0;  
            $indice = 0;
            $fonc = "";
            $fonctions = [];
    
            $tab_fonc = $tri['fonctions'];
            foreach ($tab_fonc as $key => $value){ // pour chaque fonctions et procédures
                $nbfonctions++;
                $fo = explode("\\", $tab_fonc[$indice]);
                foreach($fo as $key => $ligne){ //pour chaque ligne
                    $ligne = trim($ligne);
                    $res = explode(" ", $ligne);
                    for ($i = 1; $i < count($res); $i++){
                        $pos = strpos($res[$i], "*");
                        if($pos !== false){
                            $fonc = $fonc . substr($res[$i], 0, -1) . " ";
                        }
                        else{
                            $fonc = $fonc . $res[$i] ." ";
                        }
                    }
                }
                $fonctions[$indice] = $fonc;
                $fonc = "";
                $indice++;
            }
    
            for ($i = 0; $i < $nbfonctions; $i++){
                fwrite($fp, "               <li>$fonctions[$i]</li>\n");
                fwrite($fp, "               <br>\n");
            }
            fwrite($fp, "            </ol>\n");
            fwrite($fp, "        </article>\n");
            fwrite($fp, "    </body>\n");
            fwrite($fp, "</html>\n");
        }
    
        fclose($fp);
    
    } else {
        echo "Le fichier $fichier_html n'est pas accessible en écriture.";
    }

    return $fichier_html;
}

if (count($argv) != 4) {
    die("Usage: php script.php fichier1.c fichier2.c fichier3.c\n");
}

$fichier1 = $argv[1];
$fichier2 = $argv[2];
$fichier3 = $argv[3];


creer_doc($fichier1, 1);
creer_doc($fichier2, 2);
creer_doc($fichier3, 3);
?>