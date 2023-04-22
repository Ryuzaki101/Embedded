/******************************************************************************/
/* UART_Init.c: Serielles Polling des UART  über Hyperterminal                */
/*              Initialisierungsroutine                                       */
/******************************************************************************/
/* Autor: KRU                                                                 */
/* Datum der letzten Änderung: 2.11.2007                                      */
/******************************************************************************/

#include <LPC23xx.h>                     /* LPC23xx definitions               */

#define UART1                            /* Use UART 1                        */

/* If UART 0 */
#ifdef UART0
  #define UxFDR  U0FDR
  #define UxLCR  U0LCR
  #define UxDLL  U0DLL
  #define UxDLM  U0DLM
  #define UxLSR  U0LSR
  #define UxTHR  U0THR
  #define UxRBR  U0RBR
  #define UxIER  U0IER

/* If UART 1 */
#elif defined(UART1)
  #define UxFDR  U1FDR
  #define UxLCR  U1LCR
  #define UxDLL  U1DLL
  #define UxDLM  U1DLM
  #define UxLSR  U1LSR
  #define UxTHR  U1THR
  #define UxRBR  U1RBR
  #define UxIER  U1IER
#endif


void UART1_Init (void)
{
  UxFDR    = 0;             /* Fractional divider not used       */
  UxLCR    = 0x83;          /* 8 bits, no Parity, 1 Stop bit     */
  UxDLL    = 94;            /* 9600 Baud Rate @ 14.4 MHZ PCLK    */
  UxDLM    = 0;             /* High divisor latch = 0            */
  UxLCR    = 0x03;          /* DLAB  = 0                         */

}


