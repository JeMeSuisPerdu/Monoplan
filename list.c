#include "list.h"
#include <stdio.h>

node_t* list_create (void){
    node_t* n;
    n->data = NULL;
    return n;
}

void* list_get_data (const node_t* node){
    return node->data;
}

void list_set_data (node_t* node, void* data){
    node->data = data;
}

node_t* list_next (node_t* node){
    return node->next;
}

node_t* list_insert (node_t* head, void* data){


}

node_t* list_append (node_t*head, void* data){

    
}

node_t* list_remove (node_t* head, void* data){


}

node_t* list_headRemove (node_t* head){


}

void list_destroy (node_t* head){

}