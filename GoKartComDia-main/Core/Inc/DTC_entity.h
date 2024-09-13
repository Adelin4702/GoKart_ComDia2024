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
#include <Types.h>

//linked list for DTCs snaphots
struct node_Snapshot
{
    uint8_t snapData[2];
    struct node_Snapshot *next;
};

//typedef struct {
//    uint8_t snapData[2];
//} Snapshot;

//DTC



//linked list for DTCs
struct node
{
    Dcm_DTC1 infoDTC;
    struct node *next;
};

#endif /* INC_DTC_ENTITY_H_ */
