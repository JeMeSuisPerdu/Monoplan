#include <stdio.h>
#include "list.h"
#include <stdlib.h>

int main()
{
    node_t* list = list_create();
    int a = 25;
    int *p = &a;
    list_set_data(list, p);
    printf("Adresse stockée dans data : %p\n", list_get_data(list));
    printf("Valeur pointée : %d\n", *(int*)list_get_data(list));
    free(list);
    return 0;
}