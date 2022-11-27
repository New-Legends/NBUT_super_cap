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

void Cap_DisCharge_On(void);
void Cap_DisCharge_Off(void);

#endif
