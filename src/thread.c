#include "thread.h"
// threads to preform the mandelbrot set update
Worker_Thread threads[NTHREADS];
// init the threads
void init_threads(Worker_Thread *threads) {
  for (int i = 0; i < NTHREADS; i++) {
    int ret = pthread_create(&threads[i].thread, (pthread_attr_t *)NULL,
                             (void *(*)(void *))th_mandl_update, NULL);
  }
}
