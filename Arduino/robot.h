#define BLACK 0
#define WHITE 1
#define GREY 2
#define HOME_WHITE 2
#define HOME_BLACK 3
#define GRIPPER_OPEN 125
#define GRIPPER_CLOSED 40

/* Robot state */
#define STATE_WAIT_START	0
#define STATE_SEARCH_CUBE	1
#define STATE_GO2CUBE		2
#define STATE_TAKE_CUBE		3
#define STATE_GO_HOME		4
#define STATE_DROP_CUBE		5

/* Macros */
#define RADIANS(a)			(a)/180.0*M_PI
#define DEGREES(a)			(a)/M_PI*180

/* Constant */
const unsigned int wheel_radius = 35;
const unsigned int wheels_distance = 100; //distance between wheel_radius
const unsigned int field_length = 3000;
const unsigned int field_width = 2000;


/* Global Variables */
unsigned int robot_state = STATE_WAIT_START;
int robot_speed_left = 0, robot_speed_right = 0; //motor speed
unsigned int position_x=0, position_y=0;
float position_theta=0;
unsigned int zone=0;
unsigned int color_ground=GREY;
unsigned int myHome=0;
