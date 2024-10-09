/*
 * Project: FRC9086 Standard Drive Control (SDC)
 * File: DriveSystem.cpp
 * Description: Standardized driving interface
 * Created on: 7/3/2024
 */

#include "driveSystem/DriveSystem.h"
#include "driveSystem/SwerveModule.h"
#include "frc/XboxController.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <cmath>

// Creates drive system with swerve CAN IDs and offsets
DriveSystem::DriveSystem(
    int swerve1Drive, int swerve1Steer, double swerve1Offset,
    int swerve2Drive, int swerve2Steer, double swerve2Offset,
    int swerve3Drive, int swerve3Steer, double swerve3Offset,
    int swerve4Drive, int swerve4Steer, double swerve4Offset
):
swerve1(swerve1Drive, swerve1Steer),
swerve2(swerve2Drive, swerve2Steer),
swerve3(swerve3Drive, swerve3Steer),
swerve4(swerve4Drive, swerve4Steer)

{

    // Set offsets
    this->swerve1Offset = swerve1Offset;
    this->swerve2Offset = swerve2Offset;
    this->swerve3Offset = swerve3Offset;
    this->swerve4Offset = swerve4Offset;

}

// Applies vector to all swerves with offset angle
void DriveSystem::driveVectorOffset(double speed, double angle) {
    swerve1.setState(speed, angle + swerve1Offset);
    swerve2.setState(-speed, angle + swerve2Offset);
    swerve3.setState(-speed, angle + swerve3Offset);
    swerve4.setState(speed, angle + swerve4Offset);
}

// Applies vector to all swerves with offset angle (field oriented) (gyro needed)
void DriveSystem::driveVectorOffsetGyro(double speed, double angle) {
    driveVectorOffset(speed, angle); // TODO: ADD GYRO MODULE CODE WHEN WE GET IT
}

// Applies vector to all swerves
void DriveSystem::driveVector(double speed, double angle) {
    swerve1.setState(speed, angle);
    swerve2.setState(-speed, angle);
    swerve3.setState(-speed, angle);
    swerve4.setState(speed, angle);
}

// Sets the angle offsets
void DriveSystem::setAngleOffset(int offset1, int offset2, int offset3, int offset4) {
    swerve1Offset = offset1;
    swerve2Offset = offset2;
    swerve3Offset = offset3;
    swerve4Offset = offset4;
}

// Standard xbox controller controls
void DriveSystem::driveXbox(int id) {

    frc::XboxController controller{0};

	// Get inputs
	double x1Input = controller.GetLeftX();
	double y1Input = controller.GetLeftY();
	double forwardThrottle = controller.GetRawAxis(3);
	double backwardThrottle = controller.GetRawAxis(2);
	double rotate = controller.GetBButton();
	double lockSwerve = controller.GetXButton();

	// Output variables
	double steeringAngle, speed = 0;

	// Get the triggers to make throttles
	speed = forwardThrottle - backwardThrottle;

	// Swerve control
	steeringAngle = atan2(x1Input, y1Input);
	if (x1Input < 0) {
		steeringAngle = (2 * M_PI) + steeringAngle;
	}

	// Fix swerve values when at 0, 0
	if (x1Input == 0 && y1Input == 0) {
		speed = -speed;
	}

    // Actually make the robot move now
	if (rotate) { // rotate mode
		driveVector(speed, M_PI / 4);

	} else if (lockSwerve){ // X lock mode
		swerve1.setPosition((2 * M_PI) - M_PI / 4);
		swerve2.setPosition((2 * M_PI) - M_PI / 4);
		swerve3.setPosition((2 * M_PI) - M_PI / 4);
		swerve4.setPosition((2 * M_PI) - M_PI / 4);

	} else { // normal driving
        driveVectorOffset(speed, steeringAngle);
	}
}

// Standard xbox controller controls (field oriented) (gyro needed)
void DriveSystem::driveXboxGyro(int id) {
	driveXbox(id); // TODO: ADD GYRO MODULE CODE WHEN WE GET IT
}

// Prints all encoder locations to the FRC Smart Dashboard
void DriveSystem::printDebuggingData() {
	frc::SmartDashboard::PutNumber("SWRV Front Left ENC: ", swerve1.getPosition());
	frc::SmartDashboard::PutNumber("SWRV Front Right ENC: ", swerve2.getPosition());
	frc::SmartDashboard::PutNumber("SWRV Rear Left ENC: ", swerve3.getPosition());
	frc::SmartDashboard::PutNumber("SWRV Rear Right ENC: ", swerve4.getPosition());
}


