#include "led.h"

void LED_Init(void)
{
 
	 GPIO_InitTypeDef  GPIO_InitStructure;
		
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOG, ENABLE);	 //ʹ��PB,PE�˿�ʱ��
		
   
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;//���� 		 
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		 
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	 GPIO_Init(GPIOC, &GPIO_InitStructure);	
 
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//�����ź� 
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	 GPIO_Init(GPIOC, &GPIO_InitStructure);	
   GPIO_ResetBits(GPIOB,GPIO_Pin_11);	

	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15|GPIO_Pin_14;	    		 
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	 GPIO_Init(GPIOB, &GPIO_InitStructure);		
   GPIO_ResetBits(GPIOB,GPIO_Pin_15|GPIO_Pin_14);
	 
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;	    		 
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	 GPIO_Init(GPIOE, &GPIO_InitStructure);		
	 
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;	    		 
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	 GPIO_Init(GPIOG, &GPIO_InitStructure);		
   GPIO_SetBits(GPIOG,GPIO_Pin_15);
	 	
	 
	
	 GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//���һҶ�
	 RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO,ENABLE);
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;	    		 
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		 
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	 GPIO_Init(GPIOB, &GPIO_InitStructure);		

	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);//ǰ�ŻҶ�
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;	    		 
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		 
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	 GPIO_Init(GPIOD, &GPIO_InitStructure);	
	 GPIO_ResetBits(GPIOD,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8);
		
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);//���ŻҶ�
	 GPIO_InitStructure.GPIO_Pin =GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;				
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		 
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	 GPIO_Init(GPIOF, &GPIO_InitStructure);					 
	 GPIO_ResetBits(GPIOF,GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10);
	 
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);//���������
	 GPIO_InitStructure.GPIO_Pin =GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;				
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	 GPIO_Init(GPIOG, &GPIO_InitStructure);					 
	 GPIO_ResetBits(GPIOG,GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6);
	 
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//��Ƭ����
	 GPIO_InitStructure.GPIO_Pin =GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;				
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		 
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	 GPIO_Init(GPIOA, &GPIO_InitStructure);					 
	 GPIO_SetBits(GPIOA,GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);
}
 
