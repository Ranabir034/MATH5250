import numpy as np
import matplotlib.pyplot as plt

# Parameters
r = 0.5
k = 100
P0 = 10
tol = 0.5 # tolerance level

def exact_sol(t, r=r, k=k, P0=P0):
    t = np.asarray(t)
    return k / (1 + ((k - P0) / P0) * np.exp(-r * t))

def euler_approx(t_end, dt, r=r, k=k, P0=P0, tol=tol):
    t = np.arange(0, t_end + dt, dt)
    P = np.zeros(len(t))
    P[0] = P0
    
    for i in range(len(t) - 1):
        dPdt = r * P[i] * (1 - P[i] / k)
        P[i + 1] = P[i] + dt * dPdt
    
    P_exact = exact_sol(t, r, k, P0)
    max_error = np.max(np.abs(P - P_exact))
    
    if max_error > tol:
        print(f"  dt = {dt}: max error = {max_error:.6f} (exceeds tol = {tol})")
    else:
        print(f"  dt = {dt}: max error = {max_error:.6f} (within tol = {tol})")
    
    return t, P

def half_capacity_time(r=r, k=k, P0=P0):
    return (1 / r) * np.log((k - P0) / P0)

# main execution
if __name__ == "__main__":
    t_exact = np.linspace(0, 20, 200)
    
    # task 1: exact solution
    P_exact = exact_sol(t_exact)
    
    # task 2: euler approximation with tolerance check
    print(f"\nForward Euler convergence (tol = {tol}):")
    t_euler1, P_euler1 = euler_approx(20, dt=0.5)
    t_euler2, P_euler2 = euler_approx(20, dt=0.01)
    
    # task 3: time to reach k/2
    t_half = half_capacity_time()
    P_half = k / 2
    print(f"\nTime when population reaches k/2 = {k/2}: t = {t_half:.4f}")
    
    # Plotting
    plt.figure(figsize=(8, 6))
    plt.plot(t_exact, P_exact, 'k-', label='Exact Solution', linewidth=2)
    plt.plot(t_euler1, P_euler1, 'r--', label='Euler dt=0.5')
    plt.plot(t_euler2, P_euler2, 'g-.', label='Euler dt=0.1')
    plt.axhline(y=P_half, color='b', linestyle=':', label='k/2')
    plt.axvline(x=t_half, color='m', linestyle=':', label=f't={t_half:.2f}')
    plt.plot(t_half, P_half, 'bo', markersize=10)
    plt.title('Logistic Growth: Exact vs Euler Approximation')
    plt.xlabel('Time t')
    plt.ylabel('Population P(t)')
    plt.legend()
    plt.grid(True, alpha=0.3)
    plt.xlim(0, 20)
    plt.ylim(0, k + 10)
    
    plt.savefig('logistic_growth_comparison.png', dpi=300)
    print("Plot saved as 'logistic_growth_comparison.png'")