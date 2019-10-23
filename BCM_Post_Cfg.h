/*
 * BCM_Post_Cfg.h
 *
 *  Created on: Oct 19, 2019
 *      Author: Mina
 */

#ifndef BCM_POST_CFG_H_
#define BCM_POST_CFG_H_

#include "stdtypes.h"


typedef enum {UART, SPI, I2C}BCM_Com_t;
//typedef enum {INTERNAL, EXTERNAL}BCM_ComType_t;

typedef struct
{
	BCM_Com_t communication_type;
	//BCM_ComType_t communication_status;
}BCM_ConfigType ;

typedef struct
{
	uint8 header_id;
	uint8 check_sum_error;
	uint16 data_size;
	uint8 * data_ptr;
} BCM_Buffer_t;

typedef enum
{
	BUFFER_UNLOCKED = -9, NULLPTR, NOK,INVALID_COM_TYPE, OK=1
}EnmBCMError_t;


#endif /* BCM_POST_CFG_H_ */
