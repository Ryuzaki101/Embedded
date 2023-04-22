#include <stdio.h>
#include <LPC23xx.h> 
#include "uart.h"

extern void UART_init(unsigned int , unsigned int , unsigned int, unsigned int);
extern void UART_PutChar (unsigned int PortNum, unsigned char WW);
extern unsigned char UART_GetChar(int PortNum);

extern void lcd_init (void);
extern void lcd_print (char *string);
extern void set_cursor (unsigned char column, unsigned char line);
extern void lcd_clear (void);
extern void  init_Timer0_for_UART(void);

extern void init_VIC(void);
extern void init_ext_int0 (void);

extern int U0_rx_sw_buffer_index, U1_rx_sw_buffer_index; 

//UART related global variables
extern int U0_rx_sw_buffer_index, U1_rx_sw_buffer_index; 
extern int U0_tx_sw_buffer_index, U1_tx_sw_buffer_index; 
extern int U0_TX_NumberOfChar, U1_TX_NumberOfChar;
//extern unsigned char UART0_BytesToBeTransmitted[UART0_SW_TX_BUFFER_SIZE];
//extern  unsigned char UART1_BytesToBeTransmitted[UART1_SW_TX_BUFFER_SIZE];
extern  unsigned char UART0_ReceivedBytes[UART0_SW_RX_BUFFER_SIZE];
extern  unsigned char UART1_ReceivedBytes[UART1_SW_RX_BUFFER_SIZE];
extern  int AutoBaud_U0DLL, AutoBaud_U0DLM;
extern  int AutoBaud_U1DLL, AutoBaud_U1DLM;
extern  int U0_TX_Running, U1_TX_Running;

unsigned char MyChar;
unsigned int PortNum, UDL, UART_mode, FIFO_mode, IntEnableValue, Temp;
// PortNum = Port Number excepted to be 0 or 1 for the the EVB2300
// UDL = U_DLM*256 + U_DLL to set the data rate
//UART_mode = Content of the register UxLCR without the DLAB bit
//FIFO_mode = Content of the register UxFCR
//IntEnableValue = Content of the register UxIER
	
	

int main(void){ 
	//int LaunchAutoBaudMeasurement;
//UART Configuration 
	PortNum = 0;
	UDL = 94;
	UART_mode = 0x03; // 8 Bits, 1 stop bit, no parity, break transmission disabled	
	FIFO_mode = 0xC3;	// FIFO enabled, (TX FIFO cleared, RX FIFI cleared), RX FIFO trigger level = 14
	IntEnableValue = 0x01; //RX Interrupt enabled	
	
	U0_rx_sw_buffer_index = 0;
	U1_rx_sw_buffer_index = 0;	

//IDISABLE;	
//	IRQ_Disable();
	UART_init (PortNum, UDL, UART_mode, ((IntEnableValue << 8) | FIFO_mode)); 
//IENABLE;	
//	IRQ_Enable();
	
	init_VIC();
	U0IER |= 0x02; //TX interrupt enabled
	init_ext_int0();
	init_Timer0_for_UART();
	
	//LaunchAutoBaudMeasurement = 1; //Auto-baud measurement only if this flag is 1.
	
	lcd_init();	
  
	lcd_clear();
  lcd_print("Hallo zusammen! ");
	set_cursor(0,1);
	lcd_print("  Willkommen!   ");
	
	
while(1){
	
	}	
 }


