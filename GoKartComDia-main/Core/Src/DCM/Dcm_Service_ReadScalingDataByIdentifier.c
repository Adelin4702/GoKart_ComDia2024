/*
 * Dcm_Service_ReadScalingDataByIdentifier.c
 *
 *  Created on: Sep 9, 2024
 *      Author: PRP3CLJ
 */
#include <Dcm_Service_ReadScalingDataByIdentifier.h>
#include <Dcm_Service_SecurityAccess.h>
#include <Dcm_Service_DiagnosticSessionControl.h>


extern Dcm_DID *allDIDs[100];
extern volatile uint8_t serviceState;
extern volatile uint8_t activated_DiagnosticSession;
extern Dcm_DID *allDIDs[100];



uint8_t* scalingFunction_1(uint8_t* data, uint8_t dataLength, uint8_t* response, uint8_t* newLength){
	uint8_t responseLength = 0;
	for(int i = 0; i < dataLength; i+=2){
		if(i+1 < dataLength){
			response[responseLength++] = (data[i] & data[i+1]) + 0x01;
		}
	}
	if(dataLength % 2 == 1){
		response[responseLength++] = data[dataLength-1];
	}
	*newLength = responseLength;
	return response;
}

uint8_t* scalingFunction_2(uint8_t* data, uint8_t dataLength, uint8_t* response, uint8_t* newLength){
	uint8_t responseLength = 0;
	for(int i = 0; i < dataLength; i+=2){
		if(i+1 < dataLength){
			response[responseLength++] = (data[i] | data[i+1]) + 0x02;
		}
	}
	if(dataLength % 2 == 1){
		response[responseLength++] = data[dataLength-1];
	}
	*newLength = responseLength;
	return response;
}

uint8_t* scalingFunction_3(uint8_t* data, uint8_t dataLength, uint8_t* response, uint8_t* newLength){
	uint8_t responseLength = 0;
	for(int i = 0; i < dataLength; i+=2){
		if(i+1 < dataLength){
			response[responseLength++] = (data[i] ^ data[i+1]) + 0x03;
		}
	}
	if(dataLength % 2 == 1){
		response[responseLength++] = data[dataLength-1];
	}
	*newLength = responseLength;
	return response;
}

uint8_t scaleData(Dcm_DID *did, uint8_t *response, uint8_t *newLength){
	switch (did->scalingFunction) {
		case 1:
			scalingFunction_1(did->data, did->dataLength, response, newLength);
			break;
		case 2:
			scalingFunction_2(did->data, did->dataLength, response, newLength);
			break;
		case 3:
			scalingFunction_3(did->data, did->dataLength, response, newLength);
			break;

		default:
			break;
	}
	return 0x0;
}

// HANDLE securityAccessDenied NRC!
// HANDLE requestOutOfRange NRC! (partea cu sesiunea si dynamicDefinedDataIdentifier)
// HANDLE conditionsNotCorrect NRC!
Dcm_Service_ResponseCode Dcm_Service_ReadScalingDataByIdentifier_RequestNrcCheck(uint8_t *requestMessageData, uint8_t requestMessageDataLength){

	// 0x13 NRC
	// incorrectMessageLengthOrInvalidFormat
	// This NRC shall be sent if the length of the request message is invalid or the client exceeded
	// the maximum number of dataIdentifiers allowed to be requested at a time.
	if (requestMessageData[0] != DCM_SERVICE_ID_READ_SCALING_DATA_BY_IDENTIFIER)
	{
		return DCM_SERVICE_NRC_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT;
	}

	if (requestMessageDataLength != 3)
	{
		// Only one DID can be read at a time, since the CAN Payload only accepts 8 bytes/message
		return DCM_SERVICE_NRC_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT;
	}

	return DCM_SERVICE_NRC_NO_ERRORS;
}

Dcm_Service_ResponseCode Dcm_Service_ReadScalingDataByIdentifier_ResponseNrcCheck(uint8_t *responseMessageData, uint8_t *responseMessageDataLength)
{
	// 0x14 NRC
	// responseTooLong
	// This NRC shall be sent if the total length of the response message exceeds the limit of the
	// underlying transport protocol (e.g., when multiple DIDs are requested in a single request).
	if (*responseMessageDataLength > 8)
	{
		return DCM_SERVICE_NRC_RESPONSE_TOO_LONG;
	}

	return DCM_SERVICE_NRC_NO_ERRORS;
}

Dcm_Service_ResponseCode Dcm_Service_ReadScalingDataByIdentifier(uint8_t* requestMessageData, uint8_t requestMessageDataLength, uint8_t* responseMessageData, uint8_t* responseMessageDataLength)
{
	uint8_t requestNRC = Dcm_Service_ReadScalingDataByIdentifier_RequestNrcCheck(requestMessageData, requestMessageDataLength);

	if (requestNRC != DCM_SERVICE_NRC_NO_ERRORS)
	{
		return requestNRC;
	}


	uint8_t responseDataIndex = 0;
	responseMessageData[responseDataIndex++] = DCM_SERVICE_ID_READ_SCALING_DATA_BY_IDENTIFIER_RESPONSE_SID;
	uint8_t foundAtLeastOneDid = 0;

	for (uint8_t currentRequestByteIndex = 1; currentRequestByteIndex < requestMessageDataLength; currentRequestByteIndex += 2)
	{
		uint8_t didHighByte = requestMessageData[currentRequestByteIndex];
		uint8_t didLowByte = requestMessageData[currentRequestByteIndex + 1];
		uint16_t did = ((uint16_t)didHighByte << 8) | didLowByte;

		for (uint8_t currentDidIndex = 0; currentDidIndex < DCM_DID_COUNT; currentDidIndex++)
		{
			Dcm_DID *currentDid = allDIDs[currentDidIndex];
			if (allDIDs[currentDidIndex]->id == did)
			{
				foundAtLeastOneDid = 1;

				if(allDIDs[currentDidIndex]->securityLevel == 1 && serviceState != DCM_SERVICE_SECURITY_ACCESS_UNLOCKED){
					return DCM_NRC_SECURITY_ACCESS_DENIED;
				}

				if((allDIDs[currentDidIndex]->supportedSessionsMask >> (activated_DiagnosticSession-1)) % 2 == 0){
					return DCM_NRC_REQUEST_OUT_OF_RANGE;
				}

	    		serviceState = DCM_SERVICE_SECURITY_ACCESS_IDLE;

				responseMessageData[responseDataIndex++] = didHighByte;
				responseMessageData[responseDataIndex++] = didLowByte;

				uint8_t newLength;
				uint8_t scalingResponse[8];
				scaleData(allDIDs[currentDidIndex], scalingResponse, &newLength);

				for (uint8_t currentDidDataIndex = 0; currentDidDataIndex < newLength; currentDidDataIndex++)
				{
					responseMessageData[responseDataIndex++] = scalingResponse[currentDidDataIndex];
				}
			}
		}

		*responseMessageDataLength = responseDataIndex;
	}

	// 0x31 NRC
	// requestOutOfRange
	// This NRC shall be sent if:
	// none of the requested dataIdentifier values are supported by the device;
	// none of the requested dataIdentifiers are supported in the current session;
	// the requested dynamicDefinedDataIdentifier has not been assigned yet;
	if (!foundAtLeastOneDid)
	{
		return DCM_SERVICE_NRC_REQUEST_OUT_OF_RANGE;
	}

	uint8_t responseNRC = Dcm_Service_ReadScalingDataByIdentifier_ResponseNrcCheck(responseMessageData, responseMessageDataLength);

	if (responseNRC != 0x00)
	{
		return responseNRC;
	}

    return DCM_SERVICE_NRC_NO_ERRORS;
}
