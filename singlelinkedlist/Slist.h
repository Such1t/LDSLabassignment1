#ifndef SLIST_H
#define SLIST_H

#include <stdint.h>


/* Each node stores one value and a pointer to the next node */
typedef struct Node {
    int32_t data;
    struct Node *next;
} Node;


/* This structure stores information about the whole linked list */
typedef struct {
    Node *head;          /* Points to the first node */
    Node *tail;          /* Points to the last node */
    int32_t cont;        /* Stores the number of nodes */
    int32_t min_value;   /* Stores the smallest value */
    int32_t max_value;   /* Stores the largest value */
} Slist;


/* Creates and returns an empty linked list */
Slist slist_new(void);

/* Returns the number of nodes in the list */
int32_t get_count(const Slist *list);


/* Adds a new node at the beginning of the list */
Slist* add_at_head(Slist *list, int32_t ele);

/* Adds a new node at the end of the list */
Slist* add_at_tail(Slist *list, int32_t ele);

/* Removes the first node from the list */
Slist* slist_delete_head(Slist *list);

/* Removes the last node from the list */
Slist* slist_delete_tail(Slist *list);

/* Returns 1 if key is found, otherwise returns 0 */
uint8_t Slist_lookup(const Slist *list, int32_t key);


/* Adds a new node at the given position */
Slist* add_at_position(Slist *list, int32_t ele, int32_t position);

/* Deletes the node at the given position */
Slist* delete_at_position(Slist *list, int32_t position);

/* Adds ele after the first node containing key */
Slist* add_node_after(Slist *list, int32_t key, int32_t ele);

/* Deletes the node after the first node containing key */
Slist* delete_after(Slist *list, int32_t key);


/* Returns the largest value in the list */
int32_t get_max_value(const Slist *list);

/* Returns the smallest value in the list */
int32_t get_min_value(const Slist *list);

#endif
