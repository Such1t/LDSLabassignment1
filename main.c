#include <stdio.h>
#include "Slist.h"

int main() {
    Slist list = slist_new();

    int size, number, i;

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

    return 0;
}
