#ifndef PID_H
#define PID_H

#include "struct_typedef.h"
#include "cap_ctrl.h"

#define PID_SPEED 0 //速度环
#define PID_ANGLE 1//角度环

typedef struct
{
    uint8_t mode;
    //PID 三参数
    fp32 Kp;
    fp32 Ki;
    fp32 Kd;

    fp32 max_iout; //最大积分输出
    fp32 max_out;  //最大输出


    fp32 *set;
    fp32 *ref;
    fp32 error;
    fp32 last_error;

    fp32 error_delta; //微分项,速度环下为error之间的差值,角度环下为陀螺仪角速度值

    fp32 out;
    uint16_t *In; //输入原值进行控制
    fp32 Pout;
    fp32 Iout;
    fp32 Dout;
} pid_data_t;

//PID初始化
void Pid_Init(uint8_t mode_, const fp32 *pid_parm, fp32 *ref_, fp32 *set_, fp32 erro_delta_ , cap_ctrl_data_t *IN);

//PID计算
fp32 Pid_calc(void); 

//PID清除
void Pid_clear(void);

#endif

