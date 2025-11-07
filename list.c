#include "list.h"
#include <stdio.h>
#include <stdlib.h>

node_t* list_create (void) {
    node_t* head = malloc(sizeof(node_t));

    head->data = NULL;
    head->next = NULL;

    printf("Création de la liste effectuée\n");

    return head;
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

    printf("Insertion du noeud effectuée\n");

    return node;
}

node_t* list_append (node_t* head, void* data) {
    node_t* nodeIt = head;

    while (nodeIt->next != NULL) {
        nodeIt = list_next(nodeIt);
    }

    node_t* newNode = malloc(sizeof(node_t));

    nodeIt->next = newNode;
    newNode->data = data;

    printf("Ajout du noeud effectué\n");

    return head;
}

void list_affiche_int (node_t* head) {
    node_t* nodeIt = head;
    int compteur = 0;

    printf("Affichage de la liste :\n");
    while (nodeIt != NULL) {
        printf("%d|%d\n", compteur, *(int*)nodeIt->data);
        nodeIt = nodeIt->next;
        compteur++;
    }

    printf("\n");
}

node_t* list_remove (node_t* head, void* data) {
    node_t* node = head;

    // compare des adresses donc doit être le même objet pour marcher
    while (node->data != data) {
        node = node->next;
    }

    // compare les valeurs mais nécéssite des types précis
    /*while (*(int*)node->data != *(int*)data) {
        node = list_next(node);
    }*/

    // TODO

    return head;
}

node_t* list_headRemove (node_t* head) {
    node_t* node = head->next;
    free(head);

    printf("Suppression de la tête effectuée\n");

    return node;
}

void list_destroy (node_t* head) {
    node_t* nodeIt = head;
    node_t* nodeNext;

    while (nodeIt != NULL) {
        nodeNext = nodeIt->next;
        free(nodeIt);
        nodeIt = nodeNext;
    }

    printf("Suppression de la liste effectuée\n\n");

    // NOTE : pas de free(nodeIt->data) car on n'utilise pas de malloc pour stocker les data puisque le type est inconnu,
    // on pourra quand même le faire depuis l'endroit où on récupère la data avec l'initialisation du pointeur donc à voir plus tard
}