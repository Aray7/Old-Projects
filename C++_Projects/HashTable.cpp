#include <fstream>
#include <iostream>
using namespace std;

template <class T>
class HashTable
{
public:
    HashTable(const int size);
    ~HashTable();

    bool contains(int key) const;
    T retrieve(int key) const;
    bool insert(int key, T node);
    bool remove(int key);

    bool isFull() const;
    void print() const;

private:
    T* table;
    bool* hold;
    int itemsStored;
    int tableSize;

    int find(int key) const;
    int hash(int key) const;

};

template <class T>
HashTable<T>::HashTable(const int size)
{
    itemsStored = 0;
    tableSize = size;
    table = new T[tableSize];
    hold = new bool[tableSize];

    for(int i = 0; i < tableSize; i++)
    {
        table[i] = nullptr;
        hold[i] = false;
    }
}

template <class T>
HashTable<T>::~HashTable()
{
    for(int i = 0; i < tableSize; i++)
        if(table[i] != nullptr)
            delete table[i];
    delete [] hold;
}

template <class T>
bool HashTable<T>::contains(int key) const
{
    return table[find(key)] != nullptr;
}

template <class T>
T HashTable<T>::retrieve(int key) const
{
    int index = find(key);
    if(index == -1)
        return nullptr;
    else
        return table[find(key)];
}

template <class T>
bool HashTable<T>::insert(int key, T node)
{
    //If the table is full, we can't insert anything
    if(isFull())
        return false;

    int index = find(key);
    table[index] = node;
    hold[index] = true;
    itemsStored++;
    return true;
}

template <class T>
bool HashTable<T>::remove(int key)
{
    int index = find(key);

    //We didn't find the record
    if(table[index] == nullptr)
    {
        cout << "Could not delete employee " << key << " because they are not in the table.\n";
        return false;
    }

    cout << "Deleting the following record: ";
    table[index]->print();
    cout << "\n";

    delete table[index];
    table[index] = nullptr;
    itemsStored--;

    return true;
}

template <class T>
bool HashTable<T>::isFull() const
{
    return itemsStored == tableSize;
}

template <class T>
void HashTable<T>::print() const
{
    cout << "___Table contents___\n";
    for(int i = 0; i < tableSize; i++)
    {
        cout << i << ": ";
        if(table[i] != nullptr)
            table[i]->print();
        else if(hold[i])
            cout << "DELETED";
        cout << "\n";
    }
}

//This function will loop forever when the hash table is completely full (load factor = 100%). While this is poor behavior,
//in practical applications, as the load factor approaches 100%, the performance begins to degrade dramatically. That means
//we should never *actually* fill up the table. We would have increased the table size and rehashed all members long before this point.
//As a rule of thumb, I'd say your hash table should never be more than 90% full, and even 90% is really bad. Keeping alpha below 66% would be ideal.

//Reason #2 why this function sucks is that it uses what's called lazy deletion. Rather than filling the gaps in our clusters, we just mark them
// as DELETED. This is fine for a while, but as time goes on, the values in our hold[] array all tend to become true, and it becomes saturated.

template <class T>
int HashTable<T>::find(int key) const
{
    int index = hash(key);

    //While there's something in the table, but it's not what we're looking for OR there was something here, but it was deleted
    //  do another linear probe

    while((table[index] != nullptr && table[index]->key() != key) ||
            (table[index] == nullptr && hold[index]))
        index = (index + 1) % tableSize;

    return index;
}

template <class T>
int HashTable<T>::hash(int key) const
{
    return key % tableSize;
}

class Employee
{
public:
    Employee();
    Employee(const int _EID, const string _firstName, const string _lastName);
    ~Employee();

    int key() const;

    void setEID(const int _EID);
    void setFirstName(const string _firstName);
    void setLastName(const string _lastName);

    int getEID() const;
    string getFirstName() const;
    string getLastName() const;

    void print() const;

private:
    int EID;
    string firstName;
    string lastName;
};

Employee::Employee()
{
    EID = 0;
    firstName = "None";
    lastName = "None";
}

Employee::Employee(const int _EID, const string _firstName, const string _lastName)
{
    EID = _EID;
    firstName = _firstName;
    lastName = _lastName;
}

Employee::~Employee()
{

}

int Employee::key() const
{
    return EID;
}

void Employee::setEID(const int _EID)
{
    EID = _EID;
}

void Employee::setFirstName(const string _firstName)
{
    firstName = _firstName;
}

void Employee::setLastName(const string _lastName)
{
    lastName = _lastName;
}

int Employee::getEID() const
{
    return EID;
}

string Employee::getFirstName() const
{
    return firstName;
}

string Employee::getLastName() const
{
    return lastName;
}

void Employee::print() const
{
    cout << EID << " " << firstName << " " << lastName;
}

int main()
{
    HashTable<Employee*> ht(100);

    Employee* test;

    ifstream database;
    database.open("employees.txt");

    int eid;
    string first, last;

    while(database >> eid >> first >> last)
    {
        test = new Employee(eid, first, last);
        ht.insert(test->key(), test);
    }

    database.close();

    ht.print();

    cout << "\nTesting contains() function...\n";
    cout << "Employee #3242 is " << (ht.contains(3242) ? "" : "not ") << "in the table.\n";
    cout << "Employee #3518 is " << (ht.contains(3518) ? "" : "not ") << "in the table.\n";
    cout << "Employee #1234 is " << (ht.contains(1234) ? "" : "not ") << "in the table.\n";
    cout << "Employee #5678 is " << (ht.contains(5678) ? "" : "not ") << "in the table.\n";

    cout << "\nTesting retrieve() function...\n";
    cout << "Employee #3242 is " << (ht.contains(3242) ? ht.retrieve(3242)->getFirstName() + " " + ht.retrieve(3242)->getLastName() : "not in the table.") << "\n";
    cout << "Employee #3518 is " << (ht.contains(3518) ? ht.retrieve(3518)->getFirstName() + " " + ht.retrieve(3518)->getLastName() : "not in the table.") << "\n";
    cout << "Employee #1234 is " << (ht.contains(1234) ? ht.retrieve(1234)->getFirstName() + " " + ht.retrieve(1234)->getLastName() : "not in the table.") << "\n";
    cout << "Employee #5678 is " << (ht.contains(5678) ? ht.retrieve(5678)->getFirstName() + " " + ht.retrieve(5678)->getLastName() : "not in the table.") << "\n";

    cout << "\nTesting remove() function...\n";
    ht.remove(3242);
    ht.remove(3518);
    ht.remove(1234);
    ht.remove(5678);
    ht.remove(4830);

    cout << "Employee #9830 is " << (ht.contains(9830) ? "" : "not ") << "in the table.\n\n";

    ht.print();

    return 0;
}
