//
// Created by lukas-wiener on 12/29/25.
//

#include "Mag_DataPolling.h"

#define    BOOT_TIME        20 //ms


/* Private variables ---------------------------------------------------------*/
static I2C_HandleTypeDef *SENSOR_BUS;
static stmdev_ctx_t dev_ctx;

static int16_t data_raw_magnetic[3];
static int16_t data_raw_temperature;
static float_t magnetic_mG[3];
static float_t temperature_degC;
static uint8_t whoamI, rst;

/* Private functions ---------------------------------------------------------*/

static int32_t platform_write(void *handle, uint8_t reg, const uint8_t *bufp, uint16_t len);
static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len);
static void platform_delay(uint32_t ms);

Mag_STATUS Mag_setup(I2C_HandleTypeDef *hi2c) {

  /* Initialize mems driver interface */
  dev_ctx.write_reg = platform_write;
  dev_ctx.read_reg = platform_read;
  dev_ctx.mdelay = platform_delay;
  dev_ctx.handle = hi2c;


  /* Wait sensor boot time */
  platform_delay(BOOT_TIME);

  /* Check device ID */
  lis2mdl_device_id_get(&dev_ctx, &whoamI);

  if (whoamI != LIS2MDL_ID){
      printf("LIS2MDL: Device not found");
      return Mag_STATUS_ERROR;
  }

  /* Restore default configuration */
  lis2mdl_reset_set(&dev_ctx, PROPERTY_ENABLE);

  do {
    lis2mdl_reset_get(&dev_ctx, &rst);
  } while (rst);

  /* Enable Block Data Update */
  lis2mdl_block_data_update_set(&dev_ctx, PROPERTY_ENABLE);
  /* Set Output Data Rate */
  lis2mdl_data_rate_set(&dev_ctx, LIS2MDL_ODR_100Hz);
  /* Set / Reset sensor mode */
  lis2mdl_set_rst_mode_set(&dev_ctx, LIS2MDL_SENS_OFF_CANC_EVERY_ODR);
  /* Enable temperature compensation */
  lis2mdl_offset_temp_comp_set(&dev_ctx, PROPERTY_ENABLE);
  /* Set device in continuous mode */
  lis2mdl_operating_mode_set(&dev_ctx, LIS2MDL_CONTINUOUS_MODE);

  uint8_t reg;

  while (!reg) {
    lis2mdl_mag_data_ready_get(&dev_ctx, &reg);
  }

  return Mag_STATUS_OK;
}

void Mag_readDataPolling(void) {
  uint8_t reg;
  /* Wait for new available data sample */
  lis2mdl_mag_data_ready_get(&dev_ctx, &reg);

  if (reg) {
    /* Read magnetic field data */
    memset(data_raw_magnetic, 0x00, 3 * sizeof(int16_t));
    lis2mdl_magnetic_raw_get(&dev_ctx, data_raw_magnetic);
    magnetic_mG[0] = lis2mdl_from_lsb_to_mgauss(data_raw_magnetic[0]);
    magnetic_mG[1] = lis2mdl_from_lsb_to_mgauss(data_raw_magnetic[1]);
    magnetic_mG[2] = lis2mdl_from_lsb_to_mgauss(data_raw_magnetic[2]);

    /* Read temperature data */
    memset(&data_raw_temperature, 0x00, sizeof(int16_t));
    lis2mdl_temperature_raw_get(&dev_ctx, &data_raw_temperature);
    temperature_degC = lis2mdl_from_lsb_to_celsius(data_raw_temperature);
  }

}

void Mag_getData(Vector3D *magVector) {
  magVector->x = magnetic_mG[0];
  magVector->y = magnetic_mG[1];
  magVector->z = magnetic_mG[2];
}

static int32_t platform_write(void *handle, uint8_t reg, const uint8_t *bufp, uint16_t len)
{
  reg |= 0x80;
  HAL_I2C_Mem_Write(handle, LIS2MDL_I2C_ADD, reg, I2C_MEMADD_SIZE_8BIT, (uint8_t*) bufp, len, 1000);

  return 0;
}

static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len)
{
  reg |= 0x80;
  HAL_I2C_Mem_Read(handle, LIS2MDL_I2C_ADD, reg, I2C_MEMADD_SIZE_8BIT, bufp, len, 1000);
  return 0;
}

static void platform_delay(uint32_t ms)
{
  HAL_Delay(ms);
}