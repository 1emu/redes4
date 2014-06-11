//============================================================================
// Name        : Ejercicio3.cpp
// Author      : jp
// Version     :
// Copyright   :
// Description : Hello World in C, Ansi-style
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include "Includes.h"
#include "Queue.h"

int main(void) {
	puts("Hello World!!!");
	int queue1Id = 1;
	Queue* queue1 = Queue::create(queue1Id);
	return EXIT_SUCCESS;
}
