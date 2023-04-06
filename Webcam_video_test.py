#cv2 is used for OpenCV library
import cv2
import time
import simpleaudio as sa

# insert Video and Soundfile here
video = cv2.VideoCapture('Ressources\\Laufband_Video.mp4')
wave_obj = sa.WaveObject.from_wave_file('Ressources\\Run_Musik.wav')
wave_obj.play() # Start Music
# ENTER HERE THE LENGTH OF THE VIDEO IN MILLISECONDS (duration = xyz)
duration = 17000
cap = cv2.VideoCapture(0) # WEBCAM

start = round(time.time()*1000)
diff = round(time.time()*1000) - start
while(diff < duration):
    ret,frame = video.read() # Start playing the Video
    frame = cv2.resize(frame, None, fx=0.2, fy=0.2) # size of the screen window - Attention Video will be distorted or filled with black if it is too small/too big.
    diff = round(time.time()*1000) - start
    if ret == True:
        cv2.imshow("Run Video",frame)
    if cv2.waitKey(2) & 0xFF == ord('q'): # the video can be closed by pressing Q
        break
while(cap.isOpened()):
        ret, frame = cap.read()
        cv2.imshow('frame', frame)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

cap.release()
video.release()
cv2.destroyAllWindows()