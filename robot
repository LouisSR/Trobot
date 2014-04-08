#!/bin/sh

cd /home/pi/Desktop/robot/Python

#Take image with Raspberry Pi camera in background
sudo raspistill --width 600 --height 400 --timeout 120000 --timelapse 600 --output /home/pi/Desktop/robot/images/camera.jpg &

sudo python Main.py