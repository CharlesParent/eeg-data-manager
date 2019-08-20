#include <time.h>
#include <stdio.h>

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
