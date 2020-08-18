import cv2
import numpy as np

#read mask and image
mask = cv2.imread("mask.jpg")
image = cv2.imread("test.jpg")

#RGBtoHSV
image0 = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
mask0 = cv2.cvtColor(mask, cv2.COLOR_BGR2HSV)

#Find blue color to binary
lower_blue = np.array([100,43,46])
upper_blue = np.array([124,255,255])
mask0 = cv2.inRange(mask0,lower_blue,upper_blue)

#Filter RGB imgae
image = cv2.bitwise_and(image,image,mask = mask0)

#mask rcnn return boxes' points
y1 = 62
x1 = 313
y2 = 647
x2 = 987

#crop image
crop_img = image[y1:y2,x1:x2]

#save and show
cv2.imwrite("target.jpg",crop_img)
cv2.imshow("image",crop_img)
cv2.waitKey(0)
