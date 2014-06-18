/*
 * Process.h
 *
 *  Created on: May 2, 2014
 *      Author: jp
 */

#ifndef PROCESS_H_
#define PROCESS_H_

#include "Includes.h"
#include "Structures.h"
 
class Process {
public:
	Process();
	virtual ~Process();

	static std::string getNameForProcess(const char* process_type, int id);

	static void announce(const char* processType, int id, const char* color, const char* msg);

	static int sleepTime();

	static void createProcesses(std::string processName, unsigned int amountOfProcesses);

	static std::string nameForItemType(int itemType);

	static std::string showQueueMessage(QueueMessage queueMessage);

	static std::string showNetworkMessage(NetworkMessage networkMessage);

};

#endif /* PROCESS_H_ */
