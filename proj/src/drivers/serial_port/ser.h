#ifndef SER_H
#define SER_H

int line_ctrl_reg_write(uint8_t conf);
int line_ctrl_reg_read(uint8_t *conf);
int line_ctrl_reg_conf(uint8_t bits, uint8_t stop, uint8_t par_mode);
int bit_rate_conf(uint32_t bit_rate);

#endif
