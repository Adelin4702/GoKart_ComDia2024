/*
 * ControlDTCSetting.c
 *
 *  Created on: Sep 9, 2024
 *      Author: MTA6CLJ
 */



#include <Dcm_Service_ControlDTCSetting.h>
extern uint8_t DTCSettingStatus;
extern uint8_t currentSession;

uint8_t Dcm_Service_ControlDTCSetting(uint8_t *requestMessageData, uint8_t requestMessageLength, uint8_t *responseData, uint8_t *responseDataLength)
{
	responseData[0] = DCM_SERVICE_ID_CONTROL_DTC_SETTING + 0x40;
	responseData[1] = requestMessageData[1];
	*responseDataLength = 2;

//	uint8_t DTCSettingStatus_var = DTCSettingStatus;
	if(requestMessageLength != 2)
	{
		return DCM_SERVICE_NRC_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT;
	}
	if(currentSession == DCM_SESSION_DEFAULT)
	{
		return DCM_SERVICE_NRC_SUB_FUNCTION_NOT_SUPPORTED;
	}
	switch(requestMessageData[1])
	{
		case ON:
			if(DTCSettingStatus != ON)
			{
				DTCSettingStatus = ON;
			}
		break;
		case OFF:
			if(DTCSettingStatus != OFF)
			{
				DTCSettingStatus = OFF;
			}
		break;

	}

	return DCM_POSITIVE_RESPONSE;
}
