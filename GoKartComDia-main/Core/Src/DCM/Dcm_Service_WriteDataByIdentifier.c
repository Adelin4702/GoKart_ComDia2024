/*
 * Dcm_Service_WriteDataByIdentifier.c
 *
 *  Created on: Oct 24, 2023
 *      Author: FER3CLJ
 */
#include <Dcm_Service_WriteDataByidentifier.h>
#include <Dcm_Service_SecurityAccess.h>
#include <Constants.h>

extern uint8_t Dcm_ActiveSecurityLevel;
extern Dcm_DID *allDIDs[100];
extern volatile uint8_t serviceState;
extern volatile uint8_t activated_DiagnosticSession;

uint8_t Dcm_Service_WriteDataByIdentifier(uint8_t *requestMessageData, uint8_t requestMessageLength, uint8_t *responseData, uint8_t *responseDataLength)
{
	if (requestMessageData[0] != DCM_SERVICE_ID_WRITE_DATA_BY_IDENTIFIER)
		{
			return DCM_NRC_GENERAL_PROGRAMMING_FAILURE;
		}

    if(requestMessageLength < 4){
    	responseData[0] = NEGATIVE_RESPONSE_SID;
    	responseData[1] = 0x13;

    	return DCM_NRC_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT;

    }

	uint8_t responseDataIndex = 0;
    responseData[responseDataIndex++] = DCM_SERVICE_ID_WRITE_DATA_BY_IDENTIFIER_RESPONSE_SID;

    uint8_t requestDataIndex = 1;
    uint8_t didHighByte = requestMessageData[requestDataIndex++];
    uint8_t didLowByte = requestMessageData[requestDataIndex++];
    uint16_t did = ((uint16_t)didHighByte << 8) + didLowByte;

    for (uint8_t currentDidIndex = 0; currentDidIndex < DCM_DID_COUNT; currentDidIndex++){

    	Dcm_DID *currentDid = allDIDs[currentDidIndex];

    	if (allDIDs[currentDidIndex]->id == did){

    		if(allDIDs[currentDidIndex]->securityLevel == 1 && serviceState != DCM_SERVICE_SECURITY_ACCESS_UNLOCKED){
    			return DCM_NRC_SECURITY_ACCESS_DENIED;
    		}

    		if((allDIDs[currentDidIndex]->supportedSessionsMask >> (activated_DiagnosticSession-1)) % 2 == 0){
    			return DCM_NRC_REQUEST_OUT_OF_RANGE;
    		}

    		serviceState = DCM_SERVICE_SECURITY_ACCESS_IDLE;

    		//Modification 3.a
    		if(requestMessageLength != allDIDs[currentDidIndex]->dataLength + 3){
				responseData[0] = NEGATIVE_RESPONSE_SID;
				responseData[1] = 0x13;

				return DCM_NRC_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT;
			}
    		responseData[responseDataIndex++] = didHighByte;
    		responseData[responseDataIndex++] = didLowByte;

    		//Modification 2.a
    		uint8_t requestDataIndex_auxiliary = requestDataIndex;
    		//Modification 2.b
    		for (uint8_t currentDidDataIndex = 0; currentDidDataIndex <= requestMessageLength-requestDataIndex_auxiliary; currentDidDataIndex++){

    				currentDid->data[currentDidDataIndex] = requestMessageData[requestDataIndex++];
    		}

    	}

    }

    			*responseDataLength = responseDataIndex;


    return DCM_POSITIVE_RESPONSE;
}
