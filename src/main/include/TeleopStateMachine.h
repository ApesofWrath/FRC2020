#pragma once

#include <frc/Joystick.h>

#include <frc/smartdashboard/SmartDashboard.h>

#include <string>

using namespace frc;

namespace ButtonIDs {
    const int WAIT_FOR_BUTTON = 0,
              LOWER_INTAKE_BUTTON = 1,
              RAISE_INTAKE_BUTTON = 2,
              RUN_INTAKE_BUTTON = 3,
              STOP_INTAKE_BUTTON = 4,
              STOP_CONTROL_PANEL_BUTTON = 5,
              MANUAL_CONTROL_PANEL_BUTTON = 6,
              ROTATION_MODE_CONTROL_PANEL_BUTTON = 7,
              POSITION_MODE_CONTROL_PANEL_BUTTON = 8,
              SHOOTER_SHOOT_BUTTON = 9,
              SHOOTER_STOP_BUTTON = 10,
              SHOOTER_INTAKE_BUTTON = 11;
}


struct ButtonData {
    bool wait_for_button, lower_intake_button,
    raise_intake_button, run_intake_button,
    stop_intake_button, stop_control_panel_button, 
    manual_control_panel_button, rotation_mode_control_panel_button, position_mode_control_panel_button, 
    shooter_shoot_button, shooter_stop_button, 
    shooter_intake_button;
};

class TeleopStateMachine
{
private:
    /* data */
public:
    TeleopStateMachine(/* args */);
    ~TeleopStateMachine();

    void StateMachine(ButtonData data);
    void ProcessButtonData(ButtonData data);

    ButtonData GatherButtonDataFromJoysticks(Joystick* joyThrottle, Joystick* joyWheel, Joystick* joyOp);

    enum States {
        WAIT_FOR_BUTTON,
        LOWER_INTAKE, RAISE_INTAKE, RUN_INTAKE, IDLE_INTAKE,
        IDLE_CONTROL_PANEL, ROTATION_MODE_CONTROL_PANEL, POSITION_MODE_CONTROL_PANEL, MANUAL_CONTROL_PANEL,
        SHOOTER_SHOOT, SHOOTER_INTAKE, SHOOTER_IDLE
    };

    static std::string StateName(States state);

    States state;
    States last_state;
};