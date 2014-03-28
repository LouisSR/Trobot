void OdometryUpdate(int motor_right, int motor_left, unsigned int delta_t)
{
	unsigned long mytic = millis();
	unsigned long mytoc;
	unsigned int new_ground_color;

	position_theta += wheel_radius * (motor_left - motor_right) * delta_t / (2 * wheels_distance);
	position_theta = Normalize(position_theta);
	position_x += wheel_radius * (motor_left + motor_right) * delta_t * cos(position_theta) /2.0 ;
	position_y += wheel_radius * (motor_left + motor_right) * delta_t * sin(position_theta) /2.0 ;

	position_x = constrain(position_x, 0, field_length);
	position_y = constrain(position_y, -field_width/2, field_width/2);

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
	Serial.print("Odometry Time: ");
	Serial.println(mytoc-mytic);
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

int ToMetric(int speed)
{
	int metric_speed;
	metric_speed =  speed; 
	return metric_speed;
}