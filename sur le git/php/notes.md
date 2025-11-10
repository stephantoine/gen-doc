**Doit commencer tout le temps comme ca :**  
#![which php]

```sh
<?php

?>
```


## Variables :  
* \$nom -> $ pour déclarer et appeler

### Types :  
* Chaînes
* Flottants
* Entiers
*   Booléens
*   Tableaux

### Opérateurs

#### Arithmétiques
* \+
* \-
* \*
* /
* %
* \*\*

#### Opérateurs logiques
* &&
* ||
* !

#### Opérateurs de chaîne
* **.** --> concaténation

#### Opérateurs de réaffection 
* +=
* -= 
* *=
* /=
* %=
* .=

## Structures de Contrôle

### Condition if
```sh
if (condition) {
    ...
}
else if () {
    ...
}
else {
    ...
}
```

### Boucles for
```sh
for ($boucle = 1; $boucle < 10; $boucle++)
```

### Boucles while et do... while
```sh
while (condition) {
    ...
}
```
```sh
do {
    ....
} while(condition)
```

## Conditions et comparaisons

### Opérateurs de comparaison
* ==
* !=
* <=
* \>=
* <
* \>

### Mixage des types
PHP peut comparer des chaînes avec des valeurs numériques. Ainsi :
* 12 == "12" --> True

Aussi : 
* echo 10 * "1e2"; --> 1000 (car 1e2 est 100 en notation scientifique)
* .1 --> 0.1

### Comparaisons strictes 
* ===
* !==

## Tableaux
Il existe plus de 80 fonctions dédiées aux tableaux dans le language PHP.

### Déclaration
```sh
$tablo = []
```

### Affectation
```sh
$depts = [
    22 => "Côtes d'Armor",
    29 => "Finistères",
    35 => "Ille-et-Vilaine",
    56 => "Morbihan",
];
```

#### print_r($tab)
Affiche le contenu de la variable.
Pour du debug.

### Ajout/Remplacement
```sh
$depts[22] = "Aodou An Arvoir";
```
Ajoute "Aoudou An Arvoir" avec la clé 22.
Si la clé 22 existe déjà, la remplace.  
  
### Parcours
```sh
foreach ($depts as $num => $nom) {
    echo "Le département $num s'appelle $nom\n";
}
```
* Associe la clé à $num et la valeur à $nom
```sh
foreach ($depts as $nom) {
    echo "Le département s'appelle $nom\n";
}
```
* Prend uniquement la valeur et l'associe à $nom