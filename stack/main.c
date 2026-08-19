#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

int main() {
    uint32_t capacity;
    printf("Enter the maximum stack capacity: ");
    if (scanf("%u", &capacity) != 1) {
        printf("Invalid input. Exiting.\n");
        return 1;
    }

    Stack my_stack = stack_new(capacity);
    StackResult result;
    int choice;
    float value;

    while (1) {
        printf("\n--- Stack Menu ---\n");
        printf("1. Push an element\n");
        printf("2. Pop an element\n");
        printf("3. Peek top element\n");
        printf("4. Exit\n");
        printf("Enter your choice (1-4): ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid selection. Exiting.\n");
            break;
        }

        switch (choice) {
            case 1:
                printf("Enter float value to push: ");
                if (scanf("%f", &value) == 1) {
                    my_stack = stack_push(my_stack, value, &result);
                    if (result.status == STACK_OK) {
                        printf("Successfully pushed %.2f\n", value);
                    } else {
                        printf("Error: Stack is FULL!\n");
                    }
                } else {
                    printf("Invalid number format.\n");
                    // Clear invalid character from buffer
                    while (getchar() != '\n'); 
                }
                break;

            case 2:
                my_stack = stack_pop(my_stack, &result);
                if (result.status == STACK_OK) {
                    printf("Popped element: %.2f\n", result.data);
                } else {
                    printf("Error: Stack is EMPTY!\n");
                }
                break;

            case 3:
                my_stack = stack_peek(my_stack, &result);
                if (result.status == STACK_OK) {
                    printf("Top element is: %.2f\n", result.data);
                } else {
                    printf("Error: Stack is EMPTY!\n");
                }
                break;

            case 4:
                printf("Cleaning up memory and exiting...\n");
                stack_delete(my_stack);
                printf("Goodbye!\n");
                return 0;

            default:
                printf("Invalid option. Please choose 1, 2, 3, or 4.\n");
        }
    }

    stack_delete(my_stack);
    return 0;
}

