#include <lcom/lcf.h>
#include "rtc.h"

int rtc_hook_id = 8; 
xpm_map_t numberssprite[10]={(xpm_map_t)n0_xpm,(xpm_map_t)n1_xpm,(xpm_map_t)n2_xpm,(xpm_map_t)n3_xpm,(xpm_map_t)n4_xpm,(xpm_map_t)n5_xpm,(xpm_map_t)n6_xpm,(xpm_map_t)n7_xpm,(xpm_map_t)n8_xpm,(xpm_map_t)n9_xpm};


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

    if (read_day(day)) return 1;
    if (read_month(month)) return 1;
    if (read_year(year)) return 1;

    return 0;
}

int (read_time)(uint8_t *hours, uint8_t *minutes, uint8_t *seconds) {

    if (read_hours(hours)) return 1;
    if (read_minutes(minutes)) return 1;
    if (read_seconds(seconds)) return 1;

    return 0;
}

int (draw_time)() {
    
    uint8_t hours, minutes, seconds;
    if (read_time(&hours, &minutes, &seconds)) return 1;

    uint8_t h1 = hours / 10;
    uint8_t h2 = hours % 10;

    uint8_t m1 = minutes / 10;
    uint8_t m2 = minutes % 10;

    uint8_t s1 = seconds / 10;
    uint8_t s2 = seconds % 10;

    if (draw_number(918, 0, h1)) return 1;
    if (draw_number((918+30), 0, h2)) return 1;
    if (draw_number((918+90), 0, m1)) return 1;
    if (draw_number((918+120), 0, m2)) return 1;
    if (draw_number((918+180), 0, s1)) return 1;
    if (draw_number((918+210), 0, s2)) return 1;

    return 0;

}



