import cv2
import numpy as np
import time
from matplotlib import pyplot as plt

image = cv2.imread("lenna.png", cv2.IMREAD_GRAYSCALE)

gx = np.array([[-1,0,1],[-2,0,2],[-1,0,1]])
gy = np.array([[-1,-2,-1],[0,0,0],[1,2,1]])

rows,cols = image.shape
image_X = image.astype(np.uint8)
image_Y = image.astype(np.uint8)

image_X = cv2.filter2D(image,-1,gx)
image_Y = cv2.filter2D(image,-1,gy)

cv2.imshow("image",image)
cv2.imwrite('./106502601_image.png',image)
cv2.imshow("image_sobelx",image_X)
cv2.imwrite('./106502601_sobelx.png',image_X)
cv2.imshow("image_sobely",image_Y)
cv2.imwrite('./106502601_sobely.png',image_Y)
cv2.waitKey(0)
cv2.destroyAllWindows()
