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

#include <ctre/Phoenix.h>
#include <frc/Joystick.h>

#include "Shooter.h"
namespace apesofwrath {

class Robot : public frc::TimedRobot {
 public:

  frc::Joystick* joy;
  TalonSRX* talon0;
  Shooter* shooter, speed;

  const float CONTROL_WHEEL_SPEED_ON = 1.0f;
  const float CONTROL_WHEEL_SPEED_OFF = 0;

  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;
  void UpdateButtons();
  
  bool shoot, intake, stop, waiting;

 private:
  frc::SendableChooser<std::string> m_chooser;
  
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  std::string m_autoSelected;
};

}