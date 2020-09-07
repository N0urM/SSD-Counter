/******************************************************/ 
/* Author: Nourhan Mansour                            */
/* Date  : 16/8/2020                                  */
/* Version: 2.0                                       */
/* File  : SSD_private.h                              */
/******************************************************/ 
#ifndef     SSD_PRIVATE_H
#define     SSD_PRIVATE_H

#define SystemCoreClock 	8000000
#define NOT_USED			'n'

const u8 number[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
u8 SSD_digit[4]   = {0 , 0 , 0 , 0};

void delay_ms(u32 ms);



#endif //End Of File
