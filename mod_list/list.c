#include "list.h"
#include "../log/log.h"
#include <stdio.h>
#include <stdlib.h>

node_t* list_create (void) {
    node_t* head = malloc(sizeof(node_t));

    head->data = NULL;
    head->next = NULL;

    LOG("Création de la liste effectuée !!\n");

    return head;
}

void* list_get_data (const node_t* node) {
    return node->data;
}

void list_set_data (node_t* node, void* data) {
    if(node->data != NULL)
    {
        list_get_data(node);
        LOG("La data du noeud est déjà initialisée. Passage en mode lecture de la data !!\n");
    }else{
        node->data = data;
        LOG("Data du noeud correctement initialisée !!\n");
    }
}

node_t* list_next (node_t* node) {
    return node->next;
}

node_t* list_insert (node_t* head, void* data) {
    node_t* node = malloc(sizeof(node_t));

    node->data = data;
    node->next = head;

    LOG("Insertion du noeud effectuée\n");

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

    LOG("Ajout du noeud effectué\n");
    return head;
}

void list_affiche_int (node_t* head) {
    node_t* nodeIt = head;
    int compteur = 0;

    LOG("Affichage de la liste :\n");
    while (nodeIt != NULL) {
        LOG("%d|%d\n", compteur, *(int*)nodeIt->data);
        nodeIt = nodeIt->next;
        compteur++;
    }
    LOG("\n");
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

    LOG("Suppression de la tête effectuée\n");

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

    LOG("Suppression de la liste effectuée\n\n");
    // NOTE : pas de free(nodeIt->data) car on n'utilise pas de malloc pour stocker les data puisque le type est inconnu,
    // on pourra quand même le faire depuis l'endroit où on récupère la data avec l'initialisation du pointeur donc à voir plus tard
}