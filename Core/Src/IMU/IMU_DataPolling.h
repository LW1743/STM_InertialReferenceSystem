//
// Created by lukas-wiener on 12/29/25.
//

#ifndef INERTREFSYS_IMU_DATAPOLLING_H
#define INERTREFSYS_IMU_DATAPOLLING_H

//Private Includes
#include "lsm6dsv16x_reg.h"
#include "stm32u5xx_hal.h"
#include "../Math/vector.h"
#include "stdio.h"
#include <string.h>




void setupIMUDataPolling(I2C_HandleTypeDef *hi2c);

void IMU_readDataPolling(void);

void getAccelerationVector3D(Vector3D* accelerationVector);

void getAngularVelocityVector3D(Vector3D* angularVelocityVector);

#endif //INERTREFSYS_IMU_DATAPOLLING_H