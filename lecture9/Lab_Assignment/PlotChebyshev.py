import numpy as np
import matplotlib.pyplot as plt

def PlotChebyshev():
    data = np.loadtxt('Chebyshev.dat')
    x = data[:, 0]
    y = data[:, 1]

    plt.rc("font", size=14)
    plt.figure(1, figsize=(8, 5))
    plt.plot(x, y, linestyle="-", linewidth=2, color="blue")
    plt.xlim(0, 1.0)
    plt.xticks([0.0, 0.3, 0.5, 0.8, 1.0])
    ax = plt.gca()
    ax.grid(True)
    plt.xlabel("x-axis", size=16)
    plt.ylabel("y-axis", size=16)
    plt.title("Chebyshev Polynomial Expansion", size=16)
    plt.tight_layout()
    plt.savefig('Chebyshev.png', dpi=200, bbox_inches='tight')
    print(" Plot saved to Chebyshev.png")
    plt.show()

if __name__ == "__main__":
    PlotChebyshev()