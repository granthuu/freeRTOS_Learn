#ifndef _APP_TASK_H
#define _APP_TASK_H

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "led.h"


#define LED_TASK_STACK_SIZE     (128)  /* 128 * 4bytes = 512Byte, 32bit cpu */
#define PRINT_TASK_STACK_SIZE   (128)

#define LED_TASK_PRIORITY       (1)



extern SemaphoreHandle_t xSemaphore;


void app_createTask(void);


#endif /* _APP_TASK_H */




