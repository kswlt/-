#include <REGX52.H>
//#include "Delay.h"
//#include "Nixie.h"

sbit DS1302_SCLK=P3^6;
//P3口  ^取位
sbit DS1302_IO=P3^4;
sbit DS1302_CE=P3^5;
//读写
//把CE置1

//全局
#define  DS1302_SECOND		0X80
#define  DS1302_MINUTE  	0X82
#define  DS1302_HOUR	    0X84
#define  DS1302_DATE	    0X86
#define  DS1302_MONTH       0X88
#define  DS1302_DAY         0X8A
#define  DS1302_YEAR        0X8C
#define  DS1302_WP          0X8E 
char DS1302_Time[]={24,9,28,11,34,55,6};
char DS1302_Time2[]={24,9,28,11,34,55,6};
//////////jia
void DS1302_Init(void)
{
   DS1302_CE=0;
	 //DS1302_IO=0;
	 DS1302_SCLK=0;
	//////////////////////////////
}
void DS1302_WriteByte(unsigned char Command,Data)
{
   unsigned char i;
	
	DS1302_CE=1;
//把第0位取出来
	for(i=0;i<8;i++){
		
	//left i wei
	 DS1302_IO=Command&(0x01<<i);
	 DS1302_SCLK=1;
	 DS1302_SCLK=0;
	}
	
	for(i=0;i<8;i++){
		
	//left i wei
	 DS1302_IO=Data&(0x01<<i);
	 DS1302_SCLK=1;
	 DS1302_SCLK=0;
	}
	
		DS1302_CE=0;
	
	
	
	
	
	/*
	
	
   DS1302_IO=Command&0x01;
	 DS1302_SCLK=1;
	 DS1302_SCLK=0;
	
	 DS1302_IO=Command&0x02;

*/

}
unsigned char DS1302_ReadByte(unsigned char Command)
{
		unsigned char i,Data=0x00;
	Command|=0x01;
	DS1302_CE=1;
	for(i=0;i<8;i++){
		
	//left i wei
	 DS1302_IO=Command&(0x01<<i);
	 DS1302_SCLK=0;
	 DS1302_SCLK=1;
	}
	 for(i=0;i<8;i++)
	 {
	 DS1302_SCLK=1;
   DS1302_SCLK=0;
	 if(DS1302_IO){Data=Data|(0x01<<i);}
	 
	 }
	 
	 /*DS1302_SCLK=0;
   DS1302_SCLK=1;
	 if(DS1302_IO){Data=Data|0x01;}
	 
	 DS1302_SCLK=0;
   DS1302_SCLK=1;
	 if(DS1302_IO){Data=Data|0x02;}
	*/

	 DS1302_CE=0;
	 DS1302_IO=0;
	 return Data;
	 
}


void DS1302_SetTime(void)
{
   // DS1302_WriteByte(0x8e,0x00);
	//guan bao hu 
	DS1302_WriteByte(DS1302_WP,0x00);
	DS1302_WriteByte(DS1302_YEAR,DS1302_Time[0]/10*16+DS1302_Time[0]%10);//十进制转BCD码后写入
	DS1302_WriteByte(DS1302_MONTH,DS1302_Time[1]/10*16+DS1302_Time[1]%10);
	DS1302_WriteByte(DS1302_DATE,DS1302_Time[2]/10*16+DS1302_Time[2]%10);
	DS1302_WriteByte(DS1302_HOUR,DS1302_Time[3]/10*16+DS1302_Time[3]%10);
	DS1302_WriteByte(DS1302_MINUTE,DS1302_Time[4]/10*16+DS1302_Time[4]%10);
	DS1302_WriteByte(DS1302_SECOND,DS1302_Time[5]/10*16+DS1302_Time[5]%10);
	DS1302_WriteByte(DS1302_DAY,DS1302_Time[6]/10*16+DS1302_Time[6]%10);
	DS1302_WriteByte(DS1302_WP,0x80);
}

void DS1302_ReadTime(void)
{
	  unsigned char Temp;
	Temp=DS1302_ReadByte(DS1302_YEAR);
	DS1302_Time[0]=Temp/16*10+Temp%16;//BCD码转十进制后读取
	Temp=DS1302_ReadByte(DS1302_MONTH);
	DS1302_Time[1]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_DATE);
	DS1302_Time[2]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_HOUR);
	DS1302_Time[3]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_MINUTE);
	DS1302_Time[4]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_SECOND);
	DS1302_Time[5]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_DAY);
	DS1302_Time[6]=Temp/16*10+Temp%16;
}
