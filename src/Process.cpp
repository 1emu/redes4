/*
 * Process.cpp
 *
 *  Created on: May 3, 2014
 *      Author: jp
 */

#include "Process.h"


std::string Process::getNameForProcess(const char* process_type, int id){
	std::string processName = process_type;
	processName = processName + " #" + Utils::intToString(id);
	return processName;
}

void Process::announce(const char* processType, int id, const char* color, const char* msg){
	std::string processMessage = Process::getNameForProcess(processType, id) + ": "
			+ msg;
	Colors::writeout(processMessage, color);
}

int Process::sleepTime(){
	return Utils::generateRandomNumberBetween(SLEEP_TIME_MIN, SLEEP_TIME_MAX);
}

void Process::createProcesses(std::string processName, unsigned int amountOfProcesses) {
	pid_t child; // child processes id's

	/* Prepare strings for the process creation functions */
	std::string excecString = "./";
	excecString = excecString + processName;

	std::string perrorExeclpString = " - error on execlp: ";
	perrorExeclpString = processName + perrorExeclpString;

	std::string perrorForkString = " - error on fork: ";
	perrorForkString = processName + perrorForkString;

	/* Create child processes */
	for (int producerProcessNumber = 0 + 1;
			producerProcessNumber <= amountOfProcesses; producerProcessNumber++) {
		child = fork();
		if (child == 0) {
			std::string processCreated = processName + " created";
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

std::string Process::nameForItemType(int itemType) {
	if(itemType == PROCESSOR) return std::string("PROCESSOR");
	if(itemType == MOTHERBOARD) return std::string("MOTHERBOARD");
	if(itemType == DISK) return std::string("DISK");
	return std::string("UNKNOWN ITEM TYPE");
}

