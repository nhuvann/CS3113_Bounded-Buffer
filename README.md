# CS3113_Bounded-Buffer

Author: Nhu Van


### **Description**
The objective is to demonstrate the use of semaphores to manage access to a limited-size resource effectively. A circular buffer with a capacity of 15 positions (each position capable of storing one character) will facilitate communication between two threads: a producer and a consumer. 

The **producer thread** is responsible for reading characters sequentially from a file and placing them into the buffer until the end-of-file (EOF) marker is encountered. For the purpose of program submission, the file must be named **“mytest.dat”**, although alternative files may be used for individual testing. The file should contain no more than 150 characters. The producer must notify the consumer when it has completed placing the final character into the buffer. This notification can be achieved by placing a designated special character (e.g., “*”) in the shared buffer or by employing a shared memory flag that the producer sets to indicate completion, which the consumer will check accordingly.

The **consumer thread** will retrieve characters sequentially from the shared buffer and display them on the screen. To simulate a slower operation compared to the producer, the consumer will include a one-second delay between consecutive reads from the shared buffer.

A **parent process** will manage the creation of both producer and consumer threads and will ensure the proper destruction of semaphores once both threads have completed execution. This setup aims to ensure proper synchronization and demonstrate controlled access to shared resources.


### **Compilation Steps**

1. **Prerequisites:**

   - Make sure you have a **C compiler** installed, such as `gcc`.
   - You should also be using a **UNIX-like environment** (e.g., Linux or macOS) since the program uses system calls specific to UNIX

2. ** To run**
   - Clone the code from the github( or import the attached code)
   - In your terminal, cd into the directory that holds the file with "cd [Directory Name]"
   - Ls to check if the file "ProgAssign3.c" is in the directory
   - To compile, use 'gcc name_of_program.c -lpthread -lrt'
   - To edit, use 'nano ProgAssign3.c'
  
   - Lastly, ./a.out to run!
  
The output your program produces will be a reconstruction of the original thread contained in “mytest.dat”. It need not include the “*” character.
