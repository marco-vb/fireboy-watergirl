#ifndef __MOUSE_H
#define __MOUSE_H

#include <stdbool.h>
#include <stdint.h>
#include "i8042.h"

typedef struct {
    struct packet data;
    int byte;
    bool complete;
} mouse_packet_t;

int (mouse_subscribe_int)(uint8_t* bit_no);
int (mouse_unsubscribe_int)();
void (m_read_byte)(uint8_t b);
void (mouse_ih)();
int (mouse_send_cmd)(uint8_t cmd);
int (mouse_enable_dr)();
int (mouse_disable_dr)();

#endif /* __MOUSE_H */
