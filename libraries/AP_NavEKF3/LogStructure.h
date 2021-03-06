#pragma once

#include <AP_Logger/LogStructure.h>

#define LOG_IDS_FROM_NAVEKF3 \
    LOG_XKT_MSG, \
    LOG_XKFM_MSG, \
    LOG_XKTV_MSG

// @LoggerMessage: XKT
// @Description: EKF3 timing information
// @Field: TimeUS: Time since system startup
// @Field: C: EKF core this message instance applies to
// @Field: Cnt: count of samples used to create this message
// @Field: IMUMin: smallest IMU sample interval
// @Field: IMUMax: largest IMU sample interval
// @Field: EKFMin: low-passed achieved average time step rate for the EKF (minimum)
// @Field: EKFMax: low-passed achieved average time step rate for the EKF (maximum)
// @Field: AngMin: accumulated measurement time interval for the delta angle (minimum)
// @Field: AngMax: accumulated measurement time interval for the delta angle (maximum)
// @Field: VMin: accumulated measurement time interval for the delta velocity (minimum)
// @Field: VMax: accumulated measurement time interval for the delta velocity (maximum)
struct PACKED log_XKT {
    LOG_PACKET_HEADER;
    uint64_t time_us;
    uint8_t core;
    uint32_t timing_count;
    float dtIMUavg_min;
    float dtIMUavg_max;
    float dtEKFavg_min;
    float dtEKFavg_max;
    float delAngDT_min;
    float delAngDT_max;
    float delVelDT_min;
    float delVelDT_max;
};


// @LoggerMessage: XKFM
// @Description: EKF3 diagnostic data for on-ground-and-not-moving check
// @Field: TimeUS: Time since system startup
// @Field: C: EKF core this message instance applies to
// @Field: OGNM: True of on ground and not moving
// @Field: GLR: Gyroscope length ratio
// @Field: ALR: Accelerometer length ratio
// @Field: GDR: Gyroscope rate of change ratio
// @Field: ADR: Accelerometer rate of change ratio
struct PACKED log_XKFM {
    LOG_PACKET_HEADER;
    uint64_t time_us;
    uint8_t core;
    uint8_t ongroundnotmoving;
    float gyro_length_ratio;
    float accel_length_ratio;
    float gyro_diff_ratio;
    float accel_diff_ratio;
};

// @LoggerMessage: XKTV
// @Description: EKF3 Yaw Estimator States
// @Field: TimeUS: Time since system startup
// @Field: C: EKF3 core this data is for
// @Field: TVS: Tilt Error Variance from symbolic equations (rad^2)
// @Field: TVD: Tilt Error Variance from difference method (rad^2)
struct PACKED log_XKTV {
    LOG_PACKET_HEADER;
    uint64_t time_us;
    uint8_t core;
    float tvs;
    float tvd;
};

#define LOG_STRUCTURE_FROM_NAVEKF3        \
    { LOG_XKT_MSG, sizeof(log_XKT),   \
      "XKT", "QBIffffffff", "TimeUS,C,Cnt,IMUMin,IMUMax,EKFMin,EKFMax,AngMin,AngMax,VMin,VMax", "s#sssssssss", "F-000000000"}, \
    { LOG_XKTV_MSG, sizeof(log_XKTV),                         \
      "XKTV", "QBff", "TimeUS,C,TVS,TVD", "s#rr", "F-00"}, \
    { LOG_XKFM_MSG, sizeof(log_XKFM),   \
      "XKFM", "QBBffff", "TimeUS,C,OGNM,GLR,ALR,GDR,ADR", "s------", "F------"},
