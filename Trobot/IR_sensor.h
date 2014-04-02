
#define VDD_IRLED 4         // Digital output
#define IR_SENSOR_OUTPUT A4 //Analog input
#define ENABLE_MUX 7        //Digital output
#define MUX_S0 A0   // Digital output
#define MUX_S1 A1   // Digital output
#define MUX_S2 A2   // Digital output
#define MUX_S3 A3   // Digital output

#define GROUND_COLOR_SENSOR 12 //Mux Channel of ground color sensor
#define START_LED 10 // Mux channel of start led
#define NB_IR_DISTANCE_SENSOR 3 //Number of IR sensor for distance measuring
#define CUBE_DETECTION_LOW 11
#define CUBE_DETECTION_HIGH 13

#define BLACK_GROUND 300 //threshold
#define WHITE_GROUND 850 //threshold
#define START_LED_ON 900 //threshold
#define START_LED_OFF 100 //threshold
#define NO_CUBE 200 //threshold
#define CUBE_DETECTED 800 //threshold

const unsigned int IR_sensor[NB_IR_DISTANCE_SENSOR]={15,13,14};
const int tab_size = 19;
const int tab[19][2] =
 //Distance in mm, ADC value
{
  {300, 14},
  {250, 16},
  {200, 21},
  {170, 26},
  {150, 31},
  {140, 35},
  {130, 40},
  {120, 44},
  {110, 50},
  {100, 58},
  {90, 65},
  {80, 80},
  {70, 93},
  {60, 120},
  {50, 170},
  {40, 214},
  {30, 330},
  {20, 600},
  {10, 634}
};