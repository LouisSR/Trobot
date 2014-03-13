import time
import cv2
import numpy as np
import os
from cameraCV2 import findblob 
#from Uart import Write2Arduino, ReadFromArduino

print("Start\n")
color = 'blue'

#Take image with Raspberry Pi camera
#os.system("raspistill --width 500 --height 500 --timeout 10000 --timelapse 2000 --vflip --output ./images/camera.jpg")


for i in range(1):
	time_start=time.time()
	#Read from Arduino
	color = Color2Track(color)
	#Load image
	#image = cv2.imread("./images/camera.jpg")
	image = cv2.imread("./images/photo 3.jpg")
	height, width, depth = image.shape
	time_loadImage=time.time()
	#Find blob
	centroid_x, centroid_y = findblob(image, color)
	time_findblob=time.time()
	distance = Pix2Dist(centroid_y, height)

	#Transmit to Arduino
	data = [centroid_x, distance, color]
	Send2Arduino(data)

	print 'Load image: %0.3f s' % (time_loadImage-time_start)
	print 'Find blobs image: %0.3f s' % (time_findblob-time_loadImage)
	time_end = time.time()
	loop_time = time_end-time_start
	time.sleep(2-loop_time)


def Color2Track(previous_color):
	color = ReadFromArduino()
	if color == None:
		color = previous_color
	return color
# Unused functions
	#height, width, depth = image.shape
	#print height, width, depth
	#image = cv2.resize(image, (500,500))