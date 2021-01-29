#ifndef _KEY_H
#define _KEY_H
/***********************键盘预定义******************************************/
#define UpButton 0x01
#define DownButton 0x02
#define BackButton 0x03
#define MenuButton 0x04
#define null 0
#define Button P3

/********************************************************************************************
* 函数名称：Key_Idle()
* 功    能：键盘松开
* 入口参数：无
* 出口参数：无
*********************************************************************************************/
void Key_Wait()
{
	while ((Button & 0x0f) != 0x0f)
		;
}

/********************************************************************************************
* 函数名称：Key_Scan()
* 功    能：键盘扫描
* 入口参数：无
* 出口参数：键值
*********************************************************************************************/
uchar Key_Scan()
{
	if ((Button & 0x0f) != 0x0f) //判断按键
	{
		Delay(4); //消除抖动
		if ((Button & 0x0f) != 0x0f)
		{

			switch (Button & 0x0f) //将按键码转换成键值
			{
			case 0x0e:
				return UpButton;
			case 0x0d:
				return DownButton;
			case 0x0b:
				return BackButton;
			case 0x07:
				return MenuButton;
			default:
				return null;
			}
		}
	}
	return null;
}

/********************************************************************************************
* 函数名称：Key_Set_Clock( uchar * clock_time )
* 功    能：键盘设定时间
* 入口参数：clock_time[7]
* 出口参数：无
*********************************************************************************************/
void Key_Set_Clock(uchar *clock_time)
{
	uchar flag = 2;
	uchar minute;
	uchar hour;
	uchar day;
	uchar month;
	uchar year;
	uchar *time_head; //一直指向clock_time的起始位置
	time_head = clock_time;

	Key_Wait();
	while (1)
	{

	loop:
		Key_Wait();
		switch (flag)
		{
		case 2:
		{
			Lcd_Set_Clock(2, time_head); //屏幕显示更该时间
			clock_time++;				 //指向分

			minute = ((*clock_time >> 4) * 10) + ((*clock_time) & 0x0f);
			while (1)
			{
				switch (Key_Scan()) //调整分
				{
				case UpButton:
				{
					minute++;
					if (minute == 60)
						minute = 0;
					(*clock_time) = minute / 10 << 4;
					(*clock_time) = (*clock_time) | (minute % 10); //低位与高位相加,HEX 转 BCD
					Lcd_Set_Clock(2, time_head);				   //屏幕显示更该时间
					Key_Wait();
				}
				break;
				case DownButton:
				{
					if (minute == 0)
						minute = 60;
					minute--;
					(*clock_time) = minute / 10 << 4;
					(*clock_time) = (*clock_time) | (minute % 10); //HEX 转 BCD
					Lcd_Set_Clock(2, time_head);				   //屏幕显示更该时间
					Key_Wait();
				}
				break;
				case MenuButton:
				{
					flag++;
					goto loop;
				}
				break;
				}
			}
		}
		break;
		case 3:
		{
			clock_time++;											   //指向时
			Lcd_Set_Clock(3, time_head);							   //屏幕显示更该时间
			hour = ((*clock_time >> 4) * 10) + ((*clock_time) & 0x0f); //BCD 转 HEX
			while (1)
			{
				switch (Key_Scan())
				{
				case UpButton:
				{
					hour++;
					if (hour == 24)
						hour = 0;
					(*clock_time) = hour / 10 << 4;
					(*clock_time) = (*clock_time) | (hour % 10); //HEX 转 BCD
					Lcd_Set_Clock(3, time_head);				 //屏幕显示更该时间
					Key_Wait();
				}
				break;

				case DownButton:
				{
					if (hour == 0)
						hour = 24;
					hour--;
					if (hour == 0)
						hour = 23;
					(*clock_time) = hour / 10 << 4;
					(*clock_time) = (*clock_time) | (hour % 10); //HEX 转 BCD
					Lcd_Set_Clock(3, time_head);				 //屏幕显示更该时间
					Key_Wait();
				}
				break;
				case MenuButton:
				{
					flag++;
					goto loop;
				}
				break;
				}
			}
		}
		break;
		case 4:
		{
			clock_time++;											  //指向日
			Lcd_Set_Clock(4, time_head);							  //屏幕显示更该时间
			day = ((*clock_time >> 4) * 10) + ((*clock_time) & 0x0f); //BCD 转 HEX
			while (1)
			{
				switch (Key_Scan())
				{
				case UpButton:
				{
					day++;
					if (day == 32)
						day = 1;
					(*clock_time) = day / 10 << 4;
					(*clock_time) = (*clock_time) | (day % 10); //HEX 转 BCD
					Lcd_Set_Clock(4, time_head);				//屏幕显示更该时间
					Key_Wait();
				}
				break;
				case DownButton:
				{
					if (day == 0)
						day = 31;
					day--;
					if (day == 0)
						day = 31;
					(*clock_time) = day / 10 << 4;
					(*clock_time) = (*clock_time) | (day % 10); //HEX 转 BCD ;
					Lcd_Set_Clock(4, time_head);				//屏幕显示更该时间
					Key_Wait();
				}
				break;
				case MenuButton:
				{
					flag++;
					goto loop;
				}
				break;
				}
			}
		}
		break;
		case 5:
		{
			clock_time++;				 //指向月
			Lcd_Set_Clock(5, time_head); //屏幕显示更该时间
			month = ((*clock_time >> 4) * 10) + ((*clock_time) & 0x0f);
			while (1)
			{

				//BCD 转 HEX
				switch (Key_Scan())
				{
				case UpButton:
				{
					month++;
					if (month == 13)
						month = 1;
					(*clock_time) = month / 10 << 4;
					(*clock_time) = (*clock_time) | (month % 10); //HEX 转 BCD
					Lcd_Set_Clock(5, time_head);				  //屏幕显示更该时间
					Key_Wait();
				}
				break;
				case DownButton:
				{
					if (month == 0)
						month = 12;
					month--;
					if (month == 0)
						month = 12;
					(*clock_time) = month / 10 << 4;
					(*clock_time) = (*clock_time) | (month % 10); //HEX 转 BCD
					Lcd_Set_Clock(5, time_head);				  //屏幕显示更该时间
					Key_Wait();
				}
				break;
				case MenuButton:
				{
					flag++;
					goto loop;
				}
				break;
				}
			}
		}
		break;
		case 6:
		{
			clock_time += 2;			 //指向年
			Lcd_Set_Clock(6, time_head); //屏幕显示更该时间
			year = ((*clock_time >> 4) * 10) + ((*clock_time) & 0x0f);
			while (1)
			{
				switch (Key_Scan())
				{
				case UpButton:
				{
					year++;
					if (year == 100)
						year = 0;
					(*clock_time) = year / 10 << 4;
					(*clock_time) = (*clock_time) | (year % 10); //HEX 转 BCD
					Lcd_Set_Clock(6, time_head);				 //屏幕显示更该时间
					Key_Wait();
				}
				break;
				case DownButton:
				{
					if (year == 0)
						year = 100;
					year--;
					if (year == 0)
						year = 100;
					(*clock_time) = year / 10 << 4;
					(*clock_time) = (*clock_time) | (year % 10); //HEX 转 BCD
					Lcd_Set_Clock(6, time_head);				 //屏幕显示更该时间
					Key_Wait();
				}
				break;
				case MenuButton:
				{
					flag++;
					goto loop;
				}
				break;
				}
			}
		}
		break;
		case 7:
		{
			goto end;
		}
		default:
			goto end;
		}
	end:
		break;
	}
}

/***************************************************************************************
* 名称: Key_Set_Alarm( uchar *  alarm_time )
* 功能: 闹钟调整
* 入口参数: 闹钟地址
* 出口参数:
****************************************************************************************/
void Key_Set_Alarm(uchar *alarm_time)
{
	Lcd_Alarm(1, alarm_time);
	Key_Wait();
	while (1)
	{
		switch (Key_Scan())
		{
		case UpButton:
		{
			(*alarm_time)++;
			if (*alarm_time == 60)
				*alarm_time = 0;
			Lcd_Alarm(1, alarm_time);
			Key_Wait();
		}
		break;
		case DownButton:
		{
			if (*alarm_time == 0)
				*alarm_time = 60;
			(*alarm_time)--;
			Lcd_Alarm(1, alarm_time);
			Key_Wait();
		}
		break;
		case BackButton:
		{
			Lcd_Clear();
			goto loop;
		}
		break;
		case MenuButton:
		{
			alarm_time++;
			Lcd_Alarm(2, alarm_time - 1);
			Key_Wait();
			while (1)
			{
				switch (Key_Scan())
				{
				case UpButton:
				{
					(*alarm_time)++;
					if (*alarm_time == 24)
						*alarm_time = 0;
					Lcd_Alarm(2, alarm_time - 1);
					Key_Wait();
				}
				break;
				case DownButton:
				{
					if (*alarm_time == 0)
						*alarm_time = 24;
					(*alarm_time)--;
					Lcd_Alarm(2, alarm_time - 1);
					Key_Wait();
				}
				break;
				case BackButton:
				{
					Lcd_Clear();
					goto loop;
				}
				break;
				case MenuButton:
				{
					Lcd_Clear();
					goto loop;
				}
				break;
				}
			}
		}
		break;
		}
	}
loop:
	Key_Wait();
}
/****************************************************************************************
* 名称: Key_Function( uchar * clock_time ) 
* 功能: 系统功能调试
* 入口参数: 时钟程序
* 出口参数: 无
*****************************************************************************************/
void Key_Function(uchar *clock_time, uchar *alarm_time)
{
	uchar location = 2;
	Lcd_Clear();
	Lcd_Menu(location);
	Key_Wait();
	while (1)
	{
		switch (Key_Scan())
		{
		case UpButton:
		{
			location++;
			if (location > 2)
				location = 2;
			Lcd_Menu(location);
			Key_Wait();
		}
		break;
		case DownButton:
		{
			location--;
			if (location == 0)
				location = 1;
			Lcd_Menu(location);
			Key_Wait();
		}
		break;
		case BackButton:
		{
			Lcd_Clear();
			goto loop;
		}
		break;
		case MenuButton:
		{
			if (location == 2)
			{
				Lcd_Clear();
				Key_Set_Clock(clock_time);
				Clock_Initial(clock_time);
				Lcd_Clear();
				goto loop;
			}
			if (location == 1)
			{
				Lcd_Clear();
				Key_Set_Alarm(alarm_time);
				Lcd_Clear();
				goto loop;
			}
		}
		break;
		}
	}
loop:
	Key_Wait();
}
/********************************************************************************/
#endif