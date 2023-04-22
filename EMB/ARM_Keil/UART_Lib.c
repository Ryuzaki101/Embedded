#include "LPC2xxx_embedded.h"

#define NULL 0
pLPC_UART_TypeDef UARTopen(u_int UART_ID)
{
	if (UART_ID == UART0_ID)
			return UART0_BASE;
	if (UART_ID == UART1_ID)
			return UART1_BASE;
	return NULL;
}
void UARTinit(pLPC_UART_TypeDef UARTbase, u_int mode, u_int baudteiler_low,
			 u_int baudteiler_high,u_int FIFOmode)
{
	UARTbase-> ULCR = mode | 0x80;	   /*DLAB=1!*/
	UARTbase-> RB_TB_DIVL = baudteiler_low;
	UARTbase-> DIVH_IE = baudteiler_high;
	UARTbase-> ULCR &=    0x7F;		/*DLAB=0!*/
	UARTbase-> IIR_FCR =	FIFOmode;
}
void UARTenableInt (pLPC_UART_TypeDef UARTbase,u_int Receive_Int, u_int Transmit_Int)
{
	UARTbase-> DIVH_IE |= (Receive_Int << 0);	   /*DLAB=0!*/
	UARTbase-> DIVH_IE |= (Transmit_Int << 1);
}
void UARTclose(pLPC_UART_TypeDef UARTbase)
{	UARTbase-> ULCR &=    0x7F;		/*DLAB=0!*/
	UARTbase-> DIVH_IE =0;
	UARTbase-> IIR_FCR = 0;
}

void PINSEL_UART01 (pLPC_PinConnect_TypeDef PinSel_base, u_int value_Pinsel_0,u_int value_Pinsel_1)
{
	 PinSel_base->PIN_SEL0 |= value_Pinsel_0;
	 PinSel_base->PIN_SEL1 |= value_Pinsel_1;
}

