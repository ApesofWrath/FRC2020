 /*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <iostream>


#include <frc/smartdashboard/SmartDashboard.h>


constexpr double kRamseteB = 2;
constexpr double kRamseteZeta = 0.7;




void Robot::RobotInit() {
  std::cout << "dc\n";
  drive = new DriveController();

  std::cout << "robo_init\n";
  a_drive = new AutonDrive(10,12,11,13, drive->ahrs);
  m_container = new RobotContainer(a_drive);

  m_container->InitAutoChoices();
  std::cout << "sd:pd am\n";
  frc::SmartDashboard::PutData("Auto Modes", &(m_container->m_chooser));

  m_descolor_chooser.AddDefault("None",  Colors::WHITE);
  m_descolor_chooser.AddObject("Red",    Colors::RED);
  m_descolor_chooser.AddObject("Blue",   Colors::BLUE);
  m_descolor_chooser.AddObject("Green",  Colors::GREEN);
  m_descolor_chooser.AddObject("Yellow", Colors::YELLOW);

  frc::SmartDashboard::PutData("Desired Color", &m_descolor_chooser);


  std::cout << "joys\n";
  joyT = new frc::Joystick(0);
  joyW = new frc::Joystick(1);

  std::cout << "cp\n";
  controlpanel = new ControlPanel();
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
  // std::cout << "rp\n";
  frc2::CommandScheduler::GetInstance().Run();
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
  std::cout << "as get\n";
  m_container->m_autoSelected = m_container->m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  std::cout << "Auto selected: " << m_container->m_autoSelected << std::endl;

  m_autonomousCommand = m_container->GetAutonomousCommand();
  std::cout << "ac gotten\n";

  if (m_autonomousCommand != nullptr) {
    m_autonomousCommand->Schedule();
    std::cout << "ac schedule\n";
  }


  // a_drive->ResetOdometry();
}

void Robot::AutonomousPeriodic() {
  // if (m_container->m_autoSelected == kAutoNameCustom) {
  //   // Custom Auto goes here
  // } else {
  //   // Default Auto goes here
  // }

  a_drive->Update();
}
void Robot::TeleopInit() {
  frc2::CommandScheduler::GetInstance().Disable();
  if (m_autonomousCommand != nullptr) {
    m_autonomousCommand->Cancel();
    m_autonomousCommand = nullptr;
  }
}
// bool toggle = false;
void Robot::TeleopPeriodic() {
  
  
  // frc::SmartDashboard::PutData("Desired Color", &m_descolor_chooser);

  // controlpanel->DesireColor(m_descolor_chooser.GetSelected());
  


  // if (joyT->GetRawButton(BUTTON_STOP)) {
  //   controlpanel->Stop();
  // }
  // if (joyT->GetRawButton(POSITION_BUTTON)) {
  //   controlpanel->PositionMode();
  // }
  // if (joyT->GetRawButton(ROTATION_BUTTON)) {
  //   controlpanel->RotationMode();
  // }

  frc::SmartDashboard::PutNumber("speed", joyT->GetThrottle());

  // if (joyT->GetRawButton(1)) {
  //   Falcon_T->Set(ControlMode::PercentOutput, joyT->GetThrottle());
  //   Falcon_T2->Set(ControlMode::PercentOutput, joyT->GetThrottle());
  // } else {
  //   Falcon_T->Set(ControlMode::PercentOutput, 0);
  //   Falcon_T2->Set(ControlMode::PercentOutput, 0);
  // }

  drive->RunTeleopDrive(joyT, joyW, true, false, false);

  // drive->ManualOpenLoopDrive(joyT, joyW);
  // drive->TeleopWCDrive(joyT,joyW,false,false);

  // T46->Set(ControlMode::PercentOutput, 1.0f);

  // if (joyT->GetRawButton(1)) {

  // } else {
  //   T46->Set(ControlMode::PercentOutput, 0.0f);
  // }
  // controlpanel->StateMachine();

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
