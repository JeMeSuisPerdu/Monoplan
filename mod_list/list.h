#ifndef LIST
#define LIST

/** 
 * @struct node
 * @brief Représente un noeud d'une liste chaînée
 * 
 * Contient un pointeur vers une donnée et un pointeur vers le prochain noeud de la liste
 */
typedef struct node {
    void* data; /** Pointeur vers la donnée stockée dans le nœud */
    struct node* next; /** Pointeur vers le nœud suivant dans la liste (NULL pour le dernier noeud de la liste) */
} node_t;

/** 
 * @brief Créée une nouvelle liste, donc un noeud
 * @return Pointeur vers la noeud de la nouvelle liste
 */
node_t* list_create (void);

/**
 * @brief Récupère le pointeur vers la donnée pointée d'un noeud
 * @param node pointeur vers le noeud concerné
 * @return Pointeur vers la donnée
 * @note Peut renvoyer NULL dans le cas où il n'y a pas de donnée
 */
void* list_get_data (const node_t* node);

/**
 * @brief Initialise ou change la donnée pointée d'un noeud
 * @param node Pointeur vers le noeud dont on veut changer la donnée
 * @param data La donnée vers laquelle on veut que le noeud pointe
 */
void list_set_data (node_t* node, void* data); 

/**
 * @brief Récupère le prochain noeud dans la liste
 * @param node Le pointeur du noeud dont on veut connaître le prochain dans la liste
 * @return Pointeur vers le noeud suivant
 */
node_t* list_next (node_t* node);

/**
 * @brief Ajoute un noeud au tout début de la liste
 * @param head Pointeur vers la tête de la liste concernée
 * @param data Pointeur vers la donnée du nouveau noeud, peut être NULL
 * @return Pointeur vers la nouvelle tête de la liste
 */
node_t* list_insert (node_t* head, void* data);

/**
 * @brief Ajoute un noeud en fin de liste
 * @param head Pointeur vers la tête de la liste concernée
 * @param data Pointeur vers la donnée du nouveau noeud, peut être NULL
 * @return Pointeur vers la tête de la liste
 */
node_t* list_append (node_t* head, void* data);

/**
 * @brief Pour debug uniquement - affiche des entiers contenus dans les data pointées par des noeuds d'une même liste
 * @param head Pointeur vers la tête de la liste concernée
 */
void list_affiche_int (node_t* head);

/**
 * @brief Supprime un noeud d'une liste s'il contient une data précise
 * @param head Pointeur vers la tête de la liste concernée
 * @param data Pointeur vers la donnée que doit contenir le noeud à supprimer
 * @note On compare le pointeur et non la valeur, c'est à dire qu'il faut que l'adresse pointée soit la même pour que le noeud soit supprimé
 * @return Pointeur vers la tête de la liste
 * @todo Libération de la mémoire de la donnée : adapter en fonction du processus de création de la donnée (en cas de malloc, on fera free)
 */
node_t* list_remove (node_t* head, void* data); 

/**
 * @brief Supprime la tête d'une liste
 * @param head Pointeur vers la tête de la liste concernée
 * @return Pointeur vers la nouvelle tête de la liste
 * @todo Libération de la mémoire de la donnée : adapter en fonction du processus de création de la donnée (en cas de malloc, on fera free)
 */
node_t* list_headRemove (node_t* head); 

/**
 * @brief Supprime tout les noeuds d'une liste
 * @param head Pointeur vers la tête de la liste concernée
 * @todo Libération de la mémoire de la donnée : adapter en fonction du processus de création de la donnée (en cas de malloc, on fera free)
 */
void list_destroy (node_t* head);

#endif