#ifndef UART_H
#define UART_H

#include <lcom/lcf.h>

#define SER_BASE 0x3F8
#define SER_DLL SER_BASE
#define SER_DLM (SER_BASE + 1)
#define SER_LCR (SER_BASE + 3)
#define PAR_ODD 1
#define PAR_EVEN 2
#define PAR_ALWAYS_ODD 3
#define PAR_ALWAYS_EVEN 4
#define LCR_DLAB BIT(7)

#endif
