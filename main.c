#include "stm32f10x.h"
#include "usart.h"
#include "timer.h"
#include "string.h"
#include "led.h"
#include "main.h"
#include "lora.h"
#include "delay.h"


/*************  ���ر�������	**************/


//char Uart2_Buf[Buf2_Max];//����2���ݻ�����
u8 First_Int = 0;


#define Buf5_Max 				240 					  //����5���泤��
#define Buf1_Max 				240					  //����1���泤��
#define REX_Data_Max		240						//��Ч���ݳ���
#define Send_Data_Max		1024						//��������ֽ���
#define buff_Max		1024						//ת�崦���������󳤶�



u16 USART_RX_STA;
u8 Uart5_Buf[Buf5_Max]={0};//����5���ݻ�����



/*******************************************************
*����ָʾ����ض���
*
*
***********************************/

volatile unsigned char ONOFF=0;
volatile uint16_t LedTimer=0;



/*******************************************************
*LORA 433ͨ����ض���
*
*
***********************************/
volatile uint8_t Lora_send_BUF[4];
uint8_t UART5RxBuf[UART5_RX_BUFFER_LEN]={0};//UART5���ջ�����
uint8_t UART5Buf[UART5_RX_BUFFER_LEN]={0};//UART5��������
uint8_t Data_Packet1[22]={0};//
uint8_t Data_Packet2[22]={0};//
uint8_t UART5RxRec;  //UART5�����ֽ���
uint8_t UART5RxChar;//UART5�����ֽ�
volatile uint8_t Lora_OK=0;//������ɱ�־
volatile uint16_t LoraTimer;    //��ȡ���ʱ��
volatile u8 LoraOverTime=10;//��������ȡ��ʱ����
volatile u8 Lora_state=1;  
volatile u8 LoraErrorTimes=0;

volatile uint8_t ReceiveBuf[6]={0};
volatile u16 RxTimeOut;


/*******************************************************************************
* ������ : main 
* ����   : ������
* ����   : 
* ���   : 
* ����   : 
* ע��   : 
*******************************************************************************/
int main(void)
{
		

		RxTimeOut=0;
		delay_init();
		LED_Init();
	  LORA_Init();
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2
		UART5_Init_Config(9600);	      //433����ͨ��ģ��
		Timer2_Init_Config();    
		Timer3_Init_Config();

		while(1)
		{

				LORA_TASK();
					
				LED_TASK();                    //��������ָʾ��
			
		}	
}


	
