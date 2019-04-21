#ifndef _THREAD_H_
#define __THREAD_H_

// Based heavily on protothreading example.

typedef void * pass_t;
#define PASS_INIT(s) s = NULL
#define PASS_RESUME(s) \
  do {\
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

// A thread just contains one of these objects.
typedef struct thread {
  pass_t pass;
} thread;

// Scheduling is hard.
#define THREAD_SCHEDULE(f) ((f) < THREAD_EXITED)

void THREAD_INIT(struct thread* thread);
void THREAD_BEGIN(struct thread* thread);
int THREAD_WAIT_UNTIL(struct thread* thread, int condition);
int THREAD_YIELD(struct thread* thread);
int THREAD_END(struct thread* thread);
int THREAD_EXIT(struct thread* thread); 

#endif
