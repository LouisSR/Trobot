void OdometryUpdate(int motor_right, int motor_left, unsigned int delta_t)
{
	unsigned int new_ground_color;

	position_theta = wheel_radius * (motor_left - motor_right) / (2 * wheels_distance);
	position_x = wheel_radius * (motor_left + motor_right) * cos(position_theta) /2 ;
	position_y = wheel_radius * (motor_left + motor_right) * sin(position_theta) /2 ;

	new_ground_color = readGroundColor();
	if(new_ground_color != color_ground)
	{
		if(new_ground_color == BLACK)
		{
			zone = BLACK;
		}
		else if (new_ground_color == WHITE)
		{
			zone = WHITE;
		}
		else // new color is grey
		{
			if(zone==WHITE)
			{
				zone = HOME;
			}
			else
			{
				zone = OPPONENT_HOME;
			}
		}
		color_ground = new_ground_color;
	}
}