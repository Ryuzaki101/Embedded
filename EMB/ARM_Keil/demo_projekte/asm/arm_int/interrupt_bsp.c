/******************************************************************************/
/* IRQ-Interrupt: AD-Wandler erzeugt nach Wandlungsende einen IRQ-Interrupt   */
/*                                                                            */
/******************************************************************************/
/* Author: K.-H. Krauß                                                        */
/* Datum der letzten Änderung: 05.05.2008	Version: 1.1		              */
/******************************************************************************/
#include "LPC2xxx_embedded.h"
#include <LPC23xx.H>                    /* LPC23xx definitions                */


#define pinsel_1	0x00004000 /*AD0.0 pin für AD-Wandlung freigeben*/

pLPC_PinConnect_TypeDef	 pinsel_base;
pLPC_VIC_TypeDef VIC_Controller_basis; 
pLPC_ADC_TypeDef AD_sel_base;
                        
unsigned int AD_last,AD_neu;;

__irq void ADC_IRQHandler(void) 
{
  AD_last = (AD_sel_base->ADDR0 >> 6) & 0x3FF;      /* Read Conversion Result             */
  AD_sel_base->ADCR |= 0x01200001;					/* Start A/D Conversion   			  */ 
  VIC_Controller_basis->VIC_Address = 0; 			/* Acknowledge Interrupt              */
}
int main (void) 
{
 	pinsel_base=PinConnectBlock_BASE;
	VIC_Controller_basis=VIC_BASE;
	AD_sel_base=ADC_BASE;

	pinsel_base->PIN_SEL1=pinsel_1;	/*AD.0 freigeben*/

  /* Power enable, Setup pin, enable and setup AD converter interrupt */
  PCONP        |= (1 << 12);    /* Enable power to AD block    */
 
  AD_sel_base->ADINTEN  = (1 <<  0);    /* CH0 enable interrupt        */

/*	ADC-Interrupt  */
  VIC_Controller_basis->VIC_VectAddress[18] =(unsigned long)ADC_IRQHandler;  
  VIC_Controller_basis->VIC_VectPriority[18] = 12;     /* priority for ADC Interrupt */                     
  VIC_Controller_basis->VIC_IntEnable  |= (1  << 18);    /* Enable ADC Interrupt */

 	AD_sel_base->ADCR |= 0x01200000;		/* Start A/D Conversion   			  */ 
 //	AD_sel_base->ADCR |= 0x01200301;	/* bei PCLK=14,4MHZ!! Start A/D Conversion   			  */ 

  while (1) 
  {  			                         
  AD_neu=AD_last;
  AD_last=0;
  }
}
