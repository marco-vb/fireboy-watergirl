#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include <stdbool.h>
#include <stdint.h>

int (keyboard_subscribe_int)(uint8_t* bit_no);
int (keyboard_unsubscribe_int)();
int (keyboard_read_data)();
int (keyboard_write_cmd)(uint8_t cmd);
int (keyboard_write_arg)(uint8_t arg)
void (keyboard_ih)();
int (keyboard_write)(uint8_t port, uint8_t cmd);
int (keyboard_restore_int)();

#endif /* __KEYBOARD_H */
