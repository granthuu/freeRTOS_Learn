Platform:
	zhengdianyuanzi development board V3.0 
	stm32F103RC


1. init project: 2 LEDs flashing demo.
	
2. import FreeRTOSv8.2, didn't modify FreeRTOSConfig.h
	2 LEDS flashing demo.	

3. modify FreeRTOSConfig.h file. config task priorities.
	config interrupt priority.

4. add usart interrupt routine.
   and in this ISR, give an binary semaphore.
   
   In application layer, the red and green led task take this semaphore.
   and print according message.
   
   keywords: semaphore, interrupt.
   