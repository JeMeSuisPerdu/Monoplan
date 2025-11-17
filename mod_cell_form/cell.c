#include "cell.h"
#include <string.h>
#include <ctype.h>
#include "calcul_sheet.h"
#include "log.h"


s_cell* get_or_create_cell(int col,int line){
    if (line<0 || line >= global_sheet.lines || col <0 || col >= global_sheet.cols){
        LOG("Erreur : Indices de cellule hors limites (%d, %d)", line, col);
        return NULL;
    }

    if (global_sheet.cells[line][col] == NULL)
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


void change_content_cell(s_cell* cell, char* new_content) {
    // teste si la chaine passée est vide
    if (*new_content == '\0') { // si oui on fait pointer sur NULL
        if (cell->content != NULL) { // on vide la mémoire et pointe le pointeur vers NULL uniquement si il ne l'était pas déjà
            free(cell->content);
            cell->content = NULL;
        }
    } else {
        int taille_contenu = strlen(new_content);
        // si le contenu pointe vers NULL alors on malloc, sinon on realloc
        cell->content = (cell->content == NULL) ? malloc(taille_contenu * sizeof(char)) : realloc(cell, taille_contenu * sizeof(char));
        
        strcpy(cell->content, new_content);
    }
}


void analyse_cell(s_cell * cell){
    // initialise tableau de taill 50 pour les tokens
    cell->tokens = malloc(50 * sizeof(s_token));
    if (cell->tokens == NULL){
        LOG("Erreur d'allocation mémoire pour les tokens de la cellule");
        return;
    }

    char *string = cell->content;
    cell->token_count = 0;
    
    if (*string == '='){
        // hop on saute le =
        string++; 
    }

    while(*string != '\0'){

        if ( (*string >= '0' && *string <= '9') || *string == '.') {
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

        } else if ( (*string >= 'A' && *string <= 'Z') || (*string >= 'a' && *string <= 'z')){
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

        } else if (*string == '+' || *string == '-' || *string == '*' || *string == '/'|| *string == '%'){
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


void evaluate_cell(s_cell * cell){
    if (cell->tokens == NULL || cell->token_count == 0){
        LOG("Aucun token à évaluer dans la cellule");
        return;
    }

    my_stack_t* eval_stack = STACK_CREATE(cell->token_count, double);
    if (eval_stack == NULL){
        LOG("Erreur d'allocation mémoire pour la pile d'évaluation");
        return;
    }

    for(int i=0; i < cell->token_count; i++){
        if (cell->tokens[i].type == VALUE){
            STACK_PUSH(eval_stack, cell->tokens[i].value.cst, double);
            LOG("Token valeur empilée: %.2f", cell->tokens[i].value.cst);
        } else if (cell->tokens[i].type == REF){
            // DANS LE CAS OU C'EST UNE REF INVALIDE 
            s_cell * ref_cell = cell->tokens[i].value.ref;
            if (ref_cell == NULL){
                LOG("Référence de cellule invalide rencontrée lors de l'évaluation");
                STACK_PUSH(eval_stack, 0.0, double);
            }else{
                //CAS OU LA REF EST PAS EN DEHORS DES LIMITES DE LA FEUILLE DE CALCUL
                evaluate_cell(ref_cell); // évaluer la cell référencé avant d'utiliser sa valeur
                STACK_PUSH(eval_stack, ref_cell->value, double);
                LOG("Token référence empilée: %.2f", ref_cell->value);
            }          
        } else if (cell->tokens[i].type == OPERATOR){
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