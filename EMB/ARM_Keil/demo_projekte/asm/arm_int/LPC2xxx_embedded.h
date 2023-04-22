/*********************************************************************/
/*      Datei: LPC2xxxembedded.h                                     */
/*      Letzte Änderung: 18.05.2011 Version 1.3(KRU)                 */
/*                                                                   */
/*********************************************************************/
#ifndef _LPC_H
#define _LPC_H

#define u_int unsigned int

#define UART0_ID 0x0
#define UART1_ID 0x1
#define CAN1 1
#define CAN2 2


#define TIMER0_ID 0x0   // dient zur Auswahl des Timers 0
#define TIMER1_ID 0x1   // dient zur Auswahl des Timers 1
#define	TIMER2_ID 0x2   // dient zur Auswahl des Timers 2
#define TIMER3_ID 0x3   // dient zur Auswahl des Timers 3

#define AIC_ID    0x0

/*-----------------------*/
/* Memory mapping        */
/*-----------------------*/

#define WatchdogTimer_Base			0xE0000000
#define TIMER0_BASE					((pLPC_TIMER_TypeDef) 0xE0004000)
#define TIMER1_BASE					((pLPC_TIMER_TypeDef) 0xE0008000)
#define TIMER2_BASE					((pLPC_TIMER_TypeDef) 0xE0070000)
#define TIMER3_BASE					((pLPC_TIMER_TypeDef) 0xE0074000)
#define UART0_BASE					((pLPC_UART_TypeDef) 0xE000C000)
#define UART1_BASE					((pLPC_UART_TypeDef) 0xE0010000)
#define PWM0_BASE					0xE0014000
#define I2C_BASE					0xE001C000
#define SPI0_BASE					0xE0020000
#define RTC_BASE					0xE0024000
#define GPIO_BASE					0xE0028000
#define PinConnectBlock_BASE		((pLPC_PinConnect_TypeDef) 0xE002C000)
#define SPI1_BASE					0xE0030000
#define ADC_BASE					((pLPC_ADC_TypeDef)0xE0034000)
#define VIC_BASE					((pLPC_VIC_TypeDef) 0xFFFFF000)
#define CAN1_BASE					((pLPC_CAN_TypeDef) 0xE0044000)
#define CAN2_BASE					((pLPC_CAN_TypeDef) 0xE0048000)
#define CANAF_BASE					((pLPC_CANAF_TypeDef) 0xE003C000)
#define CANCR_BASE 					((pLPC_CANCR_TypeDef) 0xE0040000)


/*---------------------------------*/
/* PinConnectBlock                 */
/*---------------------------------*/

volatile typedef struct     //Pin Kontroll Register
{
	u_int PIN_SEL0;
	u_int PIN_SEL1;
	u_int PIN_SEL2;
	u_int PIN_SEL3;
	u_int PIN_SEL4;
	u_int PIN_SEL5;
	u_int PIN_SEL6;
	u_int PIN_SEL7;
	u_int PIN_SEL8;
	u_int PIN_SEL9;
	u_int PIN_SEL10;
	u_int Reserved[5];
	u_int PIN_MODE0;
	u_int PIN_MODE1;
	u_int PIN_MODE2;
	u_int PIN_MODE3;
	u_int PIN_MODE4;
	u_int PIN_MODE5;
	u_int PIN_MODE6;
	u_int PIN_MODE7;
	u_int PIN_MODE8;
	u_int PIN_MODE9;

} LPC_PinConnect_TypeDef, *pLPC_PinConnect_TypeDef;

/*---------------------------------*/
/* VIC Interrupt Controller LPC2368*/
/*---------------------------------*/

volatile typedef struct
{
	u_int VIC_IRQStatus ;       /* IRQ Status Register */
	u_int VIC_FIQStatus ;       /* FIQ Status Register */
	u_int VIC_RawIntr;          /* Raw Interrupt Status Register */
	u_int VIC_IntSelect;        /* Interrupt Select Register */
	u_int VIC_IntEnable;        /* Interrupt Enable Register */
	u_int VIC_IntEnClr;         /* Interrupt Enable Clear Register */
	u_int VIC_SoftInt;          /* SW Interrupt Register */
	u_int VIC_SoftIntClear ;    /* SW Interrupt ClearRegister */
	u_int VIC_Protection;       /* Protection Enable Register */
	u_int VIC_SWPrioMask;       /* Software Priority Mask */
	u_int Reserved1[0x36];      /* Reserved */
	u_int VIC_VectAddress[32];  /* Vector Address Register[0-31] */
	u_int Reserved2[0x20];      /* Reserved */
	u_int VIC_VectPriority[32]; /* Vector Priority */
	u_int Reserved3[0x320];     /* Reserved */
	u_int VIC_Address;          /* Vector Address Register */
} LPC_VIC_TypeDef, *pLPC_VIC_TypeDef ;

/*---------------------------------*/
/* CAN-Acceptance Filter                             */
/*---------------------------------*/


volatile typedef struct                          /* Acceptance Filter Registers        */
{
	u_int AFMR;
	u_int SFF_sa;
	u_int SFF_GRP_sa;
	u_int EFF_sa;
	u_int EFF_GRP_sa;
	u_int ENDofTable;
	u_int LUTerrAd;
	u_int LUTerr;
} LPC_CANAF_TypeDef, *pLPC_CANAF_TypeDef;


/*---------------------------------*/
/* CAN-Central Registers      		*/
/*---------------------------------*/

volatile typedef struct
{
	u_int   CANTxSR;
	u_int   CANRxSR;
	u_int   CANMSR;
} LPC_CANCR_TypeDef, *pLPC_CANCR_TypeDef;


/*---------------------------------*/
/* CAN                             */
/*---------------------------------*/

volatile typedef struct                          /* Controller Registers               */
{
	u_int MOD;
	u_int CMR;
	u_int GSR;
	u_int ICR;
	u_int IER;
	u_int BTR;
	u_int EWL;
	u_int SR;
	u_int RFS;
	u_int RID;
	u_int RDA;
	u_int RDB;
	u_int TFI1;
	u_int TID1;
	u_int TDA1;
	u_int TDB1;
	u_int TFI2;
	u_int TID2;
	u_int TDA2;
	u_int TDB2;
	u_int TFI3;
	u_int TID3;
	u_int TDA3;
	u_int TDB3;
} CAN_TypeDef,*pLPC_CAN_TypeDef;




/*---------------------------------*/
/* UART                            */
/*---------------------------------*/

volatile typedef struct
{
	u_int	RB_TB_DIVL;
/*		URBR;		Receiver Reg	 	when DLAB = 0, RO
		UTHR;		Transmitter Reg		when DLAB = 0, WO
		UDLL;		Divisor Latch Low Reg	when DLAB = 1
*/
	u_int	DIVH_IE;
/*		UDLM; 		Divisor Latch High Reg	when DLAB = 1
		UIER; 		Interrupt Enable Reg	when DLAB = 0
*/

	u_int	IIR_FCR;
/*	 	UIIR; 		Interrupt Identification  Reg, RO
	 	UFCR; 		FIFO Control Reg, WO
*/
	u_int	ULCR;		/*Line Control Reg	*/
	u_int	UMCR;		/*Modem Control Reg (UART1 only)*/
	u_int	ULSR;		/*Line Status Reg		RO	*/
	u_int	UMSR;		/*Modem Status Reg (UART1 only)*/
	u_int	USCR;		/*Scratch Pad Reg	  */

} LPC_UART_TypeDef, *pLPC_UART_TypeDef ;

/*----------------------------------*/
/* TIMER                            */
/*----------------------------------*/

volatile typedef struct
{
	u_int TIR;	 	/*Interrupt Register*/
	u_int TTCR;		/*Timer-Control Register*/
	u_int TTC;	 	/*Timer-Counter*/
	u_int TPR;		/*Prescale Register*/
	u_int TPC;	 	/*Prescale Counter*/
	u_int TMCR;		/*Match Control Register*/
	u_int TMR0;		/*Match Register 0*/
	u_int TMR1;		/*Match Register 1*/
	u_int TMR2;		/*Match Register 2*/
	u_int TMR3;		/*Match Register 3*/
	u_int TCCR;		/*Capture Control Register*/
	u_int TCR0;		/*Capture Register 0*/
	u_int TCR1;		/*Capture Register 1*/
	u_int TCR2;		/*Capture Register 2*/
	u_int TCR3;		/*Capture Register 3*/
	u_int TEMR;		/*External Match Register*/
	u_int Reserved[0xC];
	u_int TCTCR;	/*Count Control Register*/
}LPC_TIMER_Typedef,*pLPC_TIMER_TypeDef;

/*----------------------------------*/
/* AD-Wandler                       */
/*----------------------------------*/
volatile typedef struct
{
	u_int ADCR;   	/*AD-Control Register*/
	u_int ADGDR;  	/*AD-Global Data Register*/
	u_int ADSTAT; 	/*AD-Status Register*/
	u_int ADINTEN;	/*AD-Interrupt Enable Register*/
	u_int ADDR0;	/*ADChannel 0 Register*/
	u_int ADDR1;	/*ADChannel 1 Register*/
	u_int ADDR2;	/*ADChannel 2 Register*/
	u_int ADDR3;	/*ADChannel 3 Register*/
	u_int ADDR4;	/*ADChannel 4 Register*/
	u_int ADDR5;	/*ADChannel 5 Register*/
	u_int ADDR6;	/*ADChannel 6 Register*/
	u_int ADDR7;	/*ADChannel 7 Register*/
}LPC_ADC_Typedef,*pLPC_ADC_TypeDef;

#endif /* _LPC_H */
