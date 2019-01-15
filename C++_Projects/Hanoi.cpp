#include <iostream>
#include <string>
using namespace std;

const int TOWER_SIZE = 6;
int numMoves = 0;

class StackNode{
public:
    int val;
    StackNode* next;
};

class Stack{

public:
    Stack();
    Stack(const Stack& s);
    ~Stack();

    bool push(const int val);
    int pop();
    int peek() const;

    bool isEmpty() const;
    int getSize() const;
    void print() const;

    StackNode* top;
    string name;

private:
    int size;
};

Stack::Stack()
{
    top = nullptr;
    size = 0;
}

Stack::Stack(const Stack& s)
{
    if(s.isEmpty())
        return;

    //If the Stack s is not empty, there is at least one node. Copy it.
    StackNode* ptr = s.top;
    top = new StackNode();
    top->val = ptr->val;
    top->next = nullptr;

    //Point ptr to the next node to copy, and create a second pointer to our new list
    ptr = ptr->next;
    StackNode* copy = top;

    //While there's another node to copy
    while(ptr != nullptr)
    {
        //Allocate space for a new node and move the pointer to it
        copy->next = new StackNode();
        copy = copy->next;

        //Copy the data from s
        copy->val = ptr->val;
        copy->next = nullptr;

        //Advance ptr
        ptr = ptr->next;
    }
}

Stack::~Stack()
{
    while(top != nullptr)
    {
        StackNode* toDelete = top;
        top = top->next;
        delete toDelete;
    }
}

bool Stack::push(const int val)
{
    //Allocate space for the new node
    StackNode* newNode = new StackNode();

    //Set the new node's variables
    newNode->val = val;
    newNode->next = top;

    //Update the top pointer and the size
    top = newNode;
    size++;

    return true;
}

int Stack::pop()
{
    if(isEmpty())
        cout << "Error: Cannot pop from empty stack\n";

    StackNode* toDelete = top;
    top = top->next;
    int output = toDelete->val;
    delete toDelete;
    size--;
    return output;
}

int Stack::peek() const
{
    return top->val;
}

bool Stack::isEmpty() const
{
    return top == nullptr;
}

int Stack::getSize() const
{
    return size;
}

void Stack::print() const
{
    StackNode* ptr = top;

    while(ptr != nullptr)
    {
        cout << ptr->val << "\n";
        ptr = ptr->next;
    }
}

void print_towers(Stack& t1, Stack& t2, Stack& t3)
{
    cout << "\n\n\n";
    if(numMoves > 0)
        cout << "Move " << numMoves << ":\n";
    else
        cout << "Initial state:\n";
    cout << "src\textra\tdest\n";

    Stack* src;
    Stack* extra;
    Stack* dest;

    //Super awkward code to figure out which tower is which, since solve_hanoi renames them
    if(t1.name == "src") src = &t1;
    else if(t2.name == "src") src = &t2;
    else if(t3.name == "src") src = &t3;
    if(t1.name == "extra") extra = &t1;
    else if(t2.name == "extra") extra = &t2;
    else if(t3.name == "extra") extra = &t3;
    if(t1.name == "dest") dest = &t1;
    else if(t2.name == "dest") dest = &t2;
    else if(t3.name == "dest") dest = &t3;

    StackNode* src_ptr = src->top;
    StackNode* extra_ptr = extra->top;
    StackNode* dest_ptr = dest->top;

    for(int i = TOWER_SIZE; i > 0;  i--)
    {
        if(src->getSize() >= i)
        {
            cout << src_ptr->val;
            src_ptr = src_ptr->next;
        }
        else
            cout << "-";

        if(extra->getSize() >= i)
        {
            cout << "\t" << extra_ptr->val;
            extra_ptr = extra_ptr->next;
        }
        else
            cout << "\t-";

        if(dest->getSize() >= i)
        {
            cout << "\t" << dest_ptr->val;
            dest_ptr = dest_ptr->next;
        }
        else
            cout << "\t-";
        cout << "\n";
    }
}

void solve_hanoi(int count, Stack& src, Stack& dest, Stack& extra)
{
    if(count <= 1 && !src.isEmpty())
    {
        dest.push(src.pop());
        numMoves++;
        print_towers(src, extra, dest);
    }
    else
    {
        solve_hanoi(count - 1, src, extra, dest);
        solve_hanoi(1, src, dest, extra);
        solve_hanoi(count - 1, extra, dest, src);
    }
}

int main()
{
    Stack src;
    src.name = "src";
    Stack extra;
    extra.name = "extra";
    Stack dest;
    dest.name = "dest";

    for(int i = TOWER_SIZE; i > 0; i--)
        src.push(i);

    print_towers(src, extra, dest);
    solve_hanoi(TOWER_SIZE, src, dest, extra);

    cout << "\nThe problem was solved in " << numMoves << " moves.\n";

    return 0;
}
