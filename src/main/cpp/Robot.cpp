 /*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <iostream>


#include <frc/smartdashboard/SmartDashboard.h>



void apesofwrath::Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);


  m_descolor_chooser.AddDefault("None",  apesofwrath::Colors::WHITE);
  m_descolor_chooser.AddObject("Red",    apesofwrath::Colors::RED);
  m_descolor_chooser.AddObject("Blue",   apesofwrath::Colors::BLUE);
  m_descolor_chooser.AddObject("Green",  apesofwrath::Colors::GREEN);
  m_descolor_chooser.AddObject("Yellow", apesofwrath::Colors::YELLOW);

  frc::SmartDashboard::PutData("Desired Color", &m_descolor_chooser);

  joy = new frc::Joystick(0);
  talon0 = new TalonSRX(0);
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void apesofwrath::Robot::RobotPeriodic() {
  detectedColor = m_colorSensor.GetColor();
  
  frc::SmartDashboard::PutNumber("Red", detectedColor.red);
  frc::SmartDashboard::PutNumber("Green", detectedColor.green);
  frc::SmartDashboard::PutNumber("Blue", detectedColor.blue);

  if (detectedColor.red > 0.3 && detectedColor.green > 0.5 && detectedColor.blue < 0.2) {
    currentColor = apesofwrath::Colors::YELLOW;
    frc::SmartDashboard::PutString("Color", "Yellow");
  } else if (detectedColor.red > 0.4) {
    currentColor = apesofwrath::Colors::RED;
    frc::SmartDashboard::PutString("Color", "Red");
  } else if (detectedColor.green > 0.5 && detectedColor.blue < 0.3 && detectedColor.red < 0.2 && detectedColor.blue < 0.3) {
    currentColor = apesofwrath::Colors::GREEN;
    frc::SmartDashboard::PutString("Color", "Green");
  } else if (detectedColor.blue > 0.4 && detectedColor.red < 0.2 && detectedColor.green > 0.4) {
    frc::SmartDashboard::PutString("Color", "Blue");
    currentColor = apesofwrath::Colors::BLUE;
  } else {
    currentColor = apesofwrath::Colors::WHITE;
    frc::SmartDashboard::PutString("Color", "None");
  }

  frc::SmartDashboard::PutData("Desired Color", &m_descolor_chooser);


  desiredColor = m_descolor_chooser.GetSelected();
  std::cout << "Desired Color: " << getColor(desiredColor) << std::endl;
  
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
void apesofwrath::Robot::AutonomousInit() {
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

void apesofwrath::Robot::AutonomousPeriodic() {
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}
void apesofwrath::Robot::TeleopInit() {
}

void apesofwrath::Robot::TeleopPeriodic() {
  
  if (currentColor == desiredColor || desiredColor == apesofwrath::Colors::WHITE) {
    talon0->Set(ControlMode::PercentOutput, 0);
  } else {
    talon0->Set(ControlMode::PercentOutput, CONTROL_WHEEL_SPEED_ON * joy->GetThrottle());
  }

  if (joy->GetTrigger()) {
    talon0->Set(ControlMode::PercentOutput, CONTROL_WHEEL_SPEED_ON * joy->GetThrottle());
  } else {
    talon0->Set(ControlMode::PercentOutput, CONTROL_WHEEL_SPEED_OFF);
  }
  
  

  // if (detectedColor.red >= 50)
  // {
  //   talon0->Set(ControlMode::PercentOutput, CONTROL_WHEEL_SPEED_ON);
  // } else {
  //   talon0->Set(ControlMode::PercentOutput, CONTROL_WHEEL_SPEED_OFF);
  // }
}

void apesofwrath::Robot::TestPeriodic() {}

std::string apesofwrath::Robot::getColor(apesofwrath::Colors c) {
  switch (c) {
    case apesofwrath::Colors::RED:
      return "Red";
    case apesofwrath::Colors::YELLOW:
      return "Yellow";
    case apesofwrath::Colors::BLUE:
      return "Blue";
    case apesofwrath::Colors::GREEN:
      return "Green";
    case apesofwrath::Colors::WHITE:
      return "None";
    default:
      return "None";
  }
}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<apesofwrath::Robot>(); }
#endif
