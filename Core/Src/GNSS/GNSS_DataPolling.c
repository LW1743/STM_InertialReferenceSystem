//
// Created by lukas-wiener on 12/30/25.
//

#include "GNSS_DataPolling.h"

static uint8_t rx_buffer[64];
static GNSSParser_Data_t GNSSParser_Data;

void GNSS_setup(UART_HandleTypeDef *huart) {
    HAL_UART_Receive_DMA(huart, rx_buffer, sizeof(rx_buffer));
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    UNUSED(huart);
    GNSS_parseData();
}

void GNSS_parseData() {
    GNSS_PARSER_ParseMsg(&GNSSParser_Data, GPGGA, rx_buffer);
}

void GNSS_getData(Vector3D *v) {
    v->x = GNSSParser_Data.gpgga_data.xyz.lat;
    v->y = GNSSParser_Data.gpgga_data.xyz.lon;
    v->z = GNSSParser_Data.gpgga_data.xyz.alt;
}

GNSS_Status GNSS_getStatus() {
    return (GNSSParser_Data.gpgga_data.sats > 2) ? GNSS_ALIGN : GNSS_INITIALIZING;
}

