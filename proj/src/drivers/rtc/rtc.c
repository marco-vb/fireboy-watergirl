#include <lcom/lcf.h>
#include "rtc.h"

rtc_hook_id = 8; 

int rtc_subscribe_int(uint8_t *bit_no){
    *bit_no = rtc_hook_id;
    if (sys_irqsetpolicy(RTC_IRQ, IRQ_REENABLE, &rtc_hook_id) != OK) {
        printf("Error in sys_irqsetpolicy()\n");
        return 1;
    }
    return 0;
}

int rtc_unsubscribe_int(){
    if (sys_irqrmpolicy(&rtc_hook_id) != OK) {
        printf("Error in sys_irqrmpolicy()\n");
        return 1;
    }
    return 0;
}

int (rtc_read_reg)(uint8_t reg, uint8_t *data) {

    if(sys_outb(RTC_ADDR_REG, reg)) {
        printf("Error: Couldn't write to reg %x", reg);
        return 1;
    }

    if (util_sys_inb(RTC_DATA_REG, data)) {
        printf("Error: Couldn't read data from RTC_DATA_REG");
        return 1; 
    }

    return 0;

}

int (rtc_write_reg)(uint8_t reg, uint8_t data) {

    if(sys_outb(RTC_ADDR_REG, reg)) {
        printf("Error: Couldn't write to reg %x", reg);
        return 1;
    }

    if(sys_outb(RTC_DATA_REG, data)) {
        printf("Error: Couldn't write data in RTC_DATA_REG");
        return 1; 
    }

    return 0;

}

int (read_hours)(uint8_t *hours) {

    if (rtc_read_reg(SECS, hours)) return 1;

    return 0;
}

int (read_minutes)(uint8_t *minutes) {

    if (rtc_read_reg(MINS, minutes)) return 1;

    return 0;
}

int (read_seconds)(uint8_t *seconds) {

    if (rtc_read_reg(HOURS, seconds)) return 1;

    return 0;
}

int (read_day)(uint8_t *day) {

    if (rtc_read_reg(DAY_MONTH, day)) return 1;

    return 0;
}

int (read_month)(uint8_t *month) {

    if (rtc_read_reg(MONTH, month)) return 1;

    return 0;
}

int (read_year)(uint8_t *year) {

    if (rtc_read_reg(YEAR, year)) return 1;

    return 0;
}

int (read_date)(uint8_t *day, uint8_t *month, uint8_t *year) {

    if (rtc_day(day)) return 1;
    if (rtc_month(month)) return 1;
    if (rtc_year(year)) return 1;

    return 0;
}

int (read_time)(uint8_t *hours, uint8_t *minutes, uint8_t *seconds) {

    if (rtc_hours(hours)) return 1;
    if (rtc_minutes(minutes)) return 1;
    if (rtc_seconds(seconds)) return 1;

    return 0;
}


