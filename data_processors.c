#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#include "data_generators.h"
#include "data_processors.h"
#include "data_gatherers.h"
#include "time_utils.h"

static int next_index_to_read = 0;

// Black Box algo basically returns after 2ms or sometimes after 50ms
static int i = 0;
void algo(void *data)
{
	(void) data;
	struct timespec now, next;
	clock_gettime(CLOCK_REALTIME, &next);
	i++;
	if (i % 15 == 0) {
		printf("Algo will take 50ms this time !\n");
		timespec_add_us(&next, 50000);	
	} else {
		timespec_add_us(&next, 2000);
	}
	do {
		clock_gettime(CLOCK_REALTIME, &now);
	} while(timespec_cmp(&now, &next) < 0);
	return;
}

void* threadEEGProcessor(void* args)
{
	struct eegData current_sample;
	while(1) {
		sem_wait(&fill_count);
		memcpy(&current_sample, &(sample_storage[next_index_to_read]), sizeof(struct eegData));
		sem_post(&empty_count);
		next_index_to_read++;
		next_index_to_read = next_index_to_read % 100;
		algo(&current_sample);
		printf("finished to process sample %"PRIu32"\n", current_sample.eeg1);
	}
}

int initProcessorThreads() {
	pthread_t eeg_processor_thread_id;
	int ret;
	int r = 0;

	/*creating threads to process EEG and ACC data*/
	ret=pthread_create(&eeg_processor_thread_id, NULL, &threadEEGProcessor, NULL);
	if(ret==0){
		printf("Thread created successfully.\n");
	} else {
		printf("Thread not created.\n");
		r = -1;
	}

	return r;
}
