/****************************文件包含*************************************/
#include "reg52.h "
#include "character.h"
#include "lcd.h"
#include "clock.h"
#include "sensor.h"
#include "calendar.h"
#include "key.h"

/*****************************预定义**************************************/
#define uchar unsigned char
#define uint unsigned int
/****************************************************************************/
sbit bell = P1 ^ 6; //定义蜂鸣器端口
sbit test = P1 ^ 7;
/*****************************************************************************
* 名称: Timer0_Service() inturrupt 1
* 功能: 中断服务程序 整点报时 3声嘟嘟的声音
* 入口参数:
* 出口参数:
*****************************************************************************/
void Timer0_Service() interrupt 1
{
	static uchar count = 0;
	static uchar flag = 0; //记录鸣叫的次数
	count = 0;
	TR0 = 0; //关闭Timer0
	TH0 = 0x3c;
	TL0 = 0XB0; //延时 50 ms
	TR0 = 1;	//启动Timer0
	count++;
	if (count == 20) //鸣叫 1 秒
	{
		bell = ~bell;
		count = 0;
		flag++;
	}
	if (flag == 6)
	{
		flag = 0;
		TR0 = 0; //关闭Timer0
	}
}

/*****************************************************************************
* 名称: Timer2_Servie() interrupt 5
* 功能: 中断服务程序  整点报时 一分钟
* 入口参数: 
* 出口参数:
*****************************************************************************/
uchar HexNum_Convert(uchar HexNum) /*时间存储个位和十位的方式与我们用的十进制不一样，你懂的，呵呵--BB车*/
{
	uchar Numtemp;
	Numtemp = (HexNum >> 4) * 10 + (HexNum & 0X0F);
	return Numtemp;
}
/******************************************************************************
* 函数名称：main()
* 功    能：
* 入口参数：
* 出口参数：
********************************************************************************/
void main(void)
{
	uchar ring = 0; //闹钟停止与否的标志
	bit am = 0;
	uchar clock_time[7] = {0X00, 0X59, 0X23, 0X09, 0X04, 0X11, 0x00};
	//定义时间变量 秒  分 时 日 月 年
	uchar alarm_time[2] = {55, 20};
	//闹钟设置  alarm_time[0]: 分钟  alarm_time[1] :小时
	uchar temperature[2];
	//定义温度变量   temperature[0]  低8位   temperature[1]  高8位

	Lcd_Initial();			   //LCD初始化
	Clock_Fresh(clock_time);   //我把时间刷新放在这里，proteus会调用当前系统时间，别问为什么，经验，呵呵
	Clock_Initial(clock_time); //时钟初试化
	test = 0;

	/***********************中断初始化***************************/
	EA = 1;		 //开总中断
	ET0 = 1;	 //Timer0 开中断
	ET2 = 1;	 //Timer2 开中断
	TMOD = 0x01; //Timer0 工作方式 1
	RCAP2H = 0x3c;
	RCAP2L = 0xb0; //Timer2 延时 50 ms

	while (1)
	{
		switch (Key_Scan()) //KEY_SAN()
		{
		case UpButton:
		{
			Key_Wait();
		}
		break;
		case DownButton:
		{
			Key_Wait();
		}
		break;
		case BackButton:
		{
			am = ~am;
			Key_Wait();
		}
		break;
		case MenuButton:
		{
			Key_Function(clock_time, alarm_time);
		}
		case null:
		{
			Clock_Fresh(clock_time);	 //时间刷新
			Lcd_Clock(clock_time, am);	 //时间显示
			Sensor_Fresh(temperature);	 //温度更新
			Lcd_Temperture(temperature); //温度显示

			Calendar_Convert(0, clock_time); //农历转换与显示
			Lcd_Week(clock_time);

			//整点报时
			//   if( ( * clock_time == 0x59 ) && ( * ( clock_time + 1 ) == 0x59 ) )
			//   {
			//      bell = 0;
			// 	 TR2 = 1; //启动Timer2
			//   }
			//闹钟报警
			while (*alarm_time == HexNum_Convert(*(clock_time + 1)))
			{																									   //分钟相吻合
				if (*(alarm_time + 1) == HexNum_Convert(*(clock_time + 2)) && (Key_Scan() == null) && (ring == 0)) //小时相吻合
				{
					bell = 0;
					// TR2 = 1; //启动Timer2
				}
				if (*(alarm_time + 1) == HexNum_Convert(*(clock_time + 2)) && (Key_Scan() != null))
				{
					bell = 1;
					ring = 1;
				}
			}
			ring = 0;
		}
		break;
		}
	}
}
