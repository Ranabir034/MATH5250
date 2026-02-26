#include <stdio.h>
#include <math.h>
#include "quadrilateral.h"

void compute_area(quadrilateral *quad)
{
    double d1 = sqrt(pow(quad->p2.x - quad->p1.x, 2) + pow(quad->p2.y - quad->p1.y, 2));
    double d2 = sqrt(pow(quad->p3.x - quad->p2.x, 2) + pow(quad->p3.y - quad->p2.y, 2));
    double d3 = sqrt(pow(quad->p4.x - quad->p3.x, 2) + pow(quad->p4.y - quad->p3.y, 2));
    double d4 = sqrt(pow(quad->p1.x - quad->p4.x, 2) + pow(quad->p1.y - quad->p4.y, 2));

    double s = (d1 + d2 + d3 + d4) / 2.0;
    quad->area = sqrt((s - d1) * (s - d2) * (s - d3) * (s - d4));

    printf("Area: %.2f\n", quad->area);
}