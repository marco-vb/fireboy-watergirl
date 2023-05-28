#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <stdint.h>

#define KEYBOARD_ID 'k'
#define ROPE_ID 'r'

void send_keyboard_key(keyboard_key key);
void send_destroyed_rope(uint8_t x, uint8_t y);

#endif
