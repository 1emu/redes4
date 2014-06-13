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

using namespace std;

bool thereAreProducers(){
	return true;
}

bool thereAreProductionOrdersInQueue(){
	return true;
}

void sendProductionOrders(){

}

int main(int argc, char** argv) {

	char* programName = argv[0];

	int id = 0;
    Process::announce(SENDER_PROCESS, id, UNDERLINEDYELLOW, "initializing.");

    Queue::create(PRODUCTION_ORDERS_QUEUE_ID);

    cola_mensaje cola_msg;
	red_mensaje red_msg;
	int bytes;

	Socket * socket = new Socket(nombre);
	Cola * cola_de_recepcion = new Cola(COLA_EMISOR, Helper::traductor(COLA_EMISOR));
	atoi(argv[1]) ? cola_de_recepcion->create() : cola_de_recepcion->get();

	do{
	   cola_de_recepcion->receive((void*) &red_msg, sizeof(red_msg), EMISOR);
	   cola_msg = red_msg.msg;
	   socket->active(string(red_msg.host.address), red_msg.host.port);
	   bytes = socket->send((char*) &cola_msg, sizeof(cola_msg));
	   Helper::writeout(nombre,"Envio mensaje a "+string(cola_msg.to_nombre)+" de "+string(cola_msg.from_nombre), COLOR_CYAN);
	   socket->destroy();
	}while(bytes >= 0);

    while(thereAreProducers() || thereAreProductionOrdersInQueue()){
    	sendProductionOrders();
        Process::announce(SENDER_PROCESS, id, YELLOW, "production orders sent.");
    	sleep(1);
    }

    Process::announce(PRODUCER_PROCESS, id, UNDERLINEDYELLOW, "finished.");

    return 0;
}









