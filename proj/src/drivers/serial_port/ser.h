#ifndef SER_H
#define SER_H

int line_ctrl_reg_read(uint8_t *info);
int line_ctrl_reg_conf(uint8_t bits, uint8_t stop, uint8_t par_mode);

#endif
