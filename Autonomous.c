#pragma config(Motor,  port2,           frontRight,    tmotorVex393_MC29, openLoop, reversed, driveRight)
#pragma config(Motor,  port3,           frontLeft,     tmotorVex393_MC29, openLoop, driveLeft)
#pragma config(Motor,  port4,           backRight,     tmotorVex393_MC29, openLoop, reversed, driveRight)
#pragma config(Motor,  port5,           backLeft,      tmotorVex393_MC29, openLoop, driveLeft)

task main()
{

	string motors[] = {"frontRight", "frontLeft", "backRight", "backLeft"};

	// 5.125 makes us innacurate, how about 5.25? (Check this later down the road)
	float distanceRight, distanceLeft, rotationsRight, rotationsLeft, degreesRight, degreesLeft, ratio, diameter = 5.125, circumference = PI * diameter;
	int encoderCountsRight = 0, encoderCountsLeft = 0;

	void ForwardForDistance(int speed, float targetDistance) //The arguments are sorted alphabetically. Make speed negative to reverse and change the wait to abs to make sure it works
	{
		//float rotations = targetDistance / circumference; On torque mode (stock), there are 627 counts to a revolution, high speed there is 392, and turbo speed has 261
		//float degrees = rotations * 360;
		//float encoderCounts = degrees * 4;	// 24 / 18.375 is 1.30612244898

		//Auto-correction
		//while(nMotorEncoder[frontRight] < encoderCounts && nMotorEncoder[frontLeft] < encoderCounts)
		//{
		//	if (nMotorEncoder[frontRight] > nMotorEncoder[frontLeft])
		//	{
		//		motor[frontRight] = speed / 2;
		//		motor[backRight] = speed / 2;
		//	}
		//	else if(nMotorEncoder[frontRight] < nMotorEncoder[frontLeft])
		//	{
		//		motor[frontLeft] = speed / 2; // These are negative because we are still turning
		//		motor[backLeft] = speed / 2;
		//	}
		//	else if (nMotorEncoder[frontRight] == nMotorEncoder[frontLeft])
		//	{
		//		motor[frontRight] = speed;
		//		motor[frontLeft] = speed;
		//		motor[backRight] = speed;
		//		motor[backLeft] = speed;
		//	}
		//}



		float motorEncoderRight = targetDistance, motorEncoderLeft = targetDistance;	//600 = 1 foot

		while (nMotorEncoder(frontRight) < motorEncoderRight && nMotorEncoder(frontLeft) < motorEncoderLeft)
		{
			motor[frontRight] = speed;
			motor[frontLeft] = speed;
			motor[backRight] = speed;
			motor[backLeft] = speed;
		}

		//Could this work???
		while (nMotorEncoder(frontRight) < motorEncoderRight && nMotorEncoder(frontLeft) < motorEncoderLeft)
		{
			for (int i = 0; i <= sizeof(motors); i++)
				motor[motors[i]] = speed;
		}
	}

	//Could this work as well???
	void Turn(float degreesToTurn, int speed)
	{
		ratio = 180 / degreesToTurn;
		distanceRight = 29.85 / ratio;

		rotationsRight = distanceRight / circumference;
		degreesRight = rotationsRight * 360;

		encoderCountsRight = degreesRight * 4;
		encoderCountsLeft = encoderCountsRight * -1;

		if (degreesToTurn < 0)
		{
			motor[frontRight] = speed;
			motor[frontLeft] = speed * -1;
			motor[backRight] = speed;
			motor[backLeft] = speed * -1;

			while (nMotorEncoder[frontRight] < encoderCountsRight && nMotorEncoder[frontLeft] < encoderCountsLeft)
			{
				if (abs(nMotorEncoder[frontRight]) > abs(nMotorEncoder[frontLeft]))
				{
					motor[frontRight] = speed / 2;
					motor[backRight] = speed / 2;
				}
				else if (abs(nMotorEncoder[frontRight]) < abs(nMotorEncoder[frontLeft]))
				{
					motor[frontLeft] = speed / -2;
					motor[backLeft] = speed / -2;
				}
				else if (nMotorEncoder[frontRight] == nMotorEncoder[frontLeft])
				{
					motor[frontRight] = speed;
					motor[frontLeft] = speed;
					motor[backRight] = speed;
					motor[backLeft] = speed;
				}
			}
		}

		else if (degreesToTurn > 0)
		{
			motor[frontRight] = speed * -1;
			motor[frontLeft] = speed;
			motor[backRight] = speed * -1;
			motor[backLeft] = speed;

			while (nMotorEncoder[frontRight] < encoderCountsRight && nMotorEncoder[frontLeft] < encoderCountsLeft)
			{
				if (abs(nMotorEncoder[frontRight]) > abs(nMotorEncoder[frontLeft]))
				{
					//Since one value is negative and one is positive, abs(absolute value) makes it so that we can make sure the robot turns evenly
					motor[frontRight] = speed / -2;
					motor[backRight] = speed / -2;
				}
				else if (abs(nMotorEncoder[frontRight]) < abs(nMotorEncoder[frontLeft]))
				{
					motor[frontLeft] = speed / 2; // These are negative because we are still turning
					motor[backLeft] = speed / 2;
				}
				else if (nMotorEncoder[frontRight] == nMotorEncoder[frontLeft])
				{
					motor[frontRight] = speed;
					motor[frontLeft] = speed;
					motor[backRight] = speed;
					motor[backLeft] = speed;
				}
			}
		}
	}

	/*void TurnLeft(float degreesToTurn, int speed)
	{
		//float rotationsRight = distanceRight / circumference; On torque mode (stock), there are 627 counts to a revolution, high speed there is 392, and
		// turbo speed has 261
		//float degreesRight = rotationsRight * 627.2;
		//float encoderCountsRight = degreesRight * 4; // 24 / 18.375 is 1.30612244898
		////float rotationsLeft = distanceLeft / circumference;
		//float rotationsLeft = rotationsRight * -1; // This is the same as calculating the rotations directly
		//float degreesLeft = rotationsLeft * 627.2;
		//float encoderCountsLeft = degreesLeft * 4;

		ratio = 180 / degreesToTurn; // We find the ratio of degrees to turn to doing a 180 turn
		distanceLeft = 29.85 //ratio; This then compares the distance to turn of a 180 to the ratio made above to make the distance the robot has to turn

		rotationsLeft = distanceLeft / circumference;
		degreesLeft = rotationsLeft * 360;
		encoderCountsLeft = degreesLeft * 4; // The encoder counts in quarter degrees.
		encoderCountsRight = encoderCountsLeft * -1; // This is the same as calculating the counts directly, but saves time :)

		motor[frontRight] = speed * -1;
		motor[frontLeft] = speed;
		motor[backRight] = speed * -1;
		motor[backLeft] = speed;

		while(nMotorEncoder[frontRight] < encoderCountsRight && nMotorEncoder[frontLeft] < encoderCountsLeft)
		{
			if (abs(nMotorEncoder[frontRight]) > abs(nMotorEncoder[frontLeft]))
			{ Since one value is negative and one is positive, abs (absolute value) makes it so that we can make sure the robot
				turns evenly
				motor[frontRight] = speed / -2;
				motor[backRight] = speed / -2;
			}
			else if(abs(nMotorEncoder[frontRight]) < abs(nMotorEncoder[frontLeft]))
			{
				motor[frontLeft] = speed / 2; // These are negative because we are still turning
				motor[backLeft] = speed / 2;
			}
			else if (nMotorEncoder[frontRight] == nMotorEncoder[frontLeft])
			{
				motor[frontRight] = speed;
				motor[frontLeft] = speed;
				motor[backRight] = speed;
				motor[backLeft] = speed;
			}
		}
	}

	void TurnRight(float degreesToTurn, int speed)
	{
		ratio = 180 / degreesToTurn;
		distanceRight = 29.85 / ratio;

		rotationsRight = distanceRight / circumference;
		degreesRight = rotationsRight * 360;
		encoderCountsRight = degreesRight * 4;

		encoderCountsLeft = encoderCountsRight * -1;

		resetMotorEncoder(frontRight);
		resetMotorEncoder(frontLeft);

		motor[frontRight] = speed;
		motor[frontLeft] = speed * -1;
		motor[backRight] = speed;
		motor[backLeft] = speed * -1;

		while(nMotorEncoder[frontRight] < encoderCountsRight && nMotorEncoder[frontLeft] < encoderCountsLeft)
		{
			if (abs(nMotorEncoder[frontRight]) > abs(nMotorEncoder[frontLeft]))
			{
				motor[frontRight] = speed / 2;
				motor[backRight] = speed / 2;
			}
			else if(abs(nMotorEncoder[frontRight]) < abs(nMotorEncoder[frontLeft]))
			{
				motor[frontLeft] = speed / -2;
				motor[backLeft] = speed / -2;
			}
			else if (nMotorEncoder[frontRight] == nMotorEncoder[frontLeft])
			{
				motor[frontRight] = speed;
				motor[frontLeft] = speed;
				motor[backRight] = speed;
				motor[backLeft] = speed;
			}
		}
	}*/

	void Wait(float timeToWait)
	{
		wait1Msec(timeToWait * 1000);
	}

	void Stop()
	{
		motor[frontRight] = 0;
		motor[frontLeft] = 0;
		motor[backRight] = 0;
		motor[backLeft] = 0;
	}

	// These 'if' statements check to see if there is a jumper in the selected port. If there is a jumper in that port, the sensor returns a false value that portion of code will be ran.

	//float rotationsRight = distanceRight / circumference; // On torque mode (stock), there are 627 counts to a revolution, high speed there is 392, and
	// turbo speed has 261
	//float degreesRight = rotationsRight * 627.2;
	//float encoderCountsRight = degreesRight * 4; // 24 / 18.375 is 1.30612244898
	//float rotationsLeft = distanceLeft / circumference;
	//float degreesLeft = rotationsLeft * 627.2;
	//float encoderCountsLeft = degreesLeft * 4;

	if (!SensorBoolean[blueSide1])
	{

	}

	else if (!SensorBoolean[blueSide2])
	{

	}

	else if (!SensorBoolean[blueSide3])
	{

	}

	else if (!SensorBoolean[blueBack1])
	{

	}

	else if (!SensorBoolean[blueBack2])
	{

	}

	else if (!SensorBoolean[blueBack3])
	{

	}

	else if (!SensorBoolean[redSide1])
	{

	}

	else if (!SensorBoolean[redSide2])
	{

	}

	else if (!SensorBoolean[redSide3])
	{

	}

	else if (!SensorBoolean[redBack1])
	{

	}

	else if (!SensorBoolean[redBack2])
	{

	}

	else if (!SensorBoolean[redBack3])
	{

	}

	else
	{

	}
}
