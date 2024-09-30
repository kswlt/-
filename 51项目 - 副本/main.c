#include <REGX52.H>
#include "Delay.h"
#include "Nixie.h"
#include "DS1302.h"
#include "LCD1602.h"
#include "Key.h"
#include "Timer0.h"
#include "Buzzer.h"
//sbit Buzzer=P1^5;
//风
//unsigned char code NixieTable[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
//unsigned char Second,Minute;
//unsigned char time_buf[7]={0};
unsigned char KeyNum,MODE,TimeSetSelect,TimeSetFlashFlag;
unsigned int i;
unsigned char AlarmTime[7] = {24,9,28,11,34,55,6}; 
unsigned char AlarmEnabled = 0; 
unsigned char AlarmDuration = 0; 
unsigned char AlarmTriggered = 0;
void TimeShow(void)
{

	    DS1302_ReadTime();//读取时间
			LCD_ShowNum(1,1,DS1302_Time[0],2);//显示年
			LCD_ShowNum(1,4,DS1302_Time[1],2);//显示月
			LCD_ShowNum(1,7,DS1302_Time[2],2);//显示日
			LCD_ShowNum(2,1,DS1302_Time[3],2);//显示时
			LCD_ShowNum(2,4,DS1302_Time[4],2);//显示分
			LCD_ShowNum(2,7,DS1302_Time[5],2);//显示秒
				 
			 
			/* if ( 
        DS1302_Time[0] == AlarmTime[0] && 
        DS1302_Time[1] == AlarmTime[1] && 
        DS1302_Time[2] == AlarmTime[2] && 
        DS1302_Time[3] == AlarmTime[3] && 
        DS1302_Time[4] == AlarmTime[4] && 
        DS1302_Time[5] == AlarmTime[5]) {
        // 触发闹钟

            //Buzzer_Time(111); // 蜂鸣器响起
            Delay(100);
            //Buzzer_Time(100); // 蜂鸣器关闭
            //Delay(100);
        }
			 
			 
			 */
	
}



void TimeSet(void)
{

//P2=0X00;

	if(KeyNum==2)
	{
	
	  TimeSetSelect++;
		if(TimeSetSelect>5)TimeSetSelect=0;
	//yue jie qing 0
	  
	}
	
	
	//LCD_ShowNum(2,10,TimeSetSelect,2);
	
	
	if(KeyNum==3)
	{
	   DS1302_Time[TimeSetSelect]++;
	
	
	}
	

	
	if(KeyNum==4)
	{
	   DS1302_Time[TimeSetSelect]--;
	
	
	}
	
	    LCD_ShowNum(1,1,DS1302_Time[0],2);//显示年
			LCD_ShowNum(1,4,DS1302_Time[1],2);//显示月
			LCD_ShowNum(1,7,DS1302_Time[2],2);//显示日
			LCD_ShowNum(2,1,DS1302_Time[3],2);//显示时
			LCD_ShowNum(2,4,DS1302_Time[4],2);//显示分
			LCD_ShowNum(2,7,DS1302_Time[5],2);//显示秒
				 
	
}




/*void SetAlarm(void) {
    if (KeyNum == 2) {
        TimeSetSelect++;
			//  if (TimeSetSelect==6) {Buzzer_Time(3000);}
        if (TimeSetSelect > 6) {TimeSetSelect = 0;} // 循环选择
        //Buzzer_Time(150);
		} 
////	//////////////////////////3////////////////////////////////
		
		
		    else if (KeyNum == 3) {
                 if (TimeSetSelect < 6) { 
               AlarmTime[TimeSetSelect]++;
		    		    	Buzzer_Time(50);
               //Buzzer_Time(111); // 提示音
           } 
								 
					 
					 else if (TimeSetSelect == 6) {
		    		   //Buzzer_Time(3000);
               if (AlarmDuration < 15) {
                   AlarmDuration += 5;  // 选择响铃时长
								 
								 
								 
								 
								
			  				Buzzer_Time(2000);
                } 
							 
								
								
								else {
                   AlarmDuration = 5; // 循环回到5秒
               }
             // Buzzer_Time(111); // 提示音
          }
    }


///////////////////////////4///////////////////////////////
		          else if (KeyNum == 4) {
								
								
               if (TimeSetSelect < 6) {
                AlarmTime[TimeSetSelect]--;
                Buzzer_Time(111); // 提示音
             } 
							 
						    else if (TimeSetSelect == 6) {
							 
							 
							 
                 if (AlarmDuration==6) {
                    AlarmDuration -= 5; // 选择响铃时长
               } 
								 
							    Buzzer_Time(2000);
							 else {
                   AlarmDuration = 15; // 循环回到15秒
              }
                Buzzer_Time(111); // 提示音
        }
    }

    // 在LCD上显示设置的闹钟时间
    LCD_ShowNum(1, 1, AlarmTime[0], 2); // 显示年
    LCD_ShowNum(1, 4, AlarmTime[1], 2); // 显示月
    LCD_ShowNum(1, 7, AlarmTime[2], 2); // 显示日
    LCD_ShowNum(2, 1, AlarmTime[3], 2); // 显示时
    LCD_ShowNum(2, 4, AlarmTime[4], 2); // 显示分
    LCD_ShowNum(2, 7, AlarmTime[5], 2); // 显示秒

}

*/
void SetAlarm(void) {
    if (KeyNum == 2) {
        TimeSetSelect++;
       // if (TimeSetSelect == 6) { Buzzer_Time(3000); }
        if (TimeSetSelect > 6) { TimeSetSelect = 0; } // 循环选择
    } else if (KeyNum == 3) {
        if (TimeSetSelect < 6) {
            AlarmTime[TimeSetSelect]++;
            Buzzer_Time(50);
        } else if (TimeSetSelect == 6) {
            if (AlarmDuration < 15) {
                AlarmDuration += 5;  // 选择响铃时长
                Buzzer_Time(2000);
            } else {
                AlarmDuration = 5; // 循环回到5秒
            }
        }
    } else if (KeyNum == 4) {
        if (TimeSetSelect < 6) {
            AlarmTime[TimeSetSelect]--;
            Buzzer_Time(111); // 提示音
        } else if (TimeSetSelect == 6) {
            if (AlarmDuration >= 15) {
                AlarmDuration -= 5; // 选择响铃时长
            } else {
                AlarmDuration = 15; // 循环回到15秒
            }
            Buzzer_Time(2000);
            Buzzer_Time(111); // 提示音
        }
    }

    // 在LCD上显示设置的闹钟时间
    LCD_ShowNum(1, 1, AlarmTime[0], 2); // 显示年
    LCD_ShowNum(1, 4, AlarmTime[1], 2); // 显示月
    LCD_ShowNum(1, 7, AlarmTime[2], 2); // 显示日
    LCD_ShowNum(2, 1, AlarmTime[3], 2); // 显示时
    LCD_ShowNum(2, 4, AlarmTime[4], 2); // 显示分
    LCD_ShowNum(2, 7, AlarmTime[5], 2); // 显示秒
}






void main()
{
	  LCD_Init();
	  DS1302_Init();
	  
	  LCD_ShowString(1,1,"  -  -  ");//静态字符初始化显示
		LCD_ShowString(2,1,"  :  :  ");
	  //Second=DS1302_ReadByte(0x81);
	  //Minute=DS1302_ReadByte(0x83);
		//DS1302_ReadTime();
	  DS1302_SetTime();//设置时间
	//Delay(5000);
	//while(KeyNum == 1){Buzzer_Time(1000);}
	
     while (1) {
        KeyNum = Key();
        if (KeyNum == 1) {
            if (MODE == 0) {
                MODE = 1;
            } else if (MODE == 1) {
                MODE = 2;
            } else if (MODE == 2) {
                MODE = 0;
                AlarmEnabled = 1; // 退出设置模式时启用闹钟
            }
        }

        switch (MODE) {
            case 0:
                TimeShow();
                break;
            case 1:
                TimeSet();
                break;
            case 2:
                SetAlarm();
                break;
        }
    
			  if (AlarmEnabled && !AlarmTriggered && 
            DS1302_Time[0] == AlarmTime[0] && 
            DS1302_Time[1] == AlarmTime[1] && 
            DS1302_Time[2] == AlarmTime[2] && 
            DS1302_Time[3] == AlarmTime[3] && 
            DS1302_Time[4] == AlarmTime[4] && 
            DS1302_Time[5] == AlarmTime[5]) {
            // 触发闹钟
						if(AlarmDuration==5){Buzzer_Time(500);} // 蜂鸣器响起}
            if(AlarmDuration==10)

            {Buzzer_Time(500);
						Delay(100);
						Buzzer_Time(500);
						Delay(100);	
							
						}
						if(AlarmDuration==15){Buzzer_Time(2000);}
						/*Delay(1000);
            Buzzer_Time(100);
						Delay(100);
						Buzzer_Time(100); // 蜂鸣器响起
						Delay(100); // 蜂鸣器关闭
						*/
            AlarmTriggered = 1; // 标记闹钟已被触发
							
						}
            // 启动一个定时器或者使用其他方法来控制闹钟响铃的时间长度
        }
			   /* if (AlarmTriggered) {
            // 假设我们使用一个全局变量 i 来计数
            if (i >= 60) { // 假设每秒更新一次 i
                AlarmTriggered = 0; // 重置闹钟标志
                i = 0; // 重置计数器
            } else {
                i++; // 计数
            }
        }
			 */
			 /*DS1302_ReadTime();//DS1302读取时间，读取值为BCD码
						time_buf[0]= time[DS1302_Time[3]/16];//ݫBCDëתΪʮ޸׆ìҢȒ՚˽ةא֒սהӦʮ޸׆ք׎ѡëûСʱ֚һλû
					time_buf[1]= time[DS1302_Time[3]&0x0f];//ݫBCDëתΪʮ޸׆ìҢȒ՚˽ةא֒սהӦʮ޸׆ք׎ѡëûСʱք֚׾λû
					time_buf[2]=0x40;//ٱʽ࠘׆-û
					time_buf[3]= time[DS1302_Time[4]/16];//ݫBCDëתΪʮ޸׆ìҢȒ՚˽ةא֒սהӦʮ޸׆ք׎ѡëûؖדք֚һλû
					time_buf[4]= time[DS1302_Time[4]&0x0f];//ݫBCDëתΪʮ޸׆ìҢȒ՚˽ةא֒սהӦʮ޸׆ք׎ѡëûؖדք֚׾λû
					time_buf[5]=0x40;//ٱʽ࠘׆-û
					time_buf[6]= time[DS1302_Time[5]/16];//ݫBCDëתΪʮ޸׆ìҢȒ՚˽ةא֒սהӦʮ޸׆ք׎ѡëûīք֚һλû
					time_buf[7]= time[DS1302_Time[5]&0x0f];
          Nixie(time_buf);
*/
				
			
//Buzzer_Time(100);				
				
}
		 
	 