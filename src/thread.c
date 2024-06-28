#include "thread.h"
#include "window.h"
// threads to preform the mandelbrot set update
Worker_Thread threads[NTHREADS];

void th_update() {
  int unsigned id = 0;
  for (int i = 0; i < NTHREADS; i++) {
    threads[i].id = id;
    // spawn new thread, pass the new id
    int ret = pthread_create(&threads[i].thread, (pthread_attr_t *)NULL,
                             (void *(*)(void *))th_mandl_update,
                             (void *)&threads[i].id);
    id++;
    if (ret != 0) {
      fprintf(stderr, "Failed to create worker thread with id %d\n",
              threads[i].id);
      // kill the thread
      pthread_exit((void *)EXIT_FAILURE);
    }
  }
}

void th_mandl_update(void *args) {
  unsigned int th_id;
  unsigned int *argp;
  argp = (unsigned int *)args;
  // extract the thread id
  if (argp != NULL) {
    th_id = *argp;
    printf("thread ID: %d\n", th_id);
  } else {
    fprintf(stderr, "Could not extract args.. Exiting program\n");
    pthread_exit((void *)EXIT_FAILURE);
  }
  // preform the actual mandelbrot set update
  int dy = (DIM.width);
  // close out of thread
  pthread_exit((void *)EXIT_SUCCESS);
}
