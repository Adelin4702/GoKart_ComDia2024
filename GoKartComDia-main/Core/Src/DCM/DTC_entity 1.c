/*
 * DTC_entity.c
 *
 *  Created on: Aug 28, 2024
 *      Author: MTA6CLJ
 */

#include <DTC_entity 1.h>


void Dcm_DTC_Init()
{
	///DTC's list
	//HAL_FLASH_Lock();

	//struct node *temp = (struct node *)calloc(1, sizeof(struct node));
	//int* array = (int*)malloc(10*sizeof(int));

//	temp = startDTCList;
    uint8_t snap[2];

    DTC_0x0171_systemTooLeanBank1.id = 0x0171;
    DTC_0x0171_systemTooLeanBank1.statusMask = 0x10; // Indicating a lean condition in Bank 1
   // DTC_0x0171_systemTooLeanBank1.startSnapList = NULL;
    DTC_0x0171_systemTooLeanBank1.dataLength = 0x02;
    DTC_0x0171_systemTooLeanBank1.priority = MEDIUM_PRIORITY;
    DTC_0x0171_systemTooLeanBank1.groupOfDTC = FUEL_AND_AIR_METERING;

    //Hypothetical hexadecimal data representing air-fuel mixture and sensor readings
    snap[0] = 0xEF;
    snap[1] = 0xEF;
    //insertSnapshot(snap, &DTC_0x0171_systemTooLeanBank1);
    insertSnapShot_array(snap, &DTC_0x0171_systemTooLeanBank1);

    snap[0] = 0xE0;
    snap[1] = 0x1F;
//  insertSnapshot(snap, &DTC_0x0171_systemTooLeanBank1);
    insertSnapShot_array(snap, &DTC_0x0171_systemTooLeanBank1);

   ///insert(DTC_0x0171_systemTooLeanBank1, &startDTCList);
    insertDTC(dtcs, &numberOfDtcs, max_DTC, DTC_0x0171_systemTooLeanBank1);

    DTC_0x0300_randomMultipleCylinderMisfireDetected.id = 0x0300;
    DTC_0x0300_randomMultipleCylinderMisfireDetected.statusMask = 0x08; // Indicating multiple misfires in the cylinders
   // DTC_0x0300_randomMultipleCylinderMisfireDetected.startSnapList = NULL;
    DTC_0x0300_randomMultipleCylinderMisfireDetected.dataLength = 0x02;
    DTC_0x0300_randomMultipleCylinderMisfireDetected.priority = MEDIUM_PRIORITY;
    DTC_0x0300_randomMultipleCylinderMisfireDetected.groupOfDTC = POWERTRAIN;

    // Hypothetical hexadecimal data representing details of misfire events
    snap[0] = 0x12;
    snap[1] = 0x34;
//    insertSnapshot(snap, &DTC_0x0300_randomMultipleCylinderMisfireDetected);
    insertSnapShot_array(snap, &DTC_0x0300_randomMultipleCylinderMisfireDetected);

   // insert(DTC_0x0300_randomMultipleCylinderMisfireDetected, &startDTCList);
    insertDTC(dtcs, &numberOfDtcs, max_DTC, DTC_0x0300_randomMultipleCylinderMisfireDetected);

    DTC_0x0420_catalystSystemEfficiencyBelowThresholdBank1.id = 0x0420;
    DTC_0x0420_catalystSystemEfficiencyBelowThresholdBank1.statusMask = 0x08; //Indicating catalyst efficiency issue in Bank 1
   // DTC_0x0420_catalystSystemEfficiencyBelowThresholdBank1.startSnapList = NULL;
    DTC_0x0420_catalystSystemEfficiencyBelowThresholdBank1.dataLength = 0x02;
    DTC_0x0420_catalystSystemEfficiencyBelowThresholdBank1.priority = MEDIUM_PRIORITY;
    DTC_0x0420_catalystSystemEfficiencyBelowThresholdBank1.groupOfDTC = EMISSION_CONTROL;

    // Hypothetical hexadecimal data representing sensor readings and engine conditions
    snap[0] = 0xAB;
    snap[1] = 0xCD;
//    insertSnapshot(snap, &DTC_0x0420_catalystSystemEfficiencyBelowThresholdBank1);
    insertSnapShot_array(snap, &DTC_0x0420_catalystSystemEfficiencyBelowThresholdBank1);

   // insert(DTC_0x0420_catalystSystemEfficiencyBelowThresholdBank1, &startDTCList);
    insertDTC(dtcs, &numberOfDtcs, max_DTC, DTC_0x0420_catalystSystemEfficiencyBelowThresholdBank1);



    uint32_t id_var = 0;
    for(int i=0;i<numberOfDtcs;i++)
    {
    	//printf("%d ", DTCList[i].id);
    	id_var = dtcs[i].id;
    }
//    struct node *currentDTC = startDTCList;
//    while (currentDTC != NULL) {
//
//    	  struct node *nextDTC = currentDTC->next;
//    	        free(currentDTC);
//    	        currentDTC = nextDTC;
//
//    }
}

//insert DTC
void insert(Dcm_DTC DTC, struct node** startDTCList)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));

    if (temp == NULL) {
        exit(1);
    }

    temp->infoDTC = DTC;
    temp->next = NULL;

    if (*startDTCList == NULL) {
        *startDTCList = temp;
    }
    else {
        struct node *ptr = *startDTCList;

        while (ptr->next != NULL) {
            ptr = ptr->next;
        }
        ptr->next = temp;
    }
}

//insert Snapshot
void insertSnapshot(uint8_t data[2], Dcm_DTC *dtc)
{
    struct node_Snapshot *temp = (struct node_Snapshot*)malloc(sizeof(struct node_Snapshot));

    if (temp == NULL) {
        exit(1);
    }

    temp->snapData[0] = data[0];
    temp->snapData[1] = data[1];
    temp->next = NULL;

    if (dtc->startSnapList == NULL) {
        dtc->startSnapList = temp;
    }
    else {
        struct node_Snapshot *ptr = dtc->startSnapList;

        while (ptr->next != NULL) {
            ptr = ptr->next;
        }
        ptr->next = temp;
    }
}

//delete the snapshots for a DTC
void delete_Snap(struct node_Snapshot** start)
{
   struct node_Snapshot* current = *start;
   struct node_Snapshot* next;

   while (current != NULL)
   {
       next = current->next;
       free(current);
       current = next;
   }

   *start = NULL;
}




