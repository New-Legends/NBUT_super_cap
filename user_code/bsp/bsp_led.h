/**
 * @file bsp_led.h
 * @author NBUT NJY
 * @brief 
 * @version 0.1
 * @date 2022-11-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef BSP_LED_H
#define BSP_LED_H
#include "main.h"
#include "gpio.h"
#include "struct_typedef.h"

void LED_Init(void);

//系统初始化指示灯
void System_LED_Ready(void);
void System_LED_UnReady(void);

//充电指示灯
void Cap_Charge_LED_On(void);
void Cap_Charge_LED_Off(void);

//放电指示灯
void Cap_DisCharge_LED_On(void);
void Cap_DisCharge_LED_Off(void);

//电容电量状态指示灯
void Cap_Electricity_LED_High(void);
void Cap_Electricity_LED_Normal(void);
void Cap_Electricity_LED_Low(void);
#endif
