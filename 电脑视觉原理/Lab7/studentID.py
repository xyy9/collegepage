import cv2
import numpy as np
from math import atan2, sqrt, pi

## read image
grayImage = cv2.imread('olaf.jpg', cv2.IMREAD_GRAYSCALE)

## convert to binary image

## morphological
kernel = np.ones((3, 3), np.uint8)


## find and draw contours

## PCA analysis

## center of the object, rotational angle, length of the major axis and minor axis

## draw center circle and ellipse


## show images and write image
cv2.imshow('Gray image', grayImage)
cv2.imshow('Binary image', binaryImage)
cv2.imshow('Morphological', opening)
cv2.imshow('PCA ellipse', pca_ellipse)

cv2.imwrite("PCA_ellipse.jpg", pca_ellipse)

cv2.waitKey(0)
cv2.destroyAllWindows()
