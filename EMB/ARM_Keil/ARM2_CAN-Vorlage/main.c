/*----------------------------------------------------------------------------
 * Name:    main.c
 * Purpose: Analogwert senden und empfangen über CAN-Schnittstelle
 * Version: v1.0 / 19.8.2010 (Kru, HS-Mannheim)
 * v1.1 /  3.05.2012  ohne Senden bei Reset (Poh)
 * v1.2 / 30.11.2012  mit Anzeige der Sende- und Empfangs-ID + CAN-Stecker (Poh)
 *----------------------------------------------------------------------------*/

#include <LPC23xx.h>           /* LPC23xx definitions */
#include "LPC2xxx_embedded.h"
#include "CAN.h"               /* LPC23xx CAN adaption layer */
#include "LCD.h"               /* LCD function prototypes */


unsigned char ad_asc_out[3]         ={'-','-','-'};
unsigned char ad_asc_in[3]          ={'-','-','-'};
unsigned char CAN_Sende_ID_asc[3]   ={'-','-','-'};
unsigned char CAN_Empfangs_ID_asc[3]={'-','-','-'};
unsigned char CAN_Sendezaehler      =0;
unsigned char CAN_Empfangszaehler   =0;

// Definition Strukturzeiger
pLPC_VIC_TypeDef  VIC_Controller_basis;
pLPC_CAN_TypeDef pCAN;
pLPC_CANAF_TypeDef CANAF_Controller_basis ;

extern  void adc_init(void);
extern  void vic_init(void);
extern void CAN_EINT_setup (uint32_t CAN_x);
extern short AD_last ;
extern unsigned int CAN_Empfangs_ID;

unsigned char ad_rest;
short i;

/*------------------------------------------------------------------------------
  convert one byte to string in hexadecimal notation
 *------------------------------------------------------------------------------*/
void hex_ascii_string (unsigned short hex, unsigned char *string)
{ short y,p=0;
  unsigned char temp[3]={'-','-','-'};
  y = hex ;
  for ( i=0; i < 3; i++ )
			{
	 			ad_rest  = y>>(i<<2);
				ad_rest &= 0x00F;
				if (ad_rest < 10)
					ad_rest  += 0x30;
				else
					ad_rest  += 0x37;
				temp[i] = ad_rest;
			}

	for (i= 2; i>= 0; i--)
	{
		string[p] = temp[i] ;
		p++ ;
	}

}

/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
int main (void)  {
	short k,l ;

	VIC_Controller_basis = VIC_BASE;      /*  Initialize VIC Controller Structure	*/
	CANAF_Controller_basis = CANAF_BASE;  /*  Initialize CAN-Acceptance-Filter Structure	*/
	adc_init ();
	vic_init();                           /* initialise A/D converter */
	CAN_EINT_setup (CAN_stecker);         /* initialise CAN interface */

	//Initialize LCD
	lcd_init();
	lcd_clear();

	// set_cursor(0,0);     //Column = 0, Row = 0
	lcd_print("CAN2i:");    //LCD: Ausgabe linke Seite unter der Annahme  CAN_stecker == CAN2
	set_cursor(0,1);        //Column = 0, Row = 1
	lcd_print("CAN2o:");

	if (CAN_stecker == CAN1){  //LCD: Korrektur für CAN1
		set_cursor(0,0);	lcd_print("CAN1");		//Column = 3, Row = 0
		set_cursor(0,1);	lcd_print("CAN1");		//Column = 3, Row = 1
	}

	set_cursor (7, 1);  // Sende-ID (konstant)
	hex_ascii_string(CAN_Sende_ID, CAN_Sende_ID_asc);
	for(l=0;l<3;l++)
		lcd_putchar(CAN_Sende_ID_asc[l]);

	while (1) {  /* display Tx and Rx values to LCD disp */
		/* Zeile 0: Empfangsanzeige */

		set_cursor (7, 0);  // Empfangs-ID
		hex_ascii_string(CAN_Empfangs_ID, CAN_Empfangs_ID_asc);
		for(l=0;l<3;l++)
			lcd_putchar(CAN_Empfangs_ID_asc[l]);

		set_cursor (11, 0);  // Empfangswert
		// ad_asc_in  liegt vom Empfang bereits in ASCII-Form vor!
		for(l=0;l<3;l++)
			lcd_putchar(ad_asc_in[l]);

		set_cursor (15, 0);  // Empfangszähler 0..9
		lcd_putchar(CAN_Empfangszaehler+0x30);

		/* Zeile 1: Sendeanzeige */
		
		set_cursor (11, 1);  // Sendewert
		hex_ascii_string(AD_last, ad_asc_out);
		for(k=0;k<3;k++)
			lcd_putchar(ad_asc_out[k]);

		set_cursor (15, 1);  // Sendezähler 0..9
		lcd_putchar(CAN_Sendezaehler+0x30);
	}
}
