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

void sendProductionOrders(int id, Queue* queue, Socket* socket) {
	
	NetworkMessage networkMessage;
	ProductionOrder productionOrder;
	int bytes = 0;

	do {
		
		queue->receive((void*) &networkMessage, sizeof(networkMessage),
				SENDER_TYPE);
		productionOrder = networkMessage.productionOrder;
		
		Process::announce(SENDER_PROCESS, id, UNDERLINEDRED, Process::showProductionOrder(productionOrder).c_str());

		//int result = socket->activate(string(networkMessage.processInformation.address), networkMessage.processInformation.port);
		int result = socket->activate("localhost", RECEIVER_LISTENING_PORT);
		if(result != 0) {
			Process::announce(SENDER_PROCESS, id, UNDERLINEDRED, "error on socket when sending production orders.");
		}
		bytes = socket->send((char*) &productionOrder, sizeof(productionOrder));
		
		Process::announce(SENDER_PROCESS, id, UNDERLINEDYELLOW, "sending production order");
		
		socket->destroy();
		
		bytes = socket->send((char*) &productionOrder, sizeof(productionOrder));
		
		socket->destroy();
	} while (bytes >= 0);
}

int main(int argc, char** argv) {

	int id = 0;
    Process::announce(SENDER_PROCESS, id, UNDERLINEDYELLOW, "initializing.");

    Socket* socket = new Socket(SENDER_PROCESS);
	Queue* queue = Queue::create(SENDER_QUEUE_ID);

    while(thereAreProducers() || thereAreProductionOrdersInQueue()){
		sendProductionOrders(id, queue, socket);
    	sleep(1);
    }

    Process::announce(SENDER_PROCESS, id, UNDERLINEDYELLOW, "finished.");

    return 0;
}









