#include <reg52.h>
#include<intrins.h>
#define uchar unsigned char
#define uint unsigned int
#define LED P1

//因为步进电机是减速步进电机，减速比的1/64 ，
//所以N=64时，步进电机主轴转一圈
//使用前请短接J2跳线帽，串口助手设置为比特率9600，无校验位，停止位1，发送数据为16进制形式
uchar code CCW[8]        ={0x08,0x0c,0x04,0x06,0x02,0x03,0x01,0x09};                   //逆时钟旋转相序表
uchar code CW[8]        ={0x09,0x01,0x03,0x02,0x06,0x04,0x0c,0x08};                   //正时钟旋转相序表
//uchar code table[]        ={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};        //数码管显示数字表
sbit P2_0 = P2^0;
sbit P2_1 = P2^1;
sbit P2_2 = P2^2;
sbit P2_3 = P2^3;
sbit FMQ=P3^6;  //蜂鸣器

uchar          flag_rec;
uint        data_rec;
/*********************************************************************
        中断服务特殊功能寄存器配置
*********************************************************************/
void init_interrupt()
{
        TMOD=0x20;                //用定时器1设置串口波特率         9600
        TH1=0xfd;                //T1定时器装初值
        TL1=0xfd;                //T1定时器装初值
        TR1=1;                    //启动T1定时器
        REN=1;          //串口初始化
        SM0=0;                        //设定串口工作方式1
        SM1=1;                        //设定串口工作方式1
        EA=1;           //开启总中断
        ES=1;                        //开启串口中断

}

/*************************************************************
                                串口中断函数
**************************************************************/
void receive() interrupt 4
{
        RI=0;                                        //RI清零；因为收到数据或者或者发送了数据会由硬件置1
        data_rec=SBUF;                        //接收数据SBUF，将SBUF中的数据读走给data_rec,即将计算机的数据接收。
        //a=SBUF;
        ES = 0;                                        //关闭串口中断
        flag_rec=1;                                //中断标志位置1
}
/*****************************************************************
                                设置延时
******************************************************************/
void delaynms(uint aa)
{
  uchar bb;
  while(aa--)
  {   
          for(bb=0;bb<115;bb++)     //1ms基准延时程序
        {    ;   }
  }

}
void delay500us()
{
  int j;
  for(j=0;j<57;j++)
  {
   ;
  }
}
/*******************************************
                                蜂鸣器
******************************************/
void beep()
{
          uchar t;
          for(t=0;t<100;t++)
          {
                   delay500us();
                 FMQ=!FMQ;   //产生脉冲
          }
          FMQ=1;    //关闭蜂鸣器
}
/***************************************
                                正反转设计
****************************************/
void motor_ccw_deta(uchar deta,uchar speed)        //电机逆时针转deta度 deta=11时30度，deta=66d时180度
{
        uchar i;
        while(deta--)
        {
                for(i=0;i<8;i++)  //数组循环一周
                {
                        P1=CCW[i];
                        delaynms(speed);   //调节转速
                }
        }
}

void motor_cw_deta(uchar deta,uchar speed)        //电机顺时针转deta度 deta=11时30度，deta=66时180度
{
        uchar i;
        while(deta--)
        {
                 for(i=0;i<8;i++)  //内部循环一周
                 {
                           P1=CW[i];
                           delaynms(speed);   //调节转速
                }
        }
}
void Digital_tube_display(uint num)
{
        //4位数码管显示控制
        
        uchar temp,count;
        temp         = 0;
        count         = 0;
        if(num > 999 || num < 0) return;
        while(num)
        {
                temp         = num % 10;
                P0                 = table[temp];
                switch(count)    //判断
                {
                        case 0:P2_3=0;break;  //点亮第1个灯
                        case 1:P2_2=0;break;  //点亮第2个灯
                        case 2:P2_1=0;break;  //点亮第3个灯
                        case 3:P2_0=0;break;  //点亮第4个灯
                }
                delaynms(5);
                switch(count)    //判断
                {
                        case 0:P2_3=1;break;  //点亮第1个灯
                        case 1:P2_2=1;break;  //点亮第2个灯
                        case 2:P2_1=1;break;  //点亮第3个灯
                        case 3:P2_0=1;break;  //点亮第4个灯
                }
                num         = num / 10;
                count++;
        }
}

/**************************************************************
                                                           中断处理函数
****************************************************************/
void deal_interrupt_Date(uint dat)
{

        SBUF=dat;                         //发送数据dat_rec到SBUF，即将单片机的数据发送到计算机
        while(!TI);
        TI = 0;

        beep();
        motor_cw_deta(11,1);        //电机顺转deta度，deta=11时30度，deta=66时180度
        delaynms(10*dat);                //由于目前还没有找到如何传输255以上的数的方法，所以先乘以10
        motor_ccw_deta(11,1);        //电机逆转deta龋琩eta=11时30度，deta=66时180度                        
        
        ES=1;                 //打开串口中断        
        flag_rec=0;
}

/**************************************************************
                                                        主程序
****************************************************************/
void main()
{        
        init_interrupt();
        Digital_tube_display(0);
        while(1)
        {
                Digital_tube_display(data_rec);
                P1=0xf0;
                if(flag_rec)        //收到串口数据时，处理
                {
                        deal_interrupt_Date(data_rec);
                }
                
        }
}