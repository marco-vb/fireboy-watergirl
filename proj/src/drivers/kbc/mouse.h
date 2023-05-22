#ifndef __MOUSE_H
#define __MOUSE_H

#include <lcom/lcf.h>

#include <stdint.h>
#include "i8042.h"
#include "../../sprites/sprite.h"

typedef struct {
    int16_t byte, x, y;
    int16_t delta_x, delta_y;
    uint8_t bytes[3];
    uint8_t rb, mb, lb, x_ov, y_ov, complete;
} mouse_packet_t;

int (mouse_subscribe_int)(uint8_t* bit_no);
int (mouse_unsubscribe_int)();
void (m_read_byte)(uint8_t b);
void (mouse_build_packet)();
void (mouse_update_pos)();
void (mouse_ih)();
int (mouse_send_cmd)(uint8_t cmd);
int (mouse_enable_dr)();
int (mouse_disable_dr)();
int (mouse_stream_mode)();
int (mouse_inside)(uint16_t x, uint16_t y, uint16_t width, uint16_t height);
int (mouse_over_sprite)(Sprite* sp);
int (mouse_lclick_sprite)(Sprite* sp);
int (mouse_rclick_sprite)(Sprite* sp);

#endif /* __MOUSE_H */
