#ifndef IPRODUCER_H
#define IPRODUCER_H

#include "Includes.h"


class iProducer
{
public:
    iProducer();
    void sendToConsumers(ProductionOrder order);
    bool consumersAreReady();
    int getRegisteredId();
    CLIENT *clnt;

private:
    int registerAndGetId();
    Queue* ordersQueue;
    int producerId;
    ProcessInformation* getProcesses(int type);
    void showOutcomingOrder(ProductionOrder order, int itemType);
    void showProcessesResult(get_processes_result* getProcessesResult);
    bool thereAreConsumersFor(int itemType);
};

#endif // IPRODUCER_H
