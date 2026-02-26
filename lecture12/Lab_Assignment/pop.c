#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include "node.h"

void pop(node** top)
{
    if (*top == NULL)
    {
        printf("Error: Stack underflow.\n");
        return;
    }

    node* temp = *top;
    *top = (*top)->next;
    free(temp);

}