// #include <Thread.h>

typedef struct thread{
  long repeatInterval;
  long lastRun;
  long nextRun;
  bool timeToRun;
  void (*doSomething)();
} thread;

void turnOnSix(){
   digitalWrite(6, HIGH);
}

void turnOffSix(){
   digitalWrite(6, LOW);
}

void turnOnSeven(){
   digitalWrite(7, HIGH);
}

void printSomethingCool(){
  Serial.println("This thread is happening right now!");
  delay(1000);
  digitalWrite(6, LOW);
  Serial.println("Now I'm done.");
}

void checkIfTimeToRun(thread *t){
  bool time_remaining = (millis() - t->nextRun) & 0x80000000;
  if(!time_remaining){
    t->timeToRun = HIGH;
  }else{
    t->timeToRun = LOW;
  }
}

void threadRan(thread *t){
  t->lastRun = millis()-t->lastRun;
  t->nextRun = t->repeatInterval+ t->lastRun;
}

typedef struct controller{
  int numThreads;
  void (*runFunc)();
  thread* threads[5*sizeof(thread)];
} controller;


thread A = {.repeatInterval = 1000, .lastRun = 0, .nextRun = 0, .timeToRun=LOW, printSomethingCool};
thread B = {.repeatInterval = 1000000000000, .lastRun = 0, .nextRun = 0, .timeToRun=LOW, turnOnSix};

controller C = {.numThreads = 2, .runFunc = runThreads, {&A,&B}};



void runThreads(){
  int i;
  for(i=0;i<C.numThreads;i++){
    checkIfTimeToRun(C.threads[i]);
    if(C.threads[i]->timeToRun){
      C.threads[i]->doSomething();
    }
  }
}

void setup(){
  Serial.begin(9600);
  pinMode(6, OUTPUT);
  pinMode(7,OUTPUT);
}

void loop(){
//
  C.runFunc();

}
