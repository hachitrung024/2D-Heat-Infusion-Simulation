import numpy as np
import matplotlib.pyplot as plt
import matplotlib.colors as mcolors
import sys
import os

if len(sys.argv) < 3:
    print("Usage: python compare_heatmap_center.py <input_csv> <output_csv>")
    sys.exit(1)

input_path = sys.argv[1]
output_path = sys.argv[2]

A = np.loadtxt(input_path, delimiter=',')
B = np.loadtxt(output_path, delimiter=',')

if A.shape != B.shape:
    print("Error: input and output matrices must have the same size!")
    sys.exit(1)

# Cắt vùng trung tâm 600x600
h, w = A.shape
ch, cw = h // 2, w // 2
r = 300
A_c = A[ch - r:ch + r, cw - r:ch + r]
B_c = B[ch - r:ch + r, cw - r:ch + r]
diff = B_c - A_c

# Tìm giá trị cực đại để scale
vmin = min(A_c.min(), B_c.min())
vmax = max(A_c.max(), B_c.max())

# Dùng scale logarit để dễ thấy thay đổi vùng nóng
norm = mcolors.PowerNorm(gamma=0.5, vmin=vmin, vmax=vmax)  # gamma < 1 => sáng hơn vùng cao

fig, axes = plt.subplots(1, 3, figsize=(16, 5))

# Input
im0 = axes[0].imshow(A_c, cmap='plasma', norm=norm)
axes[0].set_title("Input Center (600×600)")
axes[0].axis('off')
plt.colorbar(im0, ax=axes[0], fraction=0.046, pad=0.04)

# Output
im1 = axes[1].imshow(B_c, cmap='plasma', norm=norm)
axes[1].set_title("Output Center (600×600)")
axes[1].axis('off')
plt.colorbar(im1, ax=axes[1], fraction=0.046, pad=0.04)

# Difference
vmax_diff = np.max(np.abs(diff))
im2 = axes[2].imshow(diff, cmap='seismic', vmin=-vmax_diff, vmax=vmax_diff)
axes[2].set_title("Difference (Output - Input)")
axes[2].axis('off')
plt.colorbar(im2, ax=axes[2], fraction=0.046, pad=0.04)

plt.tight_layout()

# Lưu ảnh
out_name = os.path.splitext(os.path.basename(output_path))[0] + "_compare.png"
plt.savefig(out_name, bbox_inches='tight', dpi=300)
plt.show()

print(f"Saved figure: {out_name}")
