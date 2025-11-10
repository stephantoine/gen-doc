#!/bin/bash
read -p "Quel est votre nom ? " nom
if [ "$nom" = "" ]
then
	echo Bonjour inconnu.e
else
	echo Bonjour $nom
fi
