#include <lcom/lcf.h>
#include "ser.h"
#include "uart.h"

static int hook_ser = 3;
static int ih_err = 0;
bool ready_to_send = false; // temp variable while queue isn't implemented 

int check_ih_err() {
    int temp = ih_err;
    ih_err = 0;
    return temp;
}

int ser_subscribe_int(uint8_t* bit_no) {
    *bit_no = BIT(hook_ser);

    if (sys_irqsetpolicy(SER_COM1_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_ser)) {
        printf("Error while subscribing to interrupts from serial port\n");
        return 1;
    }

    return 0;
}

int ser_unsubscribe_int() {
    if (sys_irqrmpolicy(&hook_ser)) {
        printf("Error while unsubscribing to interrupts from serial port\n");
        return 1;
    }

    return 0;
}

int ser_enable_interrupts() {
    uint8_t interrupts = SER_DATA_RECEIVE_INT | SER_RECEIVER_ERR_INT | SER_EMPTY_TRANSMIT_INT;

    printf("Interrupts: %x", interrupts);

    if (sys_outb(SER_IER, interrupts)) {
        printf("Error while enabling serial port's interrupts\n");
        return 1;
    }

    return 0;
}

int read_lcr(uint8_t *conf) {
    if (util_sys_inb(SER_LCR, conf)) {
        printf("Error while reading from LCR\n");
        return 1;
    }

    return 0;
}

int write_lcr(uint8_t conf) {
    if (sys_outb(SER_LCR, conf)) {
        printf("Error while writing to LCR\n");
        return 1;
    }

    return 0;
}

int ser_conf(uint8_t bits, uint8_t stop, uint8_t par_mode) {
    uint8_t conf = BIT(3);

    if (bits < 5 || bits > 8) {
        printf("Invalid number of bits (5-8)\n");
        return 1;
    }

    if (stop < 1 || stop > 2) {
        printf("Invalid number of stop bits (1-2)\n");
        return 1;
    }

    if (par_mode > 4 || par_mode < 1) {
        printf("Invalid parity mode (1-4)\n");
        return 1;
    }

    conf |= bits - 5;

    conf |= ((stop - 1) << 2);

    if (par_mode % 2 == 0)
        conf |= BIT(4);
    if (par_mode > 2)
        conf |= BIT(5);

    if (write_lcr(conf))
        return 1;

    return 0;
}

int bit_rate_conf(uint32_t bit_rate) {
    uint8_t ser_conf, lsb, msb;
    uint16_t val = 115200/bit_rate;

    if (read_lcr(&ser_conf))
        return 1;
    
    ser_conf |= LCR_DLAB;

    if (write_lcr(ser_conf))
        return 1;
    
    if (util_get_LSB(val, &lsb))
        return 1;
    
    if (util_get_MSB(val, &msb))
        return 1;
    
    if (sys_outb(SER_DLL, lsb)){
        printf("Error while writing to DLL\n");
        return 1;
    }
    
    if (sys_outb(SER_DLM, msb)){
        printf("Error while writing to DLM\n");
        return 1;
    }

    ser_conf &= ~LCR_DLAB;

    if (write_lcr(ser_conf))
        return 1;
    
    return 0;
}

int iir_status_read(uint8_t *irr_status) {
    if (util_sys_inb(SER_IIR, irr_status)) {
        printf("Error while reading interrupt identification register\n");
        return 1;
    }

    return 0;
}

int read_lsr(uint8_t *status) {
    if (util_sys_inb(SER_LSR, status)) {
        printf("Error while reading from line status register\n");
        return 1;
    }

    return 0;
}

int get_data_errors(int errors[]) {
    uint8_t status;
    uint8_t mask = BIT(1);

    if (read_lsr(&status))
        return 1;
    
    for (int i = 0; i < 4; mask <<= 1, i++) {
        if (status & mask)
            errors[i] = 1;
    }

    return 0;
}

int handle_errors(int errors[]) {
    // TODO: Actually handle the errors when the simple communication is done.

    for (int i = 0; i < 4; i++) {
        printf("Error %d\n", i);
    }

    return 0;
}

int read_char(uint8_t *data) {
    uint8_t conf;

    if (read_lcr(&conf))
        return 1;
    
    if (conf & LCR_DLAB)
        conf = conf & ~LCR_DLAB;

    if (write_lcr(conf))
        return 1;

    if (util_sys_inb(SER_RHR, data))
        return 1;

    return 0;
}

int write_char(uint8_t data) {
    uint8_t conf;

    if (read_lcr(&conf))
        return 1;
    
    if (conf & LCR_DLAB)
        conf = conf & ~LCR_DLAB;

    if (write_lcr(conf))
        return 1;

    if (sys_outb(SER_THR, data))
        return 1;

    // TODO: REMOVE THIS AFTER QUEUE IMPLEMENTATION!!!!
    ready_to_send = false;

    return 0;
}

void ser_ih() {
    uint8_t iir_status, int_orig = 0;

    if (iir_status_read(&iir_status)) {
        ih_err = 1;
    }

    int_orig = (iir_status & INT_ORIGIN_MASK) >> 1;
    
    switch(int_orig) {
        case IIR_DATA_ERR: {
            // Ask if there can be more than one error at the same time
            printf("lalau2\n");
            int errors[4] = {0, 0, 0, 0};
            if (get_data_errors(errors)) {
                ih_err = 1;
                break;
            }
            handle_errors(errors);
            break;
        }
        case IIR_DATA_RECEIVED: {
            uint8_t data;
            read_char(&data);
            break;
        }
        case IIR_CHAR_TIMEOUT:{
            uint8_t data;
            read_char(&data);
            break;
        }
        case IIR_TRANSMIT_EMPTY:
            ready_to_send = false;
            break;
    }
}
