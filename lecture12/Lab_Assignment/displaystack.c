#include<stdio.h>
#include<math.h>
#include "node.h"

void displaystack(const node* top)
{
    if (top == NULL)
    {
        printf("Stack is empty.\n");
        return;
    }

    printf("\nStack contents (top to bottom):\n");
    printf("Iter |     a     |     b     |  Midpoint  |   f(Midpoint)\n");
    printf("-------------------------------------------------------------\n");
    const node* current = top;
    while (current != NULL)
    {
        printf("%4d | %9.6f | %9.6f | %10.6f | %14.6f\n", current->iteration, current->a, current->b, current->midpoint, current->f_mid);
        current = current->next;
    }
    printf("-------------------------------------------------------------\n");
    
}