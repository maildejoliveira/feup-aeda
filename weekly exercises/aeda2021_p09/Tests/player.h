#ifndef PLAYER_H_
#define PLAYER_H_

#include "bet.h"
#include <string>
using namespace std;

//TODO
struct betHash
{
	int operator() (const Bet& b) const
	{
	    int v=0;
	    for(auto it = b.getNumbers().begin(); it!=b.getNumbers().end(); it++){
	        v = 37*v + (*it);
	    }
		return v;
	}
	
	bool operator() (const Bet& b1, const Bet& b2) const
	{
		return comp(b1,b2);
	}
};


typedef unordered_set<Bet, betHash, betHash> tabHBet;

class Player
{
	tabHBet bets;
	string name;
public:
	Player(string nm="anonymous") { name=nm; }
	void addBet(const Bet & ap);
	unsigned betsInNumber(unsigned num) const;
	tabHBet drawnBets(const tabHInt& draw) const;
	unsigned getNumBets() const { return bets.size(); }
};

#endif 
