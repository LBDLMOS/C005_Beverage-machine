#ifndef __KEYPAD4x4_H
#define __KEYPAD4x4_H	 
#include "sys.h"
#include "delay.h"


#define KEYPAD4x4PORT	GPIOB	//����IO�ӿ���
#define KEY1	GPIO_Pin_6	//����IO�ӿ�
#define KEY2	GPIO_Pin_7	//����IO�ӿ�
#define KEY3	GPIO_Pin_8	//����IO�ӿ�
#define KEY4	GPIO_Pin_9	//����IO�ӿ�
#define KEYa	GPIO_Pin_10	//����IO�ӿ�
#define KEYb	GPIO_Pin_11//����IO�ӿ�
#define KEYc	GPIO_Pin_12//����IO�ӿ�
#define KEYd	GPIO_Pin_15	//����IO�ӿ�


void KEYPAD4x4_Init(void);//��ʼ��
void KEYPAD4x4_Init2(void);//��ʼ��2������IO������ʽ��ת��
u8 KEYPAD4x4_Read (void);//�����м���
		 				    
#endif
