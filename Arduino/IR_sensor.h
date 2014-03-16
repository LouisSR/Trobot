
#define VDD_IRLED 4         // Digital output
#define IR_SENSOR_OUTPUT A4 //Analog input
#define ENABLE_MUX 7        //Digital output
#define S0 A0   // Digital output
#define S1 A1   // Digital output
#define S2 A2   // Digital output
#define S3 A3   // Digital output

#define GROUND_COLOR_SENSOR 15 //Mux Channel of ground color sensor
#define START_LED 14 // Mux channel of start led
#define NB_IR_DISTANCE_SENSOR 5 //Number of IR sensor for distance measuring
#define BLACK_GROUND 100 //threshold
#define WHITE_GROUND 500 //threshold
#define START_LED_ON 500 //threshold
#define START_LED_OFF 100 //threshold


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