/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Arm.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>

Arm::Arm() {

//  talonArm = new TalonSRX(1); uh maybe talon for intake not arm?
  armSparkM0 = new rev::CANSparkMax(1, rev::CANSparkMax::MotorType::kBrushless);
  // rev::CANSparkMax armSpark0{1, rev::CANSparkMax::MotorType::kBrushless};
  armSparkM0->RestoreFactoryDefaults();
  joy = new frc::Joystick(0);
}

void Arm::Up() {

  // talonArm->Set(ControlMode::PercentOutput, 0.3);

}

void Arm::Down() {

  // talonArm->Set(ControlMode::PercentOutput, -0.3);

}

void Arm::Rest() {

  // talonArm->Set(ControlMode::PercentOutput, 0.0);

}

void Arm::IntakeArmStateMachine(bool up, bool down, bool rest) {

  frc::SmartDashboard::PutString("INTAKE ARM STATE", "bruh");

  if(rest){
    intake_arm_state = REST;
  } else if(up) {
    intake_arm_state = UP;
  } else if (down) {
    intake_arm_state = DOWN;
  }

  switch(intake_arm_state){

    case REST:
    Rest();
    frc::SmartDashboard::PutString("INTAKE ARM", "rest");
    break;

    case UP:
    Up();
    frc::SmartDashboard::PutString("INTAKE ARM", "up");
    break;

    case DOWN:
    Down();
    frc::SmartDashboard::PutString("INTAKE ARM", "down");
    break;

  }

}


