#include "player.h"

//TODO
void Player::addBet(const Bet& b)
{
    bets.insert(b);
}

//TODO
unsigned Player::betsInNumber(unsigned num) const
{
    int counter=0;
    for(auto it= bets.begin(); it!=bets.end(); it++){
        counter += (*it).countNumNums(num);
    }
    return counter;
}

//TODO
tabHBet Player::drawnBets(const tabHInt& draw) const
{
	tabHBet res;
	for(auto it=bets.begin(); it!=bets.end(); it++){
	    if(it->countRights(draw)>3) res.insert(*it);
	}
	return res;
}
