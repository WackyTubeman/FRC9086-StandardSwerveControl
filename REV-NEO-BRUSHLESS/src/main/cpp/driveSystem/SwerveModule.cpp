/*
 * Project: FRC9086 Standard Drive Control (SDC)
 * File: SwerveModule.cpp
 * Description: Standardized creation of swerve drive modules
 * Created on: 7/3/2024
 */

#include "driveSystem/SwerveModule.h"
#include <rev/CANSparkMax.h>
#include <rev/SparkAbsoluteEncoder.h>
#include <rev/SparkPIDController.h>
#include <rev/SparkRelativeEncoder.h>
#include <cmath>

// Create a swerve module
SwerveModule::SwerveModule(const int driveID, const int steerID):
        driveMotor(driveID, rev::CANSparkMax::MotorType::kBrushless),
        steerMotor(steerID, rev::CANSparkMax::MotorType::kBrushless) {

    // Reset to the defaults to be safe
    driveMotor.RestoreFactoryDefaults();
    steerMotor.RestoreFactoryDefaults();

    // Set motor current limits to prevent them from cooking
    driveMotor.SetSmartCurrentLimit(40);
    steerMotor.SetSmartCurrentLimit(20);

    // Set modes to brake
    driveMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    steerMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

    // Drive PID is useful for adjusting how the drive motors operate
    driveEncoder.SetPositionConversionFactor(0);

    drivePID.SetP(0.1);
    drivePID.SetI(1e-4);
    drivePID.SetD(1);
    drivePID.SetIZone(0);
    drivePID.SetFF(0);
    steerPID.SetOutputRange(-1, 1);

    // Steer PID will adjust the aggressiveness of the steering system
    steerPID.SetFeedbackDevice(steerEncoder);
    steerEncoder.SetPositionConversionFactor(2 * M_PI);
    steerEncoder.SetInverted(true);

    steerPID.SetP(0.1);
    steerPID.SetI(1e-4);
    steerPID.SetD(1);
    steerPID.SetIZone(0);
    steerPID.SetFF(0);
    steerPID.SetOutputRange(-1, 1);

    steerPID.SetPositionPIDWrappingEnabled(true);
    steerPID.SetPositionPIDWrappingMinInput(0);
    steerPID.SetPositionPIDWrappingMaxInput(2 * M_PI);

    // Burn flash to save to memory
    driveMotor.BurnFlash();
    steerMotor.BurnFlash();
}

// Gets the position of the steering system (in radians)
double SwerveModule::getPosition() {
    double position = steerEncoder.GetPosition();
    return position;
}

// Sets the position of the steering system (in radians)
void SwerveModule::setPosition(double position) {

    // Check and adjust input value before applying (get it into 0 - 2pi range)
    while (position > (M_PI * 2) || position < 0) {
        if (position > (M_PI * 2)) { // Angle is over 2pi
            position -= (M_PI * 2);
        } else if (position < 0) { // Angle is less than 0
            position += (M_PI * 2);
        }
    }

    // Set steering position to the correct position using PID, steers with radians
    steerPID.SetReference(position, rev::CANSparkMax::ControlType::kPosition);
}

// Sets motor to a specific speed (-1, 1)
void SwerveModule::setSpeed(double speed) {
    drivePID.SetReference(speed, rev::CANSparkMax::ControlType::kDutyCycle);
}

// Sets both the position and speed (input vector of speed and radians)
void SwerveModule::setState(double speed, double position) {
    // Run the position and speed functions
    setPosition(position);
    setSpeed(speed);
}

// Sets the drive motor to coast (true) or brake (false)
void SwerveModule::setDriveCoast(bool coast) {
    if (coast) {
        driveMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
    } else {
        driveMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    }
}