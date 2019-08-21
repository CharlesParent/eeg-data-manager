#ifndef DATA_GENERATORS
#define DATA_GENERATORS

#include <stdint.h>

struct eegData {
	uint32_t eeg1;
	uint32_t eeg2;
	uint32_t eeg3;
};

struct accData {
	uint16_t accX;
	uint16_t accY;
	uint16_t accZ;
};

extern pthread_mutex_t eeg_data_mutex, acc_data_mutex;
extern pthread_cond_t eeg_data_cond, acc_data_cond;

void* threadEEGGenerator(void* args);
void* threadACCGenerator(void* args);

void readEEGData(struct eegData *eeg_sample);
void readACCData(struct accData *acc_sample);

int initSensorThreads(pthread_attr_t *attr);

#endif // !DATA_GENERATORS
