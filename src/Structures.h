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
    char address[ADDRESSES_LENGTH];
    unsigned short port;
    int processType;
    int id;
    bool available;
} processInfo;

typedef struct{
    long to;
    long from;
    processInfo processInformation;
    QueueMessage queueMessage;
} NetworkMessage;

typedef struct{
    int action;
    processInfo processInformation;
} idControllerMessage;

typedef struct{
	long receiverId;
	int amountOfItems[3];
} ProductionOrder;

enum Items {PROCESSOR, MOTHERBOARD, DISK};
enum Actions {PRODUCE, END};

#endif /* STRUCTURES_H_ */
