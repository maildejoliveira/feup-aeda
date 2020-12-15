#ifndef CARPARK_H_
#define CARPARK_H_

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class InfoCard {
public:
    string name;
    bool present;
    int frequency;
    friend bool operator<(const InfoCard client1, const InfoCard client2);
};

class CarPark {
    unsigned freePlaces;
    const unsigned  capacity;
    vector<InfoCard> clients;
    const unsigned numMaxClients;
public:
    CarPark(unsigned cap, unsigned nMaxCli);
    unsigned getNumPlaces() const;
    unsigned getNumMaxClients() const;
    unsigned getNumOccupiedPlaces() const;
    vector<InfoCard> getClients() const;
    unsigned getNumClients() const;
    bool addClient(const string & name);
    bool removeClient(const string & name);
    bool enter(const string & name);
    bool leave(const string & name);
    int clientPosition(const string & name) const;
    friend ostream & operator<<(ostream & os, const CarPark & cp);
    unsigned getFrequency(const string &name) const;
    InfoCard getClientAtPos(unsigned p) const;
    void sortClientsByFrequency();
    void sortClientsByName();
    vector<string> clientsBetween(unsigned f1, unsigned f2);
};

class ClientDoesNotExist
{
public:
    string name;
    string getName() {
        return name;
    }
    ClientDoesNotExist(string n) {
        name = n;
        getName();
    }
};

class PositionDoesNotExist
{
public:
    unsigned p;
    unsigned getPosition() {
        return p;
    }
    PositionDoesNotExist(unsigned pos) {
        p = pos;
        getPosition();
    }
};


#endif /*CARPARK_H_*/
