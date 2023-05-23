#ifndef __GRAPHICS_H
#define __GRAPHICS_H

#include <lcom/lcf.h>

#define VBE_VID_INT 0x10

#define VBE_MODE_INFO 0x4F01
#define VBE_SET_MODE 0x4F02
#define VBE_GET_MODE 0x4F03
#define VBE_MODE_SUPPORTED 0x4F00
#define VBE_FUNCTION 0x4F

#define VBE_VIDEO_MODE_ID 0x0105
#define VBE_VIDEO_MODE_DC 0x014c

#define SET_VBE_MODE 0x4F02
#define BIOS_SET_MODE 0x00
#define TEXT_MODE 0x03

#define VBE_LINEAR_BUFFER BIT(14)

#define VBE_MODE_GRAPHICS BIT(10)
#define VBE_MODE_COLOR BIT(8)

int (video_set_mode)(uint16_t mode);
int (video_mode)();
int (text_mode)();
int (map_memory)(uint16_t mode);
void (video_draw_pixel)(uint16_t x, uint16_t y, uint32_t color);
uint16_t(get_hres)();
uint16_t(get_vres)();
int(clear_buffer)();
int (draw_buffer)();
#endif /* __GRAPHICS_H */
