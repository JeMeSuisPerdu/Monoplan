// DUO : ANIS LAFRAD  && GABRIEL GASNIER
#include <stdio.h>
#include "mod_list/list.h"
#include "log/log.h"
#include <stdlib.h>

int main()
{
    /*
     --------------------------------------------------------------------------
                            Test de la liste chaînée (By Anis le plus cool)
    --------------------------------------------------------------------------
    */

    TEST("-------- TEST DE LA LISTE CHAINEE --------\n");
    TEST("---- Création de la liste : ----");
    node_t* list = list_create();
    TEST("---- Initialisation et ajout de données dans la liste : ----");
    int a = 25, b= 10, c=15;
    int *p1 = &a;
    int *p2 = &b;
    int *p3 = &c;
    list_set_data(list, p1);
    list = list_append(list, p2);
    list = list_insert(list, p3);
    TEST("---- Affichage de la liste : ----");
    list_affiche_int(list);
    TEST("---- Suppression d'un noeud (data = 10) : ----");
    list = list_remove (list, p2);
    TEST("---- Affichage de la liste après suppression : ----");
    list_affiche_int(list);
    TEST("---- Destruction de la liste : ----");
    list_destroy(list);
    TEST("--------------- FIN DES TESTS ---------------\n");

    /*
     --------------------------------------------------------------------------
                            Test de 
    --------------------------------------------------------------------------
    */

    
    return 0;
}