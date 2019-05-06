# Hanging By a Thread
## Allison Basore and Anusha Datar
Software Systems SP19 Project 2 : Arduino threading library in C

# Thread library

This library facilitates protothreading functionality for synchronization on an Arduino Uno. Threads created using this library library allow a single sequence stream within a program and can be used to provide blocking event handlers.

Because the Arduino Uno is a single core device, it does not support truly parallel tasks. To simulate parallel execution (i.e. to pauce current execution to run separate tasks concurrently), this library makes use of the \_\_LINE\_\_ macro. 

This library also contains an implementation of semaphores that can also be leveraged to implement the functionality of mutexes and condition variables. In this way, the library can be used to schedule and mange parallel repeated tasks, create thread safe cross-process shared variables, organize a systems processes, and run tasks in the pseudo-background behind main tasks.

# Examples
All examples can be found in the examples folder in the main directory.

- [Simple_Print](https://github.com/anushadatar/SoftSysHangingByAThread/blob/master/examples/simplePrint/simplePrint.ino): This example is the best place to get starting using the library. Simple_Print, creates two threads and manages their scheduling with flag conditional variables. The threads wait for each other to finish. They run infinitely and print a statement with each loop.

- [Basic_Thread](https://github.com/anushadatar/SoftSysHangingByAThread/blob/master/examples/basic_thread_example/basic_thread_example.ino): Similar to Simple_Print, this example creates two threads and schedules them with conditional flags. This example can be used a template for adding complex tasks.

- [Blink_With_Threads](https://github.com/anushadatar/SoftSysHangingByAThread/blob/master/examples/blinkWithThreads/blinkWithThreads.ino): With an Object-Oriented implementation of an LED blinker, Blink_With_Threads creates two LED objects, two threads. Each thread wraps an LED object. By setting variable on and off times for the LED on each thread, the threads display their overlapping processes. The LED blinker object counts milliseconds to update its state. For simplicity, the blinker object can be abstracted to a simple on/off state class for an LED.

- [LCD_Display](https://github.com/anushadatar/SoftSysHangingByAThread/blob/master/examples/LCDdispalyExample/LCDdispalyExample.ino): To set up this example, consult the [Ardunio Documentation](https://www.arduino.cc/en/Tutorial/LiquidCrystalDisplay) for how to connect the LCD screen to an Ardunio. LCD_Display uses an Object-Oriented approach to creating a wrapper for using the LCD display. This example is similar to Blink_With_Threads and displays a message from each thread to the screen. The Displayer class can be abstracted to inputing a message and displaying it on the screen, using the update method to change the message.

- [Basic_Semaphore](https://github.com/anushadatar/SoftSysHangingByAThread/blob/master/examples/basic_semaphore_example/basic_semaphore_example.ino): This example uses a basic semaphore implementation along with the thread library to simulate the Producer-Consumer problem. Basic_Semaphores exemplifies how to create a bounded buffer that handles tasks from a producer and consumer. A producer thread adds to the buffer until it reaches capacity and then a consumer thread removes from until it is empty.

- [LCD_With_Semaphores](https://github.com/anushadatar/SoftSysHangingByAThread/blob/master/examples/LCDSemaphores/LCDSemaphores.ino): Simular to Basic_Semaphore and Blink_With_Threads, LCD_With_Semaphores uses the thread and semaphore implementation to manage a producer/consumer system. The LCD screen displays the count and the semaphore value.

# How to Use
To use this threading framework in another arduino project, add the [thread.h](https://github.com/anushadatar/SoftSysHangingByAThread/blob/master/thread.h) header file to your arduino project folder and the include it in your source file.

For more information, reference our [report](https://github.com/anushadatar/SoftSysHangingByAThread/blob/master/reports/report.md).
