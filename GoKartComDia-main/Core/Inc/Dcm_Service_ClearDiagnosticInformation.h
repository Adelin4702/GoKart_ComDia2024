/*
 * Dcm_Service_ClearDiagnosticInformation.h
 *
 *  Created on: Oct 24, 2023
 *      Author: FER3CLJ
 */

#ifndef INC_DCM_SERVICE_CLEARDIAGNOSTICINFORMATION_H_
#define INC_DCM_SERVICE_CLEARDIAGNOSTICINFORMATION_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <DTC_entity 1.h>
#include <Constants.h>

//Group of DTC
#define POWERTRAIN 0x000100 //Engine and transmission-related issueS
#define CHASSIS 0x000102 //Issues related to the vehicle's chassis and suspension systems
#define BODY 0x000103 //Problems with the body control module, lighting, and other body-related systems
#define NETWORK_COMMUNICATION 0x000104 //Communication issues between various control modules in the vehicle
#define TRANSMISSION 0x000101//Issues related to the transmission system
#define FUEL_AND_AIR_METERING 0x000106//DTCs related to the management of the air-fuel mixture
#define EMISSION_CONTROL 0xFFFF33//Issues with components related to emission control, such as catalytic converters
#define COMMUNICATION_AND_NETWORK 0x000105//Communication issues between electronic control units (ECUs) in the vehicle

//NRCs
#define INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT 0X13
#define REGUEST_OUT_OF_RANGE 0X31
#define CONDITIONS_NOT_CORRECT 0X22
#define GENERAL_PROGRAMMING_FAILURE 0X72

//priorities
#define HIGH_PRIORITY 0X01
#define MEDIUM_PRIORITY 0X02
#define LOW_PRIORITY 0X03

uint8_t Dcm_Service_ClearDiagnosticInformation(uint8_t *requestMessageData, uint8_t requestMessageLength, uint8_t *responseData, uint8_t *responseDataLength);


#endif /* INC_DCM_SERVICE_CLEARDIAGNOSTICINFORMATION_H_ */
