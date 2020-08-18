import numpy as np

col = np.array([[-1, -1, -1], [0, 0, 0], [1, 1, 1]])
row = np.array([[-1, 0, 1], [-1, 0, 1], [-1, 0, 1]])
img = np.array([
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 9]
], dtype=np.uint8)
masked_img = np.pad(img, (1, 1), "constant")
for i in range(1, masked_img.shape[0] - 1):
    for j in range(1, masked_img.shape[1] - 1):
        print(masked_img[col + i, row + j])