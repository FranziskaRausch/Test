import cv2
import numpy as np
names = ['Ressources\\production ID_4945121.mp4', 'Ressources\\production ID_4468823.mp4'];
window_titles = ['first', 'second']
#cap = cv2.VideoCapture('Ressources\\production ID_4945121.mp4')
#cap2 =cv2.VideoCapture('Ressources\\production ID_4468823.mp4')

cap = [cv2.VideoCapture(i) for i in names]

frames = [None] * len(names);
gray = [None] * len(names);
ret = [None] * len(names);
#cv2.namedWindow
#cv2.resizeWindow (fx=0.5, fy=0.5, interpolation=cv2.INTER_AREA)

while True:

    for i,c in enumerate(cap):
        if c is not None:
            ret[i], frames[i] = c.read();


    for i,f in enumerate(frames):
        if ret[i] is True:
            gray[i] = cv2.cvtColor(f, cv2.COLOR_BGR2GRAY)
            cv2.imshow(window_titles[i], gray[i]);

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break


for c in cap:
    if c is not None:
        c.release();

cv2.destroyAllWindows()