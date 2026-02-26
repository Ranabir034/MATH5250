#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "node.h"

void push(const int iteration, const double a, const double b, const double midpoint, const double f_mid, node** top)
{
    node* new_node = (node*)malloc(sizeof(node));
    if (new_node==NULL)
    {
        printf("Error: Memory allocation failed.\n");
        return;
    }
    new_node->iteration = iteration;
    new_node->a = a;
    new_node->b = b;
    new_node->midpoint = midpoint;
    new_node->f_mid = f_mid;
    new_node->next = *top;
    *top = new_node;
}