#include "TeleopStateMachine.h"

using namespace frc;

TeleopStateMachine::TeleopStateMachine(/* args */)
{
    state = WAIT_FOR_BUTTON_STATE;
    last_state = WAIT_FOR_BUTTON_STATE;


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
        joyOp->GetRawButton(ButtonIDs::SHOOTER_STOP_BUTTON),
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
}

void TeleopStateMachine::StateMachine(ButtonData data) {
    ProcessButtonData(data);

    if (data.wait_for_button) {
      state = WAIT_FOR_BUTTON_STATE;
    } else {

    }

    //arm
    if (data.raise_intake_button) {
      state_arm = false;
      arm->intake_arm_state = arm->UP_STATE;
    } else if (data.lower_intake_button) {
      state_arm = false;
      arm->intake_arm_state = arm->DOWN_STATE;
    // } else if (data.arm_rest) {
    //   state_arm = false;
    //   arm->intake_arm_state = arm->REST_STATE;
    } else {
      state_arm = true;
    }

    //intake
    // if (data.intake_in) {
    //   state_intake = false;
    //   intake->intake_state = intake->IN_STATE;
    // } else 
    if (data.intake_out_button){
      state_intake = false;
      intake->intake_state = intake->OUT_STATE;
    // } else if (data.intake_stop) {
    //   state_intake = false;
    //   intake->intake_state = intake->STOP_STATE;
    } else {
      state_intake = true;
    }

    //shooter
    if (data.shooter_intake_button) {
      state_shooter = false;
      shooter->shooter_state = shooter->INTAKE_STATE;
    } else if (data.shoot_button) {
      state_shooter = false;
      shooter->shooter_state = shooter->SHOOT_STATE;
    // } else if (data.shooter_wait) {
    //   state_shooter = false;
    //   shooter->shooter_state = shooter->WAITING_STATE;
    } else if (data.shooter_stop_button) {
      state_shooter = false;
      shooter->shooter_state = shooter->STOP_STATE;
    } else {
      state_shooter = true;
    }

    //control panel
    // if ()

    switch (state) {


        case INIT_STATE:
          arm->intake_arm_state = arm->REST_STATE;
          intake->intake_state = intake->STOP_STATE;
          shooter->shooter_state = shooter->STOP_STATE;
          control_panel->control_panel_state = control_panel->IDLE_STATE;

          state = WAIT_FOR_BUTTON_STATE;
        break;


        case WAIT_FOR_BUTTON_STATE:
          if (data.lower_intake_button) {
            state = INTAKE_STATE;
          } else if (data.shoot_button) {
            state = SHOOT_STATE;
          } else if (data.rotation_mode_control_panel_button) {
            state = ROTATION_MODE_CONTROL_PANEL_STATE;
          } else if (data.position_mode_control_panel_button) {
            state = POSITION_MODE_CONTROL_PANEL_STATE;
          }

          last_state = WAIT_FOR_BUTTON_STATE;
        break;


        case INTAKE_STATE:
          if (state_arm) {
          arm->intake_arm_state = arm->DOWN_STATE;
          }
          if (state_intake) {
          intake->intake_state = intake->IN_STATE;
          }
          if (state_shooter) {
          shooter->shooter_state = shooter->INTAKE_STATE;
          }

          state = POST_INTAKE_STATE;
          last_state = INTAKE_STATE;
        break;


        case POST_INTAKE_STATE:
          if (state_arm) {
          arm->intake_arm_state = arm->UP_STATE;
          }
          if (state_intake) {
          intake->intake_state = intake->STOP_STATE;
          }
          if (state_shooter) {
          shooter->shooter_state = shooter->WAITING_STATE;
          }

          if (data.shoot_button) {
            state = SHOOT_STATE;
          }
          last_state = POST_INTAKE_STATE;
        break;


        case SHOOT_STATE:
          if (state_arm) {
          arm->intake_arm_state = arm->REST_STATE;
          }
          if (state_intake) {
          intake->intake_state = intake->STOP_STATE;
          }
          if (state_shooter) {
          shooter->shooter_state = shooter->SHOOT_STATE;
          }

          state = POST_SHOOT_STATE;
          last_state = SHOOT_STATE;
        break;


        case POST_SHOOT_STATE:
          if (state_arm) {
          arm->intake_arm_state = arm->REST_STATE;
          }
          if (state_intake) {
          intake->intake_state = intake->STOP_STATE;
          }
          if (state_shooter) {
          shooter->shooter_state = shooter->STOP_STATE;
          }

          state = WAIT_FOR_BUTTON_STATE;
          last_state = POST_SHOOT_STATE;
        break;


        case ROTATION_MODE_CONTROL_PANEL_STATE:
          if (state_control_panel) {
          control_panel->control_panel_state = control_panel->ROTATION_MODE;
          }

          state = WAIT_FOR_BUTTON_STATE;
          last_state = ROTATION_MODE_CONTROL_PANEL_STATE;
        break;


        case POSITION_MODE_CONTROL_PANEL_STATE:
          if (state_control_panel) {
          control_panel->control_panel_state = control_panel->POSITION_MODE;
          }

          state = WAIT_FOR_BUTTON_STATE;
          last_state = POSITION_MODE_CONTROL_PANEL_STATE;
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
            return "Robot::Intake";
        case POST_INTAKE_STATE:
            return "Robot::PostIntake";
        case SHOOT_STATE:
            return "Shooter::Shoot";
        case POST_SHOOT_STATE:
            return "Shooter::PostShoot";
        case ROTATION_MODE_CONTROL_PANEL_STATE:
            return "Control Panel::Rotation Mode";
        case POSITION_MODE_CONTROL_PANEL_STATE:
            return "Control Panel::Position Mode";
        default:
            return "Robot::Null State";
    }
}
