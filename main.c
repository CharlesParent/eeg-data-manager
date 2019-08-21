#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#include "time_utils.h"
#include "data_generators.h"
#include "data_gatherers.h"
#include "data_processors.h"

int main() {
	int r;
	r = initProcessorThreads();
	if (r == -1) {
		return 0;
	}
	r = initGathererThreads();
	if ( r == -1) {
		return 0;
	}
	r = initSensorThreads();
	if (r == -1) {
		return 0;
	}

	printf("I am main function.\n");
	sleep(10);
	printf("Terminating main\n");
	return 0;
}
