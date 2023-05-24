#include "sprite.h"

Sprite* create_sprite(xpm_map_t pic, uint16_t x, uint16_t y) {
    Sprite* sp = (Sprite*)malloc(sizeof(Sprite));

    if (sp == NULL) return NULL;

    xpm_image_t img;
    uint32_t* colormap = (uint32_t*)xpm_load(pic, XPM_8_8_8_8, &img);

    if (colormap == NULL) {
        free(sp);
        return NULL;
    }

    sp->x = x;
    sp->y = y;
    sp->width = img.width;
    sp->height = img.height;
    sp->map = colormap;

    return sp;
}

int load_sprites() {
    background = create_sprite((xpm_map_t)background_xpm, 0, 0);
    cursor = create_sprite((xpm_map_t)cursor_xpm, 0, 0);
    logo = create_sprite((xpm_map_t)logo_xpm, 0, 100);
    single_player_text = create_sprite((xpm_map_t)single_player_xpm, 420, 400);
    single_player_texth = create_sprite((xpm_map_t)single_playerh_xpm, 430, 400);
    coop_text = create_sprite((xpm_map_t)coop_xpm, 490, 470);
    coop_texth = create_sprite((xpm_map_t)cooph_xpm, 490, 470);
    exit_text = create_sprite((xpm_map_t)exit_xpm, 500, 560);
    exit_texth = create_sprite((xpm_map_t)exith_xpm, 500, 560);
    fireboy = create_sprite((xpm_map_t)fireboy_xpm, 300, 400);
    watergirl = create_sprite((xpm_map_t)watergirl_xpm, 500, 400);

    return 0;
}

int destroy_sprite(Sprite* sp) {
    if (!sp) return 1;

    if (sp->map) free(sp->map);

    free(sp);
    return 0;
}

int draw_sprite(Sprite* sp) {
    if (!sp) return 1;

    for (int h = 0; h < sp->height; h++) {
        for (int w = 0; w < sp->width; w++) {
            uint32_t pixel = sp->map[h * sp->width + w];
            if (pixel == xpm_transparency_color(XPM_8_8_8_8)) continue;
            video_draw_pixel(sp->x + w, sp->y + h, pixel);
        }
    }

    return 0;
}

int erase_sprite(Sprite* sp) {
    if (!sp) return 1;

    for (int h = 0; h < sp->height; h++) {
        for (int w = 0; w < sp->width; w++) {
            uint32_t pixel = sp->map[h * sp->width + w];
            if (pixel == xpm_transparency_color(XPM_8_8_8_8)) continue;
            replace_with_background(sp->x + w, sp->y + h);
        }
    }

    return 0;
}
