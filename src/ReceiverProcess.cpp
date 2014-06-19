/*
 * ReceiverProcess.cpp
 *
 *  Created on: Jun 13, 2014
 *      Author: jp
 */

#include "Includes.h"
#include "Socket.h"

void notifyReceivedMessage(const QueueMessage& queueMessage, int id) {
	std::string msg = "receiving from ";
	msg += string(queueMessage.senderName) + " to "	+ string(queueMessage.receiverName);
	Process::announce(RECEIVER_PROCESS, id, YELLOW, msg.c_str());
}

int main(int argc, char** argv) {

	char* programName = argv[0];

	// Si se ingresan menos argumentos de los necesarios
	if (argc < 2) {
		string msg = "Usage ";
		msg = msg + programName + " <-use>\n";
		Colors::writeerr(msg, RED);
		exit(EXIT_FAILURE);
	}

	int id = 0;
    Process::announce(RECEIVER_PROCESS, id, UNDERLINEDYELLOW, "initializing.");

    //Queue::create(PRODUCTION_ORDERS_QUEUE_ID);
	ProductionOrder productionOrder;
	int bytes;

	Socket* socket = new Socket(RECEIVER_PROCESS);

	Configuration* configuration = new Configuration(CONFIGURATION_FILE);
	int receiverQueueId = configuration->getInt(RECEIVER_QUEUE_ID);
	string msg = "Reading configuration file --> RECEIVER_QUEUE_ID: ";
	msg = msg + Utils::intToString(receiverQueueId);
	Process::announce(RECEIVER_PROCESS, id, CYAN, msg.c_str());
	Queue* queue = Queue::create(receiverQueueId);

	int receiverListeningPort = configuration->getInt(RECEIVER_LISTENING_PORT);
	msg = "Reading configuration file --> RECEIVER_LISTENING_PORT: ";
	msg = msg + Utils::intToString(receiverListeningPort);
	Process::announce(RECEIVER_PROCESS, id, CYAN, msg.c_str());
	socket->passivate(receiverListeningPort);

	Socket* newSocket;
	while ( (newSocket = socket->acceptOrCreateNew()) != NULL) {
		pid_t pid = fork();
		if(pid == 0){
			while((bytes = newSocket->receive((char*) &productionOrder, sizeof(productionOrder))) > 0){
				Process::announce(RECEIVER_PROCESS, id, YELLOW, Process::showProductionOrder(productionOrder).c_str());
				queue->send((void*) &productionOrder, sizeof(productionOrder));
			}
		}
		else if(pid < 0) Process::announce(RECEIVER_PROCESS, id, RED, "error on fork");
		newSocket->destroy();
	}

	Process::announce(RECEIVER_PROCESS, id, RED, "error on accept");
	socket->destroy();

    Process::announce(RECEIVER_PROCESS, id, UNDERLINEDYELLOW, "finished.");
}

