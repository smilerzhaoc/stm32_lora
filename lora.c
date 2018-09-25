#include "lora.h"
#include "delay.h"
#include "main.h"
#include "usart.h"

#define LoraStartByte 17

extern volatile uint8_t Lora_send_BUF[4];
extern uint8_t UART5RxBuf[UART5_RX_BUFFER_LEN];//UART5���ջ�����
extern uint8_t UART5Buf[UART5_RX_BUFFER_LEN];//UART5��������
extern uint8_t Data_Packet1[22];//
extern uint8_t Data_Packet2[22];//
extern uint8_t UART5RxRec;  //UART5�����ֽ���
extern uint8_t UART5RxChar;//UART5�����ֽ�
extern volatile uint8_t Lora_OK;//������ɱ�־
extern volatile uint16_t LoraTimer;    //��ȡ���ʱ��, Ŀǰ��200ms��ȡһ��
extern volatile u8 LoraOverTime;//��������ȡ��ʱ����

extern volatile u16 LoraWaittime;			//�ȴ��������ظ�ʱ��
extern volatile u16 Lorasendtime;

extern volatile uint8_t ReceiveBuf[6];
extern uint8_t Data_Send_Packet[PacketLen];


void LORA_Init(void)
{
 
		 GPIO_InitTypeDef  GPIO_InitStructure;
			
	   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE );  //ʹ��PB�˿�ʱ��
	
			//M1
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;  //MD1  PB8
			GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
			GPIO_Init(GPIOB, &GPIO_InitStructure);
			
			//M0
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;  //MD0  PB9
			GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
			GPIO_Init(GPIOB, &GPIO_InitStructure);
			
			//MD1=0,MD0=0;
			GPIO_ResetBits(GPIOB, GPIO_Pin_11);
			GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	
}

void LORA_TASK()
{
		u16 ThisCheckSum;
		uint16_t cChecksum;
		u8 Lora_send_BUF[4]={0x68,0x03,0x55,0x3f};
		u8 i;
		//���Ͷ�ȡ���������������
		if(LoraTimer==1000)	//��ʱ�ѵ�  ���Ͷ�ȡָ��
		{
				UART5RxRec = 0;
				LoraTimer=0;
				//��������
				UART5_LenSendString(Lora_send_BUF,4);//
		}	
		
		if(Lora_OK == 1)//���յ�
		{				
				switch(UART5RxBuf[1])
				{
					 case 0x01:
					 {
							Data_Packet1[LoraStartByte+0]=UART5RxBuf[0];
							Data_Packet1[LoraStartByte+1]=UART5RxBuf[1];
							Data_Packet1[LoraStartByte+2]=UART5RxBuf[2];
							Data_Packet1[LoraStartByte+3]=UART5RxBuf[3];
							
							break;
					 }
					 case 0x02:
					 {
							Data_Packet2[LoraStartByte+0]=UART5RxBuf[0];
							Data_Packet2[LoraStartByte+1]=UART5RxBuf[1];
							Data_Packet2[LoraStartByte+2]=UART5RxBuf[2];
							Data_Packet2[LoraStartByte+3]=UART5RxBuf[3];
							
							break;
					 }
					default:break;
				}
		
				Lora_OK=0;			
		}
		
}