#include "Queue.h"
#include <iostream>

// Constructor to initialize an empty queue
Queue::Queue() {
    // TODO: Your code here
    front = rear = -1;
}

// Adds a province to the end of the queue
void Queue::enqueue(int province) {
    // TODO: Your code here
    // Implement circular structure 
    // Add the province 
    if ((rear+1) % MAX_QUEUE_SIZE == front)  {
        std::cerr << "Queue is full. Couldnt add more provinces." << std::endl;
        return;
    }  else if (isEmpty())  {
        front = rear = 0;
    } else  {
        rear = (rear+1) % MAX_QUEUE_SIZE;
    }

    data[rear] = province;
}

// Removes and returns the front province from the queue
int Queue::dequeue() {
    // TODO: Your code here
    if(isEmpty())   {
        std::cerr << "Queue is empty. Cannot dequeue." << std::endl;
        return -1;      // return default value -1 but i couldnt like that
    }

    int province = data[front];

    if(front == rear)   {
        front = rear = -1;
    } else  {
        front = (front +1) % MAX_QUEUE_SIZE;
    }

    return province;
}

// Returns the front province without removing it
int Queue::peek() const {
    // TODO: Your code here
    if (isEmpty())  {
        std::cerr << "Queue is empty. Nothing to peek." << std::endl;
        return -1;
    }

    return data[front];
}

// Checks if the queue is empty
bool Queue::isEmpty() const {
    // TODO: Your code here
    return front==-1;
}

// Add a priority neighboring province in a way that will be dequeued and explored before other non-priority neighbors
void Queue::enqueuePriority(int province) {
    // TODO: Your code here
    if ((rear+1) % MAX_QUEUE_SIZE == front)   {
        std::cerr << "Queue is full. Cannpt enqueue priority province." << std::endl;
        return;
    }

    if (isEmpty())  {
        front= rear = 0;
        data[front] = province;
    } else {
        int currentSize = (rear >= front) ? (rear-front+1) : (MAX_QUEUE_SIZE-front+rear+1);
        
        for(int i = currentSize; i>0; --i)  {
            data[(front+i) % MAX_QUEUE_SIZE] = data[(front+i-1) % MAX_QUEUE_SIZE];
        }

        data[front] = province;
        rear =  (rear+1) % MAX_QUEUE_SIZE;
    }
}

