 /*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <iostream>


#include <frc/smartdashboard/SmartDashboard.h>



void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);


  m_descolor_chooser.AddDefault("None",  Colors::WHITE);
  m_descolor_chooser.AddObject("Red",    Colors::RED);
  m_descolor_chooser.AddObject("Blue",   Colors::BLUE);
  m_descolor_chooser.AddObject("Green",  Colors::GREEN);
  m_descolor_chooser.AddObject("Yellow", Colors::YELLOW);

  frc::SmartDashboard::PutData("Desired Color", &m_descolor_chooser);

  joy = new frc::Joystick(0);
  controlpanel = new ControlPanel();

  T16 = new TalonSRX(16);
  T49 = new TalonSRX(49);
  T14 = new TalonSRX(14);
  T2 = new TalonSRX(2);

  V4 = new VictorSPX(4);
  V7 = new VictorSPX(7);
  V10 = new VictorSPX(10);

  V4->Follow(*T16);
  V7->Follow(*T16);

  V10->Follow(*T49);
  T14->Follow(*T49);


}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {
  
}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  std::cout << "Auto selected: " << m_autoSelected << std::endl;

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::AutonomousPeriodic() {
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}
void Robot::TeleopInit() {
}
bool toggle = false;
void Robot::TeleopPeriodic() {
  
  
  frc::SmartDashboard::PutData("Desired Color", &m_descolor_chooser);

  controlpanel->DesireColor(m_descolor_chooser.GetSelected());

  if (joy->GetRawButton(1)) {
    T2->Set(ControlMode::PercentOutput, -1.0f);
  } else {
    T2->Set(ControlMode::PercentOutput, 0.0f);
  }


  T49->Set(ControlMode::PercentOutput, joy->GetY());
  T16->Set(ControlMode::PercentOutput, -joy->GetY());


  


  if (joy->GetRawButton(BUTTON_STOP)) {
    controlpanel->Stop();
  }
  if (joy->GetRawButton(POSITION_BUTTON)) {
    controlpanel->PositionMode();
  }
  if (joy->GetRawButton(ROTATION_BUTTON)) {
    controlpanel->RotationMode();
  }



  controlpanel->StateMachine();

  // if (((currentColor == desiredColor || desiredColor == Colors::WHITE) && !joy->GetTrigger()) || joy->GetRawButton(2)) {
  //   talon0->Set(ControlMode::PercentOutput, 0);
  // } else {
  //   talon0->Set(ControlMode::PercentOutput, CONTROL_WHEEL_SPEED_ON);
  // }

}

void Robot::TestPeriodic() {}



#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
