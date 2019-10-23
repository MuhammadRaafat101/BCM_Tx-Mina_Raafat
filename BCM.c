/*
 * BCM.c
 *
 *  Created on: Oct 19, 2019
 *      Author: Mina
 */

#include "BCM.h"
#include "LCD.h"
char check[10];
uint8  TX_Buffer_Status_Flag;
//volatile static uint16 ISR_TX_flag = INITIAL;
volatile static uint16 Dispatcher_TX_flag = INITIAL;
uint8 check_sum_flag;
static uint8 guard_flag=1;
BCM_Buffer_t BCM_Structure;
BCM_ConfigType BCM_Config;
BCM_Buffer_t * BufferPtr = &BCM_Structure;

EnmBCMError_t BCM_Init(const BCM_ConfigType *ConfigPtr)
{
	EnmBCMError_t retval;
	if (NULL == ConfigPtr)
	{
		retval = NULLPTR;
	}
	else
	{
		switch (ConfigPtr->communication_type)
		{
		case UART:
			UART_Init();
			LCD_init();
			retval = OK;
			break;
		case SPI:
			/* To call the spi function init*/
			retval = OK;
			break;
		case I2C:
			/* to call the i2c init function*/
			retval = OK;
			break;
		default:
			retval = INVALID_COM_TYPE;
			break;
		}
	}
	sei();
	return retval;
}
EnmBCMError_t BCM_DeInit(void)
{
	EnmBCMError_t retval = OK;
	UART_DeInit();
	return retval;
}
void BCM_send (uint8* data_ptr, uint16 Bytes_Num)
{
	/* In this function, we construct the frame by initializing every element in the structure used
	 * Then we lock buffer to make sure that no one corrupts the data which will be sent.*/
	BCM_Structure.header_id = UART_ID;
	BCM_Structure.check_sum_error = INITIAL;
	BCM_Structure.data_size = Bytes_Num;
	BCM_Structure.data_ptr = data_ptr;
	TX_Buffer_Status_Flag = LOCKED;
}

EnmBCMError_t BCM_TX_Dispatcher(void)
{
	static uint32 counter = 0;
	EnmBCMError_t retval;
	if(1 == guard_flag && TX_Buffer_Status_Flag == LOCKED)
	{
		guard_flag = 0;
		switch (Dispatcher_TX_flag)
		{
		case 0:
			//UART_Send('M');
			UART_Send(BufferPtr ->header_id);
			//LCD_gotoRawCol(0,0);
			//LCD_IntToStr(BufferPtr ->header_id);
			Dispatcher_TX_flag++;

			break;
		case 1:
			//UART_Send('1');
			UART_Send(BufferPtr -> data_size);
			uint8 temp = BufferPtr -> data_size;
			uint16 data = (temp) <<8;
			UART_Send(data);
			Dispatcher_TX_flag++;
			break;

		case 2:
			if (counter < BCM_Structure.data_size-2)
			{
				UART_Send(*(BufferPtr -> data_ptr + counter));
				LCD_displayChar(BufferPtr -> data_ptr[counter]);
				check_sum_flag+= BufferPtr -> data_ptr[counter];
				counter++;
			}else if(counter == BCM_Structure.data_size-2)
			{
				guard_flag=1;
				Dispatcher_TX_flag++;

				PORTC^=1<<0;
			}
			break;
		case 3 :
			//UART_Send(Dispatcher_TX_flag+48);
			UART_Send(check_sum_flag);
			LCD_gotoRawCol(1,0);

			LCD_IntToStr(check_sum_flag);
			BCM_Structure.check_sum_error = check_sum_flag;
			TX_Buffer_Status_Flag = UNLOCKED;
			Dispatcher_TX_flag=0;
			break;
		}
	}
	return retval;
}

ISR(USART_TXC_vect)
{

	guard_flag=1;

}
