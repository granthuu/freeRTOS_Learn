#ifndef _KEY_H
#define _KEY_H

#include "stm32f10x.h"


#define KEY0    GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)   //��ȡ����0
#define KEY1    GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)  //��ȡ����1
#define KEY2    GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)   //��ȡ����2 




void key_init(void);

#endif  /* _KEY_H */

