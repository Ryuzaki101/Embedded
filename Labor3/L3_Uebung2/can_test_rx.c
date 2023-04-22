/*----------------------------------------------------------------------------
 * Name:    can_test_rx.c
 * Purpose: CAN Module API File for LPC23xx Microcontrollers
 *            (Keil MCB2300 Boards are assumed)
 * Version: Version 1.1 / 13.6.2015 (KBL, HS-Mannheim)
 *----------------------------------------------------------------------------
 * History:
 *          V1.00 Initial Version
 *----------------------------------------------------------------------------*/

#include <LPC23xx.h>                             /* LPC23xx definitions */
#include "emb1_can_labs.h"
#include <stdlib.h>


int main(void)
{
															// Put your code here to perform the following tasks
															// Initialize CAN1 module e.g. Data rate value = 0x3DC002 @ 14,4 MHz 
	CAN_Init( 1, 0x3DC002);
	//CAN_Init( 2, 0x3DC002);
															// Initialize CAN2 module e.g. Data rate value = 0x3DC002 @ 14,4 MHz 
															// Set up the acceptance filtering and test the following options SEQUENTIALLY
															// ACC_OFF, ACC_ON and ACC_OFF
															// SEQUENTIALLY means that the code must be recompiled for each option and
															//	the options shall not be combined.
	CAN_Set_Acceptance_Filter_Mode(ACCF_ON);
															// Please remember the ID values for the option ACC_ON are available or can 
															// be changed in the file CAN_AcceptanceFiltering.h
  
  
  while(1); 									//Data sent by the ini File are received via TX Interrupt

//  return 1;
}


