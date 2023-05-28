#include <lcom/lcf.h>
#include "drivers/serial_port/ser.h"
#include "drivers/kbc/keyboard.h"
#include "communication.h"

void send_keyboard_key(keyboard_key key) {
    send_queue_push('k');
    send_queue_push(key);
}

void send_destroyed_rope(uint8_t x, uint8_t y) {
    send_queue_push('r');
    send_queue_push(x);
    send_queue_push(y);
}
