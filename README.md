## SoftSysHangingByAThread
Software Systems SP19 Project 2 : Arduino threading library in C

# Thread library

This library allows an Arduino programs to use thread functionality for synchronization with protothreading. Threads with the library allow a single sequence stream within a program and can be used to provide blocking event handlers. With a single core, Arudnios do not currently support parallel tasks. Making use of C macros like __LINE__, allows this library to pause a task execution and execute another task or piece of a task before accessing the __LINE__ to resume the original process. In this way, threading can be simulated.

This library implements conditional variables, mutexes, and semaphores. This library can be used to schedule and mange parallel repeated tasks, create thread safe cross-process shared variables, organize a systems processes, and run tasks in the pseudo-background behind main tasks.

# Examples
All examples can be found in the examples folder in the main directory.

Basic_Thread: Similar to Simple_Print, this example creates two threads and schedules them with conditional flags. This example can be used a template for adding complex tasks.

Blink_With_Threads: With an Object-Oriented implementation of an LED blinker, Blink_With_Threads creates two LED objects, two threads. Each thread wraps an LED object. By setting variable on and off times for the LED on each thread, the threads display their overlapping processes. The LED blinker object counts milliseconds to update its state. For simplicity, the blinker object can be abstracted to a simple on/off state class for an LED.

LCD_Display: To set up this example, consult the

Displayer

Basic_Semaphore:

LCD_With_Semaphores:
