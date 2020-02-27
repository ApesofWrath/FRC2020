#include "TeleopStateMachine.h"

using namespace frc;

TeleopStateMachine::TeleopStateMachine(Shooter* shooter_, Intake* intake_, ControlPanel* control_panel_, Arm* arm_)
{
    state = WAIT_FOR_BUTTON_STATE;
    last_state = WAIT_FOR_BUTTON_STATE;

    arm = arm_;
    intake = intake_;
    control_panel = control_panel_;
    shooter = shooter_;

}

TeleopStateMachine::~TeleopStateMachine(){
}

ButtonData TeleopStateMachine::GatherButtonDataFromJoysticks(Joystick* joyThrottle, Joystick* joyWheel, Joystick* joyOp) {
    return ButtonData {
        joyOp->GetRawButton(ButtonIDs::WAIT_FOR_BUTTON),
        joyOp->GetRawButton(ButtonIDs::LOWER_INTAKE_BUTTON),
        joyOp->GetRawButton(ButtonIDs::RAISE_INTAKE_BUTTON),
        joyOp->GetRawButton(ButtonIDs::INTAKE_OUT_BUTTON),
        joyOp->GetRawButton(ButtonIDs::SHOOT_BUTTON),
        joyOp->GetRawButton(ButtonIDs::SHOOTER_INTAKE_BUTTON),
        joyOp->GetRawButton(ButtonIDs::ROTATION_MODE_CONTROL_PANEL_BUTTON),
        joyOp->GetRawButton(ButtonIDs::POSITION_MODE_CONTROL_PANEL_BUTTON),
        joyOp->GetRawButton(ButtonIDs::EMERGENCY_BUTTON)
     };
}

void TeleopStateMachine::ProcessButtonData(ButtonData data) {
    if (data.wait_for_button) {
        state = WAIT_FOR_BUTTON_STATE;
    // } else if (data.intake_button) {
    //     state = INTAKE_STATE;
    } else if (data.shoot_button) {
        state = SHOOT_STATE;
    } else if (data.rotation_mode_control_panel_button) {
        state = ROTATION_MODE_CONTROL_PANEL_STATE;
    } else if (data.position_mode_control_panel_button) {
        state = POSITION_MODE_CONTROL_PANEL_STATE;
    }
    //arm
    if (data.raise_intake_button) {
      state = INTAKE_STATE;
    } 
    if (data.lower_intake_button) {
      state = WAIT_FOR_BUTTON_STATE;
    }
    if (data.shooter_intake_button) {
      state = INTAKE_SHOOTER_STATE;
    }
}

void TeleopStateMachine::StateMachine(ButtonData data) {
    ProcessButtonData(data);

    

    //intake
    // if (data.intake_in) {
    //   state_intake = false;
    //   intake->intake_state = intake->IN_STATE;
    // } else 
    
    //control panel
    // if ()

    switch (state) {


        case INIT_STATE:
          arm->intake_arm_state = arm->REST_STATE;
          intake->intake_state = intake->STOP_STATE;
          shooter->shooter_state = shooter->STOP_STATE_H;
          control_panel->state = control_panel->IDLE;

          state = WAIT_FOR_BUTTON_STATE;
        break;


        case WAIT_FOR_BUTTON_STATE:
          arm->intake_arm_state = arm->DOWN_STATE;
          intake->intake_state = intake->STOP_STATE;
          shooter->shooter_state = shooter->STOP_STATE_H;
          control_panel->state = control_panel->IDLE;
          last_state = WAIT_FOR_BUTTON_STATE;
        break;


        case INTAKE_STATE:
          arm->intake_arm_state = arm->DOWN_STATE;
          intake->intake_state = intake->IN_STATE;
          last_state = INTAKE_STATE;
        break;

        case INTAKE_SHOOTER_STATE:
          shooter->shooter_state = shooter->INTAKE_STATE_H;
          last_state = INTAKE_SHOOTER_STATE;
        break;

        case SHOOT_STATE:
          shooter->shooter_state = shooter->SHOOT_STATE_H;
          last_state = SHOOT_STATE;
        break;

        case ROTATION_MODE_CONTROL_PANEL_STATE:
          control_panel->state = control_panel->ROTATION_MODE;
          last_state = ROTATION_MODE_CONTROL_PANEL_STATE;
        break;


        case POSITION_MODE_CONTROL_PANEL_STATE:
          control_panel->state = control_panel->POSITION_MODE;
          last_state = POSITION_MODE_CONTROL_PANEL_STATE;
        break;
    }

    SmartDashboard::PutString("State", TeleopStateMachine::StateName(state));

    last_state = state;

    arm->IntakeArmStateMachine();
    intake->IntakeStateMachine();
    shooter->ShooterStateMachine();
    control_panel->StateMachine();

}

std::string TeleopStateMachine::StateName(TeleopStateMachine::States state) {
    switch (state) {
        case INIT_STATE:
            return "Robot::Init";
        case WAIT_FOR_BUTTON_STATE:
            return "Robot::Wait For Button";
        case INTAKE_STATE:
            return "Robot::Intake";
        case SHOOT_STATE:
            return "Shooter::Shoot";
        case ROTATION_MODE_CONTROL_PANEL_STATE:
            return "Control Panel::Rotation Mode";
        case POSITION_MODE_CONTROL_PANEL_STATE:
            return "Control Panel::Position Mode";
        default:
            return "Robot::Null State";
    }
}
