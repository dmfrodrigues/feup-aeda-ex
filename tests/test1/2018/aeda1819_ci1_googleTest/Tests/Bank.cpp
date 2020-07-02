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

// a alterar
double Bank::getWithdraw(string cod1) const{
    double ret = 0;
    for(const Account* p:accounts)
        if(p->getCodH() == cod1)
            ret += p->getWithdraw();
	return ret;
}


// a alterar
vector<Account *> Bank::removeBankOfficer(string name){
    vector<Account *> res;
    for(auto it = bankOfficers.begin(); it != bankOfficers.end(); ++it){
        if(it->getName() == name){
            res = it->getAccounts();
            bankOfficers.erase(it);
            return res;
        }
    }
	return res;
}


// a alterar
const BankOfficer & Bank::addAccountToBankOfficer(Account *ac, string name) {
    for(BankOfficer &b:bankOfficers){
        if(b.getName() == name){
            b.addAccount(ac);
            return b;
        }
    }
    throw NoBankOfficerException(name);
}


bool comp(const Account &a1, const Account &a2){
    if(a1.getBalance() != a2.getBalance()) return (a1.getBalance() < a2.getBalance());
    return (a1.getCodIBAN() < a2.getCodIBAN());
}

// a alterar
void Bank::sortAccounts() {
    for(unsigned r = 0; r < accounts.size(); ++r) {
        for (unsigned i = 0; i < accounts.size() - 1; ++i) {
            if (!comp(*accounts[i], *accounts[i + 1])) {
                swap(accounts[i], accounts[i + 1]);
            }
        }
    }
}
