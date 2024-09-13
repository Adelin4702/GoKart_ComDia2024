/*
 * Dcm_Service_WriteMemoryByAddress.c
 *
 *  Created on: Oct 24, 2023
 *      Author: FER3CLJ
 */
#include <Eeprom.h>
#include <Dcm_Service_WriteMemoryByAddress.h>
#include <Dcm_Service_SecurityAccess.h>
#include <Constants.h>

extern uint8_t Dcm_ActiveSecurityLevel;

//Modificarea 5.a
uint8_t Dcm_Service_WriteMemoryByAddress(uint8_t *requestMessageData, uint8_t requestMessageLength, uint8_t *responseData, uint8_t *responseDataLength)
{
	if (requestMessageLength < 3 || requestMessageLength > 8)
		return DCM_NRC_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT;

	uint8_t addressAndLengthFormatIdentifier, memorySizeLength, memoryAddressLength;
	/*
		bits 0-3 of addressAndLengthFormatIdentifier=length in bytes of memoryAddress
		bits 4-7 of addressAndLengthFormatIdentifier=length in bytes of memorySize
	*/
	addressAndLengthFormatIdentifier = requestMessageData[1];
	memoryAddressLength = addressAndLengthFormatIdentifier & 0x0f;
	memorySizeLength = addressAndLengthFormatIdentifier >> 4;

	if((memoryAddressLength > 6) || (memoryAddressLength < 1) || (memorySizeLength == 0) || (memorySizeLength > 7))
		return DCM_NRC_CONDITIONS_NOT_CORRECT;


	uint8_t memoryAddressArray[memoryAddressLength];
	for(int i=0;i<memoryAddressLength;i++)
	{
		memoryAddressArray[i] = requestMessageData[i+2]; //because the first 2 bytes are already occupied
	}

	uint16_t memoryAddress=memoryAddressArray[0];
	for(int i=1;i<memoryAddressLength;i++) //concatenate bytes to form the address
	{
		memoryAddress=(memoryAddress<<8) | memoryAddressArray[i];
	}

	responseData[0] = DCM_SERVICE_ID_WRITE_MEMORY_BY_ADDRESS + 0x40;

	// Modificarea 4.
	uint16_t memorySize = 0x0;
	for(uint8_t i = 0; i < memorySizeLength; i++){
		memorySize = (memorySize << 8) + requestMessageData[memoryAddressLength + 2 + i];
	}

	if(memorySize == 0x0){
		return DCM_NRC_REQUEST_OUT_OF_RANGE;
	}

	for(uint8_t i = 0; i < memorySize; i+=2)
	{
		uint16_t data = requestMessageData[memoryAddressLength + memorySizeLength + 2 + i] << 8;
		if(i+1 < memorySize){
			data = data + requestMessageData[memoryAddressLength + memorySizeLength + 2 + i + 1];
		}

		if((EE_WriteVariable(memoryAddress,  data)) != HAL_OK)
		{
			return DCM_NRC_GENERAL_PROGRAMMING_FAILURE;
//			Error_Handler();
		}

		memoryAddress++;
	}

	for(int i = 1; i < memoryAddressLength + memorySizeLength + 2; i++){
		responseData[i] = requestMessageData[i];
	}

	*responseDataLength = memoryAddressLength + memorySizeLength + 2;
    return DCM_POSITIVE_RESPONSE;
}

