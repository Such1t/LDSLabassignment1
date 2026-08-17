#include <stdlib.h>
#include <assert.h>
#include "Slist.h"


/* Creates an empty linked list */
Slist slist_new() {
    Slist list = {
        NULL,
        NULL,
        0,
        0,
        0
    };

    return list;
}


/* Returns the number of nodes in the list */
int32_t get_count(const Slist *list) {
    assert(list != NULL);

    return list->cont;
}


/* Creates a new node and stores ele in it */
static Node* get_new_node_(int32_t ele) {
    Node *new_node = (Node*)malloc(sizeof(Node));

    assert(new_node != NULL);

    new_node->data = ele;
    new_node->next = NULL;

    return new_node;
}


/* Adds a new node at the beginning of the list */
Slist* add_at_head(Slist *list, int32_t ele) {
    assert(list != NULL);

    Node *new_node = get_new_node_(ele);

    /* New node points to the old head */
    new_node->next = list->head;

    /* Make the new node the head */
    list->head = new_node;

    /* If the list was empty, this is also the tail */
    if (list->tail == NULL) {
        list->tail = new_node;
    }

    ++list->cont;

    /* Update minimum and maximum values */
    if (list->cont == 1) {
        list->min_value = ele;
        list->max_value = ele;
    } else {
        if (ele < list->min_value) {
            list->min_value = ele;
        }

        if (ele > list->max_value) {
            list->max_value = ele;
        }
    }

    return list;
}


/* Adds a new node at the end of the list */
Slist* add_at_tail(Slist *list, int32_t ele) {
    assert(list != NULL);

    Node *new_node = get_new_node_(ele);

    /* If the list is empty, new node is both head and tail */
    if (list->head == NULL) {
        list->head = new_node;
        list->tail = new_node;
    } else {
        /* Attach the new node after the old tail */
        list->tail->next = new_node;
        list->tail = new_node;
    }

    ++list->cont;

    /* Update minimum and maximum values */
    if (list->cont == 1) {
        list->min_value = ele;
        list->max_value = ele;
    } else {
        if (ele < list->min_value) {
            list->min_value = ele;
        }

        if (ele > list->max_value) {
            list->max_value = ele;
        }
    }

    return list;
}


/* Checks whether key is present in the list */
uint8_t Slist_lookup(const Slist *list, int32_t key) {
    assert(list != NULL);

    Node *curr = list->head;

    /* Go through every node */
    while (curr != NULL) {
        if (curr->data == key) {
            return 1;
        }

        curr = curr->next;
    }

    return 0;
}


/* Removes the first node from the list */
Slist* slist_delete_head(Slist *list) {
    assert(list != NULL);

    /* Nothing to delete if the list is empty */
    if (list->cont == 0) {
        return list;
    }

    Node *temp = list->head;

    /* Move head to the next node */
    list->head = temp->next;

    /* If list becomes empty, tail must also be NULL */
    if (list->head == NULL) {
        list->tail = NULL;
    }

    --list->cont;

    /* Free memory of the removed node */
    free(temp);

    return list;
}


/* Removes the last node from the list */
Slist* slist_delete_tail(Slist *list) {
    assert(list != NULL);

    /* Nothing to delete if the list is empty */
    if (list->cont == 0) {
        return list;
    }

    Node *temp = list->tail;

    /* If there is only one node, list becomes empty */
    if (list->head == list->tail) {
        list->head = NULL;
        list->tail = NULL;
    } else {
        Node *curr;

        /* Find the node just before the tail */
        for (curr = list->head;
             curr->next != list->tail;
             curr = curr->next) {
        }

        curr->next = NULL;
        list->tail = curr;
    }

    --list->cont;

    /* Free memory of the old tail */
    free(temp);

    return list;
}


/* Adds a new node at the given position */
Slist* add_at_position(Slist *list, int32_t ele, int32_t position) {
    assert(list != NULL);

    /* Position 0 means add at the beginning */
    if (position == 0) {
        return add_at_head(list, ele);
    }

    /* Negative positions are not allowed */
    if (position < 0) {
        return list;
    }

    Node *curr = list->head;

    /* Move to the node before the required position */
    for (int32_t i = 0;
         i < position - 1 && curr != NULL;
         i++) {
        curr = curr->next;
    }

    /* Position is outside the list */
    if (curr == NULL) {
        return list;
    }

    Node *new_node = get_new_node_(ele);

    /* Insert new node after curr */
    new_node->next = curr->next;
    curr->next = new_node;

    /* Update tail if node was added at the end */
    if (new_node->next == NULL) {
        list->tail = new_node;
    }

    ++list->cont;

    /* Update minimum and maximum values */
    if (ele < list->min_value) {
        list->min_value = ele;
    }

    if (ele > list->max_value) {
        list->max_value = ele;
    }

    return list;
}


/* Removes the node at the given position */
Slist* delete_at_position(Slist *list, int32_t position) {
    assert(list != NULL);

    /* Do nothing for an empty list or negative position */
    if (list->cont == 0 || position < 0) {
        return list;
    }

    /* Position 0 means delete the first node */
    if (position == 0) {
        return slist_delete_head(list);
    }

    Node *curr = list->head;

    /* Find the node before the one to delete */
    for (int32_t i = 0;
         i < position - 1 && curr != NULL;
         i++) {
        curr = curr->next;
    }

    /* Position is not valid */
    if (curr == NULL || curr->next == NULL) {
        return list;
    }

    Node *temp = curr->next;

    /* Skip the node that needs to be deleted */
    curr->next = temp->next;

    /* Update tail if the last node was deleted */
    if (temp == list->tail) {
        list->tail = curr;
    }

    --list->cont;

    /* Free memory of the removed node */
    free(temp);

    return list;
}


/* Adds ele after the first node containing key */
Slist* add_node_after(Slist *list, int32_t key, int32_t ele) {
    assert(list != NULL);

    Node *curr = list->head;

    /* Search for key */
    while (curr != NULL) {
        if (curr->data == key) {
            Node *new_node = get_new_node_(ele);

            /* Insert new node after curr */
            new_node->next = curr->next;
            curr->next = new_node;

            /* Update tail if added after the old tail */
            if (curr == list->tail) {
                list->tail = new_node;
            }

            ++list->cont;

            /* Update minimum and maximum values */
            if (list->cont == 1) {
                list->min_value = ele;
                list->max_value = ele;
            } else {
                if (ele < list->min_value) {
                    list->min_value = ele;
                }

                if (ele > list->max_value) {
                    list->max_value = ele;
                }
            }

            return list;
        }

        curr = curr->next;
    }

    return list;
}


/* Deletes the node after the first node containing key */
Slist* delete_after(Slist *list, int32_t key) {
    assert(list != NULL);

    Node *curr = list->head;

    /* Search for key */
    while (curr != NULL) {
        if (curr->data == key) {
            /* There is no node after curr */
            if (curr->next == NULL) {
                return list;
            }

            Node *temp = curr->next;

            /* Remove the next node */
            curr->next = temp->next;

            /* Update tail if the removed node was the tail */
            if (temp == list->tail) {
                list->tail = curr;
            }

            --list->cont;

            /* Free memory of the removed node */
            free(temp);

            return list;
        }

        curr = curr->next;
    }

    return list;
}


/* Returns the largest value in the list */
int32_t get_max_value(const Slist *list) {
    assert(list != NULL);

    return list->max_value;
}


/* Returns the smallest value in the list */
int32_t get_min_value(const Slist *list) {
    assert(list != NULL);

    return list->min_value;
}
