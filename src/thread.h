#ifndef THREAD_H
#define THREAD_H
#include "mandl.h"
#include <pthread.h>
#define NTHREADS 5

typedef struct Worker_Thread {
  unsigned int id;
  pthread_t thread;
} Worker_Thread;

void th_update();
void th_mandl_update(void *args);

extern Worker_Thread threads[NTHREADS];
#endif // INCLUDE_SRC_THREAD_H_
