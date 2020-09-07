
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "NVIC_interface.h"
#include "EXTI_interface.h"
#include "STK_interface.h"

#include "SSD_interface.h"
#include "PB_interface.h"

static u8 k = 0;
void interruptReset();
void interruptCouter();

void main(void)
{
	/* Initialize system Clock */
	RCC_voidInitSystemClock();

	/* Enable AF Clock */
	RCC_voidEnableClock(t_APB2 , RCC_APB2ENR_AFIOEN);

	/* Initialize SYSTICK */
	STK_voidInit();

	/* Init SSD */
	t_SSD ssd;
	ssd.port = PORTA;
	ssd.start_pin = 2;
	ssd.end_pin = 9;
	SSD_voidInit(ssd);

	/* Init Push btns */
	PB_Init(PORTB , PIN0 , PB_PLUS , PB_RELEASED);
	PB_Init(PORTB , PIN1 , PB_RESET , PB_RELEASED);

	GPIO_EnableAFOnPortPin(PORTB , PIN0 , EXTI);
	GPIO_EnableAFOnPortPin(PORTB , PIN1 , EXTI);

	/* 	Enable External Internal interrupts for PSs */
	NVIC_voidInitNVIC();
	NVIC_voidEnableInterrupt(EXTI0);
	NVIC_voidEnableInterrupt(EXTI1);

	EXTI_voidEnableExternalInterrupt(0 , FALLING_EDGE , interruptCouter);
	EXTI_voidEnableExternalInterrupt(1 , FALLING_EDGE , interruptReset );

	while (1)
    {
/**************************************************************/
//		Another approach without using interrupts 
/**************************************************************/
//	  PB_Update();			// Update PB
//
//	  /** Check Status **/
//	  if(PB_GetState(PB_RESET) == PB_PRE_RELEASED ){
//	  	  		k = 0;
//	  }
//	  else if(PB_GetState(PB_PLUS) == PB_PRE_RELEASED ){
//	  		k++;
//	  		if(k > 99 )k=0;
//	  }
//
//	  /** Update SSD **/
//	  SSD_voidSetSSDDigit( 0 , k/10);
//	  SSD_voidSetSSDDigit( 1 , k%10);
//	  SSD_voidUpdateDisplay(ssd);

		SSD_voidUpdateDisplay(ssd);			// Periodic function to update SSD

    }
}


// ----------------------------------------------------------------------------

void interruptCouter(){
	// on press increment counter
	k++;
	if(k>99){
		k=0;

	}
	// Update SSD digits 
	SSD_voidSetSSDDigit( 0 , k/10);
	SSD_voidSetSSDDigit( 1 , k%10);

	// debounce fix 
	STK_voidSetBusyWait(20000);
	
	// Clear interrupt flag 
	EXTI_voidClearInterruptSignal(0);
	NVIC_voidClearPendingFlag(EXTI0);
}

void interruptReset(){
	// On press reset counter
	k = 0;

	// Update SSD digits 
	SSD_voidSetSSDDigit( 0 , 0);
	SSD_voidSetSSDDigit( 1 , 0);
	
	// debounce fix 
	STK_voidSetBusyWait(20000);

	// Clear interrupt flag 
	EXTI_voidClearInterruptSignal(1);
	NVIC_voidClearPendingFlag(EXTI1);

}
