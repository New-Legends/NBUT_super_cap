/**
 * @file bsp_LM5106.c
 * @author NJY
 * @brief 
 * @version 0.1
 * @date 2022-11-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "bsp_LM5106.h"

void CAP_CHARGE_ON(void)
{
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_SET);
}

void CAP_CHARGE_OFF(void)
{
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_RESET);
}
