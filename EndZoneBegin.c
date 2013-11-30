#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)

#DEFINE DIRECTION 1; // 1 if blue, -1 if red
#DEFINE BUFFER_DISTANCE 3;

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
  // Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
//begin facing hanging bars, assuming initially in low-scoring zone
//assumptions: arm can knock big balls off barrier, arm cannot rotate, arm cannot affect location of robot
	//check for line
	moveStraight(24 + BUFFER_DISTANCE);
	//pick up balls
	moveStraight(-BUFFER_DISTANCE);
	turn(90 * DIRECTION);
	moveStraight(50);
	turn(90 * DIRECTION);
	moveStraight(78 + BUFFER_DISTANCE);
	//knock big ball over
	moveStraight(-BUFFER_DISTANCE);
	turn(90 * DIRECTION);
	moveStraight(36);
	turn(-90 * DIRECTION);
	moveStraight(BUFFER_DISTANCE);
	//knock big ball over
	//retract arm
	//check for line
	moveStraight(24);
	turn(-45*DIRECTION);
	//begin moving balls up
	moveStraight(33.94 + BUFFER_DISTANCE); // sqrt(2 * 24^2);
	//drop balls off and end
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol()
{
	// User control code here, inside the loop

	while (true)
	{
	  // This is the main execution loop for the user control program. Each time through the loop
	  // your program should update motor + servo values based on feedback from the joysticks.

	  // .....................................................................................
	  // Insert user code here. This is where you use the joystick values to update your motors, etc.
	  // .....................................................................................

	  UserControlCodePlaceholderForTesting(); // Remove this function call once you have "real" code.
	}
}
