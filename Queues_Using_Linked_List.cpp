#include<iostream>
#include<stdio.h>
#include<stdbool.h>

using namespace std;

int SHOWLOG = 1;

class Node {
    public:
    int data;
    Node* next;
};
class Queue {
    private:
    Node* rear, * front;
    public:
    Queue();
    Queue(int* arr, int arrLen);
    int enqueue(int data);
    int dequeue();
    void display();
    bool isEmpty();
    ~Queue();
};

int main(void) {
    int option, data;
    Queue q1;

    while (1) {
        printf("----------------------Options--------------");
        printf("1. enqueue(data)\n");
        printf("2. dequeue()\n");
        printf("3. display()\n");
        printf("4. isEmpty()\n");
        printf("-------------------------------------------");

        printf("Enter Your Option : ");
        scanf("%d", &option);

        printf("\n=========================================\n");
        switch (option) {
            case 1:
                scanf("%d", &data);
                q1.enqueue(data);
                printf("%d added to Queue\n", data);
                break;
            case 2:
                printf("%d\n", q1.dequeue());
                break;
            case 3:
                q1.display();
                break;
            case 4:
                if (q1.isEmpty()) {
                    printf("TRUE\n");
                } else printf("FALSE\n");
                break;
            default:
                printf("Enter Valid Option \n");
                break;
        }
        printf("===========================================\n");
    }
    return 0;
}

Queue::Queue(int* arr, int arrLen) {
    this->front = this->rear = NULL;
    for (int i = 0; i < arrLen; i++) {
        enqueue(arr[i]);
    }
};
Queue::Queue() {
    this->front = NULL;
    this->rear = NULL;
};

Queue::~Queue() {
    Node* startNode = this->front;
    while (startNode != NULL) {
        Node* nextNode = startNode->next;
        delete(startNode);
        startNode = nextNode;
    }
}
int Queue::enqueue(int data) {
    if (this->rear == NULL) {
        this->rear = (Node*)malloc(1 * sizeof(Node));
        this->rear->data = data;
        this->rear->next = NULL;
        this->front = this->rear;
    } else {
        Node* temp = (Node*)malloc(1 * sizeof(Node));
        temp->data = data;
        temp->next = NULL;
        this->rear->next = temp;
        this->rear = temp;
    }
    return 1;
};
int Queue::dequeue() {
    if (this->front == NULL && this->rear == NULL) {
        SHOWLOG&& printf("EMPTY, Could not enqueue\n");
        return -1;
    } else if (this->front == this->rear) {
        int deletedData = this->front->data;
        free(this->front);
        this->front = NULL;
        this->rear = NULL;
        return deletedData;
    } else {
        Node* nextNode = this->front->next;
        int deletedData = this->front->data;
        free(this->front);
        this->front = nextNode;
        return deletedData;
    }
}
void Queue::display() {
    printf("QUEUE => ||  ");
    if (isEmpty()) {
        printf("EMPTY\n");
        return;
    } else {
        Node* cursor = this->front;
        while (cursor != NULL) {
            printf("%d  ", cursor->data);
            cursor = cursor->next;
        }
        printf("\n");
    }
}
bool Queue::isEmpty() {
    if (this->front == NULL && this->rear == NULL) {
        return true;
    } else return false;
}

