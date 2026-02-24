#include <stdio.h>
#include <stdlib.h>
#include "poly.h"

void create_poly(term** head, double coeff, int exp)
{
    if (coeff == 0.0)
        return;                        

    term* newNode = (term*)malloc(sizeof(term));
    if (newNode == NULL)
    {
        fprintf(stderr, "Error: malloc failed in CreatePoly.\n");
        exit(1);
    }
    newNode->coeff = coeff;
    newNode->exp   = exp;
    newNode->next  = NULL;

    if (*head == NULL || exp > (*head)->exp)
    {
        newNode->next = *head;
        *head         = newNode;
        return;
    }

    if (exp == (*head)->exp)
    {
        (*head)->coeff += coeff;
        free(newNode);
        if ((*head)->coeff == 0.0)
        {
            term* tmp = *head;
            *head     = (*head)->next;
            free(tmp);
        }
        return;
    }

    term* prev = *head;
    term* curr = (*head)->next;

    while (curr != NULL && curr->exp > exp)
    {
        prev = curr;
        curr = curr->next;
    }

    if (curr != NULL && curr->exp == exp)
    {
        curr->coeff += coeff;
        free(newNode);
        if (curr->coeff == 0.0)
        {
            prev->next = curr->next;
            free(curr);
        }
        return;
    }

    newNode->next = curr;
    prev->next    = newNode;
}