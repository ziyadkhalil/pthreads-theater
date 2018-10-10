#include "time.h"
pthread_mutex_t time_mutex;
pthread_cond_t time_cond;
pthread_mutex_t start_mutex;
pthread_cond_t start_cond;
int time_counter = 0;