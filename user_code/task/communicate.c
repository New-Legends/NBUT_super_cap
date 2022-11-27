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
void communicate_task(void const * argument)
{

    while (1)
    {
    INA226_updata();
    }
}
