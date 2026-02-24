#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "poly.h"

double eval_poly(const term* head, double x)
{
    double result = 0.0;
    while (head != NULL)
    {
        result += head->coeff * pow(x, head->exp);
        head = head->next;
    }
    return result;
}