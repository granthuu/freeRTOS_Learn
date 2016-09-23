#ifndef _APP_TASK_H
#define _APP_TASK_H

#include "FreeRTOS.h"
#include "task.h"
#include "led.h"



#define LED_TASK_STACK_SIZE (256)  /* 256 * 2 = 512Byte */


#define LED_TASK_PRIORITY   (1)


void app_createTask(void);


#endif /* _APP_TASK_H */




