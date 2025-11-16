#ifndef CALCUL_SHEET_H
#define CALCUL_SHEET_H
#include "cell.h"

// LA FEUILLE DE CALCUL
typedef struct calcul_sheet {
    char * filename;
    int lines;
    int cols;
    s_cell *** cells; // matrice de pointeurs de cellules
} s_calcul_sheet ;

// la var globale de la feuille de calcul !!!!!!
extern s_calcul_sheet global_sheet;

// UNE OPERATIONNNNN
typedef struct {
    char* operator_name;
    void (*operator_func)(my_stack_t*);
} s_operation;

extern s_operation operations[]; // toutes les operations dispo



#endif