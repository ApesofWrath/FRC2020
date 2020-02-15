#ifndef SRC_ARM_H_
#define SRC_ARM_H_

#include <ctre/Phoenix.h>
// #include <frc/WPILib.h>
#include "rev/CANSparkMax.h"
#include <frc/Joystick.h>

class Arm {
public:

  // TalonSRX *talonArm;
  rev::CANEncoder *armEncoder;
  rev::CANPIDController *armPID;
  rev::CANSparkMax *armSparkM0;
  frc::Joystick* joy;

  float armStartPos;
  float armCurrPos;

  enum States {
    REST, UP, DOWN
  };

  States intake_arm_state = REST, last_intake_arm_state = REST;

    Arm();

    void Up();
    void Down();
    void Rest();

    void IntakeArmStateMachine(bool up, bool down, bool rest);

    void UpperSoftLimit();
    void LowerSoftLimit();


};

#endif