import numpy as np

def GaussElimination(A, b):
    A = np.copy(A).astype(float)
    b = np.copy(b).astype(float)
    n = len(b)

    #forward elimination
    for k in range(n-1):
        max_row = k #row with the largest pivot
        max_val = abs(A[k,k])
        for i in range(k+1, n):
            if abs(A[i,k]) > max_val:
                max_val = abs(A[i,k])
                max_row = i

        if max_row != k: #swap rows if the largest pivot is not in the current row
            A[[k, max_row]] = A[[max_row, k]]
            b[k], b[max_row] = b[max_row], b[k]

        if abs(A[k,k]) < 1.0e-14:  #for zero pivot
            print("Error: Matrix is singular")
            return None
        
        #elimination
        for i in range(k+1, n):
            factor= A[i,k]/A[k,k]
            for j in range(k, n):
                A[i,j] = A[i,j] - factor * A[k,j]
            b[i] = b[i] - factor * b[k]

    #back substitution
    x = np.zeros(n)
    for i in range(n-1, -1, -1): #start from last row
        sum_val = 0.0
        for j in range(i+1, n):
            sum_val = sum_val + A[i,j] * x[j] #sum of known x's
        x[i] = (b[i] - sum_val) / A[i,i]

    return x




