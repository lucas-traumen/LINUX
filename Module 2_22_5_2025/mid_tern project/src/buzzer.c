// buzzer.c
#include "buzzer.h"


#define BUZZER_PORT GPIOB
#define BUZZER_PIN  GPIO_PIN_0

//extern TIM_HandleTypeDef htim2;

void buzzer_init(void) {
    // GPIO_InitTypeDef GPIO_InitStruct = {0};
    // __HAL_RCC_GPIOB_CLK_ENABLE();
    // GPIO_InitStruct.Pin = BUZZER_PIN;
    // GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    // GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    // HAL_GPIO_Init(BUZZER_PORT, &GPIO_InitStruct);
    // HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_RESET);
}

void buzzer_beep_ms(FILE *log,uint16_t ms) {
    // HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_SET);
    for( int i =0;i<(ms/100);i++);
    fprintf(log," bip...bip...bip.....bip... \n");
    // HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_RESET);
}

void buzzer_alarm_ms(FILE*log,uint8_t times, uint16_t on_ms, uint16_t off_ms) {
    for (uint8_t i = 0; i < times; i++) {
        buzzer_beep_ms(log,on_ms);
        //HAL_Delay(off_ms);
    }
}
