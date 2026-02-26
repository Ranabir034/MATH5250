#include <stdio.h>
#include <stdlib.h>
#include "poly.h"

void print_poly(const term* head)
{
    if (head == NULL)
    {
        printf("0\n");
        return;
    }

    int first = 1;
    while (head != NULL)
    {
        double c = head->coeff;
        int e = head->exp;

        if (!first)
        {
            if (c >= 0.0)
                printf(" + ");
            else               
            {
                printf(" - ");
                c = -c;
            }
        }
        else if (c < 0.0)
        {
            printf("-");
            c = -c;
        }

        if (e == 0)
            printf("%.2lf", c);
        else if (e == 1)
            printf("%.2lfx", c);
        else
            printf("%.2lfx^%d", c, e);

        first = 0;
        head = head->next;
    }
}