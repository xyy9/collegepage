import numpy as np
import cv2

cap = cv2.VideoCapture('minion_video.avi')

while(cap.isOpened()):
    ret, frame = cap.read()
    b, g, r = cv2.split(frame)
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    cv2.imshow('106502601_original_frame',frame)
    cv2.imshow('106502601_gray_frame',gray)
    key = cv2.waitKey(1) & 0xFF 
    if key == ord('r'):
        r = cv2.merge([0*b,0*g,1*r])
        cv2.imwrite('./106502601_Capture_r.png', r)
    if key == ord('g'):
        g = cv2.merge([0*b,1*g,0*r])
        cv2.imwrite('./106502601_Capture_g.png', g)
    if key == ord('b'):
        b = cv2.merge([1*b,0*g,0*r])
        cv2.imwrite('./106502601_Capture_b.png', b)
    if key == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
