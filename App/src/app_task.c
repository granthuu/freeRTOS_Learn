#include "app_task.h"



static void redLed_Task(void *pvParameters)
{
    static u8 state = 0;
    pvParameters = pvParameters;
    
    while(1)
    {
        (state = !state) == 1 ? (LED0 = 0) : (LED0 = 1);
        vTaskDelay(500/portTICK_RATE_MS);       
    }
}


static void greenLed_Task(void *pvParameters)
{
    static u8 state = 0;
    pvParameters = pvParameters;
    
    while(1)
    {
        (state = !state) == 1 ? (LED1 = 0) : (LED1 = 1);
        vTaskDelay(1000/portTICK_RATE_MS);        
    }
}


 
void app_createTask(void)
{
    xTaskCreate( redLed_Task,   "LED1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);      
    xTaskCreate( greenLed_Task, "LED2", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 2, NULL );
}

