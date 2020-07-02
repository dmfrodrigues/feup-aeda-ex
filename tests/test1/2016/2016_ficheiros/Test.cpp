#include "Mail.h"
#include "Postman.h"
#include "PostOffice.h"
#include <vector>
#include <string>

#include <cassert>

using namespace std;

void test_a() {
	vector<int> v1;
	v1.push_back(10); v1.push_back(8);
	v1.push_back(12); v1.push_back(8);
	assert(3 == numberDifferent(v1));
	vector<string> v2;
	v2.push_back("ola"); v2.push_back("ola");
	assert(1 == numberDifferent(v2));
	v2.push_back("rio"); v2.push_back("arvore");
	v2.push_back("sol"); v2.push_back("sol");
	assert(4 == numberDifferent(v2));
}

void test_b() {
	PostOffice po;
	Postman p1;
	p1. setName("joao");
	p1.addMail(new RegularMail("ana", "rui","4400-146", 33));
	p1.addMail(new RegularMail("luis", "rui","4400-146", 33));
	Postman p2;
	p2. setName("paulo");
	p2.addMail(new RegularMail("rui", "ana","3330-454", 33));
	p2.addMail(new RegularMail("luis", "maria","8600-306", 67));
	p2.addMail(new RegularMail("carla", "lara","7100-514", 67));
	Postman p3;
	p3.setName("fernando");
	p3.addMail(new RegularMail("manuel", "ana","3330-454", 33));
	po.addPostman(p1);
	po.addPostman(p2);
	po.addPostman(p3);

	vector <Mail *> mailP = po.removePostman("paulo");
	assert(3 == mailP.size());
	assert(2 ==po.getPostman().size());

	mailP.clear();
	mailP = po.removePostman("sergio");
	assert(0 == mailP.size());

	mailP.clear();
	mailP = po.removePostman("fernando");
	assert(1 == mailP.size());

	mailP.clear();
	mailP = po.removePostman("joao");
	assert(2 == mailP.size());

	assert(0 ==po.getPostman().size());
}

void test_c() {
	RegularMail m1("manuel", "ana","3330-454", 33);
	RegularMail m2("ana", "rui","4400-146", 550);
	GreenMail m3("maria", "luis","2520-110", "bag");
	GreenMail m4("carla", "lara","7100-514", "envelope");

	assert(75 == m1.getPrice());
	assert(325 == m2.getPrice());
	assert(200 == m3.getPrice());
	assert(80 == m4.getPrice());
}

void test_d() {
	PostOffice po("3100-000", "4409-999");
	po.addMailToSend(new RegularMail("manuel", "ana","3330-454", 33));
	po.addMailToSend(new RegularMail("ana", "rui","4400-146", 550));
	po.addMailToSend(new GreenMail("maria", "luis","2520-110", "bag"));
	po.addMailToSend(new GreenMail("carla", "lara","7100-514", "envelope"));

	unsigned int bal = 0;
	vector<Mail *> mailToOtherPO = po.endOfDay(bal);
	assert(680 == bal);
	assert(2 ==mailToOtherPO.size());
	assert(2 ==po.getMailToDeliver().size());
	assert(0 ==po.getMailToSend().size());

	PostOffice po2("3100-000", "4409-999");
	po2.addMailToSend(new RegularMail("rita", "joana","5200-514", 120));

	mailToOtherPO = po2.endOfDay(bal);
	assert(140 == bal);
	assert(1 ==mailToOtherPO.size());
	assert(0 ==po2.getMailToDeliver().size());
	assert(0 ==po2.getMailToSend().size());
}

void test_e() {
	Postman p1("joao");
	Postman p2("rui");
	Postman p3("paulo");

	assert(1 == p1.getID());
	assert(2 == p2.getID());
	assert(3 == p3.getID());
}

void test_f() {
	Postman p1;
	p1. setName("joao");
	p1.addMail(new RegularMail("rui", "ana","3330-454", 33));
	p1.addMail(new RegularMail("ana", "rui","4400-146", 33));
	p1.addMail(new RegularMail("luis", "rui","4400-146", 33));

	Postman p2;
	p2. setName("paulo");
	p2.addMail(new RegularMail("rui", "ana","3330-454", 33));
	p2.addMail(new RegularMail("carla", "lara","7100-514", 67));
	p2.addMail(new RegularMail("luis", "maria","8600-306", 67));

	assert(true == (p1<p2));
	assert(false == (p2<p1));

	p1.addMail(new RegularMail("joana", "rui","4400-146", 33));
	p1.addMail(new RegularMail("rita", "joana","5200-514", 120));
	p1.addMail(new RegularMail("maria", "lara","7100-514", 67));

	p2.addMail(new RegularMail("maria", "lara","8600-306", 67));

	assert(false == (p1<p2));
	assert(true == (p2<p1));
}

void test_g() {
	PostOffice po;
	Postman p1;
	p1. setName("joao");
	p1.addMail(new RegularMail("ana", "rui","4400-146", 33));
	p1.addMail(new RegularMail("luis", "rui","4400-146", 33));
	Postman p2;
	p2. setName("paulo");
	Postman p3;
	p3.setName("fernando");
	p3.addMail(new RegularMail("manuel", "ana","3330-454", 33));
	po.addPostman(p1);
	po.addPostman(p2);
	po.addPostman(p3);

	Postman px = po.addMailToPostman(new RegularMail("rui", "ana","3330-454", 33),"paulo");
	assert(1==px.getMail().size());

	try{
		po.addMailToPostman(new RegularMail("rui", "ana","3330-454", 33),"luis");
		assert(0);
	}catch(NoPostmanException e){
		assert(1);
	}catch(...){
		assert(0);
	}

	try {
		px = po.addMailToPostman(new RegularMail("rui", "ana","3330-454", 33),"joao");
		assert(3==px.getMail().size());
		px = po.addMailToPostman(new RegularMail("rui", "ana","3330-454", 33),"ricardo");
	}
	catch(NoPostmanException &e) {
		assert("ricardo"== e.getName());
	}

	px = po.addMailToPostman(new RegularMail("rui", "ana","3330-454", 33),"fernando");
	assert(2==px.getMail().size());
}


void runSuite(){
	test_a();
	test_b();
	test_c();
	test_d();
	test_e();
	test_f();
	test_g();
}

int main(){
    runSuite();
    return 0;
}
