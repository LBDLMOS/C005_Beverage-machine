/*********************************************************************************************
模板制作：  杜洋工作室/洋桃电子
程序名：	FLASH读写LED状态程序
编写人：	杜洋	
编写时间：	2017年12月30日
硬件支持：	STM32F103C8   外部晶振8MHz RCC函数设置主频72MHz　  

修改日志：　　
1-	
	
							
说明：
 # 本模板加载了STM32F103内部的RCC时钟设置，并加入了利用滴答定时器的延时函数。
 # 可根据自己的需要增加或删减。

*********************************************************************************************/
#include "stm32f10x.h" //STM32头文件
#include "sys.h"
#include "delay.h"
#include "led.h"
#include "flash.h" 
#include "usart.h"
#include "rtc.h"
#include "KEYPAD4x4.h"
#include "tm1640.h"
#include "buzzer.h"
#include "key.h"

#define FLASH_START_ADDR1  0x0801f000	  //写入的起始地址
#define FLASH_START_ADDR2  0x0801f016	  //写入的起始地址
#define sleep_us 100//间隔时间



int main (void){//主程序
	u16 a; //定义变量
//	u8 t[2];
	u16 pwd=0;
	u8 pw=0,err=0;
	u8 zt=0,admin=0;
	//初始化程序
	RCC_Configuration(); //时钟设置
	RTC_Config();
	KEY_Init();
	KEYPAD4x4_Init();
	TM1640_Init();
	LED_Init();//LED初始化
  USART1_Init(115200);//串口1初始化并启动
  BUZZER_Init();
	
  a = FLASH_R(FLASH_START_ADDR1);//从指定页的地址读FLASH
	err = FLASH_R(FLASH_START_ADDR2);//从指定页的地址读FLASH
//	MIDI_PLAY();
//    if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5){//判断寄存数据是否丢失
//		USART1_printf("输入时分秒");
//	//调时
//			delay_us(100);
//			if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE) != RESET){  //查询串口待处理标志位
//				t[0] =USART_ReceiveData(USART1);//读取接收到的数据}
//			delay_us(100);
//			USART1_printf("时完成");}else{BUZZER_BEEP1();}
//			delay_us(100);
//			if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE) != RESET){  //查询串口待处理标志位
//				t[1] =USART_ReceiveData(USART1);//读取接收到的数据}
//			delay_us(100);
//			USART1_printf("分完成");}else{BUZZER_BEEP1();}
//			delay_us(100);
//			RTC_Set(2020,6,18,t[0],t[1],0);}
	
	if(!GPIO_ReadInputDataBit(KEYPORT,KEY1)){
		err=0;
		FLASH_W(FLASH_START_ADDR2,err);
		BUZZER_BEEP1();BUZZER_BEEP1();
		admin=1;}

	//主循环
	while(1){
//		 if (RTC_Get()==0){
//			TM1640_display(0,rhour/10); //时
//			TM1640_display(1,rhour%10+10);
//			TM1640_display(2,rmin/10); //分
//			TM1640_display(3,rmin%10+10);}
		 
		 if(err==5) {MIDI_PLAY(); while(1);}
		
		 pw=KEYPAD4x4_Read();
		 
		 switch(pw){//对比数据值
			case 11: zt=1;BUZZER_BEEP1(); break;//A 出水
			case 12: zt=2;BUZZER_BEEP1(); break;//B 停水
			case 13: zt=3;BUZZER_BEEP1(); break;//C 改密
			case 14: zt=4;BUZZER_BEEP1(); break;//D 锁定
			case 15: pwd=0;zt=0;BUZZER_BEEP1();BUZZER_BEEP1(); break;//* 清空
			case 16: zt=5; break;//# 预留
			case 1: pwd=pwd*10+pw;BUZZER_BEEP1(); break;//1
			case 2: pwd=pwd*10+pw;BUZZER_BEEP1(); break;//2
			case 3: pwd=pwd*10+pw;BUZZER_BEEP1(); break;//3
			case 4: pwd=pwd*10+pw;BUZZER_BEEP1(); break;//4
			case 5: pwd=pwd*10+pw;BUZZER_BEEP1(); break;//5
			case 6: pwd=pwd*10+pw;BUZZER_BEEP1(); break;//6
			case 7: pwd=pwd*10+pw;BUZZER_BEEP1(); break;//7
			case 8: pwd=pwd*10+pw;BUZZER_BEEP1(); break;//8
			case 9: pwd=pwd*10+pw;BUZZER_BEEP1(); break;//9
			case 10: pwd=pwd*10;BUZZER_BEEP1(); break;//0
		}
		
		switch(zt){
			case 1:
				if(pwd==a) GPIO_WriteBit(LEDPORT,LED1,(BitAction)(1));
				if(pwd==0) GPIO_WriteBit(LEDPORT,LED2,(BitAction)(1));
				if((pwd!=a) && (pwd!=0)) BUZZER_BEEP1();BUZZER_BEEP1();BUZZER_BEEP1();err=err+1;FLASH_W(FLASH_START_ADDR2,err);
				pwd=0;pw=0;
			case 2:
				GPIO_WriteBit(LEDPORT,LED1,(BitAction)(0));
				GPIO_WriteBit(LEDPORT,LED2,(BitAction)(0));
				pwd=0;pw=0;BUZZER_BEEP1();
			case 3:
				BUZZER_BEEP1();
				if (admin==1) {FLASH_W(FLASH_START_ADDR1,pwd);BUZZER_BEEP1();BUZZER_BEEP1();}
				else 	{BUZZER_BEEP1();BUZZER_BEEP1();BUZZER_BEEP1();BUZZER_BEEP1();}
			case 4:
				BUZZER_BEEP1();BUZZER_BEEP1();BUZZER_BEEP1();BUZZER_BEEP1();BUZZER_BEEP1();
				err=5;
		}
		delay_us(sleep_us);
	}
}


/*********************************************************************************************
 * 杜洋工作室 www.DoYoung.net
 * 洋桃电子 www.DoYoung.net/YT 
*********************************************************************************************/
/*

【变量定义】
u32     a; //定义32位无符号变量a
u16     a; //定义16位无符号变量a
u8     a; //定义8位无符号变量a
vu32     a; //定义易变的32位无符号变量a
vu16     a; //定义易变的 16位无符号变量a
vu8     a; //定义易变的 8位无符号变量a
uc32     a; //定义只读的32位无符号变量a
uc16     a; //定义只读 的16位无符号变量a
uc8     a; //定义只读 的8位无符号变量a

#define ONE  1   //宏定义

delay_us(1); //延时1微秒
delay_ms(1); //延时1毫秒
delay_s(1); //延时1秒

*/
