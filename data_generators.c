#include <time.h>
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <inttypes.h>

#include "data_generators.h"
#include "time_utils.h"

#define EEG_DATA_PERIOD 5000 // Period in us
#define ACC_DATA_PERIOD 100000 // Period in us

pthread_mutex_t eeg_data_mutex, acc_data_mutex;
pthread_cond_t eeg_data_cond, acc_data_cond;
// Variables symbolising data on EEG and ACC channels
static uint32_t eeg_data_sample = 0;
static uint16_t acc_data_sample = 0;

void* threadEEGGenerator(void* args)
{
	struct timespec next;

	clock_gettime(CLOCK_REALTIME, &next);
	while(1)
	{
		timespec_add_us(&next, EEG_DATA_PERIOD);
		clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &next, NULL);
		pthread_mutex_lock(&eeg_data_mutex);
		eeg_data_sample++;
		printf("EEG Data available ! value %" PRIu32" at %lu\n", eeg_data_sample, next.tv_nsec);
		pthread_mutex_unlock(&eeg_data_mutex);
		pthread_cond_signal(&eeg_data_cond);
	}
	return NULL;
}

void* threadACCGenerator(void* args)
{
	struct timespec next;

	clock_gettime(CLOCK_REALTIME, &next);
	while(1)
	{
		timespec_add_us(&next, ACC_DATA_PERIOD);
		clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &next, NULL);
		pthread_mutex_lock(&acc_data_mutex);
		acc_data_sample++;
		printf("ACC Data available ! value %" PRIu16" at %lu\n", acc_data_sample, next.tv_nsec);
		pthread_mutex_unlock(&acc_data_mutex);
		pthread_cond_signal(&acc_data_cond);
	}
	return NULL;
}

void readEEGData(struct eegData *eeg_sample)
{
	printf("read data %" PRIu32"\n", eeg_data_sample);
	eeg_sample->eeg1 = eeg_data_sample;
	eeg_sample->eeg2 = eeg_data_sample;
	eeg_sample->eeg3 = eeg_data_sample;
}

void readACCData(struct accData *acc_sample)
{
	acc_sample->accX = acc_data_sample;
	acc_sample->accY = acc_data_sample;
	acc_sample->accZ = acc_data_sample;
}

int initSensorThreads(pthread_attr_t *attr)
{
	struct sched_param param;
	pthread_t eeg_thread_id, acc_thread_id;
	int ret;
	int r = 0;

	param.sched_priority = 1;
	pthread_attr_setschedparam(attr, &param);
	/*creating threads to generate EEG and ACC data*/
	ret=pthread_create(&eeg_thread_id, attr, &threadEEGGenerator, NULL);
	if(ret==0){
		printf("Thread created successfully.\n");
	} else {
		printf("Thread not created.\n");
		r = -1;
	}

	ret=pthread_create(&acc_thread_id, attr, &threadACCGenerator, NULL);
	if(ret==0){
		printf("Thread created successfully.\n");
	} else {
		printf("Thread not created.\n");
		r = -1;
	}
	return r;
}
