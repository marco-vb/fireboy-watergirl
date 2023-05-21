#include <lcom/lcf.h>
#include "ser.h"
#include "uart.h"

int line_ctrl_reg_read(uint8_t *info) {
    if (util_sys_inb(SER_LCR, info)) {
        return 1;
    }

    return 0;
}

int line_ctrl_reg_conf(uint8_t bits, uint8_t stop, uint8_t par_mode) {
    uint8_t conf = BIT(3);

    if (bits < 5 || bits > 8) {
        printf("Invalid number of bits (5-8)\n");
        return 1;
    }

    if (stop < 1 || stop > 2) {
        printf("Invalid number of stop bits (1-2)\n");
        return 1;
    }

    if (par_mode > 4 || par_mode < 1) {
        printf("Invalid parity mode (1-4)\n");
        return 1;
    }

    conf |= bits - 5;

    conf |= ((stop - 1) << 2);

    if (par_mode % 2 == 0)
        conf |= BIT(4);
    if (par_mode > 2)
        conf |= BIT(5);

    if (sys_outb(SER_LCR, conf))
        return 1;

    return 0;
}
