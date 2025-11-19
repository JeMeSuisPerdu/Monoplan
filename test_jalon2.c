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
    
    TEST("------------------------------ DEBUTS DES TEST DU JALON 2 ------------------------------\n");

    // initialise la feuille de calcul
    initialisation_sheet(10, 10);
    TEST("        Feuille de calcul 10x10 initialisée.\n");

    // ---------------------------------------------------------------------------------------
    //-------------------   TEST 1 (calcul simple avec operator(+))   ------------------------
    // ---------------------------------------------------------------------------------------

    TEST("------------------------- TEST 1: Calcul simple avec opérateur (+) ----------------------\n");
    // crée la cellule A1 (indice 0, 0)
    s_cell* cell_A1 = get_or_create_cell(0, 0);

    // Nb1 = 10, Nb2 = 5, puis addition
    change_content_cell(cell_A1, "=10 5 +");
    TEST("Contenu de la cellule A1: %s\n", cell_A1->content);

    TEST("Tentative d'analyse de la cellule...");
    analyse_cell(cell_A1);
    TEST("Analyse terminée... %d tokens trouvés.\n", cell_A1->token_count);

    TEST("Tentative d'évaluation de la cellule...");
    evaluate_cell(cell_A1);
    TEST("Évaluation terminée...\n");

    TEST("RÉSULTAT TEST 1 (A1): %.2f\n", cell_A1->value);
    if (cell_A1->value == 15.0) {
        TEST(">>> SUCCÈS (Attendu: 15.0)\n");
    } else {
        TEST(">>> ÉCHEC (Attendu: 15.0)\n");
    }

    // ---------------------------------------------------------------------------------------
    //-------------------   TEST 2 (calcul simple avec operator(-))   ------------------------
    // ---------------------------------------------------------------------------------------

    TEST("---------------------- TEST 2: Calcul simple avec opérateur (-) ----------------------\n");
    // crée la cellule A2 (indice 0, 1)
    s_cell* cell_A2 = get_or_create_cell(0, 1);
    
    // Nb1 = 10, Nb2 = 1, puis soustraction
    change_content_cell(cell_A2, "=10 1 -");
    TEST("Contenu de la cellule A2: %s\n", cell_A2->content);

    TEST("Tentative d'analyse de la cellule...");
    analyse_cell(cell_A2);
    TEST("Analyse terminée... %d tokens trouvés.\n", cell_A2->token_count);

    TEST("Tentative d'évaluation de la cellule...");
    evaluate_cell(cell_A2);
    TEST("Évaluation terminée...\n");
    
    TEST("RÉSULTAT TEST 2 (A2): %.2f\n", cell_A2->value);
    if (cell_A2->value == 9.0) {
        TEST(">>> SUCCÈS (Attendu: 9.0 ) \n");
    } else {
        TEST(">>> ÉCHEC (Attendu: 9.0 )\n");
    }

    // ---------------------------------------------------------------------------------------
    //-------------------   TEST 3 (calcul simple avec operator(*))   ------------------------
    // ---------------------------------------------------------------------------------------

    TEST("---------------------- TEST 3: Calcul simple avec opérateur (*) ----------------------\n");
    // crée la cellule A3 (indice 0, 2)
    s_cell* cell_A3 = get_or_create_cell(0, 2);
    
    // Nb1 = 50, Nb2 = 2, puis soustraction
    change_content_cell(cell_A3, "=50 2 *");
    TEST("Contenu de la cellule A3: %s\n", cell_A3->content);

    TEST("Tentative d'analyse de la cellule...");
    analyse_cell(cell_A3);
    TEST("Analyse terminée... %d tokens trouvés.\n", cell_A3->token_count);

    TEST("Tentative d'évaluation de la cellule...");
    evaluate_cell(cell_A3);
    TEST("Évaluation terminée...\n");
    
    TEST("RÉSULTAT TEST 3 (A3): %.2f\n", cell_A3->value);
    if (cell_A3->value == 100.0) {
        TEST(">>> SUCCÈS (Attendu: 100.0 ) \n");
    } else {
        TEST(">>> ÉCHEC (Attendu: 100.0 )\n");
    }

    // ---------------------------------------------------------------------------------------
    //-------------------   TEST 4 (calcul simple avec operator(/))   ------------------------
    // ---------------------------------------------------------------------------------------

    TEST("------------------------ TEST 4: Calcul simple avec opérateur (/) ----------------------\n");
    // crée la cellule A4 (indice 0, 3)
    s_cell* cell_A4 = get_or_create_cell(0, 3);
    
    // Nb1 = 2000, Nb2 = 2, puis soustraction
    change_content_cell(cell_A4, "=2000 2 /");
    TEST("Contenu de la cellule A4: %s\n", cell_A4->content);

    TEST("Tentative d'analyse de la cellule...");
    analyse_cell(cell_A4);
    TEST("Analyse terminée... %d tokens trouvés.\n", cell_A4->token_count);

    TEST("Tentative d'évaluation de la cellule...");
    evaluate_cell(cell_A4);
    TEST("Évaluation terminée...\n");
    
    TEST("RÉSULTAT TEST 4 (A4): %.2f\n", cell_A4->value);
    if (cell_A4->value == 1000.0) {
        TEST(">>> SUCCÈS (Attendu: 1000.0 ) \n");
    } else {
        TEST(">>> ÉCHEC (Attendu: 1000.0 )\n");
    }

    // ---------------------------------------------------------------------------------------
    //-------------------   TEST 5 (calcul complexe avec operator(+ -))   --------------------
    // ---------------------------------------------------------------------------------------

    TEST("---------------------- TEST 5: Calcul complexe avec operator(+ -) ----------------------\n");
    // crée la cellule A5 (indice 0, 4)
    s_cell* cell_A5 = get_or_create_cell(0, 4);
    
    // Nb1 = 2, puis multiplication, Nb2 = 10, Nb3 = 1, puis addition
    change_content_cell(cell_A5, "=2 10 1 +*");
    TEST("Contenu de la cellule A5: %s\n", cell_A5->content);

    TEST("Tentative d'analyse de la cellule...");
    analyse_cell(cell_A5);
    TEST("Analyse terminée... %d tokens trouvés.\n", cell_A5->token_count);

    TEST("Tentative d'évaluation de la cellule...");
    evaluate_cell(cell_A5);
    TEST("Évaluation terminée...\n");
    
    TEST("RÉSULTAT TEST 5 (A5): %.2f\n", cell_A5->value);
    if (cell_A5->value == 22.0) {
        TEST(">>> SUCCÈS (Attendu: 22.0 ) \n");
    } else {
        TEST(">>> ÉCHEC (Attendu: 22.0 )\n");
    }
 
    // ---------------------------------------------------------------------------------------
    //-------------------   TEST 6 (calcul complexe avec operator(* /))   --------------------
    // ---------------------------------------------------------------------------------------

    TEST("---------------------- TEST 6: Calcul complexe avec operator(* /) ----------------------\n");
    // crée la cellule A6 (indice 0, 5)
    s_cell* cell_A6 = get_or_create_cell(0, 5);
    
    // Nb1 = 1, puis multiplication,  Nb2 = 10, Nb2 = 2, puis division
    change_content_cell(cell_A6, "=1 10 2 */");
    TEST("Contenu de la cellule A6: %s\n", cell_A6->content);

    TEST("Tentative d'analyse de la cellule...");
    analyse_cell(cell_A6);
    TEST("Analyse terminée... %d tokens trouvés.\n", cell_A6->token_count);

    TEST("Tentative d'évaluation de la cellule...");
    evaluate_cell(cell_A6);
    TEST("Évaluation terminée...\n");

    TEST("RÉSULTAT TEST 6 (A6): %.2f\n", cell_A6->value);
    if (cell_A6->value == 0.05) {
        TEST(">>> SUCCÈS (Attendu: 0.05 ) \n");
    } else {
        TEST(">>> ÉCHEC (Attendu: 0.05 )\n");
    }
    // -----------------------------------------------------------------------------------------------
    //----------------------------- TEST 7 (calcul avec référence vers A1 )---------------------------
    // -----------------------------------------------------------------------------------------------
    
    TEST("-------------------------- TEST 7: Calcul avec référence vers A1 -------------------------\n");
    // crée la cellule B1 (indice 1, 0)
    s_cell* cell_B1 = get_or_create_cell(1, 0);
    
    // ref vers A1 (vaut 15), puis nb 2, puis multiplication
    change_content_cell(cell_B1, "=A1 2 *");
    
    TEST("Contenu de B1: %s\n", cell_B1->content);

    TEST("Tentative d'analyse de la cellule...");
    analyse_cell(cell_B1);
    TEST("Analyse terminée... %d tokens trouvés.\n", cell_B1->token_count);

    TEST("Tentative d'évaluation de la cellule...");
    evaluate_cell(cell_B1);
    TEST("Évaluation terminée...\n");
    
    TEST("RÉSULTAT TEST 7 (B1): %.2f\n", cell_B1->value);
    if (cell_B1->value == 30.0) {
        TEST(">>> SUCCÈS (Attendu: 30.0 ) \n");
    } else {
        TEST(">>> ÉCHEC (Attendu: 30.0 )\n");
    }
    // -----------------------------------------------------------------------------------------------
    //----------------------------- TEST 8 (calcul avec référence inconnue)---------------------------
    // -----------------------------------------------------------------------------------------------
    
    TEST("---------------- TEST 8: Calcul avec référence inconnue (débordement de limites)---------------\n");
    // crée la cellule B2 (indice 1, 1)
    s_cell* cell_B2 = get_or_create_cell(1, 1);
    
    // ref vers A100 (supérieur à A10), puis nb 2, puis multiplication
    change_content_cell(cell_B2, "=A100 2 *");
    
    TEST("Contenu de B2: %s\n", cell_B2->content);

    TEST("Tentative d'analyse de la cellule...");
    analyse_cell(cell_B2);
    TEST("Analyse terminée... %d tokens trouvés.\n", cell_B2->token_count);

    TEST("Tentative d'évaluation de la cellule...");
    evaluate_cell(cell_B2);
    TEST("Évaluation terminée...\n");
    
    TEST("RÉSULTAT TEST 8 (B2): %.2f\n", cell_B2->value);
    if (cell_B2->value == 0.0) {
        TEST(">>> SUCCÈS (Attendu: 0.0 ) \n");
    } else {
        TEST(">>> ÉCHEC (Attendu: 0.0 )\n");
    }

    // -----------------------------------------------------------------------------------------------
    // ----------------------------- TEST 9 (cas où la cellule est vide) -----------------------------
    // -----------------------------------------------------------------------------------------------
    
    TEST("---------------------------- TEST 9: Cas où la cellule est vide --------------------------\n");
    s_cell* cell_B3 = get_or_create_cell(1, 2);
    
    change_content_cell(cell_B3, " ");
    
    TEST("Contenu de B3: %s\n", cell_B3->content);

    TEST("Tentative d'analyse de la cellule...");
    analyse_cell(cell_B3);
    TEST("Analyse terminée... %d tokens trouvés.\n", cell_B3->token_count);

    TEST("Tentative d'évaluation de la cellule...");
    evaluate_cell(cell_B3);
    TEST("Évaluation terminée...\n");
    
    TEST("RÉSULTAT TEST 9 (B3): %.2f\n", cell_B3->value);
    if (cell_B3->value == 0.0) {
        TEST(">>> SUCCÈS (Attendu: 0.0 ) \n");
    } else {
        TEST(">>> ÉCHEC (Attendu: 0.0 )\n");
    }

    // -----------------------------------------------------------------------------------------------
    // ------------------ TEST 10 : cas où il n'y a qu'une valeur (sans operateur) -------------------
    // -----------------------------------------------------------------------------------------------
    
    TEST("---------------- TEST 10 : Cas où il n'y a qu'une valeur (sans operateur) ---------------\n");
    s_cell* cell_B4 = get_or_create_cell(1, 3);
    
    change_content_cell(cell_B4, "=15");
    
    TEST("Contenu de B4: %s\n", cell_B4->content);

    TEST("Tentative d'analyse de la cellule...");
    analyse_cell(cell_B4);
    TEST("Analyse terminée... %d tokens trouvés.\n", cell_B4->token_count);

    TEST("Tentative d'évaluation de la cellule...");
    evaluate_cell(cell_B4);
    TEST("Évaluation terminée...\n");
    
    TEST("RÉSULTAT TEST 10 (B4): %.2f\n", cell_B4->value);
    if (cell_B4->value == 15.0) {
        TEST(">>> SUCCÈS (Attendu: 15.0 ) \n");
    } else {
        TEST(">>> ÉCHEC (Attendu: 15.0 )\n");
    }

    // -----------------------------------------------------------------------------------------------
    // ------------------------------ TEST 11 : Le cas obligatoirement faux --------------------------
    // -----------------------------------------------------------------------------------------------
    
    TEST("---------------------------- TEST 11 : Le cas obligatoirement faux -------------------------\n");
    s_cell* cell_B5 = get_or_create_cell(1, 4);
    
    change_content_cell(cell_B5, "ex 10 15 -");
    
    TEST("Contenu de B5: %s\n", cell_B5->content);
    TEST("Tentative d'analyser la cellule avec le cas faux...");
    analyse_cell(cell_B5);
    TEST("Tentative d'évaluer la cellule avec le cas faux...");
    evaluate_cell(cell_B5);
    
    TEST("RÉSULTAT TEST 11 (B5): %.2f\n", cell_B5->value);
    if (cell_B5->value == 0.0) {
        TEST(">>> SUCCÈS (Attendu: 0.0 ) \n");
    } else {
        TEST(">>> ÉCHEC (Attendu: 0.0 )\n");
    }
    TEST("------------------------------ LIBERATION DE LA MEMOIRE --------------------------------\n");

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

    TEST("Contenu des cellules A1,A2,B1, libérés avec succès.");
    TEST("Tokens des cellules A1,A2,B1, libérés avec succès.");
    TEST("Cellules A1,A2,B1, libérés avec succès.");
    TEST("--------------------------------------------------------------------------------------------\n");
    TEST("--------------------------------------- TESTS FINIS ----------------------------------------\n");
    return 0;
}
