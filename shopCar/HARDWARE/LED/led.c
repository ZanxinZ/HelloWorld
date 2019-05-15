#include "led.h"

void LED_Init(void)
{
 
	 GPIO_InitTypeDef  GPIO_InitStructure;
		
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOG, ENABLE);	 //使能PB,PE端口时钟
		
   
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;//激光 		 
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		 
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	 GPIO_Init(GPIOC, &GPIO_InitStructure);	
 
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//拍照信号 
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
	 	
	 
	
	 GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//左右灰度
	 RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO,ENABLE);
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;	    		 
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		 
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	 GPIO_Init(GPIOB, &GPIO_InitStructure);		

	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);//前排灰度
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;	    		 
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		 
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	 GPIO_Init(GPIOD, &GPIO_InitStructure);	
	 GPIO_ResetBits(GPIOD,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8);
		
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);//后排灰度
	 GPIO_InitStructure.GPIO_Pin =GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;				
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		 
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	 GPIO_Init(GPIOF, &GPIO_InitStructure);					 
	 GPIO_ResetBits(GPIOF,GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10);
	 
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);//电机驱动板
	 GPIO_InitStructure.GPIO_Pin =GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;				
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	 GPIO_Init(GPIOG, &GPIO_InitStructure);					 
	 GPIO_ResetBits(GPIOG,GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6);
	 
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//拨片开关
	 GPIO_InitStructure.GPIO_Pin =GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;				
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		 
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	 GPIO_Init(GPIOA, &GPIO_InitStructure);					 
	 GPIO_SetBits(GPIOA,GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);
}
 
