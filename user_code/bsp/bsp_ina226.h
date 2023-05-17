/**
 * @file bsp_ina226.h
 * @author NJY
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef BSP_INA226_H
#define BSP_INA226_H

#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_i2c.h"//根据芯片型号，自主更改
#include "struct_typedef.h"
#include "main.h"

#ifndef INA226_ADDRESS
#define INA226_ADDRESS 0x80
#endif

#ifndef OUT_INA226_ADDRESS
#define OUT_INA226_ADDRESS 0x82
#endif

#define INA226_CALIB_VAL 1024
#define INA226_CURRENTLSB 0.5F // mA/bit
#define INA226_CURRENTLSB_INV 1/INA226_CURRENTLSB // bit/mA
#define INA226_POWERLSB_INV 1/(INA226_CURRENTLSB*25) // bit/mW
#define INA226_I2CTIMEOUT 10

#define IAN226_ADDRESS_S 0x81
#define INA226_CONFIG 0x00 // 配置寄存器
#define INA226_SHUNTV 0x01 // 检测电阻电压
#define INA226_BUSV 0x02 // 总线电压
#define INA226_POWER 0x03 // 功率
#define INA226_CURRENT 0x04 // 电流
#define INA226_CALIB 0x05 // 校准
#define INA226_MASK 0x06 // 报警
#define INA226_ALERTL 0x07 // 报警
#define INA226_MANUF_ID 0xFE // 厂商
#define INA226_DIE_ID 0xFF // 芯片ID

#define INA226_MODE_POWER_DOWN (0<<0) // 掉电
#define INA226_MODE_TRIG_SHUNT_VOLTAGE (1<<0) // Shunt Voltage, Triggered
#define INA226_MODE_TRIG_BUS_VOLTAGE (2<<0) // Bus Voltage, Triggered
#define INA226_MODE_TRIG_SHUNT_AND_BUS (3<<0) // Shunt and Bus, Triggered
#define INA226_MODE_POWER_DOWN2 (4<<0) // Power-Down
#define INA226_MODE_CONT_SHUNT_VOLTAGE (5<<0) // Shunt Voltage, Continuous
#define INA226_MODE_CONT_BUS_VOLTAGE (6<<0) // Bus Voltage, Continuous
#define INA226_MODE_CONT_SHUNT_AND_BUS (7<<0) // Shunt and Bus, Continuous

//配置采样电压转换的时间
#define INA226_VSH_140uS (0<<3)
#define INA226_VSH_204uS (1<<3)
#define INA226_VSH_332uS (2<<3)
#define INA226_VSH_588uS (3<<3)
#define INA226_VSH_1100uS (4<<3)
#define INA226_VSH_2116uS (5<<3)
#define INA226_VSH_4156uS (6<<3)
#define INA226_VSH_8244uS (7<<3)

// Bus Voltage Conversion Time (VBUS CT Bit Settings[6-8])
#define INA226_VBUS_140uS (0<<6)
#define INA226_VBUS_204uS (1<<6)
#define INA226_VBUS_332uS (2<<6)
#define INA226_VBUS_588uS (3<<6)
#define INA226_VBUS_1100uS (4<<6)
#define INA226_VBUS_2116uS (5<<6)
#define INA226_VBUS_4156uS (6<<6)
#define INA226_VBUS_8244uS (7<<6)

// Averaging Mode (AVG Bit Settings[9-11])
#define INA226_AVG_1 (0<<9)
#define INA226_AVG_4 (1<<9)
#define INA226_AVG_16 (2<<9)
#define INA226_AVG_64 (3<<9)
#define INA226_AVG_128 (4<<9)
#define INA226_AVG_256 (5<<9)
#define INA226_AVG_512 (6<<9)
#define INA226_AVG_1024 (7<<9)

// Reset Bit (RST bit [15])
#define INA226_RESET_ACTIVE (1<<15)
#define INA226_RESET_INACTIVE (0<<15)

// Mask/Enable Register
#define INA226_MER_SOL (1<<15) // Shunt Voltage Over-Voltage
#define INA226_MER_SUL (1<<14) // Shunt Voltage Under-Voltage
#define INA226_MER_BOL (1<<13) // Bus Voltagee Over-Voltage
#define INA226_MER_BUL (1<<12) // Bus Voltage Under-Voltage
#define INA226_MER_POL (1<<11) // Power Over-Limit
#define INA226_MER_CNVR (1<<10) // Conversion Ready
#define INA226_MER_AFF (1<<4) // Alert Function Flag
#define INA226_MER_CVRF (1<<3) // Conversion Ready Flag
#define INA226_MER_OVF (1<<2) // Math Overflow Flag
#define INA226_MER_APOL (1<<1) // Alert Polarity Bit
#define INA226_MER_LEN (1<<0) // Alert Latch Enable

#define INA226_MANUF_ID_DEFAULT 0x5449
#define INA226_DIE_ID_DEFAULT 0x2260

//分压电阻
#define INA226_SAMPLE_RES_MR             5000   //b 5300

#define INA226_SAMPLE_RES_MR_TOTAL       5000

#define INA226_RANG_CURRENT_MA_MAX		 6000
//===INA226的电流量程每BIT对应电流值，单位是微安
#define INA226_RANG_CURRENT_UA_BIT       (uint16_t)( INA226_RANG_CURRENT_MA_MAX*1000/(1<<15) )//1<<15=2的15次幂 305.1μA/位 这里选择相近的500μA/位，用分辨率换取计算速度

#define INA226_CALIB_REG_DEFAULT         (uint16_t)( 5120*1000/(INA226_RANG_CURRENT_UA_BIT*INA226_SAMPLE_RES_MR) )//1024
//INA226数据
typedef struct
{    
    // uint16_t msgCFGReg;//---配置寄存器
	// uint16_t msgMaskReg;//---功能配置寄存器
	// uint16_t msgShuntReg;//---采样电压寄存器
	// uint16_t msgBusVReg;//---总线电压寄存器
	// uint16_t msgPowerReg;//---功率寄存器
	// uint16_t msgCurrentReg;//---采样电流寄存器
	// uint16_t msgCalibReg;//---校准寄存器
	double BusV;//---总线电压，单位毫伏
	double ShuntmV;//---采样电阻电压,单位微伏
	double ShuntmA;//---采样电阻电流，单位安      算出来的
	fp32 PowerW;//---负载的功耗，单位瓦 
	double PowerW2;  // 不知道怎么来的         算出来的
	//uint16_t Power_pid;
} INA226_Data_t;

extern INA226_Data_t INA226_Data_bus;
extern INA226_Data_t INA226_Data_cap;

void INA226_Init(void);
void INA226_updata(void);

float INA226_getBusV(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress);
float INA226_getCurrent(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress);
float INA226_getPower(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress);

uint8_t INA226_setConfig(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress, uint16_t ConfigWord);
uint16_t INA226_getConfig(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress);
uint16_t INA226_getShuntV(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress);
uint16_t INA226_getBusVReg(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress);
uint16_t INA226_getPowerReg(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress);
uint8_t INA226_setCalibrationReg(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress, uint16_t ConfigWord);
uint16_t INA226_getCalibrationReg(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress);
uint16_t INA226_getCurrentReg(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress);
uint16_t INA226_getManufID(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress);
uint16_t INA226_getDieID(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress);
uint8_t INA226_setMaskEnable(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress, uint16_t ConfigWord);
uint16_t INA226_getMaskEnable(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress);
uint8_t INA226_setAlertLimit(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress, uint16_t ConfigWord);
uint16_t INA226_getAlertLimit(I2C_HandleTypeDef *I2CHandler, uint16_t DevAddress);

extern INA226_Data_t INA226_Data_bus;
extern INA226_Data_t INA226_Data_cap;

#endif
