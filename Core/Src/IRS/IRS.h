//
// Created by lukas-wiener on 12/30/25.
//

#ifndef INERTREFSYS_IRS_H
#define INERTREFSYS_IRS_H
#include "stm32u5xx_hal.h"

//Math
#include "../Math/vector.h"
#include "../Math/quaternion.h"

//Mag
#include "../Mag/Mag_DataPolling.h"

//Baro
#include "../Baro/Baro_DataPolling.h"

//IMU
#include "../IMU/IMU_DataPolling.h"
#include "../IMU/IMU_PreProcessing.h"

//GPS
#include "../GNSS/GNSS_DataPolling.h"

//DeadReckoning
#include "../DeadReckoning/DeadReckoning.h"

//KarmanFilter
#include "../KarmanFilter/KarmanFilter.h"


typedef enum {
    IRS_STATUS_OK = 0,
    IRS_STATUS_ERROR = -1
}IRS_STATUS;

IRS_STATUS IRS_setup(I2C_HandleTypeDef *hi2c, UART_HandleTypeDef *huart);

void comparePositions(Vector3D IRS_position, Vector3D GNSS_position);
#endif //INERTREFSYS_IRS_H