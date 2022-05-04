memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock

int pthread_create(pthread_t *restrict thread,
                          const pthread_attr_t *restrict attr,
                          void *(*start_routine)(void *),
                          void *restrict arg);
       The pthread_create() function starts a new thread in the calling
       process.  The new thread starts execution by invoking
       start_routine(); arg is passed as the sole argument of
       start_routine().

int pthread_join(pthread_t thread, void **retval);
       The pthread_join() function waits for the thread specified by
       thread to terminate.  If that thread has already terminated, then
       pthread_join() returns immediately.  The thread specified by
       thread must be joinable.

       If retval is not NULL, then pthread_join() copies the exit status
       of the target thread (i.e., the value that the target thread
       supplied to pthread_exit(3)) into the location pointed to by
       retval.  If the target thread was canceled, then PTHREAD_CANCELED
       is placed in the location pointed to by retval.

int usleep(useconds_t usec);
       The usleep function suspends execution of the calling thread
       for (at least) usec microseconds.  The sleep may be lengthened
       slightly by any system activity or by the time spent processing
       the call or by the granularity of system timers.


int pthread_detach(pthread_t thread);
       The pthread_detach() function marks the thread identified by
       thread as detached.  When a detached thread terminates, its
       resources are automatically released back to the system without
       the need for another thread to join with the terminated thread.

       Attempting to detach an already detached thread results in
       unspecified behavior.

eat -> sleep -> think -> eat