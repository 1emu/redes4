/*
 * ConsumerProcess.cpp
 *
 * Created on: Apr 25, 2014
 * Author: jp
 */

#include "Includes.h"
#include "iConsumer.h"

using namespace std;

void showProductionOrder(int id, const ProductionOrder& po, int itemType) {
	string announcement = "Orden de Compra recibida = "
			+ Utils::intToString(po.amountOfItems[itemType])+ " " + Process::nameForItemType(itemType) + " items inside.";
	Process::announce(PRODUCER_PROCESS, id, PURPLE, announcement.c_str());
}

int main(int argc, char** argv) {

	char* programName = argv[0];

	// Si se ingresan menos argumentos de los necesarios
	if (argc < 4) {
		string msg = "Usage ";
		msg = msg + programName + " <-amountOfProductionOrders> <itemType> <-amountOfProducers>\n";
		Colors::writeerr(msg, RED);
		exit(EXIT_FAILURE);
	}

	int id = 0;
	const char* itemType_char = argv[2];
	int itemType = atoi(itemType_char);
	string name = Process::getNameForProcess(CONSUMER_PROCESS, id);

	int amountOfProductionOrders = atoi(argv[1]);
	int amountOfProducers = atoi(argv[3]);
	iConsumer* iface = new iConsumer(itemType);
	id = iface->getRegisteredId();

	Process::announce(CONSUMER_PROCESS, id, PURPLE, "initializing.");

	for(int i = 0; i < amountOfProductionOrders * amountOfProducers; i++){

		ProductionOrder productionOrder;
		productionOrder = iface->receiveFromProducer();

		showProductionOrder(id, productionOrder, itemType);

		sleep(Process::sleepTime());
	}

	iface->unregister();

	Process::announce(CONSUMER_PROCESS, id, PURPLE, "finished.");

	return 0;
}

