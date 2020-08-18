import cv2

def detectAndDisplay(frame,face_cascade):
    frame_gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    frame_gray = cv2.equalizeHist(frame_gray)
    faces = face_cascade.detectMultiScale(frame_gray)
    for (x, y, w, h) in faces:
        center = (x + w // 2, y + h // 2)
        frame = cv2.ellipse(frame, center, (w // 2, h // 2), 0, 0, 360, (255, 0, 255), 4)
    cv2.imshow("Iron Cat Face Detection", frame)

face_cascade1 = cv2.CascadeClassifier()
if not face_cascade1.load("data/lbpcascade_frontalface_improved.xml"):
    print("Error loading face human")
    exit(0)
face_cascade2 = cv2.CascadeClassifier()
if not face_cascade2.load("data/lbpcascade_frontalcatface.xml"):
    print("Error loading face cat")
    exit(0)

face_cascade = cv2.CascadeClassifier()
face_cascade = face_cascade1

cap = cv2.VideoCapture("Iron_Cat.mp4")
if not cap.isOpened:
    print("Error opening video capture")
    exit(0)

while True:
    ret, frame = cap.read()
    if frame is None:
        break
    detectAndDisplay(frame,face_cascade);
    k = cv2.waitKey(10) & 0xFF
    if k == ord('q'):
        break
    if k == ord('a'):
        face_cascade = face_cascade1
    if k == ord('s'):
        face_cascade = face_cascade2

cap.release()
cv2.destroyAllWindows()
