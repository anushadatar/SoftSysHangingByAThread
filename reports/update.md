

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

# Resources and First Steps

To start, we each worked to implement a basic threading framework on the Arduino. This example leveraged a very basic thread structure to write to pins in simulated synchrony. This method offers basic functionality in that it runs processes in psuedo real time, but it requires a large amount of memory and does not accurately resemble how threads work on a higher level.

After reviewing this method, we worked on implementing a method more similar to protothreading, which involves having stackless, event driven processes run as coroutines. While this is not quite a thread (because it does not have its own stack), it provides a low-overhead framework for various use cases that we would like to explore. We have been looking at existing protothreading documentation, including Adam Dunkel's [library documentation](http://dunkels.com/adam/pt/expansion.html) for learning about how these threads work and how we can implement them. We have had some difficulties finding resources that are not source code (which we are trying to avoid looking at to improve our learning experience), but we can usually find what we need.



# Current Status
Currently, we have a threading API created as well as several examples of various complexities. For the near future we will be debugging out threading code and integrating with the examples. 

Overall, our first task going forward will be to get a basic working example running on an Arduino. Next we will be designing the more advanced tests with mutexes, semaphores, etc. This task will be done when we are able to test functionality of our threading library. Lastly, we will then be able to implement the more advanced tests. Each test will be done when tested to be working on an Ardunio. Since we will be working with multiple examples we will be able to split up the design and implementation of the examples among both the team members. Once all three of these tasks are done we should be able to present a coherent threading API suitable for outside users to understand and implement.


For more information, check our [Github Repository](https://github.com/anushadatar/SoftSysHangingByAThread) and [Trello Board](https://trello.com/b/94WQDqxF/hangingbyathread).
