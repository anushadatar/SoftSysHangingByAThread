#ifndef _THREAD_H_
#define __THREAD_H_

// Switch statement based implementation of local continuation
// based protothreading architecture.
typedef unsigned short pass_t;
#define pass_INIT(s) s = 0;
#define pass_RESUME(s) switch(s) { case 0: 
#define pass_SET(s) s = __LINE__; case __LINE__: 
#define pass_END(s) }
// Taken from protothreading example.
// A thread just contains one of these objects.
typedef struct thread {
  pass_t pass;
} thread;

#define THREAD_SCHEDULE(f) ((f) < THREAD_EXITED)
#endif
