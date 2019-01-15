#include <iostream>
#include <fstream>
#include <cstring>

#define INFILENAME "guests.txt"

using namespace std;

//Guest class for each customer
class Guest{
private:
	char name[48];
	int arrivalTime;
public:
	Guest(char* n,int at){
		strcpy(name,n);
		arrivalTime = at;
	}
	char* getName(){
		return name;
	}
	int getArrivalTime(){
		return arrivalTime;
	}
};

//Queue implementation
class Queue{
private:
	Guest **guests;
	int index;
	int queueSize;
public:
	Queue(){
		index = 0;
		queueSize = 10;
		guests = new Guest*[queueSize];
	}
	void enqueue(Guest *guest){
		//if queue is full
		if(index == queueSize){
			//increase the queue size
			queueSize += 10;
			//allocate memory for the new guest queue
			Guest** newGuests = new Guest*[queueSize];
			//copy the previous array
	        for(int i=0;i<index;i++){
	            newGuests[i] = guests[i];
	        }
	        //deallocate previous memory
	        delete[] guests;
	        guests = newGuests;
		}
		//add the guest to end of the line
		guests[index] = guest;
		index ++;
	}
	Guest* peek(){
		//if queue is empty return null
		if(index == 0) return NULL;
		//return the last guest
		return guests[index - 1];
	}
	Guest* dequeue(){
		//if queue is empty return null
		if(index == 0) return NULL;
		//decrease the queue length
		index--;
		//return the last guest
		return guests[index];
	}
	int inQueue(){
		//return the total number of guest in queue
		return index;
	}
	void show(){
		//display the queue's guest's name
		for(int i=0;i<index;i++){
			cout << guests[i]->getName()<<" ";
		}
	}
};
//Ride class
class Ride{
private:
	Queue *queue;
	char name[40];
	int rideTime;
	int capacity;
	int runTime;
public:
	Ride(char *n,int rt,int cap){
		strcpy(name,n);
		queue = new Queue();
		rideTime = rt;
		capacity = cap;
		runTime = rt-1;
	}
	char * getName(){
		return name;
	}
	int getCapacity(){
		return capacity;
	}
	int getRideTime(){
		return rideTime;
	}
	void arrivalGuest(Guest *guest){
		//add the guest to the queue
		queue->enqueue(guest);
	}
	int calculateWaitTime(){
		//get total guests in queue
		int inQueue = queue->inQueue();
		//if number of guests in queue equals capacity
		if(inQueue == capacity){
			//add the rideTime of the next ride as well
			return runTime + rideTime;
		}
		//return the leftover runTime
		return runTime;
	}
	bool isBoarding(){
		//if runTime is 0 then the ride is boarding
		if(runTime == 0){
			return true;
		}
		//else ride isn't boarding
		else{
			return false;
		}
	}
	void checkBoarding(){
		//if ride is boarding
		if(isBoarding()){
			//if queue is empty then ride is idle
			if(queue->inQueue() == 0){
				cout  <<"\t"<< name << " is idle."<<endl;
			}
			//else ride is boarding
			else{
				cout <<"\t" << name << " is now boarding : ";
				for(int i=0;i<capacity;i++){
					//remove last guest of the queue
					Guest *guest = queue->dequeue();
					if(guest != NULL){
						//print the guest's name
						cout << guest->getName() << " ";
					}
				}
				cout << endl;
			}
			//increment the runTime
			runTime += rideTime;
		}
		//decrement the runTime
		runTime --;
	}
	void showQueue(){
		cout <<"\t" << name << " line : ";
		queue->show();
		cout <<endl;
	}
};
//Helper class
class GuestManager{
private:
	Guest** guests;
	int totalGuests;
public:
	GuestManager(char * fileName){
		ifstream file(fileName);
		//get the total number of guests
		file >> totalGuests;
		//allocate guests memory
		guests = new Guest*[totalGuests];
		int arrivalTime;
		char guestName[40];
		for(int i=0;i<totalGuests;i++){
			file >> arrivalTime >> guestName;
			//initialize guest
			guests[i] = new Guest(guestName,arrivalTime);
		}
	}
	Guest* getGuest(int t){
		//return guest for time stamp t
		for(int i=0;i<totalGuests;i++){
			if(guests[i]->getArrivalTime() == t){
				return guests[i];
			}
		}
		return NULL;
	}
};

int main(int argc, char const *argv[])
{
	int t = 0;
	GuestManager guestManager(INFILENAME);
	Ride mrBonesWildRide("Mr. Bones' Wild Ride",10,2);
	Ride noFunHouse("The No-Fun House",7,3);
	int waitBones,waitFun;
	//run the loop for virtual 35 minutes
	while(t < 35){
		t++;
		cout << "t = "<<t<<endl;
		cout <<"-----------------------------------"<<endl;
		//check boarding of both the rides
		mrBonesWildRide.checkBoarding();
		noFunHouse.checkBoarding();
		//get the guest - arrival at t
		Guest* guest = guestManager.getGuest(t);
		if(guest != NULL){
			//calculate waiting time of both the rides
			waitFun = noFunHouse.calculateWaitTime();
			waitBones = mrBonesWildRide.calculateWaitTime();
			//print the message
			cout <<"\t" << guest->getName() << " is choosing between "<< mrBonesWildRide.getName()
				 <<" ( wait time = "<<waitBones<<" minutes ) and "<<noFunHouse.getName()
				 <<" ( wait time = "<<waitFun<<" minutes )."<<endl;
			// allocate the ride to the one with small waiting time
			if(waitFun < waitBones){
				noFunHouse.arrivalGuest(guest);
				cout  <<"\t"<< guest->getName() << " has entered the line for "<< noFunHouse.getName()<<"."<<endl;
			}
			else if(waitFun > waitBones){
				mrBonesWildRide.arrivalGuest(guest);
				cout  <<"\t"<< guest->getName() << " has entered the line for "<< mrBonesWildRide.getName()<<"."<<endl;
			}
		}
		//show both the queue's guests
		mrBonesWildRide.showQueue();
		noFunHouse.showQueue();
		cout <<"-----------------------------------"<<endl;
	}
	return 0;
}
