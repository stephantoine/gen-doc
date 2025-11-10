[__]c’est une machine virtuelle
[__] c’est un Système d’Exploitation
[__] on doit installer un Système d’Exploitation dans chaque conteneur
[__] nécessite un ordinateur physique pour fonctionner
[X] nécessite un ordinateur logique pour fonctionner
[X] nécessite un hôte sous Linux
[X] un conteneur est un processus
[X] un conteneur est un espace confiné où s’exécutent un ou des processus

Q1- containerd-shim, systemd 
PID de tictac : 35290

Q2- non elle est isolée

Q3- le conteneur a affiché la localisation de tictac
Non la commande which ne tourne pas

Un conteneur et le processus qui s’exécute à l’intérieur du conteneur sont la
même chose.
Ce qui le différencie des autres processus du système hôte est qu’il a une vision très
restreinte du monde dans lequel il vit, dans lequel il s’exécute :
• Il ne voit que les fichiers qui sont dans le conteneur.
• Il ne voit que les autres processus qui ont été lancés (généralement par lui d’ailleurs)
dans le conteneur.


Q4- il a affiché les processus qui tournent dans le container

Q5- la commande a affiché plus en détail les processus qui sont en train de tourner, ainsi que les processus "cachés", oui la commande which tictac est apparente 

Q6- non je n'y arrive pas 

Q7- le processus s'est arrêté

Q8- le porcessus s'est relancé, cependant rien ne s'affiche dans T1

Q9- non il n'a pas reprit

Q10- which tictac, oui il est présent

Q11- oui il est en cours