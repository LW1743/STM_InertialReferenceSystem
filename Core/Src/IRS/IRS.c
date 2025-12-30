//
// Created by lukas-wiener on 12/30/25.
//


#include "IRS.h"

IRS_STATUS IRS_setup(I2C_HandleTypeDef *hi2c, UART_HandleTypeDef *huart) {

    printf("Setup IRS\n");

    uint8_t status = 0;

    status += GNSS_setup(huart);
    status += Mag_setup(hi2c);
    status += IMU_setup(hi2c);
    status += Baro_setup(hi2c);


    printf("Begin IMU_INIT()\n");
    IMU_Init();

    return (status == 0) ? IRS_STATUS_OK : IRS_STATUS_ERROR;

}