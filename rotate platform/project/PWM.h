#ifndef __PWM_H_
#define __PWM_H_

#define u8 unsigned char
#define u16 unsigned int

void PWM_Init();
void Set_PWM_Num();
void stageChangeTODO(unsigned char stage_now);
extern unsigned char stage;
#endif

