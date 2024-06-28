#include "thread.h"
// threads to preform the mandelbrot set update
Worker_Thread *threads;

void init_threads() {
  threads = (Worker_Thread *)malloc(sizeof(Worker_Thread) * NTHREADS);
}

void th_update() {
  int unsigned id = 0;
  th_args args;
  for (int i = 0; i < NTHREADS; i++) {
    printf("updating threads %d\n", i);
    threads[i].args.id = id;
    threads[i].args.screen_buffer = screen_buffer;
    // spawn new thread, pass the new id
    int ret = pthread_create(&threads[i].thread, (pthread_attr_t *)NULL,
                             (void *(*)(void *))th_mandl_update,
                             (void *)&threads[i].args);
    id++;
    if (ret != 0) {
      fprintf(stderr, "Failed to create worker thread with id %d\n",
              threads[i].args.id);
      // kill the thread
      pthread_exit((void *)EXIT_FAILURE);
    }
  }

  for (int i = 0; i < NTHREADS; i++) {
    pthread_join(threads[i].thread, NULL);
  }
}

void th_mandl_update(void *args) {
  unsigned int th_id;
  th_args *argp;
  uint32_t *screen_buffer;
  argp = (th_args *)args;
  // extract the thread id
  if (argp != NULL) {
    th_id = argp->id;
    screen_buffer = argp->screen_buffer;
    printf("thread ID: %d\n", th_id);
  } else {
    fprintf(stderr, "Could not extract args.. Exiting program\n");
    pthread_exit((void *)EXIT_FAILURE);
  }
  // preform the actual mandelbrot set update
  int dy = (DIM.height / NTHREADS) * th_id;
  int end_y = (DIM.height / NTHREADS) * (th_id + 1);

  // extract imaginary coords of plot window
  double istart = plot_window.i_start;
  double iend = plot_window.i_end;
  // real coords of plot window
  double rstart = plot_window.r_start;
  double rend = plot_window.r_end;
  double normalized_color = 0;

  for (; dy < end_y; dy++) {
    for (int dx = 0; dx < DIM.width; dx++) {
      Complex c;
      // convert pixel coordinates into the complex plot coordinates
      c.real = rstart + ((double)dy / DIM.height) * (rend - rstart);
      c.img = istart + ((double)dx / DIM.width) * (iend - istart);
      uint32_t itrs = mandl_iter(c);
      normalized_color = lmap(itrs, 0, MAX_ITER, 0, 1);
      uint32_t color = color_calc(normalized_color, 50, 50, 50, 1);
      // use RGBA color calculated via the linear mapping between iterations and
      // color strength (darker colors for converge points (ones inside the set)
      // and lighter colors for diverging points (ones not inside the set))
      screen_buffer[dy * WIDTH + dx] = color;
    }
  }
  printf("thread ID: %d finished\n", th_id);
  // close out of thread
  pthread_exit((void *)EXIT_SUCCESS);
}
