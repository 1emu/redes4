/*
 * Structures.h
 *
 *  Created on: May 3, 2014
 *      Author: jp
 */

#ifndef STRUCTURES_H_
#define STRUCTURES_H_

#define ADDRESSES_LENGTH 256
#define NAMES_LENGTH 32

#include "RPC/IdManager.h"

typedef struct{
    long receiverId;
    int amountOfItems[3];
} ProductionOrder;

typedef struct{
    long receiver;
    long sender;
    char receiverName[NAMES_LENGTH];
    char senderName[NAMES_LENGTH];
    int senderClass;
    int fromId;
    int action;
    int orden;
    int amount;
} QueueMessage;

typedef struct{
    long to;
    long from;
    ProcessInformation processInformation;
    ProductionOrder productionOrder;
} NetworkMessage;

typedef struct{
    int action;
    ProcessInformation processInformation;
} idControllerMessage;

enum Items {PROCESSOR, MOTHERBOARD, DISK};
enum Actions {PRODUCE, END};

#endif /* STRUCTURES_H_ */
