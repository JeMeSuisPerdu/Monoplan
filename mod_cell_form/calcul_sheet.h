#ifndef CALCUL_SHEET_H
#define CALCUL_SHEET_H
#include "cell.h"


/**
 * @struct calcul_sheet
 * @brief Représente la feuille de calcul
 * Contient le nom du fichier, le nombre de lignes et de colonnes et une matrice de pointeurs de cellules
 */
typedef struct calcul_sheet {
    char * filename;
    int lines;
    int cols;
    s_cell *** cells; // matrice de pointeurs de cellules
} s_calcul_sheet ;

/**
 * @brief Variable extern de type structure s_calcul_sheet (dans .h)
 * Elle permet de faire appel à une feuille de calcul et à ses champs !! 
 */
extern s_calcul_sheet global_sheet;

/**
 * @struct operation
 * 
 * Contient le nom de l'operateur et sa fonction 
 */
typedef struct operation {
    char operator_name;
    void (*operator_func)(my_stack_t*);
} s_operation;

/**
 * @var operations
 * @brief Tableau de structure (type s_operation) extern (déclaré dans le .h)
 * qui stock les opérateur et fonctions associés manipulant la stack
 */
extern s_operation operations[];

/**
 * @brief Fonction d'initialisation de la feuille de calcul qui est une matrice 
 * @param cols Nombre de colonnes
 * @param lines Nombre de lignes
 */
void initialisation_sheet(int cols,int lines);

/**
 * @brief fonction add qui prend en param une pile et fait l'addition sur les deux derniers elements empilés
 * @param stack Une pile utilisée pour l'évaluation
 */
void operator_add(my_stack_t* stack);

/**
 * @brief fonction subtract qui prend en param une pile et fait la soustraction sur les deux derniers elements empilés
 * @param stack Une pile utilisée pour l'évaluation
 */
void operator_subtract(my_stack_t* stack);

/**
 * @brief fonction multiply qui prend en param une pile et fait la multiplication sur les deux derniers elements empilés
 * @param stack Une pile utilisée pour l'évaluation
 */
void operator_multiply(my_stack_t* stack);

/**
 * @brief fonction divide qui prend en param une pile et fait la division sur les deux derniers elements empilés
 * @param stack Une pile utilisée pour l'évaluation
 */
void operator_divide(my_stack_t* stack);

/**
 * @brief fonction modulo qui prend en param une pile et fait le modulo sur les deux derniers elements empilés
 * @param stack Une pile utilisée pour l'évaluation
 */
void operator_modulo(my_stack_t* stack);

/**
 * @brief fonction find_operator_func qui prend un char,
 *  + retourne un pointeur vers une fonction qui (elle) prend un my_stack_t* et retourne void
 * @param operator_char char représentant l'opérateur
 * @return Pointeur vers une fonction operator_... ou NULL si non trouvé
 */
void (*find_operator_func(char operator_char))(my_stack_t*);

/**
 * @brief Fonction trop cool qui libère les cellules dans l'ordre inverse de la création
 * @return 1 si la libération de la mémoire c'est passé sans problème, sinon 0
 */
int free_global_sheet();


#endif