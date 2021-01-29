# 基于STC-15f2k60s2芯片的多功能万年历设计

> 本项目受限于芯片的性能仅实现以下功能,在Flynk仓库中的项目在本项目的基础上增加了物联网功能,并完成了实物搭建

## 1. 基本功能

1. 获取当前的年、月、日、时、分、秒并显示

2. 设置年、月、日、时、分、秒

3. AM、PM设置与显示

4. 农历年、月、日显示

5. 农历二十四节气显示

6. 闹钟时间设置，声光报警提示
7. 温度和湿度的检测与显示

## 2. 文件结构

Keil 文件夹为有关Keil C51软件的项目文件,包含编译的hex文件等

PCB_Clock 文件夹为使用Altium Designer设计的PCB线路图

Proteus 文件夹内为 Proteus 软件搭建的本项目的仿真程序

Source 文件夹为该项目的C语言程序源码

Docs 文件夹为搭建项目过程中学习相关元器件和软件使用方法时撰写的Markdown笔记

## 3. 元器件型号

1. 单片机:STC-15f2k60s2
2. 实时时钟芯片:DS1302
3. LCD显示模块:LCD12864
4. 温度传感器:DS18B20 
5. WIFI模块:ESP8266

## 4. 项目开发流程

1. 学习了Keil C51的基本操作(包括建立工程,DEBUG,联合Proteus远程调试等)



2. 学习了Proteus和Altium Designer的基本使用搭建了本次项目,仿真所需要的环境



3. 有关读取DS1302中年、月、日、时、分、秒的程序设计并搭建了仿真环境

- 编写流程为:
  1. 时钟芯片初始化,令时钟工作
  2. 将要读取的时间位地址写入芯片(一个字节)
  3. 将该位的时间数据读取出来(一个字节)
  4. 将读取的年月日时分秒数据返回

4. 有关农历显示的程序设计,通过LCD12864可以通过DS1302获取当前时间并通过内部算法运算获得当前时间农历日期

5. 完成了公历显示程序和农历显示程序的切换程序并获得节气信息.

## 5. 效果演示

> 仅进行Proteus仿真搭建和PCB绘制 实物部分改由Flynk仓库内的项目实现,并增加了物联网功能 -详见Flynk

基本界面

![image-20210128205351232](https://gitee.com/sun-roc/picture/raw/master/img/image-20210128205351232.png)

![image-20210128205431880](https://gitee.com/sun-roc/picture/raw/master/img/image-20210128205431880.png)

![image-20210128205512622](https://gitee.com/sun-roc/picture/raw/master/img/image-20210128205512622.png)

![image-20210128205528587](https://gitee.com/sun-roc/picture/raw/master/img/image-20210128205528587.png)

![image-20210128205549817](https://gitee.com/sun-roc/picture/raw/master/img/image-20210128205549817.png)