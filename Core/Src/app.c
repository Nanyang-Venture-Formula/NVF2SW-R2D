/* inc copyright */

#include "app.h"
#include "main.h"

/* extern variables */
extern CAN_HandleTypeDef hcan;
canbus_msg msg = {.id=MY_CAN_ID, .dlc=8};

void init_app(void)
{
    init_canhw(&hcan);
    init_r2d();
}

void deinit_app(void)
{
    deinit_r2d();
    deinit_canhw(&hcan);
}

void task_app()
{
    task_canhw(&hcan);
    task_r2d();
}

void cb_app(canbus_msg *rxmsg, CAN_RxHeaderTypeDef *rxHeader)
{
	cb_r2d(rxmsg);
}
