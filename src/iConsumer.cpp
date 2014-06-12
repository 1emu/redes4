/*
 * iConsumer.cpp
 *
 *  Created on: Jun 5, 2014
 *      Author: jp
 */

#include "iConsumer.h"

iConsumer::iConsumer(int consumerType)
{
	this->clnt = clnt_create("localhost", IDMANAGER, ver1, "tcp");
	if (clnt == NULL) {
		clnt_pcreateerror ("localhost");
		exit (1);
	}
    this->consumerType = consumerType;
    this->consumerId = registerAndGetId();
    ordersQueue = Queue::get(PRODUCTION_ORDERS_QUEUE_ID);
    // create connection with client
    Process::announce(ICONSUMER, consumerId, LIGHTPURPLE, "created.");
}

ProductionOrder iConsumer::receiveFromProducer() {
    ProductionOrder receivedOrder;

    receivedOrder.receiverId = -1;
    receivedOrder.amountOfItems[PROCESSOR] = -1;
    receivedOrder.amountOfItems[MOTHERBOARD] = -1;
    receivedOrder.amountOfItems[DISK] = -1;
    Process::announce(ICONSUMER, consumerId, LIGHTPURPLE, "receiving order.");
    ordersQueue->receive(&receivedOrder, sizeof(receivedOrder), consumerId);
    Process::announce(ICONSUMER, consumerId, LIGHTPURPLE, "order received.");
    return receivedOrder;
}

int iConsumer::registerAndGetId()
{
    ProcessInformation consumerInfo;
    consumerInfo.processType = this->consumerType;

    Process::announce(ICONSUMER, 0, LIGHTPURPLE, "registering to get an id.");

    register_and_get_id_result  *result_1 = registerandgetid_1(&consumerInfo, clnt);
    if (result_1 == (register_and_get_id_result *) NULL) {
        clnt_perror (clnt, "registerAndGetId failed at consumer");
    }
    //clnt_destroy(clnt);
    return (*result_1).register_and_get_id_result_u.processId;
}

int iConsumer::getRegisteredId() {
	return this->consumerId;
}
