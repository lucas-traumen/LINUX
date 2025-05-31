#ifndef UART_BUILDER_H
#define UART_BUILDER_H

#include <stdint.h>

// UART Configuration Structure
typedef struct {
    uint32_t baudRate;  // Baud rate (e.g., 9600, 115200)
    uint8_t parity;     // 0: None, 1: Odd, 2: Even
    uint8_t stopBits;   // 1: 1 Stop Bit, 2: 2 Stop Bits
    uint8_t dataBits;   // 8: 8 Data Bits, 9: 9 Data Bits
} UART_Config_t;

// UART Builder Structure
typedef struct UART_Builder {
    UART_Config_t config;
    struct UART_Builder* (*setBaudRate)(struct UART_Builder*, uint32_t);
    struct UART_Builder* (*setParity)(struct UART_Builder*, uint8_t);
    struct UART_Builder* (*setStopBits)(struct UART_Builder*, uint8_t);
    struct UART_Builder* (*setDataBits)(struct UART_Builder*, uint8_t);
    UART_Config_t (*build)(struct UART_Builder*);
} UART_Builder;

// Function to initialize the Builder
UART_Builder UART_Builder_Init();

#endif // UART_BUILDER_H
    