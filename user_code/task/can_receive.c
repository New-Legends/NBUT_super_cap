/**
 * @file can_receive.c
 * @author NBUT NJY
 * @brief 
 * @version 0.1
 * @date 2022-11-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "can_receive.h"

/**
 * @brief CAN通讯初始化
 * 
 */
void can_Init()
{
    can_filter_init();
}

/**
 * @brief 超电控制板can发送函数
 * 
 * @param bat_v 电池电压
 * @param cap_energy 超电剩余电能
 */
void can_cmd_cap_data(int16_t bat_v,int16_t cap_energy)
{
    uint32_t send_mail_box;
    can_tx_message.StdId = CAP_ID;
    can_tx_message.IDE = CAN_ID_STD;
    can_tx_message.RTR = CAN_RTR_DATA;
    can_tx_message.DLC = 0x08;
    can_send_data[0] = bat_v >> 8;
    can_send_data[1] = bat_v;
    can_send_data[2] = cap_energy >> 8;
    can_send_data[3] = cap_energy;
    can_send_data[4] = 0;
    can_send_data[5] = 0;
    can_send_data[6] = 0;
    can_send_data[7] = 0;

    HAL_CAN_AddTxMessage(&CAP_CAN, &can_tx_message, can_send_data, &send_mail_box);
}

