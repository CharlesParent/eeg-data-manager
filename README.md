## EEG ACC data manager
This project aims at gathering data from simulated eeg and acc sensors.

## How to Run
to run the program:
- make clean
- make
- ./main

## Overview
2 threads generate data at periodic time (200Hz for EEG, 10Hz for ACC).

First 2 threads waits on a condition variable to read and write data in circular buffers. They then indicate data is available in circular buffers to two other threads using a Producer/Consumer model with semaphores. 
The two latter then call algo (black box running during either 2ms or 50ms) display data for now.

## Missing parts
- Thread processing data coming from ACC sensor has not been implemented
- Storage in a binary file has not been implemented. I think I would have store data like this in a binary file:
TYPE (EEG/ACC) | TIME_SEC | TIME_NSEC | 3 ints of data (either uint32 or uint16 depending on the type)
That way when reading binary file, we read the first byte and then know how long data sample is.
- When writting data to circular buffer, time is not stored in the structure. It should be stored as well in order to analyse correctly data once stored in the binary file

## Limitations / Improvements
- First threads are not correctly scheduled. First Threads should have a high priority in order to be shure to collect data at the right moment. A scheduling policy should have been used such as SCHED_RR or SCHED_FIFO
- Implementation highly depends on the amount of time "algo" function takes. If it takes too much time then circular buffer may end full and threads gathering data will no be able to store data anymore. It would be really interesting to know what makes the algo function last longer on some occasions.
- Main function only sleeps and terminates violently after initialization. One better way to stop the program would have been to wait for threads generating data to exit, and set these threads to exit when the generated a X samples.
- Some values should have been defined in the code, such as CIRCULAR_BUFFER_LENGTH (100)

## Differences with implementation on FreeRTOS
- First threads would have been transformed into tasks. These tasks would have allow me to indicate the delay between 2 executions
- I don't know much about FreeRTOS, but I read that time slicing can be managed on such an OS, allowing to slice time in slots and allocate this slots to thread execution. That would allow to be shure to execute a thread periodically.
- Once data is gathered, events would have been creating to indicate to threads processing data that data is ready to be processed by algo function. I guess it would works similarly as events in ChibiOS[http://www.chibios.org/dokuwiki/doku.php?id=chibios:book:kernel_events]
