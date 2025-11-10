#include <stdio.h>
#include <string.h> 
#include <math.h>
#include <time.h>
#include <stdbool.h> //boolean
#include <stdlib.h>  //for system()


#define NB_COLONNE 7
#define NB_LIGNE 6
#define VIDE '.'
#define JOUEUR_PIECE 'X'
#define AI_PIECE 'O'

#define DEBUG false

typedef char Grille[6][7];
typedef int Coups[7];
typedef char Liste[10];

struct Minimax_struct{
    int score, colonne;
};

struct score_struct{
    int nombre, joueur;
};


//entete
void initialiseGrille(Grille grille);
void afficheGrille(Grille grille);
bool est_valide_colonne(Grille grille, int colonne);
int choisirColonne(Grille grille, char pion);
int cherche_ligne(Grille grille, int colonne);
void conversion_filtre(char filtre[], int nb_element, char pion);
void jouer(Grille grille, int ligne, int colonne, char pion);




int main()
{
    
    
    Grille grille;
    Coups coups;
    char gagnant = '.'; 
    char joueur_courant;
	int colonne, ligne;
    struct Minimax_struct minimax_value;
    
	
	//defini mon joueur courant
    joueur_courant = JOUEUR_PIECE;
    
    
    colonne = -1;
    ligne = -1;
    
	//initialise ma liste de coup
    memset( coups, -1, NB_COLONNE );
    
    initialiseGrille(grille);
    afficheGrille(grille);
    
    while (gagnant == '.'){
        if(joueur_courant == JOUEUR_PIECE){
            
            
			//mode joueur 
            //colonne = choisirColonne(grille, joueur_courant);
            //while (colonne == -1){
            //    colonne = choisirColonne(grille, joueur_courant);
            //}
            
            
            //mode automatique 
            minimax_value = minimax(grille, 3, true, JOUEUR_PIECE);
            colonne = minimax_value.colonne;
            
            
        }else{
            //mise en oeuvre de minimax
            minimax_value = minimax(grille, 5, true, AI_PIECE);
            colonne = minimax_value.colonne;
        }
        
        ligne = cherche_ligne(grille, colonne);
        jouer(grille, ligne, colonne, joueur_courant);
        afficheGrille(grille);
        
        if(est_gagnant(grille, joueur_courant) == true){
            gagnant = joueur_courant;
        }
        
        if(joueur_courant == JOUEUR_PIECE){
            joueur_courant = AI_PIECE;
        }else{
            joueur_courant = JOUEUR_PIECE;
        }
    }
    
    printf("le joueur %c est gagnant\n", gagnant);
    return 0;
}
 


//initialise la grille
void initialiseGrille(Grille grille){
    int colonne, ligne;
    for(ligne = NB_LIGNE - 1 ; ligne >=0 ; ligne--){
        for(colonne = 0; colonne < NB_COLONNE; colonne++){
            grille[ligne][colonne] = VIDE;
            
        }
    }
    
}

//procedure pour afficher le plateau de jeu
void afficheGrille(Grille grille){
    int colonne, ligne;
    int boucle;
    
	
    //system("clear"); /*clear pour linux, cls pour windows*/
    
    for(ligne = NB_LIGNE - 1 ; ligne >=0 ; ligne--){
        boucle = 0 ;
        while(boucle++ < NB_COLONNE) printf("+---"); 
        
        printf("+\n");
        
        for(colonne = 0; colonne < NB_COLONNE; colonne++){
            printf("| %c ", grille[ligne][colonne]);
            
        }
        printf("|\n");
    }
    
    boucle = 0 ;
    while(boucle++ < NB_COLONNE) printf("+---"); 
    printf("+\n");
}

// controle si une colonne est valide
bool est_valide_colonne(Grille grille, int colonne){
    
    if(grille[NB_LIGNE - 1][colonne] == VIDE){
        return true;
    }else{
        return false; 
    }
     
}

//choisir une colonne
int choisirColonne(Grille grille, char pion){
    int colonne = 0;
    
    printf("Joueur %c : sélectionner votre colonne entre (0 - %d)\n", pion, NB_COLONNE-1);
    scanf("%d", &colonne);
    
       
    if (colonne >= 0 || colonne < NB_COLONNE){
        if (est_valide_colonne(grille, colonne) == true){
            return colonne;
        }else{
            return -1;
        }
        
    }else{
        return -1;
    }
    
    return colonne;
}

//recherche la ligne disponible de la colonne
int cherche_ligne(Grille grille, int colonne){
    bool boolVide = false;
    int ligne = 0;
    
    while(boolVide == false && ligne < NB_LIGNE){
        if(grille[ligne][colonne] == VIDE){
            boolVide = true;
        }else{
            ligne ++;
        }
    }
    
    if(boolVide == false){
        return -1;
    }else{
        return ligne;
    }
}


//jouer
void jouer(Grille grille, int ligne, int colonne, char pion){
    grille[ligne][colonne] = pion;
}


//conservion de mon filtre
void conversion_filtre(char filtre[], int nb_element, char pion){
    for(int i=0; i<nb_element; i++){
        if(filtre[i] == 'P'){
            filtre[i] = pion;
        }
    }
}
