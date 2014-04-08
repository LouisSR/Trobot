import time
import cv2
import numpy as np
import os
from cameraCV2 import findblob, Pix2Dist 
from Uart import Send2Arduino, ReadFromArduino

print("Start\n")
color = 'blue'
Periode = 0.5

#Take image with Raspberry Pi camera
#os.system("raspistill --width 500 --height 500 --timeout 10000 --timelapse 2000 --vflip --output ./images/camera.jpg")

def Color2Track(previous_color):
	color = ReadFromArduino()
	if color == None:
		color = previous_color
	if color == 55:
                print "Color received 55 ok" 
	return color

for i in range(300):
	time_start=time.time()
	#Read from Arduino
	#color = Color2Track(color)
	print "Color: ", color
	print "\n"
	#Load image
	image = cv2.imread("./images/camera.jpg")
	#image = cv2.imread("./images/photo 3.jpg")
	height, width, depth = image.shape
	time_loadImage=time.time()
	#Find blob
	centroid_x, centroid_y = findblob(image, color)
	time_findblob=time.time()
	if centroid_x != -1:
                distance = Pix2Dist(centroid_y, height)
        else:
                distance = 30000 #No cube detected
                centroid_x = 30000
	#Transmit to Arduino
	if color == 'blue':
                data = [distance, width/2-centroid_x, 90]
        else:
                data = [distance, width/2-centroid_x, 91]
	#data = [2000, 21, 23]
	Send2Arduino(data)

	#print 'Load image: %0.3f s' % (time_loadImage-time_start)
	#print 'Find blobs image: %0.3f s' % (time_findblob-time_loadImage)
	time_end = time.time()
	loop_time = time_end-time_start
	if loop_time < Periode:
        	time.sleep(Periode-loop_time)
        	print'Loop time: ', loop_time



# Unused functions
#height, width, depth = image.shape
#print height, width, depth
#image = cv2.resize(image, (500,500))
