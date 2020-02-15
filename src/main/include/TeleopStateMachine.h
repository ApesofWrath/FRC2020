#pragma once

#include <Intake.h>
#include <Arm.h>
#include <Shooter.h>
#include <ControlPanel.h>

#include <frc/Joystick.h>

#include <frc/smartdashboard/SmartDashboard.h>

#include <string>

using namespace frc;

namespace ButtonIDs {
    const int WAIT_FOR_BUTTON = 0,
              LOWER_INTAKE_BUTTON = 1,
              RAISE_INTAKE_BUTTON = 2,
              INTAKE_BUTTON = 3,
              MANUAL_CONTROL_PANEL_BUTTON = 4,
              ROTATION_MODE_CONTROL_PANEL_BUTTON = 5,
              POSITION_MODE_CONTROL_PANEL_BUTTON = 6,
              SHOOT_BUTTON = 7;

}


struct ButtonData {
    bool wait_for_button, lower_intake_button,
    raise_intake_button, intake_button,
    manual_control_panel_button, rotation_mode_control_panel_button, position_mode_control_panel_button,
    shoot_button;
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
        INTAKE_STATE,
        ROTATION_MODE_CONTROL_PANEL, POSITION_MODE_CONTROL_PANEL,
        SHOOT_STATE
    };

    static std::string StateName(States state);

    States state;
    States last_state;

    Intake *intake;
    Arm *arm;
    Shooter *shooter;
    ControlPanel *control_panel;
};
