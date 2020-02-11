// #ifndef SRC_INTAKE_H_
// #define SRC_INTAKE_H_

#include <ctre/Phoenix.h>
#include <frc/WPILib.h>
// #include "Robot.h"
#include "rev/CANSparkMax.h"

class Intake {
public:

  TalonSRX *talonIntake;


  enum States {
    STOP, IN, OUT
  };

  States intake_state = STOP;

    Intake();

    void Stop();
    void In();
    void Out();

    void IntakeStateMachine();



};

// #endif
