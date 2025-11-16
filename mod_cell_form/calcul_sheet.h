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
    char operator_name;
    void (*operator_func)(my_stack_t*);
} s_operation;

extern s_operation operations[]; // toutes les operations dispo

void initialisation_sheet(int cols,int lines);
s_cell * get_or_create_cell(int col, int line);
void evaluateCell(s_cell * cell);
void analyseCell(s_cell * cell);
void operator_add(my_stack_t* stack);
void operator_subtract(my_stack_t* stack);
void operator_multiply(my_stack_t* stack);
void operator_divide(my_stack_t* stack);
void operator_modulo(my_stack_t* stack);

void (*find_operator_func(char operator_char))(my_stack_t*);


#endif