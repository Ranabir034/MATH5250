#include<stdio.h>
#include<math.h>
#include "quadrilateral.h"

int main()
{
    quadrilateral my_quad;
    printf("Enter the coordinates of the quadrilateral (x y for each point):\n");
    printf("Point 1: ");
    scanf("%lf %lf", &my_quad.p1.x, &my_quad.p1.y);
    printf("Point 2: ");
    scanf("%lf %lf", &my_quad.p2.x, &my_quad.p2.y);
    printf("Point 3: ");
    scanf("%lf %lf", &my_quad.p3.x, &my_quad.p3.y);
    printf("Point 4: ");
    scanf("%lf %lf", &my_quad.p4.x, &my_quad.p4.y); 

    compute_perimeter(&my_quad);
    compute_area(&my_quad);
    compute_inner_angle(&my_quad);

    // printf("Final Results:\n");
    // printf("Perimeter: %.2f\n", my_quad.perimeter);
    // printf("Area: %.2f\n", my_quad.area);
    // printf("Inner Angles: %.2f, %.2f, %.2f, %.2f\n", 
    //     my_quad.inner_angle[0], 
    //     my_quad.inner_angle[1], 
    //     my_quad.inner_angle[2], 
    //     my_quad.inner_angle[3]);

    return 0;
}