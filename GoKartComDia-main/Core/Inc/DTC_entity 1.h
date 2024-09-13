/*
 * DTC_entity.h
 *
 *  Created on: Aug 28, 2024
 *      Author: MTA6CLJ
 */

#ifndef INC_DTC_ENTITY_H_
#define INC_DTC_ENTITY_H_



#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
//#include <Types.h>
#include <Dcm_Service_ClearDiagnosticInformation.h>

#define MAX_SNAPSHOTS 10

//linked list for DTCs snaphots
struct node_Snapshot
{
    uint8_t snapData[2];
    struct node_Snapshot *next;
};

typedef struct {
    uint8_t snapData[2];
} Snapshot;

//DTC
typedef struct
{
	uint32_t id;
	uint8_t statusMask;
	struct node_Snapshot *startSnapList;
	Snapshot snapshots[MAX_SNAPSHOTS];
	uint8_t nrSnapshots;
	uint8_t statusAvailabilityMask;
	uint8_t priority;  // 0x01 high; 0x02 medium; 0x03 low
	uint32_t groupOfDTC;
	uint8_t dataLength;
}Dcm_DTC;

void Dcm_DTC_Init();

extern Dcm_DTC DTC_0x0300_randomMultipleCylinderMisfireDetected;
extern Dcm_DTC DTC_0x0420_catalystSystemEfficiencyBelowThresholdBank1;
extern Dcm_DTC DTC_0x0171_systemTooLeanBank1;

extern int max_DTC;
extern volatile uint8_t numberOfDtcs;
extern volatile Dcm_DTC dtcs[];


//linked list for DTCs
struct node
{
    Dcm_DTC infoDTC;
    struct node *next;
};

#endif /* INC_DTC_ENTITY_H_ */
