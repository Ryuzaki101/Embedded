/*----------------------------------------------------------------------------
 * Name:    kis_can_versuch.c
 * Purpose: CAN Module API File for LPC23xx Microcontrollers
 *            (Keil MCB2300 Boards are assumed)
 * Version: Version 1.0 / 27.4.2012 (KBL, HS-Mannheim)
 *----------------------------------------------------------------------------
 * This file is part of the Keil uVision/ARM development tools and is intended
 * to be used for education purposes only.
 * The Keil software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2009 Keil - An ARM Company. All rights reserved.
 *
 *----------------------------------------------------------------------------
 * History:
 *          V1.00 Initial Version
 *----------------------------------------------------------------------------*/

#include <LPC23xx.H>                             /* LPC23xx definitions */
#include "emb1_labs.h"

CAN_MSG   message1 = {0x456, {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88}, 8, 0,0};


int main(void)
{
  init_timer0();
  init_Port4_5();
  CAN_Init( 1, 0x3DC002 );
  CAN_Init( 2, 0x3DC002 );
  CAN_Set_Acceptance_Filter_Mode(ACCF_BYPASS);
  /* Warte bis Sende-Status OK ist  */
  //while (!(CAN1GSR.TBS));
     CAN_Send_Message(1, &message1);
  while(1);
 
//  return 1;
}
