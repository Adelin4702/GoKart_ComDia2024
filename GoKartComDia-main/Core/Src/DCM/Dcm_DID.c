/*
 * Dcm_DID.c
 *
 *  Created on: Oct 26, 2023
 *      Author: FER3CLJ
 */
#include <Dcm_DID.h>

volatile Dcm_DID *allDIDs[100];
Dcm_DID DID_0x100B_diagToolAndSessionStatus;
Dcm_DID DID_0x2010_programmingStatus;
Dcm_DID DID_0x201A_appSoftwareReprogrammingAttemptCounter;
Dcm_DID DID_0xF110_ecuDiagnosticIdentification;
Dcm_DID DID_0xF1A2_vectorDeliveryID;
Dcm_DID DID_0xF1BD_ecuSignatureType;

uint8_t memory[0x100][0x100];
/* supportedSessionsMask Explanation
 * 	bits 7 - 4 : always 0
 * 	bit 3 set to 1 if the DID is available in SAFETY SYSTEM SESSION, else 0
 * 	bit 2 set to 1 if the DID is available in EXTENDED SESSION, else 0
 * 	bit 1 set to 1 if the DID is available in PROGRAMMING SESSION, else 0
 * 	bit 0 set to 1 if the DID is available in DEFAULT SESSION, else 0
 */
void Dcm_DID_Init()
{
	DID_0x100B_diagToolAndSessionStatus.id = 0x100B;
	DID_0x100B_diagToolAndSessionStatus.dataLength = 4;
	DID_0x100B_diagToolAndSessionStatus.data[0] = 0x3A;
	DID_0x100B_diagToolAndSessionStatus.data[1] = 0x28;
	DID_0x100B_diagToolAndSessionStatus.data[2] = 0xAF;
	DID_0x100B_diagToolAndSessionStatus.data[3] = 0x58;
	DID_0x100B_diagToolAndSessionStatus.securityLevel = 0;
	DID_0x100B_diagToolAndSessionStatus.supportedSessionsMask = 0x0F; //All sessions
	DID_0x100B_diagToolAndSessionStatus.scalingFunction = 0x01;
	allDIDs[0] = &DID_0x100B_diagToolAndSessionStatus;

	DID_0x2010_programmingStatus.id = 0x2010;
	DID_0x2010_programmingStatus.dataLength = 3;
	DID_0x2010_programmingStatus.data[0] = 0x1B;
	DID_0x2010_programmingStatus.data[1] = 0x3C;
	DID_0x2010_programmingStatus.data[2] = 0x70;
	DID_0x2010_programmingStatus.securityLevel = 0;
	DID_0x2010_programmingStatus.supportedSessionsMask = 0x0F; // all sessions
	DID_0x2010_programmingStatus.scalingFunction = 0x02;
	allDIDs[1] = &DID_0x2010_programmingStatus;

	DID_0x201A_appSoftwareReprogrammingAttemptCounter.id = 0x201A;
	DID_0x201A_appSoftwareReprogrammingAttemptCounter.dataLength = 2;
	DID_0x201A_appSoftwareReprogrammingAttemptCounter.data[0] = 0xAB;
	DID_0x201A_appSoftwareReprogrammingAttemptCounter.data[1] = 0xCD;
	DID_0x201A_appSoftwareReprogrammingAttemptCounter.securityLevel = 1;
	DID_0x201A_appSoftwareReprogrammingAttemptCounter.supportedSessionsMask = 0x05; // Default and extended session
	DID_0x201A_appSoftwareReprogrammingAttemptCounter.scalingFunction = 0x03;
	allDIDs[2] = &DID_0x201A_appSoftwareReprogrammingAttemptCounter;

	DID_0xF110_ecuDiagnosticIdentification.id = 0xF110;
	DID_0xF110_ecuDiagnosticIdentification.dataLength = 1;
	DID_0xF110_ecuDiagnosticIdentification.data[0] = 0xFF;
	DID_0xF110_ecuDiagnosticIdentification.securityLevel = 0;
	DID_0xF110_ecuDiagnosticIdentification.supportedSessionsMask = 0x07; // Default, Programming and Extended session
	DID_0xF110_ecuDiagnosticIdentification.scalingFunction = 0x01;
	allDIDs[3] = &DID_0xF110_ecuDiagnosticIdentification;

	DID_0xF1A2_vectorDeliveryID.id = 0xF1A2;
	DID_0xF1A2_vectorDeliveryID.dataLength = 3;
	DID_0xF1A2_vectorDeliveryID.data[0] = 0x98;
	DID_0xF1A2_vectorDeliveryID.data[1] = 0xA3;
	DID_0xF1A2_vectorDeliveryID.data[2] = 0x7F;
	DID_0xF1A2_vectorDeliveryID.securityLevel = 1;
	DID_0xF1A2_vectorDeliveryID.supportedSessionsMask = 0x0F; //All sessionss
	DID_0xF1A2_vectorDeliveryID.scalingFunction = 0x02;
	allDIDs[4] = &DID_0xF1A2_vectorDeliveryID;

	DID_0xF1BD_ecuSignatureType.id = 0xF1BD;
	DID_0xF1BD_ecuSignatureType.dataLength = 4;
	DID_0xF1BD_ecuSignatureType.data[0] = 0x6C;
	DID_0xF1BD_ecuSignatureType.data[1] = 0x9D;
	DID_0xF1BD_ecuSignatureType.data[2] = 0xDC;
	DID_0xF1BD_ecuSignatureType.data[3] = 0x81;
	DID_0xF1BD_ecuSignatureType.securityLevel = 1;
	DID_0xF1BD_ecuSignatureType.supportedSessionsMask = 0x05;// Default and Extended session
	DID_0xF1BD_ecuSignatureType.scalingFunction = 0x03;
	allDIDs[5] = &DID_0xF1BD_ecuSignatureType;

	for(uint16_t i = 0; i < 0x10; i++){
		for( uint16_t j=0; j < 0x10; j++ ){
			memory[i][j] = (i + j) % 0x100;
		}
	}
}

Dcm_DID Dcm_Get_DID_0x100B_diagToolAndSessionStatus()
{
	return DID_0x100B_diagToolAndSessionStatus;
}

Dcm_DID Dcm_Get_DID_0x2010_programmingStatus()
{
	return DID_0x2010_programmingStatus;
}

Dcm_DID Dcm_Get_DID_0x201A_appSoftwareReprogrammingAttemptCounter()
{
	return DID_0x201A_appSoftwareReprogrammingAttemptCounter;
}

Dcm_DID Dcm_Get_DID_0xF110_ecuDiagnosticIdentification()
{
	return DID_0xF110_ecuDiagnosticIdentification;
}

Dcm_DID Dcm_Get_DID_0xF1A2_vectorDeliveryID()
{
	return DID_0xF1A2_vectorDeliveryID;
}

Dcm_DID Dcm_Get_DID_0xF1BD_ecuSignatureType()
{
	return DID_0xF1BD_ecuSignatureType;
}
