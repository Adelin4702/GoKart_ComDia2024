/*
 * Dcm_Service_CommunicationControl.h
 *
 *  Created on: Sep 4, 2024
 *      Author: MTA6CLJ
 */

#ifndef INC_DCM_SERVICE_COMMUNICATIONCONTROL_H_
#define INC_DCM_SERVICE_COMMUNICATIONCONTROL_H_


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <Constants.h>

///sub-function -> controlType
#define enableRxAndTx 0x00
#define enableRxAndDisableTx 0x01
#define disableRxAndEnableTx 0x02
#define disableRxAndTx 0x03


///communication type
#define normalCommunicationMessages 0x01


uint8_t Dcm_Service_CommunicationControl(uint8_t *requestMessageData, uint8_t requestMessageLength, uint8_t *responseData, uint8_t *responseDataLength);

#endif /* INC_DCM_SERVICE_COMMUNICATIONCONTROL_H_ */
