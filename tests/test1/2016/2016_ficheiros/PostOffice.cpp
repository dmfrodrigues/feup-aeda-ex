/*
 * PostOffice.cpp
 */

#include "PostOffice.h"
#include <string>

PostOffice::PostOffice(string firstZCode, string lastZCode):
								firstZipCode(firstZCode), lastZipCode(lastZCode)
{}
PostOffice::PostOffice() {}

void PostOffice::addMailToSend(Mail *m) {
	mailToSend.push_back(m);
}

void PostOffice::addMailToDeliver(Mail *m) {
	mailToDeliver.push_back(m);
}

void PostOffice::addPostman(const Postman &p){
	postmen.push_back(p);
}

vector<Mail *> PostOffice::getMailToSend() const {
	return mailToSend;
}

vector<Mail *> PostOffice::getMailToDeliver() const {
	return mailToDeliver;
}

vector<Postman> PostOffice::getPostman() const {
	return postmen;
}

vector<Mail *> PostOffice::removePostman(string name){
	vector<Mail *> ret;
	for(size_t i = 0; i < postmen.size(); ++i){
		if(postmen[i].getName() == name){
			ret = postmen[i].getMail();
			postmen.erase(postmen.begin()+i);
			return ret;
		}
	}
	return ret;
}

vector<Mail *> PostOffice::endOfDay(unsigned int &balance){
	balance = 0;
	vector<Mail *> ret;
	for(Mail *p:mailToSend){
		balance += p->getPrice();
		if(firstZipCode <= p->getZipCode() && p->getZipCode() <= lastZipCode){
			mailToDeliver.push_back(p);
		}else{
			ret.push_back(p);
		}
	}
	mailToSend = vector<Mail *>();
	return ret;
}

Postman PostOffice::addMailToPostman(Mail *m, string name){
	for(Postman &p:postmen){
		if(p.getName() == name){
			p.addMail(m);
			return p;
		}
	}
	throw NoPostmanException(name);
}

NoPostmanException::NoPostmanException(string nm):name(nm){}

string NoPostmanException::getName() const{
	return name;
}
