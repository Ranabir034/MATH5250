# demo_demofuncs.py
E = 2.718281828459045

def demo_factorial(n):
    if n < 0:
        raise ValueError("Factorial undefined for negative numbers")
    
    s = 1
    for k in range(1, n):
        s = s * (k + 1)
    return s


def demo_exp(x):
    x0 = int(round(x))
    z = x - x0
    
    if x0 >= 0:
        e_x0 = 1.0
        for _ in range(x0):
            e_x0 *= E
    else:
        e_x0 = 1.0
        for _ in range(-x0):
            e_x0 /= E
    
    e_z = 1.0
    term = 1.0
    for n in range(1, 50): 
        term *= z / n
        e_z += term
        if abs(term) < 1e-16:  # convergence check
            break
    
    return e_x0 * e_z


def demo_ln(x):

    if x <= 0:
        raise ValueError("ln(x) undefined for x <= 0")
    
    # initial guess based on range of x
    if x < 0.1:
        s = -2.0
    elif x < 1:
        s = x - 1  
    elif x < 3:
        s = x - 1
    else:
        s = 1.0
        temp = x
        while temp > E:
            temp /= E
            s += 1
    
    # newton's method iteration
    for _ in range(100):
        exp_neg_s = demo_exp(-s)
        s_new = s - 1 + x * exp_neg_s
        
        if abs(s_new - s) < 1e-15:  # convergence check
            break
        s = s_new
    
    return s

# main program
if __name__ == "__main__":
    import math
    
    print("Testing demo_factorial(n):")
    print("-" * 50)
    for n in range(11):
        demo_result = demo_factorial(n)
        actual = math.factorial(n)
        print(f"{n}! = {demo_result:10d}  (math.factorial = {actual:10d})")
    
    print("\n\nTesting demo_exp(x):")
    print("-" * 50)
    test_values = [-5, -2, -1, -0.5, 0, 0.5, 1, 2, 3, 5, 10]
    for x in test_values:
        demo_result = demo_exp(x)
        actual = math.exp(x)
        error = abs(demo_result - actual)
        print(f"exp({x:6.2f}): demo_exp = {demo_result:18.12f}, "
              f"math.exp = {actual:18.12f}, error = {error:.2e}")
    
    print("\n\nTesting demo_ln(x):")
    print("-" * 50)
    test_values = [0.01, 0.1, 0.5, 1, 2, 2.718281828, 5, 10, 100]
    for x in test_values:
        demo_result = demo_ln(x)
        actual = math.log(x)
        error = abs(demo_result - actual)
        print(f"ln({x:10.6f}): demo_ln = {demo_result:18.12f}, "
              f"math.log = {actual:18.12f}, error = {error:.2e}")