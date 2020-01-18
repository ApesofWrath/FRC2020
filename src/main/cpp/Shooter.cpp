#include <Shooter.h>

    const int INIT_STATE = 0;
    const int INTAKE_STATE = 1;
    const int STOP_STATE = 2;
    const int SHOOT_STATE = 3;

    // bool shoot = false;
    // bool stop = false;
    // bool intake = false;

    Shooter::Shooter() {
        shooter_state = INIT_STATE;

        canTalonBelt = new TalonSRX(TALON_ID_0);
        canTalonTopW = new TalonSRX(TALON_ID_1);
        canTalonBottomW = new TalonSRX(TALON_ID_2);
    }

    void Shooter::ShooterStateMachine(bool shoot, bool intake, bool stop){
            
            if(shoot){
                shooter_state = SHOOT_STATE;
            }

            if(intake){
                shooter_state = INTAKE_STATE;
            }
            
            if(stop){
                shooter_state = STOP_STATE;
            }
            switch(shooter_state) {
                case INIT_STATE:
                frc::SmartDashboard::PutString("Shooter ", "init");
                shooter_state = STOP_STATE;
                break;
                case INTAKE_STATE:
                frc::SmartDashboard::PutString("Shooter ", "intake");
                canTalonBelt->Set(ControlMode::PercentOutput, .20);
                canTalonTopW->Set(ControlMode::PercentOutput, -.10);
                canTalonBottomW->Set(ControlMode::PercentOutput, -.10);
                last_shooter_state = INTAKE_STATE;
                break;
                case STOP_STATE:
                frc::SmartDashboard::PutString("Shooter ", "stop");
                canTalonBelt->Set(ControlMode::PercentOutput, 0);
                canTalonTopW->Set(ControlMode::PercentOutput, 0);
                canTalonBottomW->Set(ControlMode::PercentOutput, 0);   
                last_shooter_state = STOP_STATE;
                break;
                case SHOOT_STATE:
                frc::SmartDashboard::PutString("Shooter ", "shoot");
                canTalonBelt->Set(ControlMode::PercentOutput, .4);
                canTalonTopW->Set(ControlMode::PercentOutput, .4);
                canTalonBottomW->Set(ControlMode::PercentOutput, .4);
                last_shooter_state = SHOOT_STATE;
                break;
            }

    }   