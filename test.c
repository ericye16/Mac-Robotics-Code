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

void turnRobot (int direction, int power) {
	motor[backLeftMotor] = power * -direction;
	motor[frontLeftMotor] = power * -direction;
	motor[backRightMotor] = power * direction;
	motor[frontRightMotor] = power * direction;
}

void turn(int deciseconds) {
	if (deciseconds > 0) {
		turnRobot(1 , MOTOR_POWER);
	}
	else if (deciseconds <= 0) {
		turnRobot(-1, MOTOR_POWER);
	}
	wait1Msec(100*deciseconds);
	locomoteAll(0);
}

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
task main()
{

	//raiseTheFlag();
	startConveyor();
	moveStraight(20);
	stopConveyor();
	locomoteAll(-MOTOR_POWER);
	wait1Msec(8000);
	turn(13);
	locomoteAll(0);
	reverseConveyor();
}
