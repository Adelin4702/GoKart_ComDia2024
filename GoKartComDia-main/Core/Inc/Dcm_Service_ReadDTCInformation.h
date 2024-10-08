/*
 * Dcm_Service_ReadDTCInformation.h
 *
 *  Created on: Oct 24, 2023
 *      Author: FER3CLJ
 */

#ifndef INC_DCM_SERVICE_READDTCINFORMATION_H_
#define INC_DCM_SERVICE_READDTCINFORMATION_H_

#include <stdint.h>
#include <Types.h>

void Dcm_DTC_Init();
uint8_t Dcm_Service_ReadDTCInformation(uint8_t *requestMessageData, uint8_t requestMessageLength, uint8_t *responseData, uint8_t *responseDataLength);

#endif /* INC_DCM_SERVICE_READDTCINFORMATION_H_ */
