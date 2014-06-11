#ifndef IPRODUCER_H
#define IPRODUCER_H

#include "Includes.h"


class iProducer
{
public:
    iProducer();
    bool sendToConsumers(ProductionOrder order);

private:
    Queue* ordersQueue;
    int producerId;
    int registerAndGetId();
    ProcessInformation getProcesses(int type);
    void showOutcomingOrder(ProductionOrder order);
};

#endif // IPRODUCER_H
