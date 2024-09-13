/*
 * Dcm_Service_ClearDiagnosticInformation.c
 *
 *  Created on: Oct 24, 2023
 *      Author: FER3CLJ
 */
#include <Dcm_Service_ClearDiagnosticInformation.h>
#include <DTC_entity 1.h>
#include <Dcm_Service_ReadDTCInformation.h>
#include <Constants.h>
//#include <Types.h>

struct node* startDTCList = NULL;

//Dcm_DTC1 DTC_0x0300_randomMultipleCylinderMisfireDetected;
//Dcm_DTC1 DTC_0x0420_catalystSystemEfficiencyBelowThresholdBank1;
//Dcm_DTC1 DTC_0x0171_systemTooLeanBank1;

//Dcm_DTC DTCList[30];
//int indexDTC = 0;



int insertDTC(Dcm_DTC DTCList[], int *numar_DTC, int max_DTC, Dcm_DTC newDTC) {
    if (*numar_DTC >= max_DTC) {
        return -1;
    }

    DTCList[*numar_DTC] = newDTC;
    (*numar_DTC)++;
    return 1;
}

int insertSnapShot_array(uint8_t data[2], Dcm_DTC *dtc)
{
	if (dtc->nrSnapshots >= MAX_SNAPSHOTS) {
	        return 0;
	    }

	dtc->snapshots->snapData[0] = data[0];
	dtc->snapshots->snapData[1] = data[1];
	dtc->nrSnapshots++;

	return 1;
}

//clears the information of a DTC
void clearDTCInformation(Dcm_DTC *dtc)
{
    struct node *ptr = startDTCList;

     while(ptr != NULL)
    {
        if (ptr->infoDTC.id == dtc->id)
        {
            ptr->infoDTC.statusMask = 0x00;
           // delete_Snap(&ptr->infoDTC.startSnapList);
            break;
        }

        ptr = ptr->next;
    }

}

void clearDTCInformation_array(Dcm_DTC *dtc)
{


     for(int i=0;i<numberOfDtcs;i++)
    {
        if (dtcs[i].id == dtc->id)
        {
        	dtcs[i].statusMask = 0x00;
        	delete_Snap_array(dtc->snapshots, &dtc->nrSnapshots);
            break;
        }

    }

}

void delete_Snap_array(Snapshot snapshots[], uint8_t* nrSnapshots)
{
	for(int i=0;i<*nrSnapshots;i++)
	{
		 for(int j = 0; j < 2; j++)
		 {
		     snapshots[i].snapData[j] = 0x00;
		 }

	}
	(*nrSnapshots) = 0;
}

uint8_t isCleared_Status(Dcm_DTC dtc)
{
    uint8_t ClearStatus = 1;

    if (dtc.statusMask == 0x00)
    {
        struct node_Snapshot* ptr = dtc.startSnapList;

        while(ptr != NULL)
        {
            if (ptr->snapData[0] != 0x00 || ptr->snapData[1] != 0x00)
            {
                ClearStatus = 0;
                break;
            }

            ptr = ptr->next;
        }
    }
    else
    {
        ClearStatus = 0;
    }

    return ClearStatus;
}

uint8_t isCleared_Status_array(Dcm_DTC dtc)
{
    uint8_t ClearStatus = 1;

    if (dtc.statusMask == 0x00)
    {

    	if(dtc.nrSnapshots != 0)
    	{
    		 ClearStatus = 0;

    	}

//    	 for(int i=0;i<dtc.nrSnapshots;i++)
//        {
//    		 if (dtc.snapshots[i].snapData[0] != 0x00 || dtc.snapshots[i].snapData[1] != 0x00)
//    			      {
//    			          ClearStatus = 0;
//    			          break;
//    			      }
//
//        }
    }
    else
    {
        ClearStatus = 0;
    }

    return ClearStatus;
}
//clears the information of DTCs from a certain group
void clearDTCInformation_Group(uint32_t group, uint8_t *status)
{
    struct node *ptr = startDTCList;

    while(ptr != NULL)
    {
        if (ptr->infoDTC.groupOfDTC == group)
        {
            clearDTCInformation(&ptr->infoDTC);

            if (isCleared_Status(ptr->infoDTC) == 0)
            {
                *status = GENERAL_PROGRAMMING_FAILURE;
            }
        }

        ptr = ptr->next;
    }

}

void clearDTCInformation_Group_array(uint32_t group, uint8_t *status)
{

	 for(int i=0;i<numberOfDtcs;i++)
	   {
		   if(dtcs[i].groupOfDTC == group)
		   {
			   clearDTCInformation_array(&dtcs[i]);
			   if (isCleared_Status_array(dtcs[i]) == 0)
			    {
			        *status = GENERAL_PROGRAMMING_FAILURE;
			    }

		   }
	   }


}

//search in a group for active DTCs; if there is at least an active DTC -> returns CONDITIONS_NOT_CORRECT
uint8_t isActive_InGroup(uint32_t group)
{
    struct node *ptr = startDTCList;
    while(ptr != NULL)
    {
        if (ptr->infoDTC.groupOfDTC == group)
        {
            if((ptr->infoDTC.statusMask & 0x01) == 0x01) //one of the DTCs in the group is active
            {
                return CONDITIONS_NOT_CORRECT;
            }
        }

        ptr = ptr->next;
    }

    return 0;
}

uint8_t isActive_InGroup_array(uint32_t group)
{

   for(int i=0;i<numberOfDtcs;i++)
   {
	   if(dtcs[i].groupOfDTC == group)
	   {
		   if((dtcs[i].statusMask & 0x01) == 0x01)
		   {
			   return CONDITIONS_NOT_CORRECT;
		   }
	   }
   }
    return 1;
}

uint8_t Dcm_Service_ClearDiagnosticInformation(uint8_t *requestMessageData, uint8_t requestMessageLength, uint8_t *responseData, uint8_t *responseDataLength)
{
     //implementation
//	 Dcm_DTC_Init();
	 uint8_t responseCode;
	 if (requestMessageLength != 4){
	        return DCM_NRC_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT;
	  }

	 // struct node *ptr = startDTCList;
	  uint8_t lowByte, middleByte, highByte;
	  uint8_t exists = 0;

	  lowByte = requestMessageData[3];
	  middleByte = requestMessageData[2];
	  highByte = requestMessageData[1];

	  uint32_t groupOfDTC = 0;

	  groupOfDTC |= (uint32_t)lowByte;
	  groupOfDTC |= ((uint32_t)middleByte << 8);
	  groupOfDTC |= ((uint32_t)highByte << 16);

	    responseData[0] = DCM_SERVICE_ID_CLEAR_DIAGNOSTIC_INFORMATION + 0x40;
	    *responseDataLength = 1;
	    switch(groupOfDTC){

        case POWERTRAIN:
            if (isActive_InGroup_array(POWERTRAIN) == CONDITIONS_NOT_CORRECT)
            {
                return DCM_NRC_CONDITIONS_NOT_CORRECT;
            }
            clearDTCInformation_Group_array(POWERTRAIN, &responseCode);
            break;

        case CHASSIS:
            if (isActive_InGroup_array(CHASSIS) == CONDITIONS_NOT_CORRECT)
            {
                return DCM_NRC_CONDITIONS_NOT_CORRECT;
            }

            clearDTCInformation_Group_array(CHASSIS, &responseCode);
            break;

        case BODY:
            if (isActive_InGroup_array(BODY) == CONDITIONS_NOT_CORRECT)
            {
                return DCM_NRC_CONDITIONS_NOT_CORRECT;
            }

            clearDTCInformation_Group_array(BODY, &responseCode);
            break;

        case NETWORK_COMMUNICATION:
            if (isActive_InGroup_array(NETWORK_COMMUNICATION) == CONDITIONS_NOT_CORRECT)
            {
                return DCM_NRC_CONDITIONS_NOT_CORRECT;
            }

            clearDTCInformation_Group_array(NETWORK_COMMUNICATION, &responseCode);
            break;

        case TRANSMISSION:
            if (isActive_InGroup_array(TRANSMISSION) == CONDITIONS_NOT_CORRECT)
            {
                return DCM_NRC_CONDITIONS_NOT_CORRECT;
            }

            clearDTCInformation_Group_array(TRANSMISSION, &responseCode);
            break;

        case FUEL_AND_AIR_METERING:
            if (isActive_InGroup_array(FUEL_AND_AIR_METERING) == CONDITIONS_NOT_CORRECT)
            {
                return DCM_NRC_CONDITIONS_NOT_CORRECT;
            }

            clearDTCInformation_Group_array(FUEL_AND_AIR_METERING, &responseCode);
            break;

        case EMISSION_CONTROL:
            if (isActive_InGroup_array(EMISSION_CONTROL) == CONDITIONS_NOT_CORRECT)
            {
                return DCM_NRC_CONDITIONS_NOT_CORRECT;
            }

            clearDTCInformation_Group_array(EMISSION_CONTROL, &responseCode);
            break;

        case COMMUNICATION_AND_NETWORK:
            if (isActive_InGroup_array(COMMUNICATION_AND_NETWORK) == CONDITIONS_NOT_CORRECT)
            {
                return DCM_NRC_CONDITIONS_NOT_CORRECT;
            }

            clearDTCInformation_Group_array(COMMUNICATION_AND_NETWORK, &responseCode);
            break;

        default:
        	break;
        	//if the request contains a DTC
//            while(ptr != NULL)
//            {
//                if ((ptr->infoDTC.id == groupOfDTC))
//                {
//                    if((ptr->infoDTC.statusMask & 0x01) == 0x01)
//                    {
//                        return CONDITIONS_NOT_CORRECT;
//                    }
//
//                    exists = 1;
//                    clearDTCInformation(&ptr->infoDTC);
//                    break;
//                }
//                ptr = ptr->next;
//            }
//
//            if (exists == 0)
//                return REGUEST_OUT_OF_RANGE;



	    }
	    return DCM_POSITIVE_RESPONSE;
}
