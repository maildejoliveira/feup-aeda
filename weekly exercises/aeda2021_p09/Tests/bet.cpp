#include "bet.h"
#include <iostream>
#include <sstream>
using namespace std;

bool comp(const Bet &b1, const Bet &b2){
    if(b1.getNumbers().size()!=b2.getNumbers().size()) return false;
    for(auto it = b2.getNumbers().begin(); it!=b2.getNumbers().end(); it++){
        if(!b1.contains(*it)) return false;
    }
    return true;
}

//TODO
bool Bet::contains(unsigned num) const
{
    auto it = numbers.end();
	if(numbers.find(num)==it)
        return false;
	return true;
}

//TODO
void Bet::generateBet(const vector<unsigned>& values, unsigned n)
{
    numbers.empty();
    int i = 0;
    while(numbers.size()<n){
        numbers.insert(values[i]);
        i++;
    }
}

//TODO
unsigned Bet::countRights(const tabHInt& draw) const
{
	unsigned counter=0;
	for(auto it = draw.begin(); it!= draw.end(); it++){
	    if(this->contains(*it)) counter++;
	}
    return counter;
}

unsigned Bet::countNumNums(unsigned int num) const {
    unsigned counter = 0;
    for(auto it = numbers.begin(); it!=numbers.end(); it++){
        if(*it==num){
            counter++;
        }
    }
    return counter;
}

