/******************************************************************************/
/* serielle_ss_duplex.C: Voll Duplex-Übertragung des AD-Wandlungswertes       */
/*                       mit Hardware Abstraktionsschicht                     */
/******************************************************************************/
/* Author: K.-H. Krauß                                                        */
/* Datum der letzten Änderung: 21.08.2007	Version: 1.0		              */
/******************************************************************************/
#include "LPC2xxx_embedded.h"
#include <LPC23xx.H>                    /* LPC23xx definitions                */


#define pinsel_1	0x00004001 /*AD0.0 pin und RXD1*/

pLPC_PinConnect_TypeDef	 pinsel_base;
pLPC_VIC_TypeDef VIC_Controller_basis; 
pLPC_ADC_TypeDef AD_sel_base;
                        
unsigned int AD_last,AD_neu;;

__irq void FIQ_ADC_Handler(void) 
{
  AD_last = (AD_sel_base->ADDR0 >> 6) & 0x3FF;      /* Read Conversion Result             */
  AD_sel_base->ADCR |= 0x01200000;					/* Start A/D Conversion   			  */ 
//  VIC_Controller_basis->VICAddress = 0; 			/* Acknowledge Interrupt              */
}
int main (void) 
{
 	pinsel_base=PinConnectBlock_BASE;
	VIC_Controller_basis=VIC_BASE;
	AD_sel_base=ADC_BASE;
  /* Power enable, Setup pin, enable and setup AD converter interrupt */
  	PCONP        |= (1 << 12);    /* Enable power to AD block    */
  	AD_sel_base->ADINTEN  = (1 <<  0);    /* CH0 enable interrupt        */

/*	ADC-Interrupt  */
  	VIC_Controller_basis->VICInterruptSelect |= (1  << 18);  /*AD-Interrupt ist FIQ*/
  	VIC_Controller_basis->VICInterruptEnable  |= (1  << 18);    /* Enable ADC Interrupt */
 	AD_sel_base->ADCR |= 0x01200000;		/* Start A/D Conversion   			  */ 
 
  while (1) 
  {  			                         
  AD_neu=AD_last;
  AD_last=0;
  }
}
