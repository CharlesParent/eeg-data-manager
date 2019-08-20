#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#include "time_utils.h"
#include "data_generators.h"

int initSensorThreads(void) {
	pthread_t eeg_thread_id, acc_thread_id;
	int ret;
	int r = 0;

	/*creating threads to generate EEG and ACC data*/
	ret=pthread_create(&eeg_thread_id, NULL, &threadEEGGenerator, NULL);
	if(ret==0){
		printf("Thread created successfully.\n");
	} else {
		printf("Thread not created.\n");
		r = -1;
	}

	ret=pthread_create(&acc_thread_id, NULL, &threadACCGenerator, NULL);
	if(ret==0){
		printf("Thread created successfully.\n");
	} else {
		printf("Thread not created.\n");
		r = -1;
	}
	return r;
}

int main() {
	int r;

	r = initSensorThreads();
	if (r ==1) {
		return 0;
	}

	printf("I am main function.\n");
	sleep(10);
	printf("Terminating main\n");
	return 0;
}
