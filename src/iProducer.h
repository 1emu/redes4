#ifndef IPRODUCER_H
#define IPRODUCER_H

#include "Includes.h"


class iProducer
{
public:
    iProducer();
    bool sendToConsumers(ProductionOrder order);
    int getRegisteredId();
    CLIENT *clnt;

private:
    int registerAndGetId();
    Queue* ordersQueue;
    int producerId;
    ProcessInformation getProcesses(int type);
    void showOutcomingOrder(ProductionOrder order);
    void showProcessesResult(get_processes_result* getProcessesResult);
};

#endif // IPRODUCER_H
