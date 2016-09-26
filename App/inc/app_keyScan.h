#ifndef _APP_KEYSCAN_H_
#define _APP_KEYSCAN_H_


#include "key.h"


typedef char u8KeyType_t;


// key scan parameters
#define PERIOD_KEY_SCAN             50   /*key scan period: 10ms*/
#define PERIOD_FIRST_LONG_KEY       2000
#define PERIOD_CONTIONOUS_LONG_KEY  200

// Specific KEY definition
#define KEYBUFFSIZE 4
#define KEY_UP          KEY0
#define KEY_DOWN        KEY1
#define KEY_CONFIRM     KEY2


// key state
#define NO_KEY          0
#define SHORT_KEY       1 
#define LONG_KEY        2


// key code define
#define KEYCODE_NO_PRESS     (unsigned char)0x00

#define SHORT_KEY_CODE       (unsigned char)0x10 
#define FIRSTLONG_KEY_CODE   (unsigned char)0x80
#define AFTERLONG_KEY_CODE   (unsigned char)0xC0
#define RELEASE_KEY_CODE     (unsigned char)0xE0

/* short key code */
#define KEY_UP_SHORT_KEY_CODE       (unsigned char)0x01 
#define KEY_DOWN_SHORT_KEY_CODE     (unsigned char)0x02 
#define KEY_CFM_SHORT_KEY_CODE      (unsigned char)0x04

/* first long key code */
#define KEY_UP_FRTLONG_KEY_CODE        (unsigned char)0x81 
#define KEY_DOWN_FRTLONG_KEY_CODE      (unsigned char)0x82 
#define KEY_CFM_FRTLONG_KEY_CODE       (unsigned char)0x84

/* continous long key code after the first long key */
#define KEY_UP_LONG_KEY_CODE        (unsigned char)0xC1 
#define KEY_DOWN_LONG_KEY_CODE      (unsigned char)0xC2 
#define KEY_CFM_LONG_KEY_CODE       (unsigned char)0xC4


//KEY function
void keyScan(void);
u8KeyType_t keyScan_readBuff(void);


		 				    
#endif

