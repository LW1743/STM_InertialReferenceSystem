//
// Created by lukas-wiener on 12/29/25.
//

#include "IMU_PreProcessing.h"

static Vector3D Acceleration_3D;
static Vector3D Orientation_3D;


void getInitOrientation(Vector3D *orientation) {
    Vector3D accelearion_mG;

    //Get Acceleration
    getAccelerationVector3D(&accelearion_mG);

    //Nomalize Vector
    vector3d_normalize(&accelearion_mG);


    Quaternion4D accelerationQuaternion;

}

void setupIMU(I2C_HandleTypeDef *hi2c) {
    setupIMUDataPolling(hi2c);
}

void getLinearAcceleration(Vector3D* linearAcceleration3D) {

}
