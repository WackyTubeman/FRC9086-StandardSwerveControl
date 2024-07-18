/*
 * Project: FRC9086 Standard Drive Control (SDC)
 * File: DriveSystem.h
 * Description: Standardized driving interface
 * Created on: 7/3/2024
 */

#pragma once

#include "driveSystem/SwerveModule.h"
#include "frc/XboxController.h"

class DriveSystem {
private:

    // Offset angles
    double swerve1Offset;
    double swerve2Offset;
    double swerve3Offset;
    double swerve4Offset;

public:

    // Creates drive system with swerve CAN IDs and offsets
    DriveSystem(
	    int swerve1Drive, int swerve1Steer, double swerve1Offset,
		int swerve2Drive, int swerve2Steer, double swerve2Offset,
		int swerve3Drive, int swerve3Steer, double swerve3Offset,
		int swerve4Drive, int swerve4Steer, double swerve4Offset
    );

    // Swerve modules so that they can be interacted with in Robot.cpp
	SwerveModule swerve1;
	SwerveModule swerve2;
	SwerveModule swerve3;
	SwerveModule swerve4;


    // Applies vector to all swerves with offset angle
    void driveVectorOffset(double speed, double angle);

    // Applies vector to all swerves with offset angle (field oriented) (gyro needed)
    void driveVectorOffsetGyro(double speed, double angle);

    // Applies vector to all swerves
    void driveVector(double speed, double angle);

    // Sets the angle offsets
    void setAngleOffset(int offset1, int offset2, int offset3, int offset4);

    // Standard xbox controller controls
    void driveXbox(int id);

	// Standard xbox controller controls (field oriented) (gyro needed)
	void driveXboxGyro(int id);

	// Prints all encoder locations to the FRC Smart Dashboard
	void printDebuggingData();

};