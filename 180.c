#pragma config(Motor,  port2,           frontRight,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           frontLeft,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           backRight,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           backLeft,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           rightLauncher, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           leftLauncher,  tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           topBelt,       tmotorVex393_MC29, openLoop)

// Setup for the shaft encoders. All units are in inches, unless otherwise stated.
float diameter = 4;
float circumference = PI * diameter;

// Now we will find out how many times each wheel has to turn to go a specefied distance for the right side.
float distanceRight = 29.875;
int rotationsRight = distanceRight / circumference;
float degreesRight = rotationsRight * 360;
int encoderCountsRight = degreesRight * 4; // The encoder counts in quarter degrees.

// This is so we can find out how many times the left wheels have to turn to go the specefied distance
float distanceLeft = -29.875;
int rotationsLeft = distanceLeft / circumference;
float degreesLeft = rotationsLeft * 360;
int encoderCountsLeft = degreesLeft * 4;

task main() //This will only give us the required number on the encoders for a 180 degree turn
{

	if (vexRT[Btn8D] == 1)
	{
		// We will reset the motor encoder values here so we don't screw anything up
		nMotorEncoder[frontRight] = 0;
		nMotorEncoder[frontLeft] = 0;

		if (nMotorEncoder[frontRight] >= encoderCountsRight && nMotorEncoder[frontLeft] >= encoderCountsLeft)
		{
			motor[frontRight] = 0;
			motor[frontLeft] = 0;
			motor[backRight] = 0;
			motor[backLeft] = 0;
		}

		else
		{
			motor[frontRight] = 127;
			motor[frontLeft] = -127;
			motor[backRight] = 127;
			motor[backLeft] = -127;
		}
	}

}
