#include <time.h>
#include <stdio.h>

#include "data_generators.h"
#include "time_utils.h"

#define EEG_DATA_PERIOD 5000 // Period in us
#define ACC_DATA_PERIOD 100000 // Period in us

void* threadEEGGenerator(void* args)
{
	struct timespec next;
	struct timespec now;

	clock_gettime(CLOCK_REALTIME, &next);
	while(1)
	{
		timespec_add_us(&next, EEG_DATA_PERIOD);
		clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &next, NULL);
		printf("EEG Data available ! at %lu\n", next.tv_nsec);
	}
	return NULL;
}

void* threadACCGenerator(void* args)
{
	struct timespec next;
	struct timespec now;

	clock_gettime(CLOCK_REALTIME, &next);
	while(1)
	{
		timespec_add_us(&next, ACC_DATA_PERIOD);
		clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &next, NULL);
		printf("ACC Data available ! at %lu\n", next.tv_nsec);
	}
	return NULL;
}

void readEEGData(struct eegData *eeg_sample) {
	eeg_sample->eeg1 = 0;
	eeg_sample->eeg2 = 0;
	eeg_sample->eeg3 = 0;
}

void readACCData(struct accData *acc_sample) {
	acc_sample->accX = 0;
	acc_sample->accY = 0;
	acc_sample->accZ = 0;
}
