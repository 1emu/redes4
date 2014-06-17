/*
 * Terminator.cpp
 *
 *  Created on: May 4, 2014
 *      Author: jp
 */

#include "Includes.h"
#include "Queue.h"

int main(){
    Queue::destroy(RECEIVER_QUEUE_ID);
    Queue::destroy(SENDER_QUEUE_ID);
    std::string msg = "Termination complete.";
    Colors::writeout(msg, UNDERLINEDGREEN);
    return 0;
}



