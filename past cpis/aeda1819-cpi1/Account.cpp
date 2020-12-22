/*
 * Account.cpp
 */
#include <iostream>
#include "Account.h"
using namespace std;

Account::Account(string hold, string codeH, string codeA, double bal): holder(hold), codeHolder(codeH), codeIBAN(codeA), balance(bal) {}

Account::~Account(){ }

string Account::getCodH() const {
	return codeHolder;
}

string Account::getCodIBAN() const {
	return codeIBAN;
}

double Account::getBalance() const {
	return balance;
}

double Account::getCharge() const {
    return 0;
}

double Account::getWithdraw() const {
    return balance;
}


SavingsAccount::SavingsAccount (string hold, string codeH, string codeA, double bal, double pct):
		Account(hold, codeH, codeA, bal), rate(pct/100)
{ }

double SavingsAccount::getCharge() const {
    if((rate*100)>2){
        return 0.8;
    }
    else{
        return 0;
    }
    return Account::getCharge();
}

double SavingsAccount::getWithdraw() const {
    return balance;
}


CheckingAccount::CheckingAccount(string hold, string codeH, string codeA, double bal,double lim):
			Account(hold, codeH, codeA, bal) {
	limit = lim;
}

double CheckingAccount::getCharge() const {
    if(limit<=500){
        return 0.5;
    }
    else if(limit <=1000){
        return 0.25;
    }
    else{
        return 0;
    }
    return Account::getCharge();
}

double CheckingAccount::getWithdraw() const {
    return Account::getWithdraw();
}


TimeAccount::TimeAccount(string hold, string codeH, string codeA, double bal, double pct):
			SavingsAccount(hold, codeH, codeA, bal, pct) {
	funds_avail = balance*rate;
}

double TimeAccount::getWithdraw() const {
    return balance*rate;
}


bool compAccounts(const Account *a1, const Account *a2) {
    if(a1->getBalance()<a2->getBalance()) return true;
    else if(a1->getBalance()>a2->getBalance()) return false;
    else if(a1->getBalance()==a2->getBalance()) {
        if(a1->getCodIBAN()<a2->getCodIBAN()){
            return true;
        }
    }
    return false;
}
