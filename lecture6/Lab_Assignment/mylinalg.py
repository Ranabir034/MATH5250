import numpy as np
import matplotlib.pyplot as plt

from GE import GaussElimination

def LeastSquareApprox(x, f, n):
    m = len(x)
    A = np.zeros((m, n+1))
    for i in range(m):
        for j in range(n+1):
            A[i,j] = x[i]**(n-j)

    ATA = np.dot(A.T, A)
    ATf = np.dot(A.T, f)

    coeffs = GaussElimination(ATA, ATf)
    return coeffs

def evaluate_poly(coeffs, x):
    n = len(coeffs) - 1
    result = np.zeros_like(x, dtype=float)
    for i,c in enumerate(coeffs):
        result += c * x**(n - i)
    return result


if __name__ == "__main__":
    print("Testing Least Square Polynomial Approximation")
    print("="*60)
    print("Approximating f(x) = cos(x) with polynomial of degree <= 5")
    print("at 51 nodes from -pi to pi")
    print("="*60)

    x_data = np.linspace(-np.pi, np.pi, 51)
    f_data = np.cos(x_data)
    degree = 5

    coeffs = LeastSquareApprox(x_data, f_data, degree)
    print("Computed polynomial coefficients (highest degree first):")

    for i,c in enumerate(coeffs):
        print(f"  a_{degree-i} = {c:.6e}")

    p_data = evaluate_poly(coeffs, x_data)

    #compute error
    error = np.linalg.norm(f_data - p_data, ord=2)
    max_error = np.max(np.abs(f_data - p_data))
    rms_error = np.sqrt(np.mean((f_data - p_data)**2))
    print(f"\nMaximum absolute error: {max_error:.6e}")
    print(f"RMS error: {rms_error:.6e}")

    
    #plotting
    plt.figure(figsize=(8,6))
    plt.plot(x_data, f_data, 'b-', label='f(x) = cos(x)')
    plt.plot(x_data, p_data, 'r--', label=f'Polynomial Degree {degree}')
    plt.title('Least Square Polynomial Approximation of cos(x)')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.legend()
    plt.grid()
    plt.show()
    plt.savefig('least_square_approximation.png')
    plt.close()

    #error plot
    plt.figure(figsize=(8,6))
    plt.plot(x_data, np.abs(f_data - p_data), 'm.-', label='Absolute Error at Data Points')
    plt.title('Error in Least Square Polynomial Approximation')
    plt.xlabel('x')
    plt.ylabel('Absolute Error')
    plt.legend()
    plt.grid()
    plt.show()
    plt.savefig('approximation_error.png')
    plt.close()
    




