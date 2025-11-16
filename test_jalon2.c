#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Pour strcpy

// Inclut les définitions de s_cell, s_token, etc.
#include "cell.h" 
// Inclut les définitions de s_calcul_sheet et les prototypes des fonctions
#include "calcul_sheet.h" 

/**
 * TÂCHE 3 : Tester et valider le comportement
 * des fonctions analyseCell et evaluateCell.
 */
int main() {
    
    printf("-------- Lancement des tests du JALON 2 --------\n");

    // initialise la feuille de calcul
    initialisation_sheet(10, 10);
    printf("        Feuille de calcul 10x10 initialisée.\n");

    // ----------------------------- TEST 1 (calcul nombre) ----------------------------------
    // -----------------------------------------------------------------------
    printf("\n--- TEST 1: Calcul simple ---\n");
    // crée la cellule A1 (indice 0, 0)
    s_cell* cell_A1 = get_or_create_cell(0, 0);
    // alloue et copie la formule NPI
    cell_A1->content = malloc(10 * sizeof(char));
    strcpy(cell_A1->content, "=10 5 +");
    printf("Contenu de A1: %s\n", cell_A1->content);
    // analyse
    analyseCell(cell_A1);
    printf("Analyse... %d tokens trouvés.\n", cell_A1->token_count);
    // évaluation
    evaluateCell(cell_A1);
    printf("Évaluation...\n");
    printf("RÉSULTAT Test 1 (A1): %f\n", cell_A1->value);
    if (cell_A1->value == 15.0) {
        printf(">>> SUCCÈS (Attendu: 15.0)\n");
    } else {
        printf(">>> ÉCHEC (Attendu: 15.0)\n");
    }

    // ----------------------------- TEST 2 (calcul avec référence) ----------------------------------
    // -----------------------------------------------------------------------
    printf("\n--- TEST 2: Calcul avec référence ---\n");
    // crée la cellule A2 (indice 1, 0)
    s_cell* cell_A2 = get_or_create_cell(1, 0);
    
    // ref vers A1, puis nb 2, puis multiplication
    cell_A2->content = malloc(10 * sizeof(char));
    strcpy(cell_A2->content, "=A100 2 *");
    
    printf("Contenu de A2: %s\n", cell_A2->content);

    analyseCell(cell_A2);
    printf("Analyse... %d tokens trouvés.\n", cell_A2->token_count);

    // ici evaluateCell appel récursivement evaluateCell(A1)
    evaluateCell(cell_A2);
    printf("Évaluation...\n");
    
    printf("RÉSULTAT Test 2 (A2): %.2f\n", cell_A2->value);
    if (cell_A2->value == 30.0) {
        printf(">>> SUCCÈS (Attendu: 30.0)\n");
    } else {
        printf(">>> ÉCHEC (Attendu: 30.0)\n");
    }

    // ----------------------------- TEST 3 (calcul NPI complexe) ---------------------------------
    // -----------------------------------------------------------------------
    printf("\n--- TEST 3: Calcul NPI complexe ---\n");
    // crée la cellule B1 (indice 0, 1)
    s_cell* cell_B1 = get_or_create_cell(0, 1);
    
    // etape 1: 20 5 /  = 4
    // etape 2: 4 2 %   = 0
    cell_B1->content = malloc(15 * sizeof(char));
    strcpy(cell_B1->content, "=20 5 / 2 %"); 
    
    printf("Contenu de B1: %s\n", cell_B1->content);


    analyseCell(cell_B1);
    printf("Analyse... %d tokens trouvés.\n",cell_B1->token_count);

    evaluateCell(cell_B1);
    printf("Évaluation...\n");
    
    // validation
    printf("RÉSULTAT Test 3 (B1): %.2f\n", cell_B1->value);
    if (cell_B1->value == 0.0) {
        printf(">>> SUCCÈS (Attendu: 0.0)\n");
    } else {
        printf(">>> ÉCHEC (Attendu: 0.0)\n");
    }

    // TODO: Libérer la mémoire (free) pour les cell->content
    // et les cellules à la fin du programme.
    free(cell_A1->content);
    free(cell_A2->content);
    free(cell_B1->content);
    printf("\n--- Tests terminés ---\n");
    return 0;
}
