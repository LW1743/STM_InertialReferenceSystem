//
// Created by lukas-wiener on 12/29/25.
//

#include "IMU_PreProcessing.h"


static Vector3D Acceleration_3D;
static Vector3D Orientation_3D;
static OrientationQuaternion orientationQuaternion;
static Vector3D accel_mg3D;
static Vector3D mag_mG3D;

void initOrientationQuaternion() {
    orientationQuaternion.orientation4d.w = 1.0f;
    orientationQuaternion.orientation4d.x = 0.0f;
    orientationQuaternion.orientation4d.y = 0.0f;
    orientationQuaternion.orientation4d.z = 0.0f;
    orientationQuaternion.initialized = 0;
}

void getInitOrientation() {



}

IMU_STATUS IMU_Init() {
    initOrientationQuaternion();
    getInitOrientation();
    return IMU_STATUS_OK;
}

void IMU_linearizeAcceleration() {


}


void getLinearAcceleration(Vector3D* linearAcceleration3D) {
    linearAcceleration3D->x = Acceleration_3D.x;
    linearAcceleration3D->y = Acceleration_3D.y;
    linearAcceleration3D->z = Acceleration_3D.z;
}
