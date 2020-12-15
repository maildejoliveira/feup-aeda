#include "game.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;


unsigned int Game::numberOfWords(string phrase)
{
    if ( phrase.length() == 0 ) return 0;

    unsigned n=1;
    size_t pos = phrase.find(' ');
    while (pos != string::npos) {
        phrase = phrase.substr(pos+1);
        pos = phrase.find(' ');
        n++;
    }
    return n;
}

// TODO
Game::Game() = default;

// TODO
Game::Game(list<Kid>& l2) :kids(l2) {}

// TODO
void Game::addKid(const Kid &k1)
{
    kids.push_back(k1);
}

// TODO
list<Kid> Game::getKids() const
{
    list<Kid> res;
    res.assign(kids.begin(),kids.end());
    return res;
}

// TODO
string Game::write() const
{
    string res="";
    list<Kid>::const_iterator i=kids.begin();
    for (i=kids.begin(); i!=kids.end(); i++){
        res+= i->write() + "\n";
    }
    return res;
}

// TODO
Kid& Game::loseGame(string phrase)
{
    Kid *k1 = new Kid();
    int last;
    unsigned int n= numberOfWords(phrase);
    list<Kid>::iterator it=kids.begin();
    while (kids.size()!=0){
        n = numberOfWords(phrase);
        last = kids.size()-n%kids.size();
        int l=last;
        while (last!=1){
            --last;
            if (it!=--kids.end()) it++;
            else it=kids.begin();
        }
        kids.erase(it);
        it=kids.begin();
        for (int i=1; i<l; ++i){
            if (it!=--kids.end()) it++;
            else it=kids.begin();
        }
    }
    k1=&(*it);
    return *k1;
}

// TODO
list<Kid>& Game::reverse()
{
    kids.reverse();
    return kids;
}

// TODO
list<Kid> Game::removeOlder(unsigned id)
{
    list<Kid> res;
    for (list<Kid>::const_iterator i=kids.cbegin(); i!=kids.cend(); ++i){
        if ((*i).getAge()>id) {
            res.push_back((*i));
            kids.erase(i);
            --i;
        }
    }
    return res;
}

// TODO
void Game::setKids(const list<Kid>& l1)
{
    kids.assign(l1.begin(),l1.end());
}

// TODO
bool Game::operator==(Game& g2)
{
    bool t=true;
    list<Kid>::const_iterator i2=g2.kids.cbegin();
    for (list<Kid>::const_iterator i1=kids.cbegin(); i1!=kids.cend(); ++i1){
       if ((*i1)==(*i2)) t=true;
       else return false;
       ++i2;
    }
    return t;
}

// TODO
list<Kid> Game::shuffle() const
{
    list<Kid> res;
    int r=0;
    for (int i=0; i<kids.size(); i++) {
        r = rand()%kids.size();
        cout << r << "\n";
    }
    return res;
}
