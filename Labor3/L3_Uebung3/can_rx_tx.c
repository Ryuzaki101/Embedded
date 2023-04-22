/*----------------------------------------------------------------------------
 * Name:    can_rx_tx.c
 * Purpose: TX Testbench for CAN Module of LPC23xx Microcontrollers
 *            (Keil MCB2300 Boards are assumed)
 * Version: Version 1.1 / 13.6.2015 (KBL, HS-Mannheim)
 *
 *----------------------------------------------------------------------------
 * History:
 *          V1.10 Initial Version
 *----------------------------------------------------------------------------*/

#include <LPC23xx.H>                             /* LPC23xx definitions */
#include "emb1_can_labs.h"

	
CAN_MSG   message1 = {0x333, {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88}, 8, 0,0};
CAN_MSG   My_CAN1_RX_message;
CAN_MSG   My_CAN2_RX_message;

extern uint32_t CAN1_Counter_RX, CAN2_Counter_RX;
//ISRs stored receved messages temporarily in this vector before being read by the application
//Software
extern CAN_MSG  CAN1_RX_messages[CAN1_MAX_RX_MSG], CAN2_RX_messages[CAN2_MAX_RX_MSG];


int main(void)
{
	int i;
														// Put your code here to perform the following tasks
														// Initialize CAN1 module e.g. Data rate value = 0x3DC002 @ 14,4 MHz 
	CAN_Init( 1, 0x3DC002);
														// Initialize CAN2 module e.g. Data rate value = 0x3DC002 @ 14,4 MHz 
	CAN_Init( 2, 0x3DC002);
														// Set up the acceptance filtering and test the following options SEQUENTIALLY
														// ACC_OFF, ACC_ON and ACC_OFF
														// SEQUENTIALLY means that the code must be recompiled for each option and
														// the options shall not be combined.
														// Please remember the ID values for the option ACC_ON are available or can 
														// be changed in the file CAN_AcceptanceFiltering.h
	CAN_Set_Acceptance_Filter_Mode(ACCF_ON);

	while(1){
     CAN_Send_Message(1, &message1);  //CAN frame has been sent  1=CAN1    2=CAN2
		 for (i=0; i < 100000; i++);
		 if ( CAN1_Counter_RX > 0){
			     //Read the last received message
		       My_CAN1_RX_message.id = CAN1_RX_messages[CAN1_Counter_RX-1].id;
			     My_CAN1_RX_message.length = CAN1_RX_messages[CAN1_Counter_RX-1].length;
			     My_CAN1_RX_message.frame_type = CAN1_RX_messages[CAN1_Counter_RX-1].frame_type;
			     My_CAN1_RX_message.data[0] = CAN1_RX_messages[CAN1_Counter_RX-1].data[0];
			     My_CAN1_RX_message.data[1] = CAN1_RX_messages[CAN1_Counter_RX-1].data[1];
			     My_CAN1_RX_message.data[2] = CAN1_RX_messages[CAN1_Counter_RX-1].data[2];
			     My_CAN1_RX_message.data[3] = CAN1_RX_messages[CAN1_Counter_RX-1].data[3];
			     My_CAN1_RX_message.data[4] = CAN1_RX_messages[CAN1_Counter_RX-1].data[4];
			     My_CAN1_RX_message.data[5] = CAN1_RX_messages[CAN1_Counter_RX-1].data[5];
			     My_CAN1_RX_message.data[6] = CAN1_RX_messages[CAN1_Counter_RX-1].data[6];
			     My_CAN1_RX_message.data[7] = CAN1_RX_messages[CAN1_Counter_RX-1].data[7];			 
			     CAN1_Counter_RX = 0;
		 }
		 		 if ( CAN2_Counter_RX > 0){
			     //Read the last received message
		       My_CAN2_RX_message.id = CAN1_RX_messages[CAN2_Counter_RX-1].id;
			     My_CAN2_RX_message.length = CAN1_RX_messages[CAN2_Counter_RX-1].length;
			     My_CAN2_RX_message.frame_type = CAN1_RX_messages[CAN2_Counter_RX-1].frame_type;
			     My_CAN2_RX_message.data[0] = CAN1_RX_messages[CAN2_Counter_RX-1].data[0];
			     My_CAN2_RX_message.data[1] = CAN1_RX_messages[CAN2_Counter_RX-1].data[1];
			     My_CAN2_RX_message.data[2] = CAN1_RX_messages[CAN2_Counter_RX-1].data[2];
			     My_CAN2_RX_message.data[3] = CAN1_RX_messages[CAN2_Counter_RX-1].data[3];
			     My_CAN2_RX_message.data[4] = CAN1_RX_messages[CAN2_Counter_RX-1].data[4];
			     My_CAN2_RX_message.data[5] = CAN1_RX_messages[CAN2_Counter_RX-1].data[5];
			     My_CAN2_RX_message.data[6] = CAN1_RX_messages[CAN2_Counter_RX-1].data[6];
			     My_CAN2_RX_message.data[7] = CAN1_RX_messages[CAN2_Counter_RX-1].data[7];			 
			     CAN2_Counter_RX = 0;
		 }

	}	
  
 
//  return 1;
}


