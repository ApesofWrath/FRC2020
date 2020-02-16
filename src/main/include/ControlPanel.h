#pragma once

#include "rev/ColorSensorV3.h"
#include <ctre/Phoenix.h>

#include <frc/DriverStation.h>


enum Colors {
  RED    = 0,
  BLUE   = 1,
  YELLOW = 2,
  GREEN  = 3,
  WHITE  = 4
};




class ControlPanel {

public:

    static Colors ColorFromFRCColor(frc::Color);

    TalonSRX* talon;

    ControlPanel();

    const int CONTROL_PANEL_TALON = 0;
    const float CONTROL_PANEL_SPEEN_ON = 1.0f;
    enum States {
        IDLE,
        POSITION_MODE,
        ROTATION_MODE
    };

    Colors desiredColor = Colors::WHITE;
    int requiredRotations = 3;

    void StateMachine(Colors detectedColor);
    inline void PositionMode() { state = States::POSITION_MODE; };
    inline void RotationMode() { state = States::ROTATION_MODE; };
    inline void IdleMode() { state = States::IDLE; };
    
    inline bool HasReachedPosition(Colors detectedColor) { return detectedColor == desiredColor; };
    
    void Rotate();
    void Stop();



    inline void ResetRotations() { rotations = 0; };
    inline void DesireColor(Colors color) { desiredColor = color; };

    bool passed_starting_color;

    Colors OffsetColor(Colors color);

    Colors rmode_starting_color;

    int rotations;

    States state;
    States last_state;
    
};