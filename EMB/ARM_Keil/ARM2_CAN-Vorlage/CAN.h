/*----------------------------------------------------------------------------
 * Name:    CAN.h
 * Purpose: CAN interface for LPC23xx
 * Version: v1.00 / 14.08.2010 (Kru)
 * v1.1 / 30.11.2012  CAN_Sende_ID Vorgabe 0x799 (Poh)
 *----------------------------------------------------------------------------*/

#ifndef _CAN_H_
#define _CAN_H_

#include <stdint.h>                           /* Include standard types */

#define STANDARD_FORMAT  0
#define EXTENDED_FORMAT  1

#define DATA_FRAME       0
#define REMOTE_FRAME     1

// Node IDs (000..7FF) + CAN Connector
#define CAN_Sende_ID		0x799      // Sende-ID für ARM-Board = Platznummer + 700h in BCD (z.B. Platz 12: 0x712)
#define CAN_stecker			CAN2

/* Functions defined in module CAN.c */
void CAN_setup         (uint32_t ctrl);
void CAN_start         (uint32_t ctrl);
void CAN_wrFilter      (uint32_t ctrl, uint32_t id, uint8_t filter_type);
void CAN_SetACCF_Lookup( void );
void CAN_SetACCF( unsigned long ACCFMode );


/******************************************************************************/
/*                  CAN Specific Peripheral registers structures              */
/******************************************************************************/


/*- Controller Area Network (CAN) --------------------------------------------*/
typedef struct
{
  volatile uint32_t mask[512];              /* ID Masks                           */
} CANAF_RAM_TypeDef;


#define ACCEPTANCE_FILTER_ENABLED	0

#define CAN_MEM_BASE		0xE0038000

/* Acceptance filter mode in AFMR register */
#define ACCF_OFF				0x01
#define ACCF_BYPASS				0x02
#define ACCF_ON					0x00
#define ACCF_FULLCAN			0x04

/* This number applies to all FULLCAN IDs, explicit STD IDs, group STD IDs, 
explicit EXT IDs, and group EXT IDs. */ 
#define ACCF_IDEN_NUM			4

/* Identifiers for FULLCAN, EXP STD, GRP STD, EXP EXT, GRP EXT */
#define FULLCAN_ID				0x100
#define EXP_STD_ID				0x100
#define GRP_STD_ID				0x200
#define EXP_EXT_ID				0x100000
#define GRP_EXT_ID				0x200000


/******************************************************************************/
/*                           CAN memory map                                   */
/******************************************************************************/

#define CANAF_RAM_BASE        (0xE0038000)

/******************************************************************************/
/*                         Peripheral declaration                             */
/******************************************************************************/

#define CANAF_RAM             ((CANAF_RAM_TypeDef *) CANAF_RAM_BASE)

#endif // _CAN_H_
