/**
 * @file cap_ctrl.h
 * @author NBUT NJY
 * @brief
 * @version 0.1
 * @date 2022-11-26
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef CAP_CTRL_H
#define CAP_CTRL_H

#include "main.h"
#include "FreeRTOS.h"
#include "tim.h"
#include "bsp_led.h"
#include "bsp_ina226.h"
#include "can_receive.h"
#include "struct_typedef.h"

//充电pid
#define CAP_PID_KP 0.01f
#define CAP_PID_KI 0.0f
#define CAP_PID_KD 0.0f
#define CAP_PID_MAX_IOUT 200.0f
#define CAP_PID_MAX_OUT 980.0f
#define CAP_PID_MMAX_OUT 980.0f

//参数设置
#define CAP_SHAKE 10.0f //抖动电量
#define CAP_LOW_ELECTRICITY 400.0f //电容低电量
#define CAP_BAT 0.2f //电容满电电压与电池电压差
#define CAP_LOW_V 4.2 //电容最低电压

//模式切换
#define CAP_MODE_CHARGE 0          //充电模式
#define CAP_MODE_DISCHARGE 1       //自动超电模式
#define CAP_MODE_USER_DISCHARGE 2  //手动超电模式

//控制数据结构体
typedef struct 
{
    fp32 duty_cycle; //充电占空比
    fp32 cap_electricity; // 电容电量
    fp32 last_cap_electricity; //上一次电容容量
    fp32 CAP_SHAKE_DATA;       //电容电量抖动
    uint8_t CAP_MODE;      //电容模式
}cap_ctrl_data_t;

extern cap_ctrl_data_t cap_ctrl_data;

void Cap_DisCharge_On(void);
void Cap_DisCharge_Off(void);

void Cap_Pid_Init(void);
void Cap_Ctrl_Init(void);
void Cap_Ctrl(void);

void Power_LED_ctrl(void);
#endif
