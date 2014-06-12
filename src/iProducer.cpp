#include "iProducer.h"

iProducer::iProducer() {
    // create connection with client
    this->clnt = clnt_create("localhost", IDMANAGER, ver1, "tcp");
	if (clnt == NULL) {
		clnt_pcreateerror ("localhost");
		exit (1);
	}
    this->producerId = registerAndGetId();
    ordersQueue = Queue::get(PRODUCTION_ORDERS_QUEUE_ID);
    Process::announce(IPRODUCER, producerId, LIGHTGREEN, "created.");
}

void iProducer::sendToConsumers(ProductionOrder order) {

    ProcessInformation* consumerProcesses;

    int consumerType;
    for (consumerType = PROCESSOR; consumerType < DISK; ++consumerType) {
    	consumerProcesses = getProcesses(consumerType);
    	int consumerProcessNumber = 0;
    	ProcessInformation consumerProcess = consumerProcesses[consumerProcessNumber];
    	while(consumerProcess.processId != 0){
    		order.receiverId = consumerProcess.processId;
			showOutcomingOrder(order);
			ordersQueue->send(&order, sizeof(order));
    	}
	}

}

int iProducer::registerAndGetId() {

	Process::announce(IPRODUCER, 0, LIGHTGREEN, "registering to get an id.");

    ProcessInformation producerInfo;
    producerInfo.processType = PRODUCER_TYPE;

    register_and_get_id_result  *result_1 = registerandgetid_1(&producerInfo, clnt);
    if (result_1 == (register_and_get_id_result *) NULL) {
        clnt_perror (clnt, "registerAndGetId failed for producer");
    }
    //clnt_destroy(clnt);
    return (*result_1).register_and_get_id_result_u.processId;
}

ProcessInformation* iProducer::getProcesses(int type) {

	std::string message =  "getting running processes of type = " + Utils::intToString(type);

	Process::announce(IPRODUCER, producerId, LIGHTGREEN, message.c_str());

    get_processes_result  *getProcessesResult = getprocesses_1(&type, clnt);

    Process::announce(IPRODUCER, producerId, LIGHTGREEN, "got processes result.");

    if (getProcessesResult == (get_processes_result *) NULL) {
        clnt_perror (clnt, "call failed");
    }
    else {
		std::string cod_ret = Utils::intToString((int)getProcessesResult->cod_ret);
    	std::string processes_len = Utils::intToString((int)getProcessesResult->get_processes_result_u.processes.processes_len);
		showProcessesResult(getProcessesResult);
    }
	ProcessInformation* runningProcessesOfRequestedType =
			(*getProcessesResult).get_processes_result_u.processes.processes_val;


    /*int i;
    for(i = 0; (u_int) i < (*getProcessesResult).get_processes_result_u.processes.processes_len; i++){
		ProcessInformation process = (*getProcessesResult).get_processes_result_u.processes.processes_val[i];
		if (isARunningProcessOfTheRequestedType(process, type)) {
            consumerInfo = (*getProcessesResult).get_processes_result_u.processes.processes_val[i];
        }
    }*/

    return runningProcessesOfRequestedType;
}

void iProducer::showOutcomingOrder(ProductionOrder order){
	std::string sendingOrderTo = "sending order to consumer #id ";
	std::string receiverId_str = Utils::intToString((int)order.receiverId);
	std::string message = sendingOrderTo + receiverId_str;
	Process::announce(IPRODUCER, this->producerId, LIGHTGREEN, message.c_str());
}

void iProducer::showProcessesResult(get_processes_result* getProcessesResult){
	std::string getProcessesResultStr = "# get processes result : ";
	std::string cod_ret = Utils::intToString((int)getProcessesResult->cod_ret);
	std::string processes_len = Utils::intToString((int)getProcessesResult->get_processes_result_u.processes.processes_len);
	std::string message = getProcessesResultStr + "cod_ret = " + cod_ret + " processes_len = " + processes_len;
	Process::announce(IPRODUCER, this->producerId, LIGHTGREEN, message.c_str());
}

int iProducer::getRegisteredId() {
	return this->producerId;
}
