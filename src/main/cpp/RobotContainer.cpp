#include "RobotContainer.h"



frc2::Command* RobotContainer::GetAutonomousCommand() {
  // Create a voltage constraint to ensure we don't accelerate too fast
  frc::DifferentialDriveVoltageConstraint *autoVoltageConstraint = new frc::DifferentialDriveVoltageConstraint(
      frc::SimpleMotorFeedforward<units::meter>(
          K_S, K_V, K_A),
      K_DRIVE_KINEMATICS, units::volt_t(10));

  // Set up config for trajectory
  frc::TrajectoryConfig *config = new frc::TrajectoryConfig(units::meters_per_second_t(MAX_FORWARD_MPS),
                               units::meters_per_second_squared_t(K_MAX_ACCEL));
  // Add kinematics to ensure max speed is actually obeyed
  config->SetKinematics(K_DRIVE_KINEMATICS);
  // Apply the voltage constraint
  config->AddConstraint(*autoVoltageConstraint);


  wpi::SmallString<64> deployDirectory;
  frc::filesystem::GetDeployDirectory(deployDirectory);
  wpi::sys::path::append(deployDirectory, "paths");
  wpi::sys::path::append(deployDirectory, m_autoSelected + ".wpilib.json");

  frc::Trajectory trajectory = frc::TrajectoryUtil::FromPathweaverJson(deployDirectory);

  frc2::RamseteCommand ramseteCommand(
      trajectory, [this]() { return m_drive->GetPose(); },
      frc::RamseteController(K_RAMSETE_B,
                             K_RAMSETE_ZETA),
      frc::SimpleMotorFeedforward<units::meters>(
          K_S, K_V, K_A),
      K_DRIVE_KINEMATICS,
      [this] { return m_drive->GetWheelSpeeds(); },
      frc2::PIDController(K_P_LEFT_VEL, 0, 0),
      frc2::PIDController(K_P_RIGHT_VEL, 0, 0),
      [this](auto left, auto right) { m_drive->TankDriveVolts(left, right); },
      {&m_drive});

  // no auto
  return new frc2::SequentialCommandGroup(
      std::move(ramseteCommand),
      frc2::InstantCommand([this] { m_drive->TankDriveVolts(0_V, 0_V); }, {}));
}