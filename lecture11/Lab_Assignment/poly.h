#ifndef __POLY_H__
#define __POLY_H__

typedef struct term term;
struct term {
    int coeff;
    int exp;
    term *next;
};  

void create_poly(term **head, double coeff, int exp);
void delete_poly(term **head);

term* add_poly(const term *head1, const term *head2);
// term* mul_poly(const term *head1, const term *head2);


double eval_poly(const term *head, double x);
void print_poly(const term *head);
void input_poly(term **head);

#endif