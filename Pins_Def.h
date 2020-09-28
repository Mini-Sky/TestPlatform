#ifndef __PINS_DEF_H
#define __PINS_DEF_H

#define OLED_DC 11
#define OLED_CS 12
#define OLED_CLK 10
#define OLED_MOSI 9
#define OLED_RESET 13

#define Encoder_PinA A6
#define Encoder_PinB A7

#define Trig_Pin 3  //超声波测距传感器Trig引脚定义
#define Echo_Pin 2  //超声波测距传感器Echo引脚定义
#define Echo_INT 0  //设置Echo中断号为0

//红外寻光模块引脚定义
#define HW_Pin 5  //红外测距引脚
#define LT_Pin 4  //光强测试引脚

//四路循迹模块引脚定义
#define FourTrack_PinX1 9
#define FourTrack_PinX2 8
#define FourTrack_PinX3 7
#define FourTrack_PinX4 6

//三路PWM循迹模块
#define ThreeTrack_PinX1 A3
#define ThreeTrack_PinX2 A2
#define ThreeTrack_PinX3 A1

//LED 三色照明模块引脚定义
#define RGB_PinR 10
#define RGB_PinG 11
#define RGB_PinB 12

#define RP A0   //电位器的引脚定义
#define ServoPin 13  //舵机的控制引脚定义
#endif
