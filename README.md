# qthread_test
Parallel processing implemented using QRunnable derived threads

Qt provides a managed thread pool interface called QRunnable.  This construct 
may be used to implement a parallel processing algorithm with minimal overhead.

The Runner implementation class is derived from QRunnable and implements the
run override member function to perform a long running task.  In this case, an 
HD image frame is allocated in memory, populated with random values, and then 
destroyed in a loop.

The program creates three independent worker threads that perform the task 
simoultaneously on separate cores of the CPU.  During execution of the worker 
threads, the main thread of the program is blocked by entering a polling loop to 
wait for the completion of all three worker threads.

The worker threads signal completion of their task by setting a finshed flag when
they are done.  It is important to note that the calling thread must set the 
finished flag to false in each of the worker threads prior to launching.

Worker threads are launched from the global thread pool managed by Qt.  Note that
the threads have autoDelete set to false.  This is done so that the worker threads
may be re-used by the program.  The tryStart method is used to launch re-usable
threads.
