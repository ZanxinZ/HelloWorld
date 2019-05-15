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


int location[12]={13,13,13,13,13,13,13,13,13,13,13,13};//Î»ÖÃÊı×é
int hope[4][3]={{0,1,2},{3,4,5},{6,7,8},{9,10,11}};//ÆÚÍûÊı×é°´ÕÕ»õ¼ÜË³ĞòÅÅ²¼
extern u8 finishflag;
extern u16 mode;

void take_photo_mechanical_grip(void)//»úĞµÊÖÅÄÕÕ×ËÊÆ²»ÄÜÓë³õÊ¼»¯Á¬ÓÃ²»È»»áÓĞbug
{
	int flag=0;//×´Ì¬±êÖ¾
	for(;;)
	{
		  if(flag==0)//·¢ËÍÔÊĞí
				{
				  USART_SendData(USART2,30);//·¢ËÍĞÅºÅ      
		      while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!= SET);//µÈ´ıĞÅºÅ·¢ËÍÍê±Ï 
				}
				if((finishflag<99)&&(finishflag>0))//»úĞµ±Û¿ªÊ¼¶¯×÷ĞÅºÅ
				{
					flag=1;//¹Ø±Õ·¢ËÍ
				}
				if(finishflag==30)//¶¯×öÍê³É±êÖ¾99ºÍ¸´Î»Íê³É±êÖ¾1
				{
					finishflag=0;//±êÖ¾Î»Çå³ı
					flag=0;
					break;
				}
	}
}
void init_mechanical_grip()///»úĞµÊÖ³õÊ¼»¯º¯Êı
{
	int flag=0;//×´Ì¬±êÖ¾
	for(;;)
	{
		  if(flag==0)//·¢ËÍÔÊĞí
				{
				  USART_SendData(USART2,1);//·¢ËÍĞÅºÅ      
		      while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!= SET);//µÈ´ıĞÅºÅ·¢ËÍÍê±Ï 
				}
				if(finishflag==10)//»úĞµ±Û¿ªÊ¼¶¯×÷ĞÅºÅ
				{
					flag=1;//¹Ø±Õ·¢ËÍ
				}
				if(finishflag==1)//¶¯×öÍê³É±êÖ¾99ºÍ¸´Î»Íê³É±êÖ¾1
				{
					finishflag=0;//±êÖ¾Î»Çå³ı
					flag=0;
					break;
				}
	}
}
void mechanical_grip(int mode)//¶æ»úÇı¶¯Í¨Ñ¶º¯Êı(×¥È¡)
{
	int flag=0;//×´Ì¬±êÖ¾
	for(;;)
	{
		  if(flag==0)//·¢ËÍÔÊĞí
				{
				  USART_SendData(USART2,mode+2);//·¢ËÍĞÅºÅ      
		      while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!= SET);//µÈ´ıĞÅºÅ·¢ËÍÍê±Ï 
				}
				if((finishflag<99)&&(finishflag>0))//»úĞµ±Û¿ªÊ¼¶¯×÷ĞÅºÅ
				{
					flag=1;//¹Ø±Õ·¢ËÍ
				}
				if(finishflag==99)//¶¯×öÍê³É±êÖ¾99ºÍ¸´Î»Íê³É±êÖ¾1
				{
					finishflag=0;//±êÖ¾Î»Çå³ı
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
void put_thing(int goods)//·ÅÎïº¯Êıgoods´ú±í»õ¼ÜºÅÂë
{
	int first,second,thrid;
	int flag=0,top=0,behind=0,line=0,move_timer=0,putflag=0;
	for(;;)//Ã¤×ßºó³åÊ¹ºó»Ò¶ÈÅöµ½°×Ïß
	{
		delay_ms(100);
		mode=26;
		for(;;)
		{
			if(REROAD1==0)
			{
				mode=1;//Í£³µ
				break;
			}
		}
		delay_ms(100);//ÑÓÊ±»º³å
		mode=26;//Ã¤×ßºó³å
		for(;;)
		{
			if(TOP==0)//¼ì²â»õ¼ÜÉÏ²ãÓĞÃ»ÓĞÎïÆ·
			{
				top=1;
			}
			if(THING==0)//¼ì²â»õ¼ÜÏÂ²ãÓĞÃ»ÓĞ»õÎï
			{
				behind=1;
			}
			if(RROAD3==1)//²à»Ò¶ÈÏÈ¼ì²âµ½ºÚÉ«
			{
				flag=1;
				delay_ms(50);
			}
			if((RROAD3==0)&&(flag==1))//²â»Ò¶È¼ì²âµ½°×Ïß
			{
				mode=1;
				delay_ms(200);
				for(;(RROAD3!=0);)//Í£³µĞ£Õı¼õÉÙÊıÏß´íÎó¿ÉÄÜĞÔ
		    {
			    mode=25;
		    }
		    for(;(LROAD7!=0);)
		    {
			    mode=24;
		    }
				flag=0;
				mode=1;//Í£³µ²¢ÑÓÊ±»º³å
				delay_ms(300);
				break;
			}
		}
		move_timer++;//ÒÆ¶¯´ÎÊı×Ô¼Ó
		if(top==0)//Èç¹ûÉÏ²ãÃ»ÓĞ»õÎïÖ´ĞĞÖÇÄÜ·ÅÎï
		{
			smart_put_thing(0);
			putflag++;//·ÅÖÃ´ÎÊıÔö¼Ó
			if(putflag==3)//µ±·ÅÖÃ´ÎÊı´ïµ½ÈıÌø³öÑ­»·Íê³É·ÅÎï
		  {
			  break;
		  }
		}
		else
		{
			top=0;//Èç¹ûÓĞ»õÎï±êÖ¾ÇåÁã
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
	count_line(move_timer+1,0,1);//·ÅÎïÍê³É¸ù¾İÒÆ¶¯´ÎÊıÊıÏßÀë¿ª»õ¼Ü
}
void smart_put_thing(int view_flag)//¡°ÖÇÄÜ¡°·ÅÎïº¯Êı¡
{
	static int put_timer=0;//ÓÃÀ´¼ÇÂ¼º¯Êı±»µ÷ÓÃ¶àÉÙ´ÎÈ«³Ì×Ü¹²12´Î
	int loaction=0;
	if(view_flag==0)//ÅĞ¶ÏÊÇÉÏ²ã»¹ÊÇÏÂ²ã
	{
		switch(put_timer)//Ñ¡È¡Òª·¢ËÍµÄÊı×Ö
		{
			case 0:loaction=24;break;//×óÄ¾ÉÏ26
			case 1:loaction=23;break;//ÖĞÄ¾ÉÏ25
			case 2:loaction=22;break;//ÓÒÄ¾ÉÏ24
			case 3:loaction=19;break;//×óÍ¨ÉÏ21
			case 4:loaction=18;break;//ÖĞÍ¨ÉÏ20
			case 5:loaction=17;break;//ÓÒÍ¨ÉÏ19
			case 6:loaction=19;break;
			case 7:loaction=18;break;
			case 8:loaction=17;break;
			case 9:loaction=19;break;
			case 10:loaction=20;break;//ÇòÉÏ22
			case 11:loaction=12;break;//Ä§·½ÉÏ14
		}
	}
	else
	{
		switch(put_timer)
		{
			case 0:loaction=27;break;//×óÄ¾ÏÂ29
			case 1:loaction=26;break;//ÖĞÄ¾ÏÂ28
			case 2:loaction=25;break;//ÓÒÄ¾ÏÂ27
			case 3:loaction=16;break;//×óÍ¨ÏÂ18
			case 4:loaction=15;break;//ÖĞÍ¨ÏÂ17
			case 5:loaction=14;break;//ÓÒÍ¨ÏÂ16
			case 6:loaction=16;break;
			case 7:loaction=15;break;
			case 8:loaction=14;break;
			case 9:loaction=16;break;
			case 10:loaction=21;break;//ÇòÏÂ23
			case 11:loaction=13;break;//Ä§·½ÏÂ15
		}
	}
	mechanical_grip(loaction);//»úĞµ×¥·ÅÎï
	put_timer++;//º¯Êıµ÷ÓÃ´ÎÊıÔö¼Ó
}
void thing_loction(int point1,int point2,int point3)//²Ö¿âÒ»Ãæ×¥Îïº¯Êı
{
	int flag=0;
	if((point1==0)||(point1==3)||(point1==6)||(point1==9))//µÚÒ»Î»ÖÃ×¥È¡Îï
	{
		mode=31;//Ã¤×ßÑ°Îï
		for(;;)
		{
			if(THING==1)//Ã»ÓĞ¼ì²âµ½ÎïÆ·
			{
				flag=1;
			}
			if((THING==0)&&(flag==1))//¼ì²âµ½ÎïÆ·
			{
				mode=1;//Í£³µ
				break;
			}
		}
		mode=33;
		delay_ms(70);
		mode=1;
		mechanical_grip(location[point1]);//Ö´ĞĞÏàÓ¦¶¯×÷
	}
	if((point2==1)||(point2==4)||(point2==7)||(point2==10))//µÚ¶şÎ»ÖÃ×¥È¡Îï
	{
		count_line(1,0,0);//ÊıÏßÒ»¸ñ
		mode=31;//Ã¤×ß¼ì²â
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
		mechanical_grip(location[point2]);//Ö´ĞĞÏàÓ¦×¥È¡Îï
	}
	else if(point2==13)//ÈôÎª¿Õ±êÖ¾ÔòÖ±×ßÒ»¸ñ
	{
		count_line(1,0,0);
	}
	if((point3==2)||(point3==5)||(point3==8)||(point3==11))//µÚÈıÎ»ÖÃ×¥È¡Îï
	{
		mode=31;//Ã¤×ß
		for(;;)
		{
			if(REROAD8==0)//ºó»Ò¶È¼ì²âµ½°×Ïß
			{
				 mode=1;
				 break;
			}
		}
		mode=31;//Ã¤×ß
		for(;;)
		{
			if(THING==0)//¼ì²âµ½ÎïÆ·
			{
				 mode=1;//Í£³µ
				 break;
			}
		}
		mode=33;
		delay_ms(70);
		mode=1;
		mechanical_grip(location[point3]);//Ö´ĞĞÏàÓ¦×¥È¡
		count_line(1,0,0);//Ã¤×ßÒ»¸ñ
	}
	else if(point3==13)//ÈôÎª¿Õ±êÖ¾ÔòÖ±×ßÒ»¸ñ
	{
		count_line(1,0,0);
	}
	
}
int fill[3]={13,13,13};//»õ²Õµ¥ÃæÎ»ÖÃ±êÊ¶£¬13´ú±í¿Õ
void change_wall(void)//»õ²ÕÇ½Ãæ×ª»»º¯Êı
{
	mode=4;//ÑÓÊ±Ã¤×ª
	delay_ms(1200);
	mode=1;
	delay_ms(300);
	mode=31;
	for(;;)//Ö±×ßÖ±µ½¼ì²âµ½²Ö¿âÇ½±Ú
	{
		if(THING==0)
		{
			mode=1;
			break;
		}
	}
	delay_ms(300);
}
void clearfill(void)//³õÊ¼»¯»õ²Öµ¥ÃæÊı×é
{
	int i;
	for(i=0;i<3;i++)
	{
		fill[i]=13;
	}
}
void warehouse_finding(int start_location,int corner)//»õ²ÖÕÒÎï£¬corner´ú±í»õ²ÖÃæºÅ£¬start_location´ú±í»õ¼ÜĞòºÅ
{
  int i,j,flag=0,hopeflag=0;
	clearfill();
	if(corner==0)
	{
		for(i=0;i<3;i++)//Í¨¹ıÆÚÍûÊı×éÓëÍ¼ÏñÊ¶±ğ·µ»ØµÄ°üº¬»õÎïĞÅÏ¢µÄÎ»ÖÃÊı×é±È½ÏÅĞ¶Ï¸Ã»õ²ÖÃæÊÇ·ñĞèÒª×¥È¡
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
		 if(hopeflag!=0)//Èç¹ûĞèÒª×¥È¡Ö´ĞĞ×¥È¡Âß¼­
		 {
			 thing_loction(fill[0],fill[1],fill[2]);
			 clearfill();
			 hopeflag=0;
			 flag=0;
		 }
		 else//Èç¹û²»ĞèÒª×¥È¡ÔòÂÔ¹ı¸ÃÃæ
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

