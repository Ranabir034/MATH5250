"""
Lab Assignment: Image Blurring with Parallelism
================================================
Generates a random N×N image, applies a 3×3 averaging filter
to produce a blurred (N-2)×(N-2) output, and measures walltime
for 1, 2, 4, and 8 parallel workers.
"""

from turtle import back

import numpy as np
import time
from multiprocessing import Pool

N = 5000                    
THREAD_COUNTS = [1, 2, 4, 8]

# ── Step 1: Generate a random image ───────────────────────────────────────────

def make_image(n, seed=42):
    rng = np.random.default_rng(seed)
    return rng.integers(0, 256, size=(n, n), dtype=np.uint8)

# ── Step 2: The blur kernel (runs inside each worker) ─────────────────────────

def blur_strip(strip):

    s = strip.astype(np.float32)

    blurred = (
        s[:-2, :-2] + s[:-2, 1:-1] + s[:-2, 2:] +   # top row of 3×3
        s[1:-1, :-2] + s[1:-1, 1:-1] + s[1:-1, 2:] + # middle row
        s[2:,  :-2] + s[2:,  1:-1] + s[2:,  2:]       # bottom row
    ) / 9.0

    return blurred.astype(np.uint8)

# ── Step 3: Split work across workers and run in parallel ─────────────────────

def blur_image(img, num_workers):

    ## Divide the image into horizontal strips and blur each strip on a separate worker (process), then stitch results back together.
    n = img.shape[0]

    # Interior rows: indices 1 … N-2 (the border rows have no full 3×3 neighborhood)
    interior_row_indices = np.arange(1, n - 1)

    # Split interior rows as evenly as possible across workers
    row_chunks = np.array_split(interior_row_indices, num_workers)

    # For each chunk, extract the strip including ±1 padding row above and below
    strips = [img[chunk[0] - 1 : chunk[-1] + 2] for chunk in row_chunks]

    # Launch workers — each blurs its own strip independently (no shared memory needed)
    with Pool(processes=num_workers) as pool:
        results = pool.map(blur_strip, strips)

    # Stack all strips back into a single (N-2) × (N-2) image
    return np.vstack(results)

# ── Main ──────────────────────────────────────────────────────────────────────

if __name__ == "__main__":

    print(f"Image size    : {N} × {N}")
    print(f"Blurred size  : {N-2} × {N-2}  (one border row/col removed on each side)")
    print(f"Filter        : 3×3 uniform average\n")

    # Generate the image once; all worker counts use the same image
    img = make_image(N)

    print(f"{'Workers':>8}  {'Walltime (s)':>14}  {'Speedup':>8}")
    print("─" * 38)

    baseline_time = None

    for num_workers in THREAD_COUNTS:

        t_start = time.time()
        blurred  = blur_image(img, num_workers)
        elapsed  = time.time() - t_start

        if baseline_time is None:
            baseline_time = elapsed          # single-worker time is the reference

        speedup = baseline_time / elapsed

        print(f"{num_workers:>8}  {elapsed:>14.4f}  {speedup:>8.2f}x")

    print(f"\nFinal blurred image shape : {blurred.shape}")
    print(f"Pixel value range         : {blurred.min()} – {blurred.max()}")
