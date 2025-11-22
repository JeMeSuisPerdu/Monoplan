#include "cell.h"
#include <stdlib.h>
#include <stdio.h>
#include "log.h"
#include "calcul_sheet.h"
#include <string.h>

s_calcul_sheet global_sheet;

s_operation operations[] = {
    {'+', operator_add},
    {'-', operator_subtract},
    {'*', operator_multiply},
    {'/', operator_divide},
    {'%', operator_modulo},
    {'\0', NULL} //fin tab operation
};


void initialisation_sheet(int cols,int lines){
    global_sheet.lines = lines;
    global_sheet.cols = cols;

    // allocation de la matrice de pointeurs de cellules
    global_sheet.cells = malloc(lines * sizeof(s_cell**));
    for(int i = 0; i < lines; i++){
        global_sheet.cells[i] = malloc(cols * sizeof(s_cell*));
        for(int j = 0; j < cols; j++){
            global_sheet.cells[i][j] = NULL;
        }
    }
}


void operator_add(my_stack_t* stack){
    double val1, val2,result;
    STACK_POP2(stack, val2, double);
    STACK_POP2(stack, val1, double);
    result = val1 + val2;
    STACK_PUSH(stack, result, double);
}


void operator_subtract(my_stack_t* stack){
    double val1, val2,result;
    STACK_POP2(stack, val2, double);
    STACK_POP2(stack, val1, double);
    result = val1 - val2;
    STACK_PUSH(stack, result, double);
}


void operator_multiply(my_stack_t* stack){
    double val1, val2,result;
    STACK_POP2(stack, val2, double);
    STACK_POP2(stack, val1, double);
    result = val1 * val2;
    STACK_PUSH(stack, result, double);
}


void operator_divide(my_stack_t* stack){
    double val1, val2,result;
    STACK_POP2(stack, val2, double);
    STACK_POP2(stack, val1, double);
    result = val1 / val2;
    STACK_PUSH(stack, result, double);
}


void operator_modulo(my_stack_t* stack){
    double val1, val2,result;
    STACK_POP2(stack, val2, double);
    STACK_POP2(stack, val1, double);
    result = (double)((int)val1 % (int)val2);
    STACK_PUSH(stack, result, double);
}


void (*find_operator_func(char operator_char))(my_stack_t*) {
    int i = 0;
    while(operations[i].operator_name != '\0') {
        if (operations[i].operator_name == operator_char) {
            return operations[i].operator_func;
        }
        i++;
    }
}

int free_global_sheet(){
    if(global_sheet.cells ==NULL){
        LOG("ERREUR : tentative de libérer une feuille de calcul vide ou non initialiser !!!");
        return 0;
    }
    // je parcours les lignes + liberation contenu cellule + liberation de la ligne entière
    for(int i=0; i<global_sheet.lines;i++){
        if(global_sheet.cells[i] != NULL){
            for (int j = 0; j < global_sheet.cols; j++)
            {
                s_cell * current_cell = global_sheet.cells[i][j];
                if(current_cell != NULL){
                    if(current_cell->content != NULL) free(current_cell->content);
                    if(current_cell->tokens != NULL) free(current_cell->tokens);
                    free(current_cell);
                }
            }
            
            free(global_sheet.cells[i]);
        }
    }
    
    //libère feuille cal
    free(global_sheet.cells);
    
    global_sheet.cells = NULL;
    global_sheet.lines =0;
    global_sheet.cols =0;
    return 1;
}