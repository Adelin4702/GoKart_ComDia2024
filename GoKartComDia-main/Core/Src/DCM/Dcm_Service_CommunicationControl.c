/*
 * Dcm_Service_CommunicationControl.c
 *
 *  Created on: Sep 4, 2024
 *      Author: MTA6CLJ
 */

///we are working with a single ECU => communicationType -> normal communication messages

#include <Dcm_Service_CommunicationControl.h>

extern uint8_t statusTx;
extern uint8_t statusRx;

uint8_t Dcm_Service_CommunicationControl(uint8_t *requestMessageData, uint8_t requestMessageLength, uint8_t *responseData, uint8_t *responseDataLength)
{
	uint8_t controlType = requestMessageData[1];
	uint8_t communicationType = requestMessageData[2];

	if(requestMessageLength != 3)
	{
		return DCM_SERVICE_NRC_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT;
	}
	uint8_t responseIndex = 0;
	responseData[responseIndex++] = DCM_SERVICE_ID_COMMUNICATION_CONTROL;

	if(communicationType != normalCommunicationMessages)
	{
		return DCM_NRC_REQUEST_OUT_OF_RANGE;
	}

	switch(controlType)
	{
		case enableRxAndTx:
			statusTx = ENABLE_COMM;
			statusRx = ENABLE_COMM;
			break;
		case enableRxAndDisableTx:
			 statusTx = DISABLE_COMM;
			 statusRx = ENABLE_COMM;
			 break;
		case disableRxAndEnableTx:
			 statusTx = ENABLE_COMM;
			 statusRx = DISABLE_COMM;
			 break;
		case disableRxAndTx:
			 statusTx = DISABLE_COMM;
			 statusRx = DISABLE_COMM;
			 break;
		 default:
		   ///if the sub-function (controlType) parameter doesn't exist (is not supported)
		     return DCM_SERVICE_NRC_SUB_FUNCTION_NOT_SUPPORTED;
		     break;
	}

	*responseDataLength = 2;
	responseData[responseIndex++] = controlType;

	return DCM_POSITIVE_RESPONSE;
}


