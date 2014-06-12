#include "iProducer.h"

iProducer::iProducer() {
    this->producerId = registerAndGetId();
    ordersQueue = Queue::get(PRODUCTION_ORDERS_QUEUE_ID);
    Process::announce(IPRODUCER, producerId, LIGHTGREEN, "created.");
}

bool iProducer::sendToConsumers(ProductionOrder order) {
    ProcessInformation consumerInfo;

    consumerInfo = getProcesses(PROCESSOR);
    order.receiverId = consumerInfo.processId;
    showOutcomingOrder(order);
    ordersQueue->send(&order, sizeof(order));

    consumerInfo = getProcesses(MOTHERBOARD);
    order.receiverId = consumerInfo.processId;
    showOutcomingOrder(order);
    ordersQueue->send(&order, sizeof(order));

    consumerInfo = getProcesses(DISK);
    order.receiverId = consumerInfo.processId;
    showOutcomingOrder(order);
    ordersQueue->send(&order, sizeof(order));

    return true;
}

int iProducer::registerAndGetId() {

	Process::announce(IPRODUCER, 0, LIGHTGREEN, "registering to get an id.");

    ProcessInformation producerInfo;
    producerInfo.processType = PRODUCER;

    CLIENT *clnt = clnt_create ("localhost", IDMANAGER, ver1, "udp");
    if (clnt == NULL) {
        clnt_pcreateerror ("localhost");
        exit (1);
    }
    register_and_get_id_result  *result_1 = registerandgetid_1(&producerInfo, clnt);
    if (result_1 == (register_and_get_id_result *) NULL) {
        clnt_perror (clnt, "registerAndGetId failed for producer");
    }
    clnt_destroy(clnt);
    return (*result_1).register_and_get_id_result_u.processId;
}

ProcessInformation iProducer::getProcesses(int type) {

	Process::announce(IPRODUCER, producerId, LIGHTGREEN, "getting running consumer processes.");
	ProcessInformation consumerInfo;

    get_processes_result  *getProcessesResult;
    CLIENT *clnt = clnt_create ("localhost", IDMANAGER, ver1, "udp");
    if (clnt == NULL) {
        clnt_pcreateerror ("localhost");
        exit (1);
    }
    getProcessesResult = getprocesses_1(&type, clnt);
    if (getProcessesResult == (get_processes_result *) NULL) {
        clnt_perror (clnt, "call failed");
    }
    clnt_destroy(clnt);
    int i;
    for(i = 0; (u_int)i < (*getProcessesResult).get_processes_result_u.processes.processes_len; i++){
        if((*getProcessesResult).get_processes_result_u.processes.processes_val[i].processType == type){
            consumerInfo = (*getProcessesResult).get_processes_result_u.processes.processes_val[i];
        }
    }
    return consumerInfo;
}

void iProducer::showOutcomingOrder(ProductionOrder order){
	std::string sendingOrderTo = "sending order to ";
	std::string receiverId_str = Utils::intToString((int)order.receiverId);
	std::string message = sendingOrderTo + receiverId_str;
	Process::announce(IPRODUCER, this->producerId, LIGHTGREEN, message.c_str());
}

int iProducer::getRegisteredId() {
	return this->producerId;
}
