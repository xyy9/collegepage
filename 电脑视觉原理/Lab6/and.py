import numpy as np
kernel = np.array([
    [0, 255, 0],
    [255, 255, 255],
    [0, 255, 0]], dtype=np.uint8)
img = np.array([
    [0, 0, 255],
    [0, 255, 255],
    [255, 255, 255]], dtype=np.uint8)
print(np.bitwise_and(img,kernel))