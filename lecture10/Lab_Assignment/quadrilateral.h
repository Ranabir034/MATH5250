#ifndef __Quadrilateral_H__
#define __Quadrilateral_H__

typedef struct point point;
struct point {
    double x;
    double y;
};

typedef struct quadrilateral quadrilateral;
struct quadrilateral {
    point p1;
    point p2;
    point p3;
    point p4;

    double perimeter;
    double area;
    double inner_angle[4]; 
};

void compute_perimeter(quadrilateral *quad);
void compute_area(quadrilateral *quad);
void compute_inner_angle(quadrilateral *quad);

#endif

