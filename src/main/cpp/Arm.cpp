/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Arm.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>
#include <math.h>

double kP = 0.8, kI = 0, kD = 0.0, kIz = 0, kFF = 0, kMaxOutput = 0.015, kMinOutput = -0.015;


Arm::Arm() {

//  talonArm = new TalonSRX(1); uh maybe talon for intake not arm?
  armSparkM0 = new rev::CANSparkMax(1, rev::CANSparkMax::MotorType::kBrushless);
  armEncoder = new rev::CANEncoder(armSparkM0->GetEncoder());
  armPID = new rev::CANPIDController(armSparkM0->GetPIDController());
  // rev::CANSparkMax armSpark0{1, rev::CANSparkMax::MotorType::kBrushless};
  armSparkM0->RestoreFactoryDefaults();
  armStartPos = armEncoder->GetPosition();
  joy = new frc::Joystick(0);

  armPID->SetP(kP);
  armPID->SetI(kI);
  armPID->SetD(kD);
  armPID->SetIZone(kIz);
  armPID->SetFF(kFF);
  armPID->SetOutputRange(kMinOutput, kMaxOutput);

  // display PID coefficients on SmartDashboard
  frc::SmartDashboard::PutNumber("P Gain", kP);
  frc::SmartDashboard::PutNumber("I Gain", kI);
  frc::SmartDashboard::PutNumber("D Gain", kD);
  frc::SmartDashboard::PutNumber("I Zone", kIz);
  frc::SmartDashboard::PutNumber("Feed Forward", kFF);
  frc::SmartDashboard::PutNumber("Max Output", kMaxOutput);
  frc::SmartDashboard::PutNumber("Min Output", kMinOutput);
  frc::SmartDashboard::PutNumber("Set Rotations", 0);
  armPID->SetSmartMotionAccelStrategy(rev::CANPIDController::AccelStrategy::kSCurve);


}

void Arm::Up() {

  // talonArm->Set(ControlMode::PercentOutput, 0.3);
  // armSparkM0->Set(0.1);
  // if(armCurrPos >= armStartPos){

  //   // if(armCurrPos <= armStartPos + 0.2){
  //     armSparkM0->Set(-0.025);
  //   // } else { 
  //   //   armSparkM0->Set(0);
  //   // }

  // } else {
  //   armSparkM0->Set(0);
  // }
  armPID->SetReference(armStartPos, rev::ControlType::kPosition);
  
}

void Arm::Down() {

  // talonArm->Set(ControlMode::PercentOutput, -0.3);
  // armSparkM0->Set(-0.1);
  // if(armStartPos + 0.25 >= armCurrPos){
    
  //   if(armCurrPos >= armStartPos - .0625){
  //     armSparkM0->Set(0.025);
  //   } else {
  //    armSparkM0->Set(0);
  //   }

  // } else {
  //   armSparkM0 ->Set(0);
  // }
  armPID->SetReference(armStartPos+.25, rev::ControlType::kPosition);

}

void Arm::Rest() {

  // talonArm->Set(ControlMode::PercentOutput, 0.0);
  armSparkM0->Set(0);
}

void Arm::IntakeArmStateMachine(bool up, bool down, bool rest) {
  armCurrPos = armEncoder->GetPosition();

  frc::SmartDashboard::PutNumber("INTAKE ARM STATE", intake_arm_state);
  frc::SmartDashboard::PutNumber("Rotation", armEncoder->GetPosition()); //in rot'n
  frc::SmartDashboard::PutNumber("start", armStartPos);
  // frc::SmartDashboard::PutNumber("Degrees", modf(armEncoder->GetPosition(), nullptr) * 360);// in degrees
  
  double p = frc::SmartDashboard::GetNumber("P Gain", 0);
  double i = frc::SmartDashboard::GetNumber("I Gain", 0);
  double d = frc::SmartDashboard::GetNumber("D Gain", 0);
  double iz = frc::SmartDashboard::GetNumber("I Zone", 0);
  double ff = frc::SmartDashboard::GetNumber("Feed Forward", 0);
  double max = frc::SmartDashboard::GetNumber("Max Output", 0);
  double min = frc::SmartDashboard::GetNumber("Min Output", 0);
  double rotations = frc::SmartDashboard::GetNumber("Set Rotations", 0);

  // if PID coefficients on SmartDashboard have changed, write new values to controller
  if((p != kP)) { armPID->SetP(p); kP = p; }
  if((i != kI)) { armPID->SetI(i); kI = i; }
  if((d != kD)) { armPID->SetD(d); kD = d; }
  if((iz != kIz)) { armPID->SetIZone(iz); kIz = iz; }
  if((ff != kFF)) { armPID->SetFF(ff); kFF = ff; }
  if((max != kMaxOutput) || (min != kMinOutput)) { 
    armPID->SetOutputRange(min, max); 
    kMinOutput = min; kMaxOutput = max; 
  }


  if(rest){
    intake_arm_state = REST;
  } else if(up) {
    intake_arm_state = UP;
  } else if (down) {
    intake_arm_state = DOWN;
  }

  switch(intake_arm_state){

    case REST:
      if (last_intake_arm_state != REST) {
        Rest();
      }
      frc::SmartDashboard::PutString("INTAKE ARM", "rest");
    break;

    case UP:
      if (last_intake_arm_state != UP) {
        Up();
      }
      frc::SmartDashboard::PutString("INTAKE ARM", "up");
    break;

    case DOWN:
      if (last_intake_arm_state != DOWN) {
        Down();
      }
      frc::SmartDashboard::PutString("INTAKE ARM", "down");
    break;

  }

  last_intake_arm_state = intake_arm_state;

}

