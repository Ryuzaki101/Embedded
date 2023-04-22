///////////////////////////////////////////////////////////////////////
#define UART0_SW_RX_BUFFER_SIZE 128        // UART0 receive buffer size
#define UART0_SW_TX_BUFFER_SIZE 128        // UART0 transmit buffer size
#define UART1_SW_RX_BUFFER_SIZE 128        // UART1 receive buffer size
#define UART1_SW_TX_BUFFER_SIZE 128        // UART1 transmit buffer size

extern void UART_init(unsigned int , unsigned int , unsigned int, unsigned int);
extern void UART_PutChar (unsigned int PortNum, unsigned char WW);
extern unsigned char UART_GetChar(int PortNum);

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

