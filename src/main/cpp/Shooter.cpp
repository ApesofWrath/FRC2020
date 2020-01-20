#include <Shooter.h>

    const int INIT_STATE = 0;
    const int INTAKE_STATE = 1;
    const int STOP_STATE = 2;
    const int SHOOT_STATE = 3;
    const int WAITING_STATE = 4;

    // bool shoot = false;
    // bool stop = false;
    // bool intake = false;

    Shooter::Shooter() {
        shooter_state = INIT_STATE;

        canTalonBelt = new TalonSRX(TALON_ID_0);
        canTalonTopW = new TalonSRX(TALON_ID_1);
        canTalonBottomW = new TalonSRX(TALON_ID_2);

        joy = new frc::Joystick(0);
    }

    void Shooter::ShooterStateMachine(bool shoot, bool intake, bool stop, bool waiting){
            
            speed = (-(joy->GetRawAxis(3)) + 1)/2;
            frc::SmartDashboard::PutNumber("Speed", speed);

            if(stop){
                shooter_state = STOP_STATE;
            }

            if(shoot){
                shooter_state = SHOOT_STATE;
            }

            if(intake){
                shooter_state = INTAKE_STATE;
            }
            
            if(waiting){
                shooter_state = WAITING_STATE;
            }
            
            switch(shooter_state) {
                case INIT_STATE:
                frc::SmartDashboard::PutString("Shooter ", "init");
                shooter_state = STOP_STATE;
                break;
                case INTAKE_STATE:
                frc::SmartDashboard::PutString("Shooter ", "intake");
                Intake();
                last_shooter_state = INTAKE_STATE;
                break;
                
                case STOP_STATE:
                frc::SmartDashboard::PutString("Shooter ", "stop");
                Stop();
                last_shooter_state = STOP_STATE;
                break;
                
                case SHOOT_STATE:
                frc::SmartDashboard::PutString("Shooter ", "shoot");
                Shoot();
                last_shooter_state = SHOOT_STATE;
                break;

                case WAITING_STATE:
                frc::SmartDashboard::PutString("Shooter ", "waiting");
                Waiting();
                last_shooter_state = WAITING_STATE;
                break;
            }

    }

    void Shooter::Shoot(){
        canTalonBelt->Set(ControlMode::PercentOutput, 1*speed);
        canTalonTopW->Set(ControlMode::PercentOutput, -1*speed);
        canTalonBottomW->Set(ControlMode::PercentOutput, -1*speed);
    }

    void Shooter::Intake(){                
        canTalonBelt->Set(ControlMode::PercentOutput, .20);
        canTalonTopW->Set(ControlMode::PercentOutput, .50);
        canTalonBottomW->Set(ControlMode::PercentOutput, 0);
    }

    void Shooter::Stop(){
        canTalonBelt->Set(ControlMode::PercentOutput, 0);
        canTalonTopW->Set(ControlMode::PercentOutput, 0);
        canTalonBottomW->Set(ControlMode::PercentOutput, 0);
    }

    void Shooter::Waiting(){
        canTalonBelt->Set(ControlMode::PercentOutput, .5);
        canTalonTopW->Set(ControlMode::PercentOutput, 1*speed);
        canTalonBottomW->Set(ControlMode::PercentOutput, 1*speed);
    }