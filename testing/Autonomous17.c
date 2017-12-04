//variables
int leftMotorSpeed = 0;
int rightMotorSpeed = 0;
int leftFrontMotor = motor1;
int rightFrontMotor = motor2;
int leftBackMotor = motor3;
int rightBackMotor = motor4;

/***** MOVEMENT *****/

//move the robot forward or backward
//wheelPower is how fast the robot goes, values -127 to 127 are acceptable
	//if wheelPower is positive, robot goes forwards
	//if wheelPower is negative, robot goes backwards
//curve is how much the robot should turn tbt how the robot will use that value to turn though...
void moveWheels(int wheelPower, float curve)
{
	leftMotorSpeed = wheelPower*curve;
	rightMotorSpeed = wheelPower*(1-curve);
	motor[
}

//turn in place
//power is what direction and how fast to turn, values -127 to 127 are acceptable
	//if power is a positive integer it goes clockwise
	//if power is a negative integer it goes counterclockwise
//time is how many seconds to run the code
void turn(int power, int time){

}

//lifts up a yellow cone in its claw and holds it mid air
void liftCone()
{

}

//places the cone the robot is holding midair on the mobile goal in the pouch
void placeOnMobileGoal()
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

}

//closes the claw that will pick up the cones we will place on the mobile goal
//since it is the same claw as last year, for convenience I will use the same code once I get the chance
void closeClaw()
{

}

/***** AUTONOMOUS *****/
task main()
{
	//turn clockwise
		//45 degrees i think
	turn(50, 3);
	
	//pick up cone
	
	//drive clockwise forward
	//drive backwards
	//pick up mobile goal
	//turn clockwise in an arc until you reach the 10 point zone
	//wait for driver phase

}
