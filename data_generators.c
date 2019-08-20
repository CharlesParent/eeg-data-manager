#include <time.h>
#include <stdio.h>

#include "time_utils.h"

#define EEG_DATA_PERIOD 1000000 // Period in us

void* threadEEGGenerator(void* args)
{
	struct timespec next;
	struct timespec now;

	clock_gettime(CLOCK_REALTIME, &next);
	while(1)
	{
		timespec_add_us(&next, EEG_DATA_PERIOD);
		clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &next, NULL);
		printf("Data available ! at %lu\n", next.tv_nsec);
	}
	return NULL;
}
