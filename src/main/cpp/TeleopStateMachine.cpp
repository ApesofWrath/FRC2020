#include "TeleopStateMachine.h"

using namespace frc;

TeleopStateMachine::TeleopStateMachine(/* args */)
{
    state = WAIT_FOR_BUTTON;
    last_state = WAIT_FOR_BUTTON;
}

TeleopStateMachine::~TeleopStateMachine(){
}

ButtonData TeleopStateMachine::GatherButtonDataFromJoysticks(Joystick* joyThrottle, Joystick* joyWheel, Joystick* joyOp) {
    return ButtonData {
        joyOp->GetRawButton(ButtonIDs::WAIT_FOR_BUTTON),
        joyOp->GetRawButton(ButtonIDs::LOWER_INTAKE_BUTTON),
        joyOp->GetRawButton(ButtonIDs::RAISE_INTAKE_BUTTON),
        joyOp->GetRawButton(ButtonIDs::INTAKE_BUTTON),
        joyOp->GetRawButton(ButtonIDs::MANUAL_CONTROL_PANEL_BUTTON),
        joyOp->GetRawButton(ButtonIDs::ROTATION_MODE_CONTROL_PANEL_BUTTON),
        joyOp->GetRawButton(ButtonIDs::POSITION_MODE_CONTROL_PANEL_BUTTON),
     };
}

void TeleopStateMachine::ProcessButtonData(ButtonData data) {
    if (data.wait_for_button) {
        state = WAIT_FOR_BUTTON_STATE;
    } else if (data.intake_button) {
        state = INTAKE_STATE;
    } else if (data.shooter_shoot_button) {
        state = SHOOT_STATE;
    } else if (data.rotation_mode_control_panel_button) {
        state = ROTATION_MODE_CONTROL_PANEL;
    } else if (data.position_mode_control_panel_button) {
        state = POSITION_MODE_CONTROL_PANEL;
    }
}

void TeleopStateMachine::StateMachine(ButtonData data) {
    ProcessButtonData(data);

    switch (state) {
        case INIT_STATE:
          arm->intake_arm_state = arm->REST_STATE;
          intake->intake_state = intake->STOP_STATE;
          shooter->shooter_state = shooter->STOP_STATE;
          control_panel->control_panel_state = control_panel->IDLE;
        break;
        case WAIT_FOR_BUTTON_STATE:
        break;
        case INTAKE_STATE:
        break;
        case SHOOT_STATE:
        break;
        case ROTATION_MODE_CONTROL_PANEL_STATE:
        break;
        case POSITION_MODE_CONTROL_PANEL_STATE:
        break;
    }

    SmartDashboard::PutString("State", TeleopStateMachine::StateName(state));

    last_state = state;

}

std::string TeleopStateMachine::StateName(TeleopStateMachine::States state) {
    switch (state) {
        case INIT_STATE:
            return "Robot::Init";
        case WAIT_FOR_BUTTON_STATE:
            return "Robot::Wait For Button";
        case INTAKE_STATE:
            return "Intake::";
        case SHOOT_STATE:
            return "Shooter::Shoot";
        case ROTATION_MODE_CONTROL_PANEL:
            return "Control Panel::Rotation Mode";
        case POSITION_MODE_CONTROL_PANEL:
            return "Control Panel::Position Mode";
        default:
            return "Robot::Null State";
    }
}
