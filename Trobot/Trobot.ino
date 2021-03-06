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
int motor_right=0, motor_left=0;
//unsigned char = timer_odometry, timer_UART, timer_obstacles;

void setup()
{
    //Pins initialization: input/output and low/high
    pinMode(VDD_IRLED, OUTPUT);
    digitalWrite(VDD_IRLED, HIGH);
    pinMode(ENABLE_MUX, OUTPUT);
    digitalWrite(ENABLE_MUX, HIGH);
    pinMode(LED, OUTPUT); //LED: pin13
    
    pinMode(MUX_S0, OUTPUT);
    pinMode(MUX_S1, OUTPUT);
    pinMode(MUX_S2, OUTPUT);
    pinMode(MUX_S3, OUTPUT);
    pinMode(IR_SENSOR_OUTPUT, INPUT);
    
    //timer_odometry = setTimer(OdometryUpdate, odometry_timer_interval ); //share timer with Servo
    //timer_UART = setTimer(); //check UART
    //timer_obstacles = setTimer();
    
    Serial.begin(115200);   // open the USB serial port at 115200 bps:
    Serial1.begin(115200);  // open the serial port (pin0-1) at 115200 bps:
    
    gripper.attach(SERVO1);
    OpenGripper();
    delay(1000);
}

void loop()
{
    //Variable declaration
    unsigned long mytic = millis();
    unsigned long mytoc;
    unsigned int length=3;
    unsigned int data[3]={11 ,12 ,13};
    unsigned int distance;
    int angle;
    
    
    //Check UART
    /*
     if (ReceiveFromRaspberry(&distance, &angle, &color))
     {
     
     Serial.print("Receive: ");
     Serial.print(distance);
     Serial.print("  ");
     Serial.print(angle);
     Serial.print("  ");
     Serial.println(color);
     
     }
     else
     {
     Serial.println("Nothing");
     }
     */
    
    
    //Send color to track
    //Send2Raspberry(&color , 1);
    
    
    //Serial.print("IR: ");
    //readDistanceIR(data);
    //Serial.println();
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
    
    
    OdometryUpdate();
    
    
    //Serial.println("loop");
    //Serial.println( CubeDetect() );
    //CubeDetect();
    //TakeCube();
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
    
    // move calibration
    
    //Move(0,0);
    //delay(3000);
    //FaceHome();
    
    //Move(0,10);
    
    //Rotate2Cube();
    //FaceHome();
    //SearchForCube();
    //Go2Cube();
//   FaceLight();
    
  //  GoHome();
//    
//    myPrint(position_x);
//    myPrint(position_y);
//    myPrint(DEGREES(position_theta));
//    Serial.println();
//    if (position_x<1500) {
//        Move(80,0);
//        
//    }
//    else
//    {
//        Move(0,0);
//    }
    
   
    switch(robot_state)
    {
        case STATE_WAIT_START: if( WaitForStart() )
            robot_state = STATE_SEARCH_CUBE;
            break;
        case STATE_SEARCH_CUBE: if( SearchForCube() )
            robot_state = STATE_ROTATE2CUBE;
            break;
        case STATE_ROTATE2CUBE: if( Rotate2Cube() )
            robot_state = STATE_GO2CUBE;
            break;
        case STATE_GO2CUBE: if( Go2Cube() )
            robot_state = STATE_TAKE_CUBE;
            break;
        case STATE_TAKE_CUBE: if( TakeCube() )
            robot_state = STATE_FACE_HOME;
            break;
        case STATE_FACE_HOME:
            demiTourGauche();
            robot_state = STATE_GO_HOME;
            break;
        case STATE_GO_HOME: if( GoHome() )
            robot_state = STATE_DROP_CUBE;
            break;
        case STATE_DROP_CUBE: if( DropCube() )
            robot_state = STATE_ROTATE;
            break;
        case STATE_ROTATE:
            demiTourGauche();
            robot_state = STATE_SEARCH_CUBE;
            break;
        default: break;
    }
   
    
    //demiTourGauche();
    //Move(0,0);
    //delay(3000);
    
    
    //Serial.print("State ");
    //Serial.println(robot_state);
    mytoc = millis();
    // Serial.print("Loop time: ");
    //Serial.println(mytoc-mytic);
    unsigned int wait_time = loop_time - (mytoc-mytic);
    if(wait_time < loop_time)
    {
        delay( wait_time );
    }
    
}

boolean WaitForStart(void)
{
    boolean led_off = false;
    
    //Send2Raspberry(unsigned int* data, unsigned int data_length);
    
    led_off = readStartLED();
    Serial.println(led_off);
    return led_off;
}

boolean SearchForCube(void)
{
    boolean cube_targeted = false;
    unsigned int distance = 30000;
    int angle;
    static boolean sens_rotation=true;
    //cube_targeted=CubeDetect;
    //Send2Raspberry(unsigned int* data, unsigned int data_length);
    ReceiveFromRaspberry( &distance, &angle, &color);
    
    if(distance!=30000)
    {
        cube_targeted=true;
        Serial.println("cube targeted");
    }
//    else
//    {
//        Serial.println("cube not targeted");
//        Move(0,0);
//        /*
//        Serial.println("cube_targeted");
//        // Recherche aleatoires
//        if (sens_rotation==true)
//        {
//            Move(0,10);
//        }
//        else
//        {
//            Move(0,-10);
//        }
//        if (abs(position_theta)>RADIANS(50))
//        {
//            sens_rotation= !sens_rotation;
//        }
//         */
//    }
    Serial.println(DEGREES(position_theta));
    
    return cube_targeted;
}

boolean Rotate2Cube(void)
{
    boolean cube_there = false;
    unsigned int distance=30000;
    int angle;
    int mapped_angle;
    
    ReceiveFromRaspberry( &distance, &angle, &color);
    Serial.println();
    myPrint(distance);
    myPrint(angle);
    
    if(distance!=30000)
    {
        mapped_angle=map(angle, -250 , 250 , -100,100);
        
        myPrint(angle);
        myPrint(mapped_angle);
        
        if (abs(mapped_angle)>10)
        {
            Move(0,copysign(10,mapped_angle));
            Serial.print(" Rotate");
        }
        else
        {
            Serial.print(" Cube en face");
            cube_there=true;
            Move(0,0);
        }
    }
 //   else
 //   {
 //       Move(0,0);
 //       //robot_state = STATE_SEARCH_CUBE; //No cube detected
 //   }
    
    return cube_there;
}

boolean Go2Cube(void)
{
    boolean cube_here = false;
    unsigned int distance=30000;
    int angle;
    int mapped_distance, mapped_angle;
    static int compteur_securite = 0;
    Serial.println();
    ReceiveFromRaspberry( &distance, &angle, &color);
    myPrint(distance);
    myPrint(angle);

    if(distance!=30000)
    {
        mapped_distance=map(distance, 0 , 400 ,0,100);
        mapped_angle=map(angle, -250 , 250 , -100,100);
        
        myPrint(distance);
        myPrint(mapped_distance);
        myPrint(angle);
        myPrint(mapped_angle);
        
        if (mapped_distance>distance_limite)
        {
            Move(20,mapped_angle/8);
            Serial.print(" Avance ");
        }
        else
        {
            //viser pour que le cube soit en face
//            if (abs(mapped_angle)>20)
//            {
//                Move(0,copysign(20,mapped_angle));
//                Serial.print(" Tourne ");
//            }
//            else
//            {
                Serial.print(" Cube dans les pinces ");
                Move(20,0);
                cube_here = true;
            //}
        }
    }
//    else
//    {
//        compteur_securite++;
//        //Ajouter compteur puis rentrer à la maison
//        if (compteur_securite>valeur_limite_compteur)
//        {
//            //robot_state = STATE_SEARCH_CUBE; //Cube lost
//            Move(0,0);
//            compteur_securite=0;
//            Serial.print(" Cube perdu ");
//        }
//    }
    
    return cube_here;
}

boolean TakeCube(void)
{
    boolean cube_collected = false;
    static int compteur_securite=0;
    
    
    if ( CubeDetect() )
    {
        CloseGripper();
        cube_collected = true;
        compteur_securite=0;
    }
    else
    {
        Move(30,0);
        compteur_securite++;
    }
    
    if (compteur_securite>valeur_limite_compteur)
    {
        robot_state = STATE_SEARCH_CUBE; //Cube lost
        Move(0,0);
        compteur_securite=0;
    }
    
    return cube_collected;
}

boolean FaceHome(void)
{
    boolean face_home = false;
    float diff = Normalize(RADIANS(180)-position_theta);
    
    //myPrint(diff);
    Serial.println("face home");
    
    if (abs(diff) > RADIANS(5) )
    {
        Move(0,copysign(20,diff));
    }
    else
    {
        face_home = true;
        Move(0,0);
        
        Serial.println("home found");
        
        //Serial.println("true");
        
    }
    
    return face_home;
}

boolean GoHome(void)
{
    boolean got_home = false;
    //DriveTo(0,0);
    Serial.println("go home");
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
    boolean cube_dropped = true;
    
    Move(60,0);//enter the Grey Zone
    delay(500);
    
    OpenGripper();
    
    //step back
    Move(-60,0);
    delay(1000);
    
    return cube_dropped;
}

void demiTourDroite(void)
{
    Move(0,-40);
    delay(1800);
    position_theta = Normalize(position_theta + RADIANS(180));
}
void demiTourGauche(void)
{
    Move(0,40);
    delay(1850);
    position_theta = Normalize(position_theta + RADIANS(180));
}

void myPrint(float data)
{
    Serial.print(data);
    Serial.print(" \t");
}

/*
 void sendPlotData(String seriesName, int data)
 {
 Serial.print("{");
 Serial.print(seriesName);
 Serial.print(",T,");
 Serial.print(data);
 Serial.println("}");
 }
 
 boolean FaceLight(void)
 {
 boolean light_faced = false;
 
 light_faced = AlignLight();
 
 }
 
 boolean Rotate(void)
 {
 boolean rotated = false;
 
 if( abs(position_theta) > RADIANS(5) )
 {
 Move(0,copysign(20,-position_theta)); //rotate
 //Serial.println(position_theta);
 
 }
 else
 {
 // Reset odometry
 rotated = true;
 Move(0,0);
 }
 
 return rotated;
 }
 
 */
