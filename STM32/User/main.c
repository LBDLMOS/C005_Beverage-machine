/*********************************************************************************************
ģ��������  ��������/���ҵ���
��������	FLASH��дLED״̬����
��д�ˣ�	����	
��дʱ�䣺	2017��12��30��
Ӳ��֧�֣�	STM32F103C8   �ⲿ����8MHz RCC����������Ƶ72MHz��  

�޸���־������
1-	
	
							
˵����
 # ��ģ�������STM32F103�ڲ���RCCʱ�����ã������������õδ�ʱ������ʱ������
 # �ɸ����Լ�����Ҫ���ӻ�ɾ����

*********************************************************************************************/
#include "stm32f10x.h" //STM32ͷ�ļ�
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

#define FLASH_START_ADDR1  0x0801f000	  //д�����ʼ��ַ
#define FLASH_START_ADDR2  0x0801f016	  //д�����ʼ��ַ
#define sleep_us 100//���ʱ��



int main (void){//������
	u16 a; //�������
//	u8 t[2];
	u16 pwd=0;
	u8 pw=0,err=0;
	u8 zt=0,admin=0;
	//��ʼ������
	RCC_Configuration(); //ʱ������
	RTC_Config();
	KEY_Init();
	KEYPAD4x4_Init();
	TM1640_Init();
	LED_Init();//LED��ʼ��
  USART1_Init(115200);//����1��ʼ��������
  BUZZER_Init();
	
  a = FLASH_R(FLASH_START_ADDR1);//��ָ��ҳ�ĵ�ַ��FLASH
	err = FLASH_R(FLASH_START_ADDR2);//��ָ��ҳ�ĵ�ַ��FLASH
//	MIDI_PLAY();
//    if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5){//�жϼĴ������Ƿ�ʧ
//		USART1_printf("����ʱ����");
//	//��ʱ
//			delay_us(100);
//			if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE) != RESET){  //��ѯ���ڴ������־λ
//				t[0] =USART_ReceiveData(USART1);//��ȡ���յ�������}
//			delay_us(100);
//			USART1_printf("ʱ���");}else{BUZZER_BEEP1();}
//			delay_us(100);
//			if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE) != RESET){  //��ѯ���ڴ������־λ
//				t[1] =USART_ReceiveData(USART1);//��ȡ���յ�������}
//			delay_us(100);
//			USART1_printf("�����");}else{BUZZER_BEEP1();}
//			delay_us(100);
//			RTC_Set(2020,6,18,t[0],t[1],0);}
	
	if(!GPIO_ReadInputDataBit(KEYPORT,KEY1)){
		err=0;
		FLASH_W(FLASH_START_ADDR2,err);
		BUZZER_BEEP1();BUZZER_BEEP1();
		admin=1;}

	//��ѭ��
	while(1){
//		 if (RTC_Get()==0){
//			TM1640_display(0,rhour/10); //ʱ
//			TM1640_display(1,rhour%10+10);
//			TM1640_display(2,rmin/10); //��
//			TM1640_display(3,rmin%10+10);}
		 
		 if(err==5) {MIDI_PLAY(); while(1);}
		
		 pw=KEYPAD4x4_Read();
		 
		 switch(pw){//�Ա�����ֵ
			case 11: zt=1;BUZZER_BEEP1(); break;//A ��ˮ
			case 12: zt=2;BUZZER_BEEP1(); break;//B ͣˮ
			case 13: zt=3;BUZZER_BEEP1(); break;//C ����
			case 14: zt=4;BUZZER_BEEP1(); break;//D ����
			case 15: pwd=0;zt=0;BUZZER_BEEP1();BUZZER_BEEP1(); break;//* ���
			case 16: zt=5; break;//# Ԥ��
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
 * �������� www.DoYoung.net
 * ���ҵ��� www.DoYoung.net/YT 
*********************************************************************************************/
/*

���������塿
u32     a; //����32λ�޷��ű���a
u16     a; //����16λ�޷��ű���a
u8     a; //����8λ�޷��ű���a
vu32     a; //�����ױ��32λ�޷��ű���a
vu16     a; //�����ױ�� 16λ�޷��ű���a
vu8     a; //�����ױ�� 8λ�޷��ű���a
uc32     a; //����ֻ����32λ�޷��ű���a
uc16     a; //����ֻ�� ��16λ�޷��ű���a
uc8     a; //����ֻ�� ��8λ�޷��ű���a

#define ONE  1   //�궨��

delay_us(1); //��ʱ1΢��
delay_ms(1); //��ʱ1����
delay_s(1); //��ʱ1��

*/
