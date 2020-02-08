#include "TeleopStateMachine.h"

using namespace frc;

TeleopStateMachine::TeleopStateMachine(/* args */)
{
    state = WAIT_FOR_BUTTON;
    last_state = WAIT_FOR_BUTTON;
}

TeleopStateMachine::~TeleopStateMachine()
{
}

ButtonData TeleopStateMachine::GatherButtonDataFromJoysticks(Joystick* joyThrottle, Joystick* joyWheel, Joystick* joyOp) {
    return ButtonData {
        joyOp->GetRawButton(ButtonIDs::WAIT_FOR_BUTTON),
        joyOp->GetRawButton(ButtonIDs::LOWER_INTAKE_BUTTON),
        joyOp->GetRawButton(ButtonIDs::RAISE_INTAKE_BUTTON),
        joyOp->GetRawButton(ButtonIDs::RUN_INTAKE_BUTTON),
        joyOp->GetRawButton(ButtonIDs::STOP_INTAKE_BUTTON),
        joyOp->GetRawButton(ButtonIDs::STOP_CONTROL_PANEL_BUTTON),
        joyOp->GetRawButton(ButtonIDs::MANUAL_CONTROL_PANEL_BUTTON),
        joyOp->GetRawButton(ButtonIDs::ROTATION_MODE_CONTROL_PANEL_BUTTON),
        joyOp->GetRawButton(ButtonIDs::POSITION_MODE_CONTROL_PANEL_BUTTON),
        joyOp->GetRawButton(ButtonIDs::SHOOTER_SHOOT_BUTTON),
        joyOp->GetRawButton(ButtonIDs::SHOOTER_STOP_BUTTON),
        joyOp->GetRawButton(ButtonIDs::SHOOTER_INTAKE_BUTTON)
    };
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

    SmartDashboard::PutString("State", TeleopStateMachine::StateName(state));

    last_state = state;

}

std::string TeleopStateMachine::StateName(TeleopStateMachine::States state) {
    switch (state) {
        case WAIT_FOR_BUTTON:
            return "Robot::Wait For Button";
        case LOWER_INTAKE:
            return "Intake::Lower";
        case RAISE_INTAKE:
            return "Intake::Raise";
        case RUN_INTAKE:
            return "Intake::Run";
        case IDLE_INTAKE:
            return "Intake::Idle";
        case IDLE_CONTROL_PANEL:
            return "Control Panel::Idle";
        case ROTATION_MODE_CONTROL_PANEL:
            return "Control Panel::Rotation Mode";
        case POSITION_MODE_CONTROL_PANEL:
            return "Control Panel::Position Mode";
        case MANUAL_CONTROL_PANEL:
            return "Control Panel::Manual Mode";
        case SHOOTER_SHOOT:
            return "Shooter::Shoot";
        case SHOOTER_INTAKE:
            return "Shooter::Intake";
        case SHOOTER_IDLE:
            return "Shooter::Idle";
        default:
            return "Robot::Null State";
    }
}