/*
 * SenderProcess.cpp
 *
 * 	This process waits for outgoing orders on the production orders queue,
 * 	and sends them through the network
 *
 *  Created on: Jun 11, 2014
 *      Author: jp
 */

#include "Includes.h"
#include "Socket.h"


bool thereAreProducers(){
	//TODO
	return true;
}

bool thereAreProductionOrdersInQueue(){
	//TODO
	return true;
}

void sendProductionOrders(int id, Queue* queue, Socket* socket, int senderType) {
	
	NetworkMessage networkMessage;
	ProductionOrder productionOrder;
	int bytes = 0;

	do {

		Process::announce(SENDER_PROCESS, id, UNDERLINEDYELLOW, "waiting orders from iProducer");
		queue->receive((void*) &networkMessage, sizeof(networkMessage),	senderType);
		productionOrder = networkMessage.productionOrder;
		Process::announce(SENDER_PROCESS, id, YELLOW, "order received from iProducer");
		
		Process::announce(SENDER_PROCESS, id, YELLOW, Process::showProductionOrder(productionOrder).c_str());


		//TODO: use address and port from process information sent by id manager
		// this information should be set in the consumer process
		//int result = socket->activate("localhost", receiverListeningPort);
		//int result = socket->activate(string(networkMessage.processInformation.address), networkMessage.processInformation.port);
		int result = socket->activate(string("localhost"), 27015);

		if(result != 0) {
			Process::announce(SENDER_PROCESS, id, UNDERLINEDRED, "error on socket when sending production orders.");
		}
		bytes = socket->send((char*) &productionOrder, sizeof(productionOrder));
		
		Process::announce(SENDER_PROCESS, id, YELLOW, "production order sent");
		
		socket->destroy();
	} while (bytes >= 0);
}

int main(int argc, char** argv) {

	int id = 0;
    Process::announce(SENDER_PROCESS, id, UNDERLINEDYELLOW, "initializing.");

	Configuration* configuration = new Configuration(CONFIGURATION_FILE);

    int senderQueueId = configuration->getInt(SENDER_QUEUE_ID);
	string msg = "Reading configuration file --> SENDER_QUEUE_ID: ";
	Process::announce(SENDER_PROCESS, id, CYAN, (msg + Utils::intToString(senderQueueId)).c_str());

	int senderType = configuration->getInt(SENDER_TYPE);
	msg = "Reading configuration file --> SENDER_TYPE: ";
	Process::announce(SENDER_PROCESS, id, CYAN, (msg + Utils::intToString(senderType)).c_str());

    Socket* socket = new Socket(SENDER_PROCESS);
	Queue* queue = Queue::create(senderQueueId);

    while(thereAreProducers() || thereAreProductionOrdersInQueue()){
		sendProductionOrders(id, queue, socket, senderType);
    	sleep(1);
    }

    Process::announce(SENDER_PROCESS, id, UNDERLINEDYELLOW, "finished.");

    return 0;
}









