/*----------------------------------------------------------------------------
 * Name:    emb1_lab.h
 * Purpose: Header File for LPC23xx Microcontrollers in EMB1 labs
 *            (Keil MCB2300 Boards are assumed)
 * Version: Version 1.0 / 27.4.2012 (KBL, HS-Mannheim)
 *----------------------------------------------------------------------------
 *
 *----------------------------------------------------------------------------
 * History:
 *          V1.1 Initial Version
 *----------------------------------------------------------------------------*/
 
 #ifndef _EMB1_H_
 #define _EMB1_H_

 
#define I_Bit			0x80
#define F_Bit			0x40

#define SYS32Mode		0x1F
#define IRQ32Mode		0x12
#define FIQ32Mode		0x11

#define True  1
#define False  0

#include <stdint.h>                           /* Include standard types */
 
 /********************************************************************************
            II     RRRRRR      QQQQQQ
			II     RR   RR    QQ    QQ
			II     RRRRRR     QQ    QQ 
			II     RR   RR    QQ    QQ
			II     RR    RR    QQQQQQ
                                     Q
***********************************************************************************/

volatile typedef struct
{
    uint32_t VIC_IRQStatus ;       /* IRQ Status Register */
    uint32_t VIC_FIQStatus ;       /* FIQ Status Register */
    uint32_t VIC_RawIntr;          /* Raw Interrupt Status Register */
    uint32_t VIC_IntSelect;        /* Interrupt Select Register */
    uint32_t VIC_IntEnable;        /* Interrupt Enable Register */
    uint32_t VIC_IntEnClr;         /* Interrupt Enable Clear Register */
    uint32_t VIC_SoftInt;          /* SW Interrupt Register */
    uint32_t VIC_SoftIntClear ;    /* SW Interrupt ClearRegister */
    uint32_t VIC_Protection;       /* Protection Enable Register */
    uint32_t VIC_SWPrioMask;       /* Software Priority Mask */
    uint32_t Reserved1[0x36];      /* Reserved */
    uint32_t VIC_VectAddress[32];  /* Vector Address Register[0-31] */
    uint32_t Reserved2[0x20];      /* Reserved */
    uint32_t VIC_VectPriority[32]; /* Vector Priority */
    uint32_t Reserved3[0x320];     /* Reserved */
    uint32_t VIC_Address;          /* Vector Address Register */
} LPC_VIC_TypeDef;

#define   VIC		((      LPC_VIC_TypeDef *)     VIC_BASE_ADDR) 


// Macro for enabling interrupts, moving to System mode and relevant stack operations
#define IENABLE /* Nested Interrupts Entry */ \
__asm { MRS LR, SPSR } /* Copy SPSR_irq to LR */ \
__asm { STMFD SP!, {LR} } /* Save SPSR_irq */ \
__asm { MSR CPSR_c, #SYS32Mode } /* Enable IRQ (Sys Mode) */ \
__asm { STMFD SP!, {LR} } /* Save LR */ \

// Macro for disabling interrupts, switching back to IRQ and relevant stack operations
#define IDISABLE /* Nested Interrupts Exit */ \
__asm { LDMFD SP!, {LR} } /* Restore LR */ \
__asm { MSR CPSR_c, #(IRQ32Mode|I_Bit) } /* Disable IRQ (IRQ Mode) */ \
__asm { LDMFD SP!, {LR} } /* Restore SPSR_irq to LR */ \
__asm { MSR SPSR_cf, LR } /* Copy LR to SPSR_irq */ \


 
 
 /***************************************************************************
			 CCCCCC       AA       NN      NN 
			CC           AA AA     NN NN   NN 
			CC          AAAAAAA    NN   NN NN
			CC         AA     AA   NN    NNNN 
			 CCCCCC   AA       AA  NN      NN
******************************************************************************/

 #define MAX_PORTS	2		/* Number of CAN port on the chip */	

 #define STANDARD_FORMAT  0
 #define EXTENDED_FORMAT  1

 #define DATA_FRAME       0
 #define REMOTE_FRAME     1
 
 /**************************************************************************
		  Pre-defined Baud-Rate Settings
 ***************************************************************************/
  //BTR (Bit Timing) Values for a Peripheral Clock of 14.4 Mhz  
  //Assumption: Sampling point at approximately 80 % of Bit Time
  #define BITRATE100K14_4MHZ  0x00000000
  #define BITRATE125K14_4MHZ  0x00000000
  #define BITRATE250K14_4MHZ  0x00000000
  #define BITRATE500K14_4MHZ  0x00000000
  #define BITRATE1M14_4MHZ    0x00000000
  
  //BTR (Bit Timing) Values for a Peripheral Clock of 28.8 Mhz  
  //#define BITRATE100K28_8MHZ  0x00000000
  //#define BITRATE125K28_8MHZ  0x00000000
  //#define BITRATE250K28_8MHZ  0x00000000
  //#define BITRATE500K28_8MHZ  0x00000000
  //#define BITRATE1M28_8MHZ    0x00000000  
  
/**************************************************************************
		  Pre-Defined Acceptance Filter Mode (for the AFMR register)
***************************************************************************/
#define ACCF_OFF				0x01
#define ACCF_BYPASS				0x02
#define ACCF_ON					0x00
#define ACCF_FULLCAN			0x04

/*************************************************************************
     Number of CAN messages to be temporarily stored by the ISR before being
		 fetched by the application software
***************************************************************************/		 
#define CAN1_MAX_RX_MSG   20 
#define CAN2_MAX_RX_MSG   20 
 
 /**************************************************************************
         CAN Frame Content
 ***************************************************************************/
typedef struct  {
  uint32_t   id;                    /* 29-bit or 11-bit identifier */
  uint8_t  data[8];               /* Data field */
  uint8_t  length;                   /* Length of data field in bytes */
  uint8_t  frame_format;                /* 0 - STANDARD, 1- EXTENDED IDENTIFIER */
  uint8_t  frame_type;                  /* 0 - DATA FRAME, 1 - REMOTE FRAME */
} CAN_MSG;


 /******************************************************************************
		Declaration of CAN Public API Functions
 *******************************************************************************/
 
 /**************  CAN API  *************************************************/
 extern uint32_t CAN_Init( uint32_t CAN_Module_Number, uint32_t CAN_Baud_Rate );
 extern uint32_t CAN_Receive_Message( uint32_t CAN_Module_Number, CAN_MSG  *Dest_Rx_Data );
 extern uint32_t CAN_Send_Message( uint32_t CAN_Module_Number, CAN_MSG  *Tx_Data );
 extern void CAN_Interrupt_Handler(void) __irq ;
 extern void CAN_Set_Acceptance_Filter_Mode(uint32_t  ACF_Mode);
 extern uint32_t CAN_Set_Acceptance_LUT_RAM(void);

 
/********************************************************************************
		Structures Mapping Registers of CAN Modules
*********************************************************************************/
//  CANx (x = 1 or 2 for LPC2368 MCU) Controller Registers              
volatile typedef struct                          
{
  uint32_t MOD;
  uint32_t CMR;
  uint32_t GSR;
  uint32_t ICR;
  uint32_t IER;
  uint32_t BTR;
  uint32_t EWL;
  uint32_t SR;
  uint32_t RFS;
  uint32_t RID;
  uint32_t RDA;
  uint32_t RDB;
  uint32_t TFI1;
  uint32_t TID1;
  uint32_t TDA1;
  uint32_t TDB1;
  uint32_t TFI2;
  uint32_t TID2;
  uint32_t TDA2;
  uint32_t TDB2;
  uint32_t TFI3;
  uint32_t TID3;
  uint32_t TDA3;
  uint32_t TDB3;
} LPC_CAN_TypeDef;

/* CAN Acceptance Filter (Central) Registers        */
volatile typedef struct                          
{
  uint32_t AFMR;
  uint32_t SFF_sa;
  uint32_t SFF_GRP_sa;
  uint32_t EFF_sa;
  uint32_t EFF_GRP_sa;
  uint32_t ENDofTable;
  uint32_t LUTerrAd;
  uint32_t LUTerr;
} LPC_CANAF_TypeDef;


/* CAN Status (Central) Registers */
volatile typedef struct                          
{
  uint32_t CANTxSR;
  uint32_t CANRxSR;
  uint32_t CANMSR;
} LPC_CANCR_TypeDef;


/* ID Masks  / CAN Acceptance LUT RAM    */
volatile typedef struct
{
  uint32_t mask[512];              
} LPC_CANAF_RAM_TypeDef;

/* Definition of pointers on CAN base addresses  */
#define CANAF_RAM    	((LPC_CANAF_RAM_TypeDef *)     0xE0038000)
#define CAN_AF           ((    LPC_CANAF_TypeDef *)     CAN_ACCEPT_BASE_ADDR)
#define CANCR           ((    LPC_CANCR_TypeDef *)     CAN_CENTRAL_BASE_ADDR)
#define CAN1            ((      LPC_CAN_TypeDef *)     CAN1_BASE_ADDR)
#define CAN2  			((      LPC_CAN_TypeDef *)     CAN2_BASE_ADDR)


#endif	// __EMB1_H

/******************************************************************************
**                            End Of File
******************************************************************************/
