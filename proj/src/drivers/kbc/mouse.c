#include <lcom/lcf.h>

#include <stdbool.h>
#include <stdint.h>

#include "kbc.h"
#include "mouse.h"

static int hook_mouse = 2, size = 0;
struct packet pp;
bool mouse_packet_complete = false;

int(mouse_subscribe_int)(int* bit_no) {
    *bit_no = BIT(hook_mouse);
    return sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_mouse);
}

int(mouse_unsubscribe_int)() {
    return sys_irqrmpolicy(&hook_mouse);
}

int (mouse_send_cmd)(uint8_t cmd) {
    uint8_t tries = 10, res = 0;

    while (res != MOUSE_ACK) {
        if (tries-- <= 0) {
            printf("Could not send command to mouse!\n");
            return 1;
        }

        if (!ibf_empty()) {
            tickdelay(WAIT_KBC);
            continue;
        }

        kbc_write_cmd(MOUSE_WRITE_DATA);

        if (!ibf_empty()) {
            tickdelay(WAIT_KBC);
            continue;
        }

        kbc_write_arg(cmd);

        if (!obf_full()) {
            tickdelay(WAIT_KBC);
            continue;
        }

        if (kbc_read_data(&res)) {
            tickdelay(WAIT_KBC);
            continue;
        }
    }

    return 0;
}

void (mouse_ih)() {
    mouse_packet_complete = false;

    uint8_t st, byte;

    if (size > 2) {
        size = 0;
    }

    if (kbc_get_status(&st)) {
        printf("Error reading status!\n");
        return;
    }

    if (st & (KBC_OUT_FULL | MOUSE_DATA)) {
        kbc_read_data(&byte);

        if (st & KBC_ERROR) {
            printf("Error reading data!\n");
            return;
        }

        if (size == 0 && !(byte & MOUSE_SYNC_BIT)) {
            printf("Mouse is not synced!\n");
            return;
        }

        pp.bytes[size++] = byte;

        mouse_packet_complete = size == 3;
    }
}
