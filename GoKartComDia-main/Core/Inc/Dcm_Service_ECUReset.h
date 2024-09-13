/*
 * Dcm_Service_ECUReset.h
 *
 *  Created on: Sep 5, 2024
 *      Author: PRP3CLJ
 */
#include <Types.h>

#ifndef INC_DCM_SERVICE_ECURESET_H_
#define INC_DCM_SERVICE_ECURESET_H_

//Reset modes
#define DCM_RESET_HARD_RESET 0x01
#define DCM_RESET_KEY_OFF_ON_RESET 0x02
#define DCM_RESET_SOFT_RESET 0x03
#define DCM_RESET_ENABLE_RAPID_POWER_SHUTDOWN 0x04
#define DCM_RESET_DISABLE_RAPID_POWER_SHUTDOWN 0x05

#define NR_OF_TYPES_OF_RESET 0x05
void Dcm_Reset_Init();
uint8_t Dcm_Service_ECUReset(uint8_t *requestMessageData, uint8_t requestMessageLength, uint8_t *responseData, uint8_t *responseDataLength);

#endif /* INC_DCM_SERVICE_ECURESET_H_ */
