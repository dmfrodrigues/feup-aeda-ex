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

// a alterar
BankOfficer::BankOfficer(string nm):name(nm){
    static unsigned index = 1;
    this->id = index++;
}

bool BankOfficer::operator>(const BankOfficer &b) const{
    if(myAccounts.size() != b.myAccounts.size()) return (myAccounts.size() > b.myAccounts.size());
    return (name > b.name);
}

NoBankOfficerException::NoBankOfficerException(string nm):name(nm){}

string NoBankOfficerException::getName()const{ return name; }
