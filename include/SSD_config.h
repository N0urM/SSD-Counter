/*******************************************************/ 
/* Author: Nourhan Mansour                             */
/* Date  : 16/8/2020                                   */
/* Version: 2.0                                        */
/* File  : SSD_config.h                                */
/*******************************************************/ 
#ifndef     SSD_CONFIG_H
#define     SSD_CONFIG_H


#define COMMON_ANODE_CATHODE	1   	//1: Common Anode & 0: Common Cathode

#define MUX_SSD_NUM 			2		//Maximum used SSD at the same time 4

#define SSD_SELECTION_PORT		PORTA	//values: PORTA, PORTB, PORTC

const u8 SSID_CONTROL_PINS [] = {10 , 11 , NOT_USED , NOT_USED };

#endif  // End Of File
