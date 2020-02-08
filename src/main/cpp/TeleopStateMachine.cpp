#include "TeleopStateMachine.h"

TeleopStateMachine::TeleopStateMachine(/* args */)
{
}

TeleopStateMachine::~TeleopStateMachine()
{
}

void TeleopStateMachine::ProcessButtonData(ButtonData data) {
    if (data.wait_for_button) {
        state = WAIT_FOR_BUTTON;
    } else if (data.stop_intake_button) {
        state = IDLE_INTAKE;
    } else if (data.stop_control_panel_button) {
        state = IDLE_CONTROL_PANEL;
    } else if (data.shooter_stop_button) {
        state = SHOOTER_IDLE;
    } else if (data.shooter_shoot_button) {
        state = SHOOTER_SHOOT;
    } else if (data.shooter_intake_button) {
        state = SHOOTER_INTAKE;
    } else if (data.run_intake_button) {
        state = RUN_INTAKE;
    } else if (data.rotation_mode_control_panel_button) {
        state = ROTATION_MODE_CONTROL_PANEL;
    } else if (data.raise_intake_button) {
        state = RAISE_INTAKE;
    } else if (data.position_mode_control_panel_button) {
        state = POSITION_MODE_CONTROL_PANEL;
    } else if (data.manual_control_panel_button) {
        state = MANUAL_CONTROL_PANEL;
    } else if (data.lower_intake_button) {
        state = LOWER_INTAKE;
    }
}

void TeleopStateMachine::StateMachine(ButtonData data) {
    ProcessButtonData(data);

    switch (state) {
        case WAIT_FOR_BUTTON:
            break;
        case LOWER_INTAKE:
            break;
        case RAISE_INTAKE:
            break;
        case RUN_INTAKE:
            break;
        case IDLE_INTAKE:
            break;
        case IDLE_CONTROL_PANEL:
            break;
        case ROTATION_MODE_CONTROL_PANEL:
            break;
        case POSITION_MODE_CONTROL_PANEL:
            break;
        case MANUAL_CONTROL_PANEL:
            break;
        case SHOOTER_SHOOT:
            break;
        case SHOOTER_INTAKE:
            break;
        case SHOOTER_IDLE:
            break;
    }

    last_state = state;

}