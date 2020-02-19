#include "TeleopStateMachine.h"

using namespace frc;

TeleopStateMachine::TeleopStateMachine(/* args */)
{
    state = WAIT_FOR_BUTTON_STATE;
    last_state = WAIT_FOR_BUTTON_STATE;

    bool state_arm = false;
    bool state_intake = false;
    bool state_shooter = false;
    bool state_control_panel = false;

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
        joyOp->GetRawButton(ButtonIDs::SHOOT_BUTTON)
     };
}

void TeleopStateMachine::ProcessButtonData(ButtonData data) {
    if (data.wait_for_button) {
        state = WAIT_FOR_BUTTON_STATE;
    } else if (data.intake_button) {
        state = INTAKE_STATE;
    } else if (data.shoot_button) {
        state = SHOOT_STATE;
    } else if (data.rotation_mode_control_panel_button) {
        state = ROTATION_MODE_CONTROL_PANEL;
    } else if (data.position_mode_control_panel_button) {
        state = POSITION_MODE_CONTROL_PANEL;
    }
}

void TeleopStateMachine::StateMachine(ButtonData data) {
    ProcessButtonData(data);

    if (data.wait_for_button) {
      state = WAIT_FOR_BUTTON_STATE;
    } else {

    }

    //arm
    if (data.arm_up) {
      state_arm = false;
      arm->intake_arm_state = arm->UP_STATE_H;
    } else if (data.arm_down) {
      state_arm = false;
      arm->intake_arm_state = arm->DOWN_STATE_H;
    } else if (data.arm_rest) {
      state_arm = false;
      arm->intake_arm_state = arm->REST_STATE_H;
    } else {
      state_arm = true;
    }

    //intake
    if (data.intake_in) {
      state_intake = false;
      intake->intake_state = intake->IN_STATE_H;
    } else if (data.intake_out)\ {
      state_intake = false;
      intake->intake_state = intake->OUT_STATE_H;
    } else if (data.intake_stop) {
      state_intake = false;
      intake->intake_state = intake->STOP_STATE_H;
    } else {
      state_intake = true;
    }

    //shooter
    if (data.shooter_intake) {
      state_shooter = false;
      shooter->shooter_state = shooter->INTAKE_STATE_H;
    } else if (data.shooter_shoot) {
      state_shooter = false;
      shooter->shooter_state = shooter->SHOOT_STATE_H;
    } else if (data.shooter_wait) {
      state_shooter = false;
      shooter->shooter_state = shooter->WAITING_STATE_H;
    } else if (data.shooter_stop) {
      state_shooter = false;
      shooter->shooter_state = shooter->STOP_STATE_H;
    } else {
      state_shooter = true;
    }

    //control panel
    if ()

    switch (state) {


        case INIT_STATE:
          arm->intake_arm_state = arm->REST_STATE_H;
          intake->intake_state = intake->STOP_STATE_H;
          shooter->shooter_state = shooter->STOP_STATE_H;
          control_panel->control_panel_state = control_panel->IDLE_STATE_H;

          state = WAIT_FOR_BUTTON_STATE;
        break;


        case WAIT_FOR_BUTTON_STATE:
          if (data.intake_button) {
            state = INTAKE_STATE;
          } else if (data.shoot_button) {
            state = SHOOT_STATE;
          } else if (data.rotation_mode_control_panel_button) {
            state = ROTATION_MODE_CONTROL_PANEL_STATE;
          } else if (data.position_mode_control_panel_button) {
            state = POSITION_MODE_CONTROL_PANEL_STATE;
          }

          last_state = WAIT_FOR_BUTTON_STATE
        break;


        case INTAKE_STATE:
          if (state_arm) {
          arm->intake_arm_state = arm->DOWN_STATE_H;
          }
          if (state_intake) {
          intake->intake_state = intake->IN_STATE_H;
          }
          if (state_shooter) {
          shooter->shooter_state = shooter->INTAKE_STATE_H;
          }

          state = POST_INTAKE_STATE;
          last_state = INTAKE_STATE;
        break;


        case POST_INTAKE_STATE:
          if (state_arm) {
          arm->intake_arm_state = arm->UP_STATE_H;
          }
          if (state_intake) {
          intake->intake_state = intake->STOP_STATE_H;
          }
          if (state_shooter) {
          shooter->shooter_state = shooter->WAITING_STATE_H;
          }

          if (data.shoot_button) {
            state = SHOOT_STATE;
          }
          last_state = POST_INTAKE_STATE;
        break;


        case SHOOT_STATE:
          if (state_arm) {
          arm->intake_arm_state = arm->REST_STATE_H;
          }
          if (state_intake) {
          intake->intake_state = intake->STOP_STATE_H;
          }
          if (state_shooter) {
          shooter->shooter_state = shooter->SHOOT_STATE_H;
          }

          state = POST_SHOOT_STATE;
          last_state = SHOOT_STATE;
        break;


        case POST_SHOOT_STATE:
          if (state_arm) {
          arm->intake_arm_state = arm->REST_STATE_H;
          }
          if (state_intake) {
          intake->intake_state = intake->STOP_STATE_H;
          }
          if (state_shooter) {
          shooter->shooter_state = shooter->STOP_STATE_H;
          }

          state = WAIT_FOR_BUTTON_STATE;
          last_state = POST_SHOOT_STATE;
        break;


        case ROTATION_MODE_CONTROL_PANEL_STATE:
          if (state_control_panel) {
          control_panel->control_panel_state = control_panel->ROTATION_MODE_H;
          }

          state = WAIT_FOR_BUTTON_STATE;
          last_state = ROTATION_MODE_CONTROL_PANEL_STATE;
        break;


        case POSITION_MODE_CONTROL_PANEL_STATE:
          if (state_control_panel) {
          control_panel->control_panel_state = control_panel->POSITION_MODE_H;
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
        case ROTATION_MODE_CONTROL_PANEL:
            return "Control Panel::Rotation Mode";
        case POSITION_MODE_CONTROL_PANEL:
            return "Control Panel::Position Mode";
        default:
            return "Robot::Null State";
    }
}
