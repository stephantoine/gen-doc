/**
* \brief Programme du jeu du sudoku
*
* \author ANTOINE Stéphane
*
* \version 1.0
*
* \date 1 décembre
*
* Ce programme permet à un joueur de compléter une grille de sudoku tout en respectant les règles
*/


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/**
* \def N
* \brief taille d'une sous grille
*
* correspond au nombre de blocs du sudoku et à la taille d'un bloc
*
*/

#define N 3

/**
* \def TAILLE
* \brief Taille maximale d’un tableau (N*N).
*
* correspond à la taille du sudoku, nombre de lignes, de colonnes, de blocs
*
*/

#define TAILLE 9


/**
* \typedef tGrille
* \brief Type tableau à 2 dimensions 
*
* le tableau est de taille TAILLE*TAILLE et contiendra N blocs
*
*/

typedef int tGrille[TAILLE][TAILLE];

typedef struct  {
    int valeur1; /** valeur rentrée pour la colonne*/
    int valeur2; /** valeur rentrée pour la ligne*/
    int valeur3; /** valeur donnée par l'utilisateur à mettre dans la grille*/
} valeur_rentree;

typedef struct  {
    char nomFamille[10]; /** nom de la personne*/
    char prenom[10]; /** prenom de la personne*/
    char adresse[20]; /** adresse de la personne*/
    int age; /** valeur donnée par l'utilisateur à mettre dans la grille*/
} identite;

int nbLig; /** nombre de lignes du tableau */
int nbCol; /** nombre de colonnes du tableau */

// Déclaration des entêtes de fonctions et de procédures
void chargerGrille(tGrille);
void afficherGrille(tGrille);
void saisir(int *);
bool possible(tGrille, int, int, int);
void separer();
bool pleine(tGrille);
 
/**
* \fn int main()
*
* \brief programme principal qui va permettre au joueur de jouer au sudoku
*
* \return code de sortie du programme (EXIT_SUCCESS: sortie normale).
*
* Le main va charger une grille, et tant que cette grille est vide il va faire jouer le joueur pour qu'il remplisse la grille,
* jusqu'a qu'elle soit pleine ou qu'il ne puisse plus ajouter de valeur, à chaque fois la grille va être afficher
*
*/

int main(){
    tGrille grille1;
    int numLigne, numColonne, valeur;

    chargerGrille(grille1);
    
    while(pleine(grille1)==false){
        afficherGrille(grille1);
        printf("Indices de la case ? \n");
        printf("Numéro de ligne, ");
        saisir(&numLigne);
        printf("Numéro de colonne, ");
        saisir(&numColonne);

        if (grille1[numLigne-1][numColonne-1]!=0){
            printf("IMPOSSIBLE, la case n'est pas libre.\n");   
        }

        else{
            printf("Valeur à insérer ? ");
            saisir(&valeur);

            if (possible(grille1, numLigne-1, numColonne-1, valeur)){
                grille1[numLigne-1][numColonne-1] = valeur;             
            }
        }
    }
    afficherGrille(grille1);
    printf("Grille pleine, fin de partie\n");

    return EXIT_SUCCESS;
}

/**
* \fn chargerGrille(tGrille g)
*
* \brief Charge une grille depuis un fichier binaire
*
* \param g : paramètre d'entrée/sortie qui représente la grille de sudoku
*
* demande le nom du fichier à charger et rempli la grille prise en entrée, en mettant des 0 quand les cases sont vides
* 
*/

void chargerGrille(tGrille g){
    char nomFichier[30];
    FILE * f;

    printf("Nom du fichier ? ");
    scanf("%s", nomFichier);
    f = fopen(nomFichier, "rb");

    if (f==NULL){
        printf("\n ERREUR sur le fichier %s\n", nomFichier);
    } 

    else {
        fread(g, sizeof(int), TAILLE*TAILLE, f);
    }

    fclose(f);
}

/**
* \fn afficherGrille(tGrille g)
*
* \brief Affiche la grille de sudoku
*
* \param g : paramètre d'entrée/sortie qui représente la grille de sudoku
*
* fait appel à la procédure serparer, et affiche chaque case de la grille, en délimitant chaque bloc
*/

void afficherGrille(tGrille g){
    int lig, col, noCol, x, y;

    lig = 0;
    col = 0;
    noCol = 1;

    printf("      ");
    for(x = 0; x<N; x++){   // affichage de la bande des numéros de colonnes
        for(y=0; y<N; y++){
            printf(" %d ", noCol);
            noCol++;
        }
        printf(" ");
    }
    printf("\n");  

    for (lig=0; lig<TAILLE; lig++){
        printf("   ");
        if (lig%N == 0){    //affiche les lignes qui séparent les blocs
            separer();
            printf("   ");
        }

        printf("%d ", lig+1);

        for (col=0; col<TAILLE; col++){
            if (col%N == 0){    //affiche les colonnes qui séparent les blocs
                printf("|");
            }
            if (g[lig][col] == 0){  //remplace les 0 par des "."
                printf(" . ");
            }
            else{
                printf(" %d ", g[lig][col]); 
            }
        }
        printf("|\n");
    }
    printf("   ");
    separer();
}

/**
* \fn saisir(int *s)
*
* \brief Saisie d'une valeur en s'assurant qu'elle est valide
*
* \param s : paramètre d'entrée/sortie qui représente la valeur à vérifier
*
* \return un entier, qui correspond à la valeur valide prise en entrée 
*
* Vérifie que la valeur est bien un entier compris entre 1 et N**2
*/

void saisir(int *s){
    int valeur;
    char ch[2];
    printf("Donnez la valeur : ");
    scanf("%s", ch);
    if (sscanf(ch, "%d", &valeur) !=0){
        if (valeur < 1 || valeur > N*N){    //valeur non comprise entre 1 et N
            printf("Erreur valeur non comprise entre 1 et %d\n", N*N); 
            saisir(&*s);
        }
        else{
            *s = valeur;    //valeur valide
        }
    } 
    else {
        printf("Veuillez à insérer un entier\n");   //valeur qui ne correspond pas à un entier
        saisir(&*s);
    }
}

/**
* \fn possible(tGrille g, int noLigne, int noColonne, int valeur)
* \brief Vérifie si une valeur peut être placée dans une position donnée de la grille
* \param g : paramètre d'entrée/sortie qui représente la grille de sudoku
* \param noLigne: paramètre d'entrée qui représente le numéro de ligne
* \param noColonne: paramètre d'entrée qui représente le numéro de colonne
* \param valeur: paramètre d'entrée qui représente la valeur à vérifier
* \return un booléen, vrai quand la valeur peut être placée à la position donnée, ou faux s'il elle ne peut pas
*
* vérifie si la valeur est déjà présente dans la ligne, sinon dans la colonne, sinon dans le bloc
*/

bool possible(tGrille g, int noLigne, int noColonne, int valeur){
    int i, j;

    // Vérifie la ligne
    for (i = 0; i < TAILLE; i++) {
        if (g[noLigne][i] == valeur){
            printf("Erreur : valeur déjà présente dans la ligne\n");
            return false;
        }
    }

    // Vérifie la colonne
    for (i = 0; i < TAILLE; i++) {
        if (g[i][noColonne] == valeur){
            printf("Erreur : valeur déjà présente dans la colonne\n");
            return false;
        }
    }

    // Détermine le coin supérieur gauche du bloc
    noLigne = (noLigne/N)*N;
    noColonne = (noColonne/N)*N;

    // Vérifie le bloc
    for(i=noLigne; i<noLigne+N; i++){
        for(j=noColonne; j<noColonne+N; j++){
            if(valeur == g[i][j]){
                printf("Erreur : valeur déjà présente dans le bloc\n");
                return false;
            }
        }
    }
    return true;
}


/**
* \fn pleine(tGrille g)
* \brief Vérifie si la grille est pleine
* \param g : paramètre d'entrée/sortie qui représente la grille de sudoku
* \return un booléen, vrai quand la grille est pleine et faux sinon
*
* Vérifie la présence de 0 dans la grille 
*
*/

bool pleine(tGrille g){
    bool pleine = true;
    int i, j;
    for (i=0; i<TAILLE; i++){
        for (j=0; j<TAILLE; j++){
            if (g[i][j]==0){
                pleine = false;
            }
        }
    }
    return pleine;
}


/**
* \fn separer()
* \brief Affiche une ligne de séparation dans la grille
*
* Affichage de + et de - pour séparer les lignes du sudoku pour une meilleure visibilité
*
*/

void separer(){
    int x;
    int y;
    printf("  ");
    for(x=0; x<N; x++){
        printf("+");
        for(y=0; y<TAILLE; y++){
            printf("-");
        }
    }
    printf("+\n");
}
