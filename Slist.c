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

    new_node->next = list->head;

    list->head = new_node;

    if (list->tail == NULL) {
        list->tail = new_node;
    }

    ++list->cont;

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

    if (list->head == NULL) {
        list->head = new_node;
        list->tail = new_node;
    } else {
        list->tail->next = new_node;
        list->tail = new_node;
    }

    ++list->cont;

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

    if (list->cont == 0) {
        return list;
    }

    Node *temp = list->head;

    list->head = temp->next;

    if (list->head == NULL) {
        list->tail = NULL;
    }

    --list->cont;

    free(temp);

    return list;
}


/* Removes the last node from the list */
Slist* slist_delete_tail(Slist *list) {
    assert(list != NULL);

    if (list->cont == 0) {
        return list;
    }

    Node *temp = list->tail;

    if (list->head == list->tail) {
        list->head = NULL;
        list->tail = NULL;
    } else {
        Node *curr;

        for (curr = list->head;
             curr->next != list->tail;
             curr = curr->next) {
        }

        curr->next = NULL;
        list->tail = curr;
    }

    --list->cont;

    free(temp);

    return list;
}


/* Adds a new node at the given position */
Slist* add_at_position(Slist *list, int32_t ele, int32_t position) {
    assert(list != NULL);

    if (position == 0) {
        return add_at_head(list, ele);
    }

    if (position < 0) {
        return list;
    }

    Node *curr = list->head;

    for (int32_t i = 0;
         i < position - 1 && curr != NULL;
         i++) {
        curr = curr->next;
    }

    if (curr == NULL) {
        return list;
    }

    Node *new_node = get_new_node_(ele);

    new_node->next = curr->next;
    curr->next = new_node;

    if (new_node->next == NULL) {
        list->tail = new_node;
    }

    ++list->cont;

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

    if (list->cont == 0 || position < 0) {
        return list;
    }

    if (position == 0) {
        return slist_delete_head(list);
    }

    Node *curr = list->head;

    for (int32_t i = 0;
         i < position - 1 && curr != NULL;
         i++) {
        curr = curr->next;
    }

    if (curr == NULL || curr->next == NULL) {
        return list;
    }

    Node *temp = curr->next;

    curr->next = temp->next;

    if (temp == list->tail) {
        list->tail = curr;
    }

    --list->cont;

    free(temp);

    return list;
}


/* Adds ele after the first node containing key */
Slist* add_node_after(Slist *list, int32_t key, int32_t ele) {
    assert(list != NULL);

    Node *curr = list->head;

    while (curr != NULL) {
        if (curr->data == key) {
            Node *new_node = get_new_node_(ele);

            new_node->next = curr->next;
            curr->next = new_node;

            if (curr == list->tail) {
                list->tail = new_node;
            }

            ++list->cont;

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

    while (curr != NULL) {
        if (curr->data == key) {
            if (curr->next == NULL) {
                return list;
            }

            Node *temp = curr->next;

            curr->next = temp->next;

            if (temp == list->tail) {
                list->tail = curr;
            }

            --list->cont;

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


/* Reverses the linked list */
Slist* reverse_list(Slist *list) {
    assert(list != NULL);

    Node *prev = NULL;
    Node *curr = list->head;
    Node *next = NULL;

    list->tail = list->head;

    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    list->head = prev;

    return list;
}


/* Finds the middle node of the list */
Node* find_middle(Slist *list) {
    assert(list != NULL);

    Node *slow = list->head;
    Node *fast = list->head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}


/* Finds the nth node from the end */
Node* find_nth_from_end(Slist *list, int32_t n) {
    assert(list != NULL);

    if (n <= 0) {
        return NULL;
    }

    Node *first = list->head;
    Node *second = list->head;

    for (int32_t i = 0; i < n; i++) {
        if (first == NULL) {
            return NULL;
        }

        first = first->next;
    }

    while (first != NULL) {
        first = first->next;
        second = second->next;
    }

    return second;
}


/* Removes duplicate values from the list */
Slist* remove_duplicates(Slist *list) {
    assert(list != NULL);

    Node *curr = list->head;

    while (curr != NULL) {
        Node *prev = curr;
        Node *runner = curr->next;

        while (runner != NULL) {
            if (runner->data == curr->data) {
                prev->next = runner->next;

                if (runner == list->tail) {
                    list->tail = prev;
                }

                Node *temp = runner;
                runner = runner->next;

                free(temp);

                --list->cont;
            } else {
                prev = runner;
                runner = runner->next;
            }
        }

        curr = curr->next;
    }

    return list;
}
