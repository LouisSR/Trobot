/*
UART:
 Rx: Pin 0 ; TX: Pin 1
Servos:
 Pins 5,6
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
Servo gripper;
Servo servo2;
LinearCamera LinCam = LinearCamera(5); // new instance of the camera, it works over i2c and the default address is "5"

void setup()
{
  //Pins initialization: input/output and low/high
  pinMode(IR_SENSOR_OUTPUT, INPUT);
  pinMode(VDD_IRLED, OUTPUT);
  digitalWrite(VDD_IRLED, LOW);
  pinMode(ENABLE_MUX, OUTPUT);
  digitalWrite(ENABLE_MUX, LOW);
  pinMode(LED, OUTPUT); //LED: pin13
  
  gripper.attach(S1); // pin 6
  servo2.attach(S2); // pin 5

  Serial.begin(115200);   // open the USB serial port at 115200 bps:
  Serial1.begin(115200);  // open the serial port (pin0-1) at 115200 bps:
}

void loop()
{
  //Variable declaration
  unsigned int length=2;
  unsigned int data[]={55,56};
  unsigned int distance, color=55;
  int angle;
  
  //Check UART
  // if (ReceiveFromRaspberry(&distance, &angle, &color))
  // {
  // Serial.print("Receive: ");
  // Serial.print(distance);
  // Serial.print("  ");
  // Serial.print(angle);
  // Serial.print("  ");
  // Serial.println(color);
  // }
  // else
  // {
  //   Serial.println("Nothing");
  // }
  
  //Send color to track
  Send2Raspberry(data, length);


  //Read IR sensors
  //Serial.println(readGroundColor());

  //Wait for the start signal
  //start_led = readStartLED();

  //Follow the bright LED (linear camera)
  //LinearCam();

  //Open or close the gripper
  //OpenGripper();
  //CloseGripper();

  //Set motors
  //SetMotors(motor_left, motor_right);

  //Odometry from motor commands integration, ground color
  //OdometryUpdate(motor_left, motor_right, delta_t);

  delay(1500);
}


void sendPlotData(String seriesName, int data)
{
  Serial.print("{");
  Serial.print(seriesName);
  Serial.print(",T,");
  Serial.print(data);
  Serial.println("}");
}

