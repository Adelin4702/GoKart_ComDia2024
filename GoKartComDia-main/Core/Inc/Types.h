/*
 * Types.h
 *
 *  Created on: Sep 20, 2023
 *      Author: FER3CLJ
 */

#ifndef INC_TYPES_H_
#define INC_TYPES_H_

#include "main.h"
#include "usb_host.h"
#include <Constants.h>

/* GENERAL-PURPOSE TYPES */

// General-purpose error/status flag, value should be 0 or 1
typedef uint8_t ComDia_StatusFlag;

/* CANDRV-SPECIFIC Types */

typedef uint8_t Can_Payload;
// Standard ID for CAN frame
// Standard ID is 11 bits long, but STM32 specifies its use by 32-bit unsigned integers
typedef uint32_t Can_StdId;
// CAN Mailbox
typedef uint32_t Can_Mailbox;
// CAN Message length
typedef uint32_t Can_MessageLength;

/* CANIF-SPECIFIC TYPES */

// Mapping the CAN Driver payload to a CAN Interface payload
typedef Can_Payload CanIf_Payload;
// 16-bit unsigned integer since the CAN Standard ID is 11-bits long
typedef uint16_t CanIf_StdId;
// 8-bit unsigned integer since the CAN message length doesn't go above 8 for non-extended frames
typedef uint8_t CanIf_MessageLength;

/* CANTP-SPECIFIC TYPES */

// Mapping the CAN Driver payload to a CAN Tp payload
typedef CanIf_Payload CanTp_Payload;

typedef CanIf_StdId CanTp_StdId;

typedef uint8_t CanTp_MessageLength;

typedef struct
{
	CanTp_StdId id;
    CanTp_MessageLength length;
    CanTp_Payload data[8];
} CanTp_Frame;

/* DCM-SPECIFIC TYPES */
typedef uint8_t Dcm_MessageLength;
typedef uint8_t Dcm_MessageData;
typedef struct
{
	Dcm_MessageLength length;
	Dcm_MessageData data[8];
} Dcm_Message;

typedef struct
{
	uint16_t id;
	uint8_t dataLength;
	uint8_t data[30];
	uint8_t securityLevel;
	uint8_t supportedSessionsMask;
	uint8_t scalingFunction;
} Dcm_DID;
typedef uint8_t Dcm_Service_ResponseCode;


typedef struct
{
	uint8_t id;
    uint8_t secured;
} Dcm_Reset;

//typedef struct
//{
//	uint16_t id;
//	uint8_t statusMask;
//	uint8_t dataLength;
//	uint8_t *snapData;
//}Dcm_DTC;
//
//#define MAX_SNAPSHOTS 10
//typedef struct {
//    uint8_t snapData[2];
//} Snapshot;

//typedef struct {
//	uint32_t id;
//	uint8_t statusMask;
//	struct node_Snapshot *startSnapList;
//	Snapshot snapshots[MAX_SNAPSHOTS];
//	uint8_t nrSnapshots;
//	uint8_t statusAvailabilityMask;
//	uint8_t priority;  // 0x01 high; 0x02 medium; 0x03 low
//	uint32_t groupOfDTC;
//} Dcm_DTC1;




/* STM32 ABSTRACT TYPES */

// CAN Controller Instance
typedef CAN_HandleTypeDef Can_ControllerInstance;
// CAN filter
typedef CAN_FilterTypeDef Can_Filter;
// CAN TxHeader
typedef CAN_TxHeaderTypeDef Can_TxHeader;
// CAN RxHeader
typedef CAN_RxHeaderTypeDef Can_RxHeader;

#endif /* INC_TYPES_H_ */
