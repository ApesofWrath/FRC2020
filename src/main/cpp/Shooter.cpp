#include <Shooter.h>

    const int INIT_STATE = 0;
    const int INTAKE_STATE = 1;
    const int STOP_STATE = 2;
    const int SHOOT_STATE = 3;
    const int WAITING_STATE = 4;

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
        beltNEO->Set(1*speed);
        topWNEO->Set( -1*speed);
        botWNEO->Set( -1*speed);
    }

    void Shooter::Intake(){                
        beltNEO->Set( 0);
        topWNEO->Set( 1*speed);
        botWNEO->Set( -.5*speed);
    }

    void Shooter::Stop(){
        beltNEO->Set( 0);
        topWNEO->Set( 0);
        botWNEO->Set( 0);
    }

    void Shooter::Waiting(){
        beltNEO->Set( .5);
        topWNEO->Set( 1*speed);
        botWNEO->Set( 1*speed);
    }