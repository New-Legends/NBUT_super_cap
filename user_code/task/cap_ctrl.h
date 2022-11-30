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
#define CAP_PID_KP 10.0f
#define CAP_PID_KI 0.0f
#define CAP_PID_KD 0.0f
#define CAP_PID_MAX_IOUT 800.0f
#define CAP_PID_MAX_OUT 999.0f

#define CAP_SHAKE 10.0f

//控制数据结构体
typedef struct 
{
    uint16_t duty_cycle; //充电占空比
    fp32 cap_electricity; // 电容电量
}cap_ctrl_data_t;

void Cap_DisCharge_On(void);
void Cap_DisCharge_Off(void);

void Cap_Pid_Init(void);
#endif
