// #ifndef SRC_INTAKE_H_
// #define SRC_INTAKE_H_

#include <ctre/Phoenix.h>
#include <frc/WPILib.h>
// #include "Robot.h"
#include "rev/CANSparkMax.h"
#include "Arm.h"

class Intake {
public:

  // TalonSRX *talonIntake;
  rev::CANSparkMax *intakeSparkM0;


  enum States {
    STOP_STATE, IN_STATE, OUT_STATE 
  };

  States intake_state = STOP_STATE;

    Intake();

    void Stop();
    void In();
    void Out();

    void IntakeStateMachine(Arm *arm, bool stop, bool in, bool out);



};

// #endif
