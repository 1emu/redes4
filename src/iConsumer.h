/*
 * iConsumer.h
 *
 *  Created on: Jun 5, 2014
 *      Author: jp
 */

#ifndef ICONSUMER_H_
#define ICONSUMER_H_

#include "Includes.h"

class iConsumer
{
public:
    iConsumer(int consumerType);
    ProductionOrder receiveFromProducer();
    int getRegisteredId();
private:
    Queue* ordersQueue;
    int consumerId;
    int consumerType;
    int registerAndGetId();
};

#endif /* ICONSUMER_H_ */
