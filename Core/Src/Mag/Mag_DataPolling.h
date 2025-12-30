//
// Created by lukas-wiener on 12/29/25.
//

#ifndef INERTREFSYS_MAG_DATAPOLLING_H
#define INERTREFSYS_MAG_DATAPOLLING_H

#include "stm32u5xx_hal.h"
#include <string.h>
#include <stdio.h>
#include "lis2mdl_reg.h"
#include "../Math/vector.h"

typedef enum {
    Mag_STATUS_OK = 0,
    Mag_STATUS_ERROR = -1,
}Mag_STATUS;

Mag_STATUS Mag_setup(I2C_HandleTypeDef *hi2c);
void Mag_readDataPolling(void);
void Mag_getData(Vector3D *magVector);

#endif //INERTREFSYS_MAG_DATAPOLLING_H