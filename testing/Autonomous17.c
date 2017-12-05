//variables
int leftMotorSpeed = 0;
int rightMotorSpeed = 0;
int leftFrontMotor = motor1;
int rightFrontMotor = motor2;
int leftBackMotor = motor3;
int rightBackMotor = motor4;
int claw = motor5;
int armMotor = motor6;

/***** MOVEMENT *****/

//move the robot forward or backward
//wheelPower is how fast the robot goes, values -127 to 127 are acceptable
	//if wheelPower is positive, robot goes forwards
	//if wheelPower is negative, robot goes backwards
//curve is how much the robot should turn tbd how the robot will use that value to turn though...
void moveWheels(int wheelPower, float curve, int moveTime)
{
	leftMotorSpeed = -wheelPower*curve;
	rightMotorSpeed = wheelPower*(1-curve);
	motor[leftFrontMotor] = leftMotorSpeed;
	motor[leftBackMotor] = leftMotorSpeed;
	motor[rightFrontMotor] = rightMotorSpeed;
	motor[rightBackMotor] = rightMotorSpeed;
}

//turn in place
//power is what direction and how fast to turn, values -127 to 127 are acceptable
	//if power is a positive integer it goes clockwise
	//if power is a negative integer it goes counterclockwise
void turn(int power)
{
	if(power>0)
	{
		leftFrontMotor = power;
		leftBackMotor = power;
	}
	else if(power<0)
	{
		rightFrontMotor = power;
		rightBackMotor = power;
	}
	else
	{
		return;
	}
}

//places the cone the robot is holding midair on the mobile goal in the pouch
void coneOnMobileGoal()
{

}

//lifts the mobile goal behind it and places it into the pouch
void liftMobileGoal()
{

}

//places the mobile goal in the pouch into the zone
void placeMobileGoal()
{

}

//opens the claw that will pick up the cones we will place on the mobile goal
//since it is the same claw as last year, for convenience I will use the same code once I get the chance
void openClaw()
{
	motor[claw] = 35;
	sleep(500);
	motor[claw] = 0;
}

//closes the claw that will pick up the cones we will place on the mobile goal
//since it is the same claw as last year, for convenience I will use the same code once I get the chance
void closeClaw()
{
	motor[claw] = -35;
	sleep(500);
	motor[claw] = 0;
}

//lifts up a yellow cone in its claw and holds it mid air
void liftCone()
{
	closeClaw();
	motor[armMotor] = 50;
	sleep(1500);
	motor[armMotor] = 0;
}

/***** AUTONOMOUS *****/
task main()
{
	//turn clockwise
		//45 degrees i think
	turn(50);
		//move forward until you can grab cone
		//stop
	//pick up cone
	//drive clockwise forward
	//drive backwards
		//until bumper sensor hits mobile goal
	//pick up mobile goal
	//place cone on mobile goal
	//turn clockwise in an arc until you reach the 10 point zone
	//wait for driver phase

}
