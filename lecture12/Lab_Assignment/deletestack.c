#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include "node.h"

void deletestack(node** top)
{
    node* temp;
    while (*top != NULL)
    {
        temp = *top;
        *top = (*top)->next;
        free(temp);
    }

    printf("Stack has been deleted and memory freed.\n");

}