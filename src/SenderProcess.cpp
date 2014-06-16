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
	return true;
}

bool thereAreProductionOrdersInQueue(){
	return true;
}

void notifySentMessage(const QueueMessage& queueMessage, int id) {
	std::string msg = "sending from ";
	msg += string(queueMessage.senderName) + " to " + string(queueMessage.receiverName);
	Process::announce(SENDER_PROCESS, id, UNDERLINEDYELLOW, msg.c_str());
}

void sendProductionOrders(NetworkMessage networkMessage, QueueMessage queueMessage, int bytes, int id, Queue* queue, Socket* socket) {
	do {
		queue->receive((void*) &networkMessage, sizeof(networkMessage),
				SENDER_TYPE);
		queueMessage = networkMessage.queueMessage;
		int result = socket->activate(string(networkMessage.processInformation.address),	networkMessage.processInformation.port);
		if(result != 0) {
			Process::announce(SENDER_PROCESS, id, UNDERLINEDRED, "error on socket when sending production orders.");
		}
		bytes = socket->send((char*) &queueMessage, sizeof(queueMessage));
		notifySentMessage(queueMessage, id);
		socket->destroy();
	} while (bytes >= 0);
}

int main(int argc, char** argv) {

	char* programName = argv[0];

	int id = 0;
    Process::announce(SENDER_PROCESS, id, UNDERLINEDYELLOW, "initializing.");

    Queue::create(PRODUCTION_ORDERS_QUEUE_ID);

    QueueMessage queueMessage;
	NetworkMessage networkMessage;
	int bytes;

	Socket* socket = new Socket(SENDER_PROCESS);
	Queue* queue = Queue::create(SENDER_QUEUE_ID);

    while(thereAreProducers() || thereAreProductionOrdersInQueue()){
		sendProductionOrders(networkMessage, queueMessage, bytes, id, queue, socket);
    	sleep(1);
    }

    Process::announce(SENDER_PROCESS, id, UNDERLINEDYELLOW, "finished.");

    return 0;
}









