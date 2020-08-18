import numpy as np
import cv2
import matplotlib.pyplot as plt

image = cv2.imread('photo.jpg',cv2.IMREAD_GRAYSCALE)

x = image.shape
weight = x[0]
height = x[1]
n = [0] * 256

for i in range(0, weight):
    for j in range(0, height):
        n[image[i, j]] += 1
        
print(n)
plt.bar(range(0,256),n)
plt.savefig('106502601.png')
plt.show()
