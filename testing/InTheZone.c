//declare variables below
//doubles don't exist in RobotC apparently, there is only floats
float calculatedPower = 0;
int leftMotorSpeed = 0;
int rightMotorSpeed = 0;
//i guess percentage variables aren't necessary
float percentage = 0.0;
float leftFrontWheel = motor1;
float rightFrontWheel = motor2;
float leftBackWheel = motor3;
float rightBackWheel = motor4;

void moveWheels(){
	//last year, we used the right joystick to drive the wheels
	//left wheel = motor 1
	//right wheel = motor 2
	//to calcuate the power to move the motor at, take the distance between (ch4 value, ch3 value) and (0,0) or the square root of ((x^2)+(y^2))
	calculatedPower = sqrt(pow(vexRT[ChC],2)+pow(vexRT[ChD],2));
	//if you were to face the same direction the robot is, left wheel moves -1*(calculated power) and right wheel moves the calculated power
	//to turn, make the power go to the motors at a percentage
	//percentage calculation is probably (ch4Value/254)+.5
		//254 is the denominator because it is the max motor speed, 127, times 2
	percentage = vexRT[ChD]/254+.5;
	//if ch4 > 0
	if(vexRT[ChD]>0){
		//right motor speed = ((ch4Value/254)+.5)*(calculated power)
		rightMotorSpeed = percentage*calculatedPower;
		//left motor speed = 1-(right motor speed)
		leftMotorSpeed = (1-percentage)*calculatedPower;
	}
	//if ch4 < 0
	if(vexRT[ChD]<0){
		//left motor speed = ((ch4Value/254)+.5)*(calculated power)
		leftMotorSpeed = percentage*calculatedPower;
		//right motor speed = 1-(left motor speed)
		rightMotorSpeed = (1-percentage)*calculatedPower;
	}
	//else
	else{
		//return
		return;
	}
	//left motor go
	motor[leftFrontWheel] = leftMotorSpeed;
	motor[leftBackWheel] = leftMotorSpeed;
	//right motor go
	motor[rightFrontWheel] = rightMotorSpeed;
	motor[rightBackWheel] = rightMotorSpeed;
}

//make sure main() is the last "task", weird C mechanic
task main()
{
	//apparently does not compile, but book says "this command should be the first thing in your "task main()" so idk
	//will not set up any motors and sensors, you must manually set the motos and sensors in the 'Motors and Sensors Setup' menu
	//robotType();
	//only two motors will be used for the base so we can use the rest to lift the cones and mobile goal

	while(true){
		moveWheels();
	}




}