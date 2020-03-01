#pragma once

#include <string>

//#include <frc/WPILib.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <ctre/Phoenix.h>
#include <frc/Joystick.h>
#include "rev/CANSparkMax.h"

class Shooter {
    public:

    const int TALON_ID_0 = 1;
    const int TALON_ID_1 = 2;
    const int TALON_ID_2 = 3;

    const int INIT_STATE_H = 0;
    const int INTAKE_STATE_H = 1;
    const int STOP_STATE_H = 2;
    const int SHOOT_STATE_H = 3;
    const int WAITING_STATE_H = 4;
    const int REVERSE_STATE_H = 5;
    
    int last_shooter_state = INIT_STATE_H;
    int shooter_state = INIT_STATE_H;

    float speed = 0;
    float beltPOS;

    // TalonSRX *canTalonBelt, *canTalonTopW, *canTalonBottomW;
    rev::CANSparkMax *beltNEO, *topWNEO, *botWNEO;
    rev::CANPIDController *beltPID, *topWPID, *botWPID;
    rev::CANEncoder *beltEncoder, *topWEncoder, *botWEncoder;
    frc::Joystick* joy;

    Shooter();
    void Shoot();
    void Intake();
    void Stop();
    void Waiting();
    void Reverse();

    void ShooterStateMachine();
};

