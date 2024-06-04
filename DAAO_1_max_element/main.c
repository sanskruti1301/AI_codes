#include <stdio.h>
#include <stdlib.h>

int main()
{
    #include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 10

typedef struct {
    int *array;
    int capacity;
    int front;
    int rear;
} DynamicArrayQueue;

void initializeQueue(DynamicArrayQueue *queue) {
    queue->array = (int *)malloc(INITIAL_CAPACITY * sizeof(int));
    queue->capacity = INITIAL_CAPACITY;
    queue->front = queue->rear = -1;
}

int isEmpty(DynamicArrayQueue *queue) {
    return queue->front == -1;
}

int size(DynamicArrayQueue *queue) {
    if (isEmpty(queue)) {
        return 0;
    }
    return (queue->rear - queue->front + queue->capacity) % queue->capacity + 1;
}

void enqueue(DynamicArrayQueue *queue, int item) {
    if ((queue->rear + 1) % queue->capacity == queue->front) {
        // Queue is full, resize the array
        int newCapacity = queue->capacity * 2;
        queue->array = (int *)realloc(queue->array, newCapacity * sizeof(int));

        // Adjust the rear and front pointers after resizing
        if (queue->front > queue->rear) {
            for (int i = 0; i <= queue->rear; i++) {
                queue->array[i + queue->capacity] = queue->array[i];
            }
            queue->rear += queue->capacity;
        }

        queue->capacity = newCapacity;
    }

    if (isEmpty(queue)) {
        queue->front = queue->rear = 0;
    } else {
        queue->rear = (queue->rear + 1) % queue->capacity;
    }

    queue->array[queue->rear] = item;
}

int dequeue(DynamicArrayQueue *queue) {
    if (isEmpty(queue)) {
        printf("Error: Queue is empty\n");
        return -1; // Error value, assuming -1 is not a valid element in the queue
    }

    int item = queue->array[queue->front];

    if (queue->front == queue->rear) {
        // Last element in the queue, reset front and rear
        queue->front = queue->rear = -1;
    } else {
        queue->front = (queue->front + 1) % queue->capacity;
    }

    return item;
}

void freeQueue(DynamicArrayQueue *queue) {
    free(queue->array);
    queue->front = queue->rear = -1;
    queue->capacity = 0;
}

int main() {
    DynamicArrayQueue queue;
    initializeQueue(&queue);

    char choice;
    int number, a=0;

    do {
        while(a<10)
        {
        printf("Enter an integer: ");
        scanf("%d", &number);
        enqueue(&queue, number);
        a++;
        }

        printf("Do you want to enter another integer? (Y/N): ");
        scanf(" %c", &choice);  // Notice the space before %c to consume the newline character

    } while (choice == 'Y' || choice == 'y');




    printf("Queue size: %d\n", size(&queue));





    freeQueue(&queue);

    return 0;
}

    return 0;
}
