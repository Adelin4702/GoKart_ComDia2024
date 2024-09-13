/*
 * Dcm_Service_DiagnosticSessionControl.c
 *
 *  Created on: Oct 24, 2023
 *      Author: FER3CLJ
 */
#include <Dcm_Service_DiagnosticSessionControl.h>
#include <Constants.h>

volatile uint8_t activated_DiagnosticSession = DCM_SESSION_DEFAULT_SESSION;
// Services
uint8_t Dcm_Service_DiagnosticSessionControl(uint8_t *requestMessageData, uint8_t requestMessageLength, uint8_t *responseData, uint8_t *responseDataLength)
{
	// Incorrect length
	if (requestMessageLength != 2)
		return DCM_NRC_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT;

	switch(requestMessageData[1])
	{
		case DCM_SESSION_DEFAULT_SESSION:                                    // se doreste trecerea in DCM_SESSION_DEFAULT_SESSION - se poate din orice alta sesiune
			activated_DiagnosticSession = DCM_SESSION_DEFAULT_SESSION;

			break;

		case DCM_SESSION_PROGRAMMING_SESSION:                                // se doreste trecerea in DCM_SESSION_PROGRAMMING_SESSION
			if (activated_DiagnosticSession == DCM_SESSION_EXTENDED_DIAGNOSTIC_SESSION)  // se poate doar din DCM_SESSION_EXTENDED_DIAGNOSTIC_SESSION
			{
				activated_DiagnosticSession = DCM_SESSION_PROGRAMMING_SESSION;
				 break;
			}
			else
			{
				return DCM_NRC_SUBFUNCTION_NOT_SUPPORTED_IN_ACTIVE_DIAGNOSTIC_SESSION;
			}

		case DCM_SESSION_EXTENDED_DIAGNOSTIC_SESSION:                       // se doreste trecerea in DCM_SESSION_EXTENDED_DIAGNOSTIC_SESSION - se poate din orice sesiune

				activated_DiagnosticSession = DCM_SESSION_EXTENDED_DIAGNOSTIC_SESSION;

				break;

		case DCM_SESSION_SAFETY_SYSTEM_DIAGNOSTIC_SESSION:                  // se doreste trecerea in DCM_SESSION_SAFETY_SYSTEM_DIAGNOSTIC_SESSION
			if (activated_DiagnosticSession == DCM_SESSION_EXTENDED_DIAGNOSTIC_SESSION) // se poate din DCM_SESSION_EXTENDED_DIAGNOSTIC_SESSION
			{
				 activated_DiagnosticSession = DCM_SESSION_SAFETY_SYSTEM_DIAGNOSTIC_SESSION;
				 break;
			}
			else
			{
				return DCM_NRC_SUBFUNCTION_NOT_SUPPORTED_IN_ACTIVE_DIAGNOSTIC_SESSION;
			}

		default:
		  {
			  return DCM_NRC_SUBFUNCTION_NOT_SUPPORTED;
		  }
	}

	responseData[0] = requestMessageData[0] + 0x40;
	responseData[1] = requestMessageData[1];
	responseData[2] = TIMING_FOR_ACTIVATED_SESSION_P2_SERVER_MAX_HB;
	responseData[3] = TIMING_FOR_ACTIVATED_SESSION_P2_SERVER_MAX_LB;
	responseData[4] = TIMING_FOR_ACTIVATED_SESSION_P2_SERVER_MAX_STAR_HB;
	responseData[5] = TIMING_FOR_ACTIVATED_SESSION_P2_SERVER_MAX_STAR_LB;
	*responseDataLength = 0x06;


    return 0x00;
}
