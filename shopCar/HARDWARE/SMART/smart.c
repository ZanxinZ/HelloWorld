#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "oled.h"
#include "math.h"
#include "pid.h"
#include "control.h"
#include "smart.h"


int location[12]={13,13,13,13,13,13,13,13,13,13,13,13};//λ������
int hope[4][3]={{0,1,2},{3,4,5},{6,7,8},{9,10,11}};//�������鰴�ջ���˳���Ų�
extern u8 finishflag;
extern u16 mode;

void take_photo_mechanical_grip(void)//��е���������Ʋ������ʼ�����ò�Ȼ����bug
{
	int flag=0;//״̬��־
	for(;;)
	{
		  if(flag==0)//��������
				{
				  USART_SendData(USART2,30);//�����ź�      
		      while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!= SET);//�ȴ��źŷ������ 
				}
				if((finishflag<99)&&(finishflag>0))//��е�ۿ�ʼ�����ź�
				{
					flag=1;//�رշ���
				}
				if(finishflag==30)//������ɱ�־99�͸�λ��ɱ�־1
				{
					finishflag=0;//��־λ���
					flag=0;
					break;
				}
	}
}
void init_mechanical_grip()///��е�ֳ�ʼ������
{
	int flag=0;//״̬��־
	for(;;)
	{
		  if(flag==0)//��������
				{
				  USART_SendData(USART2,1);//�����ź�      
		      while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!= SET);//�ȴ��źŷ������ 
				}
				if(finishflag==10)//��е�ۿ�ʼ�����ź�
				{
					flag=1;//�رշ���
				}
				if(finishflag==1)//������ɱ�־99�͸�λ��ɱ�־1
				{
					finishflag=0;//��־λ���
					flag=0;
					break;
				}
	}
}
void mechanical_grip(int mode)//�������ͨѶ����(ץȡ)
{
	int flag=0;//״̬��־
	for(;;)
	{
		  if(flag==0)//��������
				{
				  USART_SendData(USART2,mode+2);//�����ź�      
		      while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!= SET);//�ȴ��źŷ������ 
				}
				if((finishflag<99)&&(finishflag>0))//��е�ۿ�ʼ�����ź�
				{
					flag=1;//�رշ���
				}
				if(finishflag==99)//������ɱ�־99�͸�λ��ɱ�־1
				{
					finishflag=0;//��־λ���
					flag=0;
					break;
				}
	}
}
//void put_thing(int goods)
//{
//	int first,second,thrid;
//	int flag=0;
//	switch(goods)
//	{
//		case 1:first=22;second=23;thrid=24;break;
//		case 2:first=17;second=18;thrid=19;break;
//		case 3:first=17;second=18;thrid=19;break;
//		case 4:first=12;second=20;thrid=19;break;
//	}
//	delay_ms(100);
//	mechanical_grip(first);
//	mode=26;
//	for(;;)
//	{
//		if(REROAD1==1)
//		{
//			flag=1;
//			delay_ms(50);
//		}
//		if((REROAD1==0)&&(flag==1))
//		{
//			flag=0;
//			mode=1;
//			delay_ms(300);
//			break;
//		}
//	}
//	mechanical_grip(second);
//	mode=26;
//	for(;;)
//	{
//		if(REROAD1==1)
//		{
//			flag=1;
//			delay_ms(50);
//		}
//		if((REROAD1==0)&&(flag==1))
//		{
//			flag=0;
//			mode=1;
//			delay_ms(300);
//			break;
//		}
//	}
//	mechanical_grip(thrid);
//	count_line(4,0,1);
//}
void put_thing(int goods)//���ﺯ��goods������ܺ���
{
	int first,second,thrid;
	int flag=0,top=0,behind=0,line=0,move_timer=0,putflag=0;
	for(;;)//ä�ߺ��ʹ��Ҷ���������
	{
		delay_ms(100);
		mode=26;
		for(;;)
		{
			if(REROAD1==0)
			{
				mode=1;//ͣ��
				break;
			}
		}
		delay_ms(100);//��ʱ����
		mode=26;//ä�ߺ��
		for(;;)
		{
			if(TOP==0)//�������ϲ���û����Ʒ
			{
				top=1;
			}
			if(THING==0)//�������²���û�л���
			{
				behind=1;
			}
			if(RROAD3==1)//��Ҷ��ȼ�⵽��ɫ
			{
				flag=1;
				delay_ms(50);
			}
			if((RROAD3==0)&&(flag==1))//��Ҷȼ�⵽����
			{
				mode=1;
				delay_ms(200);
				for(;(RROAD3!=0);)//ͣ��У���������ߴ��������
		    {
			    mode=25;
		    }
		    for(;(LROAD7!=0);)
		    {
			    mode=24;
		    }
				flag=0;
				mode=1;//ͣ������ʱ����
				delay_ms(300);
				break;
			}
		}
		move_timer++;//�ƶ������Լ�
		if(top==0)//����ϲ�û�л���ִ�����ܷ���
		{
			smart_put_thing(0);
			putflag++;//���ô�������
			if(putflag==3)//�����ô����ﵽ������ѭ����ɷ���
		  {
			  break;
		  }
		}
		else
		{
			top=0;//����л����־����
		}
		if(behind==0)
		{
			smart_put_thing(1);
			putflag++;
			if(putflag==3)
		  {
			  break;
		  }
		}
		else
		{
			behind=0;
		}
	}
	count_line(move_timer+1,0,1);//������ɸ����ƶ����������뿪����
}
void smart_put_thing(int view_flag)//�����ܡ����ﺯ���
{
	static int put_timer=0;//������¼���������ö��ٴ�ȫ���ܹ�12��
	int loaction=0;
	if(view_flag==0)//�ж����ϲ㻹���²�
	{
		switch(put_timer)//ѡȡҪ���͵�����
		{
			case 0:loaction=24;break;//��ľ��26
			case 1:loaction=23;break;//��ľ��25
			case 2:loaction=22;break;//��ľ��24
			case 3:loaction=19;break;//��ͨ��21
			case 4:loaction=18;break;//��ͨ��20
			case 5:loaction=17;break;//��ͨ��19
			case 6:loaction=19;break;
			case 7:loaction=18;break;
			case 8:loaction=17;break;
			case 9:loaction=19;break;
			case 10:loaction=20;break;//����22
			case 11:loaction=12;break;//ħ����14
		}
	}
	else
	{
		switch(put_timer)
		{
			case 0:loaction=27;break;//��ľ��29
			case 1:loaction=26;break;//��ľ��28
			case 2:loaction=25;break;//��ľ��27
			case 3:loaction=16;break;//��ͨ��18
			case 4:loaction=15;break;//��ͨ��17
			case 5:loaction=14;break;//��ͨ��16
			case 6:loaction=16;break;
			case 7:loaction=15;break;
			case 8:loaction=14;break;
			case 9:loaction=16;break;
			case 10:loaction=21;break;//����23
			case 11:loaction=13;break;//ħ����15
		}
	}
	mechanical_grip(loaction);//��еץ����
	put_timer++;//�������ô�������
}
void thing_loction(int point1,int point2,int point3)//�ֿ�һ��ץ�ﺯ��
{
	int flag=0;
	if((point1==0)||(point1==3)||(point1==6)||(point1==9))//��һλ��ץȡ��
	{
		mode=31;//ä��Ѱ��
		for(;;)
		{
			if(THING==1)//û�м�⵽��Ʒ
			{
				flag=1;
			}
			if((THING==0)&&(flag==1))//��⵽��Ʒ
			{
				mode=1;//ͣ��
				break;
			}
		}
		mode=33;
		delay_ms(70);
		mode=1;
		mechanical_grip(location[point1]);//ִ����Ӧ����
	}
	if((point2==1)||(point2==4)||(point2==7)||(point2==10))//�ڶ�λ��ץȡ��
	{
		count_line(1,0,0);//����һ��
		mode=31;//ä�߼��
		for(;;)
		{
			if(THING==0)
			{
				 mode=1;
				 break;
			}
		}
		mode=33;
		delay_ms(70);
		mode=1;
		mechanical_grip(location[point2]);//ִ����Ӧץȡ��
	}
	else if(point2==13)//��Ϊ�ձ�־��ֱ��һ��
	{
		count_line(1,0,0);
	}
	if((point3==2)||(point3==5)||(point3==8)||(point3==11))//����λ��ץȡ��
	{
		mode=31;//ä��
		for(;;)
		{
			if(REROAD8==0)//��Ҷȼ�⵽����
			{
				 mode=1;
				 break;
			}
		}
		mode=31;//ä��
		for(;;)
		{
			if(THING==0)//��⵽��Ʒ
			{
				 mode=1;//ͣ��
				 break;
			}
		}
		mode=33;
		delay_ms(70);
		mode=1;
		mechanical_grip(location[point3]);//ִ����Ӧץȡ
		count_line(1,0,0);//ä��һ��
	}
	else if(point3==13)//��Ϊ�ձ�־��ֱ��һ��
	{
		count_line(1,0,0);
	}
	
}
int fill[3]={13,13,13};//���յ���λ�ñ�ʶ��13�����
void change_wall(void)//����ǽ��ת������
{
	mode=4;//��ʱäת
	delay_ms(1200);
	mode=1;
	delay_ms(300);
	mode=31;
	for(;;)//ֱ��ֱ����⵽�ֿ�ǽ��
	{
		if(THING==0)
		{
			mode=1;
			break;
		}
	}
	delay_ms(300);
}
void clearfill(void)//��ʼ�����ֵ�������
{
	int i;
	for(i=0;i<3;i++)
	{
		fill[i]=13;
	}
}
void warehouse_finding(int start_location,int corner)//�������corner���������ţ�start_location����������
{
  int i,j,flag=0,hopeflag=0;
	clearfill();
	if(corner==0)
	{
		for(i=0;i<3;i++)//ͨ������������ͼ��ʶ�𷵻صİ���������Ϣ��λ������Ƚ��жϸû������Ƿ���Ҫץȡ
		{
			for(j=0;j<3;j++)
			{
				 if(hope[start_location][j]==location[i])
				 {
						fill[flag]=i;
						hopeflag=1;
				 }
			}
			flag++;
		 }
		 if(hopeflag!=0)//�����Ҫץȡִ��ץȡ�߼�
		 {
			 thing_loction(fill[0],fill[1],fill[2]);
			 clearfill();
			 hopeflag=0;
			 flag=0;
		 }
		 else//�������Ҫץȡ���Թ�����
		 {
			 count_line(2,0,0);
			 flag=0;
		 }
	 }
	 else if(corner==1)
	 {
		 for(i=3;i<6;i++)
		 {
			 for(j=0;j<3;j++)
			 {
				 if(hope[start_location][j]==location[i])
				 {
						fill[flag]=i;
					  hopeflag=1;
				 }
			 }
			 flag++;
		 }
		 if(hopeflag!=0)
		 {
			 thing_loction(fill[0],fill[1],fill[2]);
			 clearfill();
			 hopeflag=0;
			 flag=0;
		 }
		 else
		 {
			 count_line(2,0,0);
			 flag=0;
		 }
	 }
	 else if(corner==2)
	 {
		 for(i=6;i<9;i++)
		 {
			 for(j=0;j<3;j++)
			 {
				 if(hope[start_location][j]==location[i])
				 {
						fill[flag]=i;
					  hopeflag=1;
				 }
			 }
			 flag++;
		 }
		 if(hopeflag!=0)
		 {
			 thing_loction(fill[0],fill[1],fill[2]);
			 clearfill();
			 hopeflag=0;
			 flag=0;
		 }
		 else
		 {
			 count_line(2,0,0);
			 flag=0;
		 }
	 }
	 else if(corner==3)
	 {
		 for(i=9;i<12;i++)
		 {
			 for(j=0;j<3;j++)
			 {
				 if(hope[start_location][j]==location[i])
				 {
						fill[flag]=i;
					  hopeflag=1;
				 }
			 }
			 flag++;
		 }
		 if(hopeflag!=0)
		 {
			 thing_loction(fill[0],fill[1],fill[2]);
			 clearfill();
			 hopeflag=0;
			 flag=0;
		 }
		 else
		 {
			 count_line(2,0,0);
			 flag=0;
		 }
	 }
}

