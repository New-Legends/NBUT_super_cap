/**
 * @file bsp_led.c
 * @author NBUT NJY
 * @brief 
 * @version 0.1
 * @date 2022-11-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "bsp_led.h"
#include "struct_typedef.h"

/**
 * @brief LED初始化
 * 
 */
void LED_Init()
{
    System_LED_UnReady();
    Cap_Charge_LED_Off();
    Cap_DisCharge_LED_Off();
    Cap_Electricity_LED_Low();
}

/**
 * @brief 点亮初始化完成LED
 * 
 */
void System_LED_Ready(void)
{
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_SET);
}

/**
 * @brief 初始化未完成
 * 
 */
void System_LED_UnReady(void)
{
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_RESET);
}

/**
 * @brief 点亮充电指示灯
 * 
 */
void Cap_Charge_LED_On(void)
{
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_SET);
}

/**
 * @brief 关闭充电指示灯
 * 
 */
void Cap_Charge_LED_Off(void)
{
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_RESET);
}

/**
 * @brief 点亮电容放电指示灯
 * 
 */
void Cap_DisCharge_LED_On(void)
{
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
}

/**
 * @brief 关闭电容放电指示灯
 * 
 */
void Cap_DisCharge_LED_Off(void)
{
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
}

/**
 * @brief 电容高电压指示灯
 * 
 */
void Cap_Electricity_LED_High(void)
{
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);
}
/**
 * @brief 电容中等电压指示灯
 * 
 */
void Cap_Electricity_LED_Normal(void)
{
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);
}

/**
 * @brief 电容低电量指示灯
 * 
 */
void Cap_Electricity_LED_Low(void)
{
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_SET);
}












































































