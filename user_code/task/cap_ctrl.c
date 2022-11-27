/**
 * @file cap_ctrl.c
 * @author NBUT NJY
 * @brief 
 * @version 0.1
 * @date 2022-11-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "cap_ctrl.h"


void cap_ctrl_task(void const * argument)
{
while (1)
{
    __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_1,900);
	Cap_DisCharge_On();
    HAL_Delay(5000);
    Cap_DisCharge_Off();
    HAL_Delay(5000);
}
}

/**
 * @brief 超电开始放电
 * 
 */
void Cap_DisCharge_On(void)
{
    Cap_DisCharge_LED_On();
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,GPIO_PIN_SET);
}

/**
 * @brief 超电停止放电
 * 
 */
void Cap_DisCharge_Off(void)
{
    Cap_DisCharge_LED_Off();
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,GPIO_PIN_RESET);
}
