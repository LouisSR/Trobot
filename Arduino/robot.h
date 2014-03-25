#define BLACK 0
#define WHITE 1
#define GREY 2
#define HOME_WHITE 2
#define HOME_BLACK 3
#define GRIPPER_OPEN 125
#define GRIPPER_CLOSED 40

const unsigned int wheel_radius = 35;
const unsigned int wheels_distance = 100; //distance between wheel_radius
const unsigned int field_length = 3000;
const unsigned int field_width = 2000;

unsigned int position_x=0, position_y=0;
float position_theta=0;
unsigned int zone=0;
unsigned int color_ground=GREY;
unsigned int myHome=0;
