#include "cell.h"
#include <stdlib.h>
#include <stdio.h>
#include "log.h"
#include <ctype.h>
#include "calcul_sheet.h"
#include <string.h>



// la variable globale (dans .h)
s_calcul_sheet global_sheet;

// tab des operations dispo (dans .h)
s_operation operations[] = {
    {'+', operator_add},
    {'-', operator_subtract},
    {'*', operator_multiply},
    {'/', operator_divide},
    {'%', operator_modulo},
    {'\0', NULL} //fin tab operation
};

// UTILE POUR JALON 3 JE PENSE (init matrice de cellules)
void initialisation_sheet(int lines, int cols){
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

s_cell * get_or_create_cell(int line, int col){
    if(global_sheet.cells[line][col] == NULL)
    {
        s_cell* new_cell = malloc(sizeof(s_cell));

        new_cell->content = NULL;
        new_cell->value = 0.0;
        new_cell->tokens = NULL;
        new_cell->token_count = 0;
        new_cell->dependant_cells = NULL;
        new_cell->dependant_cells_count = 0;

        global_sheet.cells[line][col] = new_cell;
    }
    return global_sheet.cells[line][col];
}


/**
 * @brief Fonction d'analyse du contenu d'une cellule (galère à écrire)
 * @param cell Pointeur vers une cellule qui doit être analysée
 */
void analyseCell(s_cell * cell){
    // initialise tableau de 50 pour les tokens
    cell->tokens = malloc(50 * sizeof(s_token));
    if(cell->tokens == NULL){
        LOG_INFO("Erreur d'allocation mémoire pour les tokens de la cellule");
        return;
    }

    char *string = cell->content;
    cell->token_count = 0;
    
    if(*string == '='){
        // hop on saute le =
        string++; 
    }

    while(*string != '\0'){

        if( (*string >= '0' && *string <= '9') || *string == '.') {
            char *end_of_string;
            // convertit une chaîne en double
            double number = strtod(string, &end_of_string);
            
            s_token number_token;
            number_token.type = VALUE;
            number_token.value.cst = number;
            // ajoute token au tableau de tokens de la cellule
            cell->tokens[cell->token_count] = number_token;
            cell->token_count++;
            
            // avance le ptr de chaîne à endstring pour ne pas retraiter le nb
            string = end_of_string;
            LOG_INFO("Nombre trouvé et ajouté en tant que token: %f", number);

        } else if( (*string >= 'A' && *string <= 'Z') || (*string >= 'a' && *string <= 'z')){
            char* end_of_string;
            // ex : A12 ou a12 -> A -> 0
            int colonne = toupper(*string) - 'A';
            string++;
            
            // ex : A1 -> 0 (c'est mieux si on stock ca dans une matrice(ligne 1 = indice 0)
            int line = strtol(string, &end_of_string, 10)-1;
            
            s_token reference_token;
            reference_token.type = REF;
            reference_token.value.ref = get_or_create_cell(line, colonne);

            cell->tokens[cell->token_count] = reference_token;
            cell->token_count++;
            string = end_of_string;
            LOG_INFO("Référence de cellule trouvée et ajoutée en tant que token : %c", *string);

        } else if(*string == '+' || *string == '-' || *string == '*' || *string == '/'|| *string == '%'){
            s_token operator_token;
            operator_token.type = OPERATOR;
            operator_token.value.operator = find_operator_func(*string);
            cell->tokens[cell->token_count] = operator_token;
            cell->token_count++;
            string++;
            LOG_INFO("Opérateur trouvé et ajouté en tant que token");
        } else {
            // ignorer les espaces + caractères non reconnus
            string++;
        }
        
    }

}

/**
 * @brief Fonction d'évaluation d'une cellule
 * @param cell Pointeur vers une cellule qui doit être évaluée
 */
void evaluateCell(s_cell * cell){
    if(cell->tokens == NULL || cell->token_count == 0){
        LOG_INFO("Aucun token à évaluer dans la cellule");
        return;
    }

    my_stack_t* eval_stack = STACK_CREATE(cell->token_count, double);
    if(eval_stack == NULL){
        LOG_INFO("Erreur d'allocation mémoire pour la pile d'évaluation");
        return;
    }

    for(int i=0; i < cell->token_count; i++){
        if(cell->tokens[i].type == VALUE){
            STACK_PUSH(eval_stack, cell->tokens[i].value.cst, double);
            LOG_INFO("Token valeur empilée: %f", cell->tokens[i].value.cst);
        } else if(cell->tokens[i].type == REF){
            evaluateCell(cell->tokens[i].value.ref); // évaluer la cell référencé avant d'utiliser sa valeur
            STACK_PUSH(eval_stack, cell->tokens[i].value.ref->value, double);
            LOG_INFO("Token référence empilée: %f", cell->tokens[i].value.ref->value);
        } else if(cell->tokens[i].type == OPERATOR){
            // appel la fonction de l'opérateur avec la pile
            cell->tokens[i].value.operator(eval_stack);
            LOG_INFO("Opérateur appliqué");
        }
    }
    STACK_POP2(eval_stack, cell->value, double);
    LOG_INFO("Valeur finale de la cellule évaluée: %f", cell->value);

    // libèration de la pileeee
    STACK_REMOVE(eval_stack);
}

/**
 * @brief fonction add qui prend en param une pile et fait l'addition sur les deux derniers elements empilés
 * @param stack Une pile utilisée pour l'évaluation
 */

 void operator_add(my_stack_t* stack){
    double val1, val2,result;
    STACK_POP2(stack, val2, double);
    STACK_POP2(stack, val1, double);
    result = val1 + val2;
    STACK_PUSH(stack, result, double);
}

 /**
 * @brief fonction subtract qui prend en param une pile et fait la soustraction sur les deux derniers elements empilés
 * @param stack Une pile utilisée pour l'évaluation
 */

 void operator_subtract(my_stack_t* stack){
    double val1, val2,result;
    STACK_POP2(stack, val2, double);
    STACK_POP2(stack, val1, double);
    result = val1 - val2;
    STACK_PUSH(stack, result, double);
}

/**
 * @brief fonction multiply qui prend en param une pile et fait la multiplication sur les deux derniers elements empilés
 * @param stack Une pile utilisée pour l'évaluation
 */

 void operator_multiply(my_stack_t* stack){
    double val1, val2,result;
    STACK_POP2(stack, val2, double);
    STACK_POP2(stack, val1, double);
    result = val1 * val2;
    STACK_PUSH(stack, result, double);
}

/**
 * @brief fonction divide qui prend en param une pile et fait la division sur les deux derniers elements empilés
 * @param stack Une pile utilisée pour l'évaluation
 */

 void operator_divide(my_stack_t* stack){
    double val1, val2,result;
    STACK_POP2(stack, val2, double);
    STACK_POP2(stack, val1, double);
    result = val1 / val2;
    STACK_PUSH(stack, result, double);
}

/**
 * @brief fonction modulo qui prend en param une pile et fait le modulo sur les deux derniers elements empilés
 * @param stack Une pile utilisée pour l'évaluation
 */

 void operator_modulo(my_stack_t* stack){

    double val1, val2,result;
    STACK_POP2(stack, val2, double);
    STACK_POP2(stack, val1, double);
    result = (double)((int)val1 % (int)val2);
    STACK_PUSH(stack, result, double);
}


/**
    * @brief fonction find_operator_func qui prend un char,
    *  + retourne un pointeur vers une fonction qui (elle) prend un my_stack_t* et retourne void
    * @param operator_char pointeur de char représentant l'opérateur
    * @return Pointeur vers une fonction operator_... ou NULL si non trouvé
**/
void (*find_operator_func(char operator_char))(my_stack_t*) {
    for (int i = 0; operations[i].operator_name != '\0'; i++) {
        if (operations[i].operator_name == operator_char) {
            return operations[i].operator_func;
        }
    }
    return NULL;
}