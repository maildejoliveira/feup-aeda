#include "fleet.h"
#include <string>

using namespace std;

vector<Vehicle *> Fleet::getVehicles() const {
    return vehicles;
}

void Fleet::addVehicle(Vehicle *v1) {
    vehicles.push_back(v1);
}

int Fleet::numVehicles() const {
    return vehicles.size();
}

int Fleet::lowestYear() const {
    if (vehicles.empty()) return 0;
    int lowest;
    for (auto it=vehicles.begin(); it!=vehicles.end(); ++it){
        if (it==vehicles.begin()) lowest=(*it)->getYear();
        else if((*it)->getYear()<lowest) lowest=(*it)->getYear();
    }
    return lowest;
}

ostream &operator << (ostream & o, const Fleet & f) {
    for (auto it=f.vehicles.begin(); it!=f.vehicles.end(); ++it){
        (*it)->info(o);
    }
    return o;
}

vector<Vehicle *> Fleet::operator()(int yearM) const {
    vector<Vehicle*> v;
    for (auto it=vehicles.begin(); it!=vehicles.end(); ++it) {
        if ((*it)->getYear()==yearM) v.push_back((*it));
    }
    return v;
}

float Fleet::totalTax() const {
    float totalTax=0;
    for (auto it=vehicles.begin(); it!=vehicles.end(); ++it) {
        totalTax += (*it)->calculateTax();
    }
    return totalTax;
}

unsigned int Fleet::removeOldVehicles(int y) {
    unsigned nVehiclesRemoved=0;
    for (auto it=vehicles.begin(); it!=vehicles.end(); ++it) {
        if ((*it)->getYear()<=y) {
            nVehiclesRemoved++;
            vehicles.erase(it);
            --it;
        }
    }
    return nVehiclesRemoved;
}