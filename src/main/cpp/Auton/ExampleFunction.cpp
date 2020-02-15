#include "Auton/ExampleFunction.h"

#include <frc/smartdashboard/SmartDashboard.h>

void ExampleFunction::Run() {
    dir = -dir;
    talonL->Set(ControlMode::PercentOutput, dir);
    talonR->Set(ControlMode::PercentOutput, -dir);
    
    frc::SmartDashboard::PutString("running", "si");
}

ExampleFunction::~ExampleFunction() {

}

//ExampleFunction::ExampleFunction(TalonFX* testTalon, int seconds_run) {

//}

void ExampleFunction::UpdateTask() {
    frc::SmartDashboard::PutNumber("time", TimeSinceTaskStarted());
    if (HasTaskStarted() && TimeSinceTaskStarted() >= seconds_to_run_for) {
        CompleteTask();
    } else if (TimeSinceTaskStarted() >= 2 * seconds_to_run_for) {
        BeginTask();
    }
}

void ExampleFunction::KillTask() {
    CompleteTask();
}

void ExampleFunction::OnCompleteTask() {
    talonL->Set(ControlMode::PercentOutput,0);
    talonR->Set(ControlMode::PercentOutput,0);
    frc::SmartDashboard::PutString("running", "no");
}