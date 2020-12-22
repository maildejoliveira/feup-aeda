/*
 * BankOfficer.cpp
 */
#include "BankOfficer.h"


BankOfficer::BankOfficer(): id(0) {}

void BankOfficer::setName(string nm){
	name = nm;
}

string BankOfficer::getName() const{
	return name;
}

vector<Account *> BankOfficer::getAccounts() const {
	return myAccounts;
}

void BankOfficer::addAccount(Account *a) {
	myAccounts.push_back(a);
}

unsigned int BankOfficer::getID() const{
	return id;
}


// ----------------------------------------------------------------------------------------------

BankOfficer::BankOfficer(string name): name(name) {
    idActual++;
    this->id=idActual;
}

bool BankOfficer::operator>(const BankOfficer &b2) {
    if(myAccounts.size()>b2.myAccounts.size()){
        return true;
    }
    else if(myAccounts.size()<b2.myAccounts.size()){
        return false;
    }
    else if(name>b2.name){
        return true;
    }
    else return false;
}



