#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

//Guest class for each customer
class Guest
{
public:
	Guest(char* n, int at);
	char* getName();
	int getArrivalTime();
  Guest* next;
private:
	char name[48];
	int arrivalTime;
};

//Queue implementation
class Queue
{
public:
	Queue();
	Queue(Queue& other);
	~Queue();
	void enqueue(Guest* guest);
	Guest* peek();
	Guest* dequeue();
	int inQueue();
	void show();
private:
  Guest* front;
  Guest* back;
	Guest** guests;
	int index;
	int queueSize;
};

//Ride class
class Ride
{
public:
	Ride(char* n, int rt, int cap);
	char* getName();
	int getCapacity();
	int getRideTime();
	void arrivalGuest(Guest* guest);
	int calculateWaitTime();
	bool isBoarding();
	void checkBoarding();
	void showQueue();
private:
	Queue* queue;
	char name[40];
	int rideTime;
	int capacity;
	int runTime;
};

//Helper class
class GuestManager
{
public:
	GuestManager(char* fileName);
	Guest* getGuest(int t);
private:
	Guest** guests;
	int totalGuests;
};

Guest::Guest(char* n, int at)
{
	strcpy(name, n);
	arrivalTime = at;
}

char* Guest::getName()
{
	return name;
}

int Guest::getArrivalTime()
{
	return arrivalTime;
}

Queue::Queue()
{
	index = 0;
	queueSize = 10;
	guests = new Guest* [queueSize];
}

Queue::Queue(Queue& other)
{
  index = other.index;
	queueSize = other.queueSize;
}

Queue::~Queue()
{
}

void Queue::enqueue(Guest* guest)
{
	if (index == queueSize)
	{
		queueSize += 10;
		Guest** newGuests = new Guest*[queueSize];
				for(int i = 0; i < index; i++)
				{
						newGuests[i] = guests[i];
				}
				delete[] guests;
				guests = newGuests;
	}

	guests[index] = guest;
	index++;
}

Guest* Queue::peek()
{
	if(index == 0)
		return NULL;

	return guests[index - 1];
}

Guest* Queue::dequeue()
{
	if(index == 0)
		return NULL;

  front = front->next;
	index--;
	return guests[index];
}

int Queue::inQueue()
{
	return index;
}

void Queue::show()
{
	for(int i = 0; i < index; i++)
	{
		cout << guests[i]->getName() << " ";
	}
}

Ride::Ride(char* n, int rt, int cap)
{
	strcpy(name, n);
	queue = new Queue();
	rideTime = rt;
	capacity = cap;
	runTime = rt-1;
}

char* Ride::getName()
{
	return name;
}

int Ride::getCapacity()
{
	return capacity;
}

int Ride::getRideTime()
{
	return rideTime;
}

void Ride::arrivalGuest(Guest* guest)
{
	queue->enqueue(guest);
}

int Ride::calculateWaitTime()
{
	int inQueue = queue->inQueue();
	if(inQueue == capacity)
  {
		return runTime + rideTime;
	}
	return runTime;
}

bool Ride::isBoarding()
{
	if(runTime == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Ride::checkBoarding()
{
	if(isBoarding())
	{
		if(queue->inQueue() == 0)
		{
			cout  << "\t" << name << " is idle." << endl;
			cout << endl;
		}
		else
		{
			cout << "\t" << name << " is now boarding : ";

			for(int i = 0; i < capacity; i++)
			{
				Guest* guest = queue->dequeue();
				if (guest != NULL)
				{
					cout << guest->getName() << " ";
				}
			}
			cout << endl << endl;
		}
		runTime += rideTime;
	}
	runTime--;
}

void Ride::showQueue()
{
  //added "\t" because found that it helps align the tab output
	cout << "\t" << name << " line : ";
	queue->show();
	cout << endl;
}

GuestManager::GuestManager(char* fileName)
{
	ifstream file(fileName);
	file >> totalGuests;

	guests = new Guest*[totalGuests];
	int arrivalTime;
	char guestName[40];

	for(int i = 0; i < totalGuests; i++)
	{
		file >> arrivalTime >> guestName;
		guests[i] = new Guest(guestName, arrivalTime);
	}
}

Guest* GuestManager::getGuest(int t)
{
	for(int i = 0; i < totalGuests; i++)
	{
		if(guests[i]->getArrivalTime() == t)
		{
			return guests[i];
		}
	}
	return NULL;
}

int main()
{
	int t = 0;
	int waitBones, waitFun;

	GuestManager guestManager("guests.txt");
	Ride mrBonesWildRide("Mr. Bones' Wild Ride", 10, 2);
	Ride noFunHouse("The No-Fun House", 7, 3);

	while(t < 35)
	{
		t++;
		cout << "t = " << t << endl;
		cout << "-----------------------------------" << endl;
    cout << endl;
		mrBonesWildRide.checkBoarding();
		noFunHouse.checkBoarding();
		Guest* guest = guestManager.getGuest(t);
		if(guest != NULL)
		{
			waitFun = noFunHouse.calculateWaitTime();
			waitBones = mrBonesWildRide.calculateWaitTime();

			//added "\t" because found that it helps align the tab output
			cout << "\t" << guest->getName() << " is choosing between "<< mrBonesWildRide.getName()
				 << " (wait time = " << waitBones << " minutes) and " << noFunHouse.getName()
				 << " (wait time = " << waitFun << " minutes)." << endl;

			if(waitFun < waitBones)
			{
				noFunHouse.arrivalGuest(guest);
				cout << "\t" << guest->getName() << " has entered the line for " <<
        noFunHouse.getName() << "." << endl;
				cout << endl;
			}

			else if(waitFun > waitBones)
			{
				mrBonesWildRide.arrivalGuest(guest);
				cout  << "\t" << guest->getName() << " has entered the line for "
				<< mrBonesWildRide.getName() << "." << endl;
				cout << endl;
			}
		}
		mrBonesWildRide.showQueue();
		noFunHouse.showQueue();
		cout << "-----------------------------------" << endl;
    cout << endl << endl;
	}
	return 0;
}
