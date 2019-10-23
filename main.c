/*
 * main.c
 *
 *  Created on: Oct 21, 2019
 *      Author: Mina
 */

#include "BCM.h"
#include <util/delay.h>

uint8 arr[15]={'M','u','h','a','m','m','a','d',' ','R','a','a','f','a','t'};

int main(void)
{

	extern BCM_ConfigType BCM_Cfg;
	const BCM_ConfigType * Config_ptr = &BCM_Cfg;
	UART_Init();
	BCM_Init(Config_ptr);
	BCM_send(arr, 19);

	while(1)
	{
		BCM_TX_Dispatcher();
	}
}
