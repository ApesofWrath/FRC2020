#include "RobotContainer.h"
#include <units/units.h>
#include <frc/trajectory/TrajectoryGenerator.h>
#include <frc/smartdashboard/SmartDashboard.h>


#include <iostream>
#include <vector>


const frc::DifferentialDriveKinematics K_DRIVE_KINEMATICS{
    units::meter_t(K_TRACK_WIDTH)};


frc2::Command* RobotContainer::GetAutonomousCommand() {

    // Setup
    frc::DifferentialDriveVoltageConstraint *autoVoltageConstraint = new frc::DifferentialDriveVoltageConstraint(
      frc::SimpleMotorFeedforward<units::meter>(
          K_S, K_V, K_A),
      K_DRIVE_KINEMATICS, units::volt_t(10));

    frc::TrajectoryConfig *config = new frc::TrajectoryConfig(units::meters_per_second_t(2),
                                units::meters_per_second_squared_t(3));
    config->SetKinematics(K_DRIVE_KINEMATICS);
    config->AddConstraint(*autoVoltageConstraint);

    // Pathweaver load    NOT YET
    // wpi::SmallString<64> deployDirectory;
    // frc::filesystem::GetDeployDirectory(deployDirectory);
    // wpi::sys::path::append(deployDirectory, "paths");
    // wpi::sys::path::append(deployDirectory, m_autoSelected + ".wpilib.json");
      // frc::Trajectory trajectory = frc::TrajectoryUtil::FromPathweaverJson(deployDirectory);
 

    // Hardcode
    frc::Pose2d start, end;
    std::vector<frc::Translation2d> points;
    switch (m_autoSelected) {
        case CROSS_INIT_LINE:
            start = frc::Pose2d(0_m, 0_m, frc::Rotation2d(0_deg));
            end = frc::Pose2d(1_m, 0_m, frc::Rotation2d(0_deg));
            points = {};
        break;

        case SHOOT_PRELOAD:
            start = frc::Pose2d(0_m, 0_m, frc::Rotation2d(0_deg));
            end = frc::Pose2d(-3.048_m, 0_m, frc::Rotation2d(0_deg));
            points = {};
        break;

        default:
            start = frc::Pose2d(0_m, 0_m, frc::Rotation2d(0_deg));
            end = frc::Pose2d(0_m, 0_m, frc::Rotation2d(0_deg));
            points = {};
        break;
    }


    auto trajectory = frc::TrajectoryGenerator::GenerateTrajectory(
        start,
        points,
        end,
        *config);

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
        {m_drive});


    switch (m_autoSelected) {
        case CROSS_INIT_LINE:
            return new frc2::SequentialCommandGroup(
                std::move(ramseteCommand),
                frc2::InstantCommand([this] { m_drive->TankDriveVolts(0_V, 0_V); }, {})
            );
        break;

        case SHOOT_PRELOAD:
            return new frc2::SequentialCommandGroup(
                std::move(ramseteCommand),
                frc2::InstantCommand([this] { m_drive->TankDriveVolts(0_V, 0_V); }, {}),
                frc2::InstantCommand([this] { m_shooter->shooter_state = m_shooter->SHOOT_STATE_H;}),
                frc2::WaitCommand(1.5_s),
                frc2::InstantCommand([this] { m_shooter->shooter_state = m_shooter->STOP_STATE_H;})
            );
        default:
            return new frc2::InstantCommand([this] { frc::SmartDashboard::PutString("status","Why aren't you running auton??");});
    }
}
/*

return new frc2::SequentialCommandGroup(
        frc2::InstantCommand([this] {
            m_arm->intake_arm_state = m_arm->DOWN_STATE;
            m_intake->intake_state = m_intake->IN_STATE;
            }),
        std::move(ramseteCommand),
        frc2::InstantCommand([this] { m_drive->TankDriveVolts(0_V, 0_V); }, {}),
        frc2::InstantCommand([this] {
            m_arm->intake_arm_state = m_arm->UP_STATE;
            m_intake->intake_state = m_intake->STOP_STATE;
            m_shooter->shooter_state = m_shooter->SHOOT_STATE_H;
            }),
        frc2::WaitCommand(1.5_s),
        frc2::InstantCommand([this] {
            m_shooter->shooter_state = m_shooter->STOP_STATE_H;
            })
        
        // frc2::InstantCommand([this] { m_shooter->DoOneBeltRotation(); }, {}),
        // frc2::WaitUntilCommand([this] () -> bool { return m_shooter->shooter_state == m_shooter->STOP_STATE_H;})
        
    );
*/
/*
change a state
frc2::InstantCommand([this] { m_intake->state = Intake::States::IN})

shoot




*/


void RobotContainer::InitAutoChoices() {

}
