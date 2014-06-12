#ifndef IPRODUCER_H
#define IPRODUCER_H

#include "Includes.h"


class iProducer
{
public:
    iProducer();
    bool sendToConsumers(ProductionOrder order);
    int getRegisteredId();

private:
    int registerAndGetId();
    Queue* ordersQueue;
    int producerId;
    ProcessInformation getProcesses(int type);
    void showOutcomingOrder(ProductionOrder order);
};

#endif // IPRODUCER_H
