/*
UART:
 Pins 0-1
Servos:
 Pins 5-6
DC motor:
 Pins 9-12
 
Linear camera(I2C):
 Pins 2,3
IR distance sensors:
 Pins A4,4,7,A0,A1,A2,A3 (6pins+1 Analog pin)
 */

#include <Servo.h> 
#include <prismino.h>
#include <LinearCamera.h>
#include <math.h>
#include "IR_sensor.h"
#include "robot.h" 

/* Variable and constant declaration*/
Servo servo1;
Servo servo2;
LinearCamera LinCam = LinearCamera(5); // new instance of the camera, it works over i2c and the default address is "5"

void setup()
{
  //Pins initialization: input/output and low/high
  pinMode(LED, OUTPUT);
  
  servo1.attach(S1); // pin 6
  servo2.attach(S2); // pin 5

  Serial.begin(115200);   // open the USB serial port at 115200 bps:
  Serial1.begin(115200);  // open the serial port (pin0-1) at 115200 bps:
}

void loop()
{
  //Variable declaration
  unsigned int length=2;
  unsigned int data[]={67,56};
  unsigned int distance;
  int angle;
  
  //Check UART
//  Send2Raspberry(data, length);
//  if (ReceiveFromRaspberry(&distance, &angle))
  
  //Send color to track

  //Read IR sensors

  //Wait for the start signal

  //Follow the bright LED (linear camera)
  //LinearCam();

  //Close the gripper

  // Open the gripper

  // Set motors

  //Odometry from motor commands integration, ground color

  delay(2000);
}


void sendPlotData(String seriesName, int data)
{
  Serial.print("{");
  Serial.print(seriesName);
  Serial.print(",T,");
  Serial.print(data);
  Serial.println("}");
}

