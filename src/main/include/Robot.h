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


class Robot : public frc::TimedRobot {
 public: 

  ControlPanel* controlpanel; 

  DriveController* drive;

<<<<<<< HEAD

  TalonSRX *T16, *T49, *T14, *T2;
=======
>>>>>>> 71a6b2bf792c7f3faed3fe74d6410f67bacb297d
//Temporary Button ids
  const int BUTTON_STOP = 2, POSITION_BUTTON = 5, ROTATION_BUTTON = 4, INTAKE = 3;

  TalonSRX *T46;
  TalonFX *Falcon_T, *Falcon_T2;

  Colors currentColor, desiredColor;
  frc::Joystick  *joyT, *joyW;
<<<<<<< HEAD

=======
>>>>>>> 71a6b2bf792c7f3faed3fe74d6410f67bacb297d

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
<<<<<<< HEAD

  
=======
>>>>>>> 71a6b2bf792c7f3faed3fe74d6410f67bacb297d
    
 private:
  frc::SendableChooser<std::string> m_chooser;
  
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  std::string m_autoSelected;
};
