
#pragma once

#include <frc/TimedRobot.h>
#include "driveSystem/DriveSystem.h"
#include "frc/XboxController.h"


class Robot : public frc::TimedRobot {
private:

    DriveSystem drive = DriveSystem(2, 1, 1.57,
                                    18, 19, 0,
                                    8, 7, 3.14,
                                    10, 11, 4.71);

public:
    void RobotInit() override;
    void RobotPeriodic() override;
    void DisabledInit() override;
    void DisabledPeriodic() override;
    void AutonomousInit() override;
    void AutonomousPeriodic() override;
    void TeleopInit() override;
    void TeleopPeriodic() override;
    void TestPeriodic() override;
    void SimulationInit() override;
    void SimulationPeriodic() override;

};