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
	for (unsigned int producerProcessNumber = 0 + 1;
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

string Process::showNetworkMessage(NetworkMessage networkMessage) {
	string msg = "Network message built: \n";
	msg += string("- from: ") + Utils::intToString(networkMessage.from) + "\n";
	msg += string("- to: ") + Utils::intToString(networkMessage.to) + "\n";
	return msg;
}

string Process::showProductionOrder(const ProductionOrder& po) {
	string announcement = "Orden de Compra =[ "
			+ Utils::intToString(po.amountOfItems[PROCESSOR]) + "P , "
			+ Utils::intToString(po.amountOfItems[MOTHERBOARD])
			+ " M , " + Utils::intToString(po.amountOfItems[DISK])
			+ "D ] - receiver id #"
			+ Utils::longToString(po.receiverId);
	return announcement;
}
