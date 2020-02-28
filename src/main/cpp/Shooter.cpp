#include <Shooter.h>

    const int INIT_STATE = 0;
    const int INTAKE_STATE = 1;
    const int STOP_STATE = 2;
    const int SHOOT_STATE = 3;
    const int WAITING_STATE = 4;
    const int REVERSE_STATE = 5;

    Shooter::Shooter() {
        shooter_state = INIT_STATE;

        // beltNEO = new TalonSRX(TALON_ID_0); //1 labeled on talon
        // topWNEO = new TalonSRX(TALON_ID_1); //2 labeled on talon
        // botWNEO = new TalonSRX(TALON_ID_2); //3 labeled on talon
// *beltNEO, topWNEO, *botWNEO;
            beltNEO = new rev::CANSparkMax(1, rev::CANSparkMax::MotorType::kBrushless);
            topWNEO = new rev::CANSparkMax(2, rev::CANSparkMax::MotorType::kBrushless);
            botWNEO = new rev::CANSparkMax(3, rev::CANSparkMax::MotorType::kBrushless);
        joy = new frc::Joystick(0);
    }

    void Shooter::ShooterStateMachine(){
            
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
                case REVERSE_STATE:
                frc::SmartDashboard::PutString("Shooter ", "reverse");
                Reverse();
                last_shooter_state = REVERSE_STATE_H;
                break;
            }

    }

    void Shooter::Shoot(){
        beltNEO->Set(1);
        topWNEO->Set(1);
        botWNEO->Set(1);
    }

    void Shooter::Intake(){                
        beltNEO->Set(0.2);
        topWNEO->Set(0);
        botWNEO->Set(0);
    }

    void Shooter::Stop(){
        beltNEO->Set(0);
        topWNEO->Set(0);
        botWNEO->Set(0);
    }

    void Shooter::Waiting(){
        beltNEO->Set(0);
        topWNEO->Set(0);
        botWNEO->Set(0);
    }

    void Shooter::Reverse() {  
        beltNEO->Set(-0.2);
        topWNEO->Set(0);
        botWNEO->Set(0);
    }