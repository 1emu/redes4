/*
 * Process.cpp
 *
 *  Created on: May 3, 2014
 *      Author: jp
 */

#include "Process.h"

using namespace std;

string Process::getNameForProcess(const char* process_type, int id){
	string processName = process_type;
	processName = processName + " #" + Utils::intToString(id);
	return processName;
}

void Process::announce(const char* processType, int id, const char* color, const char* msg){
	string processMessage = Process::getNameForProcess(processType, id) + ": "
			+ msg;
	Colors::writeout(processMessage, color);
}

int Process::sleepTime(){
	return Utils::generateRandomNumberBetween(SLEEP_TIME_MIN, SLEEP_TIME_MAX);
}

void Process::createProcesses(string processName, unsigned int amountOfProcesses) {
	pid_t child; // child processes id's

	/* Prepare strings for the process creation functions */
	string excecString = "./";
	excecString = excecString + processName;

	string perrorExeclpString = " - error on execlp: ";
	perrorExeclpString = processName + perrorExeclpString;

	string perrorForkString = " - error on fork: ";
	perrorForkString = processName + perrorForkString;

	/* Create child processes */
	for (int producerProcessNumber = 0 + 1;
			producerProcessNumber <= amountOfProcesses; producerProcessNumber++) {
		child = fork();
		if (child == 0) {
			string processCreated = processName + " created";
			Process::announce(processName.c_str(), producerProcessNumber, LIGHTBLUE, processCreated.c_str());
			execlp( excecString.c_str(),
					processName.c_str(),
					Utils::intToString(producerProcessNumber).c_str(),
					NULL);
			perror(perrorExeclpString.c_str());
			exit(EXIT_FAILURE);
		} else if (child < 0) {
			perror(perrorForkString.c_str());
		}
	}
}

string Process::nameForItemType(int itemType) {
	if(itemType == PROCESSOR) return string("PROCESSOR");
	if(itemType == MOTHERBOARD) return string("MOTHERBOARD");
	if(itemType == DISK) return string("DISK");
	return string("UNKNOWN ITEM TYPE");
}

string Process::showQueueMessage(QueueMessage queueMessage) {
	string msg = "Queue message built: \n";
	msg += string("- action: ") + Utils::intToString(queueMessage.action) + "\n";
	msg += string("- amount: ") + Utils::intToString(queueMessage.amount) + "\n";
	msg += string("- fromId: ") + Utils::intToString(queueMessage.fromId) + "\n";
	msg += string("- receiver: ") +Utils::intToString(queueMessage.receiver) + "\n";
	msg += string("- receiverName: ") + queueMessage.receiverName + "\n";
	msg += string("- sender: ") + Utils::intToString(queueMessage.sender) + "\n";
	msg += string("- senderClass: ") + Utils::intToString(queueMessage.senderClass) + "\n";
	msg += string("- senderName: ") + queueMessage.senderName + "\n";
	return msg;
}

string Process::showNetworkMessage(NetworkMessage networkMessage) {
	string msg = "Network message built: \n";
	msg += string("- from: ") + Utils::intToString(networkMessage.from) + "\n";
	msg += string("- to: ") + Utils::intToString(networkMessage.to) + "\n";
	return msg;
}