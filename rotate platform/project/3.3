#include <reg52.h>
#include "PWM.h"
#include "Uart.h"
sbit PWM=P2^0;
sbit Dir=P3^2;

u8  c_TH[19] = {251,253,254,254,255,255,255,255,255,255,255,255,255,255,255,254,254,253,251};
u8  c_TL[19] = {64438, 64987, 65170, 65261, 65316, 65353, 65379, 65398, 65414,65426,65414,65398,65379,65353,65316,65261,65170,64987,64438};
u8 C_H;
u8 C_L;

unsigned long int cnt_timer1;
unsigned long int PWM_Num;

unsigned int speeds[19] = {420,840,1260,1680,2100,2520,2940,3360,3780,4200,3780,3360,2940,2520,2100,1680,1260,840,420};
unsigned int period[19] = {0};
unsigned int periodD = 0;
//速度控制有关的参数
unsigned char stage = 0;

void PWM_Init()   //16Hz~1MHz
{
    TMOD|= 0x01;   //设置定时计数器0工作方式2为定时器 

	 
	TH0 = 253; 
	TL0 = 64768;
	PT0=1;        //设置为高优先级
	ET0= 1; 	 //开启定时器1中断
	EA = 1;

    PWM=0;
}

void Set_PWM_Num()
{
    PWM_Num = PWMNum;

	C_H = 253;
	C_L = 64768;
	/*
	  		 —— —— —— —— —— —— —— —— —— ——
	  	   /							   \
	  	  /								    \
	   	 /									 \
	  ——+—————————————————————————————————————+—————> periods
		0               					   16
	*/
	//time zero
	periodD	= PWM_Num/64*2;	
						  
	period[0] =  periodD*0.2;
	period[1] =  period[0] + periodD*0.4;
	period[2] =  period[1] + periodD*0.6;

	period[3] =  period[2] + periodD*0.8;	   
	period[4] =  period[3] + periodD;
   	period[5] =  period[4] + periodD*1.2;

	period[6] =  period[5] + periodD*1.4;
	period[7] =  period[6] + periodD*1.6;
	period[8] =  period[7] + periodD*1.8;	
	   
	period[9] =  periodD*55;		
		  
	period[10] =  period[9] + periodD*1.8;	  
	period[11] =  period[10] + periodD*1.6;
	period[12] =  period[11] + periodD*1.4;

	period[13] =  period[12] + periodD*1.2;
	period[14] =  period[13] + periodD;
	period[15] =  period[14] + periodD*0.8;

	period[16] =  period[15] + periodD*0.6;
	period[17] =  period[16] + periodD*0.4;
	period[18] =  period[17] + periodD*0.2;

	
	SBUF=period[0]; //将接收到的数据放入到发送寄存器
	while(!TI);		  //等待发送数据完成
	TI=0;			  //清除发送完成标志位	  
	//time PWMNum
	TR0=1;
}

void stageChangeTODO(unsigned char stage_now){

	if(cnt_timer1>=period[stage_now])
	{
		stage++;
		C_H = c_TH[stage];
		C_L = c_TL[stage];
	}
}
void Time1(void) interrupt 1    //3 为定时器1的中断号  1 定时器0的中断号 0 外部中断1 2 外部中断2  4 串口中断
{
	PWM=~PWM;
	if(stage <12)
	{
	stageChangeTODO(stage);
	}
	else if(stage == 12)
	{
		if(cnt_timer1>=period[stage])	
		{
	  	  PWM=0;
		  cnt_timer1=0;
		  TR0=0;
		}
	}

	TH0 = C_H; 
	TL0 = C_L;
	cnt_timer1++;    

}
