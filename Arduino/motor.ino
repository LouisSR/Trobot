void OpenGripper(void)
{
	gripper.write(GRIPPER_OPEN);
    delay(50); // add a small delay so the servo motors have time to move
}

boolean CloseGripper(void)
{
	gripper.write(GRIPPER_CLOSED);
    delay(50); // add a small delay so the servo motors have time to move
    // test if something is gripped and return true if yes.
    return(true);
}

void SetMotors(int motor_left, int motor_right)
{
	int left_speed, right_speed; // value between -100 and 100

	left_speed = motor_left;
	right_speed = motor_right;
	setSpeed(left_speed, right_speed);
	delay(50); // wait at least 100ms or the setting won't have any effect before the next setting
}