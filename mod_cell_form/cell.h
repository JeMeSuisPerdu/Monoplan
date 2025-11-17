/** 
 * @headerfile list.h
 * @brief 
 */

#ifndef CELL_H
#define CELL_H

#include "../stack/stack.h"
#include <stdlib.h>

typedef struct cell s_cell;

/** 
 * @struct token
 * @brief Représente un jeton d'une cellule
 *
 */
typedef struct token {
    enum {VALUE, REF, OPERATOR} type ;
    union {
        double cst;
        s_cell* ref;
        void (*operator) (my_stack_t* eval); // pointeur vers une fonc qui a une pile(param) et ne retourne rien
    } value ;
} s_token ;


/** 
 * @struct cell
 * @brief Représente une cellule du tableur
 * 
 */
typedef struct cell {
    char* content; /**  */
    double value; /**  */
    s_token* tokens; /** Tableau alloué dynamiquement ; Jetons créés à partir de l'analyse du contenu */
    int token_count; /** Nombre de jetons dans le tableau */
    struct cell** dependant_cells; /** Tableau de pointeurs des cellules qui dépendent de cette cellule */
    int dependant_cells_count; /** Nombre de cellules dépendantes */
} s_cell ;

/**
 * @brief Fonction d'initialisation de la feuille de calcul qui est une matrice 
 * @param cols Nombre de colonnes
 * @param lines Nombre de lignes
 * @return Un pointeur vers la cellule trouvé ou crée !!!!
 */
s_cell * get_or_create_cell(int col, int line);

/** 
 * @brief Modifie le contenue d'une cellule
 * 
 */
void change_content_cell(s_cell* cell, char* content);

/**
 * @brief Fonction d'analyse du contenu d'une cellule (galère à écrire TwT)
 * @param cell Pointeur vers une cellule qui doit être analysée
 */
void analyse_cell(s_cell * cell);

/**
 * @brief Fonction d'évaluation d'une cellule
 * @param cell Pointeur vers une cellule qui doit être évaluée
 */
void evaluate_cell(s_cell * cell);

#endif