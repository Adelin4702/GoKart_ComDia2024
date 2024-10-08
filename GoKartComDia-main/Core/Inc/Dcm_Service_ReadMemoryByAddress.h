/*
 * Dcm_Service_ReadMemoryByAddress.h
 *
 *  Created on: Oct 24, 2023
 *      Author: FER3CLJ
 */

#ifndef INC_DCM_SERVICE_READMEMORYBYADDRESS_H_
#define INC_DCM_SERVICE_READMEMORYBYADDRESS_H_
#define NEGATIVE_RESPONSE_SID 0x7F

#include <stdint.h>

uint8_t Dcm_Service_ReadMemoryByAddress(uint8_t *requestMessageData, uint8_t requestMessageLength, uint8_t *responseData, uint8_t *responseDataLength);

#endif /* INC_DCM_SERVICE_READMEMORYBYADDRESS_H_ */
