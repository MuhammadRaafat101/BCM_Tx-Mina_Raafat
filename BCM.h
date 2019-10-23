/*
 * BCM.h
 *
 *  Created on: Oct 19, 2019
 *      Author: Mina
 */

#ifndef BCM_H_
#define BCM_H_

#include "stdtypes.h"
#include "UART.h"
#include <stdlib.h>
#include <stdio.h>
#include "BCM_Post_Cfg.h"
#include "BCM_Pre_Cfg.h"
#include <avr/interrupt.h>


#define INITIAL			0
#define LOCKED			0
#define UNLOCKED		1
#define UART_ID			'A'
#define MAX_DATA_SEND	1000
#define OVERHEAD		4
#define MAX_DATA_RECEIVED	(MAX_DATA_SEND+OVERHEAD)


EnmBCMError_t BCM_Init (const BCM_ConfigType * ConfigPtr);
EnmBCMError_t BCM_DeInit(void);
void BCM_send (uint8 * data_ptr, uint16 Bytes_Num);
EnmBCMError_t BCM_TX_Dispatcher(void);
void BCM_RX_Dispatcher(void);
void Setup_RX_Buffer(uint8 * Buffer_Address, uint16 Buffer_Length);

#endif /* BCM_H_ */
