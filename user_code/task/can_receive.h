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

extern CAN_HandleTypeDef hcan;

#define CAP_CAN hcan
#define CAP_ID 0x401

//超电--控制板数据(BOOM 代表爆炸)
typedef struct 
{
    fp32 power; //从控制板获取的功率
    uint16_t power_buffer;//缓冲功率
    uint16_t power_pid;
    uint16_t boom;//是否开启超电
    uint16_t bat_v;//电池电压
    uint16_t cap_energy;//电容剩余的能量
}cap_data_t;

extern cap_data_t cap_data;

//初始化函数
void can_Init(void);

//发送函数
void can_cmd_cap_data(int16_t bat_v,int16_t cap_energy);

//接收函数
void get_can_data(uint8_t data[8]);

#endif
