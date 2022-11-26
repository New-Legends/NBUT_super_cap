## 这是一份由NEW LEGENDS战队开发的10节50法拉电容引爆代码

##  接口介绍:
##      I2C接口
##          I2C1: PB7->SDA PB6->SCL             
##                连接超级电容充电模块用于检测充电功率
##          I2C2: PB11->SDA PB10->SCL
##                连接电池用于电池功率检测
##
##      LED灯接口
##          白灯: PB5 输出PWN充电指示灯 pwn
##          蓝灯: PA3 超电初始化完成后常亮 闪烁代表初始化失败 ready
##          绿灯: PA4 超电放电时绿灯常亮 run
##          橙灯: PA5 超电电压大于20v full
##          红灯: PA6 电容电压小于12V low
##
##
##
##
##










