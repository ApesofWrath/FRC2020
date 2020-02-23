#include "RobotContainer.h"
#include <units/units.h>
#include <frc/trajectory/TrajectoryGenerator.h>

#include <iostream>
#include <vector>

const frc::DifferentialDriveKinematics K_DRIVE_KINEMATICS{
    units::meter_t(K_TRACK_WIDTH)};
frc2::Command* RobotContainer::GetAutonomousCommand() {

    std::cout << "start\n";
    frc::DifferentialDriveVoltageConstraint *autoVoltageConstraint = new frc::DifferentialDriveVoltageConstraint(
        frc::SimpleMotorFeedforward<units::meter>(
            K_S, K_V, K_A),
        K_DRIVE_KINEMATICS, units::volt_t(10));

    std::cout << "step 2\n";
    // Set up config for trajectory
    frc::TrajectoryConfig *config = new frc::TrajectoryConfig(units::meters_per_second_t(MAX_FORWARD_MPS),
                                units::meters_per_second_squared_t(K_MAX_ACCEL));
    // Add kinematics to ensure max speed is actually obeyed
    std::cout << "step 3\n";
    config->SetKinematics(K_DRIVE_KINEMATICS);
    // Apply the voltage constraint
    std::cout << "step 4\n";
    config->AddConstraint(*autoVoltageConstraint);


    std::cout << "step 5\n";
    wpi::SmallString<64> deployDirectory;
    std::cout << "step 6\n";
    frc::filesystem::GetDeployDirectory(deployDirectory);
    std::cout << "step 7\n";
    wpi::sys::path::append(deployDirectory, "paths");
    std::cout << "step 8\n";
    wpi::sys::path::append(deployDirectory, m_autoSelected + ".wpilib.json");

    std::cout << "step 9\n";
      frc::Trajectory trajectory = frc::TrajectoryUtil::FromPathweaverJson(deployDirectory);
    std::cout << "step 9.5\n";

    std::vector<frc::Translation2d> points = {
        frc::Translation2d(1_m,0_m),
        frc::Translation2d(2_m,0_m),
    };


    auto exampleTrajectory = frc::TrajectoryGenerator::GenerateTrajectory(
        // Start at the origin facing the +X direction
        frc::Pose2d(0_m, 0_m, frc::Rotation2d(0_deg)),
        // Pass through these two interior waypoints, making an 's' curve path
        points,
        // End 3 meters straight ahead of where we started, facing forward
        frc::Pose2d(3_m, 0_m, frc::Rotation2d(0_deg)),
        // Pass the config
        *config);

    std::cout << "step 10\n";
    frc2::RamseteCommand ramseteCommand(
        exampleTrajectory, [this]() { return m_drive->GetPose(); },
        frc::RamseteController(K_RAMSETE_B,
                                K_RAMSETE_ZETA),
        frc::SimpleMotorFeedforward<units::meters>(
            K_S, K_V, K_A),
        K_DRIVE_KINEMATICS,
        [this] { return m_drive->GetWheelSpeeds(); },
        frc2::PIDController(K_P_LEFT_VEL, 0, 0),
        frc2::PIDController(K_P_RIGHT_VEL, 0, 0),
        [this](auto left, auto right) { m_drive->TankDriveVolts(left, right); },
        {m_drive});

    // no auto
    std::cout << "step 11\n";
    return new frc2::SequentialCommandGroup(
        std::move(ramseteCommand),
        frc2::InstantCommand([this] { m_drive->TankDriveVolts(0_V, 0_V); }, {}));
}

void RobotContainer::InitAutoChoices() {
    std::cout << "initauto: step1\n";
    m_chooser.SetDefaultOption(kAutoName_TestPath, "TestPath");    
    m_chooser.AddObject(kAutoName_UnnamedPath, "UnnamedPath");
    m_chooser.AddObject(kAutoName_Unnamed, "Unnamed");
}
