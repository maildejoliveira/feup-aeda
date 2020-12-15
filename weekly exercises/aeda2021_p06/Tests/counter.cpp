#include <queue>
#include <cstdlib>
#include "counter.h"
#include "exceptions.h"
using namespace std;


Client::Client() {
    numGifts = rand()%4 + 1;
}
unsigned Client::getNumGifts() const {
    return numGifts;
}


Counter::Counter(unsigned wt): wrappingTime(wt) {
    actualTime=0;
    nextEnter=rand()%19 +1;
    nextLeave=0;
    numAttendedClients=0;
}
unsigned Counter::getActualTime() const {
    return actualTime;
}
unsigned Counter::getNextEnter() const {
    return nextEnter;
}
unsigned Counter::getNumAttendedClients() const {
    return numAttendedClients;
}
unsigned Counter::getWrappingTime() const {
    return wrappingTime;
}
unsigned Counter::getNextLeave() const {
    return nextLeave;
}
Client & Counter::getNextClient() {
    if(clients.empty()){
        EmptyQueue e;
        throw (e);
    }
    return clients.front();
}
void Counter::enter()
{
    if(clients.empty()){
        nextLeave=rand()%19+1;
    }
    Client *c= new Client();
    clients.push(*c);
    nextLeave= actualTime + c->getNumGifts() * wrappingTime;
    cout << "time = " << actualTime  << " Num of gifts: "<< c->getNumGifts() << endl;
}
void Counter::leave()
{
    Client *c= new Client();
    *c=getNextClient();
    clients.pop();
    nextLeave = nextLeave + c->getNumGifts()*wrappingTime;
    cout << "time = " << actualTime  << " Num of gifts: "<< c->getNumGifts() << endl;
    numAttendedClients++;
}
//REVER
void Counter:: nextEvent()
{
    if(actualTime=nextEnter){
        enter();
    }
    else if(actualTime=nextLeave){
        leave();
    }
    else if((actualTime-nextEnter) > (actualTime-nextLeave)){
        leave();
    }
    else if((actualTime-nextEnter) < (actualTime-nextLeave)) {
        enter();
    }
    cout << "Number of attended clients: " << numAttendedClients
    << " Actual time: " << actualTime << " Next enter: " << nextEnter
    << " Next leave: " << nextLeave << endl;
}
ostream & operator << (ostream & out, const Counter & c2)
{
    out << "NUM OF ATTENDED CLIENTS: "<< c2.getNumAttendedClients();
    out << "NUM OF CLIENTS IN QUEUE: "<< c2.clients.size();
    return out;
}


