#pragma config(Sensor, dgtl1,  leftMotorEncoder, sensorRotation)
#pragma config(Sensor, dgtl2,  rightMotorEncoder, sensorRotation)
#pragma config(Sensor, dgtl3,  bottomLimitSwitch, sensorTouch)
#pragma config(Sensor, dgtl4,  topLimitSwitch, sensorTouch)
#pragma config(Motor,  port1,           frontLeftMotor, tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port3,           leftArm1,      tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port4,           leftArm2,      tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port5,           backLeftMotor, tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port6,           conveyer,      tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port7,           rightArm2,     tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port8,           rightArm1,     tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port9,           backRightMotor, tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port10,          frontRightMotor, tmotorServoContinuousRotation, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)


#include "constants.h"

#define DIRECTION 1 // 1 if blue, -1 if red
#define BUFFER_DISTANCE 3
#define MOTOR_POWER 100
#define KP 5

void locomoteAll(int power) {
	motor[frontLeftMotor] = power;
	motor[frontRightMotor] = power;
	motor[backLeftMotor] = power;
	motor[backRightMotor] = power;
}

void adjustSlaveMotor(int amount) {
	motor[backRightMotor] += amount;
	motor[frontRightMotor] += amount;
}

int motorStatus;
int goUntilGlob;
int leftEncoder;
int rightEncoder;
int error;
void moveStraight(float inches) {
	if (inches > 0) {
		locomoteAll(MOTOR_POWER);
	} else {
		locomoteAll(-MOTOR_POWER);
	}

	wait1Msec(100* inches);
	locomoteAll(0);
}

/*void turnRobot (int direction, int power) {
	motor[backLeftMotor] = power * -direction;
	motor[frontLeftMotor] = power * -direction;
	motor[backRightMotor] = power * direction;
	motor[frontRightMotor] = power * direction;
}

void turn(int degrees) {
	double wheelDistance = ROBOT_RADIUS * (degrees * PI/180);
	if (degrees > 0) {
		turnRobot(1 , MOTOR_POWER);
	}
	else if (degrees <= 0) {
		turnRobot(-1, MOTOR_POWER);
	}
	int startValue = SensorValue[leftMotorEncoder];
	int beginError = SensorValue[leftMotorEncoder] - SensorValue[rightMotorEncoder];
}*/

void raiseTheFlag() {
	motor[conveyer] = -50;
	wait10Msec(30);
	motor[conveyer] = 0;
}
void setArmsAt(int power) {
	motor[rightArm1] = power;
	motor[rightArm2] = power;
	motor[leftArm1] = -power;
	motor[leftArm2] = -power;
}

void startConveyor() {
	motor[conveyer] = CONVEYOR_POWER;
}

void stopConveyor() {
	motor[conveyer] = 0;
}

void reverseConveyor() {
	motor[conveyer] = -CONVEYOR_POWER;
}
task setArmUp() {
	setArmsAt(ARM_POWER_HIGH);
	while (!SensorValue[topLimitSwitch]);
	setArmsAt(-127);
	wait1Msec(10);
	setArmsAt(0);
}

task setArmDown() {
	setArmsAt(-ARM_POWER_HIGH);
	while (!SensorValue[bottomLimitSwitch]);
	setArmsAt(127);
	wait1Msec(10);
	setArmsAt(0);
}

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
	//raiseTheFlag();
	startConveyor();
	moveStraight(20);
	stopConveyor();
	locomoteAll(-MOTOR_POWER);
	while(true);
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
	while(true)
	{
		//Right side of the robot is controlled by the right joystick, Y-axis
		motor[frontRightMotor] = vexRT[Ch2];
		motor[backRightMotor]  = vexRT[Ch2];
		//Left side of the robot is controlled by the left joystick, Y-axis
		motor[frontLeftMotor] = vexRT[Ch3];
		motor[backLeftMotor]  = vexRT[Ch3];
		if (vexRT[Btn6U] == 1) {
			if (SensorValue[topLimitSwitch] == 0) {
				setArmsAt(ARM_POWER_HIGH);
			} else {
				setArmsAt(0);
			}
		} else if (vexRT[Btn6D] == 1) {
			if (SensorValue[bottomLimitSwitch] == 0) {
				setArmsAt(-ARM_POWER_HIGH);
			}else {
				setArmsAt(0);
			}
		} else {
			setArmsAt(0);
		}

		if (vexRT[Btn5U] ==1) {
			motor[conveyer] = CONVEYOR_POWER;
		} else if (vexRT[Btn5D] == 1) {
			motor[conveyer] = -CONVEYOR_POWER;
		} else {
			motor[conveyer] = 0;
		}
	}
}
