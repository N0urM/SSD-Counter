/*******************************************************/ 
/* Author: Nourhan Mansour                             */
/* Date  : 16/8/2020                                   */
/* Vesion: 2.0                                         */
/* File  : SSD_program.c                               */
/*******************************************************/ 

// 1- include Libraries 
#include "STD_TYPES.h"
#include "BIT_MATH.h"

// 2- include interface file of needed lower layers
#include "GPIO_interface.h"
#include "RCC_interface.h"

// 3- include driver files
#include "SSD_interface.h"
#include "SSD_private.h"
#include "SSD_config.h"

void SSD_voidInit(t_SSD cpy_SSD){

		// Enable Clock for Data pins
    	switch (cpy_SSD.port)
		{
		case PORTA:
			RCC_voidEnableClock(t_APB2, RCC_APB2ENR_IOPAEN);
			break;
		case PORTB:
			RCC_voidEnableClock(t_APB2, RCC_APB2ENR_IOPBEN);
			break;
		case PORTC:
			RCC_voidEnableClock(t_APB2, RCC_APB2ENR_IOPCEN);
			break;
		default:
			break;
		}

        // Enable Clock for Control pins
    	#if SSD_SELECTION_PORT == PORTA
        	RCC_voidEnableClock(t_APB2, RCC_APB2ENR_IOPAEN);
        #elif SSD_SELECTION_PORT == PORTB
        	RCC_voidEnableClock(t_APB2, RCC_APB2ENR_IOPBEN);
        #elif SSD_SELECTION_PORT == PORTC
        	RCC_voidEnableClock(t_APB2, RCC_APB2ENR_IOPCEN);
        #endif

        // initialize O/P configuration for control pins
    	u8 i;
    	for(i=0 ; i< MUX_SSD_NUM ; i++){
    		GPIO_voidInitPortPinDirection(SSD_SELECTION_PORT , SSID_CONTROL_PINS[i]  , OUTPUT_PUSH_PULL_10MHZ);
    	}

    	// initialize O/P configuration for data pins
		for(i=cpy_SSD.start_pin ; i <= cpy_SSD.end_pin ; i++)
		{
			GPIO_voidInitPortPinDirection(cpy_SSD.port, i , OUTPUT_PUSH_PULL_10MHZ);
		}
}


void SSD_voidUpdateDisplay (t_SSD cpy_SSD)
{
	// Time Slice for each SSD
	u8 i =0;
	while(i < MUX_SSD_NUM)
	{
		u8 toDisplay = number[SSD_digit[i]];
		// Neutralize control pins on all SSDs
		#if COMMON_ANODE_CATHODE == 1
			toDisplay = ~ toDisplay ;
			u8 j = 0;
			while(j<MUX_SSD_NUM){
				GPIO_voidSetPortPinValue(SSD_SELECTION_PORT, SSID_CONTROL_PINS[j] , 0 );
				j++;
			}

		#else
			u8 j = 0 ;
			while(j< MUX_SSD_NUM){
				GPIO_voidSetPortPinValue(SSD_SELECTION_PORT, SSID_CONTROL_PINS[j] , 1 );
				j++;
			}

		#endif

		// Send data on BUS
		u8 cnt = 0 , shift=0;
		for(cnt = cpy_SSD.start_pin ; cnt <= cpy_SSD.end_pin ; cnt++)
		{
			GPIO_voidSetPortPinValue(cpy_SSD.port, cnt , (toDisplay >> shift) & 0x01 );
			shift++;
		}
		#if COMMON_ANODE_CATHODE == 1
			GPIO_voidSetPortPinValue(SSD_SELECTION_PORT, SSID_CONTROL_PINS[i] , 1 );
		#else
			GPIO_voidSetPortPinValue(SSD_SELECTION_PORT, SSID_CONTROL_PINS[i] , 0 );
		#endif

		delay_ms(2);
		i++;
	}
}

void SSD_voidSetSSDDigit(u8 SSID_IDX , u8 digit){
	SSD_digit[SSID_IDX] = digit;
}

void delay_ms(u32 ms)
{
 u32 i;

 for(i = 0; i < (SystemCoreClock/(12000)) * ms; i++){
  __asm ("NOP");
 }
}
