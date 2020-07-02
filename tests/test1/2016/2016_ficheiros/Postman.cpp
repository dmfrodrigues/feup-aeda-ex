/*
 * Postman.cpp
 */
#include "Postman.h"


Postman::Postman(): id(0) {}

Postman::Postman(string nm):name(nm){
	static unsigned int index = 1;
	id = index++;
}

void Postman::setName(string nm){
	name = nm;
}

string Postman::getName() const{
	return name;
}

vector<Mail *> Postman::getMail() const {
	return myMail;
}

void Postman::addMail(Mail *m) {
	myMail.push_back(m);
}

void Postman::addMail(vector<Mail *> mails) {
	myMail.insert(myMail.end(),mails.begin(),mails.end());
}

unsigned int Postman::getID() const{
	return id;
}

bool Postman::operator<(const Postman &obj) const{
	vector<string> zipcodes1, zipcodes2;
	for(const Mail *p:    myMail) zipcodes1.push_back(p->getZipCode());
	for(const Mail *p:obj.myMail) zipcodes2.push_back(p->getZipCode());
	unsigned int diff1 = numberDifferent(zipcodes1);
	unsigned int diff2 = numberDifferent(zipcodes2);
	return (diff1 < diff2);
}
