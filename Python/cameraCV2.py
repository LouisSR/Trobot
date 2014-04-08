import cv2
import numpy as np
import time
from math import sin, cos, radians


def binarize(image, color):
	#Change BGR to HSV
	image_hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
	if color =='blue':
		high_color = np.array((130 , 255, 255))
		low_color = np.array((95, 150, 50))
	elif color == 'red':
		high_color = np.array((180, 255, 255))
		low_color = np.array((170, 50, 50))
		high_color2 = np.array((15, 255, 255))
		low_color2 = np.array((0, 50, 50))
	else:
		print '\nError color\n'
	
	#Binarize the color
	image_blackandwhite  = cv2.inRange(image_hsv, low_color, high_color)
	if color == 'red':
		image_blackandwhite2  = cv2.inRange(image_hsv, low_color2, high_color2)
		image_blackandwhite = image_blackandwhite + image_blackandwhite2
	
	cv2.imwrite("./images/blackandwhite.jpg", image_blackandwhite)
	
	return(image_blackandwhite)

def findblob(image, color):
	time_start1 = time.time()
	
	image_blackandwhite = binarize(image, color)
	time_binarize=time.time()
	
	#Find largest (area) contour
	mycontours, hierarchy = cv2.findContours(image_blackandwhite, cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)
                
	max_area = 0
	if mycontours:
        	biggest_contour = mycontours[0]
        else:
                return (-1,-1)
        
	for contour in mycontours:
		area = cv2.contourArea(contour)
		if area>max_area:
			max_area = area
			biggest_contour = contour
	time_contour = time.time()
	#print "Max area: ", max_area
	if max_area < 10:
                print "No cube detected"
                return (-1,-1) #No cube detected        
	centroid = findCentroid(biggest_contour)
	time_moment = time.time()
	cv2.drawContours(image,[biggest_contour],0, (0,255,0), 5)
	cv2.circle(image,centroid, 10, ((0,255,0)), 5)
	cv2.imwrite("./images/blobs.jpg", image)
	
	#print 'Binarize: %0.3f s' % (time_binarize-time_start1)
	#print 'Findcontour: %0.3f s' % (time_contour-time_binarize)
	#print 'Findcentroid: %0.3f s' % (time_moment-time_contour)

	return centroid

def findCentroid(image):
	M = cv2.moments(image)
	centroid_x = int(M['m10']/M['m00'])
	centroid_y = int(M['m01']/M['m00'])
	return(centroid_x, centroid_y)
	
def Pix2Dist(Ypix, vertical_size):
        Ypix = vertical_size - Ypix
        #print "Y: ", Ypix, vertical_size
        distance = Ypix
	#Y = (Ypix-vertical_size/2)/float(vertical_size) # 500 is the image vertical size, 250 is half of this size
	#alpha = radians(30) #Angle of the camera to the horizontal
	#Hauteur = 170 # Height between the camera and the cube
	#Ltot = sin(alpha)*Hauteur
	#distance = -Ltot / ( ( sin(alpha)/Y )+cos(alpha) )
	return int(distance)


# Unused functions

	#Blur image, remove noise
	#image = cv2.blur(image, (5,5)) #take long time
	#Remove noisy pixels 
	#element3 = np.zeros((5,5), np.uint8)
	#element5 = np.zeros((10,10), np.uint8)
	#eroded = cv2.erode(image_blackandwhite,element3,iterations=2)
	#cv2.imwrite("./images/eroded.jpg", eroded)
	#dilated = cv2.dilate(eroded,element5)
	#cv2.imwrite("./images/dilated.jpg", dilated)
	#time_erode=time.time()
