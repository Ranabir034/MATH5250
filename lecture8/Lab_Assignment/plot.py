import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt("lab8_output.dat", skiprows=1)
x = data[:, 0]
my_exp = data[:, 1]
lib_exp = data[:, 2]
plt.figure(figsize=(10, 6))
plt.plot(x, lib_exp, label="math.h exp(x)", linewidth=2.5, color="royalblue")
plt.plot(x, my_exp, label="Custom Taylor exp(x)", linewidth=2, color="tomato", linestyle="--")
plt.xlabel("x", fontsize=14)
plt.ylabel("exp(x)", fontsize=14)
plt.title("Custom exp(x) vs math.h exp(x)", fontsize=14, fontweight="bold")
plt.legend(fontsize=12)
plt.grid(True, linestyle="--", alpha=0.5)
plt.tick_params(labelsize=12)
plt.savefig("exp_comparison.png", dpi=200, bbox_inches="tight")
print("Plot saved to exp_comparison.png")
plt.show()