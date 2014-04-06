#define BLACK 0
#define WHITE 1
#define GREY 2
#define HOME_WHITE 2
#define HOME_BLACK 3
#define GRIPPER_OPEN 40
#define GRIPPER_CLOSED 125

/* Robot state */
#define STATE_WAIT_START	0
#define STATE_SEARCH_CUBE	1
#define STATE_ROTATE2CUBE   2
#define STATE_GO2CUBE		3
#define STATE_TAKE_CUBE		4
#define STATE_FACE_HOME		5
#define STATE_GO_HOME		6
#define STATE_DROP_CUBE		7
#define STATE_ROTATE		8

#define LEFT 1
#define RIGHT 2


/* Macros */
#define RADIANS(a)			( (a)/180.0*M_PI )
#define DEGREES(a)			( (a)/M_PI*180 )

/* Constant */
const unsigned int wheel_radius = 35;
const unsigned int wheels_distance = 160; //distance between wheels
const unsigned int robot_max_speed = 380; //380 mm/s
const int field_length = 3000;
const int field_width = 2000;
const int distance_limite = 40;
const int valeur_limite_compteur = 10;
const float delta_t = 0.2; //odometry time in second
const unsigned int loop_time = 200; //in millisecond
const unsigned int odometry_timer_interval = 2;
const int LightIntensity=60;
const int array_speed_size = 5;
const int array_speed[5][3]={
  // %, left, right
  {20,  90,  70},
  {40,  158, 140},
  {60,  243, 215},
  {80,  323, 288},
  {100, 368, 328},
};



/* Global Variables */
unsigned int robot_state = STATE_WAIT_START;
//unsigned int robot_state = STATE_TAKE_CUBE;
int robot_speed_left = 0, robot_speed_right = 0; //motor speed
float position_x=100;
float position_y=0;
float position_theta=0;
unsigned int zone=0;
unsigned int color_ground=GREY;
unsigned int color=0;
unsigned int myHome=0;
unsigned int timer_odometry; //timer Variables
