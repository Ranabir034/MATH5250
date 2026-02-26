#include<stdio.h>
#include<stdlib.h>

#include "poly.h"

term* add_poly(const term* p, const term* q)
{
    term* result = NULL;

    while (p!=NULL)
    {
        create_poly(&result, p->coeff, p->exp);
        p = p->next;
    }

    while (q!=NULL)
    {
        create_poly(&result, q->coeff, q->exp);
        q = q->next;
    }

    return result;
}