#pragma once

#include "rev/ColorSensorV3.h"
#include <ctre/Phoenix.h>

#include "Constants.h"

enum Colors {
  RED    = 0,
  BLUE   = 1,
  YELLOW = 2,
  GREEN  = 3,
  WHITE  = 4
};



Colors ColorFromFRCColor(frc::Color);

class ControlPanel {

public:
    TalonSRX* talon;

    ControlPanel();

    const int CONTROL_PANEL_TALON = 0;
    const float CONTROL_PANEL_SPEEN_ON = 1.0f;
    enum States {
        IDLE,
        POSITION_MODE,
        ROTATION_MODE
    };

    int rotationsCompleted = 0;
    Colors desiredColor = Colors::WHITE;

    void StateMachine(Colors detectedColor);
    inline void PositionMode() { state = States::POSITION_MODE; };
    inline void RotationMode() { state = States::ROTATION_MODE; };
    inline void IdleMode() { state = States::IDLE; };
    
    inline bool HasReachedPosition(Colors detectedColor) { return detectedColor == desiredColor; };
    
    void Rotate();
    void Stop();



    inline void ResetRotations() { rotationsCompleted = 0; };
    inline void DesireColor(Colors color) { desiredColor = color; };

    

    States state;
    States last_state;
    
};