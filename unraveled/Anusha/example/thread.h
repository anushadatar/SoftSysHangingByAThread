#ifndef _THREAD_H_
#define __THREAD_H_

// Switch statement based implementation of local continuation
// based protothreading architecture.
/** \hideinitializer */
typedef void * pass_t;

#define PASS_INIT(s) s = NULL

#define PASS_RESUME(s)        \
  do {            \
    if(s != NULL) {       \
      goto *s;          \
    }           \
  } while(0)

#define PASS_CONCAT2(s1, s2) s1##s2
#define PASS_CONCAT(s1, s2) LC_CONCAT2(s1, s2)

#define PASS_SET(s)       \
  do {            \
    PASS_CONCAT(PASS_LABEL, __LINE__):            \
    (s) = &&PASS_CONCAT(PASS_LABEL, __LINE__);  \
  } while(0)

#define PASS_END(s)

// Taken from protothreading example.
// A thread just contains one of these objects.
typedef struct thread {
  pass_t pass;
} thread;

#define THREAD_SCHEDULE(f) ((f) < THREAD_EXITED)
void THREAD_INIT(thread* thread);

#endif
