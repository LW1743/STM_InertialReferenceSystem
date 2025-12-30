//
// Created by lukas-wiener on 12/29/25.
//

#ifndef INERTREFSYS_IMU_PREPROCESSING_H
#define INERTREFSYS_IMU_PREPROCESSING_H

#include "IMU_DataPolling.h"
#include "../Math/vector.h"
#include "../Math/quaternion.h"
#include "../Mag/Mag_DataPolling.h"

#define GRAVITY_MILLIG = 1000;
#define DEG_TO_RAD = (M_PI / 180.0)

typedef struct {
    Quaternion4D orientation4d;
    uint8_t initialized;
}OrientationQuaternion;

IMU_STATUS IMU_Init();

void getLinearAcceleration(Vector3D* linearAcceleration3D);

void IMU_linearizeAcceleration();


#endif //INERTREFSYS_IMU_PREPROCESSING_H