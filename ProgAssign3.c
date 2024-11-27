//Nhu Van
//van0006

#define _REENTRANT
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>


//define buffer size and input filename
#define BUFFER_SIZE 15
#define FILENAME "mytest.dat"

char buffer[BUFFER_SIZE];
sem_t empty, full, mutex; // Semaphores for synchronization

//producer thread
void *producer(void *arg) {
    char newChar;        // Variable to store each character
    FILE* fp;            // File pointer
    int index = 0;       // Circular buffer index
    // Open the file in read mode
    fp = fopen(FILENAME, "r");
    if (fp == NULL) {    // Check if file was successfully opened
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Read characters from the file and place them into the buffer
    while (fscanf(fp, "%c", &newChar) != EOF) {
        sem_wait(&empty); // Wait for an empty slot
        sem_wait(&mutex); // Lock the buffee

        buffer[index] = newChar;
        index = (index + 1) % BUFFER_SIZE; // Update buffer index (circular buffer)

        sem_post(&mutex); // Release the buffer
        sem_post(&full);  // Signal a filled slot
    }

    // Add EOF marker to indicate completion
    sem_wait(&empty);
    sem_wait(&mutex);

    buffer[index] = '*'; // Special marker to indicate EOF
    index = (index + 1) % BUFFER_SIZE;

    sem_post(&mutex);
    sem_post(&full);

    // Close the file
    fclose(fp);

    pthread_exit(NULL); // Exit the producer thread
}


void *consumer(void *arg) {
    int index = 0;
    char ch;

    while (1) {
        sem_wait(&full);
        sem_wait(&mutex);

        ch = buffer[index];
        index = (index + 1) % BUFFER_SIZE;

        sem_post(&mutex);
        sem_post(&empty);

        if (ch == '*') { // Check for EOF
            break;
        }

        printf("%c", ch);
        fflush(stdout);
        sleep(1);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t producer_thread, consumer_thread;

    sem_init(&empty, 0, BUFFER_SIZE);  //initialize empty semaphore
    sem_init(&full, 0, 0); //full are 0
    sem_init(&mutex, 0, 1); //mutex are 1

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL); //  creating producer and consumer thread

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    sem_destroy(&empty); //release
    sem_destroy(&full);
    sem_destroy(&mutex);

    printf("\nDone!\n");
    return 0;
}

