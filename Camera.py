
import cv2

video_capture = cv2.VideoCapture(0) 
print ('WIDTH',video_capture.get(3),'HEIGHT',video_capture.get(4)) 

video_capture.set(3,960) 
video_capture.set(4,720) 

while True:
    ret, frame = video_capture.read()
    cv2.imshow('Video', frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break;

# When everything is done, release the capture
video_capture.release()
cv2.destroyAllWindows()
