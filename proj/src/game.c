#include <lcom/lcf.h>

#include <stdbool.h>
#include <stdint.h>

#include "game.h"
#include "maps/map.h"
#include "count_down/count_down.h"
#include "drivers/rtc/rtc.h"
int frames_per_second = 60;
int current_frame = 0;
extern Map* map1;
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

    timer_set_frequency(0, 60);

    if (kbc_init(&irq_keyboard, &irq_mouse)) {
        printf("Error initializing kbc.\n");
        return 1;
    }

    if (load_sprites()) {
        printf("Error loading cursor.\n");
        return 1;
    }
    if (load_maps()) {
        printf("Error loading maps.\n");
        return 1;
    }

    if (create_characters()) {
        printf("Error loading characters.\n");
        return 1;
    }

    if (rtc_init()) return 1;

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
                    if (on_fire(watergirl) || on_water(fireboy)) state = GAME_OVER;

                    update_character(fireboy);
                    update_character(watergirl);
                    draw_screen();
                }

                if (msg.m_notify.interrupts & irq_keyboard) {
                    keyboard_ih();
                    if (!keyboard_packet.complete) continue;
                    keyboard_key k = keyboard_get_key();

                    switch (k) {
                    case KEY_ESC:
                        if (state == MAIN_MENU) state = EXIT;
                        else if (state == GAME) state = GAME_OVER;
                        else {
                            state = MAIN_MENU;
                            watergirl->sprite->x = 300;
                            fireboy->sprite->x = 300;
                            clear_background();
                        }
                        break;

                    case KEY_A: case KEY_W: case KEY_S: case KEY_D:
                        fireboy_move(k);
                        break;

                    case KEY_LEFT: case KEY_UP: case KEY_DOWN: case KEY_RIGHT:
                        watergirl_move(k);
                        break;

                    case KEY_A_BREAK: case KEY_D_BREAK:
                        fireboy_move(k);
                        break;
                    case KEY_LEFT_BREAK: case KEY_RIGHT_BREAK:
                        watergirl_move(k);
                        break;
                    default:
                        break;
                    }
                }
            default:
                break;
            }
        }
    } while (state != EXIT);

    return 0;
}

int draw_screen() {
    switch (state) {
    case MAIN_MENU:
        draw_main_menu();
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
    draw_sprite(background);
    draw_sprite(logo);

    Sprite* single_player = mouse_over_sprite(single_player_text) ? single_player_texth : single_player_text;
    Sprite* coop = mouse_over_sprite(coop_text) ? coop_texth : coop_text;
    Sprite* exit = mouse_over_sprite(exit_text) ? exit_texth : exit_text;

    if (mouse_lclick_sprite(single_player)) {
        state = GAME;
        start_counter(120);
        clear_background();
        map1 = create_map(1);
        draw_map(map1);
        return 0;
    }
    if (mouse_lclick_sprite(coop)) {
        state = GAME;
        return 0;
    }
    if (mouse_lclick_sprite(exit)) {
        state = EXIT;
        return 0;
    }

    draw_sprite(single_player);
    draw_sprite(coop);
    draw_sprite(exit);
    draw_sprite(cursor);

    draw_buffer();

    erase_sprite(logo);
    erase_sprite(single_player);
    erase_sprite(coop);
    erase_sprite(exit);
    erase_sprite(cursor);

    return 0;
}

void draw_ropes() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (!ropes[i][j]) continue;
            draw_sprite(ropes[i][j]);
            int x_distf = abs(ropes[i][j]->x - fireboy->sprite->x);
            int y_distf = abs(ropes[i][j]->y - fireboy->sprite->y);
            int x_distw = abs(ropes[i][j]->x - watergirl->sprite->x);
            int y_distw = abs(ropes[i][j]->y - watergirl->sprite->y);

            if ((x_distf > 150 || y_distf > 150) &&
                (x_distw > 150 || y_distw > 150)) {
                continue;
            }

            if (mouse_lclick_sprite(ropes[i][j])) {
                while (j < 10 && ropes[i][j]) {
                    erase_sprite(ropes[i][j]);
                    destroy_sprite(ropes[i][j]);
                    ropes[i][j] = NULL;
                    j++;
                }
            }
        }
    }
}

int draw_game() {
    move(fireboy);
    move(watergirl);
    draw_character(fireboy);
    draw_character(watergirl);
    draw_ropes();
    draw_blocks();
    draw_sprite(cursor);

    draw_buffer();
    erase_sprite(cursor);
    erase_sprite(fireboy->sprite);
    erase_sprite(watergirl->sprite);
    erase_blocks();

    if ((current_frame++) == frames_per_second) {
        if (!decrement_counter())draw_counter();
        current_frame = 0;
    }


    draw_counter();
    draw_time();
    draw_date();

    return 0;
}

int draw_pause_menu() {
    return 0;
}

int draw_game_over() {

    if (mouse_inside(190, 540, 240, 80) && mouse_packet.lb) {
        state = MAIN_MENU;
        clear_background();
        return 0;
    }

    if (mouse_inside(770, 540, 240, 80) && mouse_packet.lb) {
        state = GAME;
        clear_background();
        start_counter(120);
        clear_background();
        map1 = create_map(1);
        draw_map(map1);
        fireboy->sprite->x = 300;
        watergirl->sprite->x = 300;
        return 0;
    }

    draw_sprite(game_over);
    draw_sprite(cursor);
    draw_buffer();

    erase_sprite(game_over);
    erase_sprite(cursor);

    return 0;
}

int fireboy_move(keyboard_key key) {
    switch (key) {
    case KEY_A:
        move_left(fireboy);
        break;
    case KEY_W:
        jump(fireboy);
        break;
    case KEY_D:
        move_right(fireboy);
        break;
    default:
        stop_moving(fireboy);
        break;
    }

    return 0;
}

int watergirl_move(keyboard_key key) {
    switch (key) {
    case KEY_LEFT:
        move_left(watergirl);
        break;
    case KEY_UP:
        jump(watergirl);
        break;
    case KEY_RIGHT:
        move_right(watergirl);
        break;
    default:
        stop_moving(watergirl);
        break;
    }

    return 0;
}
