#ifndef BUZZER_H
#define BUZZER_H

#include <stdint.h>
//#include "stm32f1xx_hal.h"
#include "logger.h"


void buzzer_init(void);       
void buzzer_beep_ms(FILE *log,uint16_t ms); 
void buzzer_alarm_ms(FILE *log,uint8_t times, uint16_t on_ms, uint16_t off_ms); 

#endif
