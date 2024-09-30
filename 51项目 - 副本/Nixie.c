

#include <REGX52.H>
#include "Delay.h"


unsigned char NixieTable[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

/*
void Nixie(unsigned char Location,Number)
{
	switch(Location)		//位码输出
	{
		case 1:P2_4=1;P2_3=1;P2_2=1;break;
		case 2:P2_4=1;P2_3=1;P2_2=0;break;
		case 3:P2_4=1;P2_3=0;P2_2=1;break;
		case 4:P2_4=1;P2_3=0;P2_2=0;break;
		case 5:P2_4=0;P2_3=1;P2_2=1;break;
		case 6:P2_4=0;P2_3=1;P2_2=0;break;
		case 7:P2_4=0;P2_3=0;P2_2=1;break;
		case 8:P2_4=0;P2_3=0;P2_2=0;break;
	}
	P0=NixieTable[Number];	//段码输出
	Delay(1);				//显示一段时间
	P0=0x00;				//段码清0，消影
}

*/

void Nixie(unsigned char dat[])
{
	unsigned char i=0;
	for(i=0;i<8;i++)
	{
	   	switch(i)
		{
		case 0:	P2_4=1;	P2_3=1;	P2_2=1;break;
		case 1:	P2_4=1;	P2_3=1;	P2_2=0;break;
		case 2:	P2_4=1;	P2_3=0;	P2_2=1;break;
		case 3:	P2_4=1;	P2_3=0;	P2_2=0;break;
		case 4:	P2_4=0;	P2_3=1;	P2_2=1;break;
		case 5:	P2_4=0;	P2_3=1;	P2_2=0;break;
		case 6:	P2_4=0;	P2_3=0;	P2_2=1;break;
		case 7:	P2_4=0;	P2_3=0;	P2_2=0;break; 
		}
			P0=dat[i];
		Delay(1);
		P0=0x00;
	}
}
