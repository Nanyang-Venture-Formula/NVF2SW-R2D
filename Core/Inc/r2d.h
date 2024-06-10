/* inc copyright */

#ifndef INC_R2D
#define INC_R2D

#include "stm32f0xx_hal.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "main.h"
#include "canbus.h"
#include "can.h"
#include "nvf_canid.h"

/**
 * #ref R2D_MASK
*/
#define R2D_HAS_ERROR 			(1 << 0)
#define R2D_IS_TRIGGERED 		(1 << 1)
#define R2D_IS_DEACTIVATED 		(1 << 2)
#define R2D_USR_TRIG			(1 << 3)

/**
 * @ref R2D_STATE
*/
#define R2D_STATE_DEACTIVE		000000000U
#define R2D_STATE_READY			000000001U
#define R2D_STATE_ACTIVE		000000002U

typedef struct _R2D_status_t
{
	bool hasError;
	bool isTriggered;
	bool isDeactivated;
	bool isUser;
} R2D_status_t;

typedef struct _R2D_report_t
{
	uint8_t r2dState;		/* @ref R2D_STATE */
} R2D_report_t;

void init_r2d(void);
void deinit_r2d(void);
void cb_r2d(const canbus_msg* msg);
void task_r2d(void);
void _r2d_getStatus(R2D_status_t* r2d_status);
void _r2d_status2can(const R2D_status_t* r2d_status, canbus_msg* msg);
void _r2d_can2status(const canbus_msg* msg, R2D_status_t* r2d_status);
void _r2d_report2can(R2D_report_t* r2d_report, const canbus_msg* msg);
void _r2d_report2status(const canbus_msg* msg, R2D_report_t* r2d_report);
void _r2d_task();
void _r2d_handle_led();

#endif/* INC_R2D */
