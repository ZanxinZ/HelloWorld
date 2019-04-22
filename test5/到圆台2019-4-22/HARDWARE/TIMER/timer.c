#include "timer.h"
#include "led.h"
#include "oled.h"
#include "delay.h"
#include "pid.h"
#include "MOTO.h"
extern Pid pid;
extern PidParam pidSetParam;
int clr_pid_voltage=0;//���������


LightState lightState;//�Ҷȵ�״̬
LightError lightError;//ͨ���Ҷȣ��趨��ƫ��
CarState carState;//����״̬��־
extern int Roll,Pitch,Yaw,data,Angle[10],hd_front[];
//��ʱ����ʼ��////////////////////
//��ʱ��2
void TIM2_Int_Initl(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  ///ʹ��TIM3ʱ��
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);//��ʼ��TIM3
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE); //����ʱ��3�����ж�
	TIM_Cmd(TIM2,ENABLE); //ʹ�ܶ�ʱ��3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn; //��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x02; //�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}
//��ʱ��5
void TIM5_Int_Initl(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  ///ʹ��TIM3ʱ��
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStructure);//��ʼ��TIM3
	
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE); //����ʱ��3�����ж�
	TIM_Cmd(TIM5,ENABLE); //ʹ�ܶ�ʱ��5
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM5_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3; //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}
void TIM6_Int_Initl(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);  ///ʹ��TIM3ʱ��
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM6,&TIM_TimeBaseInitStructure);//��ʼ��TIM3
	
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE); //����ʱ��3�����ж�
	
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM6_DAC_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=4;//�����ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	TIM_Cmd(TIM6,ENABLE); //ʹ�ܶ�ʱ��5
	
}
////////////////////////////////////



//��ʱ���жϷ�����/////////////

void TIM2_IRQHandler(void)//��ʱ��2��ɨ�Ҷ�,������
{
	
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET) //����ж�
  {
		
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);  //����жϱ�־
			//�ɼ��Ҷ���Ϣ����������
		lightState.light[0]=HD1;
		lightState.light[1]=HD2;
		lightState.light[2]=HD3;
		lightState.light[3]=HD4;
		lightState.light[4]=HD5;
		lightState.light[5]=HD6;
		lightState.light[6]=HD7;
		lightState.light[7]=HD8;
		
		getError();	
		lightState.num=0;
		getLightNum();
		
				
		//if((lightState.light[3]==0||lightState.light[4]==0)&&lightState.light[7]==1)   flagr=1;
		
		if((lightState.light[3]==0||lightState.light[4]==0)&&lightState.light[0]==1)
			{lightState.isCrossing=0;}//����·��
		if((lightState.light[1]==0&&lightState.light[3]==0&&lightState.light[6]==0)||
			(lightState.light[1]==0&&lightState.light[4]==0&&lightState.light[6]==0))
			{lightState.isCrossing=1;}//��·��
		if(lightState.num>2){lightError.error=0;}	
		}			
}			


	       
					 
	void TIM5_IRQHandler(void)//��ʱ��5,pid ��ִ�У�ȡ���ݣ����㣬ִ��
{
	if(TIM_GetITStatus(TIM5,TIM_IT_Update)==SET) //����ж�
  {
		int leftResult,rightResult;//���
		TIM_ClearITPendingBit(TIM5,TIM_IT_Update);  //����жϱ�־
		
		clr_pid_voltage++;
		if(clr_pid_voltage>=200){pid.voltage=0;clr_pid_voltage=0;}//���������
		
		PID_realize(lightError.error);//����ƫ��
		TIM_SetCompare4(TIM3, pid.setSpeedLeft- pid.ActualSpeed);	 
		TIM_SetCompare3(TIM3, pid.setSpeedRight + pid.ActualSpeed);
		//leftResult=pid.setSpeedLeft-pid.ActualSpeed;
		//rightResult=pid.setSpeedRight + pid.ActualSpeed;
		//setSpeed(leftResult,rightResult);
		
		
		
		
		
	}		
}		

void TIM6_DAC_IRQHandler(void)//��ʱ��6��ʱ
{
	if(TIM_GetITStatus(TIM6,TIM_IT_Update)==SET) //����ж�
  {
		TIM_SetCompare2(TIM4,18);
		TIM_ClearITPendingBit(TIM6,TIM_IT_Update);
	}	
		else{
		TIM_SetCompare2(TIM4,28);
		}
}		
//////////////////////////////////
//��ʼ���Ҷ�ģ��

void init_light_block(){
	int i;
	for(i=0;i<8;i++){
		lightState.light[i]=1;
	}
	lightState.canLeftTurn=0;
	lightState.canRightTurn=0;
	lightState.num=0;
	lightState.isCrossing=0;
	lightState.isCrossing=0;
	
	lightError.error=0;
	lightError.resultSpeed=0;
	
	carState.isGoline=0;
	carState.isHoldJG=0;
	carState.isDoOption=1;
}


////////////////////////	
//ƫ����Դ
void getError(void)
		{
			int light=-1;
			int L0,L1,L2,L3,L4,L5,L6,L7;
			light=lightState.light[0]*10000000+
					lightState.light[1]*1000000+
					lightState.light[2]*100000+
					lightState.light[3]*10000+
					lightState.light[4]*1000+
					lightState.light[5]*100+
					lightState.light[6]*10+
					lightState.light[7];
		
				L0=HD1;
				L1=HD2;
				L2=HD3;
				L3=HD4;
				L4=HD5;
				L5=HD6;
				L6=HD7;
				L7=HD8;
			/*//�˲�
			if(lightState.num>2){lightError.error=0;}//��������������ƫ��Ϊ0
			//�����ڵ�����������ƫ������
			else if((L0==0&&(L4==0||L5==0||L6==0||L7==0)))
			{lightError.error=0;}
			else if((L1==0&&(L5==0||L6==0||L7==0)))
			{lightError.error=0;}
			else if((L2==0&&(L6==0||L7==0)))
			{lightError.error=0;}
			else if((L3==0&&(L7==0)))
			{lightError.error=0;}
			*/
		//�Ҷȵ�״̬������ƫ��
		 switch(light){
			//����ж�·��ʱ����Ҫ��error��0
			//�ȶ�ƣ����ٵ�
			/////////////////
			//����
			case 11100111://3,4
				lightError.error=0;pidSetParam.Lkd=0;pidSetParam.Lkp=0;	
				break;
			case 11001111://2,3
				lightError.error=0.08;pidSetParam.Lkp=15;pidSetParam.Lkd=5;		
				break;
			case 11110011://4,5
				lightError.error=-0.08;pidSetParam.Lkp=15;	pidSetParam.Lkd=5;
				break;
			case 111111://0,1
				lightError.error=1;pidSetParam.Lkp=0;	pidSetParam.Lkd=0;
				break;
			case 11111100://6,7
				lightError.error=-1;pidSetParam.Lkp=0;	pidSetParam.Lkd=0;
				break;
			case 10011111://1,2
				lightError.error=0.5;pidSetParam.Lkp=0;	pidSetParam.Lkd=0;
				break;
			case 11111001://5,6
				lightError.error=-0.5;pidSetParam.Lkp=0;pidSetParam.Lkd=0;
				break;
			////////////////
			
			/////////////////
			//����
			case 01111111://0
				lightError.error=2;
				break;
			case 10111111://1
				lightError.error=1.5;pidSetParam.Lkp=0;pidSetParam.Lkd=0;
				break;
			case 11011111://2
				lightError.error=1.2;pidSetParam.Lkp=0;pidSetParam.Lkd=0;
				break;
			case 11101111://3
				lightError.error=0.1;
				break;
			case 11110111://4
				lightError.error=-0.1;
				break;
			case 11111011://5
				lightError.error=-1.2;pidSetParam.Lkp=0;pidSetParam.Lkd=0;
				break;
			case 11111101://6
				lightError.error=-1.5;pidSetParam.Lkp=0;pidSetParam.Lkd=0;
				break;
			case 11111110://7
				lightError.error=-2;
				break;
			/////////////////
			default:
				lightError.error=0;
				break;
		}
		
		//if(((L0==0||L1==0)&&L3==0)||((L0==0||L1==0)&&L4==0)) 
		if(L0==0)
			{ 
			lightState.canLeftTurn=1; //������ת
			pidSetParam.Lkd=0;	
			pidSetParam.Lkp=25;		
			
			}
			else if(((L7==0||L6==0)&&L3==0)||((L7==0||L1==6)&&L4==0))
			//else if(L7==0)
			{ 
			lightState.canRightTurn=1;//������ת
			pidSetParam.Lkd=0;	
			pidSetParam.Lkp=25;	
			
			}	
			else {
			lightState.canLeftTurn=0;
			lightState.canRightTurn=0;
			pidSetParam.Lkd=0;	
			pidSetParam.Lkp=0;		
			}
			if(L0==0&&L1==0&&L2==0||L5==0&&L6==0&&L7==0){lightError.error=0;}
			
		}
	
void getLightNum(void)//�õ���⵽���߻Ҷȵ�����
{
	int h;
	for(h=0;h<8;h++)
	{
		if(lightState.light[h]==0)
		{
			lightState.num++;
		}
	
	}
	}