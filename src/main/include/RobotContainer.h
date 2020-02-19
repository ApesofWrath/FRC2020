#pragma once

#include <string>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/commands/Command.h>
#include <frc2/command/SequentialCommandGroup.h>
#include <frc2/command/InstantCommand.h>
#include <frc2/command/PIDCommand.h>
#include <frc/trajectory/constraint/DifferentialDriveVoltageConstraint.h>
#include <frc/trajectory/TrajectoryConfig.h>
#include <frc/trajectory/Trajectory.h>
#include <frc2/command/RamseteCommand.h>

#include "Drive/DriveBase.h"
#include <frc/Filesystem.h>
#include <frc/trajectory/TrajectoryUtil.h>
#include <wpi/Path.h>
#include <wpi/SmallString.h>

#include "AutonDrive.h"



frc::SendableChooser<std::string> m_chooser;
const std::string kAutoNameDefault = "Default";
const std::string kAutoNameCustom = "My Auto";

std::string m_autoSelected;

/**
 * This class is where the bulk of the robot should be declared.  Since
 * Command-based is a "declarative" paradigm, very little robot logic should
 * actually be handled in the {@link Robot} periodic methods (other than the
 * scheduler calls).  Instead, the structure of the robot (including subsystems,
 * commands, and button mappings) should be declared here.
 */
class RobotContainer {
 public:
  RobotContainer(AutonDrive* drive) : m_drive(drive) {};

  AutonDrive* m_drive;

  frc2::Command* GetAutonomousCommand();

 private:
  void ConfigureButtonBindings();
};