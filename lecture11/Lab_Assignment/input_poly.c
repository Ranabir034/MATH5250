#include <stdio.h>
#include <stdlib.h>

#include "poly.h"

void input_poly(term **head)
{
    int n;
    printf("Enter number of terms: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        double coeff;
        int exp;
        printf("Enter coefficient and exponent of term %d: ", i + 1);
        scanf("%lf %d", &coeff, &exp);

        if (exp < 0) {
            fprintf(stderr, "Exponent must be non-negative.\n");
            continue;
        }
        
        create_poly(head, coeff, exp);
    }
}