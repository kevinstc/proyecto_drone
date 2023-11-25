import cv2
import urllib.request # allow reading url
import numpy as np

url= 'http://192.168.1.127/cam-hi.jpg'
winName = 'CAM'
cv2.namedWindow(winName, cv2.WINDOW_AUTOSIZE)
scale_percent = 80 # percent of original size

while (1):

    imgResponse = urllib.request.urlopen(url)
    imgNp = np.array(bytearray(imgResponse.read()),dtype=np.uint8)
    img = cv2.imdecode(imgNp, -1)

    #img = cv2.rotate(img,cv2.ROTATE_90_CLOCKWISE)
    #gris = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

    cv2.imshow(winName,img)

    tecla = cv2.waitKey(5) & 0xFF
    if tecla ==27:
        break

cv2.destroyAllWindows()
