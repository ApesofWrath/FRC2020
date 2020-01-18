#include "ControlPanel.h"
#include <frc/smartdashboard/SmartDashboard.h>

ControlPanel::ControlPanel() {
    talon = new TalonSRX(CONTROL_PANEL_TALON);
}


Colors ColorFromFRCColor(frc::Color detectedColor) {
    if (detectedColor.red > 0.3 && detectedColor.green > 0.5 && detectedColor.blue < 0.2) {
      frc::SmartDashboard::PutString("Color", "Yellow");
      return Colors::YELLOW;
    } else if (detectedColor.red > 0.4) {
      frc::SmartDashboard::PutString("Color", "Red");
      return Colors::RED;
    } else if (detectedColor.green > 0.5 && detectedColor.blue < 0.3 && detectedColor.red < 0.2 && detectedColor.blue < 0.3) {
      frc::SmartDashboard::PutString("Color", "Green");
      return Colors::GREEN;
    } else if (detectedColor.blue > 0.4 && detectedColor.red < 0.2 && detectedColor.green > 0.4) {
      frc::SmartDashboard::PutString("Color", "Blue");
      return Colors::BLUE;
    } else {
      frc::SmartDashboard::PutString("Color", "None");
      return Colors::WHITE;
    }
}

void ControlPanel::Rotate() {
    talon->Set(ControlMode::PercentOutput, CONTROL_PANEL_SPEEN_ON);
}

void ControlPanel::Stop() {
    talon->Set(ControlMode::PercentOutput, 0);
    state = IDLE;
}

void ControlPanel::StateMachine(Colors detectedColor) {
    switch(state) {
        case IDLE:
            break;
        case POSITION_MODE:
            if (!HasReachedPosition(detectedColor)) {
                Rotate();
            } else {
                Stop();
            }
            break;
        case ROTATION_MODE:
            break;
    }
}
