#ifndef __THREAD_H__
#define __THREAD_H__
/******************************************************************************
	Pass variable implementation.
******************************************************************************/

/*
    struct pass_t
    Define the internal framework of the struct within each individual
    thread. This two-byte struct leverages the __LINE__ macro for threading 
    functionality. The thread struct is literally a wrapper for pass structs.
*/

typedef unsigned short pass_t;
/*
    PASS_INITIALIZE
    
    Initializes the internal continuation variable for each individual thread.

    p = the pointer to the thread to initialize the macro for.
*/
#define PASS_INITALIZE(p) p = 0;
/* 
    PASS_RESUME, PASS_SET, and PASS_CLEAR
    Leverages that switch statements are weird when in preprocessor definitions.
	Influenced by protothreading approach's "local continuation" concept. 
*/
#define PASS_RESUME(p) switch(p) { case 0:
#define PASS_SET(p) p = __LINE__; case __LINE__:
#define PASS_CLEAR(p) }

/* 
	Define the thread structure itself - it is a wrapper for a single pass struct.
 */
struct thread {
  pass_t pass;
};
/******************************************************************************
	Thread implementation.
******************************************************************************/
#define THREAD_WAITING 0
#define THREAD_YIELDED 1
#define THREAD_CLOSED  2
#define THREAD_CLEARED 3

/*
	Initializes a thread variable by initializing the pass struct.

	thread : pointer to the thread struct for the given thread.

*/
#define THREAD_INITALIZE(thread)   PASS_INITALIZE((thread)->pass)
/*
	Start up a thread by setting the pass parameter to resume.

	thread : pointer to the thread struct for the given thread.
*/
#define THREAD_START(thread) { PASS_RESUME((thread)->pass)
/*
	Block until the trigger resumes the thread.

	thread : pointer to the thread struct for the given thread.
	trigger : integer condition variable to trigger thread.
*/
#define THREAD_WAIT_UNTIL(thread, trigger) \
    PASS_SET((thread)->pass); \
    if(!(trigger)) { \
      return THREAD_WAITING; \
    } \
/*
	Block until the child thread has been scheduled.

	thread		 : pointer to the thread struct for the given thread.
	child_thread : pointer to the thread struct for the child thread.
*/
#define THREAD_WAIT_THREAD(thread, child_thread) THREAD_WAIT_UNTIL((thread), !(THREAD_SCHEDULE(child_thread)))
/*
	Create a child thread, run it, and wait until it exits.
	
	thread		 : A pointer to the protothread control structure.
	child_thread : A pointer to the child protothread's control structure.
	child		 : The child protothread with arguments
*/
#define THREAD_NEW(thread, child_thread, child) \
    THREAD_INITALIZE((child)); \
    THREAD_WAIT_THREAD((thread), (chiild_thread)); \
/*
	Schedule a thread.

	f : Call to the function in the source code that actually calls the protothread.

	Returns 0 if thread has exited, 1 otherwise.
*/
#define THREAD_SCHEDULE(f) ((f) < THREAD_CLOSED)
/*
	Hold the protothread so that other processes can happen.

	thread : pointer to the thread struct for the given thread.
*/
#define THREAD_YIELD(thread) \
    THREAD_YIELD = 0; \
    PASS_SET((thread)->pass); \
    if(THREAD_YIELD == 0) { \
      return THREAD_YIELDED; \
    } \
   
/*
	Hold until the trigger resumes the thread.

	thread : pointer to the thread struct for the given thread.
	trigger : integer condition variable to trigger thread.
*/
#define THREAD_YIELD_UNTIL(thread, trigger) \
    THREAD_YIELD = 0; \
    PASS_SET((thread)->pass); \
    if((THREAD_YIELD == 0) || !(trigger)) { \
      return THREAD_YIELDED; \
    } \
/*
	Exit the protothread, and unblock the parent thread.

	thread : pointer to the thread struct for the given thread.
*/
#define THREAD_EXIT(thread) \
    THREAD_INITALIZE(thread); \
    return THREAD_CLOSED; \
/*
	Clears and removes the thread. 

	thread : pointer to the thread struct for the given thread.
*/
#define THREAD_CLEAR(thread) \
    PASS_CLEAR((thread)->pass); \
    THREAD_INITALIZE(thread); \
    return THREAD_CLEARED; }

/******************************************************************************
	Semaphore implementation. 
******************************************************************************/
/*
*/
struct semaphore {
	int counter;
};
/*
Initializes the semaphore structure by creating the counter.

p : pointer  to the semaphore struct
i : unsigned int that increments
*/
#define SEMAPHORE_INIT(p, i) (p)->counter = i
/*
Wait for a thread to block while the counter is zero and
continue when the value of the coutner is greater than zero.

t : Pointer to the thread executing the operation.
p : Pointer to the semaphore object for the thread.
*/
#define SEMAPHORE_WAIT(t, p)	\
  {	\
    THREAD_WAIT_UNTIL(t, (p)->counter > 0);	\
    --(p)->counter;	\
  } 
/*
Signal and increment the counter inside the semaphore

t : Pointer to the thread executing the operation.
p : Pointer to the semaphore object for the thread.
*/
#define SEMAPHORE_SIGNAL(t, p) ++(p)->counter
#endif 
