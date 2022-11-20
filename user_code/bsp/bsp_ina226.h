#ifndef BSP_INA226_H
#define BSP_INA226_H



/*-----------------------他♂的地址--------------------------*/

//===基础地址
#define INA226_ADDR1	    0x80
//===配置寄存区--[0x4127]
#define CONFIGURATION_REG   0x00
//===采样电阻上的压降---[0x00000],满量程是81.92mV,最小单位是2.5uV
#define SHUNT_VOLTAGE_REG   0x01
//===总线电压---[0x00000],满量程是40.96V,最小单位是1.25mV
#define BUS_VOLTAGE_REG     0x02
//===功率寄存器---[0x00000]
#define POWER_REG           0x03
//===电流寄存器---[0x00000]
#define CURRENT_REG         0x04
//===校准寄存器---[0x00000]
#define CALIBRATION_REG     0x05
//===功能控制寄存器---[0x00000]
#define MASK_ENABLE_REG     0x06
//===设置的报警阈值---[0x00000]
#define ALERT_LIMIT_REG     0x07
//===制造商ID---[0x5449]
#define MANUFACTURER_ID_REG 0xFE
//===设备ID---[0x2260]
#define DIE_ID_REG          0xFF

/*-----------------------他♂的地址--------------------------*/
#endif
