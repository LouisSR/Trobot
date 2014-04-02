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
#define STATE_FACE_HOME		4
#define STATE_GO_HOME		5
#define STATE_DROP_CUBE		6

/* Macros */
#define RADIANS(a)			( (a)/180.0*M_PI )
#define DEGREES(a)			( (a)/M_PI*180 )

/* Constant */
const unsigned int wheel_radius = 35;
const unsigned int wheels_distance = 160; //distance between wheels
const unsigned int robot_max_speed = 380; //370 mm/s
const int field_length = 3000;
const int field_width = 2000;
const float delta_t = 0.2; //odometry time
const unsigned int loop_time = 100;
const unsigned int odometry_timer_interval = 2;


/* Global Variables */
unsigned int robot_state = STATE_WAIT_START;
int robot_speed_left = 10, robot_speed_right = -10; //motor speed
float position_x=0;
float position_y=0;
float position_theta=0;
unsigned int zone=0;
unsigned int color_ground=GREY;
unsigned int myHome=0;
unsigned int timer_odometry; //timer Variables