#pragma once

#include "Intake.h"
#include "Arm.h"
#include "Shooter.h"
#include "ControlPanel.h"

#include <frc/Joystick.h>

#include <frc/smartdashboard/SmartDashboard.h>

#include <string>

using namespace frc;

namespace ButtonIDs {
    const int WAIT_FOR_BUTTON = 13,
              LOWER_INTAKE_BUTTON = 12,
              RAISE_INTAKE_BUTTON = 1,
              INTAKE_OUT_BUTTON = 6,
              SHOOT_BUTTON = 14,
              SHOOTER_INTAKE_BUTTON = 4,
              ROTATION_MODE_CONTROL_PANEL_BUTTON = 2,
              POSITION_MODE_CONTROL_PANEL_BUTTON = 15,
              EMERGENCY_BUTTON = 99;

}


struct ButtonData {
    bool wait_for_button, lower_intake_button,
    raise_intake_button, intake_out_button,
    shooter_intake_button, rotation_mode_control_panel_button, position_mode_control_panel_button,
    shoot_button, emergency_button;
};

class TeleopStateMachine
{
private:
    /* data */
public:
    TeleopStateMachine(Shooter* shooter_, Intake* intake_, ControlPanel* control_panel_, Arm* arm_);
    ~TeleopStateMachine();

    void StateMachine(ButtonData data);
    void ProcessButtonData(ButtonData data);

    ButtonData GatherButtonDataFromJoysticks(Joystick* joyThrottle, Joystick* joyWheel, Joystick* joyOp);

    enum States {
        INIT_STATE, WAIT_FOR_BUTTON_STATE,
        INTAKE_SHOOTER_STATE, INTAKE_STATE,
        SHOOT_STATE,
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
    Shooter *shooter;
    ControlPanel *control_panel;
};
