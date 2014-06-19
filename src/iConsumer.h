/*
 * iConsumer.h
 *
 *  Created on: Jun 5, 2014
 *      Author: jp
 */

#ifndef ICONSUMER_H_
#define ICONSUMER_H_

#include "Includes.h"
#include "Configuration.h"

class iConsumer
{
public:
    iConsumer(int consumerType);
    ProductionOrder receiveFromProducer();
    int getRegisteredId();
    void unregister();
    CLIENT *clnt;

private:
    Queue* ordersQueue;
    int consumerId;
    int consumerType;
    int receiverQueueId;
    int port;
    int registerAndGetId();
};

#endif /* ICONSUMER_H_ */
