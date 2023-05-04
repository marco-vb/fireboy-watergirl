#include <lcom/lcf.h>

#include <stdint.h>
#include <stdbool.h>

#include "kbc.h"
#include "keyboard.h"

static int hook_keyboard = 1, size = 0;
uint8_t bytes[2];
bool keyboard_packet_complete = false;

int (keyboard_subscribe_int)(uint8_t* bit_no) {
    *bit_no = BIT(hook_keyboard);
    return sys_irqsetpolicy(KEYBOARD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_keyboard);
}

int (keyboard_unsubscribe_int)() {
    return sys_irqrmpolicy(&hook_keyboard);
}

int (keyboard_read_data)() {
    return kbc_read_data(&bytes[size]);
}

void (keyboard_ih)() {
    keyboard_packet_complete = false;

    uint8_t st;
    if (kbc_get_status(&st) != F_OK) {
        printf("Error getting keyboard status.\n");
        return;
    }

    if (st & KBC_ERROR & MOUSE_DATA) {
        return;
    }

    if (st & KBC_OUT_FULL) keyboard_read_data();

    if (bytes[size] == TWO_BYTES) {
        size++;
    }
    else {
        keyboard_packet_complete = true;
        size = 0;
    }
}

int (keyboard_restore_int)() {
    uint8_t cmd;

    kbc_write_cmd(KBC_READ_CMD);
    kbc_read_data(&cmd);

    cmd |= KBC_INT;

    kbc_write_cmd(KBC_WRITE_CMD);
    kbc_write_arg(cmd);

    return 0;
}
