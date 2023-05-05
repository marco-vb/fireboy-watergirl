#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    uint8_t data[2];
    uint8_t byte;
    bool complete;
} keyboard_packet_t;

int (keyboard_subscribe_int)(uint8_t* bit_no);
int (keyboard_unsubscribe_int)();
void (k_read_byte)(uint8_t b);
void (keyboard_ih)();
int (keyboard_restore_int)();

#endif /* __KEYBOARD_H */
