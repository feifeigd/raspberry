#!/usr/bin/env python3
try:
    import RPi.GPIO as GPIO
except RuntimeError:
    print("import RPi.GPIO error")

import time

colors = [0xff00, 0x00ff, 0x0ff0, 0xf00f]
makerobo_pins = (11, 12) # pin 引脚
GPIO.setmode(GPIO.BOARD) # 采用实际的物理引脚给GPIO口
GPIO.setwarnings(False)
GPIO.setup(makerobo_pins, GPIO.OUT) # 设置pin引脚为输出模式
GPIO.output(makerobo_pins, GPIO.LOW) # 设置pin引脚为低电平（0V），熄灭LED灯
p_R = GPIO.PWM(makerobo_pins[0], 2000) # 设置频率为2kHz
p_G = GPIO.PWM(makerobo_pins[1], 2000) # 设置频率为2kHz

# 初始化占空比为0
p_R.start(0)
p_G.start(0)

def makerobo_pwm_map(x, in_min, in_max, out_min, out_max):
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min

def makerobo_set_Color(col):
    R_val = col >> 8
    G_val = col & 0x00ff
    # 把0～255 同比例缩小到 0～100
    R_val = makerobo_pwm_map(R_val, 0, 255, 0, 100)
    G_val = makerobo_pwm_map(G_val, 0, 255, 0, 100)

    p_R.ChangeDutyCycle(R_val) # 改变占空比
    p_G.ChangeDutyCycle(G_val) # 改变占空比

def makerobo_loop():
    while True:
        for col in colors:
            makerobo_set_Color(col)
            time.sleep(0.5)

def makerobo_destroy():
    p_R.stop()
    p_G.stop()
    GPIO.output(makerobo_pins, GPIO.LOW) # 熄灭所有led灯
    GPIO.cleanup() # 释放资源

if "__main__" == __name__:
    try:
        makerobo_loop()
    except KeyboardInterrupt: # Ctrl + C
        makerobo_destroy()
