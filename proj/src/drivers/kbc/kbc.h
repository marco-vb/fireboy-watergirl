#ifndef __KBC_H
#define __KBC_H

#include <stdint.h>

#include "i8042.h"

/* Functions of KBC, common to keyboard and mouse */

int (kbc_get_status)(uint8_t* st);
int (kbc_read_data)(uint8_t* data);
int (kbc_write)(uint8_t port, uint8_t data);
int (kbc_write_cmd)(uint8_t cmd);
int (kbc_write_arg)(uint8_t arg);
int (obf_full)();
int (ibf_empty)();
int (buffer_full)(uint8_t flag);

#endif /* __KBC_H */