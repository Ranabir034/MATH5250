#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "matrix.h"

matrix new_matrix(const int rows, const int cols) {
    matrix M; M.rows=rows; M.cols=cols;
    M.val=(double*)calloc(rows*cols,sizeof(double));
    assert(M.val); return M;
}
vector new_vector(const int size) {
    vector v; v.size=size;
    v.val=(double*)calloc(size,sizeof(double));
    assert(v.val); return v;
}

void print_matrix_full(const matrix* mat, char* varname) {
    printf("%s (%dx%d):\n",varname,mat->rows,mat->cols);
    for(int i=1;i<=mat->rows;i++){
        for(int j=1;j<=mat->cols;j++) printf(" %10.4f",mgetp(mat,i,j));
        printf("\n");
    }
}
void print_vector_full(const vector* vec, char* varname) {
    printf("%s (%d):\n",varname,vec->size);
    for(int i=1;i<=vec->size;i++) printf(" %10.4f\n",vgetp(vec,i));
}
void print_scalar_full(const double* z, char* varname) {
    printf("%s = %10.6f\n",varname,*z);
}

matrix matrix_add(const matrix* A, const matrix* B) {
    assert(A->rows==B->rows && A->cols==B->cols);
    matrix C=new_matrix(A->rows,A->cols);
    for(int i=1;i<=A->rows;i++)
        for(int j=1;j<=A->cols;j++)
            mgetp(&C,i,j)=mgetp(A,i,j)+mgetp(B,i,j);
    return C;
}
matrix matrix_sub(const matrix* A, const matrix* B) {
    assert(A->rows==B->rows && A->cols==B->cols);
    matrix C=new_matrix(A->rows,A->cols);
    for(int i=1;i<=A->rows;i++)
        for(int j=1;j<=A->cols;j++)
            mgetp(&C,i,j)=mgetp(A,i,j)-mgetp(B,i,j);
    return C;
}
matrix matrix_mult(const matrix* A, const matrix* B) {
    assert(A->cols==B->rows);
    matrix C=new_matrix(A->rows,B->cols);
    for(int i=1;i<=A->rows;i++)
        for(int j=1;j<=B->cols;j++)
            for(int k=1;k<=A->cols;k++)
                mgetp(&C,i,j)+=mgetp(A,i,k)*mgetp(B,k,j);
    return C;
}
matrix matrix_dot_mult(const matrix* A, const matrix* B) {
    assert(A->rows==B->rows && A->cols==B->cols);
    matrix C=new_matrix(A->rows,A->cols);
    for(int i=1;i<=A->rows;i++)
        for(int j=1;j<=A->cols;j++)
            mgetp(&C,i,j)=mgetp(A,i,j)*mgetp(B,i,j);
    return C;
}

vector vector_add(const vector* x, const vector* y) {
    assert(x->size==y->size);
    vector z=new_vector(x->size);
    for(int i=1;i<=x->size;i++) vgetp(&z,i)=vgetp(x,i)+vgetp(y,i);
    return z;
}
vector vector_sub(const vector* x, const vector* y) {
    assert(x->size==y->size);
    vector z=new_vector(x->size);
    for(int i=1;i<=x->size;i++) vgetp(&z,i)=vgetp(x,i)-vgetp(y,i);
    return z;
}
double vector_dot_mult(const vector* x, const vector* y) {
    assert(x->size==y->size);
    double s=0.0;
    for(int i=1;i<=x->size;i++) s+=vgetp(x,i)*vgetp(y,i);
    return s;
}
vector matrix_vector_mult(const matrix* A, const vector* x) {
    assert(A->cols==x->size);
    vector y=new_vector(A->rows);
    for(int i=1;i<=A->rows;i++)
        for(int k=1;k<=A->cols;k++)
            vgetp(&y,i)+=mgetp(A,i,k)*vgetp(x,k);
    return y;
}

/* Gaussian elimination with partial pivoting */
vector solve(const matrix* A, const vector* b) {
    int n=A->rows;
    assert(A->cols==n && b->size==n);
    double* aug=(double*)malloc(n*(n+1)*sizeof(double));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++) aug[i*(n+1)+j]=A->val[i*A->cols+j];
        aug[i*(n+1)+n]=b->val[i];
    }
    for(int col=0;col<n;col++){
        int pivot=col;
        for(int row=col+1;row<n;row++)
            if(fabs(aug[row*(n+1)+col])>fabs(aug[pivot*(n+1)+col])) pivot=row;
        for(int j=0;j<=n;j++){
            double tmp=aug[col*(n+1)+j];
            aug[col*(n+1)+j]=aug[pivot*(n+1)+j];
            aug[pivot*(n+1)+j]=tmp;
        }
        if(fabs(aug[col*(n+1)+col])<1e-14){
            /* Near-singular: perturb diagonal slightly */
            aug[col*(n+1)+col] = (aug[col*(n+1)+col]>=0 ? 1 : -1)*1e-14;
        }
        for(int row=col+1;row<n;row++){
            double f=aug[row*(n+1)+col]/aug[col*(n+1)+col];
            for(int j=col;j<=n;j++) aug[row*(n+1)+j]-=f*aug[col*(n+1)+j];
        }
    }
    vector x=new_vector(n);
    for(int i=n-1;i>=0;i--){
        x.val[i]=aug[i*(n+1)+n];
        for(int j=i+1;j<n;j++) x.val[i]-=aug[i*(n+1)+j]*x.val[j];
        x.val[i]/=aug[i*(n+1)+i];
    }
    free(aug); return x;
}

/* Rayleigh Quotient: x^T A x / x^T x */
double rayleigh_quotient(const matrix* A, const vector* x) {
    vector Ax=matrix_vector_mult(A,x);
    double r=vector_dot_mult(x,&Ax)/vector_dot_mult(x,x);
    free(Ax.val); return r;
}
double vector_norm(const vector* x) { return sqrt(vector_dot_mult(x,x)); }
vector vector_scale(const vector* x, double s) {
    vector y=new_vector(x->size);
    for(int i=1;i<=x->size;i++) vgetp(&y,i)=s*vgetp(x,i);
    return y;
}