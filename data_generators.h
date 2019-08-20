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

void* threadEEGGenerator(void* args);
void* threadACCGenerator(void* args);

#endif // !DATA_GENERATORS
