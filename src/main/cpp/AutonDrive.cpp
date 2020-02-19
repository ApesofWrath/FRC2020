#include "AutonDrive.h"


AutonDrive::AutonDrive(int left1, int left2, int right1, int right2) : m_odometry{frc::Rotation2d(units::degree_t(GetHeading()))},
                                    t_left1{left1}, t_left2{left2}, t_right1{right1}, t_right2{right2} {
  ahrs = new AHRS(SerialPort::kUSB);
  

      
}

void AutonDrive::Update() {
    m_odometry.Update(frc::Rotation2d(units::degree_t(GetHeading())),
                    units::meter_t(t_left1.GetPosition()),
                    units::meter_t(t_right1.GetPosition()));
}

void AutonDrive::TankDriveVolts(units::volt_t left, units::volt_t right) {
    m_leftMotors.Set(left / units::volt_t(pdp.GetVoltage()));
    m_leftMotors.Set(right / units::volt_t(pdp.GetVoltage()));
    m_drive.Feed();
}

double AutonDrive::GetAverageEncoderDistance() {
    return (t_left1.GetPosition() + t_right1.GetPosition()) / 2.0;
}

void AutonDrive::SetMaxOutput(double maxOutput) {
    m_drive.SetMaxOutput(maxOutput);
}

double AutonDrive::GetHeading() {
    return std::remainder(ahrs->GetAngle(), 360);
}

double AutonDrive::GetTurnRate() {
    return ahrs->GetRate();
}

frc::Pose2d AutonDrive::GetPose() { return m_odometry.GetPose(); }


frc::DifferentialDriveWheelSpeeds AutonDrive::GetWheelSpeeds() {
  return {units::meters_per_second_t(t_left1.GetSpeed()),
          units::meters_per_second_t(t_left1.GetSpeed())};
}

void AutonDrive::ResetOdometry(frc::Pose2d pose) {
  ResetEncoders();
  m_odometry.ResetPosition(pose,
                           frc::Rotation2d(units::degree_t(GetHeading())));
}

void AutonDrive::ResetEncoders() {
    t_left1.SetPosition(0);
    t_right1.SetPosition(0);
}