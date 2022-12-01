![Image text](https://wuxi.suis.com.cn/wp-content/uploads/sites/15/2018/11/%E7%A4%BE%E4%BC%9A%E4%B8%BB%E4%B9%89%E6%A0%B8%E5%BF%83%E4%BB%B7%E5%80%BC%E8%A7%82%E5%85%9A%E5%BB%BA%E5%B1%95%E6%9D%BF.jpg)
# 这是一份由NEW LEGENDS战队开发的10节50法拉电容引爆代码

##  接口介绍:
###      I2C接口
          I2C1: PB7->SDA PB6->SCL             
                连接超级电容充电模块用于检测充电功率
          I2C2: PB11->SDA PB10->SCL
                连接电池用于电池功率检测

###      LED灯接口
          白灯: PB5 输出PWN充电指示灯 pwn
          蓝灯: PA3 超电初始化完成后常亮 闪烁代表初始化失败 ready
          绿灯: PA4 超电放电时绿灯常亮 run
          橙灯: PA5 超电电压大于20v full
          红灯: PA6 电容电压小于12V low

###     充电模块LM5106
          使能: PB3 高电平开启充电 低电平关闭充电
          PWM控制:  PB4控制占空比控制充电电压

###     CAN通讯模块
          CAN_TX -> PB9  CAN_RX -> PB8
          控制板的CAN ID为固定的0x401,此ID固定不出现严重冲突不改！！！

## 充电接口介绍
            充电使用PWM的占空比控制，占空比越高，则充电功率越大






