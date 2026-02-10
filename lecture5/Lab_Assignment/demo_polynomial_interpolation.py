import numpy as np
from GE import GaussElimination

x_pts = np.array([-0.1, -0.02, 0.02, 0.1])
y_pts = np.cos(x_pts)

A = np.column_stack([x_pts**3, x_pts**2, x_pts, np.ones(4)])
b = y_pts

print("Matrix A:")
print(A)
print("\nVector b:", b)

coeffs = GaussElimination(A, b)
a, b_coef, c, d = coeffs

print("\nPolynomial coefficients:")
print(f"  a = {a:.6e}")
print(f"  b = {b_coef:.6e}")
print(f"  c = {c:.6e}")
print(f"  d = {d:.6e}")

p_vals = a*x_pts**3 + b_coef*x_pts**2 + c*x_pts + d
errors = np.abs(y_pts - p_vals)

print("\nInterpolation results:")
print("    x        cos(x)           p(x)            error")

for i in range(4):
    print(f"  {x_pts[i]:6.2f}   {y_pts[i]:.6f}   {p_vals[i]:.6f}   {errors[i]:.2e}")

print(f"\nMaximum error: {np.max(errors):.6e}")


