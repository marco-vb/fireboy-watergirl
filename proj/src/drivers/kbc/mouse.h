#ifndef __MOUSE_H
#define __MOUSE_H

#include <stdbool.h>
#include <stdint.h>
#include "i8042.h"

//enum mouse_state {};

int (mouse_subscribe_int)(int* bit_no);
int (mouse_unsubscribe_int)();
void (mouse_ih)();
int (mouse_send_cmd)(uint8_t cmd);
void (mouse_build_packet)();
int (mouse_write)(uint8_t cmd);

#endif /* __MOUSE_H */
