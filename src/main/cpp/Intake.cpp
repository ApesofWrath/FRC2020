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
intakeSparkM0 = new rev::CANSparkMax(2, rev::CANSparkMax::MotorType::kBrushless);

}

void Intake::Stop() {

  // talonIntake->Set(ControlMode::PercentOutput, 0.0);

}

void Intake::In() {

  // talonIntake->Set(ControlMode::PercentOutput, 0.3);

}

void Intake::Out() {

  // talonIntake->Set(ControlMode::PercentOutput, -0.3);

}

void Intake::IntakeStateMachine(bool stop, bool in, bool out) {

  if (stop) {
    intake_state = STOP;
  } else if(in) {
    intake_state = IN;
  } else if(out) {
    intake_state = OUT;  
  }
  
  frc::SmartDashboard::PutNumber("INTAKE STATE", intake_state);

  switch(intake_state) {

    case STOP:
    Stop();
    frc::SmartDashboard::PutString("INTAKE", "stop");
    intakeSparkM0->Set(0);
    break;

    case IN:
    In();
    frc::SmartDashboard::PutString("INTAKE", "in");
    intakeSparkM0->Set(0.5);
    break;

    case OUT:
    Out();
    frc::SmartDashboard::PutString("INTAKE", "out");
    intakeSparkM0->Set(-0.5);
    break;

  }

}


