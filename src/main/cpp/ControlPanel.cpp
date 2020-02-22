#include "ControlPanel.h"
#include <frc/smartdashboard/SmartDashboard.h>

ControlPanel::ControlPanel() {
    talon = new TalonSRX(CONTROL_PANEL_TALON);
}

std::string ControlPanel::getColor(Colors c) {
  switch (c) {
    case Colors::RED:
      return "Red";
    case Colors::YELLOW:
      return "Yellow";
    case Colors::BLUE:
      return "Blue";
    case Colors::GREEN:
      return "Green";
    case Colors::WHITE:
      return "None";
    default:
      return "None";
  }
}


Colors ColorFromFRCColor(frc::Color detectedColor) {
    frc::SmartDashboard::PutNumber("Red", detectedColor.red);
    frc::SmartDashboard::PutNumber("Green", detectedColor.green);
    frc::SmartDashboard::PutNumber("Blue", detectedColor.blue);

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

void ControlPanel::StateMachine() {

    detectedColor = m_colorSensor.GetColor();

    switch(state) {
        case IDLE:
            last_state = States::IDLE;
            break;
        case POSITION_MODE:
            if (!HasReachedPosition(ColorFromFRCColor(detectedColor))) {
                Rotate();
            } else {
                Stop();
            }
            last_state = States::POSITION_MODE;
            break;
        case ROTATION_MODE:
            // if (ColorFromFRCColor(detectedColor) == rotationModeStartingColor) {
            //   rotations++;
            // }



            // if (rotations == neededRotations) {
            //   Stop();
            // } else {
            //   Rotate();
            // }
            last_state = States::ROTATION_MODE;
            break;
    }
}
