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
    if(node == NULL) {
        LOG("Le noeud est NULL, impossible de récupérer la data \n");
        return NULL;
    }
    return node->data;
}

void list_set_data (node_t* node, void* data) {
    if(node == NULL) {
        LOG("Le noeud est NULL, impossible d'initialiser la data");
        return;
    }
    // Cas où la data existe déjà : lecture sans écraser
    if(node->data != NULL)
    {
        list_get_data(node);
        LOG("La data du noeud est déjà initialisée. Passage en mode lecture de la data.\n");
    }
    // Cas où la data n'existe pas encore : initialisation
    else{
        node->data = data;
        LOG("Data du noeud correctement initialisée.\n");
    }
}

node_t* list_next (node_t* node) {
    if(node == NULL) {
        LOG("Le noeud est NULL, impossible de récupérer le noeud suivant");
        return NULL;
    }
    return node->next;
}

node_t* list_insert (node_t* head, void* data) {
    if(head == NULL) {
        LOG("La liste est vide, impossible d'insérer un noeud en tête de liste");
        return NULL;
    }

    // Initialisation du nouveau noeud
    node_t* node_head = malloc(sizeof(node_t));

    // Nouvelle tête pointe sur l'ancienne tête
    node_head->data = data;
    node_head->next = head;

    LOG("Insertion d'un nouveau noeud en tête de liste\n");
    return node_head;
}

node_t* list_append (node_t* head, void* data) {
    if(head == NULL) {
        LOG("La liste est vide, impossible d'ajouter un noeud en queue de file");
        return NULL;
    }
    // Parcours de la tête jusqu'à la fin de la liste
    node_t* node_iterator = head;
    while (node_iterator->next != NULL) {
        // pour avancer dans la liste
        node_iterator = list_next(node_iterator);
    }

    // Création du nouveau noeud
    node_t* tail_node = malloc(sizeof(node_t));
    // Ancienne queue pointe sur la nouvelle
    node_iterator->next = tail_node;
    tail_node->data = data;
    
    LOG("Ajout du nouveau noeud en queue de file effectué");
    return head;
}

void list_affiche_int (node_t* head) {
    if(head == NULL) {
        LOG("La liste est vide, impossible d'afficher son contenu");
        return;
    }

    node_t* node_iterator = head;
    int compteur = 0;
    
    LOG("Affichage de la liste :\n");
    while (node_iterator != NULL) {
        LOG("Indice : %d|  Valeur : %d\n", compteur, *(int*)node_iterator->data);
        // pour avancer dans la liste
        node_iterator = node_iterator->next;
        compteur++;
    }
    
}

node_t* list_remove (node_t* head, void* data) {
    if(head == NULL) {
        LOG("La liste est vide, impossible de supprimer un noeud\n");
        return NULL;
    }else if(head->data == data) {    // Suppression de la tête si elle correspond à la data
        return list_headRemove(head);
    }else{ 
        node_t* node = head;
        // On parcourt la liste jusqu'à trouver le noeud avant celui à supprimer
        while (node->next != NULL && node->next->data != data ) {
            node = node->next;
        }
        if(node->next != NULL) {
            // Noeud à supprimer (celui qui contient la data)
            node_t* node_to_delete = node->next;
            // Noeud actuel pointe sur le noeud suivant celui à supprimer
            node->next = node_to_delete->next;
            // Suppression du noeud 
            free(node_to_delete);
            LOG("Suppression d'un noeud autre que la tête effectuée et contenant la DATA\n");
        } else {
            LOG("Aucun noeud avec la data spécifiée n'a été trouvé, suppression impossible\n");
        }
    }

    return head;
}

node_t* list_headRemove (node_t* head) {
    if(head == NULL) {
        LOG("La liste est vide, impossible de supprimer la tête");
        return NULL;
    }
    node_t* node = head->next;
    free(head);

    LOG("Suppression de la tête effectuée\n");
    return node;
}

void list_destroy (node_t* head) {
    if(head == NULL) {
        LOG("La liste est vide, impossible de la détruire");
        return;
    }
    node_t* nodeIt = head;
    node_t* nodeNext;

    while (nodeIt != NULL) {
        nodeNext = nodeIt->next;
        free(nodeIt);
        nodeIt = nodeNext;
    }
    LOG("Suppression de la liste effectuée\n");
    // NOTE : pas de free(nodeIt->data). On libère tous les nœuds, mais pas les données pointées, parce qu’on ne sait pas ce qu’elles contiennent et comment elles ont été allouées (type void*).
    // On pourra quand même le faire depuis l'endroit où l'on récupère la data avec l'initialisation du pointeur (à voir plus tard).
}