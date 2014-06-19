#ifndef IPRODUCER_H
#define IPRODUCER_H

#include "Includes.h"
#include "Configuration.h"

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
    Queue* senderQueue;
    int senderQueueId;
    int producerId;
    ProcessInformation* getProcesses(int type);
    void showOutgoingOrder(ProductionOrder order, int itemType);
    void showProcessesResult(get_processes_result* getProcessesResult);
    bool thereAreConsumersFor(int itemType);
    NetworkMessage buildNetworkMessage(ProductionOrder productionOrder, ProcessInformation consumerProcess);
    void showOutgoingNetworkMessage(NetworkMessage networkMessage);
    void showOutgoingQueueMessage(QueueMessage queueMessage);
};

#endif // IPRODUCER_H
