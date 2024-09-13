/*
 * Dcm_Service_ReadDTCInformation.c
 *
 *  Created on: Oct 24, 2023
 *      Author: FER3CLJ
 */
#include <Dcm_Service_ReadDTCInformation.h>
#include <DTC_entity 1.h>
#include <Constants.h>

#define ReportNumberOfDTCByStatusMask 0x01
#define ReportDTCByStatusMask 0x02
#define ReportDTCSnapshotIdentification 0x03
#define ReportDTCExtDataRecordByDTCNumber 0x06

//Dcm_DTC DTC_0x0300_randomMultipleCylinderMisfireDetected;
//Dcm_DTC DTC_0x0420_catalystSystemEfficiencyBelowThresholdBank1;
//Dcm_DTC DTC_0x0171_systemTooLeanBank1;

//struct node
//{
//         Dcm_DTC infoDTC;
//         struct node *next;
//};

//struct node *startDTCList = NULL;

//volatile uint8_t numberOfDtcs = 0;
//volatile Dcm_DTC dtcs[30];s



//void insert_DTC(Dcm_DTC DTC);


//void Dcm_DTC_Init_ReadDTC()
//{
//    DTC_0x0171_systemTooLeanBank1.id = 0x0171;
//    DTC_0x0171_systemTooLeanBank1.statusMask = 0x11 ; // Indicating a lean condition in Bank 1
//    DTC_0x0171_systemTooLeanBank1.dataLength = 0x02;
//    //Hypothetical hexadecimal data representing air-fuel mixture and sensor readings
//   // DTC_0x0171_systemTooLeanBank1.snapData[0] = 0xEF;
//    //DTC_0x0171_systemTooLeanBank1.snapData[1] = 0xEF;
//
//    insert_DTC(DTC_0x0171_systemTooLeanBank1);
//
//    DTC_0x0300_randomMultipleCylinderMisfireDetected.id = 0x0300;
//    DTC_0x0300_randomMultipleCylinderMisfireDetected.statusMask = 0x03; // Indicating multiple misfires in the cylinders
//    DTC_0x0300_randomMultipleCylinderMisfireDetected.dataLength = 0x02;
//    // Hypothetical hexadecimal data representing details of misfire events
//    //DTC_0x0300_randomMultipleCylinderMisfireDetected.snapData[0] = 0x12;
//    //DTC_0x0300_randomMultipleCylinderMisfireDetected.snapData[1] = 0x34;
//
//    insert_DTC(DTC_0x0300_randomMultipleCylinderMisfireDetected);
//
//    DTC_0x0420_catalystSystemEfficiencyBelowThresholdBank1.id = 0x0420;
//    DTC_0x0420_catalystSystemEfficiencyBelowThresholdBank1.statusMask = 0x21; //Indicating catalyst efficiency issue in Bank 1
//    DTC_0x0420_catalystSystemEfficiencyBelowThresholdBank1.dataLength = 0x02;
//    // Hypothetical hexadecimal data representing sensor readings and engine conditions
//   // DTC_0x0420_catalystSystemEfficiencyBelowThresholdBank1.snapData[0] = 0xAB;
//    //DTC_0x0420_catalystSystemEfficiencyBelowThresholdBank1.snapData[1] = 0xCD;
//
//    insert_DTC(DTC_0x0420_catalystSystemEfficiencyBelowThresholdBank1);
//}


Dcm_DTC Dcm_Get_DTC_0x0171_systemTooLeanBank1()
{
    return DTC_0x0171_systemTooLeanBank1;
}

Dcm_DTC Dcm_Get_DTC_0x0300_randomMultipleCylinderMisfireDetected()
{
    return DTC_0x0300_randomMultipleCylinderMisfireDetected;
}

Dcm_DTC Dcm_Get_DTC_0x0420_catalystSystemEfficiencyBelowThresholdBank1()
{
    return DTC_0x0420_catalystSystemEfficiencyBelowThresholdBank1;
}
//
//void insert(Dcm_DTC DTC)
//{
//     struct node *temp = (struct node*)malloc(sizeof(struct node));
//	 struct node *ptr;
//
//     temp->infoDTC = DTC;
//     temp->next = NULL;
//
//     if(startDTCList == NULL)
//        {
//            startDTCList = temp;
//        }
//        else
//        {
//            ptr = startDTCList;
//            while(ptr->next != NULL)
//            {
//                ptr= ptr->next;
//            }
//
//            ptr->next = temp;
//        }
//	dtcs[numberOfDtcs++] = DTC;
//}

uint8_t reportNumberOfDTCByStatusMask(uint8_t statusMask)
{
    uint8_t numberOfDTCByStatusMask = 0;
//    struct node *ptr;
//
//    ptr = startDTCList;
//
//    while(ptr->next != NULL)
//    {
//        if (ptr->infoDTC.statusMask == statusMask)
//        {
//            numberOfDTCByStatusMask++;
//        }
//
//        ptr= ptr->next;
//    }
   for (int i = 0; i< numberOfDtcs; i++){
	   if((dtcs[i].statusMask & statusMask) == statusMask){
		   numberOfDTCByStatusMask++;
	   }
   }
  return numberOfDTCByStatusMask;
}


uint8_t Dcm_Service_ReadDTCInformation(uint8_t *requestMessageData, uint8_t requestMessageLength, uint8_t *responseData, uint8_t *responseDataLength)
{

	Dcm_DTC dtcs1[30];
	uint8_t numberOfDtcs1 = numberOfDtcs;
    for(int i=0;i<numberOfDtcs;i++)
    {
    	dtcs1[i] = dtcs[i];
    }

	switch(requestMessageData[1])
	{
		case ReportNumberOfDTCByStatusMask:
		{
			if (requestMessageLength != 0x03){
				return DCM_NRC_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT;
			} else {
				responseData[0] = requestMessageData[0] + 0x40;
				responseData[1] = requestMessageData[1];
				responseData[2] = 0xAB; //
				responseData[3] = 0x01; //
				responseData[4] = 0x00;
				responseData[5] = reportNumberOfDTCByStatusMask(requestMessageData[2]);
				*responseDataLength = 0x06;
				return 0x00;
			}
			break;
		}
	}
    return 0x00;
}

