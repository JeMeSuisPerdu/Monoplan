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
 *
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
 * 
 * @code 
    Création d’un tableau de 3 tokens
    cell->token_count = 3;
    cell->tokens = malloc(cell->token_count * sizeof(s_token));
  @endcode
 */
typedef struct cell {
    char* content; /**  */
    double value; /**  */
    s_token* tokens; /** Tableau alloué dynamiquement ; Jetons créés à partir de l'analyse du contenu */
    int token_count; /** Nombre de jetons dans le tableau */
    struct cell** dependant_cells; /** Tableau de pointeurs des cellules qui dépendent de cette cellule */
    int dependant_cells_count; /** Nombre de cellules dépendantes */
} s_cell ;

// les fonctions qui utilisent la var globale
void analyseCell(s_cell * cell);
void evaluateCell(s_cell * cell);

#endif