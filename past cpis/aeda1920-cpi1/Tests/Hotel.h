#ifndef SRC_HOTEL_H_
#define SRC_HOTEL_H_

#include <vector>
#include <list>
#include <algorithm>

using namespace std;

template <class Chamber>
class Hotel {
	vector<Chamber *> chambers;
	const unsigned int maxCapacity;
	const string city;
    list<Chamber> reservationsDone;
public:
	Hotel(int size, string municipality);
	~Hotel();
	vector<Chamber *> getChambers() const;
	void setChambers(vector<Chamber *> chambers);
	int getCapacity() const;
    list<Chamber> getReservationsDone() const;
	bool addChamber(Chamber *chamber);
    void addReservationDone(Chamber chamber);
    Chamber* removeChamber(string code, int floor);
	float avgArea(int floor) const;
	void sortChambers();
	bool doReservation(string code, int floor);
    list<Chamber> roomsNeverReserved() const;
};

class NoSuchChamberException {
public:
	NoSuchChamberException() { }
};
//TODO
class NoSuchFloorException {
    int floor;
public:
    NoSuchFloorException(int floor){this->floor=floor;}
    int getFloor() { return floor;}
};


template <class Chamber>
Hotel<Chamber>::Hotel(int size, string municipality) : maxCapacity(size), city(municipality) {}

template <class Chamber>
Hotel<Chamber>::~Hotel(){
	typename vector<Chamber *>::const_iterator it;
	for (it=chambers.begin(); it!=chambers.end(); it++) {
		delete *it;
	}
}

template<class Chamber>
vector<Chamber *> Hotel<Chamber>::getChambers() const {
	return chambers;
}

template<class Chamber>
void Hotel<Chamber>::setChambers(vector<Chamber*> chambers) {
	this->chambers = chambers;
}

template<class Chamber>
int Hotel<Chamber>::getCapacity() const {
	return maxCapacity;
}

template<class Chamber>
void Hotel<Chamber>::addReservationDone(Chamber chamber) {
    reservationsDone.push_back(chamber);
}

template<class Chamber>
list<Chamber> Hotel<Chamber>::getReservationsDone() const {
    return reservationsDone;
}

//------------------------------------------------------
//------------------------------------------------------

//TODO
template<class Chamber>
bool Hotel<Chamber>::addChamber(Chamber *chamber) {
    if(chambers.size()==maxCapacity) return false;
    for(typename vector<Chamber*>::const_iterator it = chambers.begin(); it < chambers.end(); it++){
        if(*chamber == *(*it))
            return false;
    }
    chambers.push_back(chamber);
    return true;
}

bool compRoom(const Room *r1, const Room *r2)
{
    if(r1->getCode() == r2 ->getCode())
        return(r1->getFloor()>r2->getFloor());
    return (r1->getCode() < r2 ->getCode());
}


//TODO
template<class Chamber>
void Hotel<Chamber>::sortChambers() {
    sort(chambers.begin(), chambers.end(), compRoom);
}

//TODO
template<class Chamber>
Chamber* Hotel<Chamber>::removeChamber(string code, int floor) {
    typename vector<Chamber *>::const_iterator it = chambers.begin();
    for(it; it!=chambers.end(); it++){
        if ((*it)->getFloor() == floor) {
            if ((*it)->getCode() == code) {
                Chamber * temp = *it;
                chambers.erase(it);
                return temp;
            }
            throw(NoSuchChamberException());
        }
    }
    throw(NoSuchChamberException());
}

//TODO
template<class Chamber>
float Hotel<Chamber>::avgArea(int floor) const {
    float numRooms =0;
    float area=0;
    typename vector<Chamber *>::const_iterator it = chambers.begin();
    for(it; it!=chambers.end(); it++){
        if((*it)->getFloor()==floor){
            area += (*it)->getArea();
            numRooms++;
        }
    }
    if(numRooms==0){
        throw(NoSuchFloorException(floor));
    }
    return area/numRooms;
}

//TODO
template<class Chamber>
bool Hotel<Chamber>::doReservation(string code, int floor){
    typename vector<Chamber *>::const_iterator it = chambers.begin();
    for(it; it!=chambers.end(); it++){
        if((*it)->getFloor()==floor && (*it)->getCode()==code){
            if((*it)->getReservation()==true){ return false;}
            else {
                (*it)->setReservation(true);
                reservationsDone.push_back(*(*it));
                return true;
            }
        }
    }
    return false;
}

//TODO
template<class Chamber>
list<Chamber> Hotel<Chamber>::roomsNeverReserved() const {
    list<Chamber> res;
    typename vector<Chamber *>::const_iterator it = chambers.begin();
    for(it; it!=chambers.end(); it++){
        if(find(reservationsDone.begin(),reservationsDone.end(),(*(*it)))==reservationsDone.end()){
            res.push_back(*(*it));
        }
    }
    return res;
}




#endif /* SRC_HOTEL_H_ */
