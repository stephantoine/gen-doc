/**
 * \page Général 
 * 
 * \author TIPREZ Tuan
 * \version 1.0
 * \date 5 Décembre 2023
 *
 * Développement d'un programme Quizlet-like.
 * Ce programme permettera de créer une série de "carte" retournable
 * permettant de mettre un terme et sa définition pour s'entrainer avec. 
 * 
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/**
* \def T_CHAINE
* \brief Taille max d'une chaine de caractère
*
* Nombre max de caractère que peut entrer l'utilisateur.
*/
#define T_CHAINE 500
/**
* \def T_NOM_DECK 
* \brief TAille max du nom d'un deck
*
* Nombre max de caractère que peut entrer l'utilisateur lorsqu'il s'agit du nom d'un deck
*/
#define T_NOM_DECK 20
/**
* \def NB_DECK
* \brief Nombre de deck maximal
*
* Nombre maximal de deck que on peut avoir en 1 fichier.
*/
#define NB_DECK 20


// Typedef
/**
* \struct s_carte
* \brief Structure d'une carte
*
* Une carte est composé de deux chaines de caractères.
*/
typedef struct {
    char recto[T_CHAINE];
    char verso[T_CHAINE];
} s_carte;


/**
* \struct s_deck
* \brief Structure d'un deck
*
* Un deck est composé d'un nom, d'un tableau de s_carte et d'un entier qui correspond au nombre de carte
* présent dans le deck.
*/
typedef struct {
    char nom_deck[T_CHAINE];
    s_carte *tdeck;
    int nb_carte;
} s_deck;

/**
* \typedef t_allDecks
* \brief Tableau composé de s_deck
*
* Tableau de taille NB_DECK qui contient des éléments s_deck.
*/
typedef s_deck t_allDecks[NB_DECK];


s_carte creerCarte();
void ajouterCarte(s_carte carte, s_deck *deck);
void afficherDeck(s_deck *deck);
void afficherCarte(s_carte carte);
void nomDeckActuel(s_deck *deck);
void renommerDeck(s_deck *deck);
void menu();
void viderBuffer();
void lire(char *chaine, int longueur);


/************************************************
*               PROGRAMME PRINCIPAL             *
*************************************************/

/**
* \fn int main(int argc, char const *argv[])
* \brief Programme principal.
* \return Code de sortie du programme (0 : sortie normale).
* 
* Le programme principal permet toutes les actions principales tel que créer un deck, s'entrainer avec
* ou l'afficher. 
*/
int main(int argc, char const *argv[])
{
    char input[T_CHAINE];
    int choix;

    int nb_deck = 1;

    bool estEnCours = true;

    t_allDecks decks_utilisateur;
    s_deck deckactuel = {.tdeck = malloc(sizeof(s_carte)), .nb_carte = 0};
    s_carte carte;

    // Si un fichier est ouvert on l'assigne directemetn à deckactuel
    if (argc > 1) {
        if (argc > 2) {
            fprintf(stderr, "[ERRORS]\nTrop d'arguments !");
            exit(1);
        }
        else {
            printf("[DEBUG]\nPas encore fais !");
            exit(0);
        }
    }
    else {
            strcpy(deckactuel.nom_deck, "temp");
    }

    while (estEnCours)
    {

        nomDeckActuel(&deckactuel);
        menu();
        printf("\nQue voulez vous faire ? ");
        lire(input, 3);

        if (sscanf(input, "%d", &choix) == 1) {
            /***********    CHOIX    ***********/
            switch (choix){

                // Creer une nouvelle carte
                case 1 :
                    printf("Création d'une carte...\n\n");

                    carte = creerCarte();
                    ajouterCarte(carte, &deckactuel);
                    printf("\nCarte correctement ajouter !\n");
                    break;
                
                // Afficher deck actuel
                case 2 :
                    if (deckactuel.nb_carte == 0)
                        printf("[INFO]\nDeck vide."); 
                    else {
                        printf("\nAffichage du deck %s: \n", deckactuel.nom_deck);
                        afficherDeck(&deckactuel);
                    }
                    break;
                
                // Retirer une carte
                case 3 :
                    afficherDeck(&deckactuel);
                    break;

                // Renommer le deck 
                case 4 :
                    renommerDeck(&deckactuel);
                    break;

                // S'entrainer avec ce deck
                case 5 :
                    break;

                // Enregistrer le deck
                case 6 :
                    break;

                // Charger le deck
                case 7 :
                    break;

                // Quitter
                case -1 :
                    estEnCours = false;
                    break;

                // Valeur inconnu
                default:
                    printf("[WARNING]\nValeur inconnue.");
                    break;
            }
        }
        else {
            fprintf(stderr, "[ERRORS]\nSaisie incorrecte.");
        }
    }

    free(deckactuel.tdeck);

    printf("[INFO]\nFin du programme.");
    return 0;
}


// Creer une carte
/**
* \fn s_carte creerCarte()
* \brief Creation d'une carte dans le deck actuel
* \return Renvoie une structure carte
* 
* Permet de créer une structure carte et d'entrée ce qui sera ecrit dans ses champs
*/
s_carte creerCarte() {

    char chaine[T_CHAINE];
    s_carte carte;

    printf("%-10s : ", "Terme");
    lire(carte.recto, T_CHAINE);
    printf("%-10s : ", "Définition");
    lire(carte.verso, T_CHAINE);

    return carte;
}

// Ajoute une carte au deck
/**
* \fn void ajouterCarte(s_carte carte, s_deck *deck)
* \brief Ajoute une carte à un deck
* \param carte Carte à ajouter
* \param deck Deck où on ajoute la carte
* 
* Ajoute une structure s_carte dans le tableau du champ tdeck de la structure s_deck 
* et incrémente le nombre de carte.
*/
void ajouterCarte(s_carte carte, s_deck *deck) {
    deck->nb_carte++;

    // Réallocation de la taille mémoire
    deck->tdeck = realloc(deck->tdeck, deck->nb_carte * sizeof(s_carte));

    deck->tdeck[deck->nb_carte-1] = carte;
}

// Affiche toute les cartes d'un deck
/**
* \fn void afficherDeck(s_deck *deck)
* \brief Afficher les cartes d'un deck
* \param deck Deck à afficher
* 
* Affiche toute les cartes contenu dans le champ tdeck de la structure s_deck entrée en paramètre
*/
void afficherDeck(s_deck *deck) {
    for (int i = 0; i < deck->nb_carte; i++) {
        printf("\t%-5s -Carte %d- \n", "", i);
        afficherCarte(deck->tdeck[i]);
        printf("\t------------------------------\n");
    }
}

// Affiche une carte
/**
* \fn void afficherCarte(s_carte carte)
* \brief Affiche la carte entrée en paramètre.
* \param carte Carte à ajouter
* 
* Affiche le terme et la définition d'une structure s_carte entrée en paramètre.
*/
void afficherCarte(s_carte carte) {
    printf("\t%-10s : %s\n", "Terme", carte.recto);
    printf("\t%-10s : %s\n", "Définition", carte.verso);
}

// Affichage du menu de choix
/**
* \fn void menu()
* \brief Affiche le menu principal.
* 
* Affiche le menu qui liste toute les actions possibles
*/
void menu() {
    printf("\n\t---------- Menu ----------\n");
    printf("\n\t1 - Creer nouvelle carte");
    printf("\n\t2 - Afficher le deck actuel");
    printf("\n\t3 - Retirer une carte");
    printf("\n\t4 - Renommer le deck");
    printf("\n\t5 - S'entrainer avec ce deck");
    printf("\n\t6 - Enregistrer le deck");
    printf("\n\t7 - Charger un deck");
    printf("\n\t-1 - Quitter\n");
    printf("\n\t--------------------------\n");
}


// Affiche le nom du deck actuel
/**
* \fn void nomDeckActuel(s_deck *deck)
* \brief Affiche le nom du deck entrée en paramètre.
* \param deck deck que l'on veut afficher le nom.
*
* Affiche le champ nom_deck de la structure s_deck.
*/
void nomDeckActuel(s_deck *deck) {
    printf("\n\tDeck actuelle : \"%s\"\n", deck->nom_deck);
}


// Vide le buffer
/**
* \fn void viderBuffer()
* \brief Vide le buffer.
*/
void viderBuffer() {
    int c = 0;
    while(c = getchar() != EOF);
}


/**
* \fn int lire(char *chaine, int longueur)
* \brief Lecture d'entrée clavier sécurisée
* \param chaine   Variable où sera stocké l'entrée clavier de l'utilisateur 
* \param longueur Entier qui représente la longueur max de la chaine.
*
* Scanf sécurisé contre l'overflow.
*/
void lire(char *chaine, int longueur) {

    char *positionEntree = NULL;

    if (fgets(chaine, longueur, stdin) != NULL) {

        positionEntree = strchr(chaine, '\n');
        if (positionEntree != NULL) {
            *positionEntree = '\0';
        }
        else {
            viderBuffer();
        }
    }
    else {

        viderBuffer();
    }
}

// Renomme le deck
/**
* \fn void renommerDeck(s_deck *deck)
* \brief Change le nom du deck entré en paramètre
* \param deck Structure s_deck ciblée.
*
* Change le champ nom_deck de la structure s_deck entrée en paramètre
*/
void renommerDeck(s_deck *deck) {
    char input[T_NOM_DECK];
    printf("Nouveau nom du deck (20 caractères max): ");
    lire(input, T_NOM_DECK);
    strcpy(deck->nom_deck, input);
}