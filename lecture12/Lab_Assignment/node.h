#ifndef __NODE_H__
#define __NODE_H__

typedef struct node node;

struct node
{
    int iteration;
    double a;
    double b;
    double midpoint;
    double f_mid;
    node* next;
};

void push(const int iteration, const double a, const double b, const double midpoint, const double f_mid, node** top);
void pop(node** top);
void displaystack(const node* top);
void deletestack(node** top);

void bisectionmethod(const double a0, const double b0, const double tol, const int max_iter);
double f(const double x);

#endif