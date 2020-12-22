/*
 * Bank.cpp
 */

#include "Bank.h"
#include <algorithm>
#include <string>

Bank::Bank() {}

void Bank::addAccount(Account *a) {
	accounts.push_back(a);
}

void Bank::addBankOfficer(BankOfficer b){
	bankOfficers.push_back(b);
}

vector<BankOfficer> Bank::getBankOfficers() const {
	return bankOfficers;
}

vector<Account *> Bank::getAccounts() const {
	return accounts;
}


// ----------------------------------------------------------------------------------------------

double Bank::getWithdraw(string cod1) const{
    double result=0;
    for(int i=0; i<accounts.size(); i++){
        if(accounts[i]->getCodH()==cod1){
            result += accounts[i]->getWithdraw();
        }
    }
    return result;
}

vector<Account *> Bank::removeBankOfficer(string name){
	vector<Account *> res;
	for(auto it=bankOfficers.begin(); it!=bankOfficers.end(); it++){
	    if((*it).getName()==name){
	        res = (*it).getAccounts();
	        bankOfficers.erase(it);
	        return res;
	    }
	}
	return res;
}


// a alterar
const BankOfficer & Bank::addAccountToBankOfficer(Account *ac, string name) {
    BankOfficer *bo= new BankOfficer();
    for(int i =0; i<bankOfficers.size(); i++){
        if(bankOfficers[i].getName()==name){
            bankOfficers[i].addAccount(ac);
            return bankOfficers[i];
        }
    }
    throw(NoBankOfficerException(name));
}


// a alterar
void Bank::sortAccounts() {
    sort(accounts.begin(), accounts.end(), compAccounts);
}

NoBankOfficerException::NoBankOfficerException(string name): name(name) {}

string NoBankOfficerException::getName() {
    return name;;
}
