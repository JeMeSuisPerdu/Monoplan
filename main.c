#include <stdio.h>
#include "mod_list/list.h"
#include <stdlib.h>

int main()
{
    node_t* list = list_create();
    int a = 25;
    int *p = &a;
    int b = 10;
    int *pb = &b;
    int c = 15;
    int *pc = &c;

    list_set_data(list, p);
    list = list_append(list, pb);
    list = list_insert(list, pc);
    list_affiche_int(list);

    list_destroy(list);
    return 0;
}