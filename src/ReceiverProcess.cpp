/*
 * ReceiverProcess.cpp
 *
 *  Created on: Jun 13, 2014
 *      Author: jp
 */

#include "Includes.h"

void notifyReceivedMessage(const QueueMessage& queueMessage, int id) {
	std::string msg = "receiving from " + queueMessage.senderName + " to "
			+ queueMessage.receiverName;
	Process::announce(RECEIVER_PROCESS, id, UNDERLINEDYELLOW, msg.c_str());
}

int main(int argc, char** argv) {

	char* programName = argv[0];

	int id = 0;
    Process::announce(RECEIVER_PROCESS, id, UNDERLINEDYELLOW, "initializing.");

    Queue::create(PRODUCTION_ORDERS_QUEUE_ID);

    QueueMessage queueMessage;
	NetworkMessage networkMessage;
	int bytes;

	Socket* socket = new Socket(RECEIVER_PROCESS);
	Queue* queue = Queue::create(RECEIVER_QUEUE_ID);

	socket->passivate(RECEIVER_LISTENING_PORT);

	Socket* newSocket;
	while ((newSocket = socket->acceptOrCreateNew()) != NULL) {
		pid_t pid = fork();
		if(pid == 0){
			while((bytes = newSocket->receive((char*) &queueMessage, sizeof(queueMessage))) > 0){
				notifyReceivedMessage(queueMessage, id);
				queue->send((void*) &queueMessage, sizeof(queueMessage));
			}
		}
		else if(pid < 0) Process::announce(RECEIVER_PROCESS, id, RED, "error on fork");
		newSocket->destroy();
	}

	Process::announce(RECEIVER_PROCESS, id, RED, "error on accept");
	socket->destroy();

    Process::announce(RECEIVER_PROCESS, id, UNDERLINEDYELLOW, "finished.");
}
