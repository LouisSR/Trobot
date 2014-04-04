void OdometryUpdate()
{
	unsigned long mytic = millis();
	unsigned long mytoc;
	unsigned int new_ground_color;
        float speed_left,speed_right;

<<<<<<< HEAD
        ToMetric( robot_speed_left, robot_speed_right, &speed_left, &speed_right);

	position_theta += (speed_right - speed_left) * delta_t / (wheels_distance*2);
=======
	position_theta += wheel_radius * (speed_left - speed_right) * delta_t / (wheels_distance);
>>>>>>> FETCH_HEAD
	position_theta = Normalize(position_theta);
        //myPrint(DEGREES(position_theta));
	position_x += wheel_radius * (speed_left + speed_right) * delta_t * cos(position_theta) /2.0 ;
	position_y += wheel_radius * (speed_left + speed_right) * delta_t * sin(position_theta) /2.0 ;

	position_x = constrain(position_x, 0, field_length);
	position_y = constrain(position_y, -field_width/2, field_width/2);
	
	// myPrint(robot_speed_right);
	// myPrint(robot_speed_left);
	// myPrint(speed_right);
	// myPrint(speed_left);
	// myPrint(position_x);
	// myPrint(position_y);
         //myPrint(DEGREES(position_theta));
         Serial.println();
	new_ground_color = readGroundColor();

	if(new_ground_color != color_ground)
	{
		if(new_ground_color == BLACK)
		{
			zone = BLACK;
			if(myHome==0) //if myHome not yet intialized
			{
				myHome = HOME_BLACK;
			}
		}
		else if (new_ground_color == WHITE)
		{
			zone = WHITE;
			if(myHome==0) //if myHome not yet intialized
			{
				myHome = HOME_WHITE;
			}
		}
		else // new color is grey
		{
			if(zone==WHITE)
			{
				zone = HOME_WHITE;
			}
			else
			{
				zone = HOME_BLACK;
			}
		}
		color_ground = new_ground_color;
	}
	mytoc = millis();
	//Serial.print("                           Odometry Time: ");
	//Serial.println(mytoc-mytic);
//myPrint(zone);
//Serial.println();
}

float Normalize(float angle)
//Keep angle between -Pi and Pi
{
	while(angle<=-M_PI || angle>M_PI)
	{
		angle -= copysign(2*M_PI,angle); // add or remove 2 PI following the sign of angle
	}
	return(angle);
}

void ToMetric(int speed_left, int speed_right, float* metric_speed_left, float* metric_speed_right)
{
        *metric_speed_left = FindSpeed(speed_left,LEFT); 
        *metric_speed_left = FindSpeed(speed_right,RIGHT); 
}


int FindSpeed(int motor_speed, unsigned int side)
//speed: motor speed
//side: direction LEFT or RIGHT
{
<<<<<<< HEAD
  int metric_speed;
        if (motor_speed == 20)
        {
                metric_speed = array_speed[0][side];
        }
        else if(motor_speed==40)
        {
                metric_speed = array_speed[1][side];
        }
        else if(motor_speed==60)
        {
                metric_speed = array_speed[2][side];
        }
        else if(motor_speed==80)
        {
                metric_speed = array_speed[3][side];
        }
        else if(motor_speed==100)
        {
                metric_speed = array_speed[4][side];
        }
        else
        {
                metric_speed = motor_speed;
        }

        return metric_speed;
=======
	float metric_speed;
	metric_speed =  speed * robot_max_speed / 100.0; 
	return metric_speed;
>>>>>>> FETCH_HEAD
}
