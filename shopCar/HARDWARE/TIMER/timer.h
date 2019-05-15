#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"

#define PWM_1 299
#define PWM_2 279
#define PWM_3 299
#define PWM_4 299


void TIM1_PWM_Init(u16 arr,u16 psc);
void TIM2_PWM_Init(u16 arr,u16 psc);
void TIM3_PWM_Init(u16 arr,u16 psc);
void TIM4_Int_Init(u16 arr,u16 psc);
void TIM5_PWM_Init(u16 arr,u16 psc);
void TIM6_Int_Init(u16 arr,u16 psc);
void TIM7_Int_Init(u16 arr,u16 psc);


#endif
