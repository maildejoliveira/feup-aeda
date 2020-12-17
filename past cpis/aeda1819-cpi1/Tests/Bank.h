/*
 * Bank.h
 */

#ifndef SRC_BANK_H_
#define SRC_BANK_H_

#include "Account.h"
#include <vector>

#include "BankOfficer.h"

template <class T>
unsigned int numberDifferent (const vector<T> & v1){
    int counter = v1.size();
    if(v1.size()==0){
        return 0;
    }
    vector<T> v2;
    for (int i = 0; i<v1.size()-1; i++){
        while(find(v2.begin(), v2.end(), v1[i])!=v2.end()){
            i++;
        }
        v2.push_back(v1[i]);
        int cnt = 0;
        for (int j = i+1; j<v1.size(); j++){
            if(v1[i]==v1[j]){
                cnt++;
            }
            else {

            }
        }
        if(cnt>0){
            counter = counter - cnt;
        }
    }
    return counter;
}

class NoBankOfficerException {
      string name;
public:
    NoBankOfficerException(string name);
    string getName();

};

class Bank {
	vector<Account *> accounts;
	vector<BankOfficer> bankOfficers;
public:
	Bank();
	void addAccount(Account *a);
	void addBankOfficer(BankOfficer b);
	vector<BankOfficer> getBankOfficers() const;
	vector<Account *> getAccounts() const;

	//-------
	double getWithdraw(string cod1) const;
	vector<Account *> removeBankOfficer(string name);
	const BankOfficer& addAccountToBankOfficer(Account *ac, string name);
	void sortAccounts();
};


#endif /* SRC_BANK_H_ */
