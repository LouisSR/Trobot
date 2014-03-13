#!/bin/sh

#cd Desktop/robot

#Take image with Raspberry Pi camera in background
sudo raspistill --width 500 --height 500 --timeout 10000 --timelapse 2000 --vflip --nopreview --output ./images/camera.jpg &

python Main.py