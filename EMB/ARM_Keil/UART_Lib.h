#define u_int unsigned int
/********************************************/
/* Function Name:	UARTopen			    */
/*	Input:			UART_ID					*/
/*  Output:			None		  		 	*/
/*  Return:			UART Base Address		*/
/********************************************/
pLPC_UART_TypeDef UARTopen(u_int UART_ID);

/**********************************************/
/* Function Name:	UARTinit			      */
/*	Description:	This funktion initializes */
/*                  the UART                  */
/*	Input1:			UART Base address         */
/*	Input1:         Mode(Char,parity,stopbits)*/
/*  Input3:			baudraten-teiler low      */
/*  Input4:			baudraten-teiler high     */
/*  Input5:			FIFO Mode	              */
/*  Return:			None                      */
/**********************************************/
void UARTinit(pLPC_UART_TypeDef UART_base, u_int mode, u_int baudrate_low,
			 u_int baudrate_high,u_int FIFOmode);

/********************************************/
/* Function Name:	UARTenableInt		    */
/*	Input1:			UART Base address       */
/*	Input2:			Receiver_Int 0:nein 1:ja*/
/*	Input3:			Transmit_Int 0:nein 1:ja*/
/*  Output:			None		  		 	*/
/*  Return:			None					*/
/********************************************/
void UARTenableInt (pLPC_UART_TypeDef UART_base,u_int Receiver_Int, u_int Transmit_Int);

/********************************************/
/* Function Name:	UARTclose			    */
/*	Input:			UART Base address		*/
/*  Output:			None		  		 	*/
/*  Return:			none					*/
/********************************************/
void UARTclose(pLPC_UART_TypeDef UART_base);


/**********************************************/
/* Function Name:	PINSEL_UART01		      */
/*	Description:	This funktion initializes */
/*                  the Pins for UART 0 and 1 */
/*	Input1:			PINSEL Base address       */
/*	Input2:         Pinsel 0 Value			  */
/*  Input3:			Pinsel 1 Value 		      */
/*  Return:			None                      */
/**********************************************/
void PINSEL_UART01 (pLPC_PinConnect_TypeDef Pinsel_base,
					 u_int value_Pinsel_0,u_int value_Pinsel_1);
