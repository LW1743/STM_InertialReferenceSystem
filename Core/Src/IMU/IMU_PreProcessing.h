//
// Created by lukas-wiener on 12/29/25.
//

#ifndef INERTREFSYS_IMU_PREPROCESSING_H
#define INERTREFSYS_IMU_PREPROCESSING_H

#include "IMU_DataPolling.h"
#include "../Math/vector.h"
#include "../Math/quaternion.h"



void setupIMU(I2C_HandleTypeDef *hi2c);

void getLinearAcceleration(Vector3D* linearAcceleration3D);


#endif //INERTREFSYS_IMU_PREPROCESSING_H