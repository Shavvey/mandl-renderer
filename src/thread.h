#ifndef THREAD_H
#define THREAD_H
#include "mandl.h"
#include "window.h"
#include <pthread.h>
#define NTHREADS 5

typedef struct th_args {
  uint32_t (*screen_buffer)[WIDTH][HEIGHT];
  unsigned int id;
} th_args;

typedef struct Worker_Thread {
  pthread_t thread;
  th_args args;
} Worker_Thread;

void th_update();
void th_mandl_update(void *args);

extern Worker_Thread threads[NTHREADS];
#endif // INCLUDE_SRC_THREAD_H_
