#cv2 is used for OpenCV library
import cv2
import time
import simpleaudio as sa


video = cv2.VideoCapture('Ressources\\production ID_4945121.mp4')
wave_obj = sa.WaveObject.from_wave_file('Ressources\\Alzmetall Bohrer.wav')
wave_obj.play()
# HIER LÄNGE DES VIDEOS IN MILLISEKUNDEN EINGEBEN (duration = xyz)
duration = 13000
cap = cv2.VideoCapture(0)

start = round(time.time()*1000)
diff = round(time.time()*1000) - start
while(diff < duration):
    ret,frame = video.read()
    frame = cv2.resize(frame, None, fx=0.2, fy=0.2)
    diff = round(time.time()*1000) - start
    if ret == True:
        cv2.imshow("Run Video",frame)
    if cv2.waitKey(2) & 0xFF == ord('q'):
        break
while(cap.isOpened()):
        ret, frame = cap.read()
        cv2.imshow('frame', frame)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

cap.release()
video.release()
cv2.destroyAllWindows()