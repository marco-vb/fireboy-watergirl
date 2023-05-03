#include <lcom/lcf.h>

#include <stdint.h>
#include <stdbool.h>

#include "kbc.h"

int (kbc_get_status)(uint8_t* st) {
    return util_sys_inb(KBC_ST_REG, st);
}

int (kbc_read_data)(uint8_t* data) {
    return util_sys_inb(KBC_OUT, data);
}

int (kbc_write)(uint8_t port, uint8_t data) {
    uint8_t st, wait = 5;

    while (wait--) {
        if (kbc_get_status(&st) || st & KBC_IN_FULL) {
            tickdelay(WAIT_KBC);
            continue;
        }

        sys_outb(port, cmd);
        return 0;
    }
    return 1;
}

int (kbc_write_cmd)(uint8_t cmd) {
    return kbc_write(KBC_IN, cmd);
}

int (kbc_write_arg)(uint8_t arg) {
    return kbc_write(KBC_IN_ARGS, arg);
}

int (buffer_full)(uint8_t flag) {
    uint8_t status, tries = 10;

    while (tries--) {
        if (kbc_get_status(&status)) {
            continue;
        }
        if (status & flag) {
            return 1;
        }
    }
    return 0;
}

int (ibf_empty)() {
    return !buffer_full(KBC_IN_FULL);
}

int (obf_full)() {
    return buffer_full(KBC_OUT_FULL);
}
