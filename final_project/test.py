"""Auxiliary background figures for the extended deck."""
import matplotlib.pyplot as plt
import matplotlib.patches as mp
import numpy as np

plt.rcParams.update({
    "font.family": "sans-serif",
    "font.size": 11,
    "axes.spines.top": False,
    "axes.spines.right": False,
})

NAVY  = "#065A82"
TEAL  = "#1C7293"
INK   = "#21295C"
ACC   = "#E8853A"
MUTED = "#5F6B7A"

# AUX 1: Biaxial test schematic
fig, ax = plt.subplots(figsize=(8, 5))
ax.set_xlim(-1, 11); ax.set_ylim(-1, 9)
ax.set_aspect('equal'); ax.axis('off')
spec = mp.FancyBboxPatch((3.5, 2.5), 3, 3, boxstyle="round,pad=0.0,rounding_size=0.3",
                         facecolor="#FAEDE0", edgecolor=ACC, linewidth=2)
ax.add_patch(spec)
ax.text(5, 4, "tissue\nspecimen", ha="center", va="center", fontsize=11, color=INK, fontweight="bold")
for y in [3.0, 3.5, 4.0, 4.5, 5.0]:
    ax.plot([3.5, 2.5], [y, y], color=NAVY, lw=1.3)
    ax.plot(2.5, y, 'o', color=NAVY, markersize=5)
    ax.plot([6.5, 7.5], [y, y], color=NAVY, lw=1.3)
    ax.plot(7.5, y, 'o', color=NAVY, markersize=5)
for x in [4.0, 4.5, 5.0, 5.5, 6.0]:
    ax.plot([x, x], [5.5, 6.5], color=NAVY, lw=1.3)
    ax.plot(x, 6.5, 'o', color=NAVY, markersize=5)
    ax.plot([x, x], [2.5, 1.5], color=NAVY, lw=1.3)
    ax.plot(x, 1.5, 'o', color=NAVY, markersize=5)
ax.annotate('', xy=(1.3, 4), xytext=(2.3, 4), arrowprops=dict(arrowstyle='->', color=ACC, lw=2.5))
ax.annotate('', xy=(8.7, 4), xytext=(7.7, 4), arrowprops=dict(arrowstyle='->', color=ACC, lw=2.5))
ax.annotate('', xy=(5, 7.7), xytext=(5, 6.7), arrowprops=dict(arrowstyle='->', color=ACC, lw=2.5))
ax.annotate('', xy=(5, 0.3), xytext=(5, 1.3), arrowprops=dict(arrowstyle='->', color=ACC, lw=2.5))
ax.text(0.4, 4, r"$F_1, \lambda_1$", fontsize=14, color=ACC, ha="left", va="center", fontweight="bold")
ax.text(9.6, 4, r"$F_1, \lambda_1$", fontsize=14, color=ACC, ha="right", va="center", fontweight="bold")
ax.text(5, 8.3, r"$F_2, \lambda_2$", fontsize=14, color=ACC, ha="center", va="bottom", fontweight="bold")
ax.text(5, -0.3, r"$F_2, \lambda_2$", fontsize=14, color=ACC, ha="center", va="top", fontweight="bold")
ax.annotate('', xy=(0.6, 1), xytext=(0, 1), arrowprops=dict(arrowstyle='->', color=MUTED, lw=1))
ax.annotate('', xy=(0, 1.6), xytext=(0, 1), arrowprops=dict(arrowstyle='->', color=MUTED, lw=1))
ax.text(0.7, 0.95, r"$x_1$", fontsize=11, color=MUTED, va="center")
ax.text(0.05, 1.7, r"$x_2$", fontsize=11, color=MUTED)
ax.set_title("Planar biaxial mechanical test", fontsize=13, color=INK, fontweight="bold", pad=10)
plt.tight_layout()
plt.savefig("aux_biaxial_test.png", dpi=160, bbox_inches="tight", facecolor="white")
plt.close()

# AUX 2: Matrix vs fiber
fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(10, 4))
ax1.set_xlim(0, 10); ax1.set_ylim(0, 6); ax1.set_aspect('equal'); ax1.axis('off')
np.random.seed(7)
for _ in range(80):
    x, y = np.random.uniform(1, 9), np.random.uniform(1, 5)
    ax1.plot(x, y, 'o', color="#B5D2DD", markersize=6, alpha=0.7)
ax1.add_patch(mp.Rectangle((1, 1), 8, 4, fill=False, edgecolor=NAVY, linewidth=2))
ax1.set_title("Ground matrix (isotropic)\nneo-Hookean term: c (I₁−3)/2", fontsize=12, color=INK, fontweight="bold", pad=8)
ax2.set_xlim(0, 10); ax2.set_ylim(0, 6); ax2.set_aspect('equal'); ax2.axis('off')
ax2.add_patch(mp.Rectangle((1, 1), 8, 4, fill=False, edgecolor=NAVY, linewidth=2))
for offset in np.linspace(-3.5, 7.5, 16):
    xs2 = np.linspace(1, 9, 200)
    ys2 = xs2 + offset - 4
    valid = (ys2 >= 1) & (ys2 <= 5)
    if valid.any():
        ax2.plot(xs2[valid], ys2[valid], '-', color=ACC, lw=1.5, alpha=0.7)
ax2.annotate('', xy=(6.5, 4.5), xytext=(5, 3), arrowprops=dict(arrowstyle='->', color=INK, lw=1.5))
ax2.plot([5, 6.5], [3, 3], color=INK, lw=1, linestyle='--')
ax2.annotate(r'$\alpha$', xy=(5.7, 3.25), fontsize=14, color=INK, fontweight='bold')
ax2.set_title("Collagen fibers (anisotropic)\nexponential term: f(I₄, k₁, k₂)", fontsize=12, color=INK, fontweight="bold", pad=8)
fig.suptitle("HGO model captures both contributions", fontsize=13, color=INK, fontweight="bold", y=1.02)
plt.tight_layout()
plt.savefig("aux_matrix_fiber.png", dpi=160, bbox_inches="tight", facecolor="white")
plt.close()

# AUX 3: Local vs global
fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(11, 4.5))
xs = np.linspace(0, 10, 200)
fxs = 5 + 2*np.sin(xs*0.8) + 0.3*xs
ax1.plot(xs, fxs, color=NAVY, lw=2)
opt_x = 6.0
opt_y = 5 + 2*np.sin(opt_x*0.8) + 0.3*opt_x
ax1.plot(opt_x, opt_y, 'o', color=ACC, markersize=14, zorder=5)
ax1.axvspan(opt_x-0.5, opt_x+0.5, alpha=0.3, color=ACC)
slope = 2*0.8*np.cos(opt_x*0.8) + 0.3
xs_tan = np.linspace(opt_x-1, opt_x+1, 20)
ax1.plot(xs_tan, opt_y + slope*(xs_tan-opt_x), '--', color=ACC, lw=1.5)
ax1.set_xlabel("parameter θ", fontsize=11)
ax1.set_ylabel("output Q(θ)", fontsize=11)
ax1.set_title("Local sensitivity\n∂Q/∂θ at one optimum point", fontsize=12, color=INK, fontweight="bold")
ax1.text(opt_x, opt_y+1.5, "fitted\noptimum", ha="center", fontsize=9, color=ACC)
ax1.grid(True, alpha=0.3)
ax2.plot(xs, fxs, color=NAVY, lw=2)
np.random.seed(3)
sample_xs = np.random.uniform(0, 10, 30)
sample_ys = 5 + 2*np.sin(sample_xs*0.8) + 0.3*sample_xs
ax2.scatter(sample_xs, sample_ys, color=ACC, s=50, zorder=5, edgecolor='white', lw=0.8)
ax2.axvspan(0, 10, alpha=0.12, color=NAVY)
ax2.set_xlabel("parameter θ", fontsize=11)
ax2.set_ylabel("output Q(θ)", fontsize=11)
ax2.set_title("Global sensitivity\nfull sweep across parameter space", fontsize=12, color=INK, fontweight="bold")
ax2.grid(True, alpha=0.3)
plt.tight_layout()
plt.savefig("aux_local_vs_global.png", dpi=160, bbox_inches="tight", facecolor="white")
plt.close()

# AUX 4: Saltelli matrices
fig, axes = plt.subplots(1, 6, figsize=(15, 3.2), gridspec_kw={'width_ratios': [1, 0.15, 1, 0.15, 1, 0.15]})
def draw_matrix(ax, label, matrix, highlight_col=None, fill_color="#B5D2DD"):
    ax.set_xlim(-0.5, 4); ax.set_ylim(-1, 6)
    ax.set_aspect('equal'); ax.axis('off')
    for r in range(5):
        for c in range(4):
            if highlight_col is not None and c == highlight_col:
                fc = ACC; ec = INK
            else:
                fc = fill_color; ec = NAVY
            ax.add_patch(mp.Rectangle((c, 4-r), 0.85, 0.85, facecolor=fc, edgecolor=ec, linewidth=0.5))
            ax.text(c+0.42, 4-r+0.42, f"{matrix[r,c]:.2f}", ha='center', va='center', fontsize=7, color=INK)
    ax.text(2, -0.5, label, ha='center', fontsize=12, fontweight='bold', color=INK)
    ax.text(2, 5.5, f"N rows × 4 cols", ha='center', fontsize=9, color=MUTED, style='italic')

rng = np.random.RandomState(42)
A_mat = rng.uniform(0, 1, (5, 4))
B_mat = rng.uniform(0, 1, (5, 4))
AB2 = A_mat.copy(); AB2[:, 1] = B_mat[:, 1]
draw_matrix(axes[0], "A", A_mat, None, "#B5D2DD")
axes[1].axis('off'); axes[1].text(0.5, 0.5, "+", ha='center', va='center', fontsize=20, color=MUTED, transform=axes[1].transAxes)
draw_matrix(axes[2], "B", B_mat, None, "#FAEDE0")
axes[3].axis('off'); axes[3].text(0.5, 0.5, "→", ha='center', va='center', fontsize=20, color=MUTED, transform=axes[3].transAxes)
draw_matrix(axes[4], r"$AB^{(2)}$  (col 2 of A swapped with B)", AB2, 1, "#B5D2DD")
axes[5].axis('off')
fig.suptitle("Saltelli matrix construction: 2 base + k cross-matrices", fontsize=13, color=INK, fontweight="bold", y=1.05)
plt.tight_layout()
plt.savefig("aux_saltelli_matrices.png", dpi=160, bbox_inches="tight", facecolor="white")
plt.close()

# AUX 5: Variance decomposition
fig, ax = plt.subplots(figsize=(8, 4.5))
labels = [r"$V_c$", r"$V_{k_1}$", r"$V_{k_2}$", r"$V_\alpha$", "interactions"]
values = [0.04, 0.30, 0.42, 0.10, 0.14]
colors = ["#4c72b0", "#55a868", "#c44e52", "#8172b3", "#A8B2BF"]
left = 0
for v, lab, col in zip(values, labels, colors):
    ax.barh(0, v, left=left, color=col, edgecolor='white', linewidth=1.5, height=0.5)
    if v > 0.05:
        ax.text(left + v/2, 0, lab, ha='center', va='center', fontsize=11, color='white', fontweight='bold')
    left += v
ax.set_xlim(0, 1.0); ax.set_ylim(-0.6, 1.1)
ax.set_yticks([])
ax.set_xlabel("fraction of total output variance", fontsize=11, color=INK)
ax.set_title("Variance decomposition\nVar(Q) = ΣVᵢ + ΣVᵢⱼ + … (here: HGO equibiaxial illustration)", fontsize=12, color=INK, fontweight="bold", pad=10)
ax.spines['left'].set_visible(False)
ax.grid(axis='x', alpha=0.3)
plt.tight_layout()
plt.savefig("aux_variance_decomp.png", dpi=160, bbox_inches="tight", facecolor="white")
plt.close()

print("done")