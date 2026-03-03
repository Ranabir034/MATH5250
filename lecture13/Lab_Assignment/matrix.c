#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "matrix.h"

// ======= MATRIX FUNCTIONS =======
matrix new_matrix(const int rows, const int cols)
{
    matrix mat; mat.rows=rows; mat.cols=cols;
    assert(rows>0); assert(cols>0);
    mat.val=(double*)malloc(sizeof(double)*rows*cols);
    assert(mat.val!=NULL);
    for(int i=0;i<rows*cols;i++) mat.val[i]=0.0;
    return mat;
}
void free_matrix(matrix* mat)
{ free(mat->val); mat->val=NULL; mat->rows=0; mat->cols=0; }

void print_matrix_full(const matrix* mat, char* varname)
{
    assert(mat->rows>0); assert(mat->cols>0);
    printf("\n %s =\n", varname);
    for(int i=1;i<=mat->rows;i++){
        printf("  | ");
        for(int j=1;j<=mat->cols;j++){
            printf("%12.5e", mgetp(mat,i,j));
            if(j<mat->cols) printf(", ");
        }
        printf(" |\n");
    }
    printf("\n");
}

matrix matrix_add(const matrix* A, const matrix* B)
{
    const int r=A->rows,c=A->cols;
    assert(r==B->rows); assert(c==B->cols);
    matrix C=new_matrix(r,c);
    for(int i=1;i<=r;i++) for(int j=1;j<=c;j++)
        mget(C,i,j)=mgetp(A,i,j)+mgetp(B,i,j);
    return C;
}
matrix matrix_sub(const matrix* A, const matrix* B)
{
    const int r=A->rows,c=A->cols;
    assert(r==B->rows); assert(c==B->cols);
    matrix C=new_matrix(r,c);
    for(int i=1;i<=r;i++) for(int j=1;j<=c;j++)
        mget(C,i,j)=mgetp(A,i,j)-mgetp(B,i,j);
    return C;
}
matrix matrix_mult(const matrix* A, const matrix* B)
{
    const int rA=A->rows,cA=A->cols,cB=B->cols;
    assert(cA==B->rows);
    matrix C=new_matrix(rA,cB);
    for(int i=1;i<=rA;i++) for(int j=1;j<=cB;j++)
        for(int k=1;k<=cA;k++) mget(C,i,j)+=mgetp(A,i,k)*mgetp(B,k,j);
    return C;
}
matrix matrix_dot_mult(const matrix* A, const matrix* B)
{
    const int r=A->rows,c=A->cols;
    assert(r==B->rows); assert(c==B->cols);
    matrix C=new_matrix(r,c);
    for(int i=1;i<=r;i++) for(int j=1;j<=c;j++)
        mget(C,i,j)=mgetp(A,i,j)*mgetp(B,i,j);
    return C;
}
matrix matrix_transpose(const matrix* A)
{
    matrix T=new_matrix(A->cols,A->rows);
    for(int i=1;i<=A->rows;i++) for(int j=1;j<=A->cols;j++)
        mget(T,j,i)=mgetp(A,i,j);
    return T;
}
matrix matrix_scalar_mult(double s, const matrix* A)
{
    matrix C=new_matrix(A->rows,A->cols);
    for(int i=1;i<=A->rows;i++) for(int j=1;j<=A->cols;j++)
        mget(C,i,j)=s*mgetp(A,i,j);
    return C;
}



// ======= VECTOR FUNCTIONS =======
vector new_vector(const int size)
{
    vector vec; vec.size=size; assert(size>0);
    vec.val=(double*)malloc(sizeof(double)*size);
    assert(vec.val!=NULL);
    for(int i=0;i<size;i++) vec.val[i]=0.0;
    return vec;
}
void free_vector(vector* vec)
{ free(vec->val); vec->val=NULL; vec->size=0; }

void print_vector_full(const vector* vec, char* varname)
{
    assert(vec->size>0);
    printf("\n %s =\n  | ", varname);
    for(int i=1;i<=vec->size;i++){
        printf("%12.5e", vgetp(vec,i));
        if(i<vec->size) printf(", ");
    }
    printf(" |^T\n\n");
}
vector vector_add(const vector* x, const vector* y)
{
    const int n=x->size; assert(n==y->size);
    vector z=new_vector(n);
    for(int i=1;i<=n;i++) vget(z,i)=vgetp(x,i)+vgetp(y,i);
    return z;
}
vector vector_sub(const vector* x, const vector* y)
{
    const int n=x->size; assert(n==y->size);
    vector z=new_vector(n);
    for(int i=1;i<=n;i++) vget(z,i)=vgetp(x,i)-vgetp(y,i);
    return z;
}
double vector_dot_mult(const vector* x, const vector* y)
{
    const int n=x->size; assert(n==y->size);
    double z=0.0;
    for(int i=1;i<=n;i++) z+=vgetp(x,i)*vgetp(y,i);
    return z;
}
double vector_norm(const vector* x){ return sqrt(vector_dot_mult(x,x)); }
void print_scalar_full(const double* z, char* varname)
{ printf("\n %s =\n    %12.5e\n\n", varname, *z); }


// ======= MATRIX-VECTOR FUNCTIONS =======
vector matrix_vector_mult(const matrix* A, const vector* x)
{
    const int r=A->rows,c=A->cols; assert(c==x->size);
    vector Ax=new_vector(r);
    for(int i=1;i<=r;i++){
        double t=0.0;
        for(int j=1;j<=c;j++) t+=mgetp(A,i,j)*vgetp(x,j);
        vget(Ax,i)=t;
    }
    return Ax;
}


// ======= SOLVER FUNCTION =======
vector solve(const matrix* Ain, const vector* bin)
{
    const int n=Ain->rows;
    assert(Ain->rows==Ain->cols); assert(n==bin->size);
    /* copies */
    matrix A=new_matrix(n,n); vector b=new_vector(n);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++) mget(A,i,j)=mgetp(Ain,i,j);
        vget(b,i)=vgetp(bin,i);
    }
    vector x=new_vector(n);
    /* forward elim */
    for(int i=1;i<=n-1;i++){
        int p=i; double mx=-1.0;
        for(int j=i;j<=n;j++){
            double t=fabs(mget(A,j,i)); if(t>mx){p=j;mx=t;}
        }
        if(mx<=1e-14){printf("Singular\n");exit(1);}
        if(p!=i){
            for(int j=1;j<=n;j++){
                double t=mget(A,i,j); mget(A,i,j)=mget(A,p,j); mget(A,p,j)=t;
            }
            double t=vget(b,i); vget(b,i)=vget(b,p); vget(b,p)=t;
        }
        for(int j=i+1;j<=n;j++){
            double dm=mget(A,j,i)/mget(A,i,i);
            for(int k=1;k<=n;k++) mget(A,j,k)-=dm*mget(A,i,k);
            vget(b,j)-=dm*vget(b,i);
        }
    }
    /* back substitution */
    vget(x,n)=vget(b,n)/mget(A,n,n);
    for(int j=1;j<=n-1;j++){
        double s=0.0;
        for(int k=n-j+1;k<=n;k++) s+=mget(A,n-j,k)*vget(x,k);
        vget(x,n-j)=(vget(b,n-j)-s)/mget(A,n-j,n-j);
    }
    free_matrix(&A); free_vector(&b);
    return x;
}
