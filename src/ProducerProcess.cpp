/*
 * ProducerProcess.cpp
 *
 * Created on: Apr 25, 2014
 * Author: jp
 */

#include "Includes.h"
#include "iProducer.h"

using namespace std;


void showProductionOrder(int id, const ProductionOrder& po) {
	string announcement = "Nueva orden de Compra =[ "
			+ Utils::intToString(po.amountOfItems[PROCESSOR]) + "P , "
			+ Utils::intToString(po.amountOfItems[MOTHERBOARD])
			+ " M , " + Utils::intToString(po.amountOfItems[DISK])
			+ "D ]";
	Process::announce(PRODUCER_PROCESS, id, GREEN, announcement.c_str());
}


ProductionOrder newProductionOrder(){
    ProductionOrder productionOrder;
    productionOrder.receiverId = 0;
    productionOrder.amountOfItems[0] = Utils::generateRandomNumberBetween(1, 5);
    productionOrder.amountOfItems[1] = Utils::generateRandomNumberBetween(1, 5);
    productionOrder.amountOfItems[2] = Utils::generateRandomNumberBetween(1, 5);
    return productionOrder;
}

ProductionOrder newProductionOrder();

int main(int argc, char** argv) {

	char* programName = argv[0];
	stringstream ss;

	// Si se ingresan menos argumentos de los necesarios
	if (argc < 2) {
		string msg = "Usage ";
		msg = msg + programName + " <-amountOfProductionOrders>\n";
		Colors::writeerr(msg, RED);
		exit(EXIT_FAILURE);
	}

	int id = 0;
	string name = Process::getNameForProcess(PRODUCER_PROCESS, id);
    Process::announce(PRODUCER_PROCESS, id, UNDERLINEDGREEN, "initializing.");

    srand(time(NULL) * id);

    int amountOfProductionOrders = atoi(argv[1]);
    Queue::create(PRODUCTION_ORDERS_QUEUE_ID);
    iProducer* iface = new iProducer();
    id = iface->getRegisteredId();

    for(int i = 0; i < amountOfProductionOrders; i++){

        ProductionOrder productionOrder = newProductionOrder();

        sleep(Process::sleepTime());

        showProductionOrder(id, productionOrder);

        iface->sendToConsumers(productionOrder);

        Process::announce(PRODUCER_PROCESS, id, GREEN, "production order sent.");

        sleep(Process::sleepTime());
    }

    Process::announce(PRODUCER_PROCESS, id, UNDERLINEDGREEN, "finished.");

    return 0;
}





