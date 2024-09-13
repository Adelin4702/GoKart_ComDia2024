/*
 * Dcm_Service_ECUReset.c
 *
 *  Created on: Sep 05, 2024
 *      Author: PRP3CLJ
 */
 
#include <stdint.h>
#include <Dcm_Service_ECUReset.h>
#include <Constants.h>
#include <Dcm_Service_SecurityAccess.h>
#include <Dcm_DID.h>
#include <Eeprom.h>
#include <DTC_entity 1.h>


extern volatile uint8_t serviceState;
extern volatile uint8_t activated_DiagnosticSession;
Dcm_Reset resets[NR_OF_TYPES_OF_RESET];
uint8_t powerDownTime = 100;
uint8_t rapidPowerShutDown = 0;

void Dcm_Reset_Init(){
	Dcm_Reset hardReset;
	hardReset.id = DCM_RESET_HARD_RESET;
	hardReset.secured = 0x01;
	resets[0] = hardReset;

	Dcm_Reset keyOffOnReset;
	keyOffOnReset.id = DCM_RESET_KEY_OFF_ON_RESET;
	keyOffOnReset.secured = 0x00;
	resets[1] = keyOffOnReset;

	Dcm_Reset softReset;
	softReset.id = DCM_RESET_SOFT_RESET;
	softReset.secured = 0x00;
	resets[2] = softReset;

	Dcm_Reset enableRapidPowerShutDown;
	enableRapidPowerShutDown.id = DCM_RESET_ENABLE_RAPID_POWER_SHUTDOWN;
	enableRapidPowerShutDown.secured = 0x00;
	resets[3] = enableRapidPowerShutDown;

	Dcm_Reset disableRapidPowerShutDown;
	disableRapidPowerShutDown.id = DCM_RESET_DISABLE_RAPID_POWER_SHUTDOWN;
	disableRapidPowerShutDown.secured = 0x00;
	resets[4] = disableRapidPowerShutDown;
}

void EcuReset_HardReset(){
	Dcm_DID_Init();
	Dcm_DTC_Init();
	EE_Init();
}

void EcuReset_KeyOffOnReset(){
	Dcm_DID_Init();
	Dcm_DTC_Init();
}

void EcuReset_SoftReset(){
	return;
}


uint8_t Dcm_Service_ECUReset(uint8_t *requestMessageData, uint8_t requestMessageLength, uint8_t *responseData, uint8_t *responseDataLength)
{
	if(requestMessageData[0] != DCM_SERVICE_ID_ECU_RESET){
		return DCM_NRC_GENERAL_PROGRAMMING_FAILURE;
	}

	if((requestMessageLength != 2 && requestMessageData[1] != DCM_RESET_ENABLE_RAPID_POWER_SHUTDOWN)
			|| (requestMessageLength != 3 && requestMessageData[1] == DCM_RESET_ENABLE_RAPID_POWER_SHUTDOWN)){
		return DCM_NRC_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT;
	}

	if(requestMessageData[1] < 0x01 || requestMessageData[1] > 0x05){
		return DCM_NRC_SUBFUNCTION_NOT_SUPPORTED;
	}

	for(uint8_t i = 0; i < NR_OF_TYPES_OF_RESET; i++){
		if(resets[i].id == requestMessageData[1]){
			if(resets[i].secured == 1){
				if(serviceState != DCM_SERVICE_SECURITY_ACCESS_UNLOCKED){
					return DCM_NRC_SECURITY_ACCESS_DENIED;
				}
				serviceState = DCM_SERVICE_SECURITY_ACCESS_IDLE;
			}

		}
	}

	switch (requestMessageData[1])
	{
		case DCM_RESET_HARD_RESET:
		{
			EcuReset_HardReset();
			break;
		}
		case DCM_RESET_KEY_OFF_ON_RESET:
		{
			EcuReset_KeyOffOnReset();
			break;
		}
		case DCM_RESET_SOFT_RESET:
		{
			EcuReset_SoftReset();
			break;
		}
		case DCM_RESET_ENABLE_RAPID_POWER_SHUTDOWN:
		{
			if(rapidPowerShutDown != 0){
				return DCM_NRC_CONDITIONS_NOT_CORRECT;
			}
			powerDownTime = requestMessageData[2];
			rapidPowerShutDown = 1;
			break;
		}
		case DCM_RESET_DISABLE_RAPID_POWER_SHUTDOWN:
		{
			if(rapidPowerShutDown != 1){
				return DCM_NRC_CONDITIONS_NOT_CORRECT;
			}
			rapidPowerShutDown = 0;
			break;
		}
		default:
			break;
	}

	responseData[0] = DCM_SERVICE_ID_ECU_RESET + 0x40;
	responseData[1] = requestMessageData[1];
	*responseDataLength = 2;

	return 0x0;
}
