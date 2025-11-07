#include "list.h"
#include <stdio.h>
#include <stdlib.h>

node_t* list_create (void) {
    node_t* n = malloc(sizeof(node_t));

    n->data = NULL;
    n->next = NULL;

    return n;
}

void* list_get_data (const node_t* node) {
    return node->data;
}

void list_set_data (node_t* node, void* data) {
    node->data = data;
}

node_t* list_next (node_t* node) {
    return node->next;
}

node_t* list_insert (node_t* head, void* data) {
    node_t* node = malloc(sizeof(node_t));

    node->data = data;
    node->next = head;

    return node;
}

node_t* list_append (node_t* head, void* data) {
    node_t* node = head;

    while (node->next != NULL) {
        node = list_next(node);
    }

    node_t* lastNode = malloc(sizeof(node_t));

    node->next = lastNode;
    lastNode->data = data;

    return head;
}

void list_affiche (node_t* head) {
    node_t* node = head;

    while (node->next != NULL) {
        printf("%d\n", *(int*)node->data);
        node = list_next(node);
    }
    printf("%d\n", *(int*)node->data);
}

node_t* list_remove (node_t* head, void* data) {
    node_t* node = head;

    // compare des adresses donc doit être le même objet pour marcher
    while (node->data != data) {
        node = list_next(node);
    }

    // compare les valeurs mais nécéssite des types précis
    /*while (*(int*)node->data != *(int*)data) {
        node = list_next(node);
    }*/

    // TODO

    return head;
}

node_t* list_headRemove (node_t* head) {


}

void list_destroy (node_t* head) {

}