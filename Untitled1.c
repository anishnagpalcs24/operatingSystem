#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

int buffer[SIZE];
int in = 0, out = 0;
int item = 0;

// Semaphores
int mutex = 1;
int empty = SIZE;
int full = 0;

// Wait (P)
void wait(int *s) {
    while (*s <= 0); // busy wait
    (*s)--;
}

// Signal (V)
void signal(int *s) {
    (*s)++;
}

// Display buffer
void display() {
    int i;
    printf("Buffer: ");
    for (i = 0; i < SIZE; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");
}

// Producer
void producer() {
    if (empty == 0) {
        printf("Buffer is FULL! Cannot produce.\n");
        return;
    }

    wait(&empty);
    wait(&mutex);

    item++;
    buffer[in] = item;
    printf("Producer produced: Item %d\n", item);

    in = (in + 1) % SIZE;

    signal(&mutex);
    signal(&full);

    display();
}

// Consumer
void consumer() {
    if (full == 0) {
        printf("Buffer is EMPTY! Cannot consume.\n");
        return;
    }

    wait(&full);
    wait(&mutex);

    int consumed = buffer[out];
    printf("Consumer consumed: Item %d\n", consumed);

    buffer[out] = 0; // optional: clear slot
    out = (out + 1) % SIZE;

    signal(&mutex);
    signal(&empty);

    display();
}

int main() {
    int choice;

    while (1) {
        printf("\n1. Producer\n2. Consumer\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                producer();
                break;
            case 2:
                consumer();
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
