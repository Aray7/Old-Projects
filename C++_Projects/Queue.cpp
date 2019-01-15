#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

class QueueNode
{
public:
    int val;
    QueueNode* next;
};

class Queue
{
public:
    Queue();
    Queue(const Queue& q);
    ~Queue();

    bool isEmpty();
    bool enqueue(const int val);
    bool dequeue();
    int peek() const;

    void print() const;

private:
    QueueNode* front;
    QueueNode* back;
    int size;
};

Queue::Queue()
{
    front = nullptr;
    back = nullptr;
    size = 0;
}

Queue::Queue(const Queue& q)
{
    QueueNode* thisPtr = new QueueNode();
    front = thisPtr;
    back = thisPtr;

    QueueNode* thatPtr = q.front;

    while(thatPtr != nullptr)
    {
        thisPtr->next = new QueueNode();
        thisPtr = thisPtr->next;

        thisPtr->val = thatPtr->val;
        back = thisPtr;

        thatPtr = thatPtr->next;
    }

    thisPtr = front;
    front = front->next;
    delete thisPtr;
    size = q.size;
}

Queue::~Queue()
{
    QueueNode* toDelete;

    while(front != nullptr)
    {
        toDelete = front;
        front = front->next;
        delete toDelete;
    }
}

bool Queue::isEmpty()
{
    return front == nullptr;
}

bool Queue::enqueue(const int val)
{
    QueueNode* newNode = new QueueNode();
    newNode->val = val;
    newNode->next = nullptr;

    if(isEmpty())
    {
        front = newNode;
        back = newNode;
    }
    else
    {
        back->next = newNode;
        back = back->next;
    }
    size++;
    return true;
}

bool Queue::dequeue()
{
    if(isEmpty())
    {
        cout << "Error: Cannot dequeue from empty queue\n";
        return false;
    }

    front = front->next;
    size--;

    return true;
}

int Queue::peek() const
{
    return front->val;
}

void Queue::print() const
{
    QueueNode* ptr = front;

    while(ptr != nullptr)
    {
        cout << ptr->val << ", ";
        ptr = ptr->next;
    }
    cout << "\n";
}

int main()
{
    Queue q;
    const int size = 20;

    //Enqueue some nodes
    srand(time(NULL));
    for(int i = 0; i < size; i++)
        q.enqueue(rand() % 100);

    q.print();

    //Dequeue some nodes
    for(int i = 0; i < 3; i++)
        q.dequeue();

    q.print();

    //Copy the queue from above, and peek the top element
    Queue q2(q);
    q2.print();
    cout << q2.peek() << "\n";

    return 0;
}
