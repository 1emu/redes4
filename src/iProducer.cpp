#include "iProducer.h"

using namespace std;

iProducer::iProducer() {
    // create connection with client
    this->clnt = clnt_create("localhost", IDMANAGER, ver1, "tcp");
	if (clnt == NULL) {
		clnt_pcreateerror ("localhost");
		exit (1);
	}
    this->producerId = registerAndGetId();

    Configuration* configuration = new Configuration(CONFIGURATION_FILE);

   	this->senderQueueId = configuration->getInt(SENDER_QUEUE_ID);
   	string msg = "Reading configuration file --> SENDER_QUEUE_ID: ";
   	Process::announce(RECEIVER_PROCESS, producerId, CYAN, (msg + Utils::intToString(senderQueueId)).c_str());

	this->senderType = configuration->getInt(SENDER_TYPE);
	msg = "Reading configuration file --> SENDER_TYPE: ";
	Process::announce(RECEIVER_PROCESS, producerId, CYAN, (msg + Utils::intToString(senderType)).c_str());


    senderQueue = Queue::get(senderQueueId);
    Process::announce(IPRODUCER, producerId, LIGHTGREEN, "created.");
}

void iProducer::sendToConsumers(ProductionOrder order) {

    ProcessInformation* consumerProcesses;
    int consumerType;
    for (consumerType = PROCESSOR; consumerType <= DISK; consumerType++) {
    	consumerProcesses = getProcesses(consumerType);
    	int consumerProcessNumber = 0;
        ProcessInformation consumerProcess = consumerProcesses[consumerProcessNumber];
        Process::announce(IPRODUCER, 0, LIGHTGREEN, 
    			Utils::intToString(consumerProcess.processId).c_str());
    	while(consumerProcess.processId != 0){
    		order.receiverId = consumerProcess.processId;
			showOutgoingOrder(order, consumerType);
			NetworkMessage networkMessage = buildNetworkMessage(order,
					consumerProcess);

			senderQueue->send(&networkMessage, sizeof(networkMessage));
            consumerProcessNumber++;
            consumerProcess = consumerProcesses[consumerProcessNumber];
    	}
	}

}

int iProducer::registerAndGetId() {

	Process::announce(IPRODUCER, 0, LIGHTGREEN, "registering to get an id.");

    ProcessInformation producerInfo;

    Configuration* configuration = new Configuration(CONFIGURATION_FILE);
    producerInfo.processType = configuration->getInt(PRODUCER_TYPE);
    string msg = "Reading configuration file --> PRODUCER_TYPE: ";
   	Process::announce(RECEIVER_PROCESS, producerId, CYAN, (msg + Utils::intToString(producerInfo.processType)).c_str());

    register_and_get_id_result  *result_1 = registerandgetid_1(&producerInfo, clnt);
    if (result_1 == (register_and_get_id_result *) NULL) {
        clnt_perror (clnt, "registerAndGetId failed for producer");
    }
    //clnt_destroy(clnt);
    return (*result_1).register_and_get_id_result_u.processId;
}

ProcessInformation* iProducer::getProcesses(int type) {

	string message =  "getting running processes of type = " + Utils::intToString(type);

	Process::announce(IPRODUCER, producerId, LIGHTGREEN, message.c_str());

    get_processes_result  *getProcessesResult = getprocesses_1(&type, clnt);

    Process::announce(IPRODUCER, producerId, LIGHTGREEN, "got processes result.");

    if (getProcessesResult == (get_processes_result *) NULL) {
        clnt_perror (clnt, "call failed");
    }
    else {
		string cod_ret = Utils::intToString((int)getProcessesResult->cod_ret);
    	string processes_len = Utils::intToString((int)getProcessesResult->get_processes_result_u.processes.processes_len);
		showProcessesResult(getProcessesResult);
    }
	ProcessInformation* runningProcessesOfRequestedType =
			(*getProcessesResult).get_processes_result_u.processes.processes_val;

    return runningProcessesOfRequestedType;
}

void iProducer::showOutgoingOrder(ProductionOrder order, int itemType){
	string sendingOrderTo = "sending order to consumer #id ";
	string receiverId_str = Utils::intToString((int)order.receiverId);
	string message = sendingOrderTo + receiverId_str + ", itemType: " + Process::nameForItemType(itemType);
	Process::announce(IPRODUCER, this->producerId, LIGHTGREEN, message.c_str());
}

bool iProducer::consumersAreReady() {
	bool consumersAreReady = true;
	int itemType;

	for (itemType = PROCESSOR; itemType <= DISK; ++itemType) {
		consumersAreReady = consumersAreReady && thereAreConsumersFor(itemType);
	}

	return consumersAreReady;
}

bool iProducer::thereAreConsumersFor(int itemType){
	bool thereAre = false;

	ProcessInformation* consumerProcesses = getProcesses(itemType);
	int firstConsumerProcess = 0;
	ProcessInformation consumerProcess = consumerProcesses[firstConsumerProcess];
	if(consumerProcess.processId != 0){
		if(consumerProcess.running > 0 && consumerProcess.processType == itemType){
			thereAre = true;
		}
	}

	return thereAre;
}

void iProducer::showProcessesResult(get_processes_result* getProcessesResult){
	string getProcessesResultStr = "# got processes result : ";
	string cod_ret = Utils::intToString((int)getProcessesResult->cod_ret);
	string processes_len = Utils::intToString((int)getProcessesResult->get_processes_result_u.processes.processes_len);
	string message = getProcessesResultStr + "cod_ret = " + cod_ret + " processes_len = " + processes_len;
	Process::announce(IPRODUCER, this->producerId, LIGHTGREEN, message.c_str());
}

int iProducer::getRegisteredId() {
	return this->producerId;
}

NetworkMessage iProducer::buildNetworkMessage(ProductionOrder productionOrder,
		ProcessInformation consumerProcess) {
	NetworkMessage networkMessage;
	networkMessage.to = this->senderType;
	networkMessage.from = this->producerId;
	networkMessage.processInformation = consumerProcess;
	networkMessage.productionOrder = productionOrder;
	return networkMessage;
}

void iProducer::showOutgoingNetworkMessage(NetworkMessage networkMessage) {
	string msg = "Network message built: \n";
	msg += string("- from: ") + Utils::intToString(networkMessage.from) + "\n";
	msg += string("- to: ") + Utils::intToString(networkMessage.to) + "\n";
	Process::announce(IPRODUCER, this->producerId, LIGHTGREEN, msg.c_str());
}
