/* inc copyright */

#ifndef INC_AUTO_APP
#define INC_AUTO_APP

#include "stm32f0xx_hal.h"

/**
 * auto generate include headers for app
*/
#include "can.h"
#include "r2d.h"

void init_app(void);
void deinit_app(void);
void task_app();
void cb_app(canbus_msg *msg, CAN_RxHeaderTypeDef *rxHeader);

#endif/* INC_AUTO_APP */
