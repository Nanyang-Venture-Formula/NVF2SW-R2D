/* inc copyright */

#include "r2d.h"

#define R2D_APP 			1
#define R2D_IS_DASH 		1

#if defined(R2D_APP)
#if R2D_IS_DASH
#endif
#if R2D_IS_VCU
#endif

bool R2D_SW_NC;
bool R2D_SW_NO;
bool R2D_BTN_NO;
bool USR_BTN_NO;
bool hasError;
bool R2D_LED_STATE;

R2D_status_t r2d_status;
R2D_report_t r2d_report;

extern CAN_HandleTypeDef hcan;
extern canbus_msg msg;

void init_r2d(void) {}
void deinit_r2d(void) {}

#if R2D_IS_DASH
void cb_r2d(const canbus_msg* msg)
{
	if (msg->data[CAN_DATA_IDX_NETWORK] != CAN_R2DN) return;					/* message not from the right network */
	if (msg->id != CAN_R2DN_VCU) return;										/* message not from VCU */
	
	switch (msg->data[CAN_DATA_IDX_MSGTYPE])
	{
		case CAN_R2DN_VCU_REPORT:
			break;
		default:
			return;
	}
}
#endif
#if R2D_IS_VCU
void cb_r2d(const canbus_msg* msg)
{
	if (msg->data[CAN_DATA_IDX_NETWORK] != CAN_R2DN) return;					/* message not from the right network */
	if (msg->id != CAN_R2DN_DASH) return;										/* message not from DASH */
	
	switch (msg->data[CAN_DATA_IDX_MSGTYPE])
	{
		case CAN_R2DN_DASH_STATUS:
			break;
		default:
			return;
	}
}
#endif

#if R2D_IS_DASH
void task_r2d(void)
{
	_r2d_getStatus(&r2d_status);
	_r2d_status2can(&r2d_status, &msg);
	canhw_send(&hcan, &msg);
	_r2d_task();
}
#endif
#if R2D_IS_VCU
void task_r2d(void)
{
	_r2d_task();
}
#endif

void _r2d_getStatus(R2D_status_t* r2d_status)
{
	R2D_SW_NC = HAL_GPIO_ReadPin(R2D_SW_NC_GPIO_Port, R2D_SW_NC_Pin);
	R2D_SW_NO = HAL_GPIO_ReadPin(R2D_SW_NO_GPIO_Port, R2D_SW_NO_Pin);
	R2D_BTN_NO = HAL_GPIO_ReadPin(R2D_BTN_NO_GPIO_Port, R2D_BTN_NO_Pin);
	USR_BTN_NO = HAL_GPIO_ReadPin(USR_KEY_GPIO_Port, USR_KEY_Pin);

	r2d_status->isUser = USR_BTN_NO;
	hasError = (R2D_SW_NC == R2D_SW_NO);
	r2d_status->hasError = hasError;
	if (hasError)
	{
		r2d_status->isDeactivated = 1;
		r2d_status->isTriggered = 0;
		return;
	}

	//	condition is that NC is closed, NO is open
		r2d_status->isDeactivated = ((hasError) || (!hasError && R2D_SW_NC));

	//	can only be triggered on 1 condition
	//	if is !isDeactivated AND button is pressed.
		r2d_status->isTriggered = (!hasError && !R2D_SW_NC && R2D_SW_NO && !R2D_BTN_NO);

	return;
}

void _r2d_status2can(const R2D_status_t* r2d_status, canbus_msg* msg)
{
	msg->dlc = 8;
	msg->data32[0] = 0x00;
	msg->data32[1] = 0x00;

	msg->data[CAN_DATA_IDX_MSGTYPE] = CAN_R2DN_DASH_STATUS;
	msg->data[0] |= (r2d_status->hasError) * R2D_HAS_ERROR;
	msg->data[0] |= (r2d_status->isTriggered) * R2D_IS_TRIGGERED;
	msg->data[0] |= (r2d_status->isDeactivated) * R2D_IS_DEACTIVATED;
	msg->data[0] |= (r2d_status->isUser) * R2D_USR_TRIG;

	return;
}

void _r2d_can2status(const canbus_msg* msg, R2D_status_t* r2d_status)
{
	if (msg->data[CAN_DATA_IDX_MSGTYPE] != CAN_R2DN_DASH)
	{
		// not from DASH
		return;
	}

	r2d_status->hasError = ((msg->data[0] & R2D_HAS_ERROR) > 0);
	r2d_status->isTriggered = ((msg->data[0] & R2D_IS_TRIGGERED) > 0);
	r2d_status->isDeactivated = ((msg->data[0] & R2D_IS_DEACTIVATED) > 0);

	return;
}

void _r2d_report2can(R2D_report_t* r2d_report, const canbus_msg* msg)
{
	if (msg->data[CAN_DATA_IDX_MSGTYPE] != CAN_R2DN_VCU_REPORT)
	{
		// not from VCU
		return;
	}

	r2d_report->r2dState = msg->data[0];
	return;
}

void _r2d_report2status(const canbus_msg* msg, R2D_report_t* r2d_report)
{
	if (msg->data[CAN_DATA_IDX_MSGTYPE] != CAN_R2DN_VCU)
	{
		// not from DASH
		return;
	}

	r2d_report->r2dState = msg->data[0];
	return;
}

void _r2d_task()
{
	#if R2D_IS_DASH
	_r2d_handle_led();
	#endif
}

void _r2d_handle_led()
{
	// use watchdog
	switch (r2d_report.r2dState)
	{
		case R2D_STATE_READY:
			// flash
			break;
		case R2D_STATE_ACTIVE:
			if (R2D_LED_STATE != 1)
			{
				HAL_GPIO_WritePin(R2D_LED_GPIO_Port, R2D_LED_Pin, 1);
				R2D_LED_STATE = 1;
			}
			break;
		case R2D_STATE_DEACTIVE:
			if (R2D_LED_STATE != 0)
			{
				HAL_GPIO_WritePin(R2D_LED_GPIO_Port, R2D_LED_Pin, 0);
				R2D_LED_STATE = 0;
			}
			break;
	}
}

#endif
