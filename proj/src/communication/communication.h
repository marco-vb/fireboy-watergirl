#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <stdint.h>

#define KEYBOARD_ID 'k'
#define ROPE_ID 'r'
#define CHANGE_ID 'x'
#define CONNECT_ID 'c'
#define CONNECT_ACK 0xFA
#define CONNECT_START 0xF9
#define CONNECT_READY 0xFB
#define GAME_OVER_ID 0x10

void send_keyboard_key(keyboard_key key);
void send_destroyed_rope(uint8_t x, uint8_t y);
void send_start_connection();
void send_accept_connection();
void send_ready_connection();
void send_game_over();
bool check_connection();
bool check_ready();

#endif
