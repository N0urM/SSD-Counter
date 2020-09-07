/*******************************************************/ 
/* Author: Nourhan Mansour                             */
/* Date  : 21/8/2020                                   */
/* Vesion: 1.0                                         */
/* File  : NVIC_interface.h                            */
/*******************************************************/ 
#ifndef NVIC_INTERFACE_H
#define NVIC_INTERFACE_H

typedef enum {
    WWDG = 0, 
    PVD,
    TAMPER,
    RTC,
    FLASH,
    RCC,
    EXTI0,
    EXTI1,
    EXTI2,
    EXTI3,
    EXTI4,
    DMA1_Channel1,
    DMA1_Channel2,
    DMA1_Channel3,
    DMA1_Channel4,
    DMA1_Channel5,
    DMA1_Channel6,
    DMA1_Channel7,
    ADC1_2,
    USB_HP_CAN_TX,
    USB_LP_CAN_RX,
    CAN_RX1,
    CAN_SCE,
    EXTI9_5,
    TIM1_BRK,
    TIM1_UP,
    TIM1_TRG_COM,
    TIM1_CC,
    TIM2,
    TIM3,
    TIM4,
    I2C1_EV,
    I2C1_ER,
    I2C2_EV,
    I2C2_ER,
    SPI1,
    SPI2,
    USART1,
    USART2,
    USART3,
    EXTI15_10,
    RTCAlarm,
    USBWakeup,
    TIM8_BRK,
    TIM8_UP,
    TIM8_TRG_COM,
    TIM8_CC,
    ADC3,
    FSMC,
    SDIO,
    TIM5,
    SPI3,
    UART4,
    UART5,
    TIM6,
    TIM7,
    DMA2_Channel1,
    DMA2_Channel2,
    DMA2_Channel3,
    DMA2_Channel4_5,

}t_Interrupt_ID;

/**
 * Function: NVIC_voidInitNVIC 
 * Description: Set interrupt groups set based on the groups configutrations in the config file
 * Parameters: No
 * Return: void
 **/
void NVIC_voidInitNVIC ();

/**
 * Function: NVIC_voidEnableInterrupt 
 * Description: Enable interrupt with id  cpy_interrupt_id ONLY 
 *              it doesn't control Prephiral interrupt control or GIE 
 * Parameters: interrupt ID
 * Return: void
 **/
void NVIC_voidEnableInterrupt(t_Interrupt_ID cpy_interrupt_id);

/**
 * Function: NVIC_voidDisableInterrupt 
 * Description: Disable interrupt with id  cpy_interrupt_id ONLY 
 *              it doesn't control Prephiral interrupt control or GIE 
 * Parameters: interrupt ID
 * Return: void
 **/
void NVIC_voidDisableInterrupt(t_Interrupt_ID cpy_interrupt_id);

/**
 * Function: NVIC_voidSetPendingFlag 
 * Description: Set pending interrupt flag with SW. No HW needed 
 * Parameters: interrupt ID
 * Return: void
 **/
void NVIC_voidSetPendingFlag(t_Interrupt_ID cpy_interrupt_id);


/**
 * Function: NVIC_voidClearPendingFlag 
 * Description: Clear pending interrupt flag with SW. No HW needed  
 * Parameters: interrupt ID
 * Return: void
 **/
void NVIC_voidClearPendingFlag(t_Interrupt_ID cpy_interrupt_id);

/**
 * Function: NVIC_u8GetActiveFlag 
 * Description: Read the active flag status of a specific interrupt
 *              Active flag indicate the interrupt is being processed. 
 * Parameters: interrupt ID
 * Return: Active flag statuse 
 *          1: Raised 
 *          0: No active
 **/
u8 NVIC_u8GetActiveFlag(t_Interrupt_ID cpy_interrupt_id);


/**
 * Function: NVIC_voidSetInterruptPiriority 
 * 
 * Description: Dependning on the divion of groups and sub Groups,
 *              Each interrupt take a group piriorty and sub group piriority 
 *              Interrupts within the same group cannot be nested 
 *              Interrupts within the same group which happened simultanusly, 
 *              will be allowed to excute in order of their subgroup piriority 
 *              If two or more interrupts have the same SW piriority, they will be served 
 *              with respect to their HW piriority.
 * 
 * Parameters: interrupt ID , Group ID , Sub Group ID
 * 
 * Note: Values of the Group pitriority and sub piriority mus be consistenet with the Interrupt groups 
 *       specified in the conofig file.
 *  
 * EX:  INTERRUPT_GROUPS = GROUP2_SUB8
 *      cpy_Group_Piriority value: 0 ~ 1
 *      cpy_Sub_piriority value: 0 ~ 7
 * 
 * Return: void
 **/
void NVIC_voidSetInterruptPiriority(t_Interrupt_ID cpy_interrupt_id , u8 cpy_Group_Piriority , u8 cpy_Sub_piriority);

#endif // End Of File