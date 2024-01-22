Amherst candy factory is preparing up for Halloween and has implemented an assembly line to 
ramp up Halloween candy production. The assembly line will be implemented using a bounded 
buffer producer and consumers. The factory contains two types of worker threads: producers and 
consumers. Each producer thread produces a certain type of candy, while each consumer creates 
boxes of assorted candies using ones produced by producers. After producing each candy, the 
producer deposits into the bounded buffer. If the buffer is full, it must wait until one slot becomes 
available. A consumer extracts candy from the bounded buffer, one at a time, and when 1 candy 
items have been extracted, it fills up a box of assorted candy. Implement a synchronization method 
to solve the problem.
