
#include <stdio.h>
#include <LPC23xx.h> 

extern void UART_init(int p_num,int u_dl,int mode,int fifo); 
extern void UART_PutChar(int p_num, int ch);
extern char UART_GetChar(int p_num);



unsigned char temp, MyChar;
unsigned int portNum=0, uDL=8, uART_mode=3, fIFO_mode=71, intEnableValue;

// PortNum = Port Number excepted to be 0 or 1 for the the EVB2300
// UDL = U_DLM*256 + U_DLL to set the data rate
//UART_mode = Content of the register UxLCR without the DLAB bit
//FIFO_mode = Content of the register UxFCR
//IntEnableValue = Content of the register UxIER


	

int main(void){

	UART_init(portNum, uDL, uART_mode, fIFO_mode); 

	while(1) {
		while(!(U0LSR&1)); 
	
		temp = UART_GetChar(portNum);
		UART_PutChar(portNum, temp);
	}
}

