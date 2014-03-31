/*
UART:
 Rx: Pin 0 ; TX: Pin 1
Servos:
  Servo1 : pin 6
  Servo2 : pin 5
DC motor:
 Pins 9-12
 
Linear camera(I2C):
 Pins 2,3
IR distance sensors:
 Pins A4,4,7,A0,A1,A2,A3 (6pins+1 Analog pin)
 */

#include <prismino.h>
#include <Servo.h> 
#include <LinearCamera.h>
#include <math.h>
#include "IR_sensor.h"
#include "robot.h" 

/* Object declaration*/
Servo gripper; 
LinearCamera LinCam = LinearCamera(5); // new instance of the camera, it works over i2c and the default address is "5"

/* Test variables*/
int gripper1 = 0;
int motor_right=10, motor_left=10;
unsigned int timer_odometry;
//unsigned char = timer_odometry, timer_UART, timer_obstacles; 

void setup()
{
  //Pins initialization: input/output and low/high
  pinMode(IR_SENSOR_OUTPUT, INPUT);
  pinMode(VDD_IRLED, OUTPUT);
  digitalWrite(VDD_IRLED, HIGH);
  pinMode(ENABLE_MUX, OUTPUT);
  digitalWrite(ENABLE_MUX, HIGH);
  pinMode(LED, OUTPUT); //LED: pin13
  digitalWrite(A5,LOW);
  
  gripper.attach(SERVO1); // pin 6 --- share timer with setTimer
  //servo2.attach(S2); // pin 5

  //timer_odometry = setTimer(OdometryUpdate, 2 ); //share timer with Servo
  //unsetTimer(timer_odometry);
  //timer_UART = setTimer(); //check UART
  //timer_obstacles = setTimer();

  Serial.begin(115200);   // open the USB serial port at 115200 bps:
  Serial1.begin(115200);  // open the serial port (pin0-1) at 115200 bps:

  delay(3000);
}

void loop()
{
  unsigned long mytic = millis();
  unsigned long mytoc;
  //Variable declaration
  unsigned int length=2;
  unsigned int data[NB_IR_DISTANCE_SENSOR];
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
  //Send2Raspberry(data, length);


  //Read IR sensors
  //Serial.print("GroundColor: ");
  //Serial.println(readGroundColor());
  readDistanceIR(data);

  //Wait for the start signal
  //Serial.print("StartLED: ");
  //Serial.println(readStartLED());
  //if ( WaitForStart() == 0 )
  //{
  //  Move(20,0);
  //}

  //Follow the bright LED (linear camera)
  //Serial.print("LinCam: ");
  //Serial.println(LinearCam());
  //LinearCam();
  //FollowLight();
  
  //Open or close the gripper
  /*if(gripper1 == 1)
  {
    OpenGripper();
    gripper.write(125);
    gripper1 = 0;
  } 
  else
  {
    CloseGripper();
     gripper.write(40);
    gripper1 = 1;
  }*/
    //delay(4000);
    //Move(100,0);
    //delay(1000);
    //Move(0,0);

  //OdometryUpdate();

    // Serial.print("Odometry: ");
    // Serial.print(position_x);
    // Serial.print("  ");
    // Serial.print(position_y);
    // Serial.print("  ");
    // Serial.print(position_theta);
    // Serial.print("  ");
    // Serial.println(zone);
  //Odometry from motor commands integration, ground color
  //OdometryUpdate(motor_left, motor_right, 500);


/*
switch(robot_state)
{
  case STATE_WAIT_START: if( WaitForStart() )
    robot_state = STATE_SEARCH_CUBE;
    break;
  case STATE_SEARCH_CUBE: if( SearchForCube() )
    robot_state = STATE_GO2CUBE;
    break;
  case STATE_GO2CUBE: if( Go2Cube() )
    robot_state = STATE_TAKE_CUBE;
    break;
  case STATE_TAKE_CUBE: if( TakeCube() )
    robot_state = STATE_FACE_HOME;
    break;
  case STATE_FACE_HOME: if( FaceHome() )
    robot_state = STATE_GO_HOME;
    break;
  case STATE_GO_HOME: if( GoHome() )
    robot_state = STATE_DROP_CUBE;
    break;
  case STATE_DROP_CUBE: if( DropCube() )
    robot_state = STATE_SEARCH_CUBE;
    break;
  default: break;
}
*/
  mytoc = millis();
  // Serial.print("Loop time: ");
  // Serial.println(mytoc-mytic);
  delay( loop_time-(mytoc-mytic) );
}

boolean WaitForStart(void)
{
  boolean led_off = false;
  
  //Send2Raspberry(unsigned int* data, unsigned int data_length);
  
  led_off = readStartLED();
  
  return led_off;
}

boolean SearchForCube(void)
{
  boolean cube_detected = false;
  //Send2Raspberry(unsigned int* data, unsigned int data_length);
  //ReceiveFromRaspberry(unsigned int* distance, int* angle, unsigned int* color);
  
  return cube_detected;
}

boolean Go2Cube(void)
{
  boolean cube_here = false;
  
  return cube_here;
}

boolean TakeCube(void)
{
  boolean cube_collected = false;
  
  cube_collected = CloseGripper();
  
  return cube_collected;
}

boolean FaceHome(void)
{
  boolean face_home = false;
  float diff = RADIANS(180)-position_theta;
  if (abs(diff) > 15 )
  {
    Move(0,diff*10);
  }
  else
  {
    face_home = true;
  }

  return face_home;
}

boolean GoHome(void)
{
  boolean got_home = false;
  //DriveTo(0,0);
  if(color_ground != GREY)
  {
    FollowLight();
  }
  else
  {
    got_home = true;
  }
  
  return got_home;
}

boolean DropCube(void)
{
  boolean cube_dropped = false;
  
  OpenGripper();
  //step back then rotate
  if( abs(position_theta) > RADIANS(5) ) 
  {
    Move(0,position_theta); //rotate
  }
  else
  {
    // Reset odometry
    cube_dropped = true;
  }
  
  return cube_dropped;
}

// void sendPlotData(String seriesName, int data)
// {
//   Serial.print("{");
//   Serial.print(seriesName);
//   Serial.print(",T,");
//   Serial.print(data);
//   Serial.println("}");
// }

void myPrint(float data)
{
  Serial.print(data);
  Serial.print(" \t");
}