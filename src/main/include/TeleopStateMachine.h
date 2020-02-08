#pragma once


struct ButtonData {
    bool wait_for_button, lower_intake_button, raise_intake_button, run_intake_button, stop_intake_button,
         stop_control_panel_button, manual_control_panel_button, rotation_mode_control_panel_button, 
         position_mode_control_panel_button, shooter_shoot_button, shooter_stop_button, 
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

    enum States {
        WAIT_FOR_BUTTON,
        LOWER_INTAKE, RAISE_INTAKE, RUN_INTAKE, IDLE_INTAKE,
        IDLE_CONTROL_PANEL, ROTATION_MODE_CONTROL_PANEL, POSITION_MODE_CONTROL_PANEL, MANUAL_CONTROL_PANEL,
        SHOOTER_SHOOT, SHOOTER_INTAKE, SHOOTER_IDLE
    };

    States state;
    States last_state;
};