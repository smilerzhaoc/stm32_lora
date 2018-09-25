#include "stm32f10x.h"
#include "usart.h"
#include "timer.h"
#include "string.h"
#include "led.h"
#include "main.h"
#include "lora.h"
#include "delay.h"


/*************  本地变量声明	**************/


//char Uart2_Buf[Buf2_Max];//串口2数据缓存区
u8 First_Int = 0;


#define Buf5_Max 				240 					  //串口5缓存长度
#define Buf1_Max 				240					  //串口1缓存长度
#define REX_Data_Max		240						//有效数据长度
#define Send_Data_Max		1024						//发送最大字节数
#define buff_Max		1024						//转义处理后数组最大长度



u16 USART_RX_STA;
u8 Uart5_Buf[Buf5_Max]={0};//串口5数据缓存区



/*******************************************************
*运行指示灯相关定义
*
*
***********************************/

volatile unsigned char ONOFF=0;
volatile uint16_t LedTimer=0;



/*******************************************************
*LORA 433通信相关定义
*
*
***********************************/
volatile uint8_t Lora_send_BUF[4];
uint8_t UART5RxBuf[UART5_RX_BUFFER_LEN]={0};//UART5接收缓冲区
uint8_t UART5Buf[UART5_RX_BUFFER_LEN]={0};//UART5处理缓冲区
uint8_t Data_Packet1[22]={0};//
uint8_t Data_Packet2[22]={0};//
uint8_t UART5RxRec;  //UART5接收字节数
uint8_t UART5RxChar;//UART5接收字节
volatile uint8_t Lora_OK=0;//接收完成标志
volatile uint16_t LoraTimer;    //读取间隔时间
volatile u8 LoraOverTime=10;//传感器读取超时控制
volatile u8 Lora_state=1;  
volatile u8 LoraErrorTimes=0;

volatile uint8_t ReceiveBuf[6]={0};
volatile u16 RxTimeOut;


/*******************************************************************************
* 函数名 : main 
* 描述   : 主函数
* 输入   : 
* 输出   : 
* 返回   : 
* 注意   : 
*******************************************************************************/
int main(void)
{
		

		RxTimeOut=0;
		delay_init();
		LED_Init();
	  LORA_Init();
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
		UART5_Init_Config(9600);	      //433无线通信模块
		Timer2_Init_Config();    
		Timer3_Init_Config();

		while(1)
		{

				LORA_TASK();
					
				LED_TASK();                    //程序运行指示灯
			
		}	
}


	
