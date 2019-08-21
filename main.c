#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#include "time_utils.h"
#include "data_generators.h"
#include "data_gatherers.h"
#include "data_processors.h"

int main() {
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
	int r;
	r = initProcessorThreads(&attr);
	if (r == -1) {
		return 0;
	}
	r = initGathererThreads(&attr);
	if ( r == -1) {
		return 0;
	}
	r = initSensorThreads(&attr);
	if (r == -1) {
		return 0;
	}

	sleep(5);
	printf("Terminating main\n");
	return 0;
}
