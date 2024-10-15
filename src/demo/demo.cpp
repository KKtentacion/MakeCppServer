#include <iostream>

#include <pthread.h>
#include <semaphore.h>
#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int count = 0;
sem_t empty, full;

void* producer(void* arg) {
  for (int i = 0; i < 10; i++) {
    sem_wait(&empty);
    buffer[count++] = i;
    std::cout << "Produced:" << i << std::endl;
    sem_post(&full);
  }
}
void* consumer(void* arg) {
  for (int i = 0; i < 10; i++) {
    sem_wait(&full);
    int item = buffer[--count];
    std::cout << "Consumed:" << i << std::endl;
    sem_post(&empty);
  }
}
int main() {
  sem_init(&empty, 0, BUFFER_SIZE);
  sem_init(&full, 0, 0);

  pthread_t prod, cons;
  pthread_create(&prod, NULL, producer, NULL);
  pthread_create(&cons, NULL, consumer, NULL);
  pthread_join(prod, NULL);
  pthread_join(cons, NULL);

  sem_destroy(&empty);
  sem_destroy(&full);

  return 0;
}