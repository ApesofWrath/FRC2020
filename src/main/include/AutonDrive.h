#pragma once

#include "AHRS.h"
#include <frc/kinematics/DifferentialDriveOdometry.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/SpeedControllerGroup.h>
#include <frc/geometry/Pose2d.h>
#include <frc/PowerDistributionPanel.h>
#include <frc/SpeedController.h>
#include "Drive/DriveBase.h"
#include "Drive/DriveConstants.h"

class AutonDrive {
public:
    AutonDrive(int left1, int left2, int right1, int right2);

    AHRS* ahrs;
    frc::PowerDistributionPanel pdp;

    frc::PWMTalonFX t_left1, t_left2, t_right1, t_right2;

    frc::SpeedControllerGroup m_leftMotors{t_left1, t_left2};
    frc::SpeedControllerGroup m_rightMotors{t_right1, t_right2};

    frc::DifferentialDriveOdometry m_odometry;

    double GetHeading();

    void Update();

    double GetAverageEncoderDistance();

    frc::Pose2d GetPose();
    
    frc::DifferentialDriveWheelSpeeds GetWheelSpeeds();

    void TankDriveVolts(units::volt_t left, units::volt_t right);

    double percentFromVolts(units::volt_t volts);

    frc::DifferentialDrive m_drive{m_leftMotors, m_rightMotors};

    void ResetOdometry(frc::Pose2d pose);
    double GetTurnRate();
    void SetMaxOutput(double maxOutput);
    void ResetEncoders();

};

const frc::DifferentialDriveKinematics K_DRIVE_KINEMATICS(
    units::meter_t(K_TRACK_WIDTH));

const double K_RAMSETE_B = 2;
const double K_RAMSETE_ZETA = 0.7;