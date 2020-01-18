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


class Robot : public frc::TimedRobot {
 public: 

  ControlPanel* controlpanel; 

//Temporary Button ids
  const int BUTTON_STOP = 2, POSITION_BUTTON = 3, ROTATION_BUTTON = 4;

  Colors currentColor, desiredColor;
  frc::Joystick* joy;

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


  static constexpr auto i2cPort = frc::I2C::Port::kOnboard;
  rev::ColorSensorV3 m_colorSensor{i2cPort};
  frc::Color detectedColor;
  
 private:
  frc::SendableChooser<std::string> m_chooser;
  frc::SendableChooser<Colors> m_descolor_chooser;
  
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  const Colors kDesColorDefault = Colors::WHITE;
  std::string m_autoSelected;
};
