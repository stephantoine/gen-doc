#!/usr/bin/php
<!DOCTYPE html>
<html lang="fr">
<head>
    <title>Document</title>
</head>

<?php

$file = file('DOC_UTILISATEUR.md');

# clear file
file_put_contents("test.txt", "");

foreach ($file as $numLigne => $ligne) {
    $mot = "";

    ####
    if ($ligne[0] == '#' && $ligne[1] == '#' &&$ligne[2] == '#' &&$ligne[3] == '#') {
        for ($i = 4; $i < strlen($ligne); $i++) {
            $mot .= $ligne[$i];
        }
        $mot = trim($mot, "\n");
        file_put_contents('test.txt', "<h4> $mot <\h4>\n", FILE_APPEND);
    }

    ###
    elseif ($ligne[0] == '#' && $ligne[1] == '#' &&$ligne[2] == '#') {
        for ($i = 3; $i < strlen($ligne); $i++) {
            $mot .= $ligne[$i];
        }
        $mot = trim($mot, "\n");
        file_put_contents('test.txt', "<h3> $mot <\h3>\n", FILE_APPEND);
    }

    ##
    elseif ($ligne[0] == '#' && $ligne[1] == '#') {
        for ($i = 2; $i < strlen($ligne); $i++) {
            $mot .= $ligne[$i];    
        }
        $mot = trim($mot, "\n");
        file_put_contents('test.txt', "<h2> $mot <\h2>\n", FILE_APPEND);
    }
    
    #
    elseif ($ligne[0] == '#') {
        for ($i = 1; $i < strlen($ligne); $i++) {
            $mot .= $ligne[$i];
        }
        $mot = trim($mot, "\n");
        file_put_contents('test.txt', "<h1> $mot <\h1>\n", FILE_APPEND);
    }

}
?>