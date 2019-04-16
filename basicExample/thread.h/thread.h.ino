typedef struct controller{
  int numThreads;
  void (*runFunc)();
  thread* threads[5*sizeof(thread)];
} controller;


typedef struct thread{
  long repeatInterval;
  long lastRun;
  long nextRun;
  bool timeToRun;
  void (*doSomething)();
} thread;
