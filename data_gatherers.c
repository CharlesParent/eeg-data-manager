#include <time.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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
		printf("received data %lu at %lu\n", sample->eeg1, now.tv_nsec);
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
		printf("received data %lu at %lu\n", sample->accX, now.tv_nsec);
		pthread_mutex_unlock(&acc_data_mutex);
	}
	return NULL;
}
