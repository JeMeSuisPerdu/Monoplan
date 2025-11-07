#include <stdio.h>
#include "list.h"

int main()
{
    node_t* list = list_create();
    int a = 25;
    int *p = &a;
    list_set_data (list, p);
    //printf("%p",list->data);
    printf("%p",list);
    return 0;
}