/*
 * Terminator.cpp
 *
 *  Created on: May 4, 2014
 *      Author: jp
 */

#include "Includes.h"
#include "Queue.h"

int main(){
    Queue::destroy(PRODUCTION_ORDERS_QUEUE_ID);
    std::string msg = "Termination complete.";
    Colors::writeout(msg, UNDERLINEDGREEN);
    return 0;
}


