#include "app_keyScan.h"
#include "app_task.h"
#include <stdio.h>

extern xQueueHandle xKeyValueQueue;

static uint32_t keyCounterL = 0, keyCounterS = 0;
char keyState = 0;


extern void vPortEnterCritical( void );
extern void vPortExitCritical( void );

#if 0

char keybuff[KEYBUFFSIZE] = {0};
char key_indexW = 0;
char key_indexR = 0;
char length = 0;

static void keyScan_writeBuff(char keyValue)
{
    if(length >= KEYBUFFSIZE )
        return;
    
    vPortEnterCritical();
    
    length ++;
    keybuff[key_indexW] = keyValue;
    if(++key_indexW >= KEYBUFFSIZE)
        key_indexW = 0;
    
    vPortExitCritical();
}


u8KeyType_t keyScan_readBuff(void)
{
    u8KeyType_t key;
    if(length == 0) return 0;
    
    vPortEnterCritical();
    
    length --;
    key = keybuff[key_indexR];
    if(++key_indexR >= KEYBUFFSIZE)
        key_indexR = 0;
    
    vPortExitCritical();
    
    return key;
}
#endif



// KEY_UP: 0X01;   KEY_DOWN: 0X02;    KEY_CONFIRM: 0X04
static u8KeyType_t keyScan_getKey(void)
{
    uint8_t a = 0, b = 0, c = 0;
    uint8_t keyValue = 0;
    
    a = (KEY_UP == 0) ?      1 : 0;  // 按键按下为低电平
    b = (KEY_DOWN == 0) ?    1 : 0;  // 按键按下为低电平
    c = (KEY_CONFIRM == 1) ? 1 : 0;  // 按键按下为高电平
    
    //printf("a: %d, b: %d, c: %d\n", a, b, c);
    keyValue = a |(b << 1) | (c <<2);
    
    return keyValue;
}

void keyScan(void)
{
    static u8KeyType_t kPreKey = 0;
    u8KeyType_t kNewKey = 0;
    u8KeyType_t keyCode;
    
    if(keyState == LONG_KEY) 
        keyCounterL++;
    else
        keyCounterL =0;
    
    if(keyState == SHORT_KEY) 
        keyCounterS++;
    else
        keyCounterS =0;
    
    // read key value 
    kNewKey = keyScan_getKey();
    //printf("keyValue: 0x%x \n", kNewKey);
    
    switch(keyState)
    {
        case NO_KEY:
            if(kNewKey != KEYCODE_NO_PRESS) 
            {
                keyState = SHORT_KEY;
                kPreKey = kNewKey;
            }                
            else                
                keyState = NO_KEY;
        break;
        
        case SHORT_KEY:
            
            if(kNewKey == kPreKey )  // 仍然是上一个按键
            {
                if(keyCounterS >=   PERIOD_FIRST_LONG_KEY/PERIOD_KEY_SCAN)  /* 2s: first long press */
                {
                    keyCounterS = 0;
                    //keyScan_writeBuff(kPreKey + FIRSTLONG_KEY_CODE);
                    
                    keyCode = kPreKey + FIRSTLONG_KEY_CODE;
                    xQueueSendToBack(xKeyValueQueue, &keyCode, 0);
                    
                    keyState = LONG_KEY;
                }     
            }
            else
            {
                //keyScan_writeBuff(kPreKey);

                keyCode = kPreKey;
                xQueueSendToBack(xKeyValueQueue, &keyCode, 0);
                
                kPreKey = KEYCODE_NO_PRESS;
                keyState = NO_KEY;
            }
            
        break;
            
        case LONG_KEY:
            
            if(kNewKey == kPreKey )  // 仍然是上一个按键
            {
                if(keyCounterL >= PERIOD_CONTIONOUS_LONG_KEY/PERIOD_KEY_SCAN)  /* 300ms: continous long press */
                {
                    keyCode = AFTERLONG_KEY_CODE + kPreKey;
                    xQueueSendToBack(xKeyValueQueue, &keyCode, 0);
                    
                    //keyScan_writeBuff(AFTERLONG_KEY_CODE + kPreKey); 
                    keyCounterL = 0;
                }
            }
            else
            {

#if 1    /* grant add code here. to notify that release key action finished. */     

                keyCode = kPreKey + RELEASE_KEY_CODE;
                xQueueSendToBack(xKeyValueQueue, &keyCode, 0);
                keyState = NO_KEY;

#else
                kPreKey = KEYCODE_NO_PRESS;
                keyState = NO_KEY;

#endif

            }         
        break;
            
        default:
            break;
    }
}


