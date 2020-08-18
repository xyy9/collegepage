import cv2
import numpy as np
import math
from math import atan2, sqrt, pi

## read image
grayImage = cv2.imread('olaf.jpg', cv2.IMREAD_GRAYSCALE)

## convert to binary image
ret,binaryImage = cv2.threshold(grayImage,250,255,cv2.THRESH_BINARY_INV)

## morphological
kernel = np.ones((3, 3), np.uint8)
opening = cv2.morphologyEx(binaryImage,cv2.MORPH_OPEN,kernel)

## find and draw contours
contours,hierarchy = cv2.findContours(opening,cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)
pca_ellipse = cv2.cvtColor(opening,cv2.COLOR_GRAY2BGR)
cv2.drawContours(pca_ellipse ,contours,-1,(0,0,255),2)
contours = np.array(contours)
data_pts = np.array(contours[0],dtype = np.float64)
data_pts = np.squeeze(data_pts,axis = (1,))

## PCA analysis
mean = np.empty((0))
mean,eigenvectors,eigenvalues = cv2.PCACompute2(data_pts,mean)

## center of the object, rotational angle, length of the major axis and minor axis
a = eigenvalues[0] ** 0.5
b = eigenvalues[1] ** 0.5
theta = math.degrees(atan2(eigenvectors[0,1],eigenvectors[0,0]))

## draw center circle and ellipse
cntr = (int(mean[0,0]),int(mean[0,1]))
cv2.circle(pca_ellipse,cntr,3,(255,0,0),2)
cv2.ellipse(pca_ellipse,cntr,(2*a,2*b),theta,0,360,(0,255,0),2)

## show images and write image
cv2.imshow('Gray image', grayImage)
cv2.imshow('Binary image', binaryImage)
cv2.imshow('Morphological', opening)
cv2.imshow('PCA ellipse', pca_ellipse)

cv2.imwrite("PCA_ellipse.jpg", pca_ellipse)

cv2.waitKey(0)
cv2.destroyAllWindows()


