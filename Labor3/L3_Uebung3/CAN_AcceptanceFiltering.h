
#include <stdint.h>   

/*********************************************************************************
		CAN-related Acceptance Filtering
**********************************************************************************/
/*  Settings related to CAN1 Controller  */
const uint32_t  CAN1_Number_FullCAN_ID = 1;
const uint16_t  CAN1_Array_FullCAN_IDs[CAN1_Number_FullCAN_ID] = {0xFFF};
const uint32_t  CAN1_Number_SFF_EXP_ID = 3;
const uint16_t  CAN1_Array_SFF_EXP_IDs[CAN1_Number_SFF_EXP_ID] = {0x100, 0x456, 0x654};
const uint32_t  CAN1_Number_GRP_SFF_ID =2;
const uint16_t  CAN1_Array_GRP_SFF_IDs[CAN1_Number_GRP_SFF_ID][2] = {{0x700, 0x7FF},{0x900,0x9FF}};
const uint32_t  CAN1_Number_EXP_EXT_ID = 2;
const uint32_t  CAN1_Array_EXP_EXT_IDs[CAN1_Number_EXP_EXT_ID] = {0x123456, 0xABCDEF};
const uint32_t  CAN1_Number_GRP_EXT_ID = 2;
const uint32_t  CAN1_Array_GRP_EXT_IDs[CAN1_Number_GRP_EXT_ID][2] = {{0xAAA700, 0xAAA7FF},{0xBBB900,0xBBB9FF}};

/*  Settings related to CAN2 Controller  */
const uint32_t  CAN2_Number_FullCAN_ID = 2;
const uint16_t  CAN2_Array_FullCAN_IDs[CAN2_Number_FullCAN_ID] = {0x111,0x222};
const uint32_t  CAN2_Number_SFF_EXP_ID = 3;
const uint16_t  CAN2_Array_SFF_EXP_IDs[CAN2_Number_SFF_EXP_ID] = {0x222,0x456, 0x444};
const uint32_t  CAN2_Number_GRP_SFF_ID = 2;
const uint16_t  CAN2_Array_GRP_SFF_IDs[CAN2_Number_GRP_SFF_ID][2] = {{0xC00,0xCFF},{0x001,0x0FF}};
const uint32_t  CAN2_Number_EXP_EXT_ID = 2;
const uint32_t  CAN2_Array_EXP_EXT_IDs[CAN2_Number_EXP_EXT_ID] = {0x1111111, 0x1222222};
const uint32_t  CAN2_Number_GRP_EXT_ID = 2;
const uint32_t  CAN2_Array_GRP_EXT_IDs[CAN2_Number_GRP_EXT_ID][2] = {{0x1000000,0x1000FFF},{0x10004000,0x10004FFF}};
