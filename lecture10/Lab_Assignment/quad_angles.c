#include<stdio.h>
#include<math.h>
#include "quadrilateral.h"

#define PI 3.14159265358979323846

static double angle_at_vertex(point a, point b, point c) {
    double ab_x = b.x - a.x;
    double ab_y = b.y - a.y;
    double ac_x = c.x - a.x;
    double ac_y = c.y - a.y;

    double dot_product = ab_x * ac_x + ab_y * ac_y;
    double magnitude_ab = sqrt(ab_x * ab_x + ab_y * ab_y);
    double magnitude_ac = sqrt(ac_x * ac_x + ac_y * ac_y);

    if (magnitude_ab == 0 || magnitude_ac == 0) {
        return 0.0; // Avoid division by zero
    }

    double cos_angle = dot_product / (magnitude_ab * magnitude_ac);
    if (cos_angle > 1.0) cos_angle = 1.0; // Clamp to avoid precision issues
    if (cos_angle < -1.0) cos_angle = -1.0;

    return acos(cos_angle) * (180.0 / PI); // Convert to degrees
}

void compute_inner_angle(quadrilateral *quad) {
    quad->inner_angle[0] = angle_at_vertex(quad->p1, quad->p2, quad->p4);
    quad->inner_angle[1] = angle_at_vertex(quad->p2, quad->p3, quad->p1);
    quad->inner_angle[2] = angle_at_vertex(quad->p3, quad->p4, quad->p2);
    quad->inner_angle[3] = angle_at_vertex(quad->p4, quad->p1, quad->p3);

    printf("Inner Angles: %.2f, %.2f, %.2f, %.2f\n", 
        quad->inner_angle[0], 
        quad->inner_angle[1], 
        quad->inner_angle[2], 
        quad->inner_angle[3]);
}

