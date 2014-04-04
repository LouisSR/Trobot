void OpenGripper(void)
{
	//unsetTimer(timer_odometry);
  //gripper.attach(SERVO1); // pin 6 --- share timer with setTimer
  //delay(50);
  gripper.write(GRIPPER_OPEN);
  Serial.println(GRIPPER_OPEN);
  //delay(50); // add a small delay so the servo motors have time to move
  //gripper.detach(); // pin 6 --- share timer with setTimer
  //timer_odometry = setTimer(OdometryUpdate, odometry_timer_interval ); //share timer with Servo
}

void CloseGripper(void)
{
  //unsetTimer(timer_odometry);
  //gripper.attach(SERVO1); // pin 6 --- share timer with setTimer
  //delay(50); 
  gripper.write(GRIPPER_CLOSED);
  Serial.println(GRIPPER_CLOSED);
  //delay(50); // add a small delay so the servo motors have time to move
  //gripper.detach();
  //timer_odometry = setTimer(OdometryUpdate, odometry_timer_interval ); //share timer with Servo
}

boolean DriveTo(unsigned int destination_x, unsigned int destination_y)
/* Absolute coordinates*/
{
	boolean arrived = false;
	unsigned int distance;
	int delta_x, delta_y;
	float alpha, diff;
	
	delta_x = (destination_x - position_x);
	delta_y = (destination_y - position_y);
	distance = sqrt( delta_x*delta_x + delta_y*delta_y ); // sqrt useless
	alpha = acos( delta_y / delta_x );
	
	diff = Normalize(alpha - position_theta);
	if  ( diff > RADIANS(10) ) // rotate
	{
		Move(0, diff); //rotate ; diff used for speed control
	}
	else //move
	{
		if(distance > 5)
		{
			Move(distance, diff); //distance and diff used for speed control
myPrint(distance);
myPrint(diff);
		}
		else
		{
			arrived = true;
		}	
	}
	return arrived;
}

void Move(unsigned int distance, int diff)
{	
	//int motor_left, motor_right;

	robot_speed_left = distance - diff;
	robot_speed_right = distance + diff;
	// Serial.print(motor_left);
	// Serial.print("    ");
	// Serial.println(motor_right);
	setSpeed(robot_speed_left, robot_speed_right); // values between -100 and 100
}

void SetMotors(int motor_left, int motor_right)
{
	int left_speed, right_speed; // value between -100 and 100

	left_speed = motor_left;
	right_speed = motor_right;
	setSpeed(left_speed, right_speed);
	delay(100); // wait at least 100ms or the setting won't have any effect before the next setting
}

void FollowLight(void)
{
	int CamPeak,PeakValue;

	CamPeak = LinearCam();
        PeakValue=LinCam.getMax();
myPrint(PeakValue);
	if(CamPeak != -100 && PeakValue>LightIntensity)
	{
		//Move(25,CamPeak/4);
		//Serial.println(CamPeak);

		if(abs(CamPeak) < 20)
		{
			Move(50,-CamPeak/2);
			//Serial.println("Tout droit");

		}
		else
		{
			Move(0, copysign(8,-CamPeak) );
			//Serial.println("Peak trop loin");

		}
	}
	else
	{
		Move(0, 4);
		//(Serial.println("No Peak");
	}
}
