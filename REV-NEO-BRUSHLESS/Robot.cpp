// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"
#include "driveSystem/DriveSystem.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include "frc/XboxController.h"

// Does things for robot start up
void Robot::RobotInit() {
}

/**
 * Used during all modes (best for diagnostics and data output)
 */
void Robot::RobotPeriodic() {
}

/**
 * Called once to start disabled
 */
void Robot::DisabledInit() {}

/**
 * Used during disabled mode
 */
void Robot::DisabledPeriodic() {}

/**
 * Called once to start auton
 */
void Robot::AutonomousInit() {}

/**
 * Used during auton mode
 */
void Robot::AutonomousPeriodic() {

	// Replace this with the code on the laptop

}

/**
 * Called once to start teleop
 */
void Robot::TeleopInit() {}

/**
 * Used during teleop mode
 */
void Robot::TeleopPeriodic() {
  	// Operate swerve
    drive.driveXbox(0);
}

/**
 * Used during test mode
 */
void Robot::TestPeriodic() {
}

/**
 * This function is called once when the robot is first started up.
 */
void Robot::SimulationInit() {}

/**
 * This function is called periodically whilst in simulation.
 */
void Robot::SimulationPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
