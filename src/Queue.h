/*
 * Queue.h
 *
 *  Created on: May 2, 2014
 *      Author: jp
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#ifndef PERMISSIONS
#define PERMISSIONS 0753
#endif

#include "Includes.h"
#include "Defaults.h"
#include "Utils.h"

class Queue {
public:
	Queue();
	virtual ~Queue();
	static Queue* create(int id);
	static Queue* get(int id);
	static void destroy(int id);
	bool send(void * message, size_t size);
	bool receive(void * message, size_t size, long type);

private:
	static int getQueueId(int id);
	static void notifyError(int id, std::string failingMethod);
	int queueId;
	int id;
	void setQueueId(int queueId);
	void setId(int id);
};

#endif /* QUEUE_H_ */
