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
#include "pid.h"

cap_ctrl_data_t cap_ctrl_data;

void cap_ctrl_task(void const * argument)
{
    Cap_Pid_Init();
    Cap_Ctrl_Init();
while (1)
{
    __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_1,0);
	Cap_DisCharge_On();
    HAL_Delay(2000);
    __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_1,1);
    Cap_DisCharge_Off();
    HAL_Delay(2000);
    __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_1,500);
    HAL_Delay(2000);
    __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_1,99);
    HAL_Delay(2000);
    __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_1,99.1);
    HAL_Delay(2000);
    __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_1,100);
    HAL_Delay(2000);

}
}

/**
 * @brief 返回绝对值
 * 
 * @param a 
 * @return fp32 
 */
fp32 abs(fp32 a)
{
    if(a > 0)
    {
        return a;
    }else
    {
        return -a;
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

/**
 * @brief 电容充电开
 * 
 */
void Cap_Charge_On(void)
{
    Cap_Charge_LED_On();
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_SET);
}

/**
 * @brief 电容充电关
 * 
 */
void Cap_Charge_Off(void)
{
    Cap_Charge_LED_Off();
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_RESET);
}

/**
 * @brief pid初始化
 * 
 */
void Cap_Pid_Init(void)
{
    fp32 cap_pid_parm[5] = {CAP_PID_KP,CAP_PID_KI,CAP_PID_KD,CAP_PID_MAX_IOUT,CAP_PID_MAX_OUT};
    Pid_Init(PID_SPEED,cap_pid_parm,&INA226_Data_bus.PowerW,&cap_data.power,0);
    Pid_clear();
}

void Cap_Ctrl_Init(void)
{
    Cap_Charge_On();
    Cap_DisCharge_Off();
    System_LED_Ready();
}

/**
 * @brief 总控制函数
 * 
 */
void Cap_Ctrl(void)
{
    //获取pid运算结果
    cap_ctrl_data.duty_cycle = (uint16_t)Pid_calc(); 
    //控制充电功率
    __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_1,cap_ctrl_data.duty_cycle);
    //计算电容电量
    cap_ctrl_data.cap_electricity = 0.5*5*INA226_Data_cap.BusV*INA226_Data_cap.BusV;
    //计算抖动电量
    cap_ctrl_data.CAP_SHAKE_DATA = abs(cap_ctrl_data.cap_electricity - cap_ctrl_data.last_cap_electricity);
    //赋值上一次的电量
    cap_ctrl_data.last_cap_electricity = cap_ctrl_data.cap_electricity;

}
