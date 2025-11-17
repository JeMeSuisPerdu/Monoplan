#include "cell.h"
#include <stdlib.h>
#include <stdio.h>
#include "log.h"
#include <ctype.h>
#include "calcul_sheet.h"
#include <string.h>



/**
 * @brief Variable extern de type structure s_calcul_sheet (dans .h)
 * Elle permet de faire appel à une feuille de calcul et à ses champs !! 
 */
s_calcul_sheet global_sheet;

/**
 * @brief Tableau de structure (type s_operation) extern (déclaré dans le .h)
 * qui stock les opérateur et fonctions associés manipulant la stack
 * @param cols Nombre de colonnes
 * @param lines Nombre de lignes
 */
s_operation operations[] = {
    {'+', operator_add},
    {'-', operator_subtract},
    {'*', operator_multiply},
    {'/', operator_divide},
    {'%', operator_modulo},
    {'\0', NULL} //fin tab operation
};

/**
 * @brief Fonction d'initialisation de la feuille de calcul qui est une matrice 
 * @param cols Nombre de colonnes
 * @param lines Nombre de lignes
 */
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

/**
 * @brief Fonction d'initialisation de la feuille de calcul qui est une matrice 
 * @param cols Nombre de colonnes
 * @param lines Nombre de lignes
 * @return Un pointeur vers la cellule trouvé ou crée !!!!
 */
s_cell * get_or_create_cell(int col,int line){
    if(line<0 || line >= global_sheet.lines || col <0 || col >= global_sheet.cols){
        LOG("Erreur : Indices de cellule hors limites (%d, %d)", line, col);
        return NULL;
    }

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
 * @brief Fonction d'analyse du contenu d'une cellule (galère à écrire TwT)
 * @param cell Pointeur vers une cellule qui doit être analysée
 */
void analyseCell(s_cell * cell){
    // initialise tableau de taill 50 pour les tokens
    cell->tokens = malloc(50 * sizeof(s_token));
    if(cell->tokens == NULL){
        LOG("Erreur d'allocation mémoire pour les tokens de la cellule");
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
            LOG("Nombre trouvé et ajouté en tant que token: %.2f", number);

        } else if( (*string >= 'A' && *string <= 'Z') || (*string >= 'a' && *string <= 'z')){
            char* end_of_string;
            // ex : A12 ou a12 -> A -> 0
            int colonne = toupper(*string) - 'A';
            string++;
            
            // ex : A1 -> 0 (c'est mieux si on stock ca dans une matrice(ligne 1 = indice 0)
            int line = strtol(string, &end_of_string, 10)-1;
            
            s_token reference_token;
            reference_token.type = REF;
            reference_token.value.ref = get_or_create_cell(colonne, line);

            cell->tokens[cell->token_count] = reference_token;
            cell->token_count++;
            string = end_of_string;
            LOG("Référence de cellule trouvée et ajoutée en tant que token : %c", *string);

        } else if(*string == '+' || *string == '-' || *string == '*' || *string == '/'|| *string == '%'){
            s_token operator_token;
            operator_token.type = OPERATOR;
            operator_token.value.operator = find_operator_func(*string);
            cell->tokens[cell->token_count] = operator_token;
            cell->token_count++;
            LOG("Opérateur trouvé et ajouté en tant que token : %c", *string);
            string++;
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
        LOG("Aucun token à évaluer dans la cellule");
        return;
    }

    my_stack_t* eval_stack = STACK_CREATE(cell->token_count, double);
    if(eval_stack == NULL){
        LOG("Erreur d'allocation mémoire pour la pile d'évaluation");
        return;
    }

    for(int i=0; i < cell->token_count; i++){
        if(cell->tokens[i].type == VALUE){
            STACK_PUSH(eval_stack, cell->tokens[i].value.cst, double);
            LOG("Token valeur empilée: %.2f", cell->tokens[i].value.cst);
        } else if(cell->tokens[i].type == REF){
            // DANS LE CAS OU C'EST UNE REF INVALIDE 
            s_cell * ref_cell = cell->tokens[i].value.ref;
            if(ref_cell == NULL){
                LOG("Référence de cellule invalide rencontrée lors de l'évaluation");
                STACK_PUSH(eval_stack, 0.0, double);
            }else{
                //CAS OU LA REF EST PAS EN DEHORS DES LIMITES DE LA FEUILLE DE CALCUL
                evaluateCell(ref_cell); // évaluer la cell référencé avant d'utiliser sa valeur
                STACK_PUSH(eval_stack, ref_cell->value, double);
                LOG("Token référence empilée: %.2f", ref_cell->value);
            }          
        } else if(cell->tokens[i].type == OPERATOR){
            // appel la fonction de l'opérateur avec la pile
            cell->tokens[i].value.operator(eval_stack);
            LOG("Opérateur appliqué avec succès !!!");
        }
    }
    STACK_POP2(eval_stack, cell->value, double);
    LOG("Valeur finale de la cellule évaluée: %.2f", cell->value);

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
    * @param operator_char char représentant l'opérateur
    * @return Pointeur vers une fonction operator_... ou NULL si non trouvé
**/
void (*find_operator_func(char operator_char))(my_stack_t*) {
    int i = 0;
    while(operations[i].operator_name != '\0') {
        if (operations[i].operator_name == operator_char) {
            return operations[i].operator_func;
        }
        i++;
    }
}