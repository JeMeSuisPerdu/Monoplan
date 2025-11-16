#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Pour strcpy

// Inclut les définitions de s_cell, s_token, etc.
#include "cell.h" 
// Inclut les définitions de s_calcul_sheet et les prototypes des fonctions
#include "calcul_sheet.h" 
#include "./log/log.h" // Pour les fonctions de log
/**
 * TÂCHE 3 : Tester et valider le comportement
 * des fonctions analyseCell et evaluateCell.
 */
int main() {
    
    LOG("\n------------------------------ DEBUTS DES TEST DU JALON 2 ------------------------------\n");

    // initialise la feuille de calcul
    initialisation_sheet(10, 10);
    LOG("        Feuille de calcul 10x10 initialisée.\n");

    // ---------------------------------------------------------------------------------------
    //-----------------------------   TEST 1 (calcul nombre)   -------------------------------
    // ---------------------------------------------------------------------------------------

    LOG("\n---------------------- TEST 1: Calcul avec NPI de nombres ----------------------\n");
    // crée la cellule A1 (indice 0, 0)
    s_cell* cell_A1 = get_or_create_cell(0, 0);
    // alloue et copie la formule NPI
    cell_A1->content = malloc(10 * sizeof(char));
    strcpy(cell_A1->content, "=10 5 +");
    LOG("Contenu de A1: %s\n", cell_A1->content);
    // analyse
    analyseCell(cell_A1);
    LOG("Analyse... %d tokens trouvés.\n", cell_A1->token_count);
    // évaluation
    evaluateCell(cell_A1);
    LOG("Évaluation...\n");
    LOG("RÉSULTAT Test 1 (A1): %f\n", cell_A1->value);
    if (cell_A1->value == 15.0) {
        LOG(">>> SUCCÈS (Attendu: 15.0)\n");
    } else {
        LOG(">>> ÉCHEC (Attendu: 15.0)\n");
    }
    // -----------------------------------------------------------------------------------------------
    //----------------------------- TEST 2 (calcul avec référence inconnue)---------------------------
    // -----------------------------------------------------------------------------------------------
    
    LOG("\n---------------- TEST 2: Calcul avec référence inconnu (débordement de limites)---------------\n");
    // crée la cellule A2 (indice 1, 0)
    s_cell* cell_A2 = get_or_create_cell(0, 1);
    
    // ref vers A1, puis nb 2, puis multiplication
    cell_A2->content = malloc(10 * sizeof(char));
    strcpy(cell_A2->content, "=A1 2 *");
    
    LOG("Contenu de A2: %s\n", cell_A2->content);

    analyseCell(cell_A2);
    LOG("Analyse... %d tokens trouvés.\n", cell_A2->token_count);

    // ici evaluateCell appel récursivement evaluateCell(A1)
    evaluateCell(cell_A2);
    LOG("Évaluation...\n");
    
    LOG("RÉSULTAT Test 2 (A2): %.2f\n", cell_A2->value);
    if (cell_A2->value == 0.0) {
        LOG(">>> SUCCÈS (Attendu: 0.0 car cellule en dehors des limites) \n");
    } else {
        LOG(">>> ÉCHEC (Attendu: 0.0 car cellule en dehors des limites)\n");
    }

    // -----------------------------------------------------------------------------------------------
    //----------------------------- TEST 4 (calcul avec référence inconnue)---------------------------
    // -----------------------------------------------------------------------------------------------
    
    LOG("\n---------------- TEST 4: Calcul avec référence inconnue (débordement de limites)---------------\n");
    // crée la cellule A4 (indice 1, 0)
    s_cell* cell_A4 = get_or_create_cell(0, 3);
    
    // ref vers A100 (supérieur à A10), puis nb 2, puis multiplication
    cell_A4->content = malloc(10 * sizeof(char));
    strcpy(cell_A4->content, "=A100 2 *");
    
    LOG("Contenu de A4: %s\n", cell_A4->content);

    analyseCell(cell_A4);
    LOG("Analyse... %d tokens trouvés.\n", cell_A4->token_count);

    // ici evaluateCell appel récursivement evaluateCell(A1)
    evaluateCell(cell_A4);
    LOG("Évaluation...\n");
    
    LOG("RÉSULTAT Test 4 (A4): %.2f\n", cell_A4->value);
    if (cell_A4->value == 0.0) {
        LOG(">>> SUCCÈS (Attendu: 0.0 car cellule en dehors des limites) \n");
    } else {
        LOG(">>> ÉCHEC (Attendu: 0.0 car cellule en dehors des limites)\n");
    }

    // --------------------------------------------------------------------------------------------
    //----------------------------- TEST 3 (calcul avec plusieurs opérateurs) ---------------------
    // --------------------------------------------------------------------------------------------

    LOG("\n---------------------- TEST 3: Calcul NPI avec plusieurs opérateurs -----------------------\n");
    // crée la cellule B1 (indice 0, 1)
    s_cell* cell_B1 = get_or_create_cell(1, 0);
    
    // etape 1: 20 5 /  = 4
    // etape 2: 4 2 %   = 0
    cell_B1->content = malloc(15 * sizeof(char));
    strcpy(cell_B1->content, "=20 5 / 2 %"); 
    
    LOG("Contenu de B1: %s\n", cell_B1->content);


    analyseCell(cell_B1);
    LOG("Analyse... %d tokens trouvés.\n",cell_B1->token_count);

    evaluateCell(cell_B1);
    LOG("Évaluation...\n");
    
    // validation
    LOG("RÉSULTAT Test 3 (B1): %.2f\n", cell_B1->value);
    if (cell_B1->value == 0.0) {
        LOG(">>> SUCCÈS (Attendu: 0.0)\n");
    } else {
        LOG(">>> ÉCHEC (Attendu: 0.0)\n");
    }

    // libérer les chaine de caractère, les tokens et les cellules allouées
    free(cell_A1->content);
    free(cell_A1->tokens);
    free(cell_A1);

    free(cell_A2->content);
    free(cell_A2->tokens);
    free(cell_A2);

    free(cell_B1->content);
    free(cell_B1->tokens);
    free(cell_B1);

    LOG("Contenu des cellules A1,A2,B1, libérés avec succès.");
    LOG("Tokens des cellules A1,A2,B1, libérés avec succès.");
    LOG("Cellules A1,A2,B1, libérés avec succès.");

    printf("\n------------------------- TESTS FINIS -------------------------\n");
    return 0;
}
