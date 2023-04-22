;********************************************************************************
;*   LPC23xx.inc:  Include file for NXP LPC23xx/24xx Family Microprocessors     *
;*                                                                              *
;*   Inkludieren mit: INCLUDE LPC2368_asm.inc                                   *
;*                                                                              *
;*   08.04.2008  ver 2.00   HS-Mannheim (KRU/Uru)  			                    *
;*   Adressen der Register:	                                                    *	  
;*   FIO0-4                                                                     *
;*   PCONP                        						                        *
;*   Fast IO Ports FIO0-3	                                                    *
;*	 VIC (Vectored Interrupt Controller)                           	        	*
;*   PINSEL								                                    	*
;*   UART0-3				       				                            	*
;*   TIMER0-3				               			                        	*
;*   ADC									                                    *
;*									                                        	*
;********************************************************************************
;	IF :DEF:__LPC_asm
	IF      (:LNOT:(:DEF:__LPC_asm))	
__LPC_asm

;/****** System Control Block(SCB) modul Power Control Register  ******/
SCB_BASE_ADDR	EQU	0xE01FC000		 
PCON		EQU (SCB_BASE_ADDR + 0x0C0)  ; volatile unsigned long
PCONP		EQU (SCB_BASE_ADDR + 0x0C4)  ; volatile unsigned long
INTWAKE		EQU (SCB_BASE_ADDR + 0x144)  ; volatile unsigned long

;Fast IO PORT 0
FIO0_BASE_ADDR	EQU	0x3FFFC000
FIO0_DIR	EQU (FIO0_BASE_ADDR + 0x000)  ; volatile unsigned long
FIO0_DIR0	EQU (FIO0_BASE_ADDR + 0x000) ; volatile unsigned long
FIO0_DIR1	EQU (FIO0_BASE_ADDR + 0x001) ; volatile unsigned long
FIO0_DIR2	EQU (FIO0_BASE_ADDR + 0x002) ; volatile unsigned long
FIO0_DIR3	EQU (FIO0_BASE_ADDR + 0x003)  ; volatile unsigned long
FIO0_DIRL	EQU (FIO0_BASE_ADDR + 0x000)  ; volatile unsigned long
FIO0_DIRU	EQU (FIO0_BASE_ADDR + 0x002)  ; volatile unsigned long

FIO0_MASK  	EQU (FIO0_BASE_ADDR + 0x010)  ; volatile unsigned long
FIO0_MASK0 	EQU (FIO0_BASE_ADDR + 0x010)  ; volatile unsigned long
FIO0_MASK1 	EQU (FIO0_BASE_ADDR + 0x011)  ; volatile unsigned long
FIO0_MASK2 	EQU (FIO0_BASE_ADDR + 0x012)  ; volatile unsigned long
FIO0_MASK3 	EQU (FIO0_BASE_ADDR + 0x013)  ; volatile unsigned long
FIO0_MASKL 	EQU (FIO0_BASE_ADDR + 0x010)  ; volatile unsigned long
FIO0_MASKU 	EQU (FIO0_BASE_ADDR + 0x012)  ; volatile unsigned long

FIO0_PIN    EQU (FIO0_BASE_ADDR + 0x014)  ; volatile unsigned long
FIO0_PIN0   EQU (FIO0_BASE_ADDR + 0x014)  ; volatile unsigned long
FIO0_PIN1   EQU (FIO0_BASE_ADDR + 0x015)  ; volatile unsigned long
FIO0_PIN2   EQU (FIO0_BASE_ADDR + 0x016)  ; volatile unsigned long
FIO0_PIN3   EQU (FIO0_BASE_ADDR + 0x017)  ; volatile unsigned long
FIO0_PINL   EQU (FIO0_BASE_ADDR + 0x014)  ; volatile unsigned long
FIO0_PINU   EQU (FIO0_BASE_ADDR + 0x016)  ; volatile unsigned long

FIO0_SET	EQU (FIO0_BASE_ADDR + 0x018)  ; volatile unsigned long
FIO0_SET0	EQU (FIO0_BASE_ADDR + 0x018)  ; volatile unsigned long
FIO0_SET1	EQU (FIO0_BASE_ADDR + 0x019)  ; volatile unsigned long
FIO0_SET2	EQU (FIO0_BASE_ADDR + 0x01A)  ; volatile unsigned long
FIO0_SET3	EQU (FIO0_BASE_ADDR + 0x01B)  ; volatile unsigned long
FIO0_SETL	EQU (FIO0_BASE_ADDR + 0x018)  ; volatile unsigned long
FIO0_SETU	EQU (FIO0_BASE_ADDR + 0x01A)  ; volatile unsigned long

FIO0_CLR  	EQU (FIO0_BASE_ADDR + 0x01C)  ; volatile unsigned long
FIO0_CLR0  	EQU (FIO0_BASE_ADDR + 0x01C)  ; volatile unsigned long
FIO0_CLR1  	EQU (FIO0_BASE_ADDR + 0x01D)  ; volatile unsigned long
FIO0_CLR2  	EQU (FIO0_BASE_ADDR + 0x01E)  ; volatile unsigned long
FIO0_CLR3  	EQU (FIO0_BASE_ADDR + 0x01F)  ; volatile unsigned long
FIO0_CLRL  	EQU (FIO0_BASE_ADDR + 0x01C)  ; volatile unsigned long
FIO0_CLRU  	EQU (FIO1_BASE_ADDR + 0x01E)  ; volatile unsigned long

;Fast IO PORT 1
FIO1_BASE_ADDR	EQU	0x3FFFC000
FIO1_DIR	EQU (FIO1_BASE_ADDR + 0x020)  ; volatile unsigned long
FIO1_DIR0	EQU (FIO1_BASE_ADDR + 0x020) ; volatile unsigned long
FIO1_DIR1	EQU (FIO1_BASE_ADDR + 0x021) ; volatile unsigned long
FIO1_DIR2	EQU (FIO1_BASE_ADDR + 0x022) ; volatile unsigned long
FIO1_DIR3	EQU (FIO1_BASE_ADDR + 0x023)  ; volatile unsigned long
FIO1_DIRL	EQU (FIO1_BASE_ADDR + 0x020)  ; volatile unsigned long
FIO1_DIRU	EQU (FIO1_BASE_ADDR + 0x022)  ; volatile unsigned long

FIO1_MASK  	EQU (FIO1_BASE_ADDR + 0x030)  ; volatile unsigned long
FIO1_MASK0 	EQU (FIO1_BASE_ADDR + 0x030)  ; volatile unsigned long
FIO1_MASK1 	EQU (FIO1_BASE_ADDR + 0x031)  ; volatile unsigned long
FIO1_MASK2 	EQU (FIO1_BASE_ADDR + 0x032)  ; volatile unsigned long
FIO1_MASK3 	EQU (FIO1_BASE_ADDR + 0x033)  ; volatile unsigned long
FIO1_MASKL 	EQU (FIO1_BASE_ADDR + 0x030)  ; volatile unsigned long
FIO1_MASKU 	EQU (FIO1_BASE_ADDR + 0x032)  ; volatile unsigned long

FIO1_PIN    EQU (FIO1_BASE_ADDR + 0x034)  ; volatile unsigned long
FIO1_PIN0   EQU (FIO1_BASE_ADDR + 0x034)  ; volatile unsigned long
FIO1_PIN1   EQU (FIO1_BASE_ADDR + 0x035)  ; volatile unsigned long
FIO1_PIN2   EQU (FIO1_BASE_ADDR + 0x036)  ; volatile unsigned long
FIO1_PIN3   EQU (FIO1_BASE_ADDR + 0x037)  ; volatile unsigned long
FIO1_PINL   EQU (FIO1_BASE_ADDR + 0x034)  ; volatile unsigned long
FIO1_PINU   EQU (FIO1_BASE_ADDR + 0x036)  ; volatile unsigned long

FIO1_SET	EQU (FIO1_BASE_ADDR + 0x038)  ; volatile unsigned long
FIO1_SET0	EQU (FIO1_BASE_ADDR + 0x038)  ; volatile unsigned long
FIO1_SET1	EQU (FIO1_BASE_ADDR + 0x039)  ; volatile unsigned long
FIO1_SET2	EQU (FIO1_BASE_ADDR + 0x03A)  ; volatile unsigned long
FIO1_SET3	EQU (FIO1_BASE_ADDR + 0x03B)  ; volatile unsigned long
FIO1_SETL	EQU (FIO1_BASE_ADDR + 0x038)  ; volatile unsigned long
FIO1_SETU	EQU (FIO1_BASE_ADDR + 0x03A)  ; volatile unsigned long

FIO1_CLR  	EQU (FIO1_BASE_ADDR + 0x03C)  ; volatile unsigned long
FIO1_CLR0  	EQU (FIO1_BASE_ADDR + 0x03C)  ; volatile unsigned long
FIO1_CLR1  	EQU (FIO1_BASE_ADDR + 0x03D)  ; volatile unsigned long
FIO1_CLR2  	EQU (FIO1_BASE_ADDR + 0x03E)  ; volatile unsigned long
FIO1_CLR3  	EQU (FIO1_BASE_ADDR + 0x03F)  ; volatile unsigned long
FIO1_CLRL  	EQU (FIO1_BASE_ADDR + 0x03C)  ; volatile unsigned long
FIO1_CLRU  	EQU (FIO1_BASE_ADDR + 0x03E)  ; volatile unsigned long
	
;Fast IO PORT 2
FIO2_BASE_ADDR	EQU	0x3FFFC000
FIO2_DIR	EQU (FIO2_BASE_ADDR + 0x040)  ; volatile unsigned long
FIO2_DIR0	EQU (FIO2_BASE_ADDR + 0x040) ; volatile unsigned long
FIO2_DIR1	EQU (FIO2_BASE_ADDR + 0x041) ; volatile unsigned long
FIO2_DIR2	EQU (FIO2_BASE_ADDR + 0x042) ; volatile unsigned long
FIO2_DIR3	EQU (FIO2_BASE_ADDR + 0x043)  ; volatile unsigned long
FIO2_DIRL	EQU (FIO2_BASE_ADDR + 0x040)  ; volatile unsigned long
FIO2_DIRU	EQU (FIO2_BASE_ADDR + 0x042)  ; volatile unsigned long

FIO2_MASK  	EQU (FIO2_BASE_ADDR + 0x050)  ; volatile unsigned long
FIO2_MASK0 	EQU (FIO2_BASE_ADDR + 0x050)  ; volatile unsigned long
FIO2_MASK1 	EQU (FIO2_BASE_ADDR + 0x051)  ; volatile unsigned long
FIO2_MASK2 	EQU (FIO2_BASE_ADDR + 0x052)  ; volatile unsigned long
FIO2_MASK3 	EQU (FIO2_BASE_ADDR + 0x053)  ; volatile unsigned long
FIO2_MASKL 	EQU (FIO2_BASE_ADDR + 0x050)  ; volatile unsigned long
FIO2_MASKU 	EQU (FIO2_BASE_ADDR + 0x052)  ; volatile unsigned long

FIO2_PIN    EQU (FIO2_BASE_ADDR + 0x054)  ; volatile unsigned long
FIO2_PIN0   EQU (FIO2_BASE_ADDR + 0x054)  ; volatile unsigned long
FIO2_PIN1   EQU (FIO2_BASE_ADDR + 0x055)  ; volatile unsigned long
FIO2_PIN2   EQU (FIO2_BASE_ADDR + 0x056)  ; volatile unsigned long
FIO2_PIN3   EQU (FIO2_BASE_ADDR + 0x057)  ; volatile unsigned long
FIO2_PINL   EQU (FIO2_BASE_ADDR + 0x054)  ; volatile unsigned long
FIO2_PINU   EQU (FIO2_BASE_ADDR + 0x056)  ; volatile unsigned long

FIO2_SET	EQU (FIO2_BASE_ADDR + 0x058)  ; volatile unsigned long
FIO2_SET0	EQU (FIO2_BASE_ADDR + 0x058)  ; volatile unsigned long
FIO2_SET1	EQU (FIO2_BASE_ADDR + 0x059)  ; volatile unsigned long
FIO2_SET2	EQU (FIO2_BASE_ADDR + 0x05A)  ; volatile unsigned long
FIO2_SET3	EQU (FIO2_BASE_ADDR + 0x05B)  ; volatile unsigned long
FIO2_SETL	EQU (FIO2_BASE_ADDR + 0x058)  ; volatile unsigned long
FIO2_SETU	EQU (FIO2_BASE_ADDR + 0x05A)  ; volatile unsigned long

FIO2_CLR  	EQU (FIO2_BASE_ADDR + 0x05C)  ; volatile unsigned long
FIO2_CLR0  	EQU (FIO2_BASE_ADDR + 0x05C)  ; volatile unsigned long
FIO2_CLR1  	EQU (FIO2_BASE_ADDR + 0x05D)  ; volatile unsigned long
FIO2_CLR2  	EQU (FIO2_BASE_ADDR + 0x05E)  ; volatile unsigned long
FIO2_CLR3  	EQU (FIO2_BASE_ADDR + 0x05F)  ; volatile unsigned long
FIO2_CLRL  	EQU (FIO2_BASE_ADDR + 0x05C)  ; volatile unsigned long
FIO2_CLRU  	EQU (FIO2_BASE_ADDR + 0x05E)  ; volatile unsigned long

;Fast IO PORT 3
FIO3_BASE_ADDR	EQU	0x3FFFC000
FIO3_DIR	EQU (FIO3_BASE_ADDR + 0x060)  ; volatile unsigned long
FIO3_DIR0	EQU (FIO3_BASE_ADDR + 0x060) ; volatile unsigned long
FIO3_DIR1	EQU (FIO3_BASE_ADDR + 0x061) ; volatile unsigned long
FIO3_DIR2	EQU (FIO3_BASE_ADDR + 0x062) ; volatile unsigned long
FIO3_DIR3	EQU (FIO3_BASE_ADDR + 0x063)  ; volatile unsigned long
FIO3_DIRL	EQU (FIO3_BASE_ADDR + 0x060)  ; volatile unsigned long
FIO3_DIRU	EQU (FIO3_BASE_ADDR + 0x062)  ; volatile unsigned long

FIO3_MASK  	EQU (FIO3_BASE_ADDR + 0x070)  ; volatile unsigned long
FIO3_MASK0 	EQU (FIO3_BASE_ADDR + 0x070)  ; volatile unsigned long
FIO3_MASK1 	EQU (FIO3_BASE_ADDR + 0x071)  ; volatile unsigned long
FIO3_MASK2 	EQU (FIO3_BASE_ADDR + 0x072)  ; volatile unsigned long
FIO3_MASK3 	EQU (FIO3_BASE_ADDR + 0x073)  ; volatile unsigned long
FIO3_MASKL 	EQU (FIO3_BASE_ADDR + 0x070)  ; volatile unsigned long
FIO3_MASKU 	EQU (FIO3_BASE_ADDR + 0x072)  ; volatile unsigned long

FIO3_PIN    EQU (FIO3_BASE_ADDR + 0x074)  ; volatile unsigned long
FIO3_PIN0   EQU (FIO3_BASE_ADDR + 0x074)  ; volatile unsigned long
FIO3_PIN1   EQU (FIO3_BASE_ADDR + 0x075)  ; volatile unsigned long
FIO3_PIN2   EQU (FIO3_BASE_ADDR + 0x076)  ; volatile unsigned long
FIO3_PIN3   EQU (FIO3_BASE_ADDR + 0x077)  ; volatile unsigned long
FIO3_PINL   EQU (FIO3_BASE_ADDR + 0x074)  ; volatile unsigned long
FIO3_PINU   EQU (FIO3_BASE_ADDR + 0x076)  ; volatile unsigned long

FIO3_SET	EQU (FIO3_BASE_ADDR + 0x078)  ; volatile unsigned long
FIO3_SET0	EQU (FIO3_BASE_ADDR + 0x078)  ; volatile unsigned long
FIO3_SET1	EQU (FIO3_BASE_ADDR + 0x079)  ; volatile unsigned long
FIO3_SET2	EQU (FIO3_BASE_ADDR + 0x07A)  ; volatile unsigned long
FIO3_SET3	EQU (FIO3_BASE_ADDR + 0x07B)  ; volatile unsigned long
FIO3_SETL	EQU (FIO3_BASE_ADDR + 0x078)  ; volatile unsigned long
FIO3_SETU	EQU (FIO3_BASE_ADDR + 0x07A)  ; volatile unsigned long

FIO3_CLR  	EQU (FIO3_BASE_ADDR + 0x07C)  ; volatile unsigned long
FIO3_CLR0  	EQU (FIO3_BASE_ADDR + 0x07C)  ; volatile unsigned long
FIO3_CLR1  	EQU (FIO3_BASE_ADDR + 0x07D)  ; volatile unsigned long
FIO3_CLR2  	EQU (FIO3_BASE_ADDR + 0x07E)  ; volatile unsigned long
FIO3_CLR3  	EQU (FIO3_BASE_ADDR + 0x07F)  ; volatile unsigned long
FIO3_CLRL  	EQU (FIO3_BASE_ADDR + 0x07C)  ; volatile unsigned long
FIO3_CLRU  	EQU (FIO1_BASE_ADDR + 0x07E)  ; volatile unsigned long

;Fast IO PORT 4
FIO4_BASE_ADDR	EQU	0x3FFFC000
FIO4_DIR	EQU (FIO4_BASE_ADDR + 0x080)  ; volatile unsigned long
FIO4_DIR0	EQU (FIO4_BASE_ADDR + 0x080) ; volatile unsigned long
FIO4_DIR1	EQU (FIO4_BASE_ADDR + 0x081) ; volatile unsigned long
FIO4_DIR2	EQU (FIO4_BASE_ADDR + 0x082) ; volatile unsigned long
FIO4_DIR3	EQU (FIO4_BASE_ADDR + 0x083)  ; volatile unsigned long
FIO4_DIRL	EQU (FIO4_BASE_ADDR + 0x080)  ; volatile unsigned long
FIO4_DIRU	EQU (FIO4_BASE_ADDR + 0x082)  ; volatile unsigned long

FIO4_MASK  	EQU (FIO4_BASE_ADDR + 0x090)  ; volatile unsigned long
FIO4_MASK0 	EQU (FIO4_BASE_ADDR + 0x090)  ; volatile unsigned long
FIO4_MASK1 	EQU (FIO4_BASE_ADDR + 0x091)  ; volatile unsigned long
FIO4_MASK2 	EQU (FIO4_BASE_ADDR + 0x092)  ; volatile unsigned long
FIO4_MASK3 	EQU (FIO4_BASE_ADDR + 0x093)  ; volatile unsigned long
FIO4_MASKL 	EQU (FIO4_BASE_ADDR + 0x090)  ; volatile unsigned long
FIO4_MASKU 	EQU (FIO4_BASE_ADDR + 0x092)  ; volatile unsigned long

FIO4_PIN    EQU (FIO4_BASE_ADDR + 0x094)  ; volatile unsigned long
FIO4_PIN0   EQU (FIO4_BASE_ADDR + 0x094)  ; volatile unsigned long
FIO4_PIN1   EQU (FIO4_BASE_ADDR + 0x095)  ; volatile unsigned long
FIO4_PIN2   EQU (FIO4_BASE_ADDR + 0x096)  ; volatile unsigned long
FIO4_PIN3   EQU (FIO4_BASE_ADDR + 0x097)  ; volatile unsigned long
FIO4_PINL   EQU (FIO4_BASE_ADDR + 0x094)  ; volatile unsigned long
FIO4_PINU   EQU (FIO4_BASE_ADDR + 0x096)  ; volatile unsigned long

FIO4_SET	EQU (FIO4_BASE_ADDR + 0x098)  ; volatile unsigned long
FIO4_SET0	EQU (FIO4_BASE_ADDR + 0x098)  ; volatile unsigned long
FIO4_SET1	EQU (FIO4_BASE_ADDR + 0x099)  ; volatile unsigned long
FIO4_SET2	EQU (FIO4_BASE_ADDR + 0x09A)  ; volatile unsigned long
FIO4_SET3	EQU (FIO4_BASE_ADDR + 0x09B)  ; volatile unsigned long
FIO4_SETL	EQU (FIO4_BASE_ADDR + 0x098)  ; volatile unsigned long
FIO4_SETU	EQU (FIO4_BASE_ADDR + 0x09A)  ; volatile unsigned long

FIO4_CLR  	EQU (FIO4_BASE_ADDR + 0x09C)  ; volatile unsigned long
FIO4_CLR0  	EQU (FIO4_BASE_ADDR + 0x09C)  ; volatile unsigned long
FIO4_CLR1  	EQU (FIO4_BASE_ADDR + 0x09D)  ; volatile unsigned long
FIO4_CLR2  	EQU (FIO4_BASE_ADDR + 0x09E)  ; volatile unsigned long
FIO4_CLR3  	EQU (FIO4_BASE_ADDR + 0x09F)  ; volatile unsigned long
FIO4_CLRL  	EQU (FIO4_BASE_ADDR + 0x09C)  ; volatile unsigned long
FIO4_CLRU  	EQU (FIO1_BASE_ADDR + 0x09E)  ; volatile unsigned long

	
;/****** Vectored Interrupt Controller (VIC) ******/
VIC_BASE_ADDR	EQU	0xFFFFF000
VIC_IRQStatus	EQU (VIC_BASE_ADDR + 0x000)  ; volatile unsigned long
VIC_FIQStatus  	EQU (VIC_BASE_ADDR + 0x004)  ; volatile unsigned long
VIC_RawIntr    	EQU (VIC_BASE_ADDR + 0x008)  ; volatile unsigned long
VIC_IntSelect  	EQU (VIC_BASE_ADDR + 0x00C)  ; volatile unsigned long
VIC_IntEnable  	EQU (VIC_BASE_ADDR + 0x010)  ; volatile unsigned long
VIC_IntEnClr   	EQU (VIC_BASE_ADDR + 0x014)  ; volatile unsigned long
VIC_SoftInt    	EQU (VIC_BASE_ADDR + 0x018)  ; volatile unsigned long
VIC_SoftIntClr 	EQU (VIC_BASE_ADDR + 0x01C)  ; volatile unsigned long
VIC_Protection 	EQU (VIC_BASE_ADDR + 0x020)  ; volatile unsigned long
VIC_SWPrioMask 	EQU (VIC_BASE_ADDR + 0x024)  ; volatile unsigned long
	
;Vector Addresse Registers 0-31
VIC_VectAddr0  	EQU (VIC_BASE_ADDR + 0x100)  ; volatile unsigned long
VIC_VectAddr1  	EQU (VIC_BASE_ADDR + 0x104)  ; volatile unsigned long
VIC_VectAddr2  	EQU (VIC_BASE_ADDR + 0x108)  ; volatile unsigned long
VIC_VectAddr3  	EQU (VIC_BASE_ADDR + 0x10C)  ; volatile unsigned long
VIC_VectAddr4  	EQU (VIC_BASE_ADDR + 0x110)  ; volatile unsigned long
VIC_VectAddr5  	EQU (VIC_BASE_ADDR + 0x114)  ; volatile unsigned long
VIC_VectAddr6  	EQU (VIC_BASE_ADDR + 0x118)  ; volatile unsigned long
VIC_VectAddr7  	EQU (VIC_BASE_ADDR + 0x11C)  ; volatile unsigned long
VIC_VectAddr8  	EQU (VIC_BASE_ADDR + 0x120)  ; volatile unsigned long
VIC_VectAddr9  	EQU (VIC_BASE_ADDR + 0x124)  ; volatile unsigned long
VIC_VectAddr10  EQU (VIC_BASE_ADDR + 0x128)  ; volatile unsigned long
VIC_VectAddr11  EQU (VIC_BASE_ADDR + 0x12C)  ; volatile unsigned long
VIC_VectAddr12  EQU (VIC_BASE_ADDR + 0x130)  ; volatile unsigned long
VIC_VectAddr13  EQU (VIC_BASE_ADDR + 0x134)  ; volatile unsigned long
VIC_VectAddr14  EQU (VIC_BASE_ADDR + 0x138)  ; volatile unsigned long
VIC_VectAddr15  EQU (VIC_BASE_ADDR + 0x13C)  ; volatile unsigned long
VIC_VectAddr16  EQU (VIC_BASE_ADDR + 0x140)  ; volatile unsigned long
VIC_VectAddr17  EQU (VIC_BASE_ADDR + 0x144)  ; volatile unsigned long
VIC_VectAddr18  EQU (VIC_BASE_ADDR + 0x148)  ; volatile unsigned long
VIC_VectAddr19  EQU (VIC_BASE_ADDR + 0x14C)  ; volatile unsigned long
VIC_VectAddr20  EQU (VIC_BASE_ADDR + 0x150)  ; volatile unsigned long
VIC_VectAddr21  EQU (VIC_BASE_ADDR + 0x154)  ; volatile unsigned long
VIC_VectAddr22  EQU (VIC_BASE_ADDR + 0x158)  ; volatile unsigned long
VIC_VectAddr23  EQU (VIC_BASE_ADDR + 0x15C)  ; volatile unsigned long
VIC_VectAddr24  EQU (VIC_BASE_ADDR + 0x160)  ; volatile unsigned long
VIC_VectAddr25  EQU (VIC_BASE_ADDR + 0x164)  ; volatile unsigned long
VIC_VectAddr26  EQU (VIC_BASE_ADDR + 0x168)  ; volatile unsigned long
VIC_VectAddr27  EQU (VIC_BASE_ADDR + 0x16C)  ; volatile unsigned long
VIC_VectAddr28  EQU (VIC_BASE_ADDR + 0x170)  ; volatile unsigned long
VIC_VectAddr29  EQU (VIC_BASE_ADDR + 0x174)  ; volatile unsigned long
VIC_VectAddr30  EQU (VIC_BASE_ADDR + 0x178)  ; volatile unsigned long
VIC_VectAddr31  EQU (VIC_BASE_ADDR + 0x17C)  ; volatile unsigned long
			  
;Vector Priority Registers 0-31
VIC_VectPrio0  	EQU (VIC_BASE_ADDR + 0x200)  ; volatile unsigned long
VIC_VectPrio1  	EQU (VIC_BASE_ADDR + 0x204)  ; volatile unsigned long
VIC_VectPrio2  	EQU (VIC_BASE_ADDR + 0x208)  ; volatile unsigned long
VIC_VectPrio3  	EQU (VIC_BASE_ADDR + 0x20C)  ; volatile unsigned long
VIC_VectPrio4  	EQU (VIC_BASE_ADDR + 0x210)  ; volatile unsigned long
VIC_VectPrio5  	EQU (VIC_BASE_ADDR + 0x214)  ; volatile unsigned long
VIC_VectPrio6  	EQU (VIC_BASE_ADDR + 0x218)  ; volatile unsigned long
VIC_VectPrio7  	EQU (VIC_BASE_ADDR + 0x21C)  ; volatile unsigned long
VIC_VectPrio8  	EQU (VIC_BASE_ADDR + 0x220)  ; volatile unsigned long
VIC_VectPrio9  	EQU (VIC_BASE_ADDR + 0x224)  ; volatile unsigned long
VIC_VectPrio10  EQU (VIC_BASE_ADDR + 0x228)  ; volatile unsigned long
VIC_VectPrio11  EQU (VIC_BASE_ADDR + 0x22C)  ; volatile unsigned long
VIC_VectPrio12  EQU (VIC_BASE_ADDR + 0x230)  ; volatile unsigned long
VIC_VectPrio13  EQU (VIC_BASE_ADDR + 0x234)  ; volatile unsigned long
VIC_VectPrio14  EQU (VIC_BASE_ADDR + 0x238)  ; volatile unsigned long
VIC_VectPrio15  EQU (VIC_BASE_ADDR + 0x23C)  ; volatile unsigned long
VIC_VectPrio16  EQU (VIC_BASE_ADDR + 0x240)  ; volatile unsigned long
VIC_VectPrio17  EQU (VIC_BASE_ADDR + 0x244)  ; volatile unsigned long
VIC_VectPrio18  EQU (VIC_BASE_ADDR + 0x248)  ; volatile unsigned long
VIC_VectPrio19  EQU (VIC_BASE_ADDR + 0x24C)  ; volatile unsigned long
VIC_VectPrio20  EQU (VIC_BASE_ADDR + 0x250)  ; volatile unsigned long
VIC_VectPrio21  EQU (VIC_BASE_ADDR + 0x254)  ; volatile unsigned long
VIC_VectPrio22  EQU (VIC_BASE_ADDR + 0x258)  ; volatile unsigned long
VIC_VectPrio23  EQU (VIC_BASE_ADDR + 0x25C)  ; volatile unsigned long
VIC_VectPrio24  EQU (VIC_BASE_ADDR + 0x260)  ; volatile unsigned long
VIC_VectPrio25  EQU (VIC_BASE_ADDR + 0x264)  ; volatile unsigned long
VIC_VectPrio26  EQU (VIC_BASE_ADDR + 0x268)  ; volatile unsigned long
VIC_VectPrio27  EQU (VIC_BASE_ADDR + 0x26C)  ; volatile unsigned long
VIC_VectPrio28  EQU (VIC_BASE_ADDR + 0x270)  ; volatile unsigned long
VIC_VectPrio29  EQU (VIC_BASE_ADDR + 0x274)  ; volatile unsigned long
VIC_VectPrio30  EQU (VIC_BASE_ADDR + 0x278)  ; volatile unsigned long
VIC_VectPrio31  EQU (VIC_BASE_ADDR + 0x27C)  ; volatile unsigned long
	
VIC_VectAddr	EQU (VIC_BASE_ADDR + 0xF00)  ; volatile unsigned long
	
;* Pin Connect Block Register Map *
PIN_SEL_BASE_ADDR     EQU	0xE002C000
PIN_SEL0	EQU (PIN_SEL_BASE_ADDR + 0x00)  ; volatile unsigned long
PIN_SEL1	EQU (PIN_SEL_BASE_ADDR + 0x04)  ; volatile unsigned long
PIN_SEL2	EQU (PIN_SEL_BASE_ADDR + 0x08)  ; volatile unsigned long
PIN_SEL3	EQU (PIN_SEL_BASE_ADDR + 0x0C)  ; volatile unsigned long
PIN_SEL4	EQU (PIN_SEL_BASE_ADDR + 0x10)  ; volatile unsigned long
PIN_SEL5	EQU (PIN_SEL_BASE_ADDR + 0x14)  ; volatile unsigned long
PIN_SEL6	EQU (PIN_SEL_BASE_ADDR + 0x18)  ; volatile unsigned long
PIN_SEL7	EQU (PIN_SEL_BASE_ADDR + 0x1C)  ; volatile unsigned long
PIN_SEL8	EQU (PIN_SEL_BASE_ADDR + 0x20)  ; volatile unsigned long
PIN_SEL9	EQU (PIN_SEL_BASE_ADDR + 0x24)  ; volatile unsigned long
PIN_SEL10	EQU (PIN_SEL_BASE_ADDR + 0x28)  ; volatile unsigned long

PIN_MODE0	EQU (PIN_SEL_BASE_ADDR + 0x40)  ; volatile unsigned long
PIN_MODE1	EQU (PIN_SEL_BASE_ADDR + 0x44)  ; volatile unsigned long
PIN_MODE2	EQU (PIN_SEL_BASE_ADDR + 0x48)  ; volatile unsigned long
PIN_MODE3	EQU (PIN_SEL_BASE_ADDR + 0x4C)  ; volatile unsigned long
PIN_MODE4	EQU (PIN_SEL_BASE_ADDR + 0x50)  ; volatile unsigned long
PIN_MODE5	EQU (PIN_SEL_BASE_ADDR + 0x54)  ; volatile unsigned long
PIN_MODE6	EQU (PIN_SEL_BASE_ADDR + 0x58)  ; volatile unsigned long
PIN_MODE7	EQU (PIN_SEL_BASE_ADDR + 0x5C)  ; volatile unsigned long
PIN_MODE8	EQU (PIN_SEL_BASE_ADDR + 0x60)  ; volatile unsigned long
PIN_MODE9	EQU (PIN_SEL_BASE_ADDR + 0x64)  ; volatile unsigned long

;* Universal Asynchronous Receiver Transmitter 0 (UART0) *
UART0_BASE_ADDR	EQU	0xE000C000
U0RBR	EQU (UART0_BASE_ADDR + 0x00)  ; volatile unsigned long
U0THR	EQU (UART0_BASE_ADDR + 0x00)  ; volatile unsigned long
U0DLL	EQU (UART0_BASE_ADDR + 0x00)  ; volatile unsigned long
U0DLM	EQU (UART0_BASE_ADDR + 0x04)  ; volatile unsigned long
U0IER	EQU (UART0_BASE_ADDR + 0x04)  ; volatile unsigned long
U0IIR	EQU (UART0_BASE_ADDR + 0x08)  ; volatile unsigned long
U0FCR	EQU (UART0_BASE_ADDR + 0x08)  ; volatile unsigned long
U0LCR	EQU (UART0_BASE_ADDR + 0x0C)  ; volatile unsigned long
U0LSR	EQU (UART0_BASE_ADDR + 0x14)  ; volatile unsigned long
U0SCR	EQU (UART0_BASE_ADDR + 0x1C)  ; volatile unsigned long
U0ACR	EQU (UART0_BASE_ADDR + 0x20)  ; volatile unsigned long
U0ICR	EQU (UART0_BASE_ADDR + 0x24)  ; volatile unsigned long
U0FDR	EQU (UART0_BASE_ADDR + 0x28)  ; volatile unsigned long
U0TER	EQU (UART0_BASE_ADDR + 0x30)  ; volatile unsigned long
	
;* Universal Asynchronous Receiver Transmitter 1 (UART1) *
UART1_BASE_ADDR	EQU	0xE0010000
U1RBR	EQU (UART1_BASE_ADDR + 0x00)  ; volatile unsigned long
U1THR	EQU (UART1_BASE_ADDR + 0x00)  ; volatile unsigned long
U1DLL	EQU (UART1_BASE_ADDR + 0x00)  ; volatile unsigned long
U1DLM	EQU (UART1_BASE_ADDR + 0x04)  ; volatile unsigned long
U1IER	EQU (UART1_BASE_ADDR + 0x04)  ; volatile unsigned long
U1IIR	EQU (UART1_BASE_ADDR + 0x08)  ; volatile unsigned long
U1FCR	EQU (UART1_BASE_ADDR + 0x08)  ; volatile unsigned long
U1LCR	EQU (UART1_BASE_ADDR + 0x0C)  ; volatile unsigned long
U1MCR	EQU (UART1_BASE_ADDR + 0x10)  ; volatile unsigned long
U1LSR	EQU (UART1_BASE_ADDR + 0x14)  ; volatile unsigned long
U1MSR	EQU (UART1_BASE_ADDR + 0x18)  ; volatile unsigned long
U1SCR 	EQU (UART1_BASE_ADDR + 0x1C)  ; volatile unsigned long
U1ACR	EQU (UART1_BASE_ADDR + 0x20)  ; volatile unsigned long
U1FDR	EQU (UART1_BASE_ADDR + 0x28)  ; volatile unsigned long
U1TER	EQU (UART1_BASE_ADDR + 0x30)  ; volatile unsigned long

;* Universal Asynchronous Receiver Transmitter 2 (UART2) *
UART2_BASE_ADDR	EQU	0xE0078000
U2RBR	EQU (UART2_BASE_ADDR + 0x00)  ; volatile unsigned long
U2THR	EQU (UART2_BASE_ADDR + 0x00)  ; volatile unsigned long
U2DLL	EQU (UART2_BASE_ADDR + 0x00)  ; volatile unsigned long
U2DLM	EQU (UART2_BASE_ADDR + 0x04)  ; volatile unsigned long
U2IER	EQU (UART2_BASE_ADDR + 0x04)  ; volatile unsigned long
U2IIR	EQU (UART2_BASE_ADDR + 0x08)  ; volatile unsigned long
U2FCR	EQU (UART2_BASE_ADDR + 0x08)  ; volatile unsigned long
U2LCR	EQU (UART2_BASE_ADDR + 0x0C)  ; volatile unsigned long
U2LSR	EQU (UART2_BASE_ADDR + 0x14)  ; volatile unsigned long
U2SCR	EQU (UART2_BASE_ADDR + 0x1C)  ; volatile unsigned long
U2ACR	EQU (UART2_BASE_ADDR + 0x20)  ; volatile unsigned long
U2ICR	EQU (UART2_BASE_ADDR + 0x24)  ; volatile unsigned long
U2FDR	EQU (UART2_BASE_ADDR + 0x28)  ; volatile unsigned long
U2TER	EQU (UART2_BASE_ADDR + 0x30)  ; volatile unsigned long
	
;* Universal Asynchronous Receiver Transmitter 3 (UART3) *
UART3_BASE_ADDR	EQU	0xE007C000
U3RBR	EQU (UART3_BASE_ADDR + 0x00)  ; volatile unsigned long
U3THR	EQU (UART3_BASE_ADDR + 0x00)  ; volatile unsigned long
U3DLL	EQU (UART3_BASE_ADDR + 0x00)  ; volatile unsigned long
U3DLM	EQU (UART3_BASE_ADDR + 0x04)  ; volatile unsigned long
U3IER	EQU (UART3_BASE_ADDR + 0x04)  ; volatile unsigned long
U3IIR	EQU (UART3_BASE_ADDR + 0x08)  ; volatile unsigned long
U3FCR	EQU (UART3_BASE_ADDR + 0x08)  ; volatile unsigned long
U3LCR	EQU (UART3_BASE_ADDR + 0x0C)  ; volatile unsigned long
U3LSR	EQU (UART3_BASE_ADDR + 0x14)  ; volatile unsigned long
U3SCR	EQU (UART3_BASE_ADDR + 0x1C)  ; volatile unsigned long
U3ACR	EQU (UART3_BASE_ADDR + 0x20)  ; volatile unsigned long
U3ICR	EQU (UART3_BASE_ADDR + 0x24)  ; volatile unsigned long
U3FDR	EQU (UART3_BASE_ADDR + 0x28)  ; volatile unsigned long
U3TER	EQU (UART3_BASE_ADDR + 0x30)  ; volatile unsigned long

;* Timer 0 *
TMR0_BASE_ADDR	EQU	0xE0004000
T0IR	EQU (TMR0_BASE_ADDR + 0x00)  ; volatile unsigned long
T0TCR	EQU (TMR0_BASE_ADDR + 0x04)  ; volatile unsigned long
T0TC	EQU (TMR0_BASE_ADDR + 0x08)  ; volatile unsigned long
T0PR	EQU (TMR0_BASE_ADDR + 0x0C)  ; volatile unsigned long
T0PC	EQU (TMR0_BASE_ADDR + 0x10)  ; volatile unsigned long
T0MCR	EQU (TMR0_BASE_ADDR + 0x14)  ; volatile unsigned long
T0MR0	EQU (TMR0_BASE_ADDR + 0x18)  ; volatile unsigned long
T0MR1	EQU (TMR0_BASE_ADDR + 0x1C)  ; volatile unsigned long
T0MR2	EQU (TMR0_BASE_ADDR + 0x20)  ; volatile unsigned long
T0MR3	EQU (TMR0_BASE_ADDR + 0x24)  ; volatile unsigned long
T0CCR	EQU (TMR0_BASE_ADDR + 0x28)  ; volatile unsigned long
T0CR0	EQU (TMR0_BASE_ADDR + 0x2C)  ; volatile unsigned long
T0CR1	EQU (TMR0_BASE_ADDR + 0x30)  ; volatile unsigned long
T0CR2	EQU (TMR0_BASE_ADDR + 0x34)  ; volatile unsigned long
T0CR3	EQU (TMR0_BASE_ADDR + 0x38)  ; volatile unsigned long
T0EMR	EQU (TMR0_BASE_ADDR + 0x3C)  ; volatile unsigned long
T0CTCR	EQU (TMR0_BASE_ADDR + 0x70)  ; volatile unsigned long
	
;* Timer 1 *
TMR1_BASE_ADDR	EQU	0xE0008000
T1IR	EQU (TMR1_BASE_ADDR + 0x00)  ; volatile unsigned long
T1TCR	EQU (TMR1_BASE_ADDR + 0x04)  ; volatile unsigned long
T1TC	EQU (TMR1_BASE_ADDR + 0x08)  ; volatile unsigned long
T1PR	EQU (TMR1_BASE_ADDR + 0x0C)  ; volatile unsigned long
T1PC	EQU (TMR1_BASE_ADDR + 0x10)  ; volatile unsigned long
T1MCR	EQU (TMR1_BASE_ADDR + 0x14)  ; volatile unsigned long
T1MR0	EQU (TMR1_BASE_ADDR + 0x18)  ; volatile unsigned long
T1MR1	EQU (TMR1_BASE_ADDR + 0x1C)  ; volatile unsigned long
T1MR2	EQU (TMR1_BASE_ADDR + 0x20)  ; volatile unsigned long
T1MR3	EQU (TMR1_BASE_ADDR + 0x24)  ; volatile unsigned long
T1CCR	EQU (TMR1_BASE_ADDR + 0x28)  ; volatile unsigned long
T1CR0	EQU (TMR1_BASE_ADDR + 0x2C)  ; volatile unsigned long
T1CR1	EQU (TMR1_BASE_ADDR + 0x30)  ; volatile unsigned long
T1CR2	EQU (TMR1_BASE_ADDR + 0x34)  ; volatile unsigned long
T1CR3	EQU (TMR1_BASE_ADDR + 0x38)  ; volatile unsigned long
T1EMR	EQU (TMR1_BASE_ADDR + 0x3C)  ; volatile unsigned long
T1CTCR	EQU (TMR1_BASE_ADDR + 0x70)  ; volatile unsigned long
	
;* Timer 2 *
TMR2_BASE_ADDR	EQU	0xE0070000
T2IR	EQU (TMR2_BASE_ADDR + 0x00)  ; volatile unsigned long  
T2TCR	EQU (TMR2_BASE_ADDR + 0x04)  ; volatile unsigned long 
T2TC	EQU (TMR2_BASE_ADDR + 0x08)  ; volatile unsigned long  
T2PR	EQU (TMR2_BASE_ADDR + 0x0C)  ; volatile unsigned long  
T2PC	EQU (TMR2_BASE_ADDR + 0x10)  ; volatile unsigned long  
T2MCR	EQU (TMR2_BASE_ADDR + 0x14)  ; volatile unsigned long 
T2MR0	EQU (TMR2_BASE_ADDR + 0x18)  ; volatile unsigned long 
T2MR1	EQU (TMR2_BASE_ADDR + 0x1C)  ; volatile unsigned long 
T2MR2	EQU (TMR2_BASE_ADDR + 0x20)  ; volatile unsigned long 
T2MR3	EQU (TMR2_BASE_ADDR + 0x24)  ; volatile unsigned long 
T2CCR	EQU (TMR2_BASE_ADDR + 0x28)  ; volatile unsigned long 
T2CR0	EQU (TMR2_BASE_ADDR + 0x2C)  ; volatile unsigned long
T2CR1	EQU (TMR2_BASE_ADDR + 0x30)  ; volatile unsigned long
T2CR2	EQU (TMR2_BASE_ADDR + 0x34)  ; volatile unsigned long 
T2CR3	EQU (TMR2_BASE_ADDR + 0x38)  ; volatile unsigned long 
T2EMR	EQU (TMR2_BASE_ADDR + 0x3C)  ; volatile unsigned long 
T2CTCR	EQU (TMR2_BASE_ADDR + 0x70)  ; volatile unsigned long
	
;* Timer 3 *
TMR3_BASE_ADDR	EQU	0xE0074000
T3IR	EQU (TMR3_BASE_ADDR + 0x00)  ; volatile unsigned long
T3TCR	EQU (TMR3_BASE_ADDR + 0x04)  ; volatile unsigned long
T3TC	EQU (TMR3_BASE_ADDR + 0x08)  ; volatile unsigned long
T3PR	EQU (TMR3_BASE_ADDR + 0x0C)  ; volatile unsigned long
T3PC	EQU (TMR3_BASE_ADDR + 0x10)  ; volatile unsigned long
T3MCR	EQU (TMR3_BASE_ADDR + 0x14)  ; volatile unsigned long
T3MR0	EQU (TMR3_BASE_ADDR + 0x18)  ; volatile unsigned long
T3MR1	EQU (TMR3_BASE_ADDR + 0x1C)  ; volatile unsigned long
T3MR2	EQU (TMR3_BASE_ADDR + 0x20)  ; volatile unsigned long
T3MR3	EQU (TMR3_BASE_ADDR + 0x24)  ; volatile unsigned long
T3CCR	EQU (TMR3_BASE_ADDR + 0x28)  ; volatile unsigned long
T3CR0	EQU (TMR3_BASE_ADDR + 0x2C)  ; volatile unsigned long
T3CR1	EQU (TMR3_BASE_ADDR + 0x30)  ; volatile unsigned long
T3CR2	EQU (TMR3_BASE_ADDR + 0x34)  ; volatile unsigned long
T3CR3	EQU (TMR3_BASE_ADDR + 0x38)  ; volatile unsigned long
T3EMR	EQU (TMR3_BASE_ADDR + 0x3C)  ; volatile unsigned long
T3CTCR	EQU (TMR3_BASE_ADDR + 0x70)  ; volatile unsigned long
	
;* A/D Converter Registers *
AD0_BASE_ADDR	EQU	0xE0034000
AD0CR		EQU (AD0_BASE_ADDR + 0x00)  ; volatile unsigned long
AD0GDR		EQU (AD0_BASE_ADDR + 0x04)  ; volatile unsigned long
AD0INTEN	EQU (AD0_BASE_ADDR + 0x0C)  ; volatile unsigned long
AD0DR0		EQU (AD0_BASE_ADDR + 0x10)  ; volatile unsigned long
AD0DR1		EQU (AD0_BASE_ADDR + 0x14)  ; volatile unsigned long
AD0DR2		EQU (AD0_BASE_ADDR + 0x18)  ; volatile unsigned long
AD0DR3		EQU (AD0_BASE_ADDR + 0x1C)  ; volatile unsigned long
AD0DR4		EQU (AD0_BASE_ADDR + 0x20)  ; volatile unsigned long
AD0DR5		EQU (AD0_BASE_ADDR + 0x24)  ; volatile unsigned long
AD0DR6		EQU (AD0_BASE_ADDR + 0x28)  ; volatile unsigned long
AD0DR7		EQU (AD0_BASE_ADDR + 0x2C)  ; volatile unsigned long
AD0STAT		EQU (AD0_BASE_ADDR + 0x30)  ; volatile unsigned long
   
	ENDIF
   	END