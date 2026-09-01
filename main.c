#include <stdio.h>
#include "Slist.h"

int main() {
    Slist list = slist_new();

    int size, number, i, n;
    Node *node;

    printf("Enter the size of the list: ");
    scanf("%d", &size);

    for (i = 0; i < size; i++) {
        printf("Enter number %d: ", i + 1);
        scanf("%d", &number);

        add_at_tail(&list, number);
    }

    printf("\nNumber of nodes: %d\n", get_count(&list));
    printf("Minimum value: %d\n", get_min_value(&list));
    printf("Maximum value: %d\n", get_max_value(&list));

    printf("\nOriginal list: ");
    node = list.head;

    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }

    printf("\n");


    reverse_list(&list);

    printf("\nReversed list: ");
    node = list.head;

    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }

    printf("\n");


    node = find_middle(&list);

    if (node != NULL) {
        printf("\nMiddle node: %d\n", node->data);
    } else {
        printf("\nList is empty\n");
    }


    printf("\nEnter n to find nth node from the end: ");
    scanf("%d", &n);

    node = find_nth_from_end(&list, n);

    if (node != NULL) {
        printf("%dth node from the end: %d\n", n, node->data);
    } else {
        printf("Invalid position\n");
    }


    remove_duplicates(&list);

    printf("\nList after removing duplicates: ");
    node = list.head;

    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }

    printf("\n");

    printf("\nNumber of nodes after removing duplicates: %d\n", get_count(&list));

    return 0;
}
