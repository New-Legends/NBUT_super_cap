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

cap_data_t cap_data;

/**
 * @brief CAN通讯初始化
 * 
 */
void can_Init()
{
    can_filter_init();
}

CAN_TxHeaderTypeDef can_tx_message;
uint8_t can_send_data[8];

/**
 * @brief 超电控制板can发送函数
 * 
 * @param bat_v 电池电压
 * @param cap_energy 超电剩余电能
 * @param boom 超电状态
 */
void can_cmd_cap_data(uint16_t bat_v,uint16_t cap_energy,uint8_t boom)
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
    can_send_data[4] = boom;
    can_send_data[5] = 0;
    can_send_data[6] = 0;
    can_send_data[7] = 0;

    HAL_CAN_AddTxMessage(&CAP_CAN, &can_tx_message, can_send_data, &send_mail_box);
}

/**
 * @brief Get the can data object
 * 
 * @param data 
 */
void get_can_data(uint8_t data[8])
{
    cap_data.power = (uint16_t)(data[0] << 8 | data[1]) * 1.0;
    cap_data.power_buffer = (uint16_t)(data[2] << 8 | data[3]);
    cap_data.boom = data[4];
}
