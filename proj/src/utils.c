#include <lcom/lcf.h>
#include <stdint.h>

int (util_get_LSB)(uint16_t val, uint8_t* lsb) {
    if (!lsb) {
        printf("Error in util_get_LSB (nullptr)\n");
        return 1;
    }
    *lsb = (uint8_t)val;
    return 0;
}

int (util_get_MSB)(uint16_t val, uint8_t* msb) {
    if (!msb) {
        printf("Error in util_get_MSB (nullptr)\n");
        return 1;
    }
    *msb = (uint8_t)(val >> 8);
    return 0;
}

int (util_sys_inb)(int port, uint8_t* value) {
    u_int32_t v = (u_int32_t)*value;

    if (sys_inb(port, &v)) {
        printf("Error in sys_inb\n");
        return 1;
    }

    *value = (uint8_t)v;
    return 0;
}
