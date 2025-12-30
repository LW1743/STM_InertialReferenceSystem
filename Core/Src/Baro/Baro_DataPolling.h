//
// Created by lukas-wiener on 12/30/25.
//

#ifndef INERTREFSYS_BARO_DATAPOLLING_H
#define INERTREFSYS_BARO_DATAPOLLING_H

#include "stm32u5xx_hal.h"
#include <string.h>
#include <stdio.h>
#include "lps22df_reg.h"

void setupBaroDataPolling(I2C_HandleTypeDef *hi2c);

void Baro_readDataPolling(void);

double getBaroData(void);

#endif //INERTREFSYS_BARO_DATAPOLLING_H