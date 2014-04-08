from SimpleCV import Color, Image
#import os

print("Start")

#Take image with Raspberry Pi camera
#os.system("raspistill --width 500 --height 500 --timeout 1000 --vflip --output image4.png")

#Load image
im1 = Image("color.jpg")

#Scale image
#im = im1.scale(0.5) #ne marche pas encore (perturbe colorDistance)

#Binarize the blue
im_blue = im.colorDistance(color=Color.BLUE).binarize()
im_blue.save("bluedistance.jpg")

blobs = im_blue.findBlobs()
blobs.draw(color=Color.BLUE, width=20)
x, y = blobs[-1].centroid()
print "Biggest blobs at ", x, y

im_blue.save("blobs.jpg")




