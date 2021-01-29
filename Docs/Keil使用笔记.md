# Keil使用笔记

## 1. 项目创建

## 1.1创建工程

1. ![image-20200525112523137](https://gitee.com/sun-roc/picture/raw/master/img/image-20200525112523137.png)

2. 选择芯片,选择是否添加有关汇编程序的文件,写c程序时不用

3. <img src="https://gitee.com/sun-roc/picture/raw/master/img/image-20200525112731424.png" alt="image-20200525112731424" style="zoom:50%;" />

4. 将所有涉及到的主函数,头文件,头文件相关的文件全部添加到工程中

5. 头文件:通过`" 双引号"`在主函数中引入不能用`<双减号>`的形式

   1. 一开始 ,且所有变量定义要在函数的一开始,全局变量定义要在头部

      ``` c
      #ifndef _MAIN_H //.h文件中写,如果其他.c文件调用.h文件会先判断防止重复调用
      #define _MAIN_H
      extern xx(全局变量)//告诉你有这么回事,具体在哪去项目(不一定是头文件相同名哦,是项目中的所有文件)中有的文件去找
          //仅对存在在项目里的文件有效,与命名无关
      void xx,(extern 相当于写道非main.c文件的.c文件中为了调用main.c文件的接口)
          //没用到的函数可以不声明,会自动调用
      //h头文件中也可直接写函数的定义,不一定非要写个c文件
      #ifndef _MAIN_C 
      extern xx(全局变量)
      #endif
      #endif
          
          //一定要把文件添加到项目中呀!!!!,extern出去的数据不能赋值;
      ```

## 2. 输出文件整理

1. 设置生成HEX文件,和晶振频率

<img src="https://gitee.com/sun-roc/picture/raw/master/img/image-20200525114344139.png" alt="image-20200525114344139" style="zoom:50%;" />

2. 选择输出文件位置,避免太过混乱

<img src="https://gitee.com/sun-roc/picture/raw/master/img/image-20200521094748875.png" alt="image-20200521094748875" style="zoom:50%;" />

<img src="https://gitee.com/sun-roc/picture/raw/master/img/image-20200521094922409.png" alt="image-20200521094922409" style="zoom:50%;" />



3. 小扳手处可以调整字体

<img src="https://gitee.com/sun-roc/picture/raw/master/img/image-20200525114655560.png" alt="image-20200525114655560" style="zoom:50%;" />

## 3. VScode编写工具

![image-20200525115230680](https://gitee.com/sun-roc/picture/raw/master/img/image-20200525115230680.png)

## 4. DEBUG

<img src="https://gitee.com/sun-roc/picture/raw/master/img/image-20200525115320430.png" alt="image-20200525115320430" style="zoom:50%;" />

<img src="https://gitee.com/sun-roc/picture/raw/master/img/image-20200525115355548.png" alt="image-20200525115355548" style="zoom: 67%;" />

<img src="https://gitee.com/sun-roc/picture/raw/master/img/image-20200525115455432.png" alt="image-20200525115455432" style="zoom:50%;" />

proteus远程调试