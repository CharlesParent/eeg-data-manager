#include <time.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "data_generators.h"

void* threadEEGGatherer(void* args)
{
	struct timespec now;
	while(1)
	{
		pthread_mutex_lock(&eeg_data_mutex);
		pthread_cond_wait(&eeg_data_cond, &eeg_data_mutex);
		clock_gettime(CLOCK_REALTIME, &now);
		struct eegData *sample = (struct eegData*) malloc(sizeof(struct eegData));
		readEEGData(sample);
		printf("received data %" PRIu32" at %lu\n", sample->eeg1, now.tv_nsec);
		pthread_mutex_unlock(&eeg_data_mutex);
	}
	return NULL;
}

void* threadACCGatherer(void* args)
{
	struct timespec now;
	while(1)
	{
		pthread_mutex_lock(&acc_data_mutex);
		pthread_cond_wait(&acc_data_cond, &acc_data_mutex);
		clock_gettime(CLOCK_REALTIME, &now);
		struct accData *sample = (struct accData*) malloc(sizeof(struct accData));
		readACCData(sample);
		printf("received data %" PRIu16" at %lu\n", sample->accX, now.tv_nsec);
		pthread_mutex_unlock(&acc_data_mutex);
	}
	return NULL;
}

int initGathererThreads()
{
	pthread_t eeg_gatherer_thread_id, acc_gatherer_thread_id;
	int ret;
	int r = 0;

	/*creating threads to generate EEG and ACC data*/
	ret=pthread_create(&eeg_gatherer_thread_id, NULL, &threadEEGGatherer, NULL);
	if(ret==0){
		printf("Thread created successfully.\n");
	} else {
		printf("Thread not created.\n");
		r = -1;
	}

	ret=pthread_create(&acc_gatherer_thread_id, NULL, &threadACCGatherer, NULL);
	if(ret==0){
		printf("Thread created successfully.\n");
	} else {
		printf("Thread not created.\n");
		r = -1;
	}
	return r;
}
