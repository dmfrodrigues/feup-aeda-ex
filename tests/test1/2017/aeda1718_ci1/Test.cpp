#include "Garage.h"
#include "Car.h"
#include <vector>
#include <string>
#include <cassert>

#include <iostream>
#include <sstream>

using namespace std;

void test_a() {
	FuelCar fc("ford", "fiesta", 30000, 60, 5);
	ElectricCar ec("tesla", "s", 70000, 30, 10);

	assert("ford" == fc.getBrand());
	assert("fiesta" == fc.getModel());
	assert(30000 == fc.getPrice());
	assert(60 == fc.getTank());
	assert(5 == fc.getL_100km());

	assert("tesla" == ec.getBrand());
	assert("s" == ec.getModel());
	assert(70000 == ec.getPrice());
	assert(30 == ec.getBattery());
	assert(10 == ec.getKWh_100km());
}

void test_b() {
	FuelCar fc1("ford", "fiesta");
	FuelCar fc2("ford", "fiesta");
	ElectricCar ec3("tesla", "s");
	HybridCar hc4("tesla", "s");

	assert(fc1 == fc2);
	assert(false == (fc1 == ec3));
	assert(ec3 == (FuelCar) hc4);
}

void test_c() {
	FuelCar fc("ford", "fiesta");
	fc.setTank(60);
	fc.setL_100km(5);
	ElectricCar ec("tesla", "s");
	ec.setBattery(30);
	ec.setKWh_100km(10);
	HybridCar hc("toyota", "prius");
	hc.setTank(60);
	hc.setL_100km(5);
	hc.setBattery(30);
	hc.setKWh_100km(10);

	assert(1200 == fc.range());
	assert(300 == ec.range());
	assert(1500 == hc.range());
}

void test_d() {
	FuelCar* fc1 = new FuelCar("ford", "fiesta");
	FuelCar* fc2 = new FuelCar("ford", "fiesta");
	ElectricCar* ec3 = new ElectricCar("tesla", "s");
	ElectricCar* ec4 = new ElectricCar("tesla", "m");

	Garage<Car> g(2);

	assert(true == g.addVehicle(fc1));
	assert(false == g.addVehicle(fc2));
	assert(true == g.addVehicle(ec3));
	assert(false == g.addVehicle(ec4));
}

void test_e() {
	FuelCar* fc1 = new FuelCar("peugeot", "3008");
	fc1->setPrice(30000);
	fc1->setTank(60);
	fc1->setL_100km(5);
	FuelCar* fc2 = new FuelCar("ford", "fiesta");
	fc2->setPrice(38000);
	fc2->setTank(60);
	fc2->setL_100km(5);
	ElectricCar* ec3 = new ElectricCar("tesla", "s");
	ec3->setPrice(70000);
	ec3->setBattery(30);
	ec3->setKWh_100km(10);
	ElectricCar* ec4 = new ElectricCar("tesla", "m");
	ec4->setPrice(78000);
	ec4->setBattery(30);
	ec4->setKWh_100km(11);

	Garage<Car> g(5);
	vector<Car *> cars;
	cars.push_back(fc1);
	cars.push_back(fc2);
	cars.push_back(ec3);
	cars.push_back(ec4);
	g.setVehicles(cars);
	g.sortVehicles();
	cars = g.getVehicles();

	assert("peugeot" == cars[1]->getBrand());
	assert(30000 == cars[1]->getPrice());
	assert("ford" == cars[0]->getBrand());
	assert(38000 == cars[0]->getPrice());
	assert("tesla" == cars[3]->getBrand());
	assert(70000 == cars[3]->getPrice());
	assert("tesla" == cars[2]->getBrand());
	assert(78000 == cars[2]->getPrice());
}

void test_f() {
	FuelCar* fc1 = new FuelCar("peugeot", "3008");
	fc1->setPrice(30000);
	fc1->setTank(60);
	fc1->setL_100km(5);
	FuelCar* fc2 = new FuelCar("ford", "fiesta");
	fc2->setPrice(38000);
	fc2->setTank(60);
	fc2->setL_100km(5);
	ElectricCar* ec3 = new ElectricCar("tesla", "s");
	ec3->setPrice(70000);
	ec3->setBattery(30);
	ec3->setKWh_100km(10);
	ElectricCar* ec4 = new ElectricCar("tesla", "m");
	ec4->setPrice(78000);
	ec4->setBattery(30);
	ec4->setKWh_100km(11);

	Garage<Car> g(5);
	vector<Car *> cars;
	cars.push_back(fc1);
	cars.push_back(fc2);
	cars.push_back(ec3);
	cars.push_back(ec4);
	g.setVehicles(cars);

    assert(fc1 == g.removeVehicle("peugeot", "3008"));
    assert(3 == g.getVehicles().size());
	try{
		g.removeVehicle("ford", "focus");
		assert(0);
	}catch(NoSuchVehicleException){
		assert(1);
	}catch(...){
		assert(0);
	}
    assert(ec4 == g.removeVehicle("tesla", "m"));
    assert(2 == g.getVehicles().size());
}

void test_g() {
	FuelCar* fc1 = new FuelCar("peugeot", "3008");
	fc1->setPrice(30000);
	fc1->setTank(60);
	fc1->setL_100km(5);
	FuelCar* fc2 = new FuelCar("peugeot", "2008");
	fc2->setPrice(20000);
	fc2->setTank(55);
	fc2->setL_100km(4);
	ElectricCar* ec3 = new ElectricCar("peugeot", "ion");
	ec3->setPrice(13000);
	ec3->setBattery(30);
	ec3->setKWh_100km(10);
	ElectricCar* ec4 = new ElectricCar("tesla", "m");
	ec4->setPrice(78000);
	ec4->setBattery(30);
	ec4->setKWh_100km(11);

	Garage<Car> g(5);
	vector<Car *> cars;
	cars.push_back(fc1);
	cars.push_back(fc2);
	cars.push_back(ec3);
	cars.push_back(ec4);
	g.setVehicles(cars);

	try{
		g.avgPrice("ford");
		assert(0);
	}catch(NoSuchBrandException){
		assert(1);
	}catch(...){
		assert(0);
	}
	try {
		g.avgPrice("ford");
	} catch(NoSuchBrandException &e) {
		assert("ford" == e.getBrand());
	}
	assert(21000 == g.avgPrice("peugeot"));
}

void test_h() {
	FuelCar fc("toyota", "auris");
	fc.setPrice(30000);
	fc.setTank(60);
	fc.setL_100km(5);
	ElectricCar ec("toyota", "yaris");
	ec.setPrice(20000);
	ec.setBattery(30);
	ec.setKWh_100km(10);
	HybridCar hc("toyota", "prius", 40000, 60, 5, 30, 10);

	stringstream ss1;
	ss1 << fc;
	assert("toyota auris (30000)" == ss1.str());
	stringstream ss2;
	ss2 << ec;
	assert("toyota yaris (20000)" == ss2.str());
	stringstream ss3;
	ss3 << (FuelCar) hc;
	assert("toyota prius (40000)" == ss3.str());
}


void runSuite(){
	test_a();
	test_b();
	test_c();
	test_d();
	test_e();
	test_f();
	test_g();
	test_h();
}

int main(){
    runSuite();
    return 0;
}
