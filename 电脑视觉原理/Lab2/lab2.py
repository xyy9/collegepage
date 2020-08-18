import cv2
import numpy as np

image = cv2.imread('detention_1.jpg', cv2.IMREAD_GRAYSCALE)

x = image.shape
width = x[0]
height = x[1]

transfer_img0 = 255 - image
transfer_img0 = transfer_img0.astype(np.uint8)

a = np.log10(1.0 + image)
c = 255/a.max()
transfer_img1 = c*np.log10(1.0 + image)
transfer_img1 = np.uint8(transfer_img1 + 0.5)

output = image.astype(np.uint8)
for i in range(0, width):
    for j in range(0,height):
        if j <= height/2:
            output[i,j] = transfer_img0[i,j]
        else:
            output[i,j] = transfer_img1[i,j]

cv2.imshow("Image", image)
cv2.imshow("Output", output)
cv2.imwrite('./106502601_output.png', output)
cv2.waitKey(0)
cv2.destroyAllWindows()
