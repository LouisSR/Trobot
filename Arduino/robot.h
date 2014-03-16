#define wheel_radius 35
#define wheels_distance 100 //distance between wheel_radius
#define BLACK 0
#define WHITE 1
#define GREY 2
#define HOME 2
#define OPPONENT_HOME 3


unsigned int position_x=0, position_y=0;
float position_theta=0;
int zone=0; //2: starting zone, 1: white zone, -1: black zone, -2: opponent starting zone
unsigned int color_ground=GREY;
