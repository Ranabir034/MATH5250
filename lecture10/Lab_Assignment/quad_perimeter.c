#include <stdio.h>
#include <math.h>
#include "quadrilateral.h"

static double distance(point p1, point p2) {
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    return sqrt(dx * dx + dy * dy);
}

void compute_perimeter(quadrilateral *quad) {
    double d1 = distance(quad->p1, quad->p2);
    double d2 = distance(quad->p2, quad->p3);
    double d3 = distance(quad->p3, quad->p4);
    double d4 = distance(quad->p4, quad->p1);
    quad->perimeter = d1 + d2 + d3 + d4;

    printf("Distances: %.2f, %.2f, %.2f, %.2f\n", d1, d2, d3, d4);
    printf("Perimeter: %.2f\n", quad->perimeter);

}   