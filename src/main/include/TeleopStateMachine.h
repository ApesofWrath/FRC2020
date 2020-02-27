#pragma once

#include "Intake.h"
#include "Arm.h"
// #include "Shooter.h"
#include "ControlPanel.h"

#include <frc/Joystick.h>

#include <frc/smartdashboard/SmartDashboard.h>

#include <string>

using namespace frc;

namespace ButtonIDs {
    const int WAIT_FOR_BUTTON = 0,
              LOWER_INTAKE_BUTTON = 13,
              RAISE_INTAKE_BUTTON = 2,
              INTAKE_OUT_BUTTON = 8,
              SHOOT_BUTTON = 3,
              SHOOTER_INTAKE_BUTTON = 16,
              SHOOTER_STOP_BUTTON = 9,
              ROTATION_MODE_CONTROL_PANEL_BUTTON = 4,
              POSITION_MODE_CONTROL_PANEL_BUTTON = 5,
              EMERGENCY_BUTTON = 12;

}


struct ButtonData {
    bool wait_for_button, lower_intake_button,
    raise_intake_button, intake_out_button,
    shooter_intake_button, rotation_mode_control_panel_button, position_mode_control_panel_button,
    shoot_button, shooter_stop_button, emergency_button;
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
        INIT_STATE, WAIT_FOR_BUTTON_STATE,
        INTAKE_STATE, POST_INTAKE_STATE,
        SHOOT_STATE, POST_SHOOT_STATE,
        ROTATION_MODE_CONTROL_PANEL_STATE, POSITION_MODE_CONTROL_PANEL_STATE,
    };

    static std::string StateName(States state);

    States state;
    States last_state;

    bool state_arm = false;
    bool state_intake = false;
    bool state_shooter = false;
    bool state_control_panel = false;


    Intake *intake;
    Arm *arm;
    // Shooter *shooter;
    ControlPanel *control_panel;
};
