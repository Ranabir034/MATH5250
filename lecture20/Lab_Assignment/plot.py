import numpy as np
import matplotlib.pyplot as plt

# ── Plot 1: Electrostatic Potential ──────────────────────
d = np.loadtxt("potential.dat")
x0, Vx = d[:, 0], d[:, 1]

fig, ax = plt.subplots(figsize=(7, 4))
ax.plot(x0, Vx, "b-", linewidth=2)
ax.set_xlabel(r"$x_0$", fontsize=13)
ax.set_ylabel(r"$V(x_0)$", fontsize=13)
ax.set_title(r"1D Electrostatic Potential  $(\rho = e^{-x^2})$", fontsize=13)
ax.grid(True, linestyle="--", alpha=0.5)
fig.tight_layout()
fig.savefig("potential.png", dpi=150)
print("Saved potential.png")

# ── Plot 2: Bessel Function J0 ────────────────────────────
d2 = np.loadtxt("bessel.dat")
x, J0 = d2[:, 0], d2[:, 1]

fig2, ax2 = plt.subplots(figsize=(8, 4))
ax2.plot(x, J0, "r-", linewidth=2)
ax2.axhline(0, color="k", linewidth=0.6)
ax2.set_xlabel(r"$x$", fontsize=13)
ax2.set_ylabel(r"$J_0(x)$", fontsize=13)
ax2.set_title(r"Bessel Function $J_0(x)$,  $x \in [0, 50]$", fontsize=13)
ax2.grid(True, linestyle="--", alpha=0.5)
fig2.tight_layout()
fig2.savefig("bessel.png", dpi=150)
print("Saved bessel.png")

plt.show()