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
#include "task.h"

cap_ctrl_data_t cap_ctrl_data;

void cap_ctrl_task(void const * argument)
{
    Cap_Pid_Init();
    Cap_Ctrl_Init();
while (1)
{
    Cap_Ctrl();
    Power_LED_ctrl();
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
    fp32 cap_pid_parm[6] = {CAP_PID_KP,CAP_PID_KI,CAP_PID_KD,CAP_PID_MAX_IOUT,CAP_PID_MAX_OUT,CAP_PID_MMAX_OUT};
    Pid_Init(PID_SPEED,cap_pid_parm,&INA226_Data_bus.PowerW,&cap_data.power, 0 , &cap_ctrl_data);
    Pid_clear();
}

/**
 * @brief 电容控制初始化
 * 
 */
void Cap_Ctrl_Init(void)
{
    //开启充电
    Cap_Charge_On();
    //开启升压模块
    Cap_DisCharge_On();
    //初始化模式
    cap_ctrl_data.CAP_MODE = CAP_MODE_CHARGE;
    //初始化功率控制
    cap_ctrl_data.duty_cycle = 80;
    //低功率充电
    __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_1,cap_ctrl_data.duty_cycle);
    HAL_Delay(20000);
    //系统初始化完成
    System_LED_Ready();

    cap_data.power = 80;
}

/**
 * @brief 总控制函数
 * 
 */
void Cap_Ctrl(void)
{
    //获取pid运算结果
    cap_ctrl_data.duty_cycle = Pid_calc(); 
    //控制充电功率
    __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_1,cap_ctrl_data.duty_cycle);
    //计算电容电量
    cap_ctrl_data.cap_electricity = 0.5*5*INA226_Data_cap.BusV*INA226_Data_cap.BusV;
    //计算抖动电量
    cap_ctrl_data.CAP_SHAKE_DATA = abs(cap_ctrl_data.cap_electricity - cap_ctrl_data.last_cap_electricity);
    //赋值上一次的电量
    cap_ctrl_data.last_cap_electricity = cap_ctrl_data.cap_electricity;
    //计算剩余电源电量百分比
    cap_ctrl_data.residue_electricity = ((INA226_Data_cap.BusV - CAP_LOW_V) / (INA226_Data_bus.BusV - CAP_LOW_V) * 100);
    //输出功率大于210W时关闭升压模块
    // if(INA226_Data_out.PowerW > 210)
    // {
    //     vTaskDelay(3500);
    //     Cap_DisCharge_Off;
    // }

    //手动模式切换
    // if((cap_data.boom == CAP_MODE_USER_DISCHARGE) && (cap_ctrl_data.cap_electricity > CAP_LOW_ELECTRICITY))
    // {
    //     can_cmd_cap_data(INA226_Data_bus.BusV,cap_ctrl_data.cap_electricity,CAP_MODE_USER_DISCHARGE);
    //     //开启放电
    //     Cap_DisCharge_On();
    //     cap_ctrl_data.CAP_MODE = CAP_MODE_USER_DISCHARGE;
    // }

    // else if(cap_ctrl_data.cap_electricity <= CAP_LOW_ELECTRICITY || (cap_data.boom == CAP_MODE_CHARGE && cap_ctrl_data.CAP_MODE == CAP_MODE_USER_DISCHARGE))
    // {
    //     // 如果电容电量过低！
    //     // 关闭放电
    //     Cap_DisCharge_Off();
    //     cap_ctrl_data.CAP_MODE = CAP_MODE_CHARGE;
    // } 

    //自动模式切换
    // if ((cap_ctrl_data.CAP_MODE == CAP_MODE_CHARGE) && (INA226_Data_cap.BusV > INA226_Data_bus.BusV - 1.0))
    // {
    //     //当电容电量足够的时候开启升压模块
    //     //Cap_Charge_Off();
    //     Cap_DisCharge_On();
    //     cap_ctrl_data.CAP_MODE = CAP_MODE_DISCHARGE;
    // } else if((cap_ctrl_data.CAP_MODE == CAP_MODE_DISCHARGE) && (INA226_Data_cap.BusV < 13.0))
    // {
    //     Cap_Charge_On();
    //     //当电容电量低的时候关闭升压模块，同时通过can发送数据使底盘降速
    //     //can_cmd_cap_data(INA226_Data_bus.BusV,cap_ctrl_data.cap_electricity,CAP_MODE_CHARGE);
    //     //Cap_DisCharge_Off();
    //     //cap_ctrl_data.CAP_MODE = CAP_MODE_CHARGE;
    // }
    // else
    // {
    //     Cap_Charge_On();
    //     Cap_DisCharge_On();
    // }

    /*
    //模式切换 当处于充电模式并且电容电量变化小于一定值时判断进入自动超电模式
    if ((cap_ctrl_data.CAP_MODE == CAP_MODE_CHARGE) && (cap_ctrl_data.CAP_SHAKE_DATA < CAP_BAT) && INA226_Data_bus.PowerW > cap_data.power)
    {
        Cap_DisCharge_On();
        cap_ctrl_data.CAP_MODE = CAP_MODE_DISCHARGE;
    } else if((cap_ctrl_data.CAP_MODE == CAP_MODE_DISCHARGE) && (cap_ctrl_data.CAP_SHAKE_DATA < CAP_BAT) && INA226_Data_bus.PowerW < cap_data.power)
    {
        Cap_DisCharge_Off();
        cap_ctrl_data.CAP_MODE = CAP_MODE_CHARGE;
    }
    */
}

void Power_LED_ctrl(void)
{
    if(INA226_Data_cap.BusV > INA226_Data_bus.BusV - 1.0)
    {
        Cap_Electricity_LED_High();
    }else if (INA226_Data_cap.BusV < 12.0)
    {
        Cap_Electricity_LED_Low();
    }else
    {
        Cap_Electricity_LED_Normal();
    }
}
