#include<stdio.h>
#include<stdlib.h>
#include "poly.h"

void delete_poly(term **head)
{
    term *current = *head;
    while (current != NULL) {
        term *temp = current;
        current = current->next;
        free(temp);
    }
    *head = NULL; // Set head to NULL after deletion
}