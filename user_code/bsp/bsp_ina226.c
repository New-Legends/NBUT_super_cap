/**
 * @file bsp_ina226.c
 * @author NJY
 * @brief
 * @version 0.1
 * @date 2022-11-22
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "bsp_ina226.h"
#include "i2c.h"
#include "can_receive.h"

INA226_Data_t INA226_Data_bus;
INA226_Data_t INA226_Data_cap;
INA226_Data_t INA226_Data_out;

/**
 * @brief 初始化INA226
 *
 */
void INA226_Init(void)
{

    INA226_setConfig(&hi2c2, INA226_ADDRESS, 0x4000 | INA226_AVG_1 | //求平均次数1
                                                 INA226_VBUS_140uS | //总线电压采集时间2116us
                                                 INA226_VSH_2116uS | //分流电压采集时间2116us
                                                 INA226_MODE_CONT_SHUNT_AND_BUS);
    INA226_setCalibrationReg(&hi2c2, INA226_ADDRESS, INA226_CALIB_REG_DEFAULT);
    INA226_setMaskEnable(&hi2c2, INA226_ADDRESS, INA226_MER_CNVR);

    INA226_setConfig(&hi2c1, INA226_ADDRESS, 0x4000 | INA226_AVG_1 |  //求平均次数1
                                                 INA226_VBUS_2116uS | //总线电压采集时间2116us
                                                 INA226_VSH_2116uS |  //分流电压采集时间2116us
                                                 INA226_MODE_CONT_SHUNT_AND_BUS);
    INA226_setCalibrationReg(&hi2c1, INA226_ADDRESS, INA226_CALIB_REG_DEFAULT);
    INA226_setMaskEnable(&hi2c1, INA226_ADDRESS, INA226_MER_CNVR);

    INA226_setConfig(&hi2c1, OUT_INA226_ADDRESS, 0x4000 | INA226_AVG_1 |  //求平均次数1
                                                 INA226_VBUS_2116uS | //总线电压采集时间2116us
                                                 INA226_VSH_2116uS |  //分流电压采集时间2116us
                                                 INA226_MODE_CONT_SHUNT_AND_BUS);
    INA226_setCalibrationReg(&hi2c1, OUT_INA226_ADDRESS, INA226_CALIB_REG_DEFAULT);
    INA226_setMaskEnable(&hi2c1, OUT_INA226_ADDRESS, INA226_MER_CNVR);
}

/**
 * @brief INA226传感器数据更新
 *
 */
void INA226_updata(void)
{
    //电池数据获取
    INA226_Data_bus.BusV = 1.25 * INA226_getBusV(&hi2c1, INA226_ADDRESS) / 1000;
    INA226_Data_bus.ShuntmV = 2.5 * INA226_getShuntV(&hi2c1, INA226_ADDRESS) / 1000000;
    INA226_Data_bus.PowerW = (INA226_Data_bus.ShuntmV / 0.005) * INA226_Data_bus.BusV; // INA226_getPower(&hi2c1,INA226_ADDRESS);
    //INA226_Data_bus.Power_pid = (uint16_t)((INA226_Data_bus.PowerW / cap_data.power)*1000);
     INA226_Data_bus.ShuntmA = INA226_getCurrent(&hi2c1,INA226_ADDRESS);
    //超电数据获取
    INA226_Data_cap.BusV = 1.25 * INA226_getBusV(&hi2c2, INA226_ADDRESS)/1000;
    INA226_Data_cap.ShuntmV = 1.25 * INA226_getShuntV(&hi2c2, INA226_ADDRESS);
    INA226_Data_cap.PowerW = INA226_getPower(&hi2c2,INA226_ADDRESS);  //着可能是一条无用数据
    INA226_Data_cap.ShuntmA = INA226_getCurrent(&hi2c2,INA226_ADDRESS);
    //超电输出数据获取
    INA226_Data_out.BusV = 1.25 * INA226_getBusV(&hi2c1, INA226_ADDRESS) / 1000;
    INA226_Data_out.ShuntmV = 2.5 * INA226_getShuntV(&hi2c1, INA226_ADDRESS) / 1000000;
    INA226_Data_out.ShuntmA = INA226_getCurrent(&hi2c1,INA226_ADDRESS);
    //INA226_Data_out.PowerW = (INA226_Data_bus.ShuntmV / 0.005) * INA226_Data_bus.BusV;
    INA226_Data_out.PowerW = INA226_Data_out.ShuntmV * INA226_Data_out.ShuntmA;

}
/**
 * @brief 获取bus电压
 *
 * @param I2CHandler
 * @param DevAddress
 * @return float
 */
float INA226_getBusV(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress)
{
    return (INA226_getBusVReg(I2CHandler, DevAddress));
}

/**
 * @brief 获取bus电流
 *
 * @param I2CHandler
 * @param DevAddress
 * @return float
 */
float INA226_getCurrent(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress)
{
    return (INA226_getCurrentReg(I2CHandler, DevAddress) * INA226_CURRENTLSB_INV);
}

/**
 * @brief 获取功率
 *
 * @param I2CHandler
 * @param DevAddress
 * @return float
 */
float INA226_getPower(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress)
{
    return (INA226_getPowerReg(I2CHandler, DevAddress) * INA226_POWERLSB_INV);
}

/**
 * @brief 设置系统配置
 *
 * @param I2CHandler
 * @param DevAddress
 * @param ConfigWord
 * @return uint8_t
 */
uint8_t INA226_setConfig(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress, uint16_t ConfigWord)
{
    uint8_t SentTable[3];
    SentTable[0] = INA226_CONFIG;
    SentTable[1] = (uint8_t)(ConfigWord >> 8);
    SentTable[2] = (uint8_t)(ConfigWord & 0x00FF);
    return HAL_I2C_Master_Transmit(I2CHandler, DevAddress, SentTable, 2, INA226_I2CTIMEOUT);
}

/**
 * @brief 获取系统配置
 *
 * @param I2CHandler
 * @param DevAddress
 * @return uint16_t
 */
uint16_t INA226_getConfig(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress)
{
    uint8_t SentTable[1] = {INA226_CONFIG};
    uint8_t ReceivedTable[2];
    HAL_I2C_Master_Transmit(I2CHandler, DevAddress, SentTable, 1, INA226_I2CTIMEOUT);
    if (HAL_I2C_Master_Receive(I2CHandler, DevAddress, ReceivedTable, 2, INA226_I2CTIMEOUT) != HAL_OK)
        return 0xFF;
    else
        return ((uint16_t)ReceivedTable[0] << 8 | ReceivedTable[1]);
}

uint16_t INA226_getShuntV(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress)
{
    uint8_t SentTable[1] = {INA226_SHUNTV};
    uint8_t ReceivedTable[2];
    HAL_I2C_Master_Transmit(I2CHandler, DevAddress, SentTable, 1, INA226_I2CTIMEOUT);
    if (HAL_I2C_Master_Receive(I2CHandler, DevAddress, ReceivedTable, 2, INA226_I2CTIMEOUT) != HAL_OK)
        return 0xFF;
    else
        return ((uint16_t)ReceivedTable[0] << 8 | ReceivedTable[1]);
}

uint16_t INA226_getBusVReg(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress)
{
    uint8_t SentTable[1] = {INA226_BUSV};
    uint8_t ReceivedTable[2];
    HAL_I2C_Master_Transmit(I2CHandler, DevAddress, SentTable, 1, INA226_I2CTIMEOUT);
    if (HAL_I2C_Master_Receive(I2CHandler, DevAddress, ReceivedTable, 2, INA226_I2CTIMEOUT) != HAL_OK)
        return 0xFF;
    else
        return ((uint16_t)ReceivedTable[0] << 8 | ReceivedTable[1]);
}

uint8_t INA226_setCalibrationReg(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress, uint16_t ConfigWord)
{
    uint8_t SentTable[3];
    SentTable[0] = INA226_CALIB;
    SentTable[1] = (ConfigWord & 0xFF00) >> 8;
    SentTable[2] = (ConfigWord & 0x00FF);
    return HAL_I2C_Master_Transmit(I2CHandler, DevAddress, SentTable, 3, INA226_I2CTIMEOUT);
}

uint16_t INA226_getCalibrationReg(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress)
{
    uint8_t SentTable[1] = {INA226_CALIB};
    uint8_t ReceivedTable[2];
    HAL_I2C_Master_Transmit(I2CHandler, DevAddress, SentTable, 1, INA226_I2CTIMEOUT);
    if (HAL_I2C_Master_Receive(I2CHandler, DevAddress, ReceivedTable, 2, INA226_I2CTIMEOUT) != HAL_OK)
        return 0xFF;
    else
        return ((uint16_t)ReceivedTable[0] << 8 | ReceivedTable[1]);
}

uint16_t INA226_getPowerReg(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress)
{
    uint8_t SentTable[1] = {INA226_POWER};
    uint8_t ReceivedTable[2];
    HAL_I2C_Master_Transmit(I2CHandler, DevAddress, SentTable, 1, INA226_I2CTIMEOUT);
    if (HAL_I2C_Master_Receive(I2CHandler, DevAddress, ReceivedTable, 2, INA226_I2CTIMEOUT) != HAL_OK)
        return 0xFF;
    else
        return ((uint16_t)ReceivedTable[0] << 8 | ReceivedTable[1]);
}

uint16_t INA226_getCurrentReg(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress)
{
    uint8_t SentTable[1] = {INA226_CURRENT};
    uint8_t ReceivedTable[2];
    HAL_I2C_Master_Transmit(I2CHandler, DevAddress, SentTable, 1, INA226_I2CTIMEOUT);
    if (HAL_I2C_Master_Receive(I2CHandler, DevAddress, ReceivedTable, 2, INA226_I2CTIMEOUT) != HAL_OK)
        return 0xFF;
    else
        return ((uint16_t)ReceivedTable[0] << 8 | ReceivedTable[1]);
}

uint16_t INA226_getManufID(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress)
{
    uint8_t SentTable[1] = {INA226_MANUF_ID};
    uint8_t ReceivedTable[2];
    HAL_I2C_Master_Transmit(I2CHandler, DevAddress, SentTable, 1, INA226_I2CTIMEOUT);
    if (HAL_I2C_Master_Receive(I2CHandler, DevAddress, ReceivedTable, 2, INA226_I2CTIMEOUT) != HAL_OK)
        return 0xFF;
    else
        return ((uint16_t)ReceivedTable[0] << 8 | ReceivedTable[1]);
}

uint16_t INA226_getDieID(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress)
{
    uint8_t SentTable[1] = {INA226_DIE_ID};
    uint8_t ReceivedTable[2];
    HAL_I2C_Master_Transmit(I2CHandler, DevAddress, SentTable, 1, INA226_I2CTIMEOUT);
    if (HAL_I2C_Master_Receive(I2CHandler, DevAddress, ReceivedTable, 2, INA226_I2CTIMEOUT) != HAL_OK)
        return 0xFF;
    else
        return ((uint16_t)ReceivedTable[0] << 8 | ReceivedTable[1]);
}

uint8_t INA226_setMaskEnable(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress, uint16_t ConfigWord)
{
    uint8_t SentTable[3];
    SentTable[0] = INA226_MASK;
    SentTable[1] = (ConfigWord & 0xFF00) >> 8;
    SentTable[2] = (ConfigWord & 0x00FF);
    return HAL_I2C_Master_Transmit(I2CHandler, DevAddress, SentTable, 3, INA226_I2CTIMEOUT);
}

uint16_t INA226_getMaskEnable(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress)
{
    uint8_t SentTable[1] = {INA226_MASK};
    uint8_t ReceivedTable[2];
    HAL_I2C_Master_Transmit(I2CHandler, DevAddress, SentTable, 1, INA226_I2CTIMEOUT);
    if (HAL_I2C_Master_Receive(I2CHandler, DevAddress, ReceivedTable, 2, INA226_I2CTIMEOUT) != HAL_OK)
        return 0xFF;
    else
        return ((uint16_t)ReceivedTable[0] << 8 | ReceivedTable[1]);
}

uint8_t INA226_setAlertLimit(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress, uint16_t ConfigWord)
{
    uint8_t SentTable[3];
    SentTable[0] = INA226_ALERTL;
    SentTable[1] = (ConfigWord & 0xFF00) >> 8;
    SentTable[2] = (ConfigWord & 0x00FF);
    return HAL_I2C_Master_Transmit(I2CHandler, DevAddress, SentTable, 3, INA226_I2CTIMEOUT);
}

uint16_t INA226_getAlertLimit(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress)
{
    uint8_t SentTable[1] = {INA226_ALERTL};
    uint8_t ReceivedTable[2];
    HAL_I2C_Master_Transmit(I2CHandler, DevAddress, SentTable, 1, INA226_I2CTIMEOUT);
    if (HAL_I2C_Master_Receive(I2CHandler, DevAddress, ReceivedTable, 2, INA226_I2CTIMEOUT) != HAL_OK)
        return 0xFF;
    else
        return ((uint16_t)ReceivedTable[0] << 8 | ReceivedTable[1]);
}
