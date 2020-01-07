#include "Auton.h"

#include "Drive/DriveBase.h"
#include <iostream>


AutonDrive::AutonDrive(DriveBase* driveb, AHRS* ahrs_) 
{

    pdp = new PowerDistributionPanel(0);
    ahrs = ahrs_;

    t_left1 = driveb->canTalonLeft1;
    t_left2 = driveb->canTalonLeft2;
    t_right1 = driveb->canTalonRight1;
    t_right2 = driveb->canTalonRight2;
    
    

    // t_left1.SetInverted(true);
    // // t_left2.SetInverted(true);
    

    m_odometry = new DifferentialDriveOdometry(frc::Rotation2d(units::degree_t(GetHeading())));

    m_drive.SetSafetyEnabled(false);
      
}

void AutonDrive::Periodic() {
    GetWheelSpeeds();
    m_odometry->Update(frc::Rotation2d(units::degree_t(GetHeading())),
                    units::meter_t(getDistanceFromTicks(t_left1->GetSelectedSensorPosition())),
                    units::meter_t(getDistanceFromTicks(t_right1->GetSelectedSensorPosition())));
}

void AutonDrive::TankDriveVolts(units::volt_t left, units::volt_t right) {
    std::cout << GetWheelSpeeds().left << "\n";
    // t_left1.Set(left / units::volt_t(pdp->GetVoltage()));
    m_leftMotors.SetVoltage(left);
    // t_left2.Set(left / units::volt_t(pdp->GetVoltage()));
    // fx_left1->Set(ControlMode::PercentOutput, 1.0f);
    // fx_left2->Set(ControlMode::PercentOutput, 1.0f);

    std::cout << GetWheelSpeeds().right << "\n";
    m_rightMotors.SetVoltage(right);
    // fx_right1->Set(ControlMode::PercentOutput, -1.0f);
    // fx_right2->Set(ControlMode::PercentOutput, -1.0f);

    frc::SmartDashboard::PutNumber("m_ left", left.value());
    frc::SmartDashboard::PutNumber("m_ right", right.value());

    // m_rightMotors.SetVoltage(right);
    // t_right2.Set(right / units::volt_t(pdp->GetVoltage()));
    // fx_right1->Set(ControlMode::PercentOutput, right / units::volt_t(pdp->GetVoltage()))
    m_drive.Feed();
}

double AutonDrive::GetAverageEncoderDistance() {
    return (getDistanceFromTicks(t_left1->GetSelectedSensorPosition()) + getDistanceFromTicks(t_right1->GetSelectedSensorPosition())) / 2.0;
}

void AutonDrive::SetMaxOutput(double maxOutput) {
    m_drive.SetMaxOutput(maxOutput);
}

double AutonDrive::GetHeading() {
    std::cout << "gh\n";
    return std::remainder(-ahrs->GetAngle(), 360);
}

double AutonDrive::GetTurnRate() {
    return ahrs->GetRate();
}

frc::Pose2d AutonDrive::GetPose() { 
    return m_odometry->GetPose();
}


frc::DifferentialDriveWheelSpeeds AutonDrive::GetWheelSpeeds() {
    frc::SmartDashboard::PutNumber("wheel speed left", getSpeedFromTicksPer100Milliseconds(t_left1->GetSelectedSensorVelocity()));
    frc::SmartDashboard::PutNumber("wheel speed right", getSpeedFromTicksPer100Milliseconds(t_right1->GetSelectedSensorVelocity()));
    return {units::meters_per_second_t(getSpeedFromTicksPer100Milliseconds(t_left1->GetSelectedSensorVelocity())),
          units::meters_per_second_t(getSpeedFromTicksPer100Milliseconds(t_right1->GetSelectedSensorVelocity()))};
}

void AutonDrive::ResetOdometry(frc::Pose2d pose) {
  ResetEncoders();
  ahrs->Reset();
  ahrs->ZeroYaw();
  m_odometry->ResetPosition(pose,
                           frc::Rotation2d(units::degree_t(GetHeading())));
}

void AutonDrive::ResetEncoders() {
    t_left1->SetSelectedSensorPosition(0);
    t_right1->SetSelectedSensorPosition(0);
}