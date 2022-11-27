/**
 * @file can_receive.h
 * @author NBUT NJY
 * @brief 
 * @version 0.1
 * @date 2022-11-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef CAN_RECEIVE_H
#define CAN_RECEIVE_H

#include "can.h"
#include "bsp_can.h"
#include "main.h"
#include "struct_typedef.h"

extern CAN_HandleTypeDef hcan1;

#define CAP_CAN hcan1
#define CAP_ID 0x401

CAN_TxHeaderTypeDef can_tx_message;
uint8_t can_send_data[8];
//超电--控制板数据(BOOM 代表爆炸)
typedef struct 
{
    uint16_t power; //从控制板获取的功率
    uint16_t power_buffer;//缓冲功率
    uint16_t boom;//是否开启超电
};

//超电控制板返回的数据
typedef struct 
{
    uint16_t bat_v;//电池电压
    uint16_t cap_energy;//电容剩余的能量
};

//初始化函数
void can_Init(void);


//发送函数
void can_cmd_cap_data(int16_t bat_v,int16_t cap_energy);

#endif
