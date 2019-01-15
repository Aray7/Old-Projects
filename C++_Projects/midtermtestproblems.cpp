#include <iostream>
using namespace std;

//#6 on midterm
void insert(const int value)
{
  ListNode* newNode = new ListNode();
  newNode->value = value;
  newNode-next = nullptr;

  if (head == nullptr)
    head = newNode;

  else
  {
    ListNode* current = head;
    ListNode* previous = head;

    while (current != nullptr && current->value < newNode->value)
    {
      previous = current;
      current = current->next;
    }

    newNode->next = current;

    if (previous != current)
      previous->next = newNode
    else
      head = newNode;
  }
}

//#10 on midterm
int sumDigits(int n)
{
  if(n < 10)
      return n;
  else
      return n % 10 + sumDigits(n / 10);
}
