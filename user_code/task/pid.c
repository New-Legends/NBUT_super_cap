#include "pid.h"

#define LimitMax(input, max)   \
    {                          \
        if (input > max)       \
        {                      \
            input = max;       \
        }                      \
        else if (input < -max) \
        {                      \
            input = -max;      \
        }                      \
    }

pid_data_t pid_data;
uint8_t pid_mode;
/**
 * @brief          pid struct data init
 * @param[out]     pid: PID结构数据指针
 * @param[in]      mode: PID_POSITION:普通PID
 *                 PID_DELTA: 差分PID
 * @param[in]      PID: 0: kp, 1: ki, 2:kd
 * @param[in]      max_iout: pid最大积分输出
 * * @param[in]      max_out: pid最大输出
 * @retval         none
 */
void Pid_init(uint8_t mode_, const fp32 *pid_parm, fp32 *ref_, fp32 *set_, fp32 erro_delta_)
{
    pid_mode = mode_;
    pid_data.Kp = pid_parm[0];
    pid_data.Ki = pid_parm[1];
    pid_data.Kd = pid_parm[2];
    pid_data.max_iout = pid_parm[3];
    pid_data.max_out = pid_parm[4];

    pid_data.set = set_;
    pid_data.ref = ref_;
    pid_data.error = *set_ - *ref_;

    if (pid_data.mode == PID_ANGLE)
        pid_data.error_delta = erro_delta_;
}

/**
 * @brief pid计算
 * 
 * @return fp32 
 */
fp32 pid_calc()
{
    pid_data.last_error = pid_data.error;
    pid_data.error = *pid_data.set - *pid_data.ref;
    if (pid_mode == PID_SPEED)
        pid_data.error_delta = pid_data.error - pid_data.last_error;

    if (pid_mode == PID_ANGLE)
        pid_data.error = rad_format(pid_data.error);
    pid_data.error_delta = rad_format(pid_data.error - pid_data.last_error);

    pid_data.Pout = pid_data.Kp * pid_data.error;
    pid_data.Iout += pid_data.Ki * pid_data.error;
    pid_data.Dout = pid_data.Kd * (pid_data.error_delta);

    LimitMax(pid_data.Iout, pid_data.max_iout);

    pid_data.out = pid_data.Pout + pid_data.Iout + pid_data.Dout;
    LimitMax(pid_data.out, pid_data.max_out);

    return pid_data.out;
}

/**
 * @brief          pid 输出清除
 * @param[out]     pid: PID结构数据指针
 * @retval         none
 */
void pid_clear()
{
    pid_data.last_error = pid_data.error = *pid_data.set = *pid_data.ref = 0;
    pid_data.out = pid_data.Pout = pid_data.Iout = pid_data.Dout = 0;
}
