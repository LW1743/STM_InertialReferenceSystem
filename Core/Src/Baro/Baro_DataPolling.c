//
// Created by lukas-wiener on 12/30/25.
//
#include "Baro_DataPolling.h"




//variable defines
static lps22df_data_t data;
static stmdev_ctx_t dev_ctx;

//Function Define
static int32_t platform_write(void *handle, uint8_t reg, const uint8_t *bufp, uint16_t len);
static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len);
static void platform_delay(uint32_t ms);

//Magic functions from example
void setupBaroDataPolling(I2C_HandleTypeDef *hi2c) {
  lps22df_pin_int_route_t int_route;
  lps22df_bus_mode_t bus_mode;
  lps22df_id_t id;
  lps22df_md_t md;
  int ret;

  /* Initialize mems driver interface */
  dev_ctx.write_reg = platform_write;
  dev_ctx.read_reg = platform_read;
  dev_ctx.mdelay = platform_delay;
  dev_ctx.handle = hi2c;

  /* Check device ID */
  lps22df_id_get(&dev_ctx, &id);
  if (id.whoami != LPS22DF_ID)
    printf("LPS22DF not found!\n");

  /* Boot device */
  ret = lps22df_init_set(&dev_ctx, LPS22DF_BOOT);
  if (ret != 0)
    printf("LPS22DF not booting!\n");

  /* Reset device */
  ret = lps22df_init_set(&dev_ctx, LPS22DF_RESET);
  if (ret != 0)
    printf("LPS22DF not resetting!\n");

  /* Set bdu and if_inc recommended for driver usage */
  lps22df_init_set(&dev_ctx, LPS22DF_DRV_RDY);

  /* Select bus interface */
  bus_mode.filter = LPS22DF_FILTER_AUTO;
  bus_mode.interface = LPS22DF_SEL_BY_HW;
  lps22df_bus_mode_set(&dev_ctx, &bus_mode);

  /* Set Output Data Rate */
  md.odr = LPS22DF_200Hz;
  md.avg = LPS22DF_16_AVG;
  md.lpf = LPS22DF_LPF_ODR_DIV_4;
  lps22df_mode_set(&dev_ctx, &md);

  /* Configure inerrupt pins */
  lps22df_pin_int_route_get(&dev_ctx, &int_route);
  int_route.drdy_pres   = PROPERTY_DISABLE;
  lps22df_pin_int_route_set(&dev_ctx, &int_route);
}

void Baro_readDataPolling(void) {

  lps22df_all_sources_t all_sources;

  lps22df_all_sources_get(&dev_ctx, &all_sources);
  if ( all_sources.drdy_pres | all_sources.drdy_temp ) {
    lps22df_data_get(&dev_ctx, &data);
  }

}

double getBaroData(void) {
  return data.pressure.hpa;
}



static int32_t platform_write(void *handle, uint8_t reg, const uint8_t *bufp, uint16_t len)
{
  HAL_I2C_Mem_Write(handle, LPS22DF_I2C_ADD_H, reg, I2C_MEMADD_SIZE_8BIT, (uint8_t*) bufp, len, 1000);
  return 0;
}

static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len)
{
  HAL_I2C_Mem_Read(handle, LPS22DF_I2C_ADD_H, reg, I2C_MEMADD_SIZE_8BIT, bufp, len, 1000);

  return 0;
}

static void platform_delay(uint32_t ms)
{
  HAL_Delay(ms);
}
