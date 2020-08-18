import numpy as np
import cv2

cap = cv2.VideoCapture("Lab4.mp4")
while(cap.isOpened()):
    ret, frame = cap.read()
    if frame is None:
        break

    image = frame.copy()
    image = cv2.GaussianBlur(image,(3,3),2)
    image1 = cv2.cvtColor(image, cv2.COLOR_BGR2YCR_CB)
    mask = ((image1[:,:,1] >= 133)&(image1[:,:,1] <= 177))&((image1[:,:,2] >= 98)&(image1[:,:,2] <= 122))

    
    mask = mask.astype(np.uint8)
    mask = cv2.erode(mask, np.ones((3,3), np.uint8))
    mask = cv2.dilate(mask,np.ones((3,3),np.uint8))
    contours, hierarchy = cv2.findContours(mask,cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)

    mask = mask.astype(np.bool)
    image2 = image.copy()
    image2[~mask] = (0,0,0)
    cv2.drawContours(image2, contours,-1,(0,255,0),1)
    
    cv2.imshow("image",image2)
    cv2.imshow("frame", frame)
    if cv2.waitKey(0) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
