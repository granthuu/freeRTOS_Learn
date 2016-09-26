#include "app_task.h"
#include "app_keyScan.h"
#include "stdio.h"

extern u8 g_u8RecByte;

SemaphoreHandle_t xSemaphore = NULL;
xQueueHandle xKeyValueQueue  = NULL;

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
        printf("%c", g_u8RecByte);
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
 
void keyScan_Task(void *pvParameters)
{
    char key;
    portBASE_TYPE xStatus;
    
    pvParameters = pvParameters;
    
    while(1)
    {
        keyScan();
        xStatus = xQueueReceive(xKeyValueQueue, &key, 0);
        if(xStatus == pdPASS)
        { 
            printf("key: 0x%x \n", key);

            switch(key)
            {
                case KEY_UP_FRTLONG_KEY_CODE:
                case KEY_UP_LONG_KEY_CODE:    /* for BUMP on/off */
                break;

                case KEY_DOWN_FRTLONG_KEY_CODE:
                case KEY_DOWN_LONG_KEY_CODE:   /* for VALVE on/off */ 
                break;

                case (RELEASE_KEY_CODE + KEY_UP_SHORT_KEY_CODE):
                break;

                case (RELEASE_KEY_CODE + KEY_DOWN_SHORT_KEY_CODE):
                break;

                case KEY_CFM_SHORT_KEY_CODE:
                    
                break;
                
                default:
                    break;
            }  
        }

        vTaskDelay(50/portTICK_RATE_MS);
    }
}


void app_createTask(void)
{
    // Create the semaphore to guard a shared resource.
    vSemaphoreCreateBinary( xSemaphore );
    xKeyValueQueue     = xQueueCreate(10, sizeof(char));
    
    if((xSemaphore != NULL) && (xKeyValueQueue != NULL))
    {
        xTaskCreate( redLed_Task,   "LED1",    LED_TASK_STACK_SIZE,   NULL, tskIDLE_PRIORITY + 3, NULL);      
        xTaskCreate( greenLed_Task, "LED2",    LED_TASK_STACK_SIZE,   NULL, tskIDLE_PRIORITY + 2, NULL);
        xTaskCreate( print_Task,    "print",   PRINT_TASK_STACK_SIZE, NULL, tskIDLE_PRIORITY + 2, NULL);    
        xTaskCreate( keyScan_Task,  "keyScan", PRINT_TASK_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
    }
}

