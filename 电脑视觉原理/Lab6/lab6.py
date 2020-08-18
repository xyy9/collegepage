import numpy as np
import cv2

img = cv2.imread("j.png", 0)
o_img = cv2.imread("opening_j.png", 0)
c_img = cv2.imread("closing_j.png", 0)
kernel = np.array([
    [0, 255, 0],
    [255, 255, 255],
    [0, 255, 0]
], dtype=np.uint8)
col = np.array([[-1, -1, -1], [0, 0, 0], [1, 1, 1]])
row = np.array([[-1, 0, 1], [-1, 0, 1], [-1, 0, 1]])


def dilate_(img, kernel, iterations=1):
    my_img = img.copy()
    for iters in range(iterations):
        masked_img = np.pad(img, (1, 1), "constant")
        my_img = np.zeros(my_img.shape,dtype = np.uint8)
        for i in range(1, masked_img.shape[0] - 1):
                for j in range(1, masked_img.shape[1] - 1):
                    if (np.bitwise_and(masked_img[col + i, row + j],kernel)==255).any():
                        my_img[i-1,j-1] = 255
    return my_img


def erosion_(img, kernel, iterations=1):
    my_img = img.copy()
    for iters in range(iterations):
        masked_img = np.pad(img, (1, 1), "constant")
        my_img = np.zeros(my_img.shape,dtype = np.uint8)
        for i in range(1, masked_img.shape[0] - 1):
                for j in range(1, masked_img.shape[1] - 1):
                    if (np.bitwise_and(masked_img[col + i, row + j],kernel)==kernel).all():
                        my_img[i-1,j-1] = 255
    return my_img


def open_(img, kernel, iterations):
    my_img = img.copy()
    for iters in range(iterations):
        my_img = erosion_(my_img, kernel, iterations=1)
    for iters in range(iterations):
            my_img = dilate_(my_img, kernel, iterations=1)
    return my_img


def close_(img, kernel, iterations):
    my_img = img.copy()
    for iters in range(iterations):
        my_img = dilate_(my_img, kernel, iterations=1)
    for iters in range(iterations):
            my_img = erosion_(my_img, kernel, iterations=1)
    return my_img



dilation_output = dilate_(img, kernel, iterations=1)
erosion_output = erosion_(img, kernel, iterations=1)
opening_output = open_(o_img, kernel, iterations=2)
closing_output = close_(c_img, kernel, iterations=2)

cv2.imshow("my_answer_dilation", dilation_output)
cv2.imshow("my_answer_erosion", erosion_output)
cv2.imshow("my_answer_opening", opening_output)
cv2.imshow("my_answer_closing", closing_output)

cv2.imwrite("dilation.jpg", dilation_output)
cv2.imwrite("erosion.jpg", erosion_output)
cv2.imwrite("opening.jpg", opening_output)
cv2.imwrite("closing.jpg", closing_output)
cv2.waitKey(0)
