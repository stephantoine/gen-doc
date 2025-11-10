#!/usr/bin/php
<!DOCTYPE html>
<html lang="fr">
<head>
<meta name="description" content="équivalent markdown en html">
		<meta charset="utf-8">
		<meta name="author" content="Basile Ceschia le meilleur">
        <link rel="stylesheet" href="DOC_UTILISATEUR.css">
		<title>md to html</title>
</head>

<body>
<?php

$file = file('doc.md');
$in_table=false;
$in_section=false;
$in_code=false;
$in_list=false;
foreach ($file as $numLigne => $ligne) {
    $mot = "";
    

    ####
    if ($ligne[0] == '#' && $ligne[1] == '#' &&$ligne[2] == '#' &&$ligne[3] == '#') {
    for ($i = 4; $i < strlen($ligne); $i++) {
        $mot .= $ligne[$i];
    }
    $mot = trim($mot, "\n");?>
    <h4><?php echo $mot?></h4>
    <?php
    }

    ###
    elseif ($ligne[0] == '#' && $ligne[1] == '#' &&$ligne[2] == '#') {
        for ($i = 3; $i < strlen($ligne); $i++) {
            $mot .= $ligne[$i];
        }
        $mot = trim($mot, "\n");?>
        <h3><?php echo $mot?></h3>
    <?php
    }

    ##
    elseif ($ligne[0] == '#' && $ligne[1] == '#') {
        if($in_section==true){
            ?> </section> <?php
            $in_section=false;
            ?> <section> <?php
            $in_section=true;
        }else{
            ?> <section> <?php
            $in_section=true;
        }

        for ($i = 2; $i < strlen($ligne); $i++) {
            $mot .= $ligne[$i];    
        }
        $mot = trim($mot, "\n");?>
        <h2><?php echo $mot?></h2>
    <?php  
    }
    
    #
    elseif ($ligne[0] == '#') {
        if($in_section==true){
            ?> </section> <?php
            $in_section=false;
            ?> <section> <?php
            $in_section=true;
        }else{
            ?> <section> <?php
            $in_section=true;
        }

        for ($i = 1; $i < strlen($ligne); $i++) {
            $mot .= $ligne[$i];
        }
        $mot = trim($mot, "\n");?>
        <h1><?php echo $mot?></h1>
    <?php
    }

     # LISTE
    elseif($ligne[0] == "-") {
        if(!$in_list) {
            ?> <ul> 
            <?php $in_list = true?>
            <?php
        }
        elseif($in_list) {
            ?> 
            <li> <?php echo substr($ligne, 1); ?> </li>
            
            <?php
        }
    }
    elseif($in_list && $ligne[0] != "-") {
        ?>
        </ul>
        <?php $in_list = false;
    }
    # TABLEAU
    elseif($ligne[0] == "|"){
        if ($in_table==false){
            $in_table=true;
            ?><table>   
                <thead>
                    <th>
                    <?php
                    for ($i = 2; $i < strlen($ligne); $i++) {
                        if ($ligne[$i-1]=="|"){
                            ?></th>
                            <?php
                            if ($i!=strlen($ligne)-1){
                                ?><th>
                            <?php
                            }
                        }else{
                            echo $ligne[$i-1];
                        }
                    }
                ?></thead><?php
        }elseif($ligne[1] != "-"){
            ?>  
                <tbody>
                    <td>
                    <?php
                    for ($i = 2; $i < strlen($ligne); $i++) {
                        if ($ligne[$i-1]=="|"){
                            ?></td>
                            <?php
                            if ($i!=strlen($ligne)-1){
                                ?><td>
                            <?php
                            }
                        }else{
                            echo $ligne[$i-1];
                        }
                    }
                ?></tbody><?php
        }

    }
    elseif($in_table==true){
        ?></table><?php
        $in_table=false;
    }

    elseif($ligne[0]=="`"){
        if($in_code==false){
            $in_code=true;
            ?><pre><code><?php
        }else{
            ?></pre></code><?php
            $in_code=false;
        }
    }
    elseif($in_code==true){
        echo $ligne;
    }

    else{
        $in_link1=false;
        $in_link2=false;
        $in_link3=false;
        $ind_mot=-1;
        for ($i = 0; $i < strlen($ligne); $i++){
            if($ligne[$i]=="["){
                $in_link1=true;
                $ind_mot=$i+1;
            }

            elseif($in_link1==true && $ligne[$i]=="("){
                ?><a href="<?php
                $in_link2=true;
            }
            elseif($in_link2==true){
                if($ligne[$i]==")"){
                    ?>"><?php
                    $in_link2=false;
                    $in_link3=true;
                    $ind_finParenthese=$i;
                }else{
                    echo $ligne[$i];
                }
            }
            elseif($in_link1==false){
                echo $ligne[$i];
            }
            if($ind_mot!=-1 && $in_link3==true){
                while($ligne[$ind_mot]!="]" && $ind_mot<strlen($ligne)){
                    echo $ligne[$ind_mot];
                    $ind_mot=$ind_mot+1;
                }
                
            }
        }
        if($in_link1==true){
            ?></a><?php
            echo substr($ligne,$ind_finParenthese+1);
        }else{
            ?><p><?php echo $ligne ?></p><?php ;
        }
    }


}
?>
</body>
