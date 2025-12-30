//
// Created by lukas-wiener on 12/29/25.
//

#include "IMU_DataPolling.h"


//Private Defines
#define BOOT_TIME 10

//Private variables
static stmdev_ctx_t dev_ctx;
static int16_t data_raw_acceleration[3];
static int16_t data_raw_angular_rate[3];
static int16_t data_raw_temperature;
static double_t acceleration_mg[3];
static double_t angular_rate_mdps[3];
static double_t temperature_degC;

static int32_t platform_write(void *handle, uint8_t reg, const uint8_t *bufp, uint16_t len);
static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len);
static void platform_delay(uint32_t ms);


IMU_STATUS IMU_setup(I2C_HandleTypeDef *hi2c) {

  dev_ctx.write_reg = platform_write;
  dev_ctx.read_reg = platform_read;
  dev_ctx.mdelay = platform_delay;
  dev_ctx.handle = hi2c;

  /* Delay for stability */
  platform_delay(BOOT_TIME);

  /* Check if device found */
  uint8_t whoamI;
  lsm6dsv16x_device_id_get(&dev_ctx, &whoamI);

  if (whoamI != LSM6DSV16X_ID) {
    printf("LSM6DSV16X device not found\n");
    return IMU_STATUS_ERROR;
  }

  /* Restore default configuration */
  lsm6dsv16x_sw_por(&dev_ctx);

  /* Enable Block Data Update */
  lsm6dsv16x_block_data_update_set(&dev_ctx, PROPERTY_ENABLE);

  /* Set Output Data Rate.
   * Selected data rate have to be equal or greater with respect
   * with MLC data rate.
   */
  lsm6dsv16x_xl_data_rate_set(&dev_ctx, LSM6DSV16X_ODR_AT_7680Hz);
  lsm6dsv16x_gy_data_rate_set(&dev_ctx, LSM6DSV16X_ODR_AT_7680Hz);

  /* Set full scale */
  lsm6dsv16x_xl_full_scale_set(&dev_ctx, LSM6DSV16X_4g);
  lsm6dsv16x_gy_full_scale_set(&dev_ctx, LSM6DSV16X_2000dps);

  /* Configure filtering chain */
  lsm6dsv16x_filt_settling_mask_t filt_settling_mask;
  filt_settling_mask.drdy = PROPERTY_ENABLE;
  filt_settling_mask.irq_xl = PROPERTY_ENABLE;
  filt_settling_mask.irq_g = PROPERTY_ENABLE;
  lsm6dsv16x_filt_settling_mask_set(&dev_ctx, filt_settling_mask);
  lsm6dsv16x_filt_gy_lp1_set(&dev_ctx, PROPERTY_ENABLE);
  lsm6dsv16x_filt_gy_lp1_bandwidth_set(&dev_ctx, LSM6DSV16X_GY_ULTRA_LIGHT);
  lsm6dsv16x_filt_xl_lp2_set(&dev_ctx, PROPERTY_ENABLE);
  lsm6dsv16x_filt_xl_lp2_bandwidth_set(&dev_ctx, LSM6DSV16X_XL_STRONG);

  return IMU_STATUS_OK;
}

void IMU_readDataPolling(void) {
  lsm6dsv16x_data_ready_t drdy;

  /* Read output only if new xl value is available */
  lsm6dsv16x_flag_data_ready_get(&dev_ctx, &drdy);

  if (drdy.drdy_xl) {
    /* Read acceleration field data */
    memset(data_raw_acceleration, 0x00, 3 * sizeof(int16_t));
    lsm6dsv16x_acceleration_raw_get(&dev_ctx, data_raw_acceleration);
    acceleration_mg[0] =
      lsm6dsv16x_from_fs2_to_mg(data_raw_acceleration[0]);
    acceleration_mg[1] =
      lsm6dsv16x_from_fs2_to_mg(data_raw_acceleration[1]);
    acceleration_mg[2] =
      lsm6dsv16x_from_fs2_to_mg(data_raw_acceleration[2]);
  }

  /* Read output only if new xl value is available */
  if (drdy.drdy_gy) {
    /* Read angular rate field data */
    memset(data_raw_angular_rate, 0x00, 3 * sizeof(int16_t));
    lsm6dsv16x_angular_rate_raw_get(&dev_ctx, data_raw_angular_rate);
    angular_rate_mdps[0] =
      lsm6dsv16x_from_fs2000_to_mdps(data_raw_angular_rate[0]);
    angular_rate_mdps[1] =
      lsm6dsv16x_from_fs2000_to_mdps(data_raw_angular_rate[1]);
    angular_rate_mdps[2] =
      lsm6dsv16x_from_fs2000_to_mdps(data_raw_angular_rate[2]);
  }

  if (drdy.drdy_temp) {
    /* Read temperature data */
    memset(&data_raw_temperature, 0x00, sizeof(int16_t));
    lsm6dsv16x_temperature_raw_get(&dev_ctx, &data_raw_temperature);
    temperature_degC = lsm6dsv16x_from_lsb_to_celsius(
                         data_raw_temperature);
  }

}

void IMU_getAccelerationVector3D(Vector3D* accelerationVector) {
  accelerationVector->x = acceleration_mg[0];
  accelerationVector->y = acceleration_mg[1];
  accelerationVector->z = acceleration_mg[2];
}

void IMU_getAngularVelocityVector3D(Vector3D* angularVelocityVector) {
  angularVelocityVector->x = angular_rate_mdps[0]*2*M_PI;
  angularVelocityVector->y = angular_rate_mdps[1]*2*M_PI;
  angularVelocityVector->z = angular_rate_mdps[2]*2*M_PI;
}


static int32_t platform_write(void *handle, uint8_t reg, const uint8_t *bufp, uint16_t len)
{
  HAL_I2C_Mem_Write(handle, LSM6DSV16X_I2C_ADD_H, reg, I2C_MEMADD_SIZE_8BIT, (uint8_t*) bufp, len, 1000);
  return 0;
}

static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len)
{
  HAL_I2C_Mem_Read(handle, LSM6DSV16X_I2C_ADD_H, reg, I2C_MEMADD_SIZE_8BIT, bufp, len, 1000);
  return 0;
}

static void platform_delay(uint32_t ms)
{
  HAL_Delay(ms);
}