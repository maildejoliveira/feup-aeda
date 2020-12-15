#include "carPark.h"
#include "insertionSort.h"
#include "sequentialSearch.h"
#include <algorithm>
#include <vector>
using namespace std;

CarPark::CarPark(unsigned cap, unsigned nMaxCli): capacity(cap), numMaxClients(nMaxCli)
{
    freePlaces=cap;
}

vector<InfoCard> CarPark::getClients() const
{
    return clients;
}

unsigned CarPark::getNumPlaces() const
{
    return capacity;
}

unsigned CarPark::getNumOccupiedPlaces() const
{
    return capacity-freePlaces;
}

unsigned CarPark::getNumMaxClients() const
{
    return numMaxClients;
}

unsigned CarPark::getNumClients() const
{
    return clients.size();
}

int CarPark::clientPosition(const string & name) const
{
    vector<string> clients_names;
    for (int i=0; i<clients.size(); i++){
        clients_names.push_back(clients[i].name);
    }
    return sequentialSearch(clients_names,name);
}

unsigned CarPark::getFrequency(const string &name) const
{
    if(clientPosition(name)==-1) throw ClientDoesNotExist(name);
    return clients[clientPosition(name)].frequency;
}

bool CarPark::addClient(const string & name)
{
    if (clients.size() == numMaxClients) return false;
    if (clientPosition(name) != -1) return false;
    InfoCard info;
    info.name=name;
    info.present=false;
    info.frequency=0;
    clients.push_back(info);
    return true;
}

bool CarPark::removeClient(const string & name)
{
    for (vector<InfoCard>::iterator it = clients.begin(); it != clients.end(); it++)
        if ( (*it).name == name ) {
            if ( (*it).present == false ) {
                clients.erase(it);
                return true;
            }
            else return false;
        }
    return false;
}

bool CarPark::enter(const string & name)
{
    if (freePlaces == 0) return false;
    int pos = clientPosition(name);
    if (pos == -1) return false;
    if (clients[pos].present == true) return false;
    clients[pos].present = true;
    clients[pos].frequency++;
    freePlaces--;
    return true;
}

bool CarPark::leave(const string & name)
{
    int pos = clientPosition(name);
    if (pos == -1) return false;
    if (clients[pos].present == false) return false;
    clients[pos].present = false;
    freePlaces++;
    return true;
}

// TODO
InfoCard CarPark::getClientAtPos(unsigned p) const
{
    InfoCard info;
    if (p > clients.size()) throw PositionDoesNotExist(p);
    info = clients[p];
    return info;
}

void CarPark::sortClientsByFrequency()
{
    insertionSort(clients);
}

void CarPark::sortClientsByName()
{
    for(unsigned int j=clients.size()-1; j>0; j--)
    {
        bool trocar=false;
        for(unsigned int i = 0; i<j; i++)
            if(clients[i+1].name < clients[i].name) {
                swap(clients[i],clients[i+1]);
                trocar = true;
            }
        if (!trocar) return;
    }
}

vector<string> CarPark::clientsBetween(unsigned f1, unsigned f2)
{
    vector<string> names;
    sortClientsByFrequency();
    for (unsigned int i=0; i<clients.size(); i++){
        if (clients[i].frequency>=f1 && clients[i].frequency<=f2)
            names.push_back(clients[i].name);
    }
    return names;
}

ostream & operator<<(ostream & os, const CarPark & cp)
{
    for (int i = 0; i < cp.clients.size(); ++i) {
        os << "Client " << i << endl;
        os << "Name: " << cp.clients[i].name << endl;
        os << "Frequency: " << cp.clients[i].frequency << endl;
        os << "Present: "  << cp.clients[i].present << endl;
    }
    return os;
}

bool operator<(const InfoCard client1, const InfoCard client2) {
    if (client1.frequency < client2.frequency) return false;
    else if(client1.frequency > client2.frequency) return true;
    else if(client1.name<client2.name) return true;
    return false;
}
