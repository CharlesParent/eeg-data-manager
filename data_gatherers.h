#ifndef DATA_GATHERERS
#define DATA_GATHERERS

void* threadEEGGatherer(void* args);
void* threadACCGatherer(void* args);
int initGathererThreads();

#endif // !DATA_GATHERERS
