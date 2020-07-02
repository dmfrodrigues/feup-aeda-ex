/*
 * Postman.h
 */

#ifndef SRC_POSTMAN_H_
#define SRC_POSTMAN_H_

#include "Mail.h"
#include <string>
#include <vector>

class Postman {
	unsigned int id;
	string name;
	vector<Mail *> myMail;
public:
	Postman();
	Postman(string nm);
	void setName(string nm);
	void addMail(Mail *m);
	void addMail(vector<Mail *> mails);
	string getName() const;
	vector<Mail *> getMail() const;
	unsigned int getID() const;
	bool operator<(const Postman &obj) const;
};

template<class T>
unsigned int numberDifferent(const vector<T> &v1){
	if(v1.empty()) return 0;
	unsigned int ret = 1;
	vector<T> v2 = v1;
	for(size_t r = 0; r < v2.size(); ++r)
		for(size_t i = 0; i < v2.size()-1; ++i)
			if(!(v2[i] < v2[i+1]))
				std::swap(v2[i], v2[i+1]);
	for(size_t i = 0; i < v2.size()-1; ++i)
		if(v2[i] != v2[i+1])
			++ret;
	return ret;
}

#endif /* SRC_POSTMAN_H_ */
