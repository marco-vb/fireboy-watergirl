#ifndef __RTC_H__
#define __RTC_H__

/**
 * @defgroup rtc rtc
 * @ingroup drivers
 * 
 * @brief Real Time Clock driver
 * 
 * @{
*/


#include <stdint.h>
#include "../graphics/graphics.h"

#define RTC_IRQ 8 /* @brief RTC IRQ Line on IRQ0 from PIC2*/
#define RTC_ADDR_REG 0x70
#define RTC_DATA_REG 0x71

#define SECS 0X00 /* @brief Seconds register */
#define SECS_ALARM 0X01 /* @brief Seconds alarm register */
#define MINS 0X02 /* @brief Minutes register */
#define MINS_ALARM 0X03 /* @brief Minutes alarm register */
#define HOURS 0X04 /* @brief Hours register */
#define HOURS_ALARM 0X05 /* @brief Hours alarm register */
#define DAY_WEEK 0X06 /* @brief Day of the week register */
#define DAY_MONTH 0X07 /* @brief Day of the month register */
#define MONTH 0X08 /* @brief Month register */
#define YEAR 0X09 /* @brief Year register */


//Register A (10)

#define REG_A 0x0A /* @brief Register A address */

#define UIP BIT(7) /* @brief BIT for Update in progress */ 
#define DV2 BIT(6) /* @brief BIT for Divisor 2 */
#define DV1 BIT(5) /* @brief BIT for Divisor 1 */
#define DV0 BIT(4) /* @brief BIT for Divisor 0 */
#define RS3 BIT(3) /* @brief BIT for Rate selector 3 */
#define RS2 BIT(2) /* @brief BIT for Rate selector 2 */
#define RS1 BIT(1) /* @brief BIT for Rate selector 1 */
#define RS0 BIT(0) /* @brief BIT for Rate selector 0 */

//Register B (11)

#define REG_B 0x0B /* @brief Register B address */

#define SET BIT(7) /* @brief BIT for Set to inhibit updates */
#define PIE BIT(6) /* @brief BIT for Periodic interrupt enable */
#define AIE BIT(5) /* @brief BIT for Alarm interrupt enable */
#define UIE BIT(4) /* @brief BIT for Update interrupt enable */
#define SQWE BIT(3) /* @brief BIT for Square wave enable */
#define DM BIT(2) /* @brief BIT for Data mode (1 - Binary, 0 - BCD)*/ 
#define HR BIT(1) /* @brief BIT for Set to 24h mode */
#define DSE BIT(0) /* @brief BIT for Daylight savings enable */


//Register C (12)

#define REG_C 0x0C /* @brief Register C address */

#define IRQF BIT(7) /* @brief BIT for IRQ active */
#define PF BIT(6) /* @brief BIT for Periodic interrupt pending */
#define AF BIT(5) /* @brief BIT for Alarm interrupt pending */
#define UF BIT(4) /* @brief BIT for Update interrupt pending */


//Register D (13)

#define REG_D 0x0D /* @brief Register D address */

#define VRT BIT(7) /* @brief BIT for Valid RAM/time */

int (rtc_init)();

int (rtc_subscribe_int)(uint8_t *bit_no);

int (rtc_unsubscribe_int)();

int (rtc_read_reg)(uint8_t reg, uint8_t *data);

int (rtc_write_reg)(uint8_t reg, uint8_t data);

int (read_hours)(uint8_t *hours);

int (read_minutes)(uint8_t *minutes);

int (read_seconds)(uint8_t *seconds);

int (read_day)(uint8_t *day);

int (read_month)(uint8_t *month);

int (read_year)(uint8_t *year);

int (read_date)(uint8_t *day, uint8_t *month, uint8_t *year);

int (read_time)(uint8_t *hours, uint8_t *minutes, uint8_t *seconds);

int (draw_time)();

int (draw_date)();


/**
 * @} 
*/


#endif // __RTC_H__
