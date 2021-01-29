#ifndef _LCD_12864
#define _LCD_12864
/*****************************预定义**************************************/
#define uchar unsigned char
#define uint unsigned int
#define port P0
/***************************12864管脚配置****************************/

sbit  rs=P2^0;
sbit  rw=P2^1;
sbit   e=P2^2;
sbit cs1=P2^3;
sbit cs2=P2^4;
/********************************************************************************************
* 函数名称：Delay()
* 功    能：延迟时间=a*1ms
* 入口参数：
* 出口参数：无
*********************************************************************************************/
void Delay(uint a)
{
   uchar  i;
   while(a--)
   for(i=0;i<125;i++);
}
/********************************************************************************************
* 函数名称：Lcd_Display_On()
* 功    能：LCD显示开
* 入口参数：无
* 出口参数：无
*********************************************************************************************/
void Lcd_Display_On()
{  
   port=0x3f;
   rs=0;
   rw=0;
   e=1;
   e=0;  
}
/********************************************************************************************
* 函数名称：Lcd_Display_Off()
* 功    能：LCD显示关
* 入口参数：无
* 出口参数：无
*********************************************************************************************/
void Lcd_Display_Off()
{  
   port=0x3e;
   rs=0;
   rw=0;
   e=1;
   e=0;  
}
/********************************************************************************************
* 函数名称：Lcd_Set_X(uchar x)
* 功    能：LCD设置X坐标
* 入口参数：x 
* 出口参数：无
*********************************************************************************************/
void Lcd_Set_X(uchar x)
{  
   port=0xb8|x;
   rs=0;
   rw=0;
   e=1;
   e=0;  
}
/********************************************************************************************
* 函数名称：Lcd_Set_Y(uchar y)
* 功    能：LCD设置Y坐标
* 入口参数：y
* 出口参数：无
*********************************************************************************************/
void Lcd_Set_Y(uchar y)
{  
   port=0x40|y;
   rs=0;
   rw=0;
   e=1;
   e=0;  
}
/********************************************************************************************
* 函数名称：Lcd_Set_X_Y(uchar x, uchar y )
* 功    能：LCD设置x y坐标
* 入口参数：x y
* 出口参数：无
*********************************************************************************************/
void Lcd_Set_X_Y(uchar x, uchar y)
{  
   
   if( y<64 )
      { cs1=1; cs2=0; Lcd_Set_Y( y ); }
   else
      { cs1=0; cs2=1; Lcd_Set_Y( y-64 );  }
    Lcd_Set_X( x);
}
/********************************************************************************************
* 函数名称：Lcd_Write_Command()
* 功    能：写指令代码
* 入口参数：无
* 出口参数：无
*********************************************************************************************/
void Lcd_Write_Command(uchar temp)
{  
   port=temp;
   rs=0;
   rw=0;
   e=1;
   e=0;  
}
/********************************************************************************************
* 函数名称：Lcd_Write_Byte()
* 功    能：写数据
* 入口参数：无
* 出口参数：无
*********************************************************************************************/
void Lcd_Write_Byte(uchar temp)
{  
   port=temp;
   rs=1;
   rw=0;
   e=1;
   e=0;  
}
/****************************************************************************
*名称:Lcd_Character_16X8( bit bit_flag, uchar x, uchar y, uchar code *point )
*功能:显示16X8字符(字母)         
*入口参数:
*出口参数:
*说明:bit_flag = 1 正常显示  bit_flag = 0 黑白反相显示 
****************************************************************************/
void Lcd_Character_16X8( bit bit_flag, uchar x, uchar y, uchar code *point )
{
   uchar i , j,temp;
   temp=y;
   if( bit_flag )
   {   
      for( i=0; i<2; i++ )
      {
         x+=i;
	     y=temp;
         for( j=0;j<8;j++ )
         {
            Lcd_Set_X_Y( x, y ); y++;
            Lcd_Write_Byte( point[ i*8 + j] );  
         } 
      }
   }
   else
   {
      for( i = 0; i < 2; i++ )
      {
         x += i;
         y = temp;
         for( j = 0; j < 8; j++ )
         {
            Lcd_Set_X_Y( x, y ); y++;
            Lcd_Write_Byte( ~point[ i * 8 + j ] );
         }
      }
   }
}
/****************************************************************************
* 名称：Lcd_Character_16X16( bit bit_flag, uchar x, uchar y, uchar code *point )
* 功能：显示16*16字符（汉字）       
* 入口参数：x y data
* 出口参数：无
*说明:bit_flag = 1 正常显示 bit_flag = 0 黑白反相显示
****************************************************************************/
void Lcd_Character_16X16( bit bit_flag, uchar x, uchar y, uchar code *point )
{
   uchar i,j,temp ;
   temp=y;
   if( bit_flag )
   {
      for( i=0; i<2; i++ )
      {
         x+=i;
	     y=temp;
         for( j=0;j<16;j++ )
         {
            Lcd_Set_X_Y( x, y ); y++;
            Lcd_Write_Byte( point[ i*16 + j] );  
         } 
      }
   }
   else
   {
      for( i = 0; i<2; i++ )
      {
         x += i;
         y = temp;
         for( j = 0; j < 16; j++ )
         {
            Lcd_Set_X_Y( x, y ); y++;
            Lcd_Write_Byte( ~ point[ i * 16 + j ] );
         }
      }
   }
}
/****************************************************************************
* 名称：Lcd_Clear(void)
* 功能：清屏        
* 入口参数：无
* 出口参数：无
****************************************************************************/
void Lcd_Clear()
{
   uchar i,j;
   cs1=1;cs2=1;
   for(i=0;i<8;i++)
   {
      Lcd_Set_X( i );
      Lcd_Set_Y( 0 );
      for(j=0;j<64;j++)
         Lcd_Write_Byte(0x00);
   }
}
/*******************************************************************************************
* 函数名称：Lcd_Initial()
* 功    能：初始化LCD
* 入口参数：无
* 出口参数：无
*********************************************************************************************/
void Lcd_Initial()
{  
   Lcd_Display_Off();
   Lcd_Write_Command(0xb8);     //Page_Add
   Lcd_Write_Command(0x40);     //Col_Add
   Lcd_Write_Command(0xc0);     //Start_Line
   Lcd_Display_On();
   Lcd_Clear();
}

/****************************************************************************
* 名称：Lcd_Time(uchar * clock_time )
* 功能：显示时间       
* 入口参数：无
* 出口参数：无                 
* 说明    : 时间数组 BCD 码形式
****************************************************************************/
void Lcd_Time(uchar * clock_time ,bit am)
{
   uchar i=0;
   //显示   "hour时min分sec秒"                                            
   i= * clock_time >> 4;
   Lcd_Character_16X8( 1, 2, 80, letter_logo[i]);    //显示   sec的高位
   i= * clock_time & 0x0f;
   Lcd_Character_16X8( 1, 2, 88, letter_logo[i]);    //显示   sec的低位
   Lcd_Character_16X16( 1, 2, 96 , time_logo[2]);  //显示   秒

   clock_time ++;
   i= *  clock_time >> 4;
   Lcd_Character_16X8( 1, 2, 48, letter_logo[i]);    //显示   min的高位
   i= * clock_time & 0x0f;
   Lcd_Character_16X8( 1, 2, 56, letter_logo[i]);   //显示   min的低位
   Lcd_Character_16X16( 1, 2, 64 , time_logo[1]);  //显示   分

   clock_time ++;
if (am == 0)
{  
   i= * clock_time >> 4;
   Lcd_Character_16X8( 1, 2, 16 , letter_logo[i]);    //显示   hour的高位
   i= * clock_time & 0x0f;
   Lcd_Character_16X8( 1, 2, 24 , letter_logo[i]);    //显示   hour的低位
   Lcd_Character_16X16( 1, 2, 32 , time_logo[0]);  //显示   分      
}   
if (am == 1)
{  
   i=(* clock_time>>4)*10+(* clock_time&0X0F);//BCD转HEX
   if(i>12){
         i -= 12;
         * clock_time = ((i/10)<<4) + ((i%10) & 0x0F);
         i= * clock_time >> 4;
         Lcd_Character_16X8( 1, 2, 16 , letter_logo[i]);    //显示   hour的高位
         i= * clock_time & 0x0f;
         Lcd_Character_16X8( 1, 2, 24 , letter_logo[i]);    //显示   hour的低位
         Lcd_Character_16X16( 1, 2, 32 , time_logo[0]);  //显示   分    
         }
   else
      {
      i= * clock_time >> 4;
      Lcd_Character_16X8( 1, 2, 16 , letter_logo[i]);    //显示   hour的高位
      i= * clock_time & 0x0f;
      Lcd_Character_16X8( 1, 2, 24 , letter_logo[i]);    //显示   hour的低位
      Lcd_Character_16X16( 1, 2, 32 , time_logo[0]);  //显示   分    
      }  
} 
}
/****************************************************************************
* 名称：Lcd_Data(uchar * clock_time )
* 功能：显示日期       
* 入口参数：无
* 出口参数：无                 
* 说明    : 时间数组 BCD 码形式
****************************************************************************/
void Lcd_Data(uchar * clock_time )
{
   uchar i=0;
   clock_time += 3;

   //显示   "year 年 month 月 day 日"                                                  
   i= * clock_time >> 4;
   Lcd_Character_16X8( 1, 0, 88, letter_logo[i]);  //显示   day的高位
   i= * clock_time & 0x0f;
   Lcd_Character_16X8( 1, 0, 96, letter_logo[i]);  //显示   day的低位  
   Lcd_Character_16X16( 1, 0, 104, data_logo[2]); //显示   日
   
   clock_time ++;
   i= * clock_time >> 4 ;
   Lcd_Character_16X8( 1, 0, 56, letter_logo[i]);  //显示   month的高位
   i= * clock_time & 0x0f;
   Lcd_Character_16X8( 1, 0, 64, letter_logo[i]); //显示   month的低位
   Lcd_Character_16X16( 1, 0, 72, data_logo[1]);   //显示   月
   
   clock_time += 2 ;   
   i= * clock_time >>  4;
   Lcd_Character_16X8( 1, 0, 24 , letter_logo[i]); //显示   year的高位
   i= * clock_time & 0x0f;
   Lcd_Character_16X8( 1, 0, 32 , letter_logo[i]); //显示   year的低位
   Lcd_Character_16X16( 1, 0, 40, data_logo[0]);   //显示   年
   Lcd_Character_16X8(1,0,8,letter_logo[2]);
   Lcd_Character_16X8(1,0,16,letter_logo[0]);
}
/****************************************************************************
* 名称：Lcd_Data(uchar * clock_time )
* 功能：显示日期       
* 入口参数：无
* 出口参数：无                 
* 说明    : 时间数组 BCD 码形式
****************************************************************************/
void Lcd_Week( uchar * clock_time )
{  
   uchar week = clock_time[6];
   Lcd_Character_16X16( 1, 6, 0,  week_logo[7] ); //星
   Lcd_Character_16X16( 1, 6, 16, week_logo[8] ); //期
   Lcd_Character_16X16( 1, 6, 32, week_logo[  week & 0x0f ] );
}
/******************************************************************************
* 函数名称: Lcd_Clock( uchar *clock_time )
* 功能: 显示时钟
* 入口参数: 时钟地址
* 出口参数: 无
********************************************************************************/
void Lcd_Clock( uchar * clock_time ,bit am)
{  
   Lcd_Data( clock_time ); //显示日期
   Lcd_Time( clock_time ,am); //显示时间
}
/******************************************************************************
* 名称: void Lcd_Lunar_Calendar( uchar * lunch_calendar )
* 功能: 显示农历
* 入口参数: 农历指针
* 出口参数: 无
*******************************************************************************/
void Lcd_Lunar_Calendar( uchar * lunar_canlendar )
{
   uint i,j,k;
  //农历
  // Lcd_Character_16X8(1,4,0,letter_logo[11]);
  // Lcd_Character_16X8(1,4,24,letter_logo[11]);  
 
   i= * lunar_canlendar >>  4;
   j= * lunar_canlendar & 0x0f; 
   k=i*10+j;
   if(k/10==01 && k%10>0)
   Lcd_Character_16X16(1,4,96,ucLunar[10]);
   else if(k/10==02 && k%10>0)
   Lcd_Character_16X16(1,4,96,ucLunar[19]);
   else if(k/10==01 )
   Lcd_Character_16X16(1,4,96,ucLunar[0]);
   else
   Lcd_Character_16X16(1,4,96,ucLunar[k/10]);

   if(!(k%10))
   Lcd_Character_16X16(1,4,112,ucLunar[10]);
   else
   Lcd_Character_16X16(1,4,112,ucLunar[k%10]);

 
//   Lcd_Character_16X16( 1, 4, 96, ucLunar[i] ); //农历天的高位
//   i= * lunar_canlendar & 0x0f;
//   Lcd_Character_16X16( 1, 4, 112, ucLunar[i] ); //农历天的低位
 // Lcd_Character_16X8( 1, 4, 88, letter_logo[11] ); //-

   lunar_canlendar ++;
   i= * lunar_canlendar >>  4;
   j= * lunar_canlendar & 0x0f;
   k=i*10+j;
   Lcd_Character_16X16( 1, 4, 80, data_logo[1] );// 显示‘月’
   if(k==1)
   Lcd_Character_16X16( 1, 4, 64, ucLunar[15] );
   else if(k==11)
   Lcd_Character_16X16( 1, 4, 64, ucLunar[16] );
   else if(k==12)
   Lcd_Character_16X16( 1, 4, 64, ucLunar[17] );
   else
   Lcd_Character_16X16( 1, 4, 64, ucLunar[k] );

   
  
   lunar_canlendar ++;
 
   i= * lunar_canlendar >>  4;
   j= * lunar_canlendar & 0x0f;
   k=i*10+j;
   Lcd_Character_16X16( 1, 4, 0, TianGan[(uint)(2000+k)%10] ); //农历年的天干
      i= * lunar_canlendar & 0x0f;
   Lcd_Character_16X16( 1, 4, 16, DiZhi[(uint)(2000+k)%12] ); //农历年的地支

   Lcd_Character_16X16( 1, 4, 32, SX[(uint)(2000+k)%12] );	 //生肖年 
   Lcd_Character_16X16( 1, 4, 48, data_logo[0] );// 显示‘年’
 }
/*******************************************************************************
* 名称: Lcd_Temperature( uchar * temperture )
* 功能: 显示温度
* 入口参数: 温度
* 出口参数: 无
*********************************************************************************/
void Lcd_Temperture( uchar * temperature )
{
  uchar temp;
 
  uchar sign=0;    //定义符号标志位,revised by iam3i

  if(temperature[1]>127)
  {
  sign=1;
  temperature[0]=(~temperature[0]+1);
  if((temperature[0])>=0xff)
  temperature[1]=(~temperature[1])+1;
  else
  temperature[1]=~temperature[1];
  }
  else
  sign=0;
  switch( * temperature & 0x0f )                    //查表 精确到 0.1  °C
   {
      case 0x00: temp = 0; break;
      case 0x01: temp = 1; break;
      case 0x02: temp = 1; break;
      case 0x03: temp = 2; break;
      case 0x04: temp = 2; break;
      case 0x05: temp = 3; break;
      case 0x06: temp = 4; break;
      case 0x07: temp = 4; break;
      case 0x08: temp = 5; break;
      case 0x09: temp = 6; break;
      case 0x0a: temp = 6; break;
      case 0x0b: temp = 7; break;
      case 0x0c: temp = 8; break;
      case 0x0d: temp = 8; break;
      case 0x0e: temp = 9; break;
      case 0x0f: temp = 9; break;
      default:  break;
   } 
 
   Lcd_Character_16X8( 1, 6, 56, letter_logo[12] );
   Lcd_Character_16X8( 1, 6, 64, letter_logo[10] );
   Lcd_Character_16X8( 1, 6, 120, temperture_logo[2] );    //   C 
   Lcd_Character_16X8( 1, 6, 112, temperture_logo[1] );    //   ° 
   Lcd_Character_16X8( 1, 6, 104, letter_logo[temp] );  //  小数位
   Lcd_Character_16X8( 1, 6, 96,  temperture_logo[0] );     //  .
   temp = ( * temperature ) >> 4;
   temperature++;
   temp |= ( * temperature ) << 4;
   Lcd_Character_16X8( 1, 6, 88, letter_logo[temp% 10 ] ); //个位
   if (temp/10==0 )
   Lcd_Character_16X8(1,6,80,letter_logo[13]);	//十位为0，不显示
   else
   Lcd_Character_16X8( 1, 6, 80, letter_logo[temp/10 ] );  //十位,该程序不能正确显示大于99.9度的温度
  
   if(sign==1) 
   Lcd_Character_16X8(1,6,72,letter_logo[11]);
   else
   Lcd_Character_16X8(1,6,72,letter_logo[13]);
   
/*   if( temp >= 30 )
      Lcd_Character_16X16( 1, 6, 112, sensor_inducator_logo[0] );  //大于30度显示图形
   else
   {
      if( temp < 20 )
	     Lcd_Character_16X16( 1, 6, 112, sensor_inducator_logo[2] );  //小于20度显示图形
	  else 
	     Lcd_Character_16X16( 1, 6, 112, sensor_inducator_logo[1] );  //大于20度小于30度显示图形
   }
*/
}

/***************************************************************************
*名称    ：Lcd_Set_Clock( uchar bit_flag, uchar *point )
*功能    ：显示调整的时间
*入口参数：flag(指示滚动位置),指针(时间数据的指针)
****************************************************************************/
void Lcd_Set_Clock( uchar flag, uchar *point )
{  
   
   bit year_flag = 1;
   bit month_flag = 1;
   bit day_flag = 1;
   bit hour_flag =1;
   bit minute_flag = 1;
   bit second_flag = 1;
   uchar i;
   if( flag == 1 ) //滚动到 second
     second_flag = 0;
   if( flag == 2 ) //滚动到 minute
      minute_flag = 0;
   if( flag == 3 ) //滚动到 hour
      hour_flag = 0;
   if( flag == 4 ) //滚动到 day
      day_flag = 0;
   if( flag == 5 ) //滚动到 month
      month_flag = 0;
   if( flag == 6 ) //滚动到 year
      year_flag = 0;
   //显示"日期"两个字
   Lcd_Character_16X16( 1, 2, 0 , data_time_logo[0] );
   Lcd_Character_16X16( 1, 2, 16, data_time_logo[1] );
   point += 6;    //指向年
   //显示年
   i = *point >> 4;  //高位
   Lcd_Character_16X8( year_flag, 2, 40, letter_logo[i] );
   i = *point & 0x0f; //低位
   Lcd_Character_16X8( year_flag, 2, 48, letter_logo[i] );
   //显示"-"
   Lcd_Character_16X8( 1, 2, 56, letter_logo[11] );
   point -= 2;   //指向月,跳过星期
   //显示月
   i = *point >>4;
   Lcd_Character_16X8( month_flag, 2, 64, letter_logo[i] );
   i = *point & 0x0f;
   Lcd_Character_16X8( month_flag, 2, 72, letter_logo[i] );      
   //显示"-""
   Lcd_Character_16X8( 1, 2, 80, letter_logo[11] );
   point --;   //指向日
   //显示日
   i = *point >>4;
   Lcd_Character_16X8( day_flag, 2, 88, letter_logo[i] );
   i = *point & 0x0f;
   Lcd_Character_16X8( day_flag, 2, 96, letter_logo[i] );
   //显示"时间"
   Lcd_Character_16X16( 1, 4, 0, data_time_logo[2] );
   Lcd_Character_16X16( 1, 4, 16, data_time_logo[3] );
   point -- ; //指向时
   //显示"小时"  
    i = *point >>4;
   Lcd_Character_16X8( hour_flag, 4, 40, letter_logo[i] );
   i = *point & 0x0f;
   Lcd_Character_16X8( hour_flag, 4, 48, letter_logo[i] );   
   //:
   Lcd_Character_16X8( 1, 4, 56, letter_logo[10] );
   point -- ;  //指向分
   //显示"分钟"
   i = *point >>4;
   Lcd_Character_16X8( minute_flag, 4, 64, letter_logo[i] );
   i = *point & 0xff;
   Lcd_Character_16X8( minute_flag, 4, 72, letter_logo[i] );
   //:
   Lcd_Character_16X8( 1, 4, 80, letter_logo[10] );
   point --;   //指向秒
   //显示"秒"
   i = *point >> 4;
   Lcd_Character_16X8( second_flag, 4, 88, letter_logo[i] );
   i = * point & 0x0f;
   Lcd_Character_16X8( second_flag, 4, 96, letter_logo[i] );
   

   
}
/**************************************************************************************
* 名称: Lcd_Menu( uchar temp )
* 功能: 滚动显示 时间设置 闹钟设置
* 入口参数: 滚动位置
* 出口参数: 无
**************************************************************************************/
void Lcd_Menu( uchar location )
{
   bit time_flag = 1;
   bit alarm_flag = 1;
   uchar i;
   if( location == 2 ) //滚动到 时间设置
      time_flag = 0;
   if( location == 1 ) //滚动到 闹钟设置
      alarm_flag = 0;
   //时间设置
   for(i=0;i<4;i++)
   {
      Lcd_Character_16X16( time_flag, 0, i*16, Menu_Logo[i] );//第一位表示阴阳,1为正常
   }
   //闹钟设置
   for(i=4;i<8;i++)
   {
      Lcd_Character_16X16( alarm_flag, 2, (i-4)*16, Menu_Logo[i] );
   }
   // Lcd_Character_16X16( alarm_flag, 2, 0, Menu_Logo[4] );
   // Lcd_Character_16X16( alarm_flag, 2, 16, Menu_Logo[5] );
   // Lcd_Character_16X16( alarm_flag, 2, 32, Menu_Logo[6] );
   // Lcd_Character_16X16( alarm_flag, 2, 48, Menu_Logo[7] );
}
/************************************************************************************
* 名称: Lcd_Alarm( uchar * alarm_time )
* 功能: 闹钟调整画面显示
* 入口参数: 闹钟地址
* 出口参数: 无
************************************************************************************/
void Lcd_Alarm( uchar temp, uchar * alarm_time )
{
   uchar i;
   bit hour_flag = 1;
   bit minute_flag = 1;
   if( temp == 1 )
      minute_flag = 0;
   if( temp == 2 )
      hour_flag = 0;
   Lcd_Character_16X16( 1, 0, 0, alarm_logo[0] ); //显示闹钟标志
   // 小时:分钟
   Lcd_Character_16X16( 1, 0, 16, alarm_logo[1] );
   Lcd_Character_16X16( 1, 0, 32, alarm_logo[2] );
   Lcd_Character_16X8( 1, 0, 48, letter_logo[10] );
   Lcd_Character_16X16( 1, 0, 56, alarm_logo[3] );
   Lcd_Character_16X16( 1, 0, 72, alarm_logo[4] );


   i = ( *  ( alarm_time + 1 ) ) / 10;
   Lcd_Character_16X8( hour_flag, 2, 32, letter_logo[i] ); //显示时的高位 
   i = ( * ( alarm_time + 1 )  ) % 10;
   Lcd_Character_16X8( hour_flag, 2, 40, letter_logo[i] ); //显示时的低位
   Lcd_Character_16X8( 1, 2, 48, letter_logo[10] ); //:

   i = ( *  ( alarm_time ) ) / 10;
   Lcd_Character_16X8( minute_flag, 2, 56, letter_logo[i] ); //显示分的高位 
   i = ( * ( alarm_time  ) ) % 10;
   Lcd_Character_16X8( minute_flag, 2, 64, letter_logo[i] ); //显示分的低位
}
/********************************************************************************/
#endif
