#ifndef _LUNARCALENDER_H
#define _LUNARCALENDER_H
/*************************************************************************/
#define uchar unsigned char
#define uint unsigned int

/********************************************************************************
* 名称: get_moon_day(uchar month_p,uint table_addr)
* 功能: 读取数据表中农历的大月或小月 ，如果大月返回1, 小月返回0
* 入口参数:
* 出口参数:
*********************************************************************************/
bit get_moon_day( uchar month_p,uint calendar_address )
{
    uchar temp,temp1;

	temp1=(month_p+3)/8;
	temp=0x80>>((month_p+3)%8);
	temp=year_code[calendar_address+temp1]&temp;
	if(temp==0){return(0);}else{return(1);}
}
/**************************************************************************
* 名称: void Calendar_Convert( uchar * clock_time )
* 功能: 输入BCD的阳历数据， 输出BCD阴历数据( 1901 - 2099 )
* 入口参数: c_flag:阳历的世纪标志  clock_time: 时钟地址
* 出口参数: 无
* 说明: c_flag = 0 :21世纪 c_flag = 1 :19世纪 
*****************************************************************************/
void Calendar_Convert( uchar c_flag, uchar * clock_time )
{
   bit flag_month, flag_year;
   uchar year, month, day, month_point; //定义 年 月 天
   uchar temp1, temp2, temp3;
   uint calendar_address; //定义农历地址
   uint day_number;
   uchar clock_moon[3]; //定义阴历


   clock_time += 3; //指向日
   day = ( * clock_time >> 4 ) * 10 + ( *clock_time & 0x0f ); //BCD转换十进制
   clock_time ++; //指向月
   month = ( * clock_time >> 4 ) * 10 + ( * clock_time & 0x0f ); //BCD转换十进制
   clock_time += 2; //指向年
   year = ( * clock_time >> 4 ) * 10 + ( * clock_time & 0x0f ); //BCD转换十进制 
  
   //定位日历地址
   if( c_flag == 0 )
      calendar_address = ( year + 99 ) * 3;  
   else
      calendar_address = ( year - 1 ) * 3;

   //春节(正月初一)所在的阳历月份
   temp1 = year_code[ calendar_address + 2 ] & 0x60; //Bit6~~Bit5:春节所在的阳历月份
   temp1 >>= 5 ;
   //春节(正月初一)所在的阳历日期
   temp2 = year_code[ calendar_address + 2 ] & 0x1f; //Bit4~~Bit0:春节所在的阳历日期
  
	temp3=temp2-1;
	if(temp1!=1) temp3+=0x1f;
   

   //计算阳历月离当年元旦{ 1月1日(阳历) }的天数
   if( month < 10 )
      {day_number = day_code1[ month - 1 ] + day  ;} 
   else
      {day_number = day_code2[ month - 10 ] + day ;}

   //如果阳历的月大于2 且该年的2月为闰月，天数加1 
   //闰年指的就是阳历有闰日或阴历有闰月的一年；
   //阳历四年一闰，在二月加一天，这一天叫做闰日：
   //农历三年一闰，五年两闰，十九年七闰，每逢闰年所加的一个月叫做闰月。
   if( ( month <= 2 ) || ( year % 0x04!= 0) ) day_number-=1;
   //   day_number ++;

  //   if ((month<2)||(year%0x04!=0))
  //   day_number-=1;

   //判断阳历日 在春节(正月初一) 之前 还是 之后
   if( day_number >= temp3 ) //阳历在春节之后 或者 春节当日
   {
      day_number -= temp3;
      month = 1;
      month_point = 1; // month_point 为月份指向，阳历日在春季前就是春季
	  flag_month = get_moon_day( month_point, calendar_address ); //检查该阴历月的大小  大月返回1  小月返回0
	  flag_year = 0;
	 /* if( flag_month )
	     temp1 = 30; //大月30天
	  else
 	     temp1 = 29; //小月29天
      */
      if (flag_month==0) {temp1=29;} else{temp1=30;}

	  //闰月所在的月分
	  temp2 = year_code[ calendar_address ] & 0xf0;
	  temp2 >>= 4; //提取高四位  假如是0 表示没有闰月

	  while( day_number >= temp1 )
	  {
	     day_number -= temp1;
         month_point ++;
         if( month == temp2 )
         {
            flag_year = ~ flag_year; 
            if( flag_year == 0 ) 
               month +=1;
         }
         else
            month ++ ;
         flag_month = get_moon_day( month_point, calendar_address );
         if( flag_month )
            temp1 = 30;
         else
            temp1 = 29;
       }
       day = day_number + 1;
   }
   else //阳历在春节之前使用以下代码进行运算
   {
      temp3 -= day_number;
      if( year == 0 )
         { year = 0xe3; c_flag = 1; }
      else
         year -= 1;
      calendar_address -= 3;
      month = 0xc;
      temp2 = year_code[ calendar_address ] & 0xf0;
      temp2 >>= 4; //提取高4位
      flag_year=0;
	  if( temp2 == 0 )
         month_point = 12;
      else
         month_point = 13;
      //flag_year = 0;
      flag_month = get_moon_day( month_point, calendar_address );
      if( flag_month )
         temp1 = 30;
      else
         temp1 = 29;
      while( temp3 > temp1 )
      {
         temp3 -= temp1;
         month_point --;
         if( flag_year == 0 )
         month -=1;
         if( month == temp2 )
         flag_year = ~ flag_year;
         flag_month = get_moon_day( month_point, calendar_address );
         if( flag_month )
            temp1 = 0x1e;
         else
            temp1 = 0x1d;
         
      }
      day = temp1 - temp3 + 1;
   }
   //HEX->BCD ,运算结束后,把数据转换为BCD数据
   temp1 = year / 10;
   temp1 <<= 4;
   clock_moon[2] = temp1 | ( year % 10 );
 
   temp1 = month / 10;
   temp1 <<= 4;
   clock_moon[1] = temp1 | ( month % 10 );
 
   temp1 = day / 10;
   temp1 <<= 4;
   clock_moon[0] = temp1 | ( day % 10 );
   Lcd_Lunar_Calendar( clock_moon );
}
/****************************************************************************************************************************
函数功能： 二十四节气数据库
入口参数： unsigned char(yy,mo,dd) 对应 年月日
出口参数： unsigned char(0-24) 1-24对应二十四节气
作者    ： TOTOP
二十四节气数据库（1901--2050） 
数据格式说明:   
如1901年的节气为   
     1月    2月     3月     4月       5月      6月    7月     8月      9月    10月   11月    12月   
[ 6,21][ 4,19][ 6,21][ 5,21][ 6,22][ 6,22][ 8,23][ 8,24][ 8,24][ 8,24][ 8,23][ 8,22]   
[ 9, 6][11, 4][ 9, 6][10, 6][ 9, 7][ 9, 7][ 7, 8][ 7, 9][ 7, 9][ 7, 9][ 7, 8][ 7,15]   
上面第一行数据为每月节气对应公历日期,15减去每月第一个节气,每月第二个节气减去15得第二
行，这样每月两个节气对应数据都小于16,每月用一个字节存放,高位存放第一个节气数据,低位存
放第二个节气的数据,可得下表   
****************************************************************************************************************************/
uchar code SolarTerms_Table[]=
{ 
       0x96,0xB4,0xA5,0xB5,0xA6,0xA6,0x87,0x88,0x88,0x78,0x87,0x86,     //2000   
       0xA5,0xB3,0xA5,0xA5,0xA6,0xA6,0x88,0x88,0x88,0x78,0x87,0x87,     //2001   
       0xA5,0xB4,0x96,0xA5,0x96,0x96,0x88,0x78,0x78,0x78,0x87,0x87,     //2002   
       0x95,0xB4,0x96,0xA5,0x96,0x97,0x88,0x78,0x78,0x69,0x78,0x87,     //2003   
       0x96,0xB4,0xA5,0xB5,0xA6,0xA6,0x87,0x88,0x88,0x78,0x87,0x86,     //2004   
       0xA5,0xB3,0xA5,0xA5,0xA6,0xA6,0x88,0x88,0x88,0x78,0x87,0x87,     //2005   
       0xA5,0xB4,0x96,0xA5,0xA6,0x96,0x88,0x88,0x78,0x78,0x87,0x87,     //2006   
       0x95,0xB4,0x96,0xA5,0x96,0x97,0x88,0x78,0x78,0x69,0x78,0x87,     //2007   
       0x96,0xB4,0xA5,0xB5,0xA6,0xA6,0x87,0x88,0x87,0x78,0x87,0x86,     //2008   
       0xA5,0xB3,0xA5,0xB5,0xA6,0xA6,0x88,0x88,0x88,0x78,0x87,0x87,     //2009   
       0xA5,0xB4,0x96,0xA5,0xA6,0x96,0x88,0x88,0x78,0x78,0x87,0x87,     //2010   
       0x95,0xB4,0x96,0xA5,0x96,0x97,0x88,0x78,0x78,0x79,0x78,0x87,     //2011   
       0x96,0xB4,0xA5,0xB5,0xA5,0xA6,0x87,0x88,0x87,0x78,0x87,0x86,     //2012   
       0xA5,0xB3,0xA5,0xB5,0xA6,0xA6,0x87,0x88,0x88,0x78,0x87,0x87,     //2013   
       0xA5,0xB4,0x96,0xA5,0xA6,0x96,0x88,0x88,0x78,0x78,0x87,0x87,     //2014   
       0x95,0xB4,0x96,0xA5,0x96,0x97,0x88,0x78,0x78,0x79,0x77,0x87,     //2015   
       0x95,0xB4,0xA5,0xB4,0xA5,0xA6,0x87,0x88,0x87,0x78,0x87,0x86,     //2016   
       0xA5,0xC3,0xA5,0xB5,0xA6,0xA6,0x87,0x88,0x88,0x78,0x87,0x87,     //2017   
       0xA5,0xB4,0xA6,0xA5,0xA6,0x96,0x88,0x88,0x78,0x78,0x87,0x87,     //2018   
       0xA5,0xB4,0x96,0xA5,0x96,0x96,0x88,0x78,0x78,0x79,0x77,0x87,     //2019   
       0x95,0xB4,0xA5,0xB4,0xA5,0xA6,0x97,0x87,0x87,0x78,0x87,0x86,     //2020   
       0xA5,0xC3,0xA5,0xB5,0xA6,0xA6,0x87,0x88,0x88,0x78,0x87,0x86,     //2021   
       0xA5,0xB4,0xA5,0xA5,0xA6,0x96,0x88,0x88,0x88,0x78,0x87,0x87,     //2022   
       0xA5,0xB4,0x96,0xA5,0x96,0x96,0x88,0x78,0x78,0x79,0x77,0x87,     //2023   
       0x95,0xB4,0xA5,0xB4,0xA5,0xA6,0x97,0x87,0x87,0x78,0x87,0x96,     //2024   
       0xA5,0xC3,0xA5,0xB5,0xA6,0xA6,0x87,0x88,0x88,0x78,0x87,0x86,     //2025   
       0xA5,0xB3,0xA5,0xA5,0xA6,0xA6,0x88,0x88,0x88,0x78,0x87,0x87,     //2026   
       0xA5,0xB4,0x96,0xA5,0x96,0x96,0x88,0x78,0x78,0x78,0x87,0x87,     //2027   
       0x95,0xB4,0xA5,0xB4,0xA5,0xA6,0x97,0x87,0x87,0x78,0x87,0x96,     //2028   
       0xA5,0xC3,0xA5,0xB5,0xA6,0xA6,0x87,0x88,0x88,0x78,0x87,0x86,     //2029   
       0xA5,0xB3,0xA5,0xA5,0xA6,0xA6,0x88,0x88,0x88,0x78,0x87,0x87,     //2030   
       0xA5,0xB4,0x96,0xA5,0x96,0x96,0x88,0x78,0x78,0x78,0x87,0x87,     //2031   
       0x95,0xB4,0xA5,0xB4,0xA5,0xA6,0x97,0x87,0x87,0x78,0x87,0x96,     //2032   
       0xA5,0xC3,0xA5,0xB5,0xA6,0xA6,0x88,0x88,0x88,0x78,0x87,0x86,     //2033   
       0xA5,0xB3,0xA5,0xA5,0xA6,0xA6,0x88,0x78,0x88,0x78,0x87,0x87,     //2034   
       0xA5,0xB4,0x96,0xA5,0xA6,0x96,0x88,0x88,0x78,0x78,0x87,0x87,     //2035   
       0x95,0xB4,0xA5,0xB4,0xA5,0xA6,0x97,0x87,0x87,0x78,0x87,0x96,     //2036   
       0xA5,0xC3,0xA5,0xB5,0xA6,0xA6,0x87,0x88,0x88,0x78,0x87,0x86,     //2037   
       0xA5,0xB3,0xA5,0xA5,0xA6,0xA6,0x88,0x88,0x88,0x78,0x87,0x87,     //2038   
       0xA5,0xB4,0x96,0xA5,0xA6,0x96,0x88,0x88,0x78,0x78,0x87,0x87,     //2039   
       0x95,0xB4,0xA5,0xB4,0xA5,0xA6,0x97,0x87,0x87,0x78,0x87,0x96,     //2040   
       0xA5,0xC3,0xA5,0xB5,0xA5,0xA6,0x87,0x88,0x87,0x78,0x87,0x86,     //2041   
       0xA5,0xB3,0xA5,0xB5,0xA6,0xA6,0x88,0x88,0x88,0x78,0x87,0x87,     //2042   
       0xA5,0xB4,0x96,0xA5,0xA6,0x96,0x88,0x88,0x78,0x78,0x87,0x87,     //2043   
       0x95,0xB4,0xA5,0xB4,0xA5,0xA6,0x97,0x87,0x87,0x88,0x87,0x96,     //2044   
       0xA5,0xC3,0xA5,0xB4,0xA5,0xA6,0x87,0x88,0x87,0x78,0x87,0x86,     //2045   
       0xA5,0xB3,0xA5,0xB5,0xA6,0xA6,0x87,0x88,0x88,0x78,0x87,0x87,     //2046   
       0xA5,0xB4,0x96,0xA5,0xA6,0x96,0x88,0x88,0x78,0x78,0x87,0x87,     //2047   
       0x95,0xB4,0xA5,0xB4,0xA5,0xA5,0x97,0x87,0x87,0x88,0x86,0x96,     //2048   
       0xA4,0xC3,0xA5,0xA5,0xA5,0xA6,0x97,0x87,0x87,0x78,0x87,0x86,     //2049   
       0xA5,0xC3,0xA5,0xB5,0xA6,0xA6,0x87,0x88,0x78,0x78,0x87,0x87,     //2050
    };


//入参为年月日,出参为对应节气的序号
uchar SolarTerm (uchar *DateTime)
{
    uchar year_solar = DateTime[6];
    uchar month_solar = DateTime[4];
    uchar day_solar = DateTime[3];
    uchar temp,day,year,year1,month;
    uint addr;

    day=day_solar/16*10+day_solar%16;
    month=month_solar/16*10+month_solar%16; 
    year1=year_solar/16*10+year_solar%16+2000;
    year=year1-2000;
    addr=year*12+month-1;
    if(day<15)
        {
        temp=15-day;
        if((SolarTerms_Table[addr]>>4)==temp) return (month*2-1);
        else return (0);
        }
    if(day==15) return (0);
    if(day>15)
        {
        temp=day-15;
        if((SolarTerms_Table[addr]&0x0f)==temp) return (month*2);
        else return (0);
        }
    }
#endif