#include <stdio.h>
#include <stdlib.h>

#include "poly.h"

int main(void)
{
    term* p = NULL;
    term* q = NULL;
    term* r = NULL;

    printf("Polynomial Operations");

    //enter first polynomial
    printf("Input first polynomial:\n");
    input_poly(&p);

    printf("\n P(x) = ");
    print_poly(p);
    printf("\n\n");

    // enter second polynomial
    printf("Input second polynomial:\n");
    input_poly(&q);

    printf("\n Q(x) = ");
    print_poly(q);
    printf("\n\n");

    // add the two polynomials
    r = add_poly(p, q);
    printf("R(x) = P(x) + Q(x) = ");
    print_poly(r);
    printf("\n\n");
    
    // // multiply the two polynomials
    // r = mul_poly(p, q);
    // printf("R(x) = P(x) * Q(x) = ");
    // print_poly(r);
    // printf("\n\n");
    

    // evaluation

    double x;
    printf("Enter value of x for evaluation: ");
    scanf("%lf", &x);

    printf("P(%.2lf) = %.2lf\n", x, eval_poly(p, x));
    printf("Q(%.2lf) = %.2lf\n", x, eval_poly(q, x));
    printf("R(%.2lf) = %.2lf\n", x, eval_poly(r, x));
    printf("\n");

    // free memory
    delete_poly(&p);
    delete_poly(&q);
    delete_poly(&r);

    printf("Memory freed. Exiting program.\n");
    return 0;

}