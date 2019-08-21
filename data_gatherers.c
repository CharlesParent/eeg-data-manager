#include <time.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "data_gatherers.h"
#include "data_generators.h"

struct eegData sample_storage[100];

static int next_index_to_write = 0;
sem_t empty_count, fill_count;

void* threadEEGGatherer(void* args)
{
	struct timespec now;
	while(1)
	{
		// Wait for data to be produced by EEGGeneratorThread
		pthread_mutex_lock(&eeg_data_mutex);
		pthread_cond_wait(&eeg_data_cond, &eeg_data_mutex);
		clock_gettime(CLOCK_REALTIME, &now);
		// Store data in eegBuffer
		sem_wait(&empty_count);
		readEEGData(&(sample_storage[next_index_to_write]));
		next_index_to_write++;
		next_index_to_write = next_index_to_write % 100;
		sem_post(&fill_count);
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

int initGathererThreads(pthread_attr_t* attr)
{
	
	struct sched_param param;
	pthread_t eeg_gatherer_thread_id, acc_gatherer_thread_id;
	int ret;
	int r = 0;

	sem_init(&fill_count,0,0);
	sem_init(&empty_count,0,100);

	param.sched_priority = 2;
	pthread_attr_setschedparam(attr, &param);

	/*creating threads to generate EEG and ACC data*/
	ret=pthread_create(&eeg_gatherer_thread_id, attr, &threadEEGGatherer, NULL);
	if(ret==0){
		printf("Thread created successfully.\n");
	} else {
		printf("Thread not created.\n");
		r = -1;
	}

	ret=pthread_create(&acc_gatherer_thread_id, attr, &threadACCGatherer, NULL);
	if(ret==0){
		printf("Thread created successfully.\n");
	} else {
		printf("Thread not created.\n");
		r = -1;
	}
	return r;
}
