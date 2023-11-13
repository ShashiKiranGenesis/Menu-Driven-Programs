#include<iostream>
#include<stdio.h>
#include<math.h>

using namespace std;

bool SHOW_LOG = true;

class Queue {
    private:
    int size;
    int front, rear;

    int* data;
    public:
    Queue() {
        front = 0; rear = 0;
    }
    Queue(int size) {
        front = 0; rear = 0;
        this->size = size + 1;
        data = (int*)malloc((this->size) * sizeof(int));
    };
    int enqueue(int data);
    void display();
    int dequeue();
    bool isEmpty();
    bool isFull();
    void getDetails();
    ~Queue() {
        delete[]data;
    }
};

int main(void) {
    Queue q1;
    int size;

    int option; int val;

    printf("Enter the size of the Queue to Create : ");
    scanf("%d", &size);
    q1 = Queue(size);

    while (1) {

        printf("\n-------------Options----------------\n");
        printf("1. enqueue(data)\n");
        printf("2. dequeue()\n");
        printf("3. display()\n");
        printf("4. isEmpty()\n");
        printf("5. isFull()\n");
        printf("6. getDetails()\n");
        printf("---------------------------------------\n");
        printf("Enter Your Option  : ");
        scanf("%d", &option);

        printf("\n=============================================\n");
        switch (option) {
            case 1:
                scanf("%d", &val);
                q1.enqueue(val) && printf("%d added to queue\n", val);
                break;
            case 2:
                printf("%d\n", q1.dequeue());
                break;
            case 3:
                q1.display();
                break;
            case 4:
                if (q1.isEmpty()) printf("TRUE\n");
                else printf("FALSE\n");
                break;
            case 5:
                if (q1.isFull()) printf("TRUE\n");
                else printf("FALSE\n");
                break;
            case 6:
                q1.getDetails();
                break;
            default:
                printf("INVALID CHOICE\n");
                break;
        }
        printf("=============================================\n");
    }

    return 0;
};

int Queue::enqueue(int data) {
    if ((this->rear + 1) % this->size == this->front) {
        SHOW_LOG&& printf("Queue Full, Could not add to Queue\n");
        return 0;
    } else {
        this->rear = (this->rear + 1) % this->size;
        this->data[this->rear] = data;
        return 1;
    }
};
int Queue::dequeue() {
    if (this->front == this->rear) {
        SHOW_LOG&& printf("Queue Empty, could not dequeue\n");
        return -1;
    } else {
        this->front = (this->front + 1) % this->size;
        return this->data[this->front];
    }
};
bool Queue::isEmpty() {
    if ((this->front == this->rear)) {
        return true;
    } else return false;
}
bool Queue::isFull() {
    if ((this->rear + 1) % size == this->front) {
        return true;
    } else return false;
}
void Queue::display() {

    printf("Q || =>  ");
    int frontP = this->front;
    int rearP = this->rear;
    while (frontP != rearP) {
        frontP = (frontP + 1) % this->size;
        printf("%d  ", this->data[frontP]);
    }
    printf("_ \n");

    return;
}
void Queue::getDetails() {
    int availableSlots;
    if (this->rear >= this->front)
        availableSlots = this->size - 1 - (abs(this->rear - this->front));
    else if (this->front > this->rear)
        availableSlots = this->front - this->rear - 1;

    printf("Queue Size    :    %d\n", this->size - 1);
    printf("Free spaces   :    %d\n", availableSlots);
    printf("Front Pointer :    %d\n", this->front);
    printf("Rear Pointer  :    %d\n", this->rear);
    display();
}