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

  joy = new frc::Joystick(0);
  talon1 = new TalonSRX(36);

  neo_1 = new rev::CANSparkMax(1, rev::CANSparkMax::MotorType::kBrushless);
  neo_2 = new rev::CANSparkMax(2, rev::CANSparkMax::MotorType::kBrushless);
  neo_3 = new rev::CANSparkMax(3, rev::CANSparkMax::MotorType::kBrushless);
  neo_4 = new rev::CANSparkMax(4, rev::CANSparkMax::MotorType::kBrushless);


  arm = new Arm();
  intake = new Intake();
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
  // if (joy->GetRawButton(4)){
  //   neo_1->Set(joy->GetThrottle());
  // }
  // if (joy->GetRawButton(3)){
  //   neo_1->Set(-joy->GetThrottle());
  // }
  // if (joy->GetRawButton(8)){
  //   neo_1->Set(joy->GetThrottle() - (joy->GetThrottle() / 10.0f));
  //   neo_2->Set(joy->GetThrottle());
  //   neo_3->Set(-joy->GetThrottle()/ 0.75f);
  //   neo_4->Set(joy->GetThrottle());
  // }
  // if (joy->GetRawButton(7)){
  //   neo_1->Set(joy->GetThrottle());
  //   neo_2->Set(-joy->GetThrottle());
  //   neo_3->Set(joy->GetThrottle());
  //   neo_4->Set(joy->GetThrottle());
  // }
  // if (joy->GetRawButton(2)) {
  //   neo_2->Set(0.25);
  // }

  // if (joy->GetRawButton(10)){
  //   neo_3->Set(joy->GetThrottle());
  // }
  // if (joy->GetRawButton(9)){
  //   neo_3->Set(-joy->GetThrottle());
  // }
  // if (joy->GetRawButton(12)){
  //   neo_4->Set(joy->GetThrottle());
  // }
  // if (joy->GetRawButton(11)){
  //   neo_4->Set(-joy->GetThrottle());
  // }

  // if (joy->GetRawButton(5)) {
  //   neo_1->Set(-joy->GetThrottle());
  //   neo_2->Set(-joy->GetThrottle());
  //   neo_3->Set(-joy->GetThrottle());
  //   neo_4->Set(-joy->GetThrottle());
  // }
  // if (joy->GetRawButton(6)) {
  //   neo_1->Set(joy->GetThrottle());
  //   neo_2->Set(joy->GetThrottle());
  //   neo_3->Set(joy->GetThrottle());
  //   neo_4->Set(joy->GetThrottle());
  // }
  // if (joy->GetRawButton(1)) {
  //   neo_1->Set(0.0f);
  //   neo_2->Set(0.0f);
  //   neo_3->Set(0.0f);
  //   neo_4->Set(0.0f);
  // }

  if (joy->GetRawButton(1)) {
    neo_1->Set(0.8f); // Conveyor
    neo_2->Set(0.5f); // Bottom Outtake
    neo_3->Set(1.0f); // Top Outtake
  } else {
    neo_1->Set(0.0f); // Conveyor 
    neo_2->Set(0.0f); // Bottom Outtake
    neo_3->Set(0.0f); // Top Outtake
  }

  UpdateButtons();

  intake->IntakeStateMachine(arm, stop, in, out);

  frc::SmartDashboard::PutNumber("Speed", joy->GetThrottle());

}

void apesofwrath::Robot::UpdateButtons(){

  // rest = joy->GetRawButton(9);
  // down = joy->GetRawButton(8);
  // up = joy->GetRawButton(7);
  
  stop = joy->GetRawButton(7);
  in = joy->GetRawButton(8);
  out = joy->GetRawButton(9);

}

void apesofwrath::Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<apesofwrath::Robot>(); }
#endif
