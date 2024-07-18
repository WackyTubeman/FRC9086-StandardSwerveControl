/*
 * Project: FRC9086 Standard Drive Control (SDC)
 * File: SwerveModule.h
 * Description: Standardized creation of swerve drive modules
 * Created on: 7/3/2024
 */

#pragma once

#include <rev/CANSparkMax.h>
#include <rev/SparkAbsoluteEncoder.h>
#include <rev/SparkPIDController.h>
#include <rev/SparkRelativeEncoder.h>

class SwerveModule {
private:

    // Create drive motors
    rev::CANSparkMax driveMotor;
    rev::CANSparkMax steerMotor;

    // Create PID controllers
    rev::SparkPIDController drivePID = driveMotor.GetPIDController();
    rev::SparkPIDController steerPID = steerMotor.GetPIDController();

    // Create encoder
    rev::SparkAbsoluteEncoder steerEncoder = steerMotor.GetAbsoluteEncoder(rev::SparkAbsoluteEncoder::Type::kDutyCycle);
    rev::SparkRelativeEncoder driveEncoder = driveMotor.GetEncoder();

public:

	// Create a swerve module
    SwerveModule(const int driveID, const int steerID);

	// Gets the position of the steering system (in radians)
    double getPosition();

	// Sets the position of the steering system (in radians)
    void setPosition(double position);

	// Sets motor to a specific speed (-1, 1)
    void setSpeed(double speed);

	// Sets both the position and speed (input vector of speed and radians)
    void setState(double speed, double position);

	// Sets the drive motor to coast (true) or brake (false)
    void setDriveCoast(bool coast);

};