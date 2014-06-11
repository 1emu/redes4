/*
 * Queue.cpp
 *
 *  Created on: May 3, 2014
 *      Author: jp
 */

#include "Queue.h"

Queue::Queue(){
	this->id = -1;
	this->queueId = -1;
}

Queue::~Queue(){

}

Queue* Queue::create(int id){
	Queue* newQueue = new Queue();
	key_t key = ftok(PATH, id);
	if (key == -1)	{
		notifyError(id, "create - ftok");
		exit(EXIT_FAILURE);
	}
	else {
		int queueId = msgget(key, IPC_CREAT | IPC_EXCL | PERMISSIONS);
		if (queueId == -1) {
			notifyError(id, "create - msgget");
			exit(EXIT_FAILURE);
		}
		newQueue->setId(id);
		newQueue->setQueueId(queueId);
	}
	return newQueue;
}

Queue* Queue::get(int id){
	Queue* newQueue = new Queue();
	int queueId = getQueueId(id);
	newQueue->setId(id);
	newQueue->setQueueId(queueId);
	return newQueue;
}

void Queue::destroy(int id){
	int queueId = getQueueId(id);
	int removeResult = msgctl(queueId, IPC_RMID, NULL);
	bool removeFailed = removeResult == -1;
	if (removeFailed) {
		notifyError(id, "destroy");
	}
}

void Queue::setQueueId(int queueId){
	this->queueId = queueId;
}

void Queue::setId(int id){
	this->id = id;
}

bool Queue::send(void * message, size_t size){
	int msgSendResult = msgsnd(queueId, message, size - sizeof(long), 0);
	bool sendFailed = (msgSendResult == -1);
	if (sendFailed) {
        notifyError(id, "send");
    }
	return !sendFailed;
}

bool Queue::receive(void * message, size_t size, long type){
	int msgReceiveResult = msgrcv(queueId, message, size - sizeof (long), type, 0);
	bool receiveFailed = (msgReceiveResult == -1);
	if (receiveFailed) {
        notifyError(id, "receive");
    }
	return !receiveFailed;
}

int Queue::getQueueId(int id) {
	int queueIdTemp;
	key_t key = ftok(PATH, id);
	if (key == -1)	{
		notifyError(id, "getQueueId - ftok");
		exit(EXIT_FAILURE);
	}
	else {
		queueIdTemp = msgget(key, 0600);
		if (queueIdTemp == -1) {
			notifyError(id, "getQueueId - msgget");
			exit(EXIT_FAILURE);
		}
	}
	return queueIdTemp;
}

void Queue::notifyError(int id, std::string failingMethod){
	std::string msg = "Error on queue with id #";
	msg = msg + Utils::intToString(id) + " when trying to " + failingMethod;
	Colors::writeerr(msg, RED);
}


