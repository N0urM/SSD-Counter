/*******************************************************/ 
/* Author: Nourhan Mansour                             */
/* Date  : 16/8/2020                                   */
/* Version: 2.0                                        */
/* File  : SSD_interface.h                             */
/*******************************************************/ 
#ifndef     SSD_INTERFACE_H
#define     SSD_INTERFACE_H


/************************ public dataTypes *************************/

/*
 * Define Wiring Scheme for SSD
 * Warning: Pins must be continuous on the same port
 */
typedef struct
{
    t_PORT port; 
    t_PIN start_pin;
    t_PIN end_pin; 

}t_SSD;


/*********************** public functions *************************/

/*
 *  Function: SSD_voidInit
 *  Parameters: Struct of the wiring scheme
 *  Description: Initialize GPIO pins and Clock
 *  No Return
 *
 */

void SSD_voidInit(t_SSD cpy_SSD);

/*
 *  Function: SSD_voidUpdateDisplay
 *  Parameters: Struct of the wiring scheme
 *  Description: Does the multiplexing between one or more SSDs
 *  			 MAX : 4 SSDs
 *  No Return
 *
 */
void SSD_voidUpdateDisplay (t_SSD cpy_SSD);

/*
 *  Function: SSD_voidSetSSDDigit
 *  Parameters: SSD_IDX: index of the SSD to assign a digit 0~3
 *  			digit  : digit to display on the selected SSD
 *  Description: Stores a digit to display
 *  No Return
 *
 */

void SSD_voidSetSSDDigit(u8 SSD_IDX , u8 digit);

/***************************************************************/

void delay_ms(u32 ms);

#endif // End Of File
