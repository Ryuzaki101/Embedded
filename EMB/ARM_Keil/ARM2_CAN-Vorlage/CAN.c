/*----------------------------------------------------------------------------
 * Name:    Can.c
 * Purpose: CAN interface for for LPC23xx with MCB2300
 * Version: v1.0 / 22.8.2010 (Kru, HS-Mannheim)
 * v1.1 / 30.11.2012  mit Sende- und Empfangs-ID + Zähler (Poh)
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2009 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#include <LPC23xx.H>                             /* LPC23xx definitions */
#include "LPC2xxx_embedded.h"
#include "CAN.h"                                 /* LPC23xx CAN adaption layer */

void CAN_EINT_setup (uint32_t CAN_x);
void CAN_ISR (void) __irq;
void EINT0_ISR (void) __irq;

unsigned int CAN_Empfangs_ID;
short m;

extern pLPC_VIC_TypeDef  VIC_Controller_basis;
extern pLPC_CANAF_TypeDef CANAF_Controller_basis;
extern pLPC_CAN_TypeDef pCAN ;
extern void CAN_wrFilter (uint32_t CANx, uint32_t id, uint8_t format);

extern unsigned char ad_asc_out[3];
extern unsigned char ad_asc_in[3];
extern unsigned char CAN_Sendezaehler;
extern unsigned char CAN_Empfangszaehler;


/*----------------------------------------------------------------------------
  setup CAN interface.  CAN controller (1..2)
 *----------------------------------------------------------------------------*/
void CAN_EINT_setup (uint32_t CAN_x)  {
  if (CAN_x == CAN1)
  {
  	pCAN	= CAN1_BASE ;
    PCONP   |= 1 << 13;                          /* Enable clock for CAN1 */
    PINSEL0 &= 0xFFFFFFF0;                       /* Reset CAN1 bits */
    PINSEL0 |= 0x00000005;                       /* Set CAN1 bits to b0101 */

  } else 
  {
    pCAN	= CAN2_BASE ;
    PCONP   |= 1 << 14;                          /* Enable clock for CAN2 */
    PINSEL0 &= 0xFFFFF0FF;                       /* Reset CAN2 bits */
    PINSEL0 |= 0x00000A00;                       /* Set CAN2 bits to b1010 */
  }
/*----------------------------------------------------------------------------
  setup external interrupt EINT0
 *----------------------------------------------------------------------------*/
	PINSEL4 |= 0x00100000; 
	EXTMODE |=( 1<<0 );
	EXTPOLAR=0;
	CAN_wrFilter (CAN_stecker, 0x700, STANDARD_FORMAT);  // Acceptance Filter ON  0x700=PCAN am Projektor
	CAN_wrFilter (CAN_stecker, 0x799, STANDARD_FORMAT);  // Acceptance Filter ON  hier weitere Empfangs-ID eintragen
	pCAN->MOD = 1;         /* Enter reset mode */
	pCAN->IER = 0;         /* Disable all interrupts */
	pCAN->GSR = 0;         /* Clear status register */
	pCAN->BTR = 0x3DC002;  /* 250kbits/s 14.4MHZ  BRP=2  80%  Tq = 208ns  */
	pCAN->IER = 0x0003;    /* Enable Tx and Rx interrupt */
	pCAN->MOD = 0;
}

/*----------------------------------------------------------------------------
  CAN Interrupt-Service-Routine 
*----------------------------------------------------------------------------*/
void CAN_ISR (void) __irq  
{
	volatile uint32_t temp;
	unsigned char can_eingangspuffer[8];
   
	if (pCAN->GSR & (1 << 0))  /* CAN Controller meassage is received */
	{
		CAN_Empfangs_ID = pCAN->RID;  // Received Identifier
		*(unsigned int *)&can_eingangspuffer[0] = pCAN->RDA;

		for(m=0;m<3;m++)
		ad_asc_in[m] = can_eingangspuffer[m];

		pCAN->CMR = (1 << 2);	  						/* Release receive buffer */
		if(++CAN_Empfangszaehler==10) CAN_Empfangszaehler=0;  // Zähler für die LCD-Anzeige erhöhen
	}

	temp =pCAN->ICR;
	VIC_Controller_basis->VIC_Address = 0;	
}

void EINT0_ISR (void) __irq 
{
	volatile uint32_t temp;
	if (pCAN->GSR & (1 << 3)) 
	{    				/* CAN Controller #2 meassage is transmitted */
		if (pCAN->SR & (1<<2))  {                      /* Transmit buffer 1 free */
			pCAN->TFI1  = 0x00030000;                      /* Write frame informations */
    		pCAN->TID1 = CAN_Sende_ID;                           /* Write CAN message identifier */  	
			pCAN->TDA1 = *(int *)(ad_asc_out); 			/* Write first 4 data bytes */				
			pCAN->CMR  = 0x21;  							/* Start transmission without loop-back */
			if(++CAN_Sendezaehler==10) CAN_Sendezaehler=0;  // Zähler für die LCD-Anzeige erhöhen
		}
	}
    temp =pCAN->ICR;
	EXTINT |= (1<<0);
  	VIC_Controller_basis->VIC_Address = 0;
}
