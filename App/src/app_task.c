#include "app_task.h"
#include "stdio.h"

extern u8 g_u8RecByte;

SemaphoreHandle_t xSemaphore = NULL;

static void redLed_Task(void *pvParameters)
{
    u8 state = 0;
    pvParameters = pvParameters;
    
    while(1)
    {
        //(state = !state) == 1 ? (LED0 = 0) : (LED0 = 1);
        //vTaskDelay(500/portTICK_RATE_MS);  

        xSemaphoreTake( xSemaphore, ( TickType_t ) portMAX_DELAY);
        (state = !state) == 1 ? (LED0 = 0) : (LED0 = 1);
        portENTER_CRITICAL();
        printf("red led\n");
        portEXIT_CRITICAL();
    }
}


static void greenLed_Task(void *pvParameters)
{
    u8 state = 0;
    pvParameters = pvParameters;
    
    while(1)
    {
        //(state = !state) == 1 ? (LED1 = 0) : (LED1 = 1);
        //vTaskDelay(1000/portTICK_RATE_MS);   

        xSemaphoreTake( xSemaphore, ( TickType_t ) portMAX_DELAY);
        (state = !state) == 1 ? (LED1 = 0) : (LED1 = 1);
        portENTER_CRITICAL();
        printf("green led\n");
        portEXIT_CRITICAL();

    }
}

static void print_Task(void *pvParameters)
{
    pvParameters = pvParameters;
    
    while(1)
    {
        portENTER_CRITICAL();
        printf("print task.\n");
        portEXIT_CRITICAL();
        vTaskDelay(1000/portTICK_RATE_MS);        
    }
}
 
void app_createTask(void)
{
    // Create the semaphore to guard a shared resource.
    vSemaphoreCreateBinary( xSemaphore );

    if( xSemaphore != NULL )
    {
        xTaskCreate( redLed_Task,   "LED1",  configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 3, NULL);      
        xTaskCreate( greenLed_Task, "LED2",  configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 2, NULL);
        xTaskCreate( print_Task,    "print", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 2, NULL);    
    }
}

