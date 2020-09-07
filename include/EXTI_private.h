/*******************************************************/ 
/* Author: Nourhan Mansour                             */
/* Date  : 29/8/2020                                   */
/* Vesion: 1.1                                         */
/* File  : EXTI_private.h                              */
/*******************************************************/ 
#ifndef EXTI_PRIVATE_H
#define EXTI_PRIVATE_H

/**************** Registers Definition ****************/

typedef struct 
{
    volatile u32 IMR;
    volatile u32 EMR;
    volatile u32 RTSR;
    volatile u32 FTSR;
    volatile u32 SWIER;
    volatile u32 PR;

}t_EXTI;

#define EXTI_BASE_ADDRESS    0x40010400 
#define EXTI                 ((t_EXTI *) EXTI_BASE_ADDRESS)


// Interupt Functions Call back 
void (*functionCallBack[7])(void) ;

#endif // End Of File