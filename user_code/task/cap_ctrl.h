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
#include "pid.h"
#include "bsp_ina226.h"
#include "can_receive.h"

#define CAP_PID_KP 10.0f
#define CAP_PID_KI 0.0f
#define CAP_PID_KD 0.0f
#define CAP_PID_MAX_IOUT 800.0f
#define CAP_PID_MAX_OUT 1000.0f

void Cap_DisCharge_On(void);
void Cap_DisCharge_Off(void);

void Cap_Pid_Init(void);
#endif
