#ifndef TIME_UTILS
#define TIME_UTILS

void timespec_add_us(struct timespec *t, long us);
int timespec_cmp(struct timespec *a, struct timespec *b);

#endif // !TIME_UTILS
