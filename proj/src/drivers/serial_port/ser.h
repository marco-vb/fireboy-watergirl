#ifndef SER_H
#define SER_H

void init_queues();
void clear_queues();
void destroy_queues();
uint8_t receive_queue_pop();
void send_queue_push(uint8_t byte);
bool receive_queue_is_empty();
bool send_queue_is_empty();
uint8_t receive_queue_front();
uint8_t receive_queue_size();
void receive_queue_push(uint8_t data);
int read_byte(uint8_t *data);
int send_byte(uint8_t data);
int send_bytes();
int read_lsr(uint8_t *status);
int write_lcr(uint8_t conf);
int read_lcr(uint8_t *conf);
int ser_conf(uint8_t bits, uint8_t stop, uint8_t par_mode);
int bit_rate_conf(uint32_t bit_rate);
int ser_init();
int ser_subscribe_int(uint8_t* bit_no);
int ser_unsubscribe_int();
int ser_enable_interrupts();
int iir_status_read();
int get_data_errors(int errors[]);
int handle_errors(int errors[]);
void ser_ih();
int check_ih_err();
bool transmitter_ready();
int init_fifos();
int clear_fifos();

#endif
