#!/bin/bash
read -p "Quel est votre fichier ? " nom
if [ -f $nom ]
then
	echo erreur
else
	touch $nom
fi
