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
  rev::CANAnalog *analog;
  rev::CANSparkMax *armSparkM0;
  rev::CANSparkMax *armSparkM1;

  frc::Joystick* joy;

  float armStartPos;
  float armCurrPos;

  enum States {
    REST_STATE, UP_STATE, DOWN_STATE
  };

  States intake_arm_state = REST_STATE, last_intake_arm_state = REST_STATE;

    Arm();

    void Up();
    void Down();
    void Rest();

    void IntakeArmStateMachine(bool up, bool down, bool rest);

    void UpperSoftLimit();
    void LowerSoftLimit();


};

#endif
