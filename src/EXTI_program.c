/*******************************************************/ 
/* Author: Nourhan Mansour                             */
/* Date  : 29/8/2020                                   */
/* Vesion: 1.1                                         */
/* File  : EXTI_program.c                              */
/*******************************************************/ 

// 1- include Libraries 
#include "STD_TYPES.h"
#include "BIT_MATH.h"

// 2- include interface file of needed lower layers

// 3- include driver files
#include "EXTI_interface.h"
#include "EXTI_private.h"
#include "EXTI_config.h"


void EXTI_voidEnableExternalInterrupt (u8 cpy_line  , t_EDGE cpy_Edge_Selection , void (*func)(void) )
{
    /**
     * Configure the mask bits of the 20 Interrupt lines (EXTI_IMR)
    • Configure the Trigger Selection bits of the Interrupt lines (EXTI_RTSR and
        EXTI_FTSR)
    • Configure the enable and mask bits that control the NVIC IRQ channel mapped to the
        External Interrupt Controller (EXTI) so that an interrupt coming from one of the 20 lines
        can be correctly acknowledged
     */
    switch (cpy_Edge_Selection)
    {
    case FALLING_EDGE:
        SET_BIT (EXTI -> FTSR , cpy_line);          // Enable Falling Edge on line cpy_line
        CLR_BIT (EXTI -> RTSR , cpy_line);          // Disable Rising Edge on line cpy_line
        break;
    
    case RISING_EDGE:
        SET_BIT (EXTI -> RTSR , cpy_line);           // Enable Rising Edge on line cpy_line
        CLR_BIT (EXTI -> FTSR , cpy_line);           // Disable Falling Edge on line cpy_line
        break;
    
    case ON_CHANGE:
        SET_BIT (EXTI -> FTSR , cpy_line);           // Enable Falling Edge on line cpy_line
        SET_BIT (EXTI -> RTSR , cpy_line);           // Enable Rising Edge on line cpy_line
        break;
    
    default:
        break;
    }
    SET_BIT(EXTI -> IMR , cpy_line );

    // Assign call back 
    if (cpy_line < 5)
    {
        functionCallBack[cpy_line] = func;
    }
    else if (cpy_line>= 5 && cpy_line <= 9)
    {
        functionCallBack[5] = func;
    }
    else 
    {
        functionCallBack[6] = func;
    }
    
}

void EXTI_voidDisableExternalInterrupt(u8 cpy_line )
{
    /* Clear alll interrupt configurations */
    CLR_BIT (EXTI -> IMR  , cpy_line); 
    CLR_BIT (EXTI -> FTSR , cpy_line);
    CLR_BIT (EXTI -> RTSR , cpy_line);
       
}

void EXTI_voidSetSoftwareInterrupt (u8 cpy_line)
{
    SET_BIT (EXTI->SWIER , cpy_line);
}

void EXTI_voidClearInterruptSignal(u8 cpy_line)
{
    SET_BIT (EXTI->PR , cpy_line);
}

/***** Interrupt handlers *******/

void EXTI0_IRQHandler(void){
    functionCallBack[0]();
}
void EXTI1_IRQHandler(void){
    functionCallBack[1]();
}
void EXTI2_IRQHandler(void){
    functionCallBack[2]();
}
void EXTI3_IRQHandler(void){
    functionCallBack[3]();
}
void EXTI4_IRQHandler(void){
    functionCallBack[4]();
}

void EXTI9_5_IRQHandler(void){
    functionCallBack[5]();
}

void EXTI15_10_IRQHandler(void){
    functionCallBack[6]();
}