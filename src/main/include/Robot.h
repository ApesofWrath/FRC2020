/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string>

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>

#include <frc/Joystick.h>

#include "ControlPanel.h"
#include "Drive/DriveController.h"
#include "RobotContainer.h"


class Robot : public frc::TimedRobot {
 public: 

  ControlPanel* controlpanel; 

  DriveController* drive;

//Temporary Button ids
  const int BUTTON_STOP = 2, POSITION_BUTTON = 5, ROTATION_BUTTON = 4, INTAKE = 3;

  Colors currentColor, desiredColor;
  frc::Joystick  *joyT, *joyW;

  const float CONTROL_WHEEL_SPEED_ON = 1.0f;
  const float CONTROL_WHEEL_SPEED_OFF = 0;

  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;
  std::string getColor(Colors c);
    
  AutonDrive *a_drive;

 private:
  frc::SendableChooser<Colors> m_descolor_chooser;
  
  frc2::Command* m_autonomousCommand = nullptr;
  RobotContainer m_container = RobotContainer(a_drive);
  const Colors kDesColorDefault = Colors::WHITE;
};
