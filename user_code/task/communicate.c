/**
 * @file communicate.c
 * @author NBUT NJY
 * @brief 
 * @version 0.1
 * @date 2022-11-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "communicate.h"
#include "cap_ctrl.h"

void communicate_task(void const * argument)
{
    can_Init();
    while (1)
    {
    INA226_updata();
    can_cmd_cap_data((uint16_t)(INA226_Data_cap.BusV * 100),(uint16_t)(cap_ctrl_data.residue_electricity * 100),cap_ctrl_data.CAP_MODE,(uint16_t)(INA226_Data_bus.BusV * 100));
    }
}

/**
* @brief          hal库CAN回调函数,接收电机数据
* @param[in]      hcan:CAN句柄指针
* @retval         none
*/
	CAN_RxHeaderTypeDef rx_header;
	uint8_t rx_data[8];
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{

	HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_header, rx_data);
    switch (rx_header.StdId)
    {
		case CAP_ID:
			get_can_data(rx_data);
			break;
    default:
    {
			break;
    }
    }
}
