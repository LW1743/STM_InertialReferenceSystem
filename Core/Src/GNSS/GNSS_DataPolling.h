//
// Created by lukas-wiener on 12/30/25.
//

#ifndef INERTREFSYS_GNSS_DATAPOLLING_H
#define INERTREFSYS_GNSS_DATAPOLLING_H
#include "teseo_liv3f.h"
#include "stm32u5xx_hal.h"
#include "../Math/vector.h"
#include "gnss_parser.h"


typedef enum {
    GNSS_ALIGN = 1,
    GNSS_INITIALIZING = 0
}GNSS_Status;

void GNSS_setup(UART_HandleTypeDef *huart);
void GNSS_getData(Vector3D *v);
void GNSS_parseData();

GNSS_Status GNSS_getStatus();

#endif //INERTREFSYS_GNSS_DATAPOLLING_H