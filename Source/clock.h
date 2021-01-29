#ifndef _CLOCK_DS1302_H
#define _CLOCK_DS1302_H
/*****************************预定义**************************************/
#define uchar unsigned char
#define uint unsigned int
/***************************DS1302管脚配置****************************/
sbit IO  = P1^0;       
sbit SCLK= P1^1;
sbit RST = P1^2;
/*********************为了编程方便定义的位变量**********************/
sbit ACC0 = ACC ^ 0;
sbit ACC7 = ACC ^ 7;
#define second_address	0x80
#define minute_address	0x82
#define hour_address	0x84 
#define day_address	    0x86
#define month_address	0x88
#define year_address	0x8C
/********************************************************************************************
* 函数名称：Clock_Write_Byte()
* 功    能：向时钟DS1302写入一个字节
* 入口参数：byte
* 出口参数：无
*********************************************************************************************/
void Clock_Write_Byte(uchar byte)
{
    uchar count;
    ACC=byte;
    for(count = 8; count > 0; count--)
    {
        IO = ACC0;    //低位到高位依次传输
        SCLK = 1;
        SCLK = 0;
        ACC = ACC >> 1; 
    } 
}
/********************************************************************************************
* 函数名称：Clock_Read_Byte()
* 功    能：从时钟DS1302读取一个字节
* 入口参数：无
* 出口参数：ACC(一个Byte的数据)
*********************************************************************************************/
uchar Clock_Read_Byte(void)
{
	uchar count;
    for(count = 8; count > 0; count--)
    {
        ACC = ACC >>1;         			
        ACC7= IO;   //高位到低位依次读取
		SCLK = 1;
        SCLK = 0;
	} 
    return(ACC);
}
/********************************************************************************************
* 函数名称：Clock_Write_Time()
* 功    能：向时钟写入一个时间
* 入口参数：地址 时间数据 
* 出口参数：无
*********************************************************************************************/
void Clock_Write_Time(uchar address, uchar time)
{
	SCLK=0;
	RST=0;
	RST=1;
	Clock_Write_Byte(address);
	Clock_Write_Byte(time);
	RST=0;
	SCLK=1;
}
/********************************************************************************************
* 函数名称：Clock_Read_Time()
* 功    能：从时钟读出一个时间
* 入口参数：时间地址  
* 出口参数：时间数据
*********************************************************************************************/
uchar Clock_Read_Time(uchar address)
{
	uchar time=0;
	SCLK=0;
	RST=0;
	RST=1;
	Clock_Write_Byte( address|0x01 );
	time=Clock_Read_Byte();
	RST=0;
	SCLK=1;
	return(time);
}

// /********************************************************************************************
// * 函数名称：Clock_Initial()
// * 功    能：时钟初始化
// * 入口参数：时间地址   时间数据
// * 出口参数：
// *********************************************************************************************/
void Clock_Initial(uchar *clock_time )
{
    Clock_Write_Time(0x8e,0x00);                //WP=0 写操作
    *clock_time &= 0x7f;                             //最高位为 0 时钟芯片工作
	Clock_Write_Time( second_address, * clock_time );   //秒
    clock_time ++;
    Clock_Write_Time( minute_address, * clock_time );    //分
    clock_time ++;
    Clock_Write_Time( hour_address, * clock_time );     //时
    clock_time ++;
    Clock_Write_Time( day_address, * clock_time );      //日
    clock_time ++;
    Clock_Write_Time( month_address, * clock_time);   //月
	clock_time += 2;
    Clock_Write_Time( year_address, * clock_time );    //年
    Clock_Write_Time( 0x8e,0x80);              //WP=1 写保护	
}

// /********************************************************************************************
// * 函数名称：Clock_Fresh( uchar * clock_time )
// * 功    能：从时钟DS1302读出时间
// * 入口参数：时间地址  
// * 出口参数：时间数据
// *********************************************************************************************/
void Clock_Fresh(uchar * clock_time )
{
    uchar i = 0, addrres = 0x80; //1000 0001 最后1为读
	for (i = 0; i < 7; i++)
	{
		clock_time[i] = Clock_Read_Time(addrres);
		addrres += 2;
	}
}
/********************************************************************************/

// unchar Read_Data(unchar addr)//根据传入的地址数据,给出每一位寄存器的8位数据
// {
// 	unchar datas;
// 	RST = 0;
// 	SCLK = 0;
// 	RST = 1;
// 	Clock_Write_Byte(addr);	  //发送地址命令字节,控制读还是写,这里是读
// 	datas = Clock_Read_Byte(); //读取寄存器内容
// 	SCLK = 1;
// 	RST = 0;
// 	return datas;
// }
// void GetTime(unchar *clock_time)
// {
// 	unchar i = 0, addr = 0x81; //1000 0001 最后1为读
// 	for (i = 0; i < 7; i++)
// 	{
// 		clock_time[i] = Read_Data(addr);
// 		addr += 2;
// 	}
// }
#endif
