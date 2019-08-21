#ifndef DATA_GATHERERS
#define DATA_GATHERERS

#include <semaphore.h>
#include "data_generators.h"

extern sem_t empty_count, fill_count;
extern struct eegData sample_storage[100];

void* threadEEGGatherer(void* args);
void* threadACCGatherer(void* args);
int initGathererThreads(pthread_attr_t *attr);

#endif // !DATA_GATHERERS
