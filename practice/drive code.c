#pragma config(Sensor, in1,    potentiometer,  sensorPotentiometer)
#pragma config(Motor,  port2,           leftFrontWheel, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           rightFrontWheel, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           leftBackWheel, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           rightBackWheel, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           armLeft,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           armRight,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           claw,          tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//declare variables below
//doubles don't exist in RobotC apparently, there is only floats



void moveWheels(){
	motor[leftFrontWheel] = .5*vexRT[Ch3];
	motor[leftBackWheel] = .5*vexRT[Ch3];
	motor[rightFrontWheel] = .5*-vexRT[Ch2];
	motor[rightBackWheel] = .5*-vexRT[Ch2];
}

//opens or closes claw
	//if 6U is pressed, it opens
	//if 6D is pressed, it closes
void updateClaw()
{
    if(vexRT[Btn6U] == 1) // If upper Z button down
        motor[claw] = 25;
    else if(vexRT[Btn6D] == 1) // If lower Z button down
        motor[claw] = -25;
    else
    	motor[claw] = 0;
}

//raises, lowers, or stops moving the arm depending if button 5U, 5D, or neither are pressed
void updateArm()
{
	int power = 0;

	if((SensorValue[potentiometer]>=2000)||((vexRT[Btn5U] == 0) && (vexRT[Btn5D] == 0)))
	{
		motor[armLeft]=-30;
		motor[armRight]=30;
	}
	else if(vexRT[Btn5U] == 1) //if left upper Z button is pressed
	{
		power += 60;
		motor[armLeft] = -50-power;
		motor[armRight] = 50+power;
	}
	else if(vexRT[Btn5D] == 1) //if left lower Z button is pressed
	{
		power += 1;
		motor[armLeft] = -7-power;
		motor[armRight] = 6+power;
	}
	else
	{
		motor[armLeft] = -30;
		motor[armRight] = 30;
	}

}


//method to raise arm but can't do anything else until it stops moving
//supposed to be used with if(vexRT[Btn5U] == 1)
//just here in case updateArm doesn't work out
//void raiseArm(){
//	motor[armLeft] = 50;
//	motor[armRight] = -50;
//	waitUntil(vexRT[Btn5U] == 0);
//	motor[armLeft] = 0;
//	motor[armRight] = 0;
//}

//method to lower arm but can't do anything else until it stops moving
//supposed to be used with if(vexRT[Btn5D] == 1)
//just here in case updateArm doesn't work out
//void lowerArm(){
//	motor[armLeft] = -50;
//	motor[armRight] = 50;
//	waitUntil(vexRT[Btn5D] == 0);
//	motor[armLeft] = 0;
//	motor[armRight] = 0;
//}

//claw - 6U opens
// 6D close
//arm - 5U raises up
// 5D lowers
//mobile goal
//8D raises
//8R lowers
//left joystick controls wheels

//make sure main() is the last "task", weird C mechanic
task main()
{
	//apparently does not compile, but book says "this command should be the first thing in your "task main()" so idk
	//will not set up any motors and sensors, you must manually set the motos and sensors in the 'Motors and Sensors Setup' menu
	//robotType();
	//only two motors will be used for the base so we can use the rest to lift the cones and mobile goal

	while(true){
		moveWheels();
		updateClaw();
		updateArm();
	}
}
