/*
 * Terminator.cpp
 *
 *  Created on: May 4, 2014
 *      Author: jp
 */

#include "Includes.h"
#include "Configuration.h"
#include "Queue.h"

int main(){
	int id = 101010;
	Configuration* configuration = new Configuration(CONFIGURATION_FILE);

	int receiverQueueId = configuration->getInt(RECEIVER_QUEUE_ID);
	std::string msg = "Reading configuration file --> RECEIVER_QUEUE_ID: ";
	msg = msg + Utils::intToString(receiverQueueId);
	Process::announce(RECEIVER_PROCESS, id, CYAN, msg.c_str());

	int senderQueueId = configuration->getInt(SENDER_QUEUE_ID);
	msg = "Reading configuration file --> SENDER_QUEUE_ID: ";
	msg = msg + Utils::intToString(senderQueueId);
	Process::announce(RECEIVER_PROCESS, id, CYAN, msg.c_str());

    Queue::destroy(receiverQueueId);
    Queue::destroy(senderQueueId);
    msg = "Termination complete.";
    Colors::writeout(msg, UNDERLINEDGREEN);
    return 0;
}



