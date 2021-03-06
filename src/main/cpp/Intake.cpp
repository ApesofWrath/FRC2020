/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Intake.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>

Intake::Intake() {

//  talonIntake = new TalonSRX(0);
intakeSparkM0 = new rev::CANSparkMax(22, rev::CANSparkMax::MotorType::kBrushless);

}

void Intake::Stop() {

  // talonIntake->Set(ControlMode::PercentOutput, 0.0);
  intakeSparkM0->Set(0);
}

void Intake::In() {

  // talonIntake->Set(ControlMode::PercentOutput, 0.3);
  intakeSparkM0->Set(0.30);

}

void Intake::Out() {

  // talonIntake->Set(ControlMode::PercentOutput, -0.3);
  intakeSparkM0->Set(-0.30);

}

void Intake::IntakeStateMachine(Arm *arm, bool stop, bool in, bool out) {

  if (stop) {
    intake_state = STOP_STATE;
    arm->intake_arm_state = Arm::States::UP_STATE;
  } else if(in) {
    intake_state = IN_STATE;
    arm->intake_arm_state = Arm::States::DOWN_STATE;
  } else if(out) {
    intake_state = OUT_STATE;  
  }
  
  arm->IntakeArmStateMachine();
  frc::SmartDashboard::PutNumber("INTAKE STATE", intake_state);

  switch(intake_state) {

    case STOP_STATE:
    Stop();
    frc::SmartDashboard::PutString("INTAKE", "stop");
    break;

    case IN_STATE:
    In();
    frc::SmartDashboard::PutString("INTAKE", "in");
    break;

    case OUT_STATE:
    Out();
    frc::SmartDashboard::PutString("INTAKE", "out");
    break;

  }

}


