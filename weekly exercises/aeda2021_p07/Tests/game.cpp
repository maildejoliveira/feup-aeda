#include "game.h"
#include <sstream>
#include <bits/stdc++.h>


//TODO
ostream &operator << (ostream &os, Circle &c1)
{
	return os;
}

void Circle::oneMoreVisit() {
    nVisits++;
}


//TODO 2a)
Game::Game(int h, vector<int> &points, vector<bool> &states)
{
    game = startGame(0,h,points,states);
}


//TODO
string Game::writeGame()
{
	string g="";
    BTItrLevel<Circle> it(game);
	while(!it.isAtEnd()){
	    g += to_string(it.retrieve().getPoints()) + "-";
	    if(it.retrieve().getState()) g+="true";
	    else g+="false";
	    g+= "-" + to_string(it.retrieve().getNVisits())+ "\n";
	    it.advance();
	}
	return g;
}


//TODO
int Game::move()
{
    int pos=1; int points=-1;
    BTItrLevel<Circle> it(game);
    if (it.isAtEnd()) return points;
    while (true) {
        Circle &c1=it.retrieve();
        bool state=c1.getState();
        int n;
        if (!state) n=pos;
        else n=pos+1;
        c1.changeState();
        c1.oneMoreVisit();
        points=c1.getPoints();
        int i=0;
        while(i<n && !it.isAtEnd()) {
            it.advance();
            i++;
        }
        if (!it.isAtEnd()) pos+=n; else break;
    }
    return points;

}


//TODO d)
int Game::mostVisited()
{
    vector<int> visits;
    BTItrLevel<Circle> it(game);
    it.advance();
    while(!it.isAtEnd()){
        visits.push_back(it.retrieve().getNVisits());
        it.advance();
    }
    sort(visits.begin(),visits.end());
    return visits[visits.size()-1];

}

BinaryTree<Circle> Game::startGame(int pos, int niv, vector<int> &points, vector<bool> &states) {
    Circle c1(points[pos],states[pos]);
    if(niv==0) return BinaryTree<Circle>(c1);
    BinaryTree<Circle> left = startGame(2*pos+1,niv-1,points,states);
    BinaryTree<Circle> right = startGame(2*pos+2,niv-1,points,states);
    return BinaryTree<Circle>(c1,left,right);
}
