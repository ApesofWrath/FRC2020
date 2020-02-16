#include "ControlPanel.h"
#include <frc/smartdashboard/SmartDashboard.h>

#ifndef OFFSET
#define OFFSET 0
#endif

ControlPanel::ControlPanel() {
    talon = new TalonSRX(CONTROL_PANEL_TALON);
}

Colors ControlPanel::OffsetColor(Colors color) {
  int cn = color;
  if (cn + OFFSET > 3) {
    cn = (cn + OFFSET) - 3;
  } else {
    cn = cn + OFFSET;
  }

  return Colors(cn); 
}


Colors ControlPanel::ColorFromFRCColor(frc::Color detectedColor) {
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
  std::string gameData;
  gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
  if(gameData.length() > 0 && state == States::POSITION_MODE) {
    switch (gameData[0])
    {
      case 'B' :
        DesireColor(Colors::BLUE);
        break;
      case 'G' :
        DesireColor(Colors::GREEN);
        break;
      case 'R' :
        DesireColor(Colors::RED);
        break;
      case 'Y' :
        DesireColor(Colors::YELLOW);
        break;
      default:
        DesireColor(Colors::WHITE);
        break;
    }
  }

  switch(state) {
    case IDLE:
      last_state = IDLE;
      break;
    case POSITION_MODE:
      if (!HasReachedPosition(detectedColor)) {
        Rotate();
      } else {
        Stop();
      }
      last_state = POSITION_MODE;;
      break;
    case ROTATION_MODE:
      if (last_state != ROTATION_MODE) {
        rmode_starting_color = OffsetColor(desiredColor);
      } else if (detectedColor != rmode_starting_color && rmode_starting_color != WHITE) {
        passed_starting_color = true;
      }

      if (passed_starting_color && detectedColor == rmode_starting_color) {
        rotations++;
        passed_starting_color = false;
      }

      if (rotations == requiredRotations) {
        rotations = 0;
        passed_starting_color = false;
        rmode_starting_color = WHITE;
        Stop();
      }

      last_state = ROTATION_MODE;
      break;
  }
}
