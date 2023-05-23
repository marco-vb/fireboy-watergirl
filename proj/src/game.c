#include <lcom/lcf.h>

#include <stdbool.h>
#include <stdint.h>

#include "game.h"

uint8_t irq_mouse, irq_timer, irq_keyboard;

int game_init() {
    if (video_mode()) {
        printf("Error setting video mode.\n");
        return 1;
    }

    if (timer_subscribe_int(&irq_timer)) {
        printf("Error subscribing timer interrupts.\n");
        return 1;
    }

    timer_set_frequency(0, 30);

    if (kbc_init(&irq_keyboard, &irq_mouse)) {
        printf("Error initializing kbc.\n");
        return 1;
    }

    if (load_sprites()) {
        printf("Error loading cursor.\n");
        return 1;
    }

    return 0;
}

int game_exit() {
    if (kbc_disable() != OK) {
        printf("Error disabling kbc.\n");
        return 1;
    }

    if (timer_unsubscribe_int()) {
        printf("Error unsubscribing timer interrupts.\n");
        return 1;
    }

    if (text_mode() != OK) {
        printf("Error exiting video mode.\n");
        return 1;
    }

    return 0;
}

game_state state = MAIN_MENU;

int game_loop() {
    int ipc_status, r;
    message msg;

    do {
        if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
            printf("Error receiving message: %d\n", r);
            continue;
        }

        if (is_ipc_notify(ipc_status)) {
            switch (_ENDPOINT_P(msg.m_source)) {
            case HARDWARE:
                if (msg.m_notify.interrupts & irq_mouse) {
                    mouse_ih();
                    if (!mouse_packet.complete) continue;

                    cursor->x = mouse_packet.x;
                    cursor->y = mouse_packet.y;
                }

                if (msg.m_notify.interrupts & irq_timer) {
                    timer_ih();
                    draw_screen();
                }

                if (msg.m_notify.interrupts & irq_keyboard) {
                    keyboard_ih();
                    if (keyboard_packet.complete) {
                        if (keyboard_get_key() == KEY_A) {
                            cursor->x = 0;
                            cursor->y = 0;
                        }
                    }
                }
                break;
            default:
                break;
            }
        }
    } while (keyboard_packet.data[0] != ESC_BREAK && state != EXIT);

    return 0;
}

int draw_screen() {
    return draw_main_menu();
    switch (state) {
    case MAIN_MENU:
        draw_main_menu();
        break;
    case SETTINGS_MENU:
        draw_settings_menu();
        break;
    case GAME:
        draw_game();
        break;
    case PAUSE_MENU:
        draw_pause_menu();
        break;
    case GAME_OVER:
        draw_game_over();
        break;
    default:
        break;
    }

    return 0;
}

int draw_main_menu() {
    draw_sprite(logo);

    if (mouse_over_sprite(play_text)) {
        draw_sprite(play_texth);
        if (mouse_lclick_sprite(play_text)) {
            state = GAME;
        }
    }
    else {
        draw_sprite(play_text);
    }
    if (mouse_over_sprite(settings_text)) {
        draw_sprite(settings_texth);
        if (mouse_lclick_sprite(settings_text)) {
            state = SETTINGS_MENU;
        }
    }
    else {
        draw_sprite(settings_text);
    }
    if (mouse_over_sprite(exit_text)) {
        draw_sprite(exit_texth);
        if (mouse_lclick_sprite(exit_text)) {
            state = EXIT;
        }
    }
    else {
        draw_sprite(exit_text);
    }

    draw_sprite(cursor);
    draw_buffer();

    return 0;
}

int draw_settings_menu() {
    return 0;
}

int draw_game() {
    return 0;
}

int draw_pause_menu() {
    return 0;
}

int draw_game_over() {
    return 0;
}
