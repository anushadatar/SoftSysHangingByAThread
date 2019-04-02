# Hanging by a Thread: Concurrency on an Arduino
## Allison Basore and Anusha Datar


# Goals

The goal of our project is to write the appropriate firmware to support threading on an Arduino Uno. In doing so, we hope to implement several different methods of handling concurrent processes and create interesting examples that leverage this functionality.

Our MVP functionality includes:
- An functioning threading API for embedded targets implemented in C 
- Documentation of functionality for basic threading examples (blinking different LEDs without interruption) on an Arduino Uno

Our stretch goals include:
- Include support for advanced hazard control (mutexes, locks, etc.)
- Develop advanced examples (such as an LCD display with processes, etc.)


# Learning Goals

Our learning goals include learning more about threading and general C programming, especially in the context of embedded programming. We would like to use this project to explore the complexity of thread management and the different strategies used to implement threading on the arduino. Additionally, we want to learn practical design using C programming - ideally, any other developer should be able to easily leverage our threading framework into their own programs.


# Resources
Several people have made basic threading examples. We hope to study these examples but independently develop our own framework.
- [ArduinoThread Library](https://github.com/ivanseidel/ArduinoThread)
- [Protothreading](https://create.arduino.cc/projecthub/reanimationxp/how-to-multithread-an-arduino-protothreading-tutorial-dd2c37)
- [mthread Library](https://github.com/jlamothe/mthread)
- [Concurrency with Arduino](http://concurrency.cc/)
- [Adafruit Overview](https://learn.adafruit.com/multi-tasking-the-arduino-part-1/overview)

We also hope to study general material about concurrency, especially about embedded applications, so we can apply it in our project.
- [The Little Book of Semaphores](http://greenteapress.com/semaphores/LittleBookOfSemaphores.pdf)
- [How to Use Semaphores](https://barrgroup.com/Embedded-Systems/How-To/RTOS-Mutex-Semaphore)
- [Semaphores in Arduino](https://www.hackster.io/feilipu/using-freertos-semaphores-in-arduino-ide-b3cd6c)

# First Steps

1. Our first step will be for both of us to implement a basic threading method on an Arduino Uno. To do this, we will each explore other projects' methods and write our own basic version. Both team members will be responsible for implementing a version before the consolidation meeting - a complete implementation should be able to carry out a basic example like blinking an LED. 
2. Once we have both implemented a basic version we will meet to consolidate ideas and build a second iteration. This will be done by all team members and should result in a consolidated file. At this point we will also be making basic examples of threading in use. 
3. As we are iterating on our thread implementation, we will be accumulating ideas for advancements we can make and additional features we can add. This task will be done by both team members. We will track this in trello and will be done when these cards have been added and accounted for.
4. We will next be implementing more advanced examples of our threading method in use. Once we have decided which examples we expect to implement we will split up the examples between the team members. This will be done when we have multiple complete, functional advanced examples. 
